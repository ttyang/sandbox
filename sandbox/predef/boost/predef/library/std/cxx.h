/*
Copyright Redshift Software Inc 2011-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_LIBRARY_STD_CXX_H
#define BOOST_PREDEF_LIBRARY_STD_CXX_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_LIB_STD_CXX`]

[@http://libcxx.llvm.org/ libc++] C++ Standard Library.
If available version number as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_LIB_STD_CXX BOOST_VERSION_NUMBER(0,0,0)

#if defined(_LIBCPP_VERSION)
#   undef BOOST_LIB_STD_CXX
#   define BOOST_LIB_STD_CXX BOOST_PREDEF_MAKE_10_VPPP(_LIBCPP_VERSION)
#endif

#define BOOST_LIB_STD_CXX_NAME "libc++"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_LIB_STD_CXX,BOOST_LIB_STD_CXX_NAME)


#endif
