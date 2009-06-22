// Copyright Tom St Denis 2002 - 2007.
// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MATH_INTEGER_DETAIL_POWER_HPP
#define BOOST_MP_MATH_INTEGER_DETAIL_POWER_HPP

#include <boost/mp_math/integer/detail/multiplier.hpp>
#include <boost/type_traits/make_unsigned.hpp>

namespace boost {
namespace mp_math {
namespace detail {

template<
  class ApInt,
  bool IsSigned = ApInt::is_signed
>
struct power;


template<class ApInt>
struct power<ApInt, false>
{
  typedef typename ApInt::digit_type digit_type;
  typedef typename ApInt::size_type  size_type;

  static void pow(ApInt& z, const ApInt& x, size_type y);
  static void pow(ApInt& z, const ApInt& x, const ApInt& y);
  static void pow2(ApInt& z, size_type n);
};


template<class ApInt>
void power<ApInt, false>::pow(ApInt& z, const ApInt& x, size_type y)
{
  z = digit_type(1);

  if (y == 0U)
    return;

  size_type mask = size_type(1) << (std::numeric_limits<size_type>::digits - 1);

  int i = 0;
  while (!(y & mask)) // skip leading zero bits
  {
    ++i;
    mask >>= 1;
  }

  for (; i < std::numeric_limits<size_type>::digits; ++i)
  {
    multiplier<ApInt>::sqr(z);

    // if the bit is set multiply
    if (y & mask)
      multiplier<ApInt>::mul(z, z, x);

    // shift to next bit
    mask >>= 1;
  }
}

// calculate z = x^y using a square-multiply algorithm
template<class ApInt>
void power<ApInt, false>::pow(ApInt& z, const ApInt& x, const ApInt& y)
{
  if (y.size() == 1)
  {
    pow(z, x, y[0]);
    return;
  }

  z = digit_type(1);

  ApInt mask(digit_type(1));
  mask <<= y.precision() - 1; // TODO use pow2

  for (size_type i = 0; i < y.precision(); ++i)
  {
    multiplier<ApInt>::sqr(z);

    // if the bit is set multiply
    if (y & mask)
      multiplier<ApInt>::mul(z, z, x);

    // shift to next bit
    mask >>= 1;
  }
}

// computes z = 2^n
template<class ApInt>
void power<ApInt, false>::pow2(ApInt& z, size_type n)
{
  static const size_type db = ApInt::traits_type::digit_bits;
  const size_type q = n / db + 1;
  const size_type r = n % db;

  z.reserve(q);

  std::memset(z.digits(), 0, q * sizeof(digit_type));

  z[q-1] = digit_type(1) << r;

  z.set_size(q);
}



template<class ApInt>
struct power<ApInt, true>
{
  typedef typename ApInt::size_type size_type;

  static void pow(ApInt& z, const ApInt& x, size_type y)
  {
    power<ApInt, false>::pow(z, x, y);
    z.set_sign_bit(y & 1 ? x.sign_bit() : 0);
  }

  static void pow(ApInt& z, const ApInt& x, const ApInt& y)
  {
    if (y.is_negative())
      throw std::domain_error("pow: negative exponent");
    power<ApInt, false>::pow(z, x, y);
    z.set_sign_bit(y.is_odd() ? x.sign_bit() : 0);
  }

  static void pow2(ApInt& z, size_type n)
  {
    power<ApInt, false>::pow2(z, n);
  }
};


} // namespace detail
} // namespace mp_math
} // namespace boost

#endif

