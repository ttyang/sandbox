/*
Copyright Redshift Software, Inc. 2008-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_OS_AIX_H
#define BOOST_PREDEF_OS_AIX_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_OS_AIX`]

[@http://en.wikipedia.org/wiki/AIX_operating_system IBM AIX] operating system.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_OS_AIX BOOST_VERSION_NUMBER(0,0,0)

#if defined(_AIX) || defined(__TOS_AIX__)
#   undef BOOST_OS_AIX
#   if defined(_AIX43)
#       define BOOST_OS_AIX BOOST_VERSION_NUMBER(4,3,0)
#   elif defined(_AIX41)
#       define BOOST_OS_AIX BOOST_VERSION_NUMBER(4,1,0)
#   elif defined(_AIX32)
#       define BOOST_OS_AIX BOOST_VERSION_NUMBER(3,2,0)
#   elif defined(_AIX3)
#       define BOOST_OS_AIX BOOST_VERSION_NUMBER(3,0,0)
#   else
#       define BOOST_OS_AIX BOOST_VERSION_NUMBER(0,0,1)
#   endif
#endif

#define BOOST_OS_AIX_NAME "IBM AIX"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_OS_AIX,BOOST_OS_AIX_NAME)


#endif
