
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_GAMMA_HPP_
  #define _E_FLOAT_GAMMA_HPP_

  #include <boost/e_float/e_float_complex.hpp>

  namespace ef
  {
    e_float gamma               (const e_float& x);
    e_float gamma_near_n        (const INT32 n, const e_float& x);
    e_float factorial           (const UINT32 n);
    e_float factorial2          (const  INT32 n);
    e_float binomial            (const UINT32 n, const UINT32 k);
    e_float binomial            (const UINT32 n, const e_float& y);
    e_float binomial            (const e_float& x, const UINT32 k);
    e_float binomial            (const e_float& x, const e_float& y);
    e_float pochhammer          (const e_float& x, const UINT32 n);
    e_float pochhammer          (const e_float& x, const e_float& a);
  }

  namespace efz
  {
    ef_complex gamma           (const ef_complex& z);
    ef_complex pochhammer      (const ef_complex& z, const UINT32 n);
    ef_complex pochhammer      (const ef_complex& z, const ef_complex& a);
  }

#endif // _E_FLOAT_GAMMA_HPP_
