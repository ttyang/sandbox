//  (C) Copyright John Maddock 2005-2006.
//
//  This code may be used under either of the following two licences:
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE. OF SUCH DAMAGE.
//
//  Or:
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_FPCLASSIFY_HPP
#define BOOST_MATH_FPCLASSIFY_HPP

#include <math.h>
#include <cmath>
#include <boost/limits.hpp>
#include <boost/math/tools/real_cast.hpp>
#include <boost/type_traits/is_floating_point.hpp>

#if defined(_MSC_VER) || defined(__BORLANDC__)
#include <float.h>
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::abs; using ::fabs; }
#endif

#ifndef FP_NORMAL

#define FP_ZERO        0
#define FP_NORMAL      1
#define FP_INFINITE    2
#define FP_NAN         3
#define FP_SUBNORMAL   4

#else

#define BOOST_HAS_FPCLASSIFY

#ifndef fpclassify
#  if (defined(__GLIBCPP__) || defined(__GLIBCXX__)) && defined(_GLIBCXX_USE_C99_MATH) && (!_GLIBCXX_USE_C99_FP_MACROS_DYNAMIC)
#     define BOOST_FPCLASSIFY_PREFIX ::std::
#  else
#     undef BOOST_HAS_FPCLASSIFY
#     define BOOST_FPCLASSIFY_PREFIX
#  endif
#elif defined(__HP_aCC)
// aCC appears to do "#define fpclassify fpclassify" which messes us up a bit!
#  define BOOST_FPCLASSIFY_PREFIX ::
#else
#  define BOOST_FPCLASSIFY_PREFIX
#endif

#endif

namespace boost{ namespace math{

#define BOOST_NO_MACRO_EXPAND /**/

#if defined(BOOST_HAS_FPCLASSIFY) || defined(isnan)
namespace detail{

template <class T>
inline bool is_nan_helper(T t, const boost::true_type&)
{
#ifdef BOOST_HAS_FPCLASSIFY
   if( BOOST_FPCLASSIFY_PREFIX fpclassify(t) == FP_NAN)
      return true;
#elif defined(isnan)
   if(isnan(t))
      return true;
#endif
   return false;
}

template <class T>
inline bool is_nan_helper(T t, const boost::false_type&)
{
   return false;
}
}
#endif

template <class T>
int fpclassify BOOST_NO_MACRO_EXPAND(T t)
{
   // whenever possible check for Nan's first:
#ifdef BOOST_HAS_FPCLASSIFY
   if(detail::is_nan_helper(t, ::boost::is_floating_point<T>()))
      return FP_NAN;
#elif defined(isnan)
   if(detail::is_nan_helper(t, ::boost::is_floating_point<T>()))
      return FP_NAN;
#elif defined(_MSC_VER) || defined(__BORLANDC__)
   if(::_isnan(boost::math::tools::real_cast<double>(t)))
      return FP_NAN;
#endif
   // std::fabs broken on a few systems especially for long long!!!!
   T at = (t < T(0)) ? -t : t; 

   // Use a process of exclusion to figure out
   // what kind of type we have, this relies on
   // IEEE conforming reals that will treat
   // Nan's as unordered.  Some compilers
   // don't do this once optimisations are
   // turned on, hence the check for nan's above.
   if(std::numeric_limits<T>::is_specialized == 0)
   {
      // so what do we do here?
      return at == 0 ? FP_ZERO : FP_NORMAL;
   }
   if(at <= (std::numeric_limits<T>::max)())
   {
      if(at >= (std::numeric_limits<T>::min)())
         return FP_NORMAL;
      return (at != 0) ? FP_SUBNORMAL : FP_ZERO;
   }
   else if(at > (std::numeric_limits<T>::max)())
      return FP_INFINITE;
   return FP_NAN;
}

#if defined(BOOST_HAS_FPCLASSIFY)
inline int fpclassify BOOST_NO_MACRO_EXPAND(float t)
{
   return BOOST_FPCLASSIFY_PREFIX fpclassify(t);
}
inline int fpclassify BOOST_NO_MACRO_EXPAND(double t)
{
   return BOOST_FPCLASSIFY_PREFIX fpclassify(t);
}
#if !defined(__CYGWIN__) && !defined(__HP_aCC) && !defined(BOOST_INTEL) && !defined(BOOST_NO_NATIVE_LONG_DOUBLE_FP_CLASSIFY)
// The native fpclassify broken for long doubles with aCC
// use portable one instead....
inline int fpclassify BOOST_NO_MACRO_EXPAND(long double t)
{
   return BOOST_FPCLASSIFY_PREFIX fpclassify(t);
}
#endif

#elif defined(_MSC_VER)
// This only works for type double, for both float 
// and long double it gives misleading answers.
int fpclassify BOOST_NO_MACRO_EXPAND(double t)
{
   switch(::_fpclass(t))
   {
   case _FPCLASS_SNAN /* Signaling NaN */ :
   case _FPCLASS_QNAN /* Quiet NaN */ :
      return FP_NAN;
   case _FPCLASS_NINF /*Negative infinity ( �INF) */ :
   case _FPCLASS_PINF /* Positive infinity (+INF) */ :
      return FP_INFINITE;
   case _FPCLASS_NN /* Negative normalized non-zero */ :
   case _FPCLASS_PN /* Positive normalized non-zero */ :
      return FP_NORMAL;
   case _FPCLASS_ND /* Negative denormalized */:
   case _FPCLASS_PD /* Positive denormalized */ :
      return FP_SUBNORMAL;
   case _FPCLASS_NZ /* Negative zero ( � 0) */ :
   case _FPCLASS_PZ /* Positive 0 (+0) */ :
      return FP_ZERO;
   default:
      /**/ ;
   }
   return FP_NAN;  // should never get here!!!
}
#endif

template <class T>
inline bool isfinite BOOST_NO_MACRO_EXPAND(T z)
{
   int t = (::boost::math::fpclassify)(z);
   return (t != FP_NAN) && (t != FP_INFINITE);
}

template <class T>
inline bool isinf BOOST_NO_MACRO_EXPAND(T t)
{
   return (::boost::math::fpclassify)(t) == FP_INFINITE;
}

template <class T>
inline bool isnan BOOST_NO_MACRO_EXPAND(T t)
{
   return (::boost::math::fpclassify)(t) == FP_NAN;
}

template <class T>
inline bool isnormal BOOST_NO_MACRO_EXPAND(T t)
{
   return (::boost::math::fpclassify)(t) == FP_NORMAL;
}

} } // namespaces

#endif // BOOST_MATH_FPCLASSIFY_HPP


