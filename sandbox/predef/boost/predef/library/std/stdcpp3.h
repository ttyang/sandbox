/*
Copyright Redshift Software, Inc. 2008-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_LIBRARY_STD_STDCPP3_H
#define BOOST_PREDEF_LIBRARY_STD_STDCPP3_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_LIB_STD_GNU`]

[@http://gcc.gnu.org/libstdc++/ GNU libstdc++] Standard C++ library.
Version number available as year (from 1970), month, and day.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_LIB_STD_GNU BOOST_VERSION_NUMBER(0,0,0)

#if defined(__GLIBCPP__) || defined(__GLIBCXX__)
#   undef BOOST_LIB_STD_GNU
#   if defined(__GLIBCXX__)
#       define BOOST_LIB_STD_GNU BOOST_PREDEF_MAKE_YYYYMMDD(__GLIBCXX__)
#   else
#       define BOOST_LIB_STD_GNU BOOST_PREDEF_MAKE_YYYYMMDD(__GLIBCPP__)
#   endif
#endif

#define BOOST_LIB_STD_GNU_NAME "GNU"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_LIB_STD_GNU,BOOST_LIB_STD_GNU_NAME)


#endif
