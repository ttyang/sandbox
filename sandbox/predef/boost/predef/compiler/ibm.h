/*
Copyright Redshift Software, Inc. 2008-2011
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_COMPILER_IBM_H
#define BOOST_PREDEF_COMPILER_IBM_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_CXX_IBM`]

[@http://en.wikipedia.org/wiki/VisualAge IBM XL C/C++] compiler.
Version number available as major, minor, and patch.
 */

#define BOOST_CXX_IBM BOOST_VERSION_NUMBER(0,0,0)

#if defined(__IBMCPP__) || defined(__xlC__) || defined(__xlc__)
    #undef BOOST_CXX_IBM
    #if defined(__COMPILER_VER__)
        #define BOOST_CXX_IBM BOOST_PREDEF_MAKE_F_FF_FFFF(__COMPILER_VER__)
    #elif defined(__xlC__)
        #define BOOST_CXX_IBM BOOST_PREDEF_MAKE_FF_FF(__xlC__)
    #elif defined(__xlc__)
        #define BOOST_CXX_IBM BOOST_PREDEF_MAKE_FF_FF(__xlc__)
    #else
        #define BOOST_CXX_IBM BOOST_PREDEF_MAKE_N_N_N(__IBMCPP__)
    #endif
#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_CXX_IBM,"IBM XL C/C++")

#endif
