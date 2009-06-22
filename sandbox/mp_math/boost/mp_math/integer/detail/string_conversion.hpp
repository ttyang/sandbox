// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MATH_INTEGER_DETAIL_STRING_CONVERTER_HPP
#define BOOST_MP_MATH_INTEGER_DETAIL_STRING_CONVERTER_HPP

#include <algorithm>
#include <iostream>
#include <memory>

namespace boost {
namespace mp_math {
namespace detail {

template<
  typename T,
  T Radix,
  T Count = 0,
  T Temp = Radix,
  bool continue_recursion = true
>
struct max_power_impl
{
  // continue recursion until Temp overflows
  static const T a = static_cast<T>(Temp * Radix);
  static const bool c = (a / Radix) == Temp;

  typedef max_power_impl<T, Radix, Count + 1, c ? a : Temp, c> result;

  static const T exponent = result::exponent;
  static const T value    = result::value;
};

template<typename T, T Radix, T Count, T Temp>
struct max_power_impl<T, Radix, Count, Temp, false>
{
  static const T exponent = Count;
  static const T value    = Temp;
};

// T must be an unsigned integral type
template<typename T, T Radix>
struct max_power
{
  static const T exponent = max_power_impl<T, Radix>::exponent;
  static const T value    = max_power_impl<T, Radix>::value;
};


// Supported radices are 2, 4, 8, 16, 32, 64 and 10
template<class ApInt>
struct sc_constants
{
  typedef typename ApInt::digit_type digit_type;

//private:

  const unsigned index_;

  static unsigned map_radix_to_index(unsigned radix)
  {
    switch (radix)       // map radix 2^x to index x-1
    {
      case  2: return 0;
      case  4: return 1;
      case  8: return 2;
      case 16: return 3;
      case 32: return 4;
      case 64: return 5;
      default: return 6; // map radix 10 to index 6
    }
  }

  static const digit_type max_exponent_array_[7];
  static const digit_type max_power_value_array_[7];
  static const digit_type radix_storage_bits_array_[7];

public:

  explicit sc_constants(unsigned radix)
  :
    index_(map_radix_to_index(radix))
  {}

  // returns maximal exponent x so that radix^x still fits into a digit_type
  digit_type max_exponent() const
  {
    return max_exponent_array_[index_];
  }

  // returns the corresponding value y = radix^max_power
  digit_type max_power_value() const
  {
    return max_power_value_array_[index_];
  }

  // returns ceil(log2(radix))
  digit_type radix_storage_bits() const
  {
    return radix_storage_bits_array_[index_];
  }
};

template<class ApInt>
const typename ApInt::digit_type
sc_constants<ApInt>::max_exponent_array_[7] =
{
  max_power<digit_type,  2>::exponent,
  max_power<digit_type,  4>::exponent,
  max_power<digit_type,  8>::exponent,
  max_power<digit_type, 16>::exponent,
  max_power<digit_type, 32>::exponent,
  max_power<digit_type, 64>::exponent,
  max_power<digit_type, 10>::exponent
};

template<class ApInt>
const typename ApInt::digit_type
sc_constants<ApInt>::max_power_value_array_[7] =
{
  max_power<digit_type,  2>::value,
  max_power<digit_type,  4>::value,
  max_power<digit_type,  8>::value,
  max_power<digit_type, 16>::value,
  max_power<digit_type, 32>::value,
  max_power<digit_type, 64>::value,
  max_power<digit_type, 10>::value
};

template<class ApInt>
const typename ApInt::digit_type
sc_constants<ApInt>::radix_storage_bits_array_[7] = {1, 2, 3, 4, 5, 6, 4};


// Always call detect_properties before calling convert, unless you're providing
// the radix explicitly. In that case the number must not have a radix prefix.

template<class ApInt>
struct from_string_converter
{
  typedef typename ApInt::digit_type digit_type;
  typedef typename ApInt::size_type  size_type;

  // detect sign, radix, length
  template<typename Iter>
  void detect_properties(Iter& first, Iter last)
  {
    detect_properties(first, last,
                      typename std::iterator_traits<Iter>::iterator_category());
  }

  // as above, additionally it checks if the number prefix is formatted
  // according to the flags
  template<typename Iter>
  void detect_properties(Iter& first, Iter last, std::ios_base::fmtflags f);

  // manual radix parameter for radices 2-64
  template<typename Iter>
  void convert(ApInt& x, Iter first, Iter last, unsigned radix) const
  {
    assert(x.is_uninitialized());
    if (first != last)
      convert(x, first, last, radix,
            typename std::iterator_traits<Iter>::iterator_category());
  }

  // use the detected radix, can only be 8, 10 or 16
  template<typename Iter>
  void convert(ApInt& x, Iter first, Iter last) const
  {
    convert(x, first, last, radix);
  }

  template<typename InputIter>
  void convert(ApInt& x, InputIter c) const;

  // converts the string [first, last) to digits one at a time beginning with
  // the most significant digit, works only for power of two radices
  template<typename Iter>
  digit_type get_next_digit(Iter& first, Iter last) const;

  static bool is_power_of_two(unsigned radix)
  {
    return (radix & (radix - 1)) == 0;
  }

  // properties
  std::size_t total_length;
  unsigned    prefix_length;
  std::size_t length;          // = total_length - prefix_length
  unsigned    radix;
  bool        is_positive;     // do we have a '-' as first character?

private:

  typedef sc_constants<ApInt> sc_type;
  typedef typename ApInt::traits_type::ops_type ops_type;

  static const unsigned radix_bits = ApInt::traits_type::radix_bits;

  enum error_t
  {
    err_invalid_char,
    err_bad_prefix,
    err_no_number_after_prefix,
    err_no_number_after_sign,
    err_no_error
  };

  template<typename charT>
  static digit_type ascii_to_value(charT c);

  template<typename RandomAccessIterator>
  void detect_properties(RandomAccessIterator& first,
                         RandomAccessIterator last,
                         std::random_access_iterator_tag);

  template<typename InputIterator>
  void detect_properties(InputIterator& first,
                         InputIterator last,
                         std::input_iterator_tag);

  template<typename RandomAccessIterator>
  void convert(ApInt& x,
               RandomAccessIterator first, RandomAccessIterator last,
               unsigned radix,
               std::random_access_iterator_tag) const;

  template<typename InputIterator>
  void convert(ApInt& x,
               InputIterator first, InputIterator last,
               unsigned radix,
               std::input_iterator_tag) const;

  template<typename Iter>
  void convert_pow2_radix(
      ApInt& x, Iter first, Iter last, unsigned radix, const sc_type& sc) const
  {
    convert_pow2_radix(x, first, last, radix, sc,
                       typename std::iterator_traits<Iter>::iterator_category());
  }

  template<typename Iter>
  void convert_other_radix(ApInt& x,
                           Iter first, Iter last,
                           unsigned radix,
                           const sc_type& sc) const
  {
    convert_other_radix(x, first, last, radix, sc,
                        typename std::iterator_traits<Iter>::iterator_category());
  }

  template<typename RandomAccessIterator>
  void convert_pow2_radix(ApInt& x,
                          RandomAccessIterator first, RandomAccessIterator last,
                          unsigned radix,
                          const sc_type& sc,
                          std::random_access_iterator_tag) const;

  template<typename RandomAccessIterator>
  void convert_other_radix(ApInt& x,
                           RandomAccessIterator first, RandomAccessIterator last,
                           unsigned radix,
                           const sc_type& sc,
                           std::random_access_iterator_tag) const;

  template<typename InputIterator>
  void convert_pow2_radix(ApInt& x,
                          InputIterator first, InputIterator last,
                          unsigned radix,
                          const sc_type& sc,
                          std::input_iterator_tag) const;

  template<typename InputIterator>
  void convert_other_radix(ApInt& x,
                           InputIterator first, InputIterator last,
                           unsigned radix,
                           const sc_type& sc,
                           std::input_iterator_tag) const;
};


template<class ApInt>
template<typename charT>
inline
typename ApInt::digit_type
from_string_converter<ApInt>::ascii_to_value(charT c)
{
  switch (c)
  {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      c = c - '0';
      break;
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
      c = c - 'A' + 10;
      break;
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
      c = c - 'a' + 10;
  }
  return static_cast<digit_type>(c);
}


// pre: first <= last
template<class ApInt>
template<typename RandomAccessIterator>
void from_string_converter<ApInt>::
detect_properties(RandomAccessIterator& first, RandomAccessIterator last,
                  std::random_access_iterator_tag)
{
  const RandomAccessIterator beg = first;

  detect_properties(first, last, std::input_iterator_tag());

  total_length = std::distance(beg, last);
  prefix_length = std::distance(beg, first);
  length = total_length - prefix_length;
};

// pre: first <= last
template<class ApInt>
template<typename InputIterator>
void from_string_converter<ApInt>::
detect_properties(InputIterator& first, InputIterator last,
                  std::input_iterator_tag)
{
  if (first == last)
  {
    is_positive = true;
    return;
  }

  if (*first == '-')
  {
    ++first;
    is_positive = false;
  }
  else
  {
    if (*first == '+')
      ++first;
    is_positive = true;
  }

  // detect the radix
  if (first != last)
  {
    if (*first == '0') // octal
    {
      ++first;
      if (first != last && (*first == 'x' || *first == 'X')) // hex
      {
        radix = 16;
        ++first;
      }
      else
      {
        radix = 8;
        --first; // keep the zero, necessary for int_type("0")
      }
    }
    else // decimal
      radix = 10;
  }
  else
    throw std::invalid_argument(
        "from_string_converter::detect_properties: malformed string");
};

template<class ApInt>
template<typename Iter>
void from_string_converter<ApInt>::
detect_properties(Iter& first, Iter last, std::ios_base::fmtflags f)
{
  total_length = std::distance(first, last);

  if (first == last)
    return;

  const Iter beg = first;

  if (*first == '-')
  {
    is_positive = false;
    ++first;
  }
  else
  {
    if (f & std::ios_base::showpos)
    {
      if (*first == '+')
        ++first;
      else
        throw std::invalid_argument(
            "from_string_converter::detect_properties: expected a '+' sign");
    }
    is_positive = true;
  }

  // TODO should uppercase also mean that hex prefix must be 0X?
  //const bool uppercase = f & std::ios_base::uppercase;
  const bool showbase  = f & std::ios_base::showbase;

  bool bad_prefix = false;

  if (f & std::ios_base::hex)
  {
    if (showbase)
    {
      if (*first == '0')
        ++first;
      else
        bad_prefix = true;
      if (*first == 'x' || *first == 'X')
        ++first;
      else
        bad_prefix = true;
    }
    radix = 16;
  }
  else if (f & std::ios_base::oct)
  {
    if (showbase)
    {
      if (*first != '0') // keep the zero, necessary for int_type("0")
        bad_prefix = true;
    }
    radix = 8;
  }
  else if (f & std::ios_base::dec)
    radix = 10;
  else
    throw std::invalid_argument(
        "from_string_converter::detect_properties: unknown radix");

  if (bad_prefix)
    throw std::invalid_argument(
        "from_string_converter::detect_properties: bad radix prefix");

  prefix_length = std::distance(beg, first);
  length = total_length - prefix_length;
}

template<class ApInt>
template<typename RandomAccessIterator>
void
from_string_converter<ApInt>::
convert_pow2_radix(ApInt& x,
                   RandomAccessIterator first, RandomAccessIterator last,
                   unsigned radix,
                   const sc_type& sc,
                   std::random_access_iterator_tag) const
{
  digit_type result = 0;
  int        offset = 0;

  typedef std::reverse_iterator<RandomAccessIterator> reverse_iter_type;
  for (reverse_iter_type c(last); c != reverse_iter_type(first); ++c)
  {
    const digit_type y = static_cast<digit_type>(ascii_to_value(*c));

    if (y >= radix)
      throw std::invalid_argument("inv_msg");

    result |= y << offset;
    offset += sc.radix_storage_bits();

    if (offset >= static_cast<int>(radix_bits))
    {
      x.push(result);
      offset -= radix_bits;
      result = static_cast<digit_type>(y >> (sc.radix_storage_bits() - offset));
    }
  }

  if (result || x.is_uninitialized())
    x.push(result);

  x.clamp();
}

template<class ApInt>
template<typename RandomAccessIterator>
void
from_string_converter<ApInt>::
convert_other_radix(ApInt& x,
                    RandomAccessIterator first, RandomAccessIterator last,
                    unsigned radix,
                    const sc_type& sc,
                    std::random_access_iterator_tag) const
{
  for (size_type i = sc.max_exponent(); i < length; i += sc.max_exponent())
  {
    digit_type result = 0U;

    // first convert a block of decimal digits to radix 10^sc.max_exponent
    // which will still fit into a digit_type
    for (unsigned int j = 0; j < sc.max_exponent(); ++j)
    {
      const digit_type y = *first++ - '0';
      if (y >= 10U)
        throw std::invalid_argument("inv_msg");
      result = result * 10U + y;
    }

    // then use multi precision routines to convert this digit to binary
    if (x.is_initialized())
    {
      digit_type carry =
        ops_type::multiply_by_digit(x.digits(),
                                    x.digits(), x.size(),
                                    sc.max_power_value());

      carry += ops_type::add_single_digit(x.digits(),
                                          x.digits(), x.size(),
                                          result);

      if (carry)
        x.push(carry);
    }
    else
      x.push(result);
  }

  // one last round for the remaining decimal digits
  if (first != last)
  {
    digit_type radix_power = 1U;
    digit_type result = 0U;

    while (first != last)
    {
      const digit_type y = *first++ - '0';
      if (y >= 10U)
        throw std::invalid_argument("inv_msg");
      result = result * 10U + y;
      radix_power *= 10U;
    }

    if (x.size())
    {
      digit_type carry =
        ops_type::multiply_by_digit(x.digits(), x.digits(), x.size(),
                                    static_cast<digit_type>(radix_power));

      carry += ops_type::add_single_digit(x.digits(),
                                          x.digits(), x.size(),
                                          result);

      if (carry)
        x.push(carry);
    }
    else
      x.push(result);
  }
}

template<class ApInt>
template<typename InputIterator>
void
from_string_converter<ApInt>::
convert_pow2_radix(ApInt& x,
                   InputIterator first, InputIterator last,
                   unsigned radix,
                   const sc_type& sc,
                   std::input_iterator_tag) const
{
  digit_type result = 0;
  int        offset = 0;
  size_type  bits_read = 0;

  for (; first != last; ++first)
  {
    const digit_type y = static_cast<digit_type>(ascii_to_value(*first));

    if (y >= radix)
      throw std::invalid_argument("inv_msg");

    result |= y << offset;
    offset += sc.radix_storage_bits();

    if (offset >= static_cast<int>(radix_bits))
    {
      x.push(result);
      offset -= radix_bits;
      result = static_cast<digit_type>(y >> (sc.radix_storage_bits() - offset));
    }

    bits_read += sc.radix_storage_bits();
  }

  if (result || x.is_uninitialized())
    x.push(result);

  // right shift bits and reverse the digits
  const size_type n = bits_read % radix_bits;

  if (n)
  {
    const size_type shift = radix_bits - n;
    const digit_type mask = (digit_type(1) << n) - 1;
    typename ApInt::iterator b = x.begin();
    typename ApInt::iterator e = x.end();

    if (b == e)
    {
      x[0] >>= shift;
      return;
    }

    --e;
    digit_type carry1 = 0;

    while (b < e)
    {
      const digit_type c1 = *b & mask;
      digit_type d1 = (*b >> n) | (carry1 << shift);
      carry1 = c1;

      const digit_type carry2 = *(e-1) & mask;
      digit_type d2 = (*e >> n) | (carry2 << shift);

      *b = d2;
      *e = d1;

      ++b;
      --e;
    }

    // if the number of digits is odd, we need to shift the digit in the middle
    if (x.size() & 1)
      *b = (*b >> n) | (carry1 << shift);
  }
  else
    std::reverse(x.begin(), x.end());

  x.clamp();
}

template<class ApInt>
template<typename RandomAccessIterator>
void
from_string_converter<ApInt>::
convert(ApInt& x,
        RandomAccessIterator first, RandomAccessIterator last,
        unsigned radix,
        std::random_access_iterator_tag) const
{
  const sc_type sc(radix);

  //static const char* inv_msg =
  //  "from_string_converter::convert: invalid character";

  if (is_power_of_two(radix))
  {
    const size_type required =
      (length * sc.radix_storage_bits() + (radix_bits - 1)) / radix_bits;

    x.reserve(required);

    convert_pow2_radix(x, first, last, radix, sc);
  }
  else
  {
    size_type required;

    // approximate log2(10) = 3.32192809488736234787 with 10/3
    if (length < std::numeric_limits<size_type>::max() / 10U)
      required = (10U * length + 2U) / 3U;
    else
      required = length / 3U * 10U;

    required = (required + (radix_bits - 1)) / radix_bits;

    x.reserve(required);

    convert_other_radix(x, first, last, radix, sc);
  }
}


template<class ApInt, bool is_signed = ApInt::is_signed>
struct sign_prefix;

template<class ApInt> struct sign_prefix<ApInt,false>
{
  template<typename OutputIter>
  static void write(const ApInt&, std::ios_base::fmtflags f, OutputIter& c)
  {
    if (f & std::ios_base::showpos)
      *c++ = '+';
  }
};

template<class ApInt> struct sign_prefix<ApInt,true>
{
  template<typename OutputIter>
  static void write(const ApInt& x, std::ios_base::fmtflags f, OutputIter& c)
  {
    if (x.is_negative())
      *c++ = '-';
    else if (f & std::ios_base::showpos)
      *c++ = '+';
  }
};


template<class ApInt>
struct to_string_converter
{
  typedef typename ApInt::size_type             size_type;
  typedef typename ApInt::digit_type            digit_type;
  typedef typename ApInt::traits_type::ops_type ops_type;

  template<typename OutputIter>
  void convert(const ApInt& x, std::ios_base::fmtflags f, OutputIter c);

  template<class StringT>
  void convert(StringT&, const ApInt& x, std::ios_base::fmtflags f);

  static bool is_power_of_two(unsigned radix)
  {
    return (radix & (radix - 1)) == 0;
  }

  unsigned int radix;
  size_type    total_bits_; // precision of the integer we're converting
  size_type    prefix_length_;
  size_type    number_length_;
  size_type    total_length_;

  enum error_t
  {
    err_unsupported_radix,
    err_out_of_memory,
    err_no_error
  };

  error_t err;

  void check_fmtflags(std::ios_base::fmtflags f);

private:

  typedef sc_constants<ApInt> sc_type;

  static const unsigned radix_bits = ApInt::traits_type::radix_bits;

  static const char* const lowercase_tab_;
  static const char* const uppercase_tab_;
  const char* tab_;

  template<typename OutputIter>
  static void write_sign_prefix(const ApInt& x, std::ios_base::fmtflags f, OutputIter& c)
  {
    sign_prefix<ApInt>::write(x, f, c);
  }

  template<typename OutputIter>
  void write_radix_prefix(std::ios_base::fmtflags f, OutputIter& c);

  template<typename OutputIter>
  void convert_pow2_radix(const ApInt& x, const sc_type& sc, OutputIter& c) const;

  template<typename OutputIter>
  void convert_other_radix(const ApInt& x, const sc_type& sc, OutputIter& c) const;

  void estimate_number_length(const ApInt& x,
                              const sc_type& sc);
};


template<class ApInt>
const char* const
to_string_converter<ApInt>::lowercase_tab_ = "0123456789abcdef";

template<class ApInt>
const char* const
to_string_converter<ApInt>::uppercase_tab_ = "0123456789ABCDEF";


template<class ApInt>
void
to_string_converter<ApInt>::
estimate_number_length(const ApInt& x,
                       const sc_type& sc)
{
  total_bits_ = x.precision();

  // round up to a multiple of sc.radix_storage_bits
  if (total_bits_ % sc.radix_storage_bits())
    total_bits_ = total_bits_ - total_bits_ % sc.radix_storage_bits()
                + sc.radix_storage_bits();

  if (is_power_of_two(radix))
    number_length_ = (total_bits_ + (sc.radix_storage_bits() - 1))
                   / sc.radix_storage_bits();
  // approximate log2(10) with 13/4 = 3.25
  else if (total_bits_ < std::numeric_limits<size_type>::max() / 4)
    number_length_ = (total_bits_ * 4 + 12) / 13;
  else
    number_length_ = total_bits_ / 13 * 4;

  total_length_ = number_length_ + prefix_length_;
}

template<class ApInt>
void
to_string_converter<ApInt>::check_fmtflags(std::ios_base::fmtflags f)
{
  prefix_length_ = f & std::ios_base::showbase ? 1 : 0;

  if (f & std::ios_base::hex)
  {
    radix = 16;
    if (f & std::ios_base::showbase)
      prefix_length_ += 2;
  }
  else if (f & std::ios_base::oct)
  {
    radix = 8;
    if (f & std::ios_base::showbase)
      prefix_length_ += 1;
  }
  else if (f & std::ios_base::dec)
    radix = 10;
  else
    err = err_unsupported_radix;

  if (f & std::ios_base::uppercase)
    tab_ = uppercase_tab_;
  else
    tab_ = lowercase_tab_;
}

template<class ApInt>
template<typename OutputIter>
void
to_string_converter<ApInt>::
write_radix_prefix(std::ios_base::fmtflags f, OutputIter& c)
{
  if (f & std::ios_base::showbase)
  {
    if (radix == 16)
    {
      *c++ = '0';
      if (f & std::ios_base::uppercase)
        *c++ = 'X';
      else
        *c++ = 'x';
    }
    else if (radix == 8)
      *c++ = '0';
  }
}

template<class ApInt>
template<typename OutputIter>
void
to_string_converter<ApInt>::
convert_pow2_radix(const ApInt& x, const sc_type& sc, OutputIter& c) const
{
  const digit_type mask = (digit_type(1) << sc.radix_storage_bits()) - 1;

  int offset = total_bits_ % radix_bits;
  if (!offset)
    offset = radix_bits;

  typename ApInt::const_reverse_iterator d = x.rbegin();
  for (;;)
  {
    offset -= sc.radix_storage_bits();

    while (offset >= 0)
    {
      *c++ = tab_[(*d >> offset) & mask];
      offset -= sc.radix_storage_bits();
    }

    const digit_type partial_value = (*d << -offset) & mask;

    if (++d == x.rend())
      break;

    offset += radix_bits;
    *c++ = tab_[partial_value | (*d >> offset)];
  }
}

template<class ApInt>
template<typename OutputIter>
void
to_string_converter<ApInt>::
convert_other_radix(const ApInt& x, const sc_type& sc, OutputIter& c) const
{
  ApInt tmp = abs(x);

  while (tmp)
  {
    digit_type remainder = ops_type::divide_by_digit(tmp.digits(),
                                                     tmp.digits(),
                                                     tmp.size(),
                                                     sc.max_power_value());
    tmp.clamp_high_digit();

    for (digit_type i = 0; i < sc.max_exponent(); ++i)
    {
      if (remainder || tmp)
        *c++ = static_cast<char>('0' + remainder % 10U);
      remainder /= 10U;
    }
  }
}

template<class ApInt>
template<typename OutputIter>
void
to_string_converter<ApInt>::convert(const ApInt& x,
                                    std::ios_base::fmtflags f,
                                    OutputIter c)
{
  if (x.is_uninitialized())
    return;

  write_sign_prefix(x, f, c);
  write_radix_prefix(f, c);

  if (!x)
  {
    if (!(f & std::ios_base::oct))
      *c = '0';
    return;
  }

  const sc_type sc(radix);

  if (is_power_of_two(radix))
    convert_pow2_radix(x, sc, c);
  else
  {
    std::pair<char*, std::ptrdiff_t> buf =
      std::get_temporary_buffer<char>(number_length_);

    if (buf.first)
    {
      char* ptr = buf.first;
      convert_other_radix(x, sc, ptr);

      std::reverse_copy(buf.first, ptr, c);

      std::return_temporary_buffer<char>(buf.first);
    }
    else
      err = err_out_of_memory;
  }
}

template<class ApInt>
template<class StringT>
void
to_string_converter<ApInt>::convert(StringT& s,
                                    const ApInt& x,
                                    std::ios_base::fmtflags f)
{
  check_fmtflags(f);

  const sc_type sc(radix);

  estimate_number_length(x, sc);
  s.reserve(total_length_);

  convert(x, f, std::back_inserter(s));
}



} // namespace detail
} // namespace mp_math
} // namespace boost

#endif

