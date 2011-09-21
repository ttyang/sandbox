
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float_functions.hpp>
#include "gamma_util.h"

using boost::multiprecision::mp_float;

void GammaUtil::GammaOfPlusXMinusX(const mp_float& x, mp_float& gamma_plus_x, mp_float& gamma_minus_x)
{
  // Calculate gamma(x) and gamma(-x) without regard for the actual sign of x.
  // In other words, calculate gamma(abs(x)) and set the results appropriately
  // using the reflection formula.
  const bool    bo_x_isneg    =  boost::multiprecision::isneg(x);
  const mp_float abs_x         =  boost::multiprecision::fabs(x);
  const mp_float gamma_x_pos   =  boost::multiprecision::gamma(abs_x);
  const mp_float gamma_x_neg   = -boost::multiprecision::pi() / ((abs_x * gamma_x_pos) * boost::multiprecision::sin(boost::multiprecision::pi() * abs_x));

  gamma_plus_x  =  bo_x_isneg ? gamma_x_neg : gamma_x_pos;
  gamma_minus_x =  bo_x_isneg ? gamma_x_pos : gamma_x_neg;
}
