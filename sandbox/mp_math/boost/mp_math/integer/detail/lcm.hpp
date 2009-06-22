// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MATH_INTEGER_DETAIL_LCM_HPP
#define BOOST_MP_MATH_INTEGER_DETAIL_LCM_HPP


namespace boost {
namespace mp_math {
namespace detail {

// compute least common multiple as |a*b|/gcd(a,b)

template<class ApInt, bool IsSigned = ApInt::is_signed>
struct lcm_finder;


template<class ApInt>
struct lcm_finder<ApInt, false>
{
  static void lcm(ApInt& z, const ApInt& a, const ApInt& b);
};


template<class ApInt>
void lcm_finder<ApInt, false>::lcm(ApInt& z, const ApInt& a, const ApInt& b)
{
  if (!a || !b)
  {
    z = typename ApInt::digit_type(0);
    return;
  }

  const ApInt u(a);
  const ApInt v(b);

  z = u / gcd(u, v) * v;
}


template<class ApInt>
struct lcm_finder<ApInt, true>
{
  static void lcm(ApInt& z, const ApInt& a, const ApInt& b);
};


template<class ApInt>
void lcm_finder<ApInt, true>::lcm(ApInt& z, const ApInt& a, const ApInt& b)
{
  if (!a || !b)
  {
    z = typename ApInt::digit_type(0);
    return;
  }

  const ApInt u = abs(a);
  const ApInt v = abs(b);

  z = u / gcd(u, v) * v;
}


} // namespace detail
} // namespace mp_math
} // namespace boost

#endif

