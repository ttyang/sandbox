
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} � ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_ZETA_HPP_
  #define _E_FLOAT_ZETA_HPP_

  #include <e_float/e_float.hpp>
  #include <e_float/e_float_complex.hpp>

  namespace ef
  {
    e_float riemann_zeta(const INT32 n);
    e_float riemann_zeta(const e_float& s);
  }

  namespace efz
  {
    ef_complex riemann_zeta(const ef_complex& s);
  }

#endif // _E_FLOAT_ZETA_HPP_