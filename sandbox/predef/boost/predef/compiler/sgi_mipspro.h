/*
Copyright Redshift Software, Inc. 2008-2010
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_COMPILER_SGI_MIPSPRO_H
#define BOOST_PREDEF_COMPILER_SGI_MIPSPRO_H

#include <boost/predef/version_number.h>
#include <boost/predef/detail/vrp.h>

#define BOOST_CXX_SGI BOOST_VERSION_NUMBER(0,0,0)

#if defined(__sgi)
    #undef BOOST_CXX_SGI
    #if defined(_SGI_COMPILER_VERSION)
        #define BOOST_CXX_SGI BOOST_PREDEF_VRP_N_N_N(_SGI_COMPILER_VERSION)
    #else
        #define BOOST_CXX_SGI BOOST_PREDEF_VRP_N_N_N(_COMPILER_VERSION)
    #endif
#endif

#endif
