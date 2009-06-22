// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MATH_INTEGER_DETAIL_BASE_PRIMITIVE_OPS
#define BOOST_MP_MATH_INTEGER_DETAIL_BASE_PRIMITIVE_OPS

#include <cassert>
#include <cstring>
#include <algorithm>
#include <boost/cstdint.hpp>
#include <iostream>

namespace boost {
namespace mp_math {
namespace detail {
namespace base {


// this struct contains some basic arithmetic algorithms
// which can be implemented via assembly rather easily

#ifdef BOOST_MP_MATH_PRIMITIVE_OPS_OLD
template<typename DigitT, typename WordT, typename SizeT>
struct basic_primitive_ops
{
  typedef DigitT digit_type;
  typedef WordT  word_type;
  typedef SizeT  size_type;

  static const word_type digit_bits = std::numeric_limits<digit_type>::digits;

  // ADD ------------------------------------
  // z = x + y, returns carry
  static digit_type add(digit_type& z, digit_type x, digit_type y);
  // z += x, returns carry
  static digit_type add(digit_type& z, digit_type x);
  // z += x * y, returns carry
  static digit_type multiply_add(digit_type& z_hi, digit_type& z_lo,
                                 digit_type x, digit_type y);
  // z = x * y, returns high part of the product
  static digit_type mul(digit_type& z, digit_type x, digit_type y);

  // add y to the digits in x and store result in z
  // xlen must be > 0
  // returns: the last carry (it will not get stored in z)
  static digit_type add_single_digit(digit_type* z,
                                     const digit_type* x, size_type xlen,
                                     digit_type y);

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
  // returns last carry
  static digit_type add_smaller_magnitude(digit_type* z,
                                          const digit_type* x, size_type xlen,
                                          const digit_type* y, size_type ylen);

  // SUB ------------------------------------

  // subtracts x from the digits in y and store result in z
  static void subtract_single_digit(digit_type* z,
                                    const digit_type* x, size_type xlen,
                                    digit_type y);

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
                                      const digit_type* x, size_type xlen,
                                      digit_type y);

  // z = x * 2
  static digit_type multiply_by_two(digit_type* z,
                                    const digit_type* x, size_type len);

  // z = x * y
  static void classic_mul(digit_type* z, const digit_type* x, size_type xlen,
                                         const digit_type* y, size_type ylen);

  // z = x * y; precondition: xlen >= ylen
  static void comba_mul(digit_type* z, const digit_type* x, size_type xlen,
                                       const digit_type* y, size_type ylen);

  // z = x * y; for numbers of the same size
  static void comba_mul(digit_type* z,
                        const digit_type* x,
                        const digit_type* y, size_type xylen);

  // z = x * y; precondition: xlen >= ylen and workspace must have at least ylen
  // digits this function is only used by the integral ops interaction code, it
  // allows x and z to be the same pointer.
  static void comba_mul(digit_type* z, const digit_type* x, size_type xlen,
                                       const digit_type* y, size_type ylen,
                                       digit_type* workspace);

  // computes the lower num digits of the product of x and y
  static void comba_mul_lo(digit_type* z, const digit_type* x, size_type xlen,
                                          const digit_type* y, size_type ylen,
                                          size_type num);

  // computes the high product of x and y without num least significant digits
  // basically the result is: z = (x*y) >> radix^num
  static void comba_mul_hi(digit_type* z, const digit_type* x, size_type xlen,
                                          const digit_type* y, size_type ylen,
                                          size_type num);

  // SQR ------------------------------------

  // z = x * x;
  static void comba_sqr(digit_type* z, const digit_type* x, size_type xlen);

  // MADD ------------------------------------

  // z = z + x * y
  static digit_type multiply_add_digits(digit_type* z,
                                        const digit_type* x,
                                        digit_type y,
                                        size_type n);

  // DIV -------------------------------------

  // z = x / 2
  static void divide_by_two(digit_type* z, const digit_type* x, size_type len);

  // z = x / y
  // returns remainder
  static digit_type divide_by_digit(digit_type* z,
                                    const digit_type* x, size_type xlen,
                                    digit_type y);

  // q = x/y, r = x%y; workspace must have length of ylen + 1
  static void divide(digit_type* q, digit_type* r,
                     const digit_type* x, size_type xlen,
                     const digit_type* y, size_type ylen,
                     digit_type* workspace);

  // SHIFT -----------------------------------

  // shifts x by n bits to the left, where n > 0 && n < digit_bits
  // returns carry
  static digit_type shift_bits_left(digit_type* x, size_type xlen, size_type n);

  // shifts x by n bits to the right, where n > 0 && n < digit_bits
  static void shift_bits_right(digit_type* x, size_type xlen, size_type n);

  // CMP -------------------------------------

  // returns  1 if x  > y
  // returns  0 if x == y
  // returns -1 if x  < y
  static int compare_magnitude(const digit_type* x, size_type xlen,
                               const digit_type* y, size_type ylen);
};



template<typename D, typename W, typename S>
inline
D basic_primitive_ops<D,W,S>::add(digit_type& z, digit_type x, digit_type y)
{
  z = x + y;
  return z < x;
}

template<typename D, typename W, typename S>
inline
D basic_primitive_ops<D,W,S>::add(digit_type& z, digit_type x)
{
  z += x;
  return z < x;
}

template<typename D, typename W, typename S>
inline
D basic_primitive_ops<D,W,S>::multiply_add(digit_type& z_hi, digit_type& z_lo,
                                           digit_type x, digit_type y)
{
  static const digit_type lo_mask = (1 << digit_bits / 2) - 1;

  const digit_type x_lo = x & lo_mask;
  const digit_type x_hi = x >> digit_bits/2;
  const digit_type y_lo = y & lo_mask;
  const digit_type y_hi = y >> digit_bits/2;

  const digit_type z0 = x_lo * y_lo;
  const digit_type z1 = x_lo * y_hi;
  const digit_type z2 = x_hi * y_lo;
  const digit_type z3 = x_hi * y_hi;

  digit_type z12 = z1 + (z0 >> digit_bits/2);
  const digit_type carry = add(z12, z2);

  const digit_type w_lo = (z12 << digit_bits/2) + (z0 & lo_mask);
  const digit_type w_hi = z3 + (carry << digit_bits/2) + (z12 >> digit_bits/2);

  digit_type u = add(z_lo, w_lo);
  digit_type v = add(z_hi, u);

  return v + add(z_hi, w_hi);
}

template<typename D, typename W, typename S>
inline
D basic_primitive_ops<D,W,S>::mul(digit_type& z_lo, digit_type x, digit_type y)
{
  static const digit_type lo_mask = (1 << digit_bits / 2) - 1;
  static const digit_type hi_mask = lo_mask << (digit_bits / 2);

  const digit_type x_lo = x & lo_mask;
  const digit_type x_hi = x & hi_mask;
  const digit_type y_lo = y & lo_mask;
  const digit_type y_hi = y & hi_mask;

  // do a normal school multiplication on the 'half digits'
  const digit_type z0 = x_lo * y_lo;
  const digit_type z1 = x_lo * y_hi;
  const digit_type z2 = x_hi * y_lo;
  const digit_type z3 = x_hi * y_hi;

  digit_type z12 = z1 + (z0 & hi_mask);
  const digit_type carry = add(z12, z2);

  z_lo = (z12 << digit_bits/2) | (z0 & lo_mask);

  const digit_type z_hi = z3 + (carry << digit_bits/2) + (z12 & hi_mask);

  return z_hi;
}

//////////////////////////////////////////////////////////////
template<typename D, typename W, typename S>
inline
D basic_primitive_ops<D,W,S>::add_single_digit(digit_type* z,
                                               const digit_type* x,
                                               size_type xlen,
                                               digit_type y)
{
  word_type carry = static_cast<word_type>(*x++) + y;
  *z++ = static_cast<digit_type>(carry);
  carry >>= digit_bits;

  while (carry && --xlen)
  {
    carry += static_cast<word_type>(*x++);
    *z++ = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  return static_cast<digit_type>(carry);
}


template<typename D, typename W, typename S>
inline
D basic_primitive_ops<D,W,S>::add_digits(digit_type* z,
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
S basic_primitive_ops<D,W,S>::ripple_carry(digit_type* z,
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
D basic_primitive_ops<D,W,S>::add_smaller_magnitude(digit_type* z,
                                                    const digit_type* x,
                                                    size_type xlen,
                                                    const digit_type* y,
                                                    size_type ylen)
{
  digit_type carry = add_digits(z, x, y, ylen);

  size_type n = ripple_carry(z + ylen, x + ylen, xlen - ylen, carry);

  n += ylen;

  if (n < xlen && z != x)
    std::memcpy(z + n, x + n, sizeof(digit_type) * (xlen - n));

  return carry;
}

template<typename D, typename W, typename S>
inline
void
basic_primitive_ops<D,W,S>::subtract_single_digit(digit_type* z,
                                                  const digit_type* y,
                                                  size_type ylen,
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
D basic_primitive_ops<D,W,S>::subtract_digits(digit_type* z,
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
S basic_primitive_ops<D,W,S>::ripple_borrow(digit_type* z,
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

  size_type n = ripple_borrow(z + ylen, x + ylen, xlen - ylen, borrow);

  if (z != x)
  {
    n += ylen;
    std::memcpy(z + n, x + n, (xlen - n) * sizeof(digit_type));
  }
}

template<typename D, typename W, typename S>
inline
D basic_primitive_ops<D,W,S>::multiply_by_digit(digit_type* z,
                                                const digit_type* y,
                                                size_type ylen,
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
inline
D basic_primitive_ops<D,W,S>::multiply_by_two(digit_type* z,
                                              const digit_type* x, size_type n)
{
  static const digit_type one = 1U;

  digit_type carry = 0;

  while (n--)
  {
    // get carry bit for next iteration
    const digit_type r = *x >> (static_cast<digit_type>(digit_bits) - one);

    *z++ = (*x++ << one) | carry;

    carry = r;
  }

  return carry;
}

template<typename D, typename W, typename S>
void
basic_primitive_ops<D,W,S>::classic_mul(
    digit_type* z, const digit_type* x, size_type xlen,
                   const digit_type* y, size_type ylen)
{
  // phase 1
  word_type tmp = static_cast<word_type>(x[0]) * static_cast<word_type>(y[0]);
  z[0] = static_cast<digit_type>(tmp);

  for (size_type i = 1; i < xlen; ++i)
  {
    tmp = (tmp >> digit_bits)
        + static_cast<word_type>(x[i])
        * static_cast<word_type>(y[0]);
    z[i] = static_cast<digit_type>(tmp);
  }

  tmp >>= digit_bits;
  z[xlen] = static_cast<digit_type>(tmp);

  // phase 2
  for (size_type i = 1; i < ylen; ++i)
  {
    tmp = static_cast<word_type>(y[i])
        * static_cast<word_type>(x[0])
        + static_cast<word_type>(z[i]);
    z[i] = static_cast<digit_type>(tmp);

    for (size_type j = 1; j < xlen; ++j)
    {
      tmp = (tmp >> digit_bits)
          + static_cast<word_type>(y[i]) * static_cast<word_type>(x[j])
          + static_cast<word_type>(z[i+j]);
      z[i+j] = static_cast<digit_type>(tmp);
    }

    tmp >>= digit_bits;
    z[i + xlen] = static_cast<digit_type>(tmp);
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
basic_primitive_ops<D,W,S>::comba_mul(digit_type* z,
                                      const digit_type* x, size_type xlen,
                                      const digit_type* y, size_type ylen)
{
  assert(xlen >= ylen);

  // instead of initializing acc and carry with zero and entering the loop below
  // we manually calculate the first low digit of the result here
  // acc is the accumulator for each column
  word_type acc = static_cast<word_type>(*x) * static_cast<word_type>(*y++);
  word_type carry = acc >> digit_bits;
  acc = static_cast<digit_type>(acc);
  *z++ = static_cast<digit_type>(acc);
  acc = static_cast<digit_type>(carry);
  carry >>= digit_bits;

  // phase 1
  for (size_type i = 1; i < ylen; ++i)
  {
    for (size_type j = 0; j <= i; ++j)
    {
      acc += static_cast<word_type>(*x++) * static_cast<word_type>(*y--);
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }

    x -= i + 1;
    y += i + 2;
    *z++ = static_cast<digit_type>(acc);
    acc  = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  // phase 2
  --y; // now y is at index ylen - 1
  for (size_type i = 0; i < xlen - ylen; ++i)
  {
    ++x;

    for (size_type j = 0; j < ylen; ++j)
    {
      acc += static_cast<word_type>(*x++) * static_cast<word_type>(*y--);
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }

    x -= ylen;
    y += ylen;
    *z++ = static_cast<digit_type>(acc);
    acc  = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  // phase 3
  for (size_type i = 0; i < ylen - 1; ++i)
  {
    ++x;

    for (size_type j = i + 1; j < ylen; ++j)
    {
      acc += static_cast<word_type>(*x++) * static_cast<word_type>(*y--);
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }

    x -= ylen - 1 - i;
    y += ylen - 1 - i;
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
                                      const digit_type* y, size_type xylen)
{
  // phase 1
  // instead of initializing acc and carry with zero and entering the loop below
  // we manually calculate the first low digit of the result here
  word_type acc = static_cast<word_type>(*x) * static_cast<word_type>(*y++);
  word_type carry = acc >> digit_bits;
  acc = static_cast<digit_type>(acc);
  *z++ = static_cast<digit_type>(acc);
  acc = static_cast<digit_type>(carry);
  carry >>= digit_bits;

  for (size_type i = 1; i < xylen; ++i)
  {
    for (size_type j = 0; j <= i; ++j)
    {
      acc += static_cast<word_type>(*x++) * static_cast<word_type>(*y--);
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }

    x -= i + 1;
    y += i + 2;
    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }
  --y;
  // phase 2
  while (--xylen)
  {
    ++x;
    for (size_type j = 0; j < xylen; ++j)
    {
      acc += static_cast<word_type>(*x++) * static_cast<word_type>(*y--);
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }

    x -= xylen;
    y += xylen;
    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  *z = static_cast<digit_type>(acc);
}

template<typename D, typename W, typename S>
void
basic_primitive_ops<D,W,S>::comba_mul(digit_type* z,
                                      const digit_type* x, size_type xlen,
                                      const digit_type* y, size_type ylen,
                                      digit_type* workspace)
{
  assert(xlen >= ylen);

  digit_type* w = workspace;
  word_type acc = 0;  // accumulator for each column
  word_type carry = 0;

  // phase 1
  for (size_type i = 0; i < ylen; ++i)
  {
    const digit_type* a = x;
    const digit_type* b = y + i;

    for (size_type j = 0; j <= i; ++j)
    {
      acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }

    *w++ = static_cast<digit_type>(acc);
    acc  = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  w -= ylen;

  // phase 2
  for (size_type i = 0; i < xlen - ylen; ++i)
  {
    const digit_type* a = x + 1 + i;
    const digit_type* b = y + ylen - 1;

    for (size_type j = 0; j < ylen; ++j)
    {
      acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }

    *z++ = *w;
    *w++ = static_cast<digit_type>(acc);

    if (static_cast<size_type>(w - workspace) == ylen)
      w -= ylen;

    acc  = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  // phase 3
  for (size_type i = 0; i < ylen - 1; ++i)
  {
    const digit_type* a = x + xlen - (ylen - 1);
    const digit_type* b = y + ylen - 1;

    for (size_type j = i + 1; j < ylen; ++j)
    {
      acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }

    *z++ = *w;
    *w++ = static_cast<digit_type>(acc);

    if (static_cast<size_type>(w - workspace) == ylen)
      w -= ylen;

    acc  = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  const digit_type* ws_index = w;

  while (w < (workspace + ylen))
    *z++ = *w++;

  w = workspace;

  while (w < ws_index)
    *z++ = *w++;

  *z = static_cast<digit_type>(acc);
}

template<typename D, typename W, typename S>
void
basic_primitive_ops<D,W,S>::comba_mul_lo(digit_type* z,
                                         const digit_type* x, size_type xlen,
                                         const digit_type* y, size_type ylen,
                                         size_type num)
{
  //assert(xlen >= ylen);
  assert(num <= (xlen + ylen));

  word_type acc = 0;  // accumulator for each column
  word_type carry = 0;

  // phase 1
  if (num)
  {
    const size_type m = ylen < num ? ylen : num;
    for (size_type i = 0; i < m; ++i)
    {
      const digit_type* a = x;
      const digit_type* b = y + i;

      for (size_type j = 0; j <= i; ++j)
      {
        acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
        carry += acc >> digit_bits;
        acc = static_cast<digit_type>(acc);
      }

      *z++ = static_cast<digit_type>(acc);
      acc  = static_cast<digit_type>(carry);
      carry >>= digit_bits;
    }
  }

  // phase 2
  if (num >= ylen)
  {
    const size_type m = xlen - ylen < num ? xlen - ylen : num;
    for (size_type i = 0; i < m; ++i)
    {
      const digit_type* a = x + 1 + i;
      const digit_type* b = y + ylen - 1;

      for (size_type j = 0; j < ylen; ++j)
      {
        acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
        carry += acc >> digit_bits;
        acc = static_cast<digit_type>(acc);
      }

      *z++ = static_cast<digit_type>(acc);
      acc  = static_cast<digit_type>(carry);
      carry >>= digit_bits;
    }
  }

  // phase 3
  if (num >= xlen + ylen)
  {
    const size_type m = ylen - 1 < num ? ylen - 1 : num;
    for (size_type i = 0; i < m; ++i)
    {
      const digit_type* a = x + xlen - (ylen - 1);
      const digit_type* b = y + ylen - 1;

      for (size_type j = i + 1; j < ylen; ++j)
      {
        acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
        carry += acc >> digit_bits;
        acc = static_cast<digit_type>(acc);
      }

      *z++ = static_cast<digit_type>(acc);
      acc  = static_cast<digit_type>(carry);
      carry >>= digit_bits;
    }
  }

  *z = static_cast<digit_type>(acc);
}

template<typename D, typename W, typename S>
void
basic_primitive_ops<D,W,S>::comba_mul_hi(digit_type* z,
                                         const digit_type* x, size_type xlen,
                                         const digit_type* y, size_type ylen,
                                         size_type num)
{
  //assert(xlen >= ylen);
  assert(num > 0);
  assert(num < (xlen + ylen));

  word_type acc = 0;  // accumulator for each column
  word_type carry = 0;

  // phase 1
  if (num < ylen)
  {
    for (size_type i = num; i < ylen; ++i)
    {
      const digit_type* a = x;
      const digit_type* b = y + i;

      for (size_type j = 0; j <= i; ++j)
      {
        acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
        carry += acc >> digit_bits;
        acc = static_cast<digit_type>(acc);
      }

      *z++ = static_cast<digit_type>(acc);
      acc  = static_cast<digit_type>(carry);
      carry >>= digit_bits;
    }
  }

  // phase 2
  if (num < xlen)
  {
    for (size_type i = num - ylen; i < xlen - ylen; ++i)
    {
      const digit_type* a = x + 1 + i;
      const digit_type* b = y + ylen - 1;

      for (size_type j = 0; j < ylen; ++j)
      {
        acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
        carry += acc >> digit_bits;
        acc = static_cast<digit_type>(acc);
      }

      *z++ = static_cast<digit_type>(acc);
      acc  = static_cast<digit_type>(carry);
      carry >>= digit_bits;
    }
  }

  // phase 3
  if (num < (xlen + ylen))
  {
    for (size_type i = num - (xlen + ylen); i < ylen - 1; ++i)
    {
      const digit_type* a = x + xlen - (ylen - 1);
      const digit_type* b = y + ylen - 1;

      for (size_type j = i + 1; j < ylen; ++j)
      {
        acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
        carry += acc >> digit_bits;
        acc = static_cast<digit_type>(acc);
      }

      *z++ = static_cast<digit_type>(acc);
      acc  = static_cast<digit_type>(carry);
      carry >>= digit_bits;
    }
  }

  *z = static_cast<digit_type>(acc);
}

template<typename D, typename W, typename S>
void
basic_primitive_ops<D,W,S>::comba_sqr(digit_type* z,
                                      const digit_type* x,
                                      size_type xlen)
{
/*  word_type acc = 0;
  word_type carry = 0;
  word_type acc2;

  for (size_type i = 0; i < xlen; ++i)
  {
    // even colum
    acc += static_cast<word_type>(x[i]) * static_cast<word_type>(x[i]);

    const digit_type* a = x + i;
    const digit_type* b = x + i;

    acc2 = 0;
    for (size_type j = 0; j < (i - n&1) >> 1; ++j)
    {
      acc2 += static_cast<word_type>(*(--a)) * static_cast<word_type>(*(--b));
      carry += acc2 >> digit_bits;
      acc2 = static_cast<digit_type>(acc2);
    }

    acc += acc2 + acc2;

    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;

    // odd column
    const digit_type* a = x + i;
    const digit_type* b = x + i + 1;

    acc2 = 0;
    for (size_type j = 0; j <= i; ++j)
    {
      acc2 += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
      carry += acc2 >> digit_bits;
      acc2 = static_cast<digit_type>(acc2);
    }

    acc += acc2 + acc2;

    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  *z = static_cast<digit_type>(acc);*/

  word_type acc = 0;  // accumulator for each column
  word_type carry = 0;

  // phase 1
  for (size_type i = 0; i < xlen; ++i)
  {
    const digit_type* a = x;
    const digit_type* b = x + i;

    for (size_type j = 0; j <= i; ++j)
    {
      acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
      carry += acc >> digit_bits;
      acc = static_cast<digit_type>(acc);
    }

    *z++ = static_cast<digit_type>(acc);
    acc = static_cast<digit_type>(carry);
    carry >>= digit_bits;
  }

  // phase 2
  for (size_type i = 1; i < xlen; ++i)
  {
    const digit_type* a = x + i;
    const digit_type* b = x + xlen - 1;

    for (size_type j = 0; j < xlen - i; ++j)
    {
      acc += static_cast<word_type>(*a++) * static_cast<word_type>(*b--);
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
D basic_primitive_ops<D,W,S>::multiply_add_digits(digit_type* z,
                                                  const digit_type* x,
                                                  digit_type y,
                                                  size_type n)
{
  digit_type carry = 0;
  while (n--)
  {
    const word_type r = static_cast<word_type>(*z)
                      + static_cast<word_type>(*x)
                      * static_cast<word_type>(y)
                      + static_cast<word_type>(carry);

    *z = static_cast<digit_type>(r);
    carry = static_cast<digit_type>(r >> digit_bits);
    ++z;
    ++x;
  }

  return carry;
}


template<typename D, typename W, typename S>
inline
void basic_primitive_ops<D,W,S>::divide_by_two(digit_type* z,
                                               const digit_type* x, size_type n)
{
  z += n - 1;
  x += n - 1;

  digit_type carry = 0;

  while (n--)
  {
    // get carry for next iteration
    const digit_type r = *x & 1;

    *z-- = (*x-- >> 1) | (carry << (digit_bits - 1));

    carry = r;
  }
}
/*
// divides half digits [x1, x2, x3] by [y1, y2] and returns remainder
template<typename D, typename W, typename S>
D basic_primitive_ops<D,W,S>::divide_half_digits(
                                      digit_type& q,
                                      digit_type x12, digit_type x3,
                                      digit_type y1, digit_type y2)
{
  q = x12 / y1;
  const digit_type c = x12 - q * y1;
  const digit_type D = q * y2;

  digit_type R = (c << digit_bits / 2) | x3;

  if (R < D) // R is too large by at most 2
  {
    const digit_type y = (y1 << digit_bits / 2) | y2;
    --q;
    R += y;
    if (R < D)
    {
      --q;
      R += y;
    }
  }

  return R - D;
}

// divide two digit number x by one digit number y
// returns remainder
// q = x / y , r = x % y
template<typename D, typename W, typename S>
D basic_primitive_ops<D,W,S>::divide(digit_type& q,
                                     digit_type x_hi, digit_type x_lo,
                                     digit_type y)
{
  static const digit_type lo_mask = (1 << digit_bits / 2) - 1;
  static const digit_type hi_mask = lo_mask << (digit_bits / 2);

  digit_type q1, q2;
  const digit_type r = divide_half_digits(q1, x_hi, x_lo & hi_mask,
                                              y & hi_mask, y & lo_mask);
  const digit_type s = divide_half_digits(q2, r, x_lo & lo_mask,
                                              y & hi_mask, y & lo_mask);
  q = (q1 << digit_bits / 2) & q2;
  return s;
}*/

template<typename D, typename W, typename S>
D basic_primitive_ops<D,W,S>::divide_by_digit(digit_type* z,
                                              const digit_type* x, size_type n,
                                              digit_type y)
{
/*  z += n - 1;
  x += n - 1;

  while (n--)
  {
    if ()
  }*/

  z += n - 1;
  x += n - 1;

  word_type w = 0;

  while (n--)
  {
    w = (w << digit_bits) | static_cast<word_type>(*x--);
    //this turned out to be slower:
    //const digit_type q = static_cast<digit_type>(w / y);
    //w -= q * y;
    //*z-- = q;
    digit_type q;
    if (w >= y)
    {
      q = static_cast<digit_type>(w / y);
      w -= q * y;
    }
    else
      q = 0;
    *z-- = q;
  }

  return static_cast<digit_type>(w);
}

// This is basically a Knuth division with the difference that we form the trial
// quotient by using a 3 digit by 2 digit division instead of a 2 by 1. This has
// the effect of limiting the error in q_hat to 1 instead of 2.
/*template<typename D, typename W, typename S>
void basic_primitive_ops<D,W,S>::divide(digit_type* q, digit_type* r,
                                        const digit_type* x, size_type xlen,
                                        const digit_type* y, size_type ylen,
                                        digit_type* ws)
{
  assert(xlen >= 3);
  assert(ylen >= 2);

  if (y[ylen-1] & (1 << (digit_bits-1))) // if y is already normalized
  {
    digit_type q_estimate =
      div3by2(x[xlen - 1], x[xlen - 2], x[xlen - 3],
              y[ylen - 1], y[ylen - 2]);

    // multiply subtract in place
    digit_type* ws_ptr = ws;
    digit_type borrow = 0;
    for (size_type i = 0; i < ylen; ++i)
    {
      const word_type tmp = static_cast<word_type>(*y++)
                          * static_cast<word_type>(q_estimate);
      *ws_ptr++ = x_ptr - static_cast<digit_type>(tmp);
      borrow = static_cast<digit_type>(tmp >> digit_bits);
    }

    return borrow;
  }
  else
  {
    //count leading zero bits
    norm = 1;

    // store normalized y at ws[0] and normalized x at ws[ylen]
    digit_type q_estimate =
      div3by2(ws[xlen - 1], ws[xlen - 2], ws[xlen - 3],
              ws[ylen - 1], ws[ylen - 2]);
  }


  // TODO normalize in place or store normalized y at ws and let wslen be
  // ylen * 2 + 1.

  const digit_type* x_beg = x;
  x += xlen - 3;

  digit_type q_hat = div3by2(x, y + ylen - 2);
  *(ws + ylen) = multiply_by_digit(ws, y, ylen, q_hat);

  const digit_type borrow = subtract_digits(ws, x, ws, ylen + 1);
  if (borrow)
  {
    ++q_hat;
    add_digits(ws, ws, y, ylen);
  }

  *q++ = q_hat;
  --x;

  ++ws;

  // TODO need to multiply_subtract otherwise I'd need a second buffer to hold
  // the result of multiply_by_digit
  while (x != x_beg)
  {
    digit_type q_hat = div3by2(ws, y + ylen - 2);
    *(ws + ylen) = multiply_by_digit(ws, y, ylen, q_hat);

    const digit_type borrow = subtract_digits(ws, x, ws, ylen + 1);
    if (borrow)
    {
      ++q_hat;
      add_digits(ws, ws, y, ylen);
    }

    *q++ = q_hat;
    --x;
    *(ws - 1) = *x;
  }
}*/

template<typename D, typename W, typename S>
D basic_primitive_ops<D,W,S>::shift_bits_left(digit_type* x,
                                              size_type xlen,
                                              size_type n)
{
  assert(n > 0 && n < digit_bits);

  // shift for msbs
  const digit_type shift = digit_bits - n;

  digit_type carry = 0;
  while (xlen--)
  {
    const digit_type c = (*x >> shift);
    *x = (*x << n) | carry;
    carry = c;
    ++x;
  }

  return carry;
}

template<typename D, typename W, typename S>
void basic_primitive_ops<D,W,S>::shift_bits_right(digit_type* x,
                                                  size_type xlen,
                                                  size_type n)
{
  assert(n > 0 && n < digit_bits);

  const digit_type mask = (digit_type(1) << n) - 1;

  // shift for lsb
  const digit_type shift = digit_bits - n;

  x += xlen;

  digit_type carry = 0;
  while (xlen--)
  {
    --x;
    const digit_type c = *x & mask;
    *x = (*x >> n) | (carry << shift);
    carry = c;
  }
}

template<typename D, typename W, typename S>
int basic_primitive_ops<D,W,S>::compare_magnitude(const digit_type* x,
                                                  size_type xlen,
                                                  const digit_type* y,
                                                  size_type ylen)
{
  if (xlen > ylen)
    return 1;

  if (xlen < ylen)
    return -1;

  // compare all digits
  x += xlen;
  y += ylen;
  while (xlen--)
  {
    --x; --y;
    if (*x > *y)
      return 1;
    if (*x < *y)
      return -1;
  }

  return 0;
}


// This exists to ease development of primitive_ops specializations. If a
// specialized function isn't available yet, the compiler will just choose the
// inherited one. It also means that whenever we add a new function to
// basic_primitive_ops no code will break since it will be available to all
// specializations as well.
template<typename D, typename W, typename S>
struct primitive_ops : basic_primitive_ops<D,W,S>
{};


#else

template<typename DigitT, typename SizeT>
struct basic_primitive_ops
{
  typedef DigitT digit_type;
  typedef SizeT  size_type;

  static const digit_type digit_bits = std::numeric_limits<digit_type>::digits;

  // ADD ------------------------------------

  // z = x + y, returns carry
  static digit_type add(digit_type& z, digit_type x, digit_type y);

  // z += x, returns carry
  static digit_type add(digit_type& z, digit_type x);

  // add y to the digits in x and store result in z
  // xlen must be > 0
  // returns: the last carry (it will not get stored in z)
  static digit_type add_single_digit(digit_type* z,
                                     const digit_type* x, size_type xlen,
                                     digit_type y);

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
  // returns last carry
  static digit_type add_smaller_magnitude(digit_type* z,
                                          const digit_type* x, size_type xlen,
                                          const digit_type* y, size_type ylen);

  // SUB ------------------------------------

  // z = x - y, returns borrow
  static digit_type sub(digit_type& z, digit_type x, digit_type y);

  // z -= x, returns borrow
  static digit_type sub(digit_type& z, digit_type x);

  // subtracts x from the digits in y and store result in z
  static void subtract_single_digit(digit_type* z,
                                    const digit_type* x, size_type xlen,
                                    digit_type y);

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

  // z = x * y, returns high part of the product
  static digit_type mul(digit_type& z, digit_type x, digit_type y);

  // z *= x, returns high part of the product
  static digit_type mul(digit_type& z, digit_type x);

  // multiply y of length ylen with x and store result in z
  // returns: the last carry (it will not get stored in z)
  static digit_type multiply_by_digit(digit_type* z,
                                      const digit_type* x, size_type xlen,
                                      digit_type y);

  // z = x * 2
  static digit_type multiply_by_two(digit_type* z,
                                    const digit_type* x, size_type len);

  // z = x * y; precondition: xlen >= ylen
  static void long_mul(digit_type* z, const digit_type* x, size_type xlen,
                                      const digit_type* y, size_type ylen);

  // z = x * y; precondition: xlen >= ylen
  static void comba_mul(digit_type* z, const digit_type* x, size_type xlen,
                                       const digit_type* y, size_type ylen);

  // z = x * y; for numbers of the same size
  static void comba_mul(digit_type* z,
                        const digit_type* x,
                        const digit_type* y, size_type xylen);

  // z = x * y; precondition: xlen >= ylen and workspace must have at least ylen
  // digits this function is only used by the integral ops interaction code, it
  // allows x and z to be the same pointer.
  static void comba_mul(digit_type* z, const digit_type* x, size_type xlen,
                                       const digit_type* y, size_type ylen,
                                       digit_type* workspace);

  // computes the lower num digits of the product of x and y
  static void comba_mul_lo(digit_type* z, const digit_type* x, size_type xlen,
                                          const digit_type* y, size_type ylen,
                                          size_type num);

  // computes the high product of x and y without num least significant digits
  // basically the result is: z = (x*y) >> radix^num
  static void comba_mul_hi(digit_type* z, const digit_type* x, size_type xlen,
                                          const digit_type* y, size_type ylen,
                                          size_type num);

  // SQR ------------------------------------

  // z = x * x;
  static void comba_sqr(digit_type* z, const digit_type* x, size_type xlen);

  // MADD ------------------------------------

  // z = z + x * y, returns carry
  static digit_type multiply_add(digit_type& z,
                                 digit_type x, digit_type y);

  // z = z + x * y, returns carry
  static digit_type multiply_add(digit_type& z_hi, digit_type& z_lo,
                                 digit_type x, digit_type y);

  // z = z + x * y
  static digit_type multiply_add_digits(digit_type* z,
                                        const digit_type* x,
                                        digit_type y,
                                        size_type n);

  // DIV -------------------------------------

  // z = x / 2
  static void divide_by_two(digit_type* z, const digit_type* x, size_type len);

  // z = x / y
  // returns remainder
  static digit_type divide_by_digit(digit_type* z,
                                    const digit_type* x, size_type xlen,
                                    digit_type y);

  // SHIFT -----------------------------------

  // shifts x by n bits to the left, where n > 0 && n < digit_bits
  // returns carry
  static digit_type shift_bits_left(digit_type* x, size_type xlen, size_type n);

  // shifts x by n bits to the right, where n > 0 && n < digit_bits
  static void shift_bits_right(digit_type* x, size_type xlen, size_type n);

  // CMP -------------------------------------

  // returns  1 if x  > y
  // returns  0 if x == y
  // returns -1 if x  < y
  static int compare_magnitude(const digit_type* x, size_type xlen,
                               const digit_type* y, size_type ylen);

private:

  // divides half digits [x1, x2, x3] by [y1, y2] and returns remainder
  // this function is used by divide_by_digit
  static digit_type divide_half_digits(digit_type& q,
                                       digit_type x12, digit_type x3,
                                       digit_type y1, digit_type y2);
};



template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::add(digit_type& z, digit_type x, digit_type y)
{
  z = x + y;
  return z < x;
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::add(digit_type& z, digit_type x)
{
  z += x;
  return z < x;
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::add_single_digit(digit_type* z,
                                             const digit_type* x,
                                             size_type xlen,
                                             digit_type y)
{
  digit_type carry = add(*z++, *x++, y);

  while (carry && --xlen)
    carry = add(*z++, *x++, carry);

  return carry;
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::add_digits(digit_type* z,
                                       const digit_type* x,
                                       const digit_type* y, size_type n)
{
  digit_type carry = 0;
  while (n--)
  {
    const digit_type c0 = add(*z, *x++, *y++);
    const digit_type c1 = add(*z++, carry);
    carry = c0 | c1;
  }

  return carry;
}

template<typename D, typename S>
inline
S basic_primitive_ops<D,S>::ripple_carry(digit_type* z,
                                         const digit_type* x,
                                         size_type n,
                                         digit_type& carry)
{
  size_type i = 0;

  for (; carry && (i < n); ++i)
    carry = add(*z++, *x++, carry);

  return i;
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::add_smaller_magnitude(digit_type* z,
                                                  const digit_type* x,
                                                  size_type xlen,
                                                  const digit_type* y,
                                                  size_type ylen)
{
  digit_type carry = add_digits(z, x, y, ylen);

  size_type n = ripple_carry(z + ylen, x + ylen, xlen - ylen, carry);

  n += ylen;

  if (n < xlen && z != x)
    std::memcpy(z + n, x + n, sizeof(digit_type) * (xlen - n));

  return carry;
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::sub(digit_type& z, digit_type x, digit_type y)
{
  z = x - y;
  return z > x;
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::sub(digit_type& z, digit_type x)
{
  const digit_type tmp = z;
  z -= x;
  return z > tmp;
}

template<typename D, typename S>
inline
void
basic_primitive_ops<D,S>::subtract_single_digit(digit_type* z,
                                                const digit_type* y,
                                                size_type ylen,
                                                digit_type x)
{
  digit_type borrow = sub(*z++, *y++, x);

  while (borrow && --ylen)
    borrow = sub(*z++, *y++, borrow);
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::subtract_digits(digit_type* z,
                                            const digit_type* x,
                                            const digit_type* y,
                                            size_type n)
{
  digit_type borrow = 0;

  while (n--)
  {
    const digit_type b0 = sub(*z, *x++, *y++);
    const digit_type b1 = sub(*z++, borrow);
    borrow = b0 | b1;
  }

  return borrow;
}

template<typename D, typename S>
inline
S basic_primitive_ops<D,S>::ripple_borrow(digit_type* z,
                                          const digit_type* x,
                                          size_type n,
                                          digit_type borrow)
{
  size_type i = 0;

  for (; borrow && (i < n); ++i)
    borrow = sub(*z++, *x++, borrow);

  return i;
}

template<typename D, typename S>
inline
void basic_primitive_ops<D,S>::sub_smaller_magnitude(
    digit_type* z,
    const digit_type* x, size_type xlen,
    const digit_type* y, size_type ylen)
{
  const digit_type borrow = subtract_digits(z, x, y, ylen);

  size_type n = ripple_borrow(z + ylen, x + ylen, xlen - ylen, borrow);

  if (z != x)
  {
    n += ylen;
    std::memcpy(z + n, x + n, (xlen - n) * sizeof(digit_type));
  }
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::mul(digit_type& z_lo, digit_type x, digit_type y)
{
  static const digit_type lo_mask = (1 << digit_bits / 2) - 1;

  const digit_type x_lo = x & lo_mask;
  const digit_type x_hi = x >> digit_bits/2;
  const digit_type y_lo = y & lo_mask;
  const digit_type y_hi = y >> digit_bits/2;

  const digit_type z0 = x_lo * y_lo;
  const digit_type z1 = x_lo * y_hi;
  const digit_type z2 = x_hi * y_lo;
  const digit_type z3 = x_hi * y_hi;

  digit_type z12 = z1 + (z0 >> digit_bits/2);
  const digit_type carry = add(z12, z2);

  z_lo = (z12 << digit_bits/2) + (z0 & lo_mask);

  const digit_type z_hi = z3 + (carry << digit_bits/2) + (z12 >> digit_bits/2);

  return z_hi;
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::mul(digit_type& z, digit_type x)
{
  return mul(z, z, x);
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::multiply_by_digit(digit_type* z,
                                              const digit_type* y,
                                              size_type ylen,
                                              digit_type x)
{
  digit_type carry = 0;

  while (ylen--)
  {
    const digit_type tmp = mul(*z, *y++, x);
    carry = tmp + add(*z++, carry);
  }

  return carry;
}


template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::multiply_by_two(digit_type* z,
                                            const digit_type* x, size_type n)
{
  static const digit_type one = 1U;

  digit_type carry = 0;

  while (n--)
  {
    // get carry bit for next iteration
    const digit_type r = *x >> (digit_bits - one);

    *z++ = (*x++ << one) | carry;

    carry = r;
  }

  return carry;
}

template<typename D, typename S>
void
basic_primitive_ops<D,S>::long_mul(digit_type* z,
                                   const digit_type* x, size_type xlen,
                                   const digit_type* y, size_type ylen)
{
  assert(xlen >= ylen);
  z[xlen] = multiply_by_digit(z++, x, xlen, *(y++));
  --ylen;
  while(--ylen)
    z[xlen] = multiply_add_digits(z++, x, xlen, *(y++));
}

template<typename D, typename S>
void
basic_primitive_ops<D,S>::comba_mul(digit_type* z,
                                    const digit_type* x, size_type xlen,
                                    const digit_type* y, size_type ylen)
{
  assert(xlen >= ylen);

  digit_type acc_hi = 0;  // accumulator for each column
  digit_type acc_lo = 0;
  digit_type carry_hi = 0;
  digit_type carry_lo = 0;

  // phase 1
  for (size_type i = 0; i < ylen; ++i)
  {
    const digit_type* a = x;
    const digit_type* b = y + i;

    for (size_type j = 0; j <= i; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *z++     = acc_lo;
    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  // phase 2
  for (size_type i = 0; i < xlen - ylen; ++i)
  {
    const digit_type* a = x + 1 + i;
    const digit_type* b = y + ylen - 1;

    for (size_type j = 0; j < ylen; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *z++     = acc_lo;
    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  // phase 3
  for (size_type i = 0; i < ylen - 1; ++i)
  {
    const digit_type* a = x + xlen - (ylen - 1) + i;
    const digit_type* b = y + ylen - 1;

    for (size_type j = i + 1; j < ylen; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *z++     = acc_lo;
    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  *z = acc_lo;
}

template<typename D, typename S>
void
basic_primitive_ops<D,S>::comba_mul(digit_type* z,
                                    const digit_type* x,
                                    const digit_type* y, size_type xylen)
{
  digit_type acc_hi = 0;  // accumulator for each column
  digit_type acc_lo = 0;
  digit_type carry_hi = 0;
  digit_type carry_lo = 0;

  // phase 1
  for (size_type i = 0; i < xylen; ++i)
  {
    const digit_type* a = x;
    const digit_type* b = y + i;

    for (size_type j = 0; j <= i; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *z++     = acc_lo;
    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  // phase 2
  for (size_type i = 1; i < xylen; ++i)
  {
    const digit_type* a = y + xylen - 1;
    const digit_type* b = x + i;

    for (size_type j = 0; j < xylen - i; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a--, *b++);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *z++     = acc_lo;
    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  *z = acc_lo;
}

template<typename D, typename S>
void
basic_primitive_ops<D,S>::comba_mul(digit_type* z,
                                    const digit_type* x, size_type xlen,
                                    const digit_type* y, size_type ylen,
                                    digit_type* workspace)
{
  assert(xlen >= ylen);

  digit_type* w = workspace;
  digit_type acc_hi = 0;  // accumulator for each column
  digit_type acc_lo = 0;
  digit_type carry_hi = 0;
  digit_type carry_lo = 0;

  // phase 1
  for (size_type i = 0; i < ylen; ++i)
  {
    const digit_type* a = x;
    const digit_type* b = y + i;

    for (size_type j = 0; j <= i; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *w++     = acc_lo;
    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  w -= ylen;

  // phase 2
  for (size_type i = 0; i < xlen - ylen; ++i)
  {
    const digit_type* a = x + 1 + i;
    const digit_type* b = y + ylen - 1;

    for (size_type j = 0; j < ylen; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *z++ = *w;
    *w++ = acc_lo;

    if (static_cast<size_type>(w - workspace) == ylen)
      w -= ylen;

    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  // phase 3
  for (size_type i = 0; i < ylen - 1; ++i)
  {
    const digit_type* a = x + xlen - (ylen - 1) + i;
    const digit_type* b = y + ylen - 1;

    for (size_type j = i + 1; j < ylen; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *z++ = *w;
    *w++ = acc_lo;

    if (static_cast<size_type>(w - workspace) == ylen)
      w -= ylen;

    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  const digit_type* ws_index = w;

  while (w < (workspace + ylen))
    *z++ = *w++;

  w = workspace;

  while (w < ws_index)
    *z++ = *w++;

  *z = acc_lo;
}

template<typename D, typename S>
void
basic_primitive_ops<D,S>::comba_mul_lo(digit_type* z,
                                       const digit_type* x, size_type xlen,
                                       const digit_type* y, size_type ylen,
                                       size_type num)
{
  //assert(xlen >= ylen);
  assert(num <= (xlen + ylen));

  digit_type acc_hi = 0;  // accumulator for each column
  digit_type acc_lo = 0;
  digit_type carry_hi = 0;
  digit_type carry_lo = 0;

  // phase 1
  if (num)
  {
    const size_type m = ylen < num ? ylen : num;
    for (size_type i = 0; i < m; ++i)
    {
      const digit_type* a = x;
      const digit_type* b = y + i;

      for (size_type j = 0; j <= i; ++j)
      {
        const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
        carry_hi += add(carry_lo, carry);
        carry_hi += add(carry_lo, acc_hi);
        acc_hi = 0;
      }

      *z++     = acc_lo;
      acc_lo   = carry_lo;
      carry_lo = carry_hi;
      carry_hi = 0;
    }
  }

  // phase 2
  if (num >= ylen)
  {
    const size_type m = xlen - ylen < num ? xlen - ylen : num;
    for (size_type i = 0; i < m; ++i)
    {
      const digit_type* a = x + 1 + i;
      const digit_type* b = y + ylen - 1;

      for (size_type j = 0; j < ylen; ++j)
      {
        const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
        carry_hi += add(carry_lo, carry);
        carry_hi += add(carry_lo, acc_hi);
        acc_hi = 0;
      }

      *z++     = acc_lo;
      acc_lo   = carry_lo;
      carry_lo = carry_hi;
      carry_hi = 0;
    }
  }

  // phase 3
  if (num >= xlen + ylen)
  {
    const size_type m = ylen - 1 < num ? ylen - 1 : num;
    for (size_type i = 0; i < m; ++i)
    {
      const digit_type* a = x + xlen - (ylen - 1);
      const digit_type* b = y + ylen - 1;

      for (size_type j = i + 1; j < ylen; ++j)
      {
        const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
        carry_hi += add(carry_lo, carry);
        carry_hi += add(carry_lo, acc_hi);
        acc_hi = 0;
      }

      *z++     = acc_lo;
      acc_lo   = carry_lo;
      carry_lo = carry_hi;
      carry_hi = 0;
    }
  }

  *z = acc_lo;
}

template<typename D, typename S>
void
basic_primitive_ops<D,S>::comba_mul_hi(digit_type* z,
                                       const digit_type* x, size_type xlen,
                                       const digit_type* y, size_type ylen,
                                       size_type num)
{
  //assert(xlen >= ylen);
  assert(num > 0);
  assert(num < (xlen + ylen));

  digit_type acc_hi = 0;  // accumulator for each column
  digit_type acc_lo = 0;
  digit_type carry_hi = 0;
  digit_type carry_lo = 0;

  // phase 1
  if (num < ylen)
  {
    for (size_type i = num; i < ylen; ++i)
    {
      const digit_type* a = x;
      const digit_type* b = y + i;

      for (size_type j = 0; j <= i; ++j)
      {
        const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
        carry_hi += add(carry_lo, carry);
        carry_hi += add(carry_lo, acc_hi);
        acc_hi = 0;
      }

      *z++     = acc_lo;
      acc_lo   = carry_lo;
      carry_lo = carry_hi;
      carry_hi = 0;
    }
  }

  // phase 2
  if (num < xlen)
  {
    for (size_type i = num - ylen; i < xlen - ylen; ++i)
    {
      const digit_type* a = x + 1 + i;
      const digit_type* b = y + ylen - 1;

      for (size_type j = 0; j < ylen; ++j)
      {
        const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
        carry_hi += add(carry_lo, carry);
        carry_hi += add(carry_lo, acc_hi);
        acc_hi = 0;
      }

      *z++     = acc_lo;
      acc_lo   = carry_lo;
      carry_lo = carry_hi;
      carry_hi = 0;
    }
  }

  // phase 3
  if (num < (xlen + ylen))
  {
    for (size_type i = num - (xlen + ylen); i < ylen - 1; ++i)
    {
      const digit_type* a = x + xlen - (ylen - 1);
      const digit_type* b = y + ylen - 1;

      for (size_type j = i + 1; j < ylen; ++j)
      {
        const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
        carry_hi += add(carry_lo, carry);
        carry_hi += add(carry_lo, acc_hi);
        acc_hi = 0;
      }

      *z++     = acc_lo;
      acc_lo   = carry_lo;
      carry_lo = carry_hi;
      carry_hi = 0;
    }
  }

  *z = acc_lo;
}

template<typename D, typename S>
void
basic_primitive_ops<D,S>::comba_sqr(digit_type* z,
                                    const digit_type* x,
                                    size_type xlen)
{
  digit_type acc_hi = 0;  // accumulator for each column
  digit_type acc_lo = 0;
  digit_type carry_hi = 0;
  digit_type carry_lo = 0;

  // phase 1
  for (size_type i = 0; i < xlen; ++i)
  {
    const digit_type* a = x;
    const digit_type* b = x + i;

    for (size_type j = 0; j <= i; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *z++     = acc_lo;
    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  // phase 2
  for (size_type i = 1; i < xlen; ++i)
  {
    const digit_type* a = x + i;
    const digit_type* b = x + xlen - 1;

    for (size_type j = 0; j < xlen - i; ++j)
    {
      const digit_type carry = multiply_add(acc_hi, acc_lo, *a++, *b--);
      carry_hi += add(carry_lo, carry);
      carry_hi += add(carry_lo, acc_hi);
      acc_hi = 0;
    }

    *z++     = acc_lo;
    acc_lo   = carry_lo;
    carry_lo = carry_hi;
    carry_hi = 0;
  }

  *z = acc_lo;
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::multiply_add(digit_type& z_hi, digit_type& z_lo,
                                         digit_type x, digit_type y)
{
  static const digit_type lo_mask = (1 << digit_bits / 2) - 1;

  const digit_type x_lo = x & lo_mask;
  const digit_type x_hi = x >> digit_bits/2;
  const digit_type y_lo = y & lo_mask;
  const digit_type y_hi = y >> digit_bits/2;

  const digit_type z0 = x_lo * y_lo;
  const digit_type z1 = x_lo * y_hi;
  const digit_type z2 = x_hi * y_lo;
  const digit_type z3 = x_hi * y_hi;

  digit_type z12 = z1 + (z0 >> digit_bits/2);
  const digit_type carry = add(z12, z2);

  const digit_type w_lo = (z12 << digit_bits/2) + (z0 & lo_mask);
  const digit_type w_hi = z3 + (carry << digit_bits/2) + (z12 >> digit_bits/2);

  digit_type u = add(z_lo, w_lo);
  digit_type v = add(z_hi, u);

  return v + add(z_hi, w_hi);
}

template<typename D, typename S>
inline
D basic_primitive_ops<D,S>::multiply_add(digit_type& z,
                                         digit_type x, digit_type y)
{
  static const digit_type lo_mask = (1 << digit_bits / 2) - 1;

  const digit_type x_lo = x & lo_mask;
  const digit_type x_hi = x >> digit_bits/2;
  const digit_type y_lo = y & lo_mask;
  const digit_type y_hi = y >> digit_bits/2;

  const digit_type z0 = x_lo * y_lo;
  const digit_type z1 = x_lo * y_hi;
  const digit_type z2 = x_hi * y_lo;
  const digit_type z3 = x_hi * y_hi;

  digit_type z12 = z1 + (z0 >> digit_bits/2);
  const digit_type carry = add(z12, z2);

  const digit_type w_lo = (z12 << digit_bits/2) + (z0 & lo_mask);
  const digit_type w_hi = z3 + (carry << digit_bits/2) + (z12 >> digit_bits/2);

  const digit_type u = add(z, w_lo);

  return u + w_hi;
}

template<typename D, typename S>
D basic_primitive_ops<D,S>::multiply_add_digits(digit_type* z,
                                                const digit_type* x,
                                                digit_type y,
                                                size_type n)
{
  digit_type carry = 0;
  while (n--)
  {
    carry = add(*z, carry);
    carry += multiply_add(*z, *x, y);
    ++z; ++x;
  }

  return carry;
}

template<typename D, typename S>
inline
void basic_primitive_ops<D,S>::divide_by_two(digit_type* z,
                                             const digit_type* x, size_type n)
{
  z += n - 1;
  x += n - 1;

  digit_type carry = 0;

  while (n--)
  {
    // get carry for next iteration
    const digit_type r = *x & 1;

    *z-- = (*x-- >> 1) | (carry << (digit_bits - 1));

    carry = r;
  }
}

template<typename D, typename S>
D basic_primitive_ops<D,S>::divide_by_digit(digit_type* z,
                                            const digit_type* x, size_type n,
                                            digit_type y)
{
  /*if (n == 1)
  {
    *z = *x / y;
    return *x % y;
  }*/
  static const digit_type lo_mask = (1 << digit_bits / 2) - 1;
  static const digit_type hi_mask = lo_mask << (digit_bits / 2);
  static const digit_type hi_bit = 1 << (digit_bits - 1);
  static const digit_type d2 = digit_bits / 2;

  z += n - 1;
  x += n - 1;

  digit_type w_hi, w_lo = 0;

  if (y & hi_bit) // if y is normalized
  {
    while (n--)
    {
      w_hi = w_lo;
      w_lo = *x--;
      // Do a 2 digit by 1 digit division -> [w_hi, w_lo] / y
      if (w_hi || w_lo >= y) // if w >= y
      {
        digit_type q_hi, q_lo;
        const digit_type rem = divide_half_digits(
            q_hi,
            w_hi, (w_lo & hi_mask) >> d2,
            (y & hi_mask) >> d2, y & lo_mask);

        w_lo = divide_half_digits(
            q_lo,
            rem, w_lo & lo_mask,
            (y & hi_mask) >> d2, y & lo_mask);

        if (w_hi >= y)
          ++q_lo;

        *z-- = (q_hi << d2) | q_lo;
      }
      else
        *z-- = 0;

      // q is never larger than one digit because w_hi is always set to the
      // remainder and thus w_hi can never be greater than y which is the
      // precondition for producing a quotient carry.
      // TODO we could do a 2 by 1 division before the loop, that could produce
      // a q carry. And then continue on as usual.
    }

    return w_lo;
  }
  else
  {
    // count leading zeros
    unsigned norm = 0;
    while (!(y & hi_bit))
    {
      ++norm;
      y <<= 1;
    }

    // we're going to normalize the number in place
    const digit_type shift = digit_bits - norm;

    w_hi = *x >> shift;

    while (n--)
    {
      w_lo = (*x << norm);
      if (n)
      {
        --x;
        w_lo |= *x >> shift;
      }

      // Do a 2 digit by 1 digit division -> [w_hi, w_lo] / y
      if (w_hi || w_lo >= y) // if w >= y
      {
        digit_type q_hi, q_lo;
        const digit_type rem = divide_half_digits(
            q_hi,
            w_hi, (w_lo & hi_mask) >> d2,
            (y & hi_mask) >> d2, y & lo_mask);

        w_lo = divide_half_digits(
            q_lo,
            rem, w_lo & lo_mask,
            (y & hi_mask) >> d2, y & lo_mask);

        *z-- = (q_hi << d2) | q_lo;
      }
      else
        *z-- = 0;

      w_hi = w_lo;
    }

    return w_lo >> norm;
  }
}

template<typename D, typename S>
D basic_primitive_ops<D,S>::divide_half_digits(digit_type& q,
                                               digit_type x12, digit_type x3,
                                               digit_type y1, digit_type y2)
{
  const digit_type y = (y1 << digit_bits / 2) | y2;
  //if (x12 >= y)
  //  x12 -= y;

  q = x12 / y1;

  const digit_type c = x12 - q * y1;
  const digit_type D_ = q * y2;

  digit_type R = (c << digit_bits / 2) | x3;

  if (R < D_) // R is too large by at most 2
  {
    static const digit_type z = ~digit_type(0);
    --q;
    R += y;
    if (R < y) // overflow
      return z - D_ + R + 1;
    if (R < D_)
    {
      --q;
      R += y;
      if (R < y) // overflow
        return z - D_ + R + 1;
    }
  }

  return R - D_;
}

template<typename D, typename S>
D basic_primitive_ops<D,S>::shift_bits_left(digit_type* x,
                                            size_type xlen,
                                            size_type n)
{
  assert(n > 0 && n < digit_bits);

  // shift for msbs
  const digit_type shift = digit_bits - n;

  digit_type carry = 0;
  while (xlen--)
  {
    const digit_type c = (*x >> shift);
    *x = (*x << n) | carry;
    carry = c;
    ++x;
  }

  return carry;
}

template<typename D, typename S>
void basic_primitive_ops<D,S>::shift_bits_right(digit_type* x,
                                                size_type xlen,
                                                size_type n)
{
  assert(n > 0 && n < digit_bits);

  const digit_type mask = (digit_type(1) << n) - 1;

  // shift for lsb
  const digit_type shift = digit_bits - n;

  x += xlen;

  digit_type carry = 0;
  while (xlen--)
  {
    --x;
    const digit_type c = *x & mask;
    *x = (*x >> n) | (carry << shift);
    carry = c;
  }
}

template<typename D, typename S>
int basic_primitive_ops<D,S>::compare_magnitude(const digit_type* x,
                                                size_type xlen,
                                                const digit_type* y,
                                                size_type ylen)
{
  if (xlen > ylen)
    return 1;

  if (xlen < ylen)
    return -1;

  // compare all digits
  x += xlen;
  y += ylen;
  while (xlen--)
  {
    --x; --y;
    if (*x > *y)
      return 1;
    if (*x < *y)
      return -1;
  }

  return 0;
}

template<typename D, typename S>
struct primitive_ops : basic_primitive_ops<D,S>
{};

#endif




/*
// Here we include primitive_ops specializations that use assembler

#if defined(BOOST_MP_MATH_INTEGER_USE_ASM)

  #if defined(__GNU__)
    #if defined(__386__)
      #include <boost/mp_math/mp_int/detail/base/asm/x86/gnu_386_primitive_ops.hpp>
    #endif
  #endif

#endif
*/


} // namespace base
} // namespace detail
} // namespace mp_math
} // namespace boost

#endif

