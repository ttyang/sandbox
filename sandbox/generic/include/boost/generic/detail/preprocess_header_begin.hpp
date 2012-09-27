/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#include <boost/generic/detail/nary_cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#ifdef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

#ifndef BOOST_GENERIC_PREPROCESSED_ROOT
#error BOOST_GENERIC_PREPROCESSED_ROOT must be defined to be the proper directory when generating Boost.Generic preprocessed headers
#endif

#pragma wave option( output: push )
#pragma wave option( line: push )
#pragma wave option( line: 0 )
#pragma wave option( output: BOOST_PP_STRINGIZE( BOOST_GENERIC_DETAIL_NARY_CAT( BOOST_GENERIC_PREPROCESSED_ROOT, eric/std_, BOOST_GENERIC_PREPROCESSED_HEADER_NAME, ei ) ) )

#endif

#undef BOOST_GENERIC_PREPROCESSED_HEADER_NAME
