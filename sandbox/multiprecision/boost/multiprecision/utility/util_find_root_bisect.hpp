
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FIND_ROOT_BISECT_2009_10_31_HPP_
  #define _UTIL_FIND_ROOT_BISECT_2009_10_31_HPP_

  #include <boost/cstdint.hpp>
  #include <boost/multiprecision/mp_float.hpp>
  #include <utility/util_find_root_base.h>

  namespace boost
  {
    namespace multiprecision
    {
      namespace utility
      {
        template<typename T>
        class find_root_bisect : public find_root_base<T>
        {
        public:
          virtual ~find_root_bisect() { }

        protected:
          find_root_bisect(const T& lo,
                           const T& hi,
                           const T& tol) : find_root_base<T>(lo, hi, tol) { }

        private:
          // Set a maximum of 2048 iterations.
          static const boost::int_fast32_t my_max_iteration = static_cast<boost::int_fast32_t>(2048);

          virtual T my_operation(void) const
          {
            // Bisection method as described in Numerical Recipes in C++ 2nd Ed., chapter 9.1.
            // This template implementation was inspired by the program on page 358.

            function_operation<T>::op_ok = true;

            T lo = ranged_function_operation<T>::xlo;
            T hi = ranged_function_operation<T>::xhi;

            const T f = function(lo);

            static const T t_zero = T(0);

            // Make sure that there is at least one root in the interval.
            if(f * function(ranged_function_operation<T>::xhi) >= t_zero)
            {
              return t_zero;
            }

            // Orient the search such that f > 0 lies at x + dx.
            T dx;
            T rt;

            if(f < t_zero)
            {
              dx = hi - lo;
              rt = lo;
            }
            else
            {
              dx = lo - hi;
              rt = hi;
            }

            // Bisection iteration loop, maximum my_max_iteration times.
            boost::int_fast32_t i;
            for(i = static_cast<boost::int_fast32_t>(0); i < my_max_iteration; i++)
            {
              dx /= static_cast<boost::int32_t>(2);

              const T x_mid = rt + dx;
              const T f_mid = function(x_mid);

              if(f_mid <= t_zero)
              {
                rt = x_mid;
              }

              // Check for convergence to within a tolerance.
              const T dx_abs = ((dx < t_zero) ? -dx : dx);

              const bool f_mid_is_zero = (f_mid == T(0));

              if(dx_abs < ranged_function_operation<T>::eps || f_mid_is_zero)
              {
                // Break and return root.
                break;
              }
            }

            const bool bo_did_not_converge = (i == my_max_iteration);

            if(bo_did_not_converge)
            {
              // Bisection iteration did not converge.
              function_operation<T>::op_ok = false;
              return t_zero;
            }
            else
            {
              return rt;
            }
          }
        };
      }
    }
  }

#endif // _UTIL_FIND_ROOT_BISECT_2009_10_31_HPP_
