
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_TRAPEZOID_2008_09_06_HPP_
  #define _UTIL_TRAPEZOID_2008_09_06_HPP_

  #include "util_ranged_function_operation.hpp"

  namespace boost
  {
    namespace multiprecision
    {
      namespace utility
      {
        template<typename T> class recursive_trapezoid_rule : public ranged_function_operation<T>
        {
        protected:

          recursive_trapezoid_rule(const T& lo, const T& hi, const T& tol) : ranged_function_operation<T>(lo, hi, tol) { }

        public:

          virtual ~recursive_trapezoid_rule() { }

        private:

          virtual T my_operation(void) const
          {
            boost::int32_t n = static_cast<boost::int32_t>(1);

            T a = ranged_function_operation<T>::xlo;
            T b = ranged_function_operation<T>::xhi;
            T h = (b - a) / T(n);
        
            static const T one  = T(1);
            static const T half = T(0.5);

            T I = (function_base<T>::function(a) + function_base<T>::function(b)) * (h * half);

            for(boost::int32_t k = static_cast<boost::int32_t>(0); k < static_cast<boost::int32_t>(31); k++)
            {
              h *= half;

              const T I0 = I;

              T sum(0);

              for(boost::int32_t j = static_cast<boost::int32_t>(1); j <= n; j++)
              {
                sum += function(a + (T((j * 2) - 1) * h));
              }

              I = (I0 * half) + (h * sum);

              const T ratio = I0 / I;
              const T delta = ((ratio > one) ? (ratio - one) : (one - ratio));

              if((k > static_cast<boost::int32_t>(2)) && delta < ranged_function_operation<T>::eps)
              {
                function_operation<T>::op_ok = true;
                break;
              }

              n = n * 2;
            }

            return I;
          }
        };
      }
    }
  }

#endif // _UTIL_TRAPEZOID_2008_09_06_HPP_
