/*
Copyright Redshift Software, Inc. 2008-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_OS_BSD_H
#define BOOST_PREDEF_OS_BSD_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_OS_BSD`]

[@http://en.wikipedia.org/wiki/Berkeley_Software_Distribution BSD] operating system.

BSD has various branch operating systems possible and each detected
individually. This detects the following variations and sets a specific
version number macro to match:

* `BOOST_OS_BSD_DRAGONFLY` [@http://en.wikipedia.org/wiki/DragonFly_BSD DragonFly BSD]
* `BOOST_OS_BSD_FREE` [@http://en.wikipedia.org/wiki/Freebsd FreeBSD]
* `BOOST_OS_BSD_BSDI` [@http://en.wikipedia.org/wiki/BSD/OS BSDi BSD/OS]
* `BOOST_OS_BSD_NET` [@http://en.wikipedia.org/wiki/Netbsd NetBSD]
* `BOOST_OS_BSD_OPEN` [@http://en.wikipedia.org/wiki/Openbsd OpenBSD]

[note The general `BOOST_OS_BSD` is set in all cases to indicate some form
of BSD. If the above variants is detected the corresponding macro is also set.]

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_OS_BSD BOOST_VERSION_NUMBER(0,0,0)

#if defined(BSD) || \
    defined(_SYSTYPE_BSD)
#   undef BOOST_OS_BSD
#   include <sys/param.h>
#   if defined(BSD4_2)
#       define BOOST_OS_BSD BOOST_VERSION_NUMBER(4,2,0)
#   elif defined(BSD4_3)
#       define BOOST_OS_BSD BOOST_VERSION_NUMBER(4,3,0)
#   elif defined(BSD4_4)
#       define BOOST_OS_BSD BOOST_VERSION_NUMBER(4,4,0)
#   elif defined(BSD)
#       define BOOST_OS_BSD BOOST_PREDEF_MAKE_10_VVRR(BSD)
#   else
#       define BOOST_OS_BSD BOOST_VERSION_NUMBER(0,0,1)
#   endif
#endif

#define BOOST_OS_BSD_NAME "BSD"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_OS_BSD,BOOST_OS_BSD_NAME)

#include <boost/predef/os/bsd/bsdi.h>
#include <boost/predef/os/bsd/dragonfly.h>
#include <boost/predef/os/bsd/free.h>
#include <boost/predef/os/bsd/open.h>
#include <boost/predef/os/bsd/net.h>

#endif
