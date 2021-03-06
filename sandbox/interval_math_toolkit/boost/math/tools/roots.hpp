//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_NEWTON_SOLVER_HPP
#define BOOST_MATH_TOOLS_NEWTON_SOLVER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <utility>
#include <cmath>
#include <stdexcept>

#include <boost/tr1/tuple.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4512)
#endif
#include <boost/tr1/tuple.hpp>
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/math/special_functions/sign.hpp>
#include <boost/math/tools/toms748_solve.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{ namespace math{ namespace tools{

namespace detail{

template <class F, class T>
void handle_zero_derivative(F f,
                            T& last_f0,
                            const T& f0,
                            T& delta,
                            T& result,
                            T& guess,
                            const T& vmin,
                            const T& vmax)
{
   if(last_f0 == 0)
   {
      // this must be the first iteration, pretend that we had a
      // previous one at either vmin or vmax:
      if(result == vmin)
      {
         guess = vmax;
      }
      else
      {
         guess = vmin;
      }
      last_f0 = std::tr1::get<0>(f(guess));
      delta = guess - result;
   }
   if(sign(last_f0) * sign(f0) < 0)
   {
      // we've crossed over so move in opposite direction to last step:
      if(delta < 0)
      {
         delta = (result - vmin) / 2;
      }
      else
      {
         delta = (result - vmax) / 2;
      }
   }
   else
   {
      // move in same direction as last step:
      if(delta < 0)
      {
         delta = (result - vmax) / 2;
      }
      else
      {
         delta = (result - vmin) / 2;
      }
   }
}

} // namespace

template <class F, class T, class Tol, class Policy>
std::pair<T, T> bisect(F f, T vmin, T vmax, Tol tol, boost::uintmax_t& max_iter, const Policy& pol)
{
   T fmin = f(vmin);
   T fmax = f(vmax);
   if(fmin == 0)
      return std::make_pair(vmin, vmin);
   if(fmax == 0)
      return std::make_pair(vmax, vmax);

   //
   // Error checking:
   //
   static const char* function = "boost::math::tools::bisect<%1%>";
   if(vmin >= vmax)
   {
      policies::raise_evaluation_error(function, 
         "Arguments in wrong order in boost::math::tools::bisect (first arg=%1%)", vmin, pol);
   }
   if(fmin * fmax >= 0)
   {
      policies::raise_evaluation_error(function, 
         "No change of sign in boost::math::tools::bisect, either there is no root to find, or there are multiple roots in the interval (f(vmin) = %1%).", fmin, pol);
   }

   //
   // Three function invocations so far:
   //
   boost::uintmax_t count = max_iter;
   if(count < 3)
      count = 0;
   else
      count -= 3;

   while(count && (0 == tol(vmin, vmax)))
   {
      T mid = (vmin + vmax) / 2;
      T fmid = f(mid);
      if((mid == vmax) || (mid == vmin))
         break;
      if(fmid == 0)
      {
         vmin = vmax = mid;
         break;
      }
      else if(sign(fmid) * sign(fmin) < 0)
      {
         vmax = mid;
         fmax = fmid;
      }
      else
      {
         vmin = mid;
         fmin = fmid;
      }
      --count;
   }

   max_iter -= count;

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Bisection iteration, final count = " << max_iter << std::endl;

   static boost::uintmax_t max_count = 0;
   if(max_iter > max_count)
   {
      max_count = max_iter;
      std::cout << "Maximum iterations: " << max_iter << std::endl;
   }
#endif

   return std::make_pair(vmin, vmax);
}

template <class F, class T, class Tol>
inline std::pair<T, T> bisect(F f, T vmin, T vmax, Tol tol, boost::uintmax_t& max_iter)
{
   return bisect(f, vmin, vmax, tol, max_iter, policies::policy<>());
}

template <class F, class T, class Tol>
inline std::pair<T, T> bisect(F f, T vmin, T vmax, Tol tol)
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
   return bisect(f, vmin, vmax, tol, m, policies::policy<>());
}

template <class F, class T>
T newton_raphson_iterate(F f, T guess, T vmin, T vmax, int digits, boost::uintmax_t& max_iter)
{
   BOOST_MATH_STD_USING

   T f0(0), f1, last_f0(0);
   T result = guess;

   T factor = static_cast<T>(ldexp(1.0, 1 - digits));
   T delta = 1;
   T delta1 = tools::max_value<T>();
   T delta2 = tools::max_value<T>();

   boost::uintmax_t count(max_iter);

   do{
      last_f0 = f0;
      delta2 = delta1;
      delta1 = delta;
      std::tr1::tie(f0, f1) = f(result);
      if(0 == f0)
         break;
      if(f1 == 0)
      {
         // Oops zero derivative!!!
#ifdef BOOST_MATH_INSTRUMENT
         std::cout << "Newton iteration, zero derivative found" << std::endl;
#endif
         detail::handle_zero_derivative(f, last_f0, f0, delta, result, guess, vmin, vmax);
      }
      else
      {
         delta = f0 / f1;
      }
#ifdef BOOST_MATH_INSTRUMENT
      std::cout << "Newton iteration, delta = " << delta << std::endl;
#endif
      if(fabs(delta * 2) > fabs(delta2))
      {
         // last two steps haven't converged, try bisection:
         delta = (delta > 0) ? (result - vmin) / 2 : (result - vmax) / 2;
      }
      guess = result;
      result -= delta;
      if(result <= vmin)
      {
         delta = 0.5F * (guess - vmin);
         result = guess - delta;
         if((result == vmin) || (result == vmax))
            break;
      }
      else if(result >= vmax)
      {
         delta = 0.5F * (guess - vmax);
         result = guess - delta;
         if((result == vmin) || (result == vmax))
            break;
      }
      // update brackets:
      if(delta > 0)
         vmax = guess;
      else
         vmin = guess;
   }while(--count && (fabs(result * factor) < fabs(delta)));

   max_iter -= count;

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Newton Raphson iteration, final count = " << max_iter << std::endl;

   static boost::uintmax_t max_count = 0;
   if(max_iter > max_count)
   {
      max_count = max_iter;
      std::cout << "Maximum iterations: " << max_iter << std::endl;
   }
#endif

   return result;
}

template <class F, class T>
inline T newton_raphson_iterate(F f, T guess, T vmin, T vmax, int digits)
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
   return newton_raphson_iterate(f, guess, vmin, vmax, digits, m);
}

template <class F, class T>
T halley_iterate(F f, T guess, T vmin, T vmax, int digits, boost::uintmax_t& max_iter)
{
   BOOST_MATH_STD_USING
   using std::max;

   T f0(0), f1, f2;
   T result = guess;

   T factor = static_cast<T>(ldexp(1.0, 1 - digits));
   T delta = max BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<T>(10000000 * guess), T(10000000));  // arbitarily large delta
   T last_f0 = 0;
   T delta1 = delta;
   T delta2 = delta;

   bool out_of_bounds_sentry = false;

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Halley iteration, limit = " << factor << std::endl;
#endif

   boost::uintmax_t count(max_iter);

   do{
      last_f0 = f0;
      delta2 = delta1;
      delta1 = delta;
      std::tr1::tie(f0, f1, f2) = f(result);
      if(0 == f0)
         break;
      if((f1 == 0) && (f2 == 0))
      {
         // Oops zero derivative!!!
#ifdef BOOST_MATH_INSTRUMENT
         std::cout << "Halley iteration, zero derivative found" << std::endl;
#endif
         detail::handle_zero_derivative(f, last_f0, f0, delta, result, guess, vmin, vmax);
      }
      else
      {
         if(f2 != 0)
         {
            T denom = 2 * f0;
            T num = 2 * f1 - f0 * (f2 / f1);
            if((fabs(num) < 1) && (fabs(denom) >= fabs(num) * tools::max_value<T>()))
            {
               // possible overflow, use Newton step:
               delta = f0 / f1;
            }
            else
               delta = denom / num;
            if(delta * f1 / f0 < 0)
            {
               // probably cancellation error, try a Newton step instead:
               delta = f0 / f1;
            }
         }
         else
            delta = f0 / f1;
      }
#ifdef BOOST_MATH_INSTRUMENT
      std::cout << "Halley iteration, delta = " << delta << std::endl;
#endif
      T convergence = fabs(delta / delta2);
      if((convergence > 0.8) && (convergence < 2))
      {
         // last two steps haven't converged, try bisection:
         delta = (delta > 0) ? (result - vmin) / 2 : (result - vmax) / 2;
         // reset delta2 so that this branch will *not* be taken on the
         // next iteration:
         delta2 = delta * 3;
      }
      guess = result;
      result -= delta;

      // check for out of bounds step:
      if(result < vmin)
      {
         T diff = ((fabs(vmin) < 1) && (fabs(result) > 1) && (tools::max_value<T>() / fabs(result) < fabs(vmin))) ? static_cast<T>(1000)  : static_cast<T>(result / vmin);
         if(fabs(diff) < 1)
            diff = 1 / diff;
         if(!out_of_bounds_sentry && (diff > 0) && (diff < 3))
         {
            // Only a small out of bounds step, lets assume that the result
            // is probably approximately at vmin:
            delta = 0.99f * (guess  - vmin);
            result = guess - delta;
            out_of_bounds_sentry = true; // only take this branch once!
         }
         else
         {
            delta = (guess - vmin) / 2;
            result = guess - delta;
            if((result == vmin) || (result == vmax))
               break;
         }
      }
      else if(result > vmax)
      {
         T diff = ((fabs(vmax) < 1) && (fabs(result) > 1) && (tools::max_value<T>() / fabs(result) < fabs(vmax))) ? static_cast<T>(1000)  : static_cast<T>(result / vmax);
         if(fabs(diff) < 1)
            diff = 1 / diff;
         if(!out_of_bounds_sentry && (diff > 0) && (diff < 3))
         {
            // Only a small out of bounds step, lets assume that the result
            // is probably approximately at vmin:
            delta = 0.99f * (guess  - vmax);
            result = guess - delta;
            out_of_bounds_sentry = true; // only take this branch once!
         }
         else
         {
            delta = (guess - vmax) / 2;
            result = guess - delta;
            if((result == vmin) || (result == vmax))
               break;
         }
      }
      // update brackets:
      if(delta > 0)
         vmax = guess;
      else
         vmin = guess;
   }while(--count && (fabs(result * factor) < fabs(delta)));

   max_iter -= count;

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Halley iteration, final count = " << max_iter << std::endl;

   static boost::uintmax_t max_count = 0;
   if(max_iter > max_count)
   {
      max_count = max_iter;
      std::cout << "Maximum iterations: " << max_iter << std::endl;
   }
#endif

   return result;
}

template <class F, class T>
inline T halley_iterate(F f, T guess, T vmin, T vmax, int digits)
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
   return halley_iterate(f, guess, vmin, vmax, digits, m);
}

template <class F, class T>
T schroeder_iterate(F f, T guess, T vmin, T vmax, int digits, boost::uintmax_t& max_iter)
{
   BOOST_MATH_STD_USING

   T f0(0), f1, f2, last_f0(0);
   T result = guess;

   T factor = static_cast<T>(ldexp(1.0, 1 - digits));
   T delta = 0;
   T delta1 = tools::max_value<T>();
   T delta2 = tools::max_value<T>();

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Schroeder iteration, limit = " << factor << std::endl;
#endif

   boost::uintmax_t count(max_iter);

   do{
      last_f0 = f0;
      delta2 = delta1;
      delta1 = delta;
      std::tr1::tie(f0, f1, f2) = f(result);
      if(0 == f0)
         break;
      if((f1 == 0) && (f2 == 0))
      {
         // Oops zero derivative!!!
#ifdef BOOST_MATH_INSTRUMENT
         std::cout << "Halley iteration, zero derivative found" << std::endl;
#endif
         detail::handle_zero_derivative(f, last_f0, f0, delta, result, guess, vmin, vmax);
      }
      else
      {
         T ratio = f0 / f1;
         if(ratio / result < 0.1)
         {
            delta = ratio + (f2 / (2 * f1)) * ratio * ratio;
            // check second derivative doesn't over compensate:
            if(delta * ratio < 0)
               delta = ratio;
         }
         else
            delta = ratio;  // fall back to Newton iteration.
      }
      if(fabs(delta * 2) > fabs(delta2))
      {
         // last two steps haven't converged, try bisection:
         delta = (delta > 0) ? (result - vmin) / 2 : (result - vmax) / 2;
      }
      guess = result;
      result -= delta;
#ifdef BOOST_MATH_INSTRUMENT
      std::cout << "Halley iteration, delta = " << delta << std::endl;
#endif
      if(result <= vmin)
      {
         delta = 0.5F * (guess - vmin);
         result = guess - delta;
         if((result == vmin) || (result == vmax))
            break;
      }
      else if(result >= vmax)
      {
         delta = 0.5F * (guess - vmax);
         result = guess - delta;
         if((result == vmin) || (result == vmax))
            break;
      }
      // update brackets:
      if(delta > 0)
         vmax = guess;
      else
         vmin = guess;
   }while(--count && (fabs(result * factor) < fabs(delta)));

   max_iter -= count;

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Schroeder iteration, final count = " << max_iter << std::endl;

   static boost::uintmax_t max_count = 0;
   if(max_iter > max_count)
   {
      max_count = max_iter;
      std::cout << "Maximum iterations: " << max_iter << std::endl;
   }
#endif

   return result;
}

template <class F, class T>
inline T schroeder_iterate(F f, T guess, T vmin, T vmax, int digits)
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
   return schroeder_iterate(f, guess, vmin, vmax, digits, m);
}

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_NEWTON_SOLVER_HPP



