
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_TYPES_HPP_
  #define _E_FLOAT_TYPES_HPP_

  #if !defined(_MSC_VER) && !defined(__INTEL_COMPILER) && !defined(__GNUC__)
    #error "Compiler not supported: Types can not be determined"
  #endif

  #if defined(_MSC_VER) || defined(__INTEL_COMPILER)
  
    typedef   signed __int64  INT64;
    typedef unsigned __int64 UINT64;

  #elif defined(__GNUC__)

    typedef   signed long long  INT64;
    typedef unsigned long long UINT64;

  #endif

  typedef   signed int    INT32;
  typedef unsigned int   UINT32;

#endif // _E_FLOAT_TYPES_HPP_
