
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_RANGED_FUNCTION_OPERATION_2009_10_27_HPP_
  #define _UTIL_RANGED_FUNCTION_OPERATION_2009_10_27_HPP_

  #include "util_function_operation.hpp"

  namespace boost
  {
    namespace multiprecision
    {
      namespace utility
      {
        template<typename T> class ranged_function_operation : public function_operation<T>
        {
        public:
          virtual ~ranged_function_operation() { }

        protected:
          const T xlo;
          const T xhi;
          const T eps;

          ranged_function_operation(const T& lo,
                                  const T& hi,
                                  const T& tol) : xlo(lo),
                                                  xhi(hi),
                                                  eps(tol) { }
        };
      }
    }
  }

#endif // _UTIL_RANGED_FUNCTION_OPERATION_2009_10_27_HPP_
