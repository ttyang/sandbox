
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} � ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FIND_ROOT_BISECT_2009_10_31_H_
  #define _UTIL_FIND_ROOT_BISECT_2009_10_31_H_

  #include <utility/util_find_root_base.h>
  #include <e_float/e_float.hpp>

  namespace Util
  {
    template<typename T> class FindRootBisect : public FindRootBase<T>
    {
    protected:
    
      FindRootBisect(const T& lo,
                     const T& hi,
                     const T& tol) : FindRootBase<T>(lo, hi, tol) { }

    public:

      virtual ~FindRootBisect() { }

    private:

      virtual T my_operation(void) const
      {
        // Bisection method as described in Numerical Recipes in C++ 2nd Ed., chapter 9.1.
        // The program on page 358 was taken directly from the book and slightly modified
        // to improve adherence with standard C++ coding practices.

        FunctionOperation<T>::op_ok = true;

        T lo = RangedFunctionOperation<T>::xlo;
        T hi = RangedFunctionOperation<T>::xhi;

        const T f = function(lo);

        static const T t_zero = T(0);

        // Make sure that there is at least one root in the interval.
        if(f * function(RangedFunctionOperation<T>::xhi) >= t_zero)
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
        for(UINT32 i = static_cast<UINT32>(0u); i < static_cast<UINT32>(2048u); i++)
        {
          dx /= static_cast<INT32>(2);

          const T x_mid = rt + dx;
          const T f_mid = function(x_mid);

          if(f_mid <= t_zero)
          {
            rt = x_mid;
          }

          // Check for convergence to within a tolerance.
          const T dx_abs = ((dx < t_zero) ? -dx : dx);

          if(dx_abs < RangedFunctionOperation<T>::eps || ef::iszero(f_mid))
          {
            // Return root.
            return rt;
          }
        }

        // Bisection iteration did not converge.
        FunctionOperation<T>::op_ok = false;

        return t_zero;
      }
    };
  }

#endif // _UTIL_FIND_ROOT_BISECT_2009_10_31_H_
