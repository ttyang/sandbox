/*
Copyright Redshift Software, Inc. 2008-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_LIBRARY_STD_ROGUEWAVE_H
#define BOOST_PREDEF_LIBRARY_STD_ROGUEWAVE_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_LIB_STD_RW`]

[@http://stdcxx.apache.org/ Roguewave] Standard C++ library.
If available version number as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_LIB_STD_RW BOOST_VERSION_NUMBER(0,0,0)

#if defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
#   undef BOOST_LIB_STD_RW
#   if defined(_RWSTD_VER)
#       if _RWSTD_VER < 0x010000
#           define BOOST_LIB_STD_RW BOOST_PREDEF_MAKE_0X_VVRRP(_RWSTD_VER)
#       else
#          define BOOST_LIB_STD_RW BOOST_PREDEF_MAKE_FF_FF_FF(_RWSTD_VER)
#       endif
#   else
#       define BOOST_LIB_STD_RW BOOST_VERSION_NUMBER(0,0,1)
#   endif
#endif

#define BOOST_LIB_STD_RW_NAME "Roguewave"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_LIB_STD_RW,BOOST_LIB_STD_RW_NAME)


#endif
