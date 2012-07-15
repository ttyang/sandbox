/*
Copyright Redshift Software Inc. 2011-2012
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_LANGUAGE_STDC_H
#define BOOST_PREDEF_LANGUAGE_STDC_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_LANG_STDC`]

[@http://en.wikipedia.org/wiki/C_(programming_language) Standard C] language.
If available, the year of the standard is detected as YYYY.1.1 from the Epoc date.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[``] [__predef_detection__]]

    [[``] [V.R.P]]
    ]
 */

#define BOOST_LANG_STDC BOOST_VERSION_NUMBER(0,0,0)

#if defined(__STDC__)
#   undef BOOST_LANG_STDC
#   if defined(__STDC_VERSION__)
#       if (__STDC_VERSION__ > 100)
#           define BOOST_LANG_STDC BOOST_PREDEF_MAKE_YYYY(__STDC_VERSION__)
#       else
#           define BOOST_LANG_STDC BOOST_VERSION_NUMBER(0,0,1)
#       endif
#   else
#       define BOOST_LANG_STDC BOOST_VERSION_NUMBER(0,0,1)
#   endif
#endif

#define BOOST_LANG_STDC_NAME "Standard C"

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_LANG_STDC,BOOST_LANG_STDC_NAME)


#endif
