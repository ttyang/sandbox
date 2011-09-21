
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FUNCTION_BASE_2009_10_27_HPP_
  #define _UTIL_FUNCTION_BASE_2009_10_27_HPP_

  namespace boost
  {
    namespace multiprecision
    {
      namespace utility
      {
        template<typename T> class function_base
        {
        public:
          virtual ~function_base() { }

          T function(const T& x) const { return my_function(x); }

        protected:
          function_base() { }

        private:
          const function_base& operator=(const function_base&);
          function_base(const function_base&);

          virtual T my_function(const T&) const = 0;
        };
      }
    }
  }

#endif // _UTIL_FUNCTION_BASE_2009_10_27_HPP_
