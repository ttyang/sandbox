
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>

#include "../tables/tables.h"

using boost::multiprecision::mp_float;

namespace
{
  mp_float my_factorial_series_at_infinity(const boost::uint32_t n)
  {
    const mp_float x                              = mp_float(n);
          mp_float one_over_x_pow_two_n_minus_one = boost::multiprecision::one() / x;
    const mp_float one_over_x2                    = one_over_x_pow_two_n_minus_one * one_over_x_pow_two_n_minus_one;

    static const mp_float B2 =   boost::multiprecision::tables::A000367()[static_cast<std::size_t>(1u)]()
                              / boost::multiprecision::tables::A002445()[static_cast<std::size_t>(1u)]();

    mp_float sum = (B2 * one_over_x_pow_two_n_minus_one) / static_cast<boost::int32_t>(2);

    static const std::size_t sz_A000367 = boost::multiprecision::tables::A000367().size();
    static const std::size_t sz_A002445 = boost::multiprecision::tables::A002445().size();
    static const std::size_t sz_max     = (std::min)(sz_A000367, sz_A002445);

    // Perform the Bernoulli series expansion without explicitly calling the function
    // boost::multiprecision::Bernoulli in order to avoid any recursive calls of boost::multiprecision::factorial. This is
    // because boost::multiprecision::bernoulli_b calls boost::multiprecision::factorial for large integers.

    for(boost::int32_t k = static_cast<boost::int32_t>(2); k < static_cast<boost::int32_t>(sz_max); k++)
    {
      one_over_x_pow_two_n_minus_one *= one_over_x2;

      const boost::int32_t two_k           = static_cast<boost::int32_t>(k     * static_cast<boost::int32_t>(2));
      const boost::int32_t two_k_minus_one = static_cast<boost::int32_t>(two_k - static_cast<boost::int32_t>(1));

      const mp_float B2k =   boost::multiprecision::tables::A000367()[static_cast<std::size_t>(k)]()
                          / boost::multiprecision::tables::A002445()[static_cast<std::size_t>(k)]();

      const mp_float term = ((B2k * one_over_x_pow_two_n_minus_one) / two_k) / two_k_minus_one;

      if(term.order() < -boost::multiprecision::tol())
      {
        break;
      }

      sum += term;
    }

    static const mp_float half_ln_two_pi = boost::multiprecision::log(boost::multiprecision::two_pi()) / static_cast<boost::int32_t>(2);

    return boost::multiprecision::exp(((((x - boost::multiprecision::half()) * boost::multiprecision::log(x)) - x) + half_ln_two_pi) + sum);
  }
}

mp_float boost::multiprecision::factorial(const boost::uint32_t n)
{
  return (static_cast<std::size_t>(n) < boost::multiprecision::tables::A000142().size()) ? boost::multiprecision::tables::A000142()[n]()
                                                                  : ::my_factorial_series_at_infinity(static_cast<boost::uint32_t>(n + static_cast<boost::uint32_t>(1u)));
}

mp_float boost::multiprecision::binomial(const boost::uint32_t n, const boost::uint32_t k)
{
  if(k > n)
  {
    return std::numeric_limits<mp_float>::quiet_NaN();
  }
  else if(k == n)
  {
    return boost::multiprecision::one();
  }
  else
  {
    if(n < static_cast<boost::uint32_t>(boost::multiprecision::tables::A007318().size()))
    {
      return boost::multiprecision::tables::A007318()[static_cast<std::size_t>(n)]()[static_cast<std::size_t>(k)];
    }
    else
    {
      return boost::multiprecision::factorial(n) / (boost::multiprecision::factorial(k) * boost::multiprecision::factorial(n - k));
    }
  }
}

mp_float boost::multiprecision::binomial(const boost::uint32_t n, const mp_float& y)
{
  return boost::multiprecision::factorial(n) / (boost::multiprecision::gamma(y + boost::multiprecision::one()) * boost::multiprecision::gamma((mp_float(n) - y) + boost::multiprecision::one()));
}

mp_float boost::multiprecision::binomial(const mp_float& x, const boost::uint32_t k)
{
  return boost::multiprecision::gamma(x + boost::multiprecision::one()) / (boost::multiprecision::factorial(k) * boost::multiprecision::gamma((x - mp_float(k)) + boost::multiprecision::one()));
}

mp_float boost::multiprecision::binomial(const mp_float& x, const mp_float& y)
{
  return boost::multiprecision::gamma(x + boost::multiprecision::one()) / (boost::multiprecision::gamma(y + boost::multiprecision::one()) * boost::multiprecision::gamma((x - y) + boost::multiprecision::one()));
}
