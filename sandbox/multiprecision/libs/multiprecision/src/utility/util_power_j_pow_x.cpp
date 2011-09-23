
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float_functions.hpp>
#include <boost/multiprecision/utility/util_point.hpp>
#include <boost/multiprecision/utility/util_power_j_pow_x.hpp>
#include "../functions/integer/prime_factors.h"

using boost::multiprecision::mp_float;
using boost::multiprecision::mp_complex;

namespace
{
  mp_float my_logn(const boost::uint_fast32_t n)
  {
    static std::map<boost::uint_fast32_t, mp_float> logn_data;

    const std::map<boost::uint_fast32_t, mp_float>::const_iterator it = logn_data.find(n);

    if(it == logn_data.end())
    {
      const mp_float logn_value = boost::multiprecision::log(mp_float(n));

      logn_data[static_cast<std::size_t>(n)] = logn_value;

      return logn_value;
    }
    else
    {
      return it->second;
    }
  }

  template<typename T>
  inline T my_j_pow_x_template(const boost::uint_fast32_t j, const T& x, std::map<boost::uint_fast32_t, T>& n_pow_x_prime_factor_map)
  {
    using boost::multiprecision::exp;
    using boost::multiprecision::exp;
    using boost::multiprecision::pown;
    using boost::multiprecision::pown;
    using boost::multiprecision::real;
    using boost::multiprecision::real;

    std::deque<boost::multiprecision::utility::point<boost::uint_fast32_t> > pf;

    boost::multiprecision::prime_factors(j, pf);

    T jpx = boost::multiprecision::one();

    for(std::size_t i = static_cast<std::size_t>(0u); i < pf.size(); i++)
    {
      T pf_pow_x;

      const boost::uint_fast32_t n = pf[i].x;
      const boost::uint_fast32_t p = pf[i].y;

      const typename std::map<boost::uint_fast32_t, T>::const_iterator it = n_pow_x_prime_factor_map.find(n);

      if(it == n_pow_x_prime_factor_map.end())
      {
        // Compute n^x using exp[x * log(n)] and use the map data in the Zeta::logn(...).
        // Obtain the necessary integer logarithms from a table.
        if(boost::multiprecision::isint(x))
        {
          const mp_float rx = real(x);

          // Compute pure integer power for pure integer arguments.
          if((rx < boost::multiprecision::int64_max()) && (rx > boost::multiprecision::int64_min()))
          {
            pf_pow_x = pown(T(n), boost::multiprecision::to_int64(rx));
          }
          else
          {
            pf_pow_x = exp(x * ::my_logn(n));
          }
        }
        else
        {
          pf_pow_x = exp(x * ::my_logn(n));
        }

        n_pow_x_prime_factor_map[n] = pf_pow_x;
      }
      else
      {
        pf_pow_x = it->second;
      }

      // Do the power expansion.
      if     (p == static_cast<boost::uint_fast32_t>(1u)) { }
      else if(p == static_cast<boost::uint_fast32_t>(2u)) { pf_pow_x *=  pf_pow_x; }
      else if(p == static_cast<boost::uint_fast32_t>(3u)) { pf_pow_x *= (pf_pow_x * pf_pow_x); }
      else                                                { pf_pow_x *= pown(pf_pow_x, static_cast<boost::int64_t>(p - 1u)); }

      jpx *= pf_pow_x;
    }

    return jpx;
  }
}

mp_float   boost::multiprecision::utility::j_pow_x(const boost::uint_fast32_t j, const mp_float&   x, std::map<boost::uint_fast32_t, mp_float>&    n_pow_x_prime_factor_map) { return ::my_j_pow_x_template<mp_float>(j, x, n_pow_x_prime_factor_map); }
mp_complex boost::multiprecision::utility::j_pow_x(const boost::uint_fast32_t j, const mp_complex& x, std::map<boost::uint_fast32_t, mp_complex>& n_pow_x_prime_factor_map)  { return ::my_j_pow_x_template<mp_complex>(j, x, n_pow_x_prime_factor_map); }
