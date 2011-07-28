
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>

#include <e_float/e_float.hpp>

#include <e_float/e_float_complex.hpp>
#include <e_float/e_float_constants.hpp>
#include <e_float/e_float_elementary.hpp>
#include <e_float/e_float_integer.hpp>
#include <e_float/e_float_gamma.hpp>
#include <e_float/e_float_prime.hpp>
#include <e_float/e_float_zeta.hpp>

#include "../tables/tables.h"
#include "../../utility/util_power_j_pow_x.h"

namespace Zeta_Series
{
  bool has_simple_form_for_zeta_n(const INT32 n)
  {
    // Zeta(n) has a simple form for all negative integer values of n as well
    // as for all positive, even values of n. The simple form is related to
    // a Bernoulli number. Therefore the simple form is only easy to calculate
    // as long as the range of n stays within the range of the tabulated values
    // of the Bernoulli numbers.

    // Check the range of the tabulated values of the Bernoulli numbers.
    static const std::size_t sz_A000367 = static_cast<std::size_t>(Tables::A000367().size());
    static const std::size_t sz_A002445 = static_cast<std::size_t>(Tables::A002445().size());

    static const INT32 b2n_table_max = static_cast<INT32>(2u * (std::min)(sz_A000367, sz_A002445));

    const bool is_neg  = (n < static_cast<INT32>(0));
    const bool is_even = (n % static_cast<INT32>(2)) == static_cast<INT32>(0);

    const bool is_pos_and_even = ((!is_neg) && is_even);
    const bool is_in_table     = (n < b2n_table_max);

    return (is_in_table && (is_pos_and_even || is_neg));
  }

  template<typename T,
           typename TR>
  T Reflection(const T& s)
  {
    using ef::gamma;
    using efz::gamma;
    using ef::pow;
    using efz::pow;
    using ef::sin;
    using efz::sin;
    using ef::riemann_zeta;
    using efz::riemann_zeta;
    using ef::one;
    using ef::two;
    using ef::pi;
    using ef::two_pi;
    using ef::pi_half;

    const T two_pi_term = pow(two_pi(), s) / pi();
    const T chi         = (two_pi_term * sin(pi_half() * s)) * gamma(one() - s);

    return chi * riemann_zeta(one() - s);
  }

  template<typename T,
           typename TR>
  T ZetaTemplate(const T& s)
  {
    using ef::abs;
    using efz::abs;
    using ef::imag;
    using efz::imag;
    using ef::pow;
    using ef::pown;
    using efz::pow;
    using ef::real;
    using efz::real;
    using ef::tol;
    using ef::prime;
    using ef::isneg;
    using ef::iszero;
    using ef::isint;
    using ef::to_int32;
    using ef::to_double;
    using ef::order_of;
    using ef::factorial;
    using ef::riemann_zeta;
    using ef::one;
    using ef::two;
    using ef::four;
    using ef::hundred;
    using ef::million;

    if(isint(s))
    {
      // Support pure-integer arguments according to certain conditions.
      const INT32 n = to_int32(real(s));

      if(Zeta_Series::has_simple_form_for_zeta_n(n))
      {
        return T(riemann_zeta(n));
      }
    }

    if(isneg(s))
    {
      // Support negative arguments using the reflection formula.
      // Support arguments with a real part which is less than 1/2.
      return Zeta_Series::Reflection<T, TR>(s);
    }

    // The algorithms for calculating the Riemann zeta function below use calculations
    // of the integer j raised to the power s, or in other words j^s. The calculation of
    // j^s is accelerated using tables of the prime factors of j raised to the power s.
    // The calculation is furthermore accelerated by storing the necessary integer
    // logarithms in a static table.

    // Declare a map of prime factors raised to the power of the argument s.
    std::map<UINT32, T> n_pow_s_prime_factor_map;

    // Generate a list of the first 300 prime numbers.
    static std::deque<UINT32> prime_data;

    if(prime_data.empty())
    {
      prime(static_cast<UINT32>(300u), prime_data);
    }

    static const std::vector<UINT32> primes(prime_data.begin(), prime_data.end());

    // Test the conditions for the expansion of the product of primes. Set up a
    // test for the product of primes. The expansion in the product of primes can
    // be used if the number of prime-power terms remains reasonably small, say
    // less than or equal to 300.
    static const double lg10_max_prime = ::log10(static_cast<double>(primes.back()));
    static const double td             = static_cast<double>(static_cast<INT32>(tol()));
           const double sd             = to_double(real(s));

    if(iszero(imag(s)) && ((td / sd) < lg10_max_prime))
    {
      // Perform the product of primes.
      T product(1u);

      for(std::size_t p = static_cast<std::size_t>(0u); p < primes.size(); p++)
      {
        const T prime_p_pow_s = Util::j_pow_x(primes[p], s, n_pow_s_prime_factor_map);

        product *= prime_p_pow_s / (prime_p_pow_s - one());

        if(order_of(abs(prime_p_pow_s)) > tol())
        {
          break;
        }
      }

      return product;
    }
    else
    {
      static const TR very_large = million() + hundred();

      if(abs(imag(s)) > very_large)
      {
        // Return NaN if s has a very large imaginary part.
        return std::numeric_limits<TR>::quiet_NaN();
      }

      // Use the accelerated alternating converging series for Zeta as shown in:
      // http://numbers.computation.free.fr/Constants/Miscellaneous/zetaevaluations.html
      // taken from P. Borwein, "An Efficient Algorithm for the Riemann Zeta Function",
      // January 1995.

      // Compute the coefficients dk in a loop and calculate the zeta function sum
      // within the same loop on the fly.

      // Set up the factorials and powers for the calculation of the coefficients dk.
      // Note that j = n at this stage in the calculation. Also note that the value of
      // dn is equal to the value of d0 at the end of the loop.

      // Use N = (digits * 1.45) + {|imag(s)| * 1.1}
      static const double nd = static_cast<double>(std::numeric_limits<TR>::digits10) * static_cast<double>(1.45);
             const double ni = static_cast<double>(1.10 * ::fabs(to_double(imag(s))));

      const INT32 N        = static_cast<INT32>(static_cast<INT64>(static_cast<double>(nd + ni)));
            bool  neg_term = (N % static_cast<INT32>(2)) == static_cast<INT32>(0);

      TR n_plus_j_minus_one_fact = factorial(static_cast<UINT32>((N + N) - 1));
      TR four_pow_j              = pown(four(), static_cast<INT64>(N));
      TR n_minus_j_fact          = one();
      TR two_j_fact              = n_plus_j_minus_one_fact * static_cast<INT32>(static_cast<INT32>(2) * N);

      TR dn = (n_plus_j_minus_one_fact * four_pow_j) / (n_minus_j_fact * two_j_fact);

      T jps = Util::j_pow_x(N, s, n_pow_s_prime_factor_map);

      T dn_term = ((!neg_term) ? dn : -dn);

      T zs = dn_term / jps;

      for(INT32 j = N - static_cast<INT32>(1); j >= static_cast<INT32>(0); j--)
      {
        const bool j_is_zero = (j == static_cast<INT32>(0));

        const INT32 two_jp1_two_j =   static_cast<INT32>((static_cast<INT32>(2) * j) + static_cast<INT32>(1))
                                    * static_cast<INT32> (static_cast<INT32>(2) * ((!j_is_zero) ? j : static_cast<INT32>(1)));

        n_plus_j_minus_one_fact /= static_cast<INT32>(N + j);
        four_pow_j              /= static_cast<INT32>(4);
        n_minus_j_fact          *= static_cast<INT32>(N - j);
        two_j_fact              /= two_jp1_two_j;

        dn += ((n_plus_j_minus_one_fact * four_pow_j) / (n_minus_j_fact * two_j_fact));

        if(!j_is_zero)
        {
          // Increment the zeta function sum.
          jps = Util::j_pow_x(static_cast<UINT32>(j), s, n_pow_s_prime_factor_map);

          neg_term = !neg_term;

          dn_term = ((!neg_term) ? dn : -dn);

          zs += (dn_term / jps);
        }
      }

      const T two_pow_one_minus_s = pow(two(), one() - s);

      return zs / (dn * (one() - two_pow_one_minus_s));
    }
  }
}

e_float ef::riemann_zeta(const INT32 n)
{
  // Check if the result of the expansion will significantly differ from one.
  if(n > static_cast<INT32>(1))
  {
    static const double log10_of_2 = ::log10(2.0);
    static const double dtol       = static_cast<double>(static_cast<INT32>(ef::tol()));

    const double n_log10_of_2 = static_cast<double>(n) * log10_of_2;

    if(n_log10_of_2 > dtol)
    {
      // The result does not significantly differ from one.
      return ef::one();
    }
  }

  // Check if there is a simple form for Zeta(n).
  if(!Zeta_Series::has_simple_form_for_zeta_n(n))
  {
    // There is no simple form for Zeta(n). Do the e_float calculation.
    return riemann_zeta(e_float(n));
  }
  else
  {
    // There is a simple form for Zeta(n). Use the Bernoulli representation.
    if     (n == static_cast<INT32>(0)) { return -ef::half(); }
    else if(n == static_cast<INT32>(1)) { return std::numeric_limits<e_float>::infinity(); }
    else if(n == static_cast<INT32>(2)) { return  ef::pi_squared() / static_cast<INT32>(6); }
    else if(n == static_cast<INT32>(4)) { return (ef::pi_squared() * ef::pi_squared()) / static_cast<INT32>(90); }
    else
    {
      if(n < static_cast<INT32>(0))
      {
        const UINT32 two_n = static_cast<UINT32>(static_cast<INT32>(-n) + static_cast<INT32>(1));

        const bool is_even = (n % static_cast<INT32>(2)) == static_cast<INT32>(0);

        return is_even ? ef::zero() : -ef::bernoulli(two_n) / static_cast<INT32>(two_n);
      }
      else
      {
        const UINT32 two_n = static_cast<UINT32>(n);

        const e_float two_pi_pow_2n = ef::pown(ef::two_pi(), static_cast<INT64>(two_n));

        return ((two_pi_pow_2n * ef::fabs(ef::bernoulli(two_n))) / ef::factorial(two_n)) / static_cast<INT32>(2);
      }
    }
  }
}

e_float ef::riemann_zeta(const e_float& s)
{
  if(s.has_its_own_riemann_zeta())
  {
    return e_float::my_riemann_zeta(s);
  }
  else
  {
    return Zeta_Series::ZetaTemplate<e_float, e_float>(s);
  }
}

ef_complex efz::riemann_zeta(const ef_complex& s)
{
  if(ef::iszero(s.imag()))
  {
    return ef_complex(Zeta_Series::ZetaTemplate<e_float, e_float>(s.real()));
  }
  else
  {
    return Zeta_Series::ZetaTemplate<ef_complex, e_float>(s);
  }
}
