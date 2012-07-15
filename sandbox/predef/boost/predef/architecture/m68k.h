/*
Copyright Redshift Software, Inc. 2008-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_ARCHITECTURE_M68K_H
#define BOOST_PREDEF_ARCHITECTURE_M68K_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_ARCH_M68K`]

[@http://en.wikipedia.org/wiki/M68k Motorola 68k] architecture.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_ARCH_M68K BOOST_VERSION_NUMBER(0,0,0)

#if defined(__m68k__) || defined(M68000)
#   undef BOOST_ARCH_M68K
#   if defined(__mc68060__) || defined(mc68060) || defined(__mc68060)
#       define BOOST_ARCH_M68K BOOST_VERSION_NUMBER(6,0,0)
#   elif defined(__mc68040__) || defined(mc68040) || defined(__mc68040)
#       define BOOST_ARCH_M68K BOOST_VERSION_NUMBER(4,0,0)
#   elif defined(__mc68030__) || defined(mc68030) || defined(__mc68030)
#       define BOOST_ARCH_M68K BOOST_VERSION_NUMBER(3,0,0)
#   elif defined(__mc68020__) || defined(mc68020) || defined(__mc68020)
#       define BOOST_ARCH_M68K BOOST_VERSION_NUMBER(2,0,0)
#   elif defined(__mc68010__) || defined(mc68010) || defined(__mc68010)
#       define BOOST_ARCH_M68K BOOST_VERSION_NUMBER(1,0,0)
#   elif defined(__mc68000__) || defined(mc68000) || defined(__mc68000)
#       define BOOST_ARCH_M68K BOOST_VERSION_NUMBER(0,0,1)
#   else
#       define BOOST_ARCH_M68K BOOST_VERSION_NUMBER(0,0,1)
#   endif
#endif

#define BOOST_ARCH_M68K_NAME "Motorola 68k"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_ARCH_M68K,BOOST_ARCH_M68K_NAME)


#endif
