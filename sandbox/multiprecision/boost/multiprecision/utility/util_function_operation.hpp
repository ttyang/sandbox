
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FUNCTION_OPERATION_2009_10_27_HPP_
  #define _UTIL_FUNCTION_OPERATION_2009_10_27_HPP_

  #include <boost/multiprecision/utility/util_function_base.hpp>

  namespace boost
  {
    namespace multiprecision
    {
      namespace utility
      {
        template<typename T>
        class function_operation : public function_base<T>
        {
        protected:

          mutable bool op_ok;

        protected:

          function_operation() : op_ok(false) { }

        public:

          virtual ~function_operation() { }

          bool success(void) const { return op_ok; }
          T operation(void) const { return my_operation(); }

        protected:

          virtual T my_operation(void) const = 0;
        };
      }
    }
  }

#endif // _UTIL_FUNCTION_OPERATION_2009_10_27_HPP_
