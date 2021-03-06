
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/e_float/e_float.hpp>
#include <boost/e_float/e_float_functions.hpp>

#include "../tables/tables.h"

namespace Factorial_Series
{
  e_float AtInfinity(const UINT32 n);
}

e_float Factorial_Series::AtInfinity(const UINT32 n)
{
  const e_float x                              = e_float(n);
        e_float one_over_x_pow_two_n_minus_one = ef::one() / x;
  const e_float one_over_x2                    = one_over_x_pow_two_n_minus_one * one_over_x_pow_two_n_minus_one;

  static const e_float B2 =   Tables::A000367()[static_cast<std::size_t>(1u)]()
                            / Tables::A002445()[static_cast<std::size_t>(1u)]();

  e_float sum = (B2 * one_over_x_pow_two_n_minus_one) / static_cast<INT32>(2);

  static const std::size_t sz_A000367 = Tables::A000367().size();
  static const std::size_t sz_A002445 = Tables::A002445().size();
  static const std::size_t sz_max     = (std::min)(sz_A000367, sz_A002445);

  // Perform the Bernoulli series expansion without explicitly calling the function
  // ef::Bernoulli in order to avoid any recursive calls of ef::factorial. This is
  // because ef::bernoulli_b calls ef::factorial for large integers.

  for(INT32 k = static_cast<INT32>(2); k < static_cast<INT32>(sz_max); k++)
  {
    one_over_x_pow_two_n_minus_one *= one_over_x2;

    const INT32 two_k           = static_cast<INT32>(k     * static_cast<INT32>(2));
    const INT32 two_k_minus_one = static_cast<INT32>(two_k - static_cast<INT32>(1));

    const e_float B2k =   Tables::A000367()[static_cast<std::size_t>(k)]()
                        / Tables::A002445()[static_cast<std::size_t>(k)]();

    const e_float term = ((B2k * one_over_x_pow_two_n_minus_one) / two_k) / two_k_minus_one;

    if(term.order() < -ef::tol())
    {
      break;
    }

    sum += term;
  }

  static const e_float half_ln_two_pi = ef::log(ef::two_pi()) / static_cast<INT32>(2);

  return ef::exp(((((x - ef::half()) * ef::log(x)) - x) + half_ln_two_pi) + sum);
}

e_float ef::factorial(const UINT32 n)
{
  return (static_cast<std::size_t>(n) < Tables::A000142().size()) ? Tables::A000142()[n]()
                                                                  : Factorial_Series::AtInfinity(static_cast<UINT32>(n + static_cast<UINT32>(1u)));
}

e_float ef::binomial(const UINT32 n, const UINT32 k)
{
  if(k > n)
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }
  else if(k == n)
  {
    return ef::one();
  }
  else
  {
    if(n < static_cast<UINT32>(Tables::A007318().size()))
    {
      return Tables::A007318()[static_cast<std::size_t>(n)]()[static_cast<std::size_t>(k)];
    }
    else
    {
      return ef::factorial(n) / (ef::factorial(k) * ef::factorial(n - k));
    }
  }
}

e_float ef::binomial(const UINT32 n, const e_float& y)
{
  return ef::factorial(n) / (ef::gamma(y + ef::one()) * ef::gamma((e_float(n) - y) + ef::one()));
}

e_float ef::binomial(const e_float& x, const UINT32 k)
{
  return ef::gamma(x + ef::one()) / (ef::factorial(k) * ef::gamma((x - e_float(k)) + ef::one()));
}

e_float ef::binomial(const e_float& x, const e_float& y)
{
  return ef::gamma(x + ef::one()) / (ef::gamma(y + ef::one()) * ef::gamma((x - y) + ef::one()));
}
