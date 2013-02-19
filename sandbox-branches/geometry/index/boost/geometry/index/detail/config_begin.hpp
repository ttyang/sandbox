// Boost.Geometry Index
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#ifdef BOOST_MSVC

    #define BOOST_GEOMETRY_INDEX_DETAIL_USE_PARAM(A) (void)A;

    #ifndef _CRT_SECURE_NO_DEPRECATE
    #define BOOST_GEOMETRY_INDEX_DETAIL_CRT_SECURE_NO_DEPRECATE_ENABLED
    #define _CRT_SECURE_NO_DEPRECATE
    #endif

    #pragma warning (push)
    #pragma warning (disable : 4512) // assignment operator could not be generated
    #pragma warning (disable : 4127) // conditional expression is constant

#else //BOOST_MSVC

    #define BOOST_GEOMETRY_INDEX_DETAIL_USE_PARAM(A)

#endif   //BOOST_MSVC

