/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_UNIQUE_ID_HPP
#define BOOST_GENERIC_DETAIL_UNIQUE_ID_HPP

#include <boost/preprocessor/cat.hpp>

// Takes a potentially unique ID as an argument
#define BOOST_GENERIC_DETAIL_UNIQUE_ID( name )                                 \
BOOST_PP_CAT                                                                   \
( BOOST_PP_CAT( BOOST_PP_CAT( detail_boost_generic_unique_id_, __COUNTER__ )   \
              , BOOST_PP_CAT( _on_line_, __LINE__ )                            \
              )                                                                \
, BOOST_PP_CAT( _with_name_, name )                                            \
)

#define BOOST_GENERIC_DETAIL_UNIQUE_ID_()                                      \
BOOST_GENERIC_DETAIL_UNIQUE_ID( unnamed )

#endif // BOOST_GENERIC_DETAIL_UNIQUE_ID_HPP
