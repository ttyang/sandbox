/*
Copyright Redshift Software Inc. 2011-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_LANGUAGE_OBJC_H
#define BOOST_PREDEF_LANGUAGE_OBJC_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_LANG_OBJC`]

[@http://en.wikipedia.org/wiki/Objective-C Objective-C] language.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_LANG_OBJC BOOST_VERSION_NUMBER(0,0,0)

#if defined(__OBJC__)
#   undef BOOST_LANG_OBJC
#   define BOOST_LANG_OBJC BOOST_VERSION_NUMBER(0,0,1)
#endif

#define BOOST_LANG_OBJC_NAME "Objective-C"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_LANG_OBJC,BOOST_LANG_OBJC_NAME)


#endif
