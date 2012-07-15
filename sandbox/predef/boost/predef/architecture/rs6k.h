/*
Copyright Redshift Software, Inc. 2008-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_ARCHITECTURE_RS6K_H
#define BOOST_PREDEF_ARCHITECTURE_RS6K_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_ARCH_RS6000`]

[@http://en.wikipedia.org/wiki/RS/6000 RS/6000] architecture.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_ARCH_RS6000 BOOST_VERSION_NUMBER(0,0,0)

#if defined(__THW_RS6000) || defined(_IBMR2) || \
    defined(_POWER) || defined(_ARCH_PWR) || \
    defined(_ARCH_PWR2)
#   undef BOOST_ARCH_RS6000
#   define BOOST_ARCH_RS6000 BOOST_VERSION_NUMBER(0,0,1)
#endif

#define BOOST_ARCH_PWR BOOST_ARCH_RS6000

#define BOOST_ARCH_RS6000_NAME "RS/6000"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_ARCH_RS6000,BOOST_ARCH_RS6000_NAME)


#endif
