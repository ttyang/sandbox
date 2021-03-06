/*
Copyright Redshift Software, Inc. 2008-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_ARCHITECTURE_PARISC_H
#define BOOST_PREDEF_ARCHITECTURE_PARISC_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_ARCH_PARISK`]

[@http://en.wikipedia.org/wiki/PA-RISC_family HP/PA RISC] architecture.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_ARCH_PARISC BOOST_VERSION_NUMBER(0,0,0)

#if defined(__hppa__) || defined(__hppa) || defined(__HPPA__)
#   undef BOOST_ARCH_PARISC
#   if defined(_PA_RISC1_0)
#       define BOOST_ARCH_PARISC BOOST_VERSION_NUMBER(1,0,0)
#   elif defined(_PA_RISC1_1) || defined(__HPPA11__) || defined(__PA7100__)
#       define BOOST_ARCH_PARISC BOOST_VERSION_NUMBER(1,1,0)
#   elif defined(_PA_RISC2_0) || defined(__RISC2_0__) || defined(__HPPA20__) || defined(__PA8000__)
#       define BOOST_ARCH_PARISC BOOST_VERSION_NUMBER(2,0,0)
#   else
#       define BOOST_ARCH_PARISC BOOST_VERSION_NUMBER(0,0,1)
#   endif
#endif

#define BOOST_ARCH_PARISC_NAME "HP/PA RISC"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_ARCH_PARISC,BOOST_ARCH_PARISC_NAME)


#endif
