
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

mp_float boost::multiprecision::bernoulli(const boost::uint32_t n)
{
  if(static_cast<boost::uint32_t>(n % static_cast<boost::uint32_t>(2u)) != static_cast<boost::uint32_t>(0u))
  {
    return (n == static_cast<boost::uint32_t>(1u) ? -boost::multiprecision::half() : boost::multiprecision::zero());
  }
  else
  {
    static const std::size_t sz_A000367 = Tables::A000367().size();
    static const std::size_t sz_A002445 = Tables::A002445().size();
    static const std::size_t sz_max     = (std::min)(sz_A000367, sz_A002445);

    const std::size_t n_half = static_cast<std::size_t>(n / static_cast<boost::uint32_t>(2u));

    if(n_half < sz_max)
    {
      return Tables::A000367()[n_half]() / Tables::A002445()[n_half]();
    }
    else
    {
      // Do a loop calculation for higher numbered Bernoulli numbers.
      // See Abramowitz & Stegun 23.1.18, page 805, for x = 0.
      // See Computation of Special Functions, Zhang & Jin, 1.1.16, page 5.

      mp_float sum = boost::multiprecision::one();

      // TBD: Check the power of two using logs and floating point math to see
      //      if the loop is even necessary.

      for(boost::int32_t k = static_cast<boost::int32_t>(2); k < boost::multiprecision::max_iteration(); k++)
      {
        const mp_float one_over_k = boost::multiprecision::one() / k;
        const mp_float term       = boost::multiprecision::pown(one_over_k, static_cast<boost::int64_t>(n));
        
        if(term.order() < -boost::multiprecision::tol())
        {
          break;
        }

        sum += term;
      }

      const bool b_neg = static_cast<boost::uint32_t>(static_cast<boost::uint32_t>(n / static_cast<boost::uint32_t>(2u)) & static_cast<boost::uint32_t>(1u)) == static_cast<boost::uint32_t>(0u);

      const mp_float factor = ((boost::multiprecision::factorial(n) / boost::multiprecision::pown(boost::multiprecision::two_pi(), static_cast<boost::int64_t>(n))) * static_cast<boost::int32_t>(2));
      const mp_float bn     = sum * factor;

      return ((!b_neg) ? bn : -bn);
    }
  }
}

void boost::multiprecision::bernoulli_table(std::vector<mp_float>& bn, const boost::uint32_t n)
{
  // See reference "Computing Bernoulli and Tangent Numbers", Richard P. Brent.
  // Also see "Modern Computer Arithmetic", Richard P. Brent and Paul Zimmermann,
  // Cambridge University Press, 2010, 237 pp.

  const boost::uint32_t nn = (((n % static_cast<boost::uint32_t>(2)) != static_cast<boost::uint32_t>(0u)) ? static_cast<boost::uint32_t>(n + 1u) : n);

  const boost::int32_t m = static_cast<boost::int32_t>(nn / static_cast<boost::uint32_t>(2u));

  std::vector<mp_float> tangent_numbers(static_cast<std::vector<mp_float>::size_type>(m + 1));

  tangent_numbers[0u] = boost::multiprecision::zero();
  tangent_numbers[1u] = boost::multiprecision::one();

  for(boost::int32_t k = static_cast<boost::int32_t>(2); k <= m; k++)
  {
    tangent_numbers[k] = tangent_numbers[k - 1] * static_cast<boost::int32_t>(k - static_cast<boost::int32_t>(1));
  }

  for(boost::int32_t k = static_cast<boost::int32_t>(2); k <= m; k++)
  {
    for(boost::int32_t j = k; j <= m; j++)
    {
      const boost::int32_t j_minus_k = static_cast<boost::int32_t>(j - k);

      tangent_numbers[j] =   (tangent_numbers[j - 1] * j_minus_k)
                           + (tangent_numbers[j] * static_cast<boost::int32_t>(j_minus_k + static_cast<boost::int32_t>(2)));
    }
  }

  mp_float two_pow_two_m(4);

  bn.clear();
  bn.resize(static_cast<std::vector<mp_float>::size_type>(nn + static_cast<boost::uint32_t>(1u)));

  for(boost::int32_t i = static_cast<boost::int32_t>(1); i < static_cast<boost::int32_t>(tangent_numbers.size()); i++)
  {
    const boost::int32_t two_i = static_cast<boost::int32_t>(static_cast<boost::int32_t>(2) * i);

    const mp_float b = (tangent_numbers[i] * two_i) / ((two_pow_two_m * two_pow_two_m) - two_pow_two_m);

    const bool  b_neg = (static_cast<boost::int32_t>(two_i % static_cast<boost::int32_t>(4)) == static_cast<boost::int32_t>(0));

    bn[2 * i] = ((!b_neg) ? b : -b);

    two_pow_two_m *= static_cast<boost::int32_t>(4);
  }

  bn[0u] =  boost::multiprecision::one();
  bn[1u] = -boost::multiprecision::half();
}
