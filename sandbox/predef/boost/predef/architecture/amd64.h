/*
Copyright Redshift Software, Inc. 2008-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_ARCHITECTURE_AMD64_H
#define BOOST_PREDEF_ARCHITECTURE_AMD64_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_ARCH_AMD64`, [@http://en.wikipedia.org/wiki/Amd64 Advanced Micro Devices AMD 64] architecture.]

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_ARCH_AMD64 BOOST_VERSION_NUMBER(0,0,0)

#if defined(__amd64__) || defined(__amd64) || \
    defined(__x86_64__) || defined(__x86_64) || \
    defined(_M_X64)
#   undef BOOST_ARCH_AMD64
#   define BOOST_ARCH_AMD64 BOOST_VERSION_NUMBER(0,0,1)
#endif

#define BOOST_ARCH_AMD64_NAME "Advanced Micro Devices AMD 64"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_ARCH_AMD64,BOOST_ARCH_AMD64_NAME)


#endif
