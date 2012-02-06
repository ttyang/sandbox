
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _UTIL_FIND_ROOT_NEWTON_RAPHSON_2009_10_27_H_
  #define _UTIL_FIND_ROOT_NEWTON_RAPHSON_2009_10_27_H_

  #include "util_find_root_base.h"

  namespace Util
  {
    template<typename T>
    class FindRootNewtonRaphson : public FindRootBase<T>
    {
    public:
      virtual ~FindRootNewtonRaphson() { }

      void function_derivative(const T& x, T& f, T& d) const { my_function_derivative(x, f, d); }

    protected:
      FindRootNewtonRaphson(const T& lo,
                            const T& hi,
                            const T& tol) : FindRootBase<T>(lo, hi, tol) { }

    private:
      virtual void my_function_derivative(const T& x, T& f, T& d) const = 0;

      virtual T my_operation(void) const
      {
        FunctionOperation<T>::op_ok = true;

        T x = (FindRootBase<T>::xlo + FindRootBase<T>::xhi) / static_cast<INT32>(2);

        for(INT32 j = static_cast<INT32>(0); j < static_cast<INT32>(256); j++)
        {
          T f, d;
          my_function_derivative(x, f, d);

          const T dx = f / d;

          x -= dx;

          if((FindRootBase<T>::xlo - x) * (x - FindRootBase<T>::xhi) < ef::zero())
          {
            FunctionOperation<T>::op_ok = false;
            break;
          }

          const T delta = ((dx < T(0)) ? -dx : dx);
          
          if(delta < FindRootBase<T>::eps)
          {
            break;
          }
        }

        return (FunctionOperation<T>::op_ok ? x : T(0));
      }
    };
  }

#endif // _UTIL_FIND_ROOT_NEWTON_RAPHSON_2009_10_27_H_
