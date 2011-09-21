
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_POWER_J_POW_X_2009_01_25_HPP_
  #define _UTIL_POWER_J_POW_X_2009_01_25_HPP_

  #include <map>

  #include <boost/multiprecision/mp_float_functions.hpp>

  namespace boost
  {
    namespace multiprecision
    {
      namespace utility
      {
        boost::multiprecision::mp_float   j_pow_x(const boost::uint32_t j, const boost::multiprecision::mp_float&   x, std::map<boost::uint32_t, boost::multiprecision::mp_float>&   n_pow_x_prime_factor_map);
        boost::multiprecision::mp_complex j_pow_x(const boost::uint32_t j, const boost::multiprecision::mp_complex& x, std::map<boost::uint32_t, boost::multiprecision::mp_complex>& n_pow_x_prime_factor_map);
      }
    }
  }

#endif // _UTIL_POWER_J_POW_X_2009_01_25_HPP_
