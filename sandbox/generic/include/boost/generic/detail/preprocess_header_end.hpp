/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#include <boost/preprocessor/cat.hpp>

#ifdef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
BOOST_PP_CAT( #un, def BOOST_GENERIC_PREPROCESSED_HEADER_NAME )
#pragma wave option( line: pop )
#pragma wave option( output: pop )
#endif
