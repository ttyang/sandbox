
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float.hpp>
#include <boost/lexical_cast.hpp>

using boost::multiprecision::mp_float;

const mp_float& boost::multiprecision::value_nan(void) { static const mp_float val = mp_float().my_value_nan(); return val; }
const mp_float& boost::multiprecision::value_inf(void) { static const mp_float val = mp_float().my_value_inf(); return val; }
const mp_float& boost::multiprecision::value_max(void) { static const mp_float val = mp_float().my_value_max(); return val; }
const mp_float& boost::multiprecision::value_min(void) { static const mp_float val = mp_float().my_value_min(); return val; }

const mp_float& boost::multiprecision::value_eps(void)
{
  static const mp_float val("1E-" + boost::lexical_cast<std::string>(std::numeric_limits<mp_float>::digits10 - 1));
  return val;
}

const mp_float& boost::multiprecision::zero(void) { static const mp_float val(0u);    return val; }
const mp_float& boost::multiprecision::one (void) { static const mp_float val(1u);    return val; }
const mp_float& boost::multiprecision::half(void) { static const mp_float val("0.5"); return val; }
