
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} � ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _TABLES_2008_01_10_H_
  #define _TABLES_2008_01_10_H_

  #include <vector>

  #include <e_float/e_float.hpp>

  namespace Tables
  {
    typedef const e_float&              (*pfn_efloat)       (void);
    typedef const std::vector<e_float>& (*pfn_vector_efloat)(void);

    const std::vector<pfn_efloat>&        A000142(void);
    const std::vector<pfn_efloat>&        A000367(void);
    const std::vector<pfn_efloat>&        A002445(void);
    const std::vector<pfn_efloat>&        A006882(void);
    const std::vector<pfn_vector_efloat>& A007318(void);
  }

#endif // _TABLES_2008_01_10_H_
