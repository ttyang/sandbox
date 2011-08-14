
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <deque>

#include <boost/e_float/e_float_complex.hpp>
#include <boost/e_float/e_float_prime.hpp>
#include <boost/e_float/e_float_constants.hpp>
#include <boost/e_float/e_float_elementary.hpp>

#include "../functions/integer/prime_factors.h"
#include "util_point.h"
#include "util_power_j_pow_x.h"

namespace Util
{
  static e_float logn(const UINT32 n)
  {
    static std::map<UINT32, e_float> ln_data;

    const std::map<UINT32, e_float>::const_iterator it = ln_data.find(n);

    if(it == ln_data.end())
    {
      const e_float ln = ef::log(e_float(n));

      ln_data[n] = ln;

      return ln;
    }
    else
    {
      return it->second;
    }
  }

  template<typename T> inline T j_pow_x_template(const UINT32 j, const T& x, std::map<UINT32, T>& n_pow_x_prime_factor_map)
  {
    using ef::exp;
    using efz::exp;
    using ef::pown;
    using efz::pown;
    using ef::real;
    using efz::real;

    std::deque<Util::point<UINT32> > pf;

    ef::prime_factors(j, pf);

    T jpx = ef::one();

    for(std::size_t i = static_cast<std::size_t>(0u); i < pf.size(); i++)
    {
      T pf_pow_x;

      const UINT32 n = pf[i].x;
      const UINT32 p = pf[i].y;

      const typename std::map<UINT32, T>::const_iterator it = n_pow_x_prime_factor_map.find(n);

      if(it == n_pow_x_prime_factor_map.end())
      {
        // Compute n^x using exp[x * log(n)] and use the map data in the Zeta::logn(...).
        // Obtain the necessary integer logarithms from a table.
        if(ef::isint(x))
        {
          const e_float rx = real(x);

          // Compute pure integer power for pure integer arguments.
          if((rx < ef::int64_max()) && (rx > ef::int64_min()))
          {
            pf_pow_x = pown(T(n), ef::to_int64(rx));
          }
          else
          {
            pf_pow_x = exp(x * Util::logn(n));
          }
        }
        else
        {
          pf_pow_x = exp(x * Util::logn(n));
        }

        n_pow_x_prime_factor_map[n] = pf_pow_x;
      }
      else
      {
        pf_pow_x = it->second;
      }

      // Do the power expansion.
      if     (p == static_cast<UINT32>(1u)) { }
      else if(p == static_cast<UINT32>(2u)) { pf_pow_x *=  pf_pow_x; }
      else if(p == static_cast<UINT32>(3u)) { pf_pow_x *= (pf_pow_x * pf_pow_x); }
      else                                  { pf_pow_x *= pown(pf_pow_x, static_cast<INT64>(p - 1u)); }

      jpx *= pf_pow_x;
    }

    return jpx;
  }
}

e_float    Util::j_pow_x(const UINT32 j, const e_float&    x, std::map<UINT32, e_float>&    n_pow_x_prime_factor_map) { return Util::j_pow_x_template<e_float>   (j, x, n_pow_x_prime_factor_map); }
ef_complex Util::j_pow_x(const UINT32 j, const ef_complex& x, std::map<UINT32, ef_complex>& n_pow_x_prime_factor_map) { return Util::j_pow_x_template<ef_complex>(j, x, n_pow_x_prime_factor_map); }
