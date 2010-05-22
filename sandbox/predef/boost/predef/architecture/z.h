/*
Copyright Redshift Software, Inc. 2008-2010
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_ARCHITECTURE_Z_H
#define BOOST_PREDEF_ARCHITECTURE_Z_H

#include <boost/predef/version_number.h>
#include <boost/predef/detail/vrp.h>

#define BOOST_ARCHITECTURE_Z BOOST_VERSION_NUMBER(0,0,0)

#if defined(__SYSC_ZARCH__)
    #undef BOOST_ARCHITECTURE_Z
    #define BOOST_ARCHITECTURE_Z BOOST_VERSION_NUMBER(0,0,1)
#endif

#endif
