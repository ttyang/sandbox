/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_NARY_CAT_HPP
#define BOOST_GENERIC_DETAIL_NARY_CAT_HPP

#include <boost/generic/detail/num_args.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_GENERIC_DETAIL_NARY_CAT( ... )                                   \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_NARY_CAT_                                   \
            , BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ )                     \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NARY_CAT_1( arg ) arg

#define BOOST_GENERIC_DETAIL_NARY_CAT_2( l, r ) BOOST_PP_CAT( l, r )

#define BOOST_GENERIC_DETAIL_NARY_CAT_3( head, ... )                           \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_2( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_4( head, ... )                           \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_3( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_5( head, ... )                           \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_4( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_6( head, ... )                           \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_5( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_7( head, ... )                           \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_6( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_8( head, ... )                           \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_7( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_9( head, ... )                           \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_8( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_10( head, ... )                          \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_9( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_11( head, ... )                          \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_10( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_12( head, ... )                          \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_11( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_13( head, ... )                          \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_12( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_14( head, ... )                          \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_13( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_15( head, ... )                          \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_14( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_NARY_CAT_16( head, ... )                          \
BOOST_PP_CAT( head, BOOST_GENERIC_DETAIL_NARY_CAT_15( __VA_ARGS__ ) )

#endif // BOOST_GENERIC_DETAIL_NARY_CAT_HPP
