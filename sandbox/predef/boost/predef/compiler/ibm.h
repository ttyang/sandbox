/*
Copyright Redshift Software, Inc. 2008-2010
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_COMPILER_IBM_H
#define BOOST_PREDEF_COMPILER_IBM_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

#define BOOST_CXX_IBM BOOST_VERSION_NUMBER(0,0,0)

#if defined(__IBMCPP__) || defined(__xlC__)
    #undef BOOST_CXX_IBM
    #if defined(__COMPILER_VER__)
        #define BOOST_CXX_IBM BOOST_PREDEF_MAKE_F_FF_FFFF(__COMPILER_VER__)
    #elif defined(__xlC__)
        #define BOOST_CXX_IBM BOOST_PREDEF_MAKE_FF_FF(__xlC__)
    #else
        #define BOOST_CXX_IBM BOOST_PREDEF_MAKE_N_N_N(__IBMCPP__)
    #endif
#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_CXX_IBM,"IBM")

#endif
