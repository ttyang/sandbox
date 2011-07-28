
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float.hpp>
#include <e_float/e_float_constants.hpp>
#include <e_float/e_float_elementary.hpp>
#include <e_float/e_float_integer.hpp>
#include <e_float/e_float_gamma.hpp>

#include "../tables/tables.h"

e_float ef::bernoulli(const UINT32 n)
{
  if(static_cast<UINT32>(n % static_cast<UINT32>(2u)) != static_cast<UINT32>(0u))
  {
    return (n == static_cast<UINT32>(1u) ? -ef::half() : ef::zero());
  }
  else
  {
    static const std::size_t sz_A000367 = Tables::A000367().size();
    static const std::size_t sz_A002445 = Tables::A002445().size();
    static const std::size_t sz_max     = (std::min)(sz_A000367, sz_A002445);

    const std::size_t n_half = static_cast<std::size_t>(n / static_cast<UINT32>(2u));

    if(n_half < sz_max)
    {
      return Tables::A000367()[n_half]() / Tables::A002445()[n_half]();
    }
    else
    {
      // Do a loop calculation for higher numbered Bernoulli numbers.
      // See Abramowitz & Stegun 23.1.18, page 805, for x = 0.
      // See Computation of Special Functions, Zhang & Jin, 1.1.16, page 5.

      e_float sum = ef::one();

      // TBD: Check the power of two using logs and floating point math to see
      //      if the loop is even necessary.

      for(INT32 k = static_cast<INT32>(2); k < ef::max_iteration(); k++)
      {
        const e_float one_over_k = ef::one() / k;
        const e_float term       = ef::pown(one_over_k, static_cast<INT64>(n));
        
        if(term.order() < -ef::tol())
        {
          break;
        }

        sum += term;
      }

      const bool b_neg = static_cast<UINT32>(static_cast<UINT32>(n / static_cast<UINT32>(2u)) & static_cast<UINT32>(1u)) == static_cast<UINT32>(0u);

      const e_float factor = ((ef::factorial(n) / ef::pown(ef::two_pi(), static_cast<INT64>(n))) * static_cast<INT32>(2));
      const e_float bn     = sum * factor;

      return !b_neg ? bn : -bn;
    }
  }
}

void ef::bernoulli_table(std::vector<e_float>& bn, const UINT32 n)
{
  // See reference "Computing Bernoulli and Tangent Numbers", Richard P. Brent.
  // See also the book Richard P. Brent and Paul Zimmermann, "Modern Computer Arithmetic",
  // Cambridge University Press, 2010, 237 pp.

  const UINT32 nn = (((n % static_cast<UINT32>(2)) != static_cast<UINT32>(0u)) ? static_cast<UINT32>(n + 1u) : n);

  const INT32 m = nn / 2;

  std::vector<e_float> tangent_numbers(static_cast<std::vector<e_float>::size_type>(m + 1));

  tangent_numbers[0u] = ef::zero();
  tangent_numbers[1u] = ef::one();

  for(INT32 k = 2; k <= m; k++)
  {
    tangent_numbers[k] = (k - 1) * tangent_numbers[k - 1];
  }

  for(INT32 k = 2; k <= m; k++)
  {
    for(INT32 j = k; j <= m; j++)
    {
      tangent_numbers[j] = (tangent_numbers[j - 1] * (j - k)) + (tangent_numbers[j] * (j - k + 2));
    }
  }

  e_float two_pow_two_m(4);

  bn.clear();
  bn.resize(static_cast<std::vector<e_float>::size_type>(nn + 1));

  for(INT32 i = 1; i < static_cast<INT32>(tangent_numbers.size()); i++)
  {
    const INT32 two_i = static_cast<INT32>(static_cast<INT32>(2) * i);

    const e_float b = (tangent_numbers[i] * two_i) / (two_pow_two_m * (two_pow_two_m - 1));

    const bool  b_neg = (static_cast<INT32>(two_i % static_cast<INT32>(4)) == static_cast<INT32>(0));

    bn[2 * i] = ((!b_neg) ? b : -b);

    two_pow_two_m *= 4;
  }

  bn[0u] =  ef::one();
  bn[1u] = -ef::half();
}
