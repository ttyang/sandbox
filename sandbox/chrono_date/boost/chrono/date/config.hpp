//  config.hpp
//
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_CONFIG_HPP
#define BOOST_CHRONO_DATE_CONFIG_HPP

#include <boost/chrono/config.hpp>

// 1 => days + ymd + leap
// 2 => days
// 3 => ymd + leap
// 4 => ydoy + leap
#ifndef BOOST_CHRONO_DATE_DATE_DESIGN
#define BOOST_CHRONO_DATE_DATE_DESIGN 3
#endif

// 1 => days +ymd +leap
// 2 => days
// 3 => ymd +leap
#ifndef BOOST_CHRONO_DATE_REL_DATE_DESIGN
#define BOOST_CHRONO_DATE_REL_DATE_DESIGN 3
#endif


//#define BOOST_CHRONO_DATE_DATE_DESIGN_BUG

#if ! defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS) || defined  BOOST_CHRONO_DATE_DOXYGEN_INVOKED
#define BOOST_CHRONO_EXPLICIT explicit
#else
#define BOOST_CHRONO_EXPLICIT
#endif

#if ! defined BOOST_NO_CXX11_CONSTEXPR && defined __clang__
#define BOOST_CHRONO_DATE_CONSTEXPR BOOST_CONSTEXPR
#else
#define BOOST_CHRONO_DATE_NO_CXX11_CONSTEXPR
#define BOOST_CHRONO_DATE_CONSTEXPR
#endif


#ifndef  BOOST_NO_CXX11_CONSTEXPR
#define BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(T, N, V) constexpr T N(V)
#define BOOST_CONSTEXPR_OR_EXTERN_CONST_DEF(T, N, V)

#else
#define BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(T, N, V) extern const T N
#define BOOST_CONSTEXPR_OR_EXTERN_CONST_DEF(T, N, V) const T N(V);
#endif


#endif  // header
