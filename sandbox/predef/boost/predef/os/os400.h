/*
Copyright Redshift Software Inc 2011
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_OS_OS400_H
#define BOOST_PREDEF_OS_OS400_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_OS_OS400`]

[@http://en.wikipedia.org/wiki/IBM_i IBM OS/400] operating system.
 */

#define BOOST_OS_OS400 BOOST_VERSION_NUMBER(0,0,0)

#if defined(__OS400__)
    #undef BOOST_OS_OS400
    #define BOOST_OS_OS400 BOOST_VERSION_NUMBER(0,0,1)
#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_OS_OS400,"IBM OS/400")

#endif
