// Copyright Tom St Denis 2002 - 2007.
// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MATH_INTEGER_DETAIL_GCD_HPP
#define BOOST_MP_MATH_INTEGER_DETAIL_GCD_HPP

namespace boost {
namespace mp_math {
namespace detail {


template<class ApInt, bool IsSigned = ApInt::is_signed>
struct gcd_finder;


template<class ApInt>
struct gcd_finder<ApInt, false>
{
  static void gcd(ApInt& z, const ApInt& a, const ApInt& b);
  static void binary_method(ApInt& z, ApInt& u, ApInt& v);
};


template<class ApInt>
void gcd_finder<ApInt, false>::gcd(ApInt& z, const ApInt& a, const ApInt& b)
{
  // either zero then gcd is the largest
  if (!a)
  {
    z = b;
    return;
  }

  if (!b)
  {
    z = a;
    return;
  }

  // get copies of a and b we can modify
  ApInt u(a);
  ApInt v(b);

  binary_method(z, u, v);
}

// Greatest Common Divisor using the binary method
template<class ApInt>
void gcd_finder<ApInt, false>::binary_method(ApInt& z, ApInt& u, ApInt& v)
{
  typedef typename ApInt::size_type size_type;

  // Find the common power of two for u and v
  const size_type u_tzb = u.count_trailing_zero_bits();
  const size_type v_tzb = v.count_trailing_zero_bits();
  const size_type     k = std::min(u_tzb, v_tzb);

  // divide out powers of two
  u >>= u_tzb;
  v >>= v_tzb;

  while (v)
  {
    if (u > v)
      u.swap(v);

    v -= u;

    // Divide out all factors of two
    v >>= v.count_trailing_zero_bits();
  }

  // multiply by 2^k which we divided out at the beginning
  u <<= k;

  swap(z, u);
}


template<class ApInt>
struct gcd_finder<ApInt, true>
{
  static void gcd(ApInt& z, const ApInt& a, const ApInt& b);
};


template<class ApInt>
void gcd_finder<ApInt, true>::gcd(ApInt& z, const ApInt& a, const ApInt& b)
{
  // either zero then gcd is the largest
  if (!a)
  {
    z = abs(b);
    return;
  }
  if (!b)
  {
    z = abs(a);
    return;
  }

  // get copies of a and b we can modify
  ApInt u = abs(a);
  ApInt v = abs(b);

  gcd_finder<ApInt, false>::binary_method(z, u, v);
}


} // namespace detail
} // namespace mp_math
} // namespace boost

#endif

