
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} � ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FIND_ROOT_BASE_2009_10_31_H_
  #define _UTIL_FIND_ROOT_BASE_2009_10_31_H_

  #include "util_ranged_function_operation.h"

  namespace Util
  {
    template<typename T> class FindRootBase : public RangedFunctionOperation<T>
    {
    protected:
    
      FindRootBase(const T& lo,
                   const T& hi,
                   const T& tol) : RangedFunctionOperation<T>(lo, hi, tol) { }

    public:

      virtual ~FindRootBase() { }
    };
  }

#endif // _UTIL_FIND_ROOT_BASE_2009_10_31_H_