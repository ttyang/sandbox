/*
Copyright Redshift Software, Inc. 2008-2011
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_LIBRARY_STD_STLPORT_H
#define BOOST_PREDEF_LIBRARY_STD_STLPORT_H

#include <boost/predef/version_number.h>
#include <boost/predef/make.h>

/*`
[heading `BOOST_LIBSTD_STLPORT`]

[@http://en.wikipedia.org/wiki/XXX STLport Standard C++] library.
Version number available as major, minor, and patch.
 */

#define BOOST_LIBSTD_STLPORT BOOST_VERSION_NUMBER(0,0,0)

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
    #undef BOOST_LIBSTD_STLPORT
    #if defined(_STLPORT_MAJOR)
        #define BOOST_LIBSTD_STLPORT \
            BOOST_VERSION_NUMBER(_STLPORT_MAJOR,_STLPORT_MINOR,_STLPORT_PATCHLEVEL)
    #elif defined(_STLPORT_VERSION)
        #define BOOST_LIBSTD_STLPORT BOOST_PREDEF_MAKE_F_F_F(_STLPORT_VERSION)
    #else
        #define BOOST_LIBSTD_STLPORT BOOST_PREDEF_MAKE_F_F_F(__SGI_STL_PORT)
    #endif
#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_LIBSTD_STLPORT,"STLport")

#endif
