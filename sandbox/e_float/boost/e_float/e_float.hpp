
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_HPP_
  #define _E_FLOAT_HPP_

  // Select the e_float back-end big-number type
  // by defining E_FLOAT_TYPE_xxx, for example,
  // as a compiler defined preprocessor macro.

  #if defined(E_FLOAT_TYPE_EFX)
    #include <e_float/e_float_efx.hpp>
  #elif defined(E_FLOAT_TYPE_GMP)
    #include <e_float/e_float_gmp.hpp>
  #elif defined(E_FLOAT_TYPE_MPFR)
    #include <e_float/e_float_mpfr.hpp>
  #else
    #error e_float type undefined!
  #endif

  #include <e_float/e_float_global_math.hpp>
  #include <e_float/e_float_limits.hpp>

#endif // _E_FLOAT_HPP_
