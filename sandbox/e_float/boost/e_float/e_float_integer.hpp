
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_INTEGER_HPP_
  #define _E_FLOAT_INTEGER_HPP_

  #include <vector>

  #include <boost/e_float/e_float.hpp>

  namespace ef
  {
    e_float bernoulli      (const UINT32 n);
    void    bernoulli_table(std::vector<e_float>& bn, const UINT32 n);
  }

#endif // _E_FLOAT_INTEGER_HPP_
