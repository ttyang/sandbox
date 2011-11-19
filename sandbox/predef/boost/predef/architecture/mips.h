/*
Copyright Redshift Software, Inc. 2008-2011
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_ARCHITECTURE_MIPS_H
#define BOOST_PREDEF_ARCHITECTURE_MIPS_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_ARCHITECTURE_MIPS`]

[@http://en.wikipedia.org/wiki/MIPS_architecture MIPS] architecture.
 */

#define BOOST_ARCHITECTURE_MIPS BOOST_VERSION_NUMBER(0,0,0)

#if defined(__mips__) || defined(__mips) || \
    defined(__MIPS__)
    #undef BOOST_ARCHITECTURE_MIPS
    #if defined(__mips)
        #define BOOST_ARCHITECTURE_MIPS BOOST_VERSION_NUMBER(__mips,0,0)
    #elif defined(_MIPS_ISA_MIPS1) || defined(_R3000)
        #define BOOST_ARCHITECTURE_MIPS BOOST_VERSION_NUMBER(1,0,0)
    #elif defined(_MIPS_ISA_MIPS2) || defined(__MIPS_ISA2__) || defined(_R4000)
        #define BOOST_ARCHITECTURE_MIPS BOOST_VERSION_NUMBER(2,0,0)
    #elif defined(_MIPS_ISA_MIPS3) || defined(__MIPS_ISA3__)
        #define BOOST_ARCHITECTURE_MIPS BOOST_VERSION_NUMBER(3,0,0)
    #elif defined(_MIPS_ISA_MIPS4) || defined(__MIPS_ISA4__)
        #define BOOST_ARCHITECTURE_MIPS BOOST_VERSION_NUMBER(4,0,0)
    #else
        #define BOOST_ARCHITECTURE_MIPS BOOST_VERSION_NUMBER(0,0,1)
    #endif
#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_ARCHITECTURE_MIPS,"MIPS")

#endif
