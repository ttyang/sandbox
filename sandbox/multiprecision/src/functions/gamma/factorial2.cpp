
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float_functions.hpp>
#include "../tables/tables.h"

using boost::multiprecision::mp_float;

namespace Factorial2_Series
{
  mp_float AtInfinity(const boost::int32_t n);
}

mp_float Factorial2_Series::AtInfinity(const boost::int32_t n)
{
  const bool n_is_even = static_cast<boost::int32_t>(n % static_cast<boost::int32_t>(2)) == static_cast<boost::int32_t>(0u);

  if(n_is_even)
  {
    const boost::uint32_t n_half = static_cast<boost::uint32_t>(static_cast<boost::uint32_t>(n) / static_cast<boost::uint32_t>(2));

    return boost::multiprecision::pow2(static_cast<boost::int64_t>(n_half)) * boost::multiprecision::factorial(n_half);
  }
  else
  {
    const boost::int32_t n_plus_one = static_cast<boost::int32_t>(static_cast<boost::int32_t>(n) + static_cast<boost::int32_t>(1));

    return boost::multiprecision::factorial(static_cast<boost::uint32_t>(n_plus_one)) / boost::multiprecision::factorial2(n_plus_one);
  }
}

mp_float boost::multiprecision::factorial2(const boost::int32_t n)
{
  const bool n_is_neg  = (n < static_cast<boost::int32_t>(0));

  if(!n_is_neg)
  {
    return (static_cast<std::size_t>(n) < Tables::A006882().size()) ? Tables::A006882()[n]()
                                                                    : Factorial2_Series::AtInfinity(n);
  }
  else
  {
    if(n == static_cast<boost::int32_t>(-1))
    {
      return boost::multiprecision::one();
    }

    const boost::int32_t nn        = (!n_is_neg ? n : static_cast<boost::int32_t>(-n));
    const bool  n_is_even = (static_cast<boost::int32_t>(nn % static_cast<boost::int32_t>(2)) == static_cast<boost::int32_t>(0u));

    if(n_is_even)
    {
      return std::numeric_limits<mp_float>::quiet_NaN();
    }
    else
    {
      // Double factorial for negative odd integers.
      const boost::int32_t n_minus_one_over_two = static_cast<boost::int32_t>(static_cast<boost::int32_t>(nn - static_cast<boost::int32_t>(1)) / static_cast<boost::int32_t>(2));
      const bool  b_negate             = static_cast<boost::int32_t>(n_minus_one_over_two % static_cast<boost::int32_t>(2)) != static_cast<boost::int32_t>(0);

      const mp_float f2 = boost::multiprecision::one() / boost::multiprecision::factorial2(static_cast<boost::int32_t>(nn - static_cast<boost::int32_t>(2)));

      return (!b_negate ? f2 : -f2);
    }
  }
}
