
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FIND_ROOT_BISECT_2009_10_31_HPP_
  #define _UTIL_FIND_ROOT_BISECT_2009_10_31_HPP_

  #include <utility/util_find_root_base.h>
  #include <boost/multiprecision/mp_float.hpp>

  namespace boost
  {
    namespace multiprecision
    {
      namespace utility
      {
        template<typename T> class find_root_bisect : public find_root_base<T>
        {
        protected:
    
          find_root_bisect(const T& lo,
                         const T& hi,
                         const T& tol) : find_root_base<T>(lo, hi, tol) { }

        public:

          virtual ~find_root_bisect() { }

        private:

          virtual T my_operation(void) const
          {
            // Bisection method as described in Numerical Recipes in C++ 2nd Ed., chapter 9.1.
            // The program on page 358 was taken directly from the book and slightly modified
            // to improve adherence with standard C++ coding practices.

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

            // Bisection iteration loop, maximum 2048 times.
            for(boost::uint32_t i = static_cast<boost::uint32_t>(0u); i < static_cast<boost::uint32_t>(2048u); i++)
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

              if(dx_abs < ranged_function_operation<T>::eps || boost::multiprecision::iszero(f_mid))
              {
                // Return root.
                return rt;
              }
            }

            // Bisection iteration did not converge.
            function_operation<T>::op_ok = false;

            return t_zero;
          }
        };
      }
    }
  }

#endif // _UTIL_FIND_ROOT_BISECT_2009_10_31_HPP_
