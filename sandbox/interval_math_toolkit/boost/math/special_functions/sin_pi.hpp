//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SIN_PI_HPP
#define BOOST_MATH_SIN_PI_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cmath>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/real_cast.hpp>
#include <boost/math/constants/constants.hpp>

namespace boost{ namespace math{

template <class T>
T sin_pi(T x)
{
   BOOST_MATH_STD_USING // ADL of std names
   if(x < 0)
      return -sin_pi(static_cast<T>(-x));
   // sin of pi*x:
   bool invert;
   if(x < 0.5)
      return sin(constants::pi<T>() * x);
   if(x < 1)
   {
      invert = true;
      x = -x;
   }
   else
      invert = false;

   T rem = floor(x);
   if(tools::real_cast<int>(rem) & 1)
      invert = !invert;
   rem = x - rem;
   if(rem > 0.5f)
      rem = 1 - rem;
   if(rem == 0.5f)
      return static_cast<T>(invert ? -1 : 1);
   
   rem = sin(constants::pi<T>() * rem);
   return invert ? -rem : rem;
}

template <class T, class Policy>
inline T sin_pi(T x, const Policy&)
{
   return boost::math::sin_pi(x);
}

} // namespace math
} // namespace boost
#endif
