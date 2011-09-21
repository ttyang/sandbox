
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FIND_ROOT_BASE_2009_10_31_HPP_
  #define _UTIL_FIND_ROOT_BASE_2009_10_31_HPP_

  #include "util_ranged_function_operation.hpp"

  namespace boost
  {
    namespace multiprecision
    {
      namespace utility
      {
        template<typename T> class find_root_base : public ranged_function_operation<T>
        {
        protected:
    
          find_root_base(const T& lo,
                       const T& hi,
                       const T& tol) : ranged_function_operation<T>(lo, hi, tol) { }

        public:

          virtual ~find_root_base() { }
        };
      }
    }
  }

#endif // _UTIL_FIND_ROOT_BASE_2009_10_31_HPP_
