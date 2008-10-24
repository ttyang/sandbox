// Copyright Kevin Sopp 2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MATH_MP_INT_DETAIL_PRIMITIVE_OPS
#define BOOST_MP_MATH_MP_INT_DETAIL_PRIMITIVE_OPS

namespace boost {
namespace mp_math {
namespace detail {


// this struct contains some basic arithmetic algorithms
// which can be implemented via assembly rather easily

template<typename DigitT, typename WordT, typename SizeT>
struct basic_primitive_ops
{
  typedef DigitT digit_type;
  typedef WordT  word_type;
  typedef SizeT  size_type;
  
  static const word_type digit_bits = std::numeric_limits<digit_type>::digits;

  // ADD ------------------------------------

  // add x to the digits in y and store result in z
  // ylen must be > 0
  // returns: the last carry (it will not get stored in z)
  static digit_type add_single_digit(digit_type* z,
                                     const digit_type* y, size_type ylen,
                                     digit_type x);

  // z = x + y, returns last carry
  static digit_type add_digits(digit_type* z,
                               const digit_type* x,
                               const digit_type* y,
                               size_type num);

  // ripples the carry c up through n digits of x and stores results in z
  // returns the number of digits the carry rippled through and stores the last
  // carry in c. If there isn't a last carry then c will be 0.
  static size_type ripple_carry(digit_type* z,
                                const digit_type* x,
                                size_type n,
                                digit_type& c);

  // z = x + y, where xlen >= ylen
  // z and x may not overlap
  static void add_magnitude(digit_type* z,
                            const digit_type* x, size_type xlen,
                            const digit_type* y, size_type ylen);

  // SUB ------------------------------------

  // subtracts x from the digits in y and store result in z
  static void subtract_single_digit(digit_type* z,
                                    const digit_type* y, size_type ylen,
                                    digit_type x);

  // z = x - y, returns last borrow
  static digit_type subtract_digits(digit_type* z,
                                    const digit_type* x,
                                    const digit_type* y,
                                    size_type num);

  // ripples the borrow up through n digits of x and stores results in z
  // returns the number of digits the borrow rippled through
  static size_type ripple_borrow(digit_type* z,
                                 const digit_type* x,
                                 size_type n,
                                 digit_type borrow);

  // z = x - y, where x >= y
  static void sub_smaller_magnitude(digit_type* z,
                                    const digit_type* x, size_type xlen,
                                    const digit_type* y, size_type ylen);

  // MUL ------------------------------------

  // multiply y of length ylen with x and store result in z
  // returns: the last carry (it will not get stored in z)
  static digit_type multiply_by_digit(digit_type* z,
                                      const digit_type* y, size_type ylen,
                                      digit_type x);

  // z = x * y
  static void classic_mul(digit_type* z, const digit_type* x, size_type x_size,
                                         const digit_type* y, size_type y_size);

  // z = x * y; precondition: x_size >= y_size
  static void comba_mul(digit_type* z, const digit_type* x, size_type x_size,
                                       const digit_type* y, size_type y_size);

  // z = x * y; for numbers of the same size
  static void comba_mul(digit_type* z,
                        const digit_type* x,
                        const digit_type* y, size_type xy_size);
  
  // SQR ------------------------------------

  // z = x * x;
  static void comba_sqr(digit_type* z, const digit_type* x, size_type x_size);
};



template<typename D, typename W, typename S>
inline
typename basic_primitive_ops<D,W,S>::digit_type
basic_primitive_ops<D,W,S>::add_single_digit(digit_type* z,
                                             const digit_type* y, size_type ylen,
                                             digit_type x)
{
  word_type carry = static_cast<word_type>(*y++) + x;
  *z++ = static_cast<digit_type>(carry);
  carry >>= digit_bits;

  while (carry && --ylen)
  {
    carry += static_cast<word_type>(*y++);
    *z++ = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  return static_cast<digit_type>(carry);
}


template<typename D, typename W, typename S>
inline
typename basic_primitive_ops<D,W,S>::digit_type
basic_primitive_ops<D,W,S>::add_digits(digit_type* z,
                                       const digit_type* x,
                                       const digit_type* y, size_type n)
{
  word_type carry = 0;

  while (n--)
  {
    carry += static_cast<word_type>(*x++) + static_cast<word_type>(*y++);
    *z++ = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  return static_cast<digit_type>(carry);
}

template<typename D, typename W, typename S>
inline
typename basic_primitive_ops<D,W,S>::size_type
basic_primitive_ops<D,W,S>::ripple_carry(digit_type* z,
                                         const digit_type* x,
                                         size_type n,
                                         digit_type& carry)
{
  word_type c = carry;
  size_type i = 0;

  for (; c && (i < n); ++i)
  {
    c += static_cast<word_type>(*x++);
    *z++ = static_cast<digit_type>(c);
    c >>= digit_bits;
  }

  carry = static_cast<digit_type>(c);
  
  return i;
}

template<typename D, typename W, typename S>
inline
void basic_primitive_ops<D,W,S>::add_magnitude(
    digit_type* z,
    const digit_type* x, size_type xlen,
    const digit_type* y, size_type ylen)
{
  digit_type carry = add_digits(z, x, y, ylen);
  
  size_type n = ripple_carry(z + ylen, x + ylen, xlen - ylen, carry);

  if (carry)
    *(z + n++) = carry; // wrong
  
  const size_type cur = ylen + n;
  if (cur < xlen)
    std::memcpy(z + cur, x + cur, (xlen - cur) * sizeof(digit_type));
}

template<typename D, typename W, typename S>
inline
void
basic_primitive_ops<D,W,S>::subtract_single_digit(digit_type* z,
                                                  const digit_type* y, size_type ylen,
                                                  digit_type x)
{
  word_type borrow = static_cast<word_type>(*y++) - x;
  *z++ = static_cast<digit_type>(borrow);
  borrow >>= static_cast<word_type>(std::numeric_limits<word_type>::digits - 1);

  while (borrow && --ylen)
  {
    borrow = static_cast<word_type>(*y++) - borrow;
    *z++   = static_cast<digit_type>(borrow);
    borrow >>= static_cast<word_type>(std::numeric_limits<word_type>::digits - 1);
  }
}

template<typename D, typename W, typename S>
inline
typename basic_primitive_ops<D,W,S>::digit_type
basic_primitive_ops<D,W,S>::subtract_digits(digit_type* z,
                                            const digit_type* x,
                                            const digit_type* y,
                                            size_type n)
{
  word_type borrow = 0;

  while (n--)
  {
    borrow = static_cast<word_type>(*x++) - static_cast<word_type>(*y++) - borrow;
    *z++   = static_cast<digit_type>(borrow);
    borrow >>= std::numeric_limits<word_type>::digits - 1;
  }

  return static_cast<digit_type>(borrow);
}

template<typename D, typename W, typename S>
inline
typename basic_primitive_ops<D,W,S>::size_type
basic_primitive_ops<D,W,S>::ripple_borrow(digit_type* z,
                                          const digit_type* x,
                                          size_type n,
                                          digit_type borrow)
{
  word_type b = borrow;
  size_type i = 0;
  for (; b && (i < n); ++i)
  {
    b    = static_cast<word_type>(*x++) - b;
    *z++ = static_cast<digit_type>(b);
    b >>= std::numeric_limits<word_type>::digits - 1;
  }
  
  return i;
}

template<typename D, typename W, typename S>
inline
void basic_primitive_ops<D,W,S>::sub_smaller_magnitude(
    digit_type* z,
    const digit_type* x, size_type xlen,
    const digit_type* y, size_type ylen)
{
  const digit_type borrow = subtract_digits(z, x, y, ylen);

  const size_type n = ripple_borrow(z + ylen, x + ylen, xlen - ylen, borrow);

  const size_type cur = ylen + n;
  std::memcpy(z + cur, x + cur, (xlen - cur) * sizeof(digit_type));
}


template<typename D, typename W, typename S>
inline
typename basic_primitive_ops<D,W,S>::digit_type
basic_primitive_ops<D,W,S>::multiply_by_digit(digit_type* z,
                                              const digit_type* y, size_type ylen,
                                              digit_type x)
{
  digit_type carry = 0;

  while (ylen--)
  {
    const word_type tmp = static_cast<word_type>(carry)
                        + static_cast<word_type>(*y++)
                        * static_cast<word_type>(x);
    *z++ = static_cast<digit_type>(tmp);
    carry = static_cast<digit_type>(tmp >> digit_bits);
  }
  return carry;
}

template<typename D, typename W, typename S>
void
basic_primitive_ops<D,W,S>::classic_mul(
    digit_type* z, const digit_type* x, size_type x_size,
                   const digit_type* y, size_type y_size)
{
  // phase 1
  word_type tmp = static_cast<word_type>(x[0]) * static_cast<word_type>(y[0]);
  z[0] = static_cast<digit_type>(tmp);
  
  for (size_type i = 1; i < x_size; ++i)
  {
    tmp = (tmp >> digit_bits)
        + static_cast<word_type>(x[i])
        * static_cast<word_type>(y[0]);
    z[i] = static_cast<digit_type>(tmp);
  }
  
  tmp >>= digit_bits;
  z[x_size] = static_cast<digit_type>(tmp);
  
  // phase 2
  for (size_type i = 1; i < y_size; ++i)
  {
    tmp = static_cast<word_type>(y[i])
        * static_cast<word_type>(x[0])
        + static_cast<word_type>(z[i]);
    z[i] = static_cast<digit_type>(tmp);
    
    for (size_type j = 1; j < x_size; ++j)
    {
      tmp = (tmp >> digit_bits)
          + static_cast<word_type>(y[i]) * static_cast<word_type>(x[j])
          + static_cast<word_type>(z[i+j]);
      z[i+j] = static_cast<digit_type>(tmp);
    }
    
    tmp >>= digit_bits;
    z[i + x_size] = static_cast<digit_type>(tmp);
  }
}


// K = 2 ^ (alpha - (2*beta-1))
// alpha = num bits of word_type, beta = num bits of digit_type
// calculation works in 3 phases
//                65432
//              x   223
//----------------------------------
//              | 18  15 | 12  9  6
//           12 | 10   8 |  6  4
//        12 10 |  8   6 |  4 
//              |        |    
// phase:   3   |    2   |    1
//
// TODO handle too long columns => carry may overflow. This can happen if
// digit_type is 8bit; in that case delegate to classic_mul routine in
// operator *= (). Just check if (smaller number).used_ >= overflow_count.
template<typename D, typename W, typename S>
void
basic_primitive_ops<D,W,S>::comba_mul(
    digit_type* z, const digit_type* x, size_type x_size,
                   const digit_type* y, size_type y_size)
{
  assert(x_size >= y_size);

  const size_type k = x_size + y_size;

  word_type acc = 0;  // accumulator in each column
  word_type carry = 0;
  
  // phase 1
  for (size_type i = 0; i < y_size; ++i)
  {
    for (size_type j = 0; j <= i; ++j)
    {
      const word_type r = static_cast<word_type>(y[j])
                        * static_cast<word_type>(x[i-j]);
      acc += r;
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }
    *z++ = static_cast<digit_type>(acc);
    acc  = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }
  
  // phase 2
  for (size_type i = 0; i < x_size - y_size; ++i)
  {
    size_type j = 0;
    size_type m = y_size;
    while (j < y_size)
    {
      const word_type r = static_cast<word_type>(y[j])
                        * static_cast<word_type>(x[m+i]);
      acc += r;
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
      ++j; --m;
    }
    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }
  
  // phase 3
  for (size_type i = x_size; i < k - 1; ++i)
  {
    for (size_type j = y_size - (k - i - 1); j < y_size; ++j)
    {
      const word_type r = static_cast<word_type>(y[j])
                        * static_cast<word_type>(x[i-j]);
      acc += r;
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }
    *z++ = static_cast<digit_type>(acc);
    acc  = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }
  
  *z = static_cast<digit_type>(acc);
}

template<typename D, typename W, typename S>
void
basic_primitive_ops<D,W,S>::comba_mul(digit_type* z,
                                      const digit_type* x,
                                      const digit_type* y, size_type xy_size)
{
  word_type acc = 0;  // accumulator for each column
  word_type carry = 0;

  // phase 1
  for (size_type i = 0; i < xy_size; ++i)
  {
    for (size_type j = 0; j <= i; ++j)
    {
      const word_type r = static_cast<word_type>(x[j])
                        * static_cast<word_type>(y[i-j]);
      acc += r;
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }
    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  // phase 2
  for (size_type i = xy_size; i < 2 * xy_size - 1; ++i)
  {
    for (size_type j = i - xy_size + 1; j < xy_size; ++j)
    {
      const word_type r = static_cast<word_type>(x[j])
                        * static_cast<word_type>(y[i-j]);
      acc += r;
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }
    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  *z = static_cast<digit_type>(acc);
}

template<typename D, typename W, typename S>
void
basic_primitive_ops<D,W,S>::comba_sqr(digit_type* z,
                                      const digit_type* x,
                                      size_type x_size)
{
  word_type acc = 0;  // accumulator for each column
  word_type carry = 0;

  // phase 1
  for (size_type i = 0; i < x_size; ++i)
  {
    for (size_type j = 0; j <= i; ++j)
    {
      const word_type r = static_cast<word_type>(x[j])
                        * static_cast<word_type>(x[i-j]);
      acc += r;
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }
    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  // phase 2
  for (size_type i = x_size; i < 2 * x_size - 1; ++i)
  {
    for (size_type j = i - x_size + 1; j < x_size; ++j)
    {
      const word_type r = static_cast<word_type>(x[j])
                        * static_cast<word_type>(x[i-j]);
      acc += r;
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }
    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  *z = static_cast<digit_type>(acc);
}





// This exists to ease development of primitive_ops specializations. If a
// specialized function isn't available yet, the compiler will just choose the
// inherited one. It also means that whenever we add a new function to
// basic_primitive_ops no code will break since it will be available to all
// specializations as well.
template<typename D, typename W, typename S>
struct primitive_ops : basic_primitive_ops<D,W,S>
{};


// Here we include primitive_ops specializations that use assembler

#if defined(BOOST_MP_MATH_MP_INT_USE_ASM)
  
  #if defined(__GNU__)
    #if defined(__386__)
      #include <boost/mp_math/mp_int/detail/asm/x86/gnu_386_primitive_ops.hpp>
    #endif
  #endif

#endif



} // namespace detail
} // namespace mp_math
} // namespace boost

#endif

