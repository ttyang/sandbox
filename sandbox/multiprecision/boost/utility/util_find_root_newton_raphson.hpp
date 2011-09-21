
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FIND_ROOT_NEWTON_RAPHSON_2009_10_27_HPP_
  #define _UTIL_FIND_ROOT_NEWTON_RAPHSON_2009_10_27_HPP_

  #include "util_find_root_base.hpp"

  namespace boost
  {
    namespace multiprecision
    {
      namespace utility
      {
        template<typename T> class find_root_newton_raphson : public find_root_base<T>
        {
        protected:
    
          find_root_newton_raphson(const T& lo,
                                const T& hi,
                                const T& tol) : find_root_base<T>(lo, hi, tol) { }

        public:

          virtual ~find_root_newton_raphson() { }

        public:

          void function_derivative(const T& x, T& f, T& d) const { my_function_derivative(x, f, d); }

        private:

          virtual void my_function_derivative(const T& x, T& f, T& d) const = 0;

          virtual T my_operation(void) const
          {
            function_operation<T>::op_ok = true;

            T x = (find_root_base<T>::xlo + find_root_base<T>::xhi) / static_cast<boost::int32_t>(2);

            for(boost::int32_t j = static_cast<boost::int32_t>(0); j < static_cast<boost::int32_t>(256); j++)
            {
              T f, d;
              my_function_derivative(x, f, d);

              const T dx = f / d;

              x -= dx;

              if((find_root_base<T>::xlo - x) * (x - find_root_base<T>::xhi) < T(0))
              {
                function_operation<T>::op_ok = false;
                break;
              }

              const T delta = ((dx < T(0)) ? -dx : dx);

              if(delta < find_root_base<T>::eps)
              {
                break;
              }
            }

            return (function_operation<T>::op_ok ? x : T(0));
          }
        };
      }
    }
  }

#endif // _UTIL_FIND_ROOT_NEWTON_RAPHSON_2009_10_27_HPP_
