/*
Copyright Redshift Software, Inc. 2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_OS_BSD_BSDI_H
#define BOOST_PREDEF_OS_BSD_BSDI_H

/*`

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_OS_BSD_BSDI BOOST_VERSION_NUMBER(0,0,0)

#if defined(__bsdi__)
#   ifndef BOOST_OS_BSD
#       define BOOST_OS_BSD BOOST_VERSION_NUMBER(0,0,1)
#   endif
#   undef BOOST_OS_BSD_BSDI
#   define BOOST_OS_BSD_BSDI BOOST_VERSION_NUMBER(0,0,1)
#endif

#define BOOST_OS_BSD_BSDI_NAME "BSDi BSD/OS"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_OS_BSD_BSDI,BOOST_OS_BSD_BSDI_NAME)

#endif
