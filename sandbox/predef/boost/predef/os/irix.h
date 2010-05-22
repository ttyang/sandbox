/*
Copyright Redshift Software, Inc. 2008-2010
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_COMPILER_IRIX_H
#define BOOST_PREDEF_COMPILER_IRIX_H

#include <boost/predef/version_number.h>
#include <boost/predef/detail/vrp.h>

#define BOOST_OS_IRIX BOOST_VERSION_NUMBER(0,0,0)

#if defined(sgi) || defined(__sgi)
    #undef BOOST_OS_IRIX
    #define BOOST_OS_IRIX BOOST_VERSION_NUMBER(0,0,1)
#endif

#endif
