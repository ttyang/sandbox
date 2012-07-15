/*
Copyright Redshift Software, Inc. 2008-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_OS_AMIGAOS_H
#define BOOST_PREDEF_OS_AMIGAOS_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_OS_AMIGAOS`]

[@http://en.wikipedia.org/wiki/AmigaOS AmigaOS] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_OS_AMIGAOS BOOST_VERSION_NUMBER(0,0,0)

#if defined(AMIGA) || defined(__amigaos__)
#   undef BOOST_OS_AMIGAOS
#   define BOOST_OS_AMIGAOS BOOST_VERSION_NUMBER(0,0,1)
#endif

#define BOOST_OS_AMIGAOS_NAME "AmigaOS"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_OS_AMIGAOS,BOOST_OS_AMIGAOS_NAME)


#endif
