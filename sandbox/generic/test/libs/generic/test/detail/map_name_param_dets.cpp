/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/map_name_params_details.hpp>

#define UNPARENTHESIZED_INVALID_DETAILS                                        \
BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS( class X )

#if BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IS_PARENTHESIZED                 \
    ( UNPARENTHESIZED_INVALID_DETAILS )

#error Unparenthesized invalid name and params recognized as parenthesized
#endif

#if BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IS_VALID                         \
    ( UNPARENTHESIZED_INVALID_DETAILS )
#error Unparenthesized invalid param list recognized as valid
#endif

#define PARENTHESIZED_INVALID_DETAILS                                          \
BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS( ( class X ) )

#if !BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IS_PARENTHESIZED                \
    ( PARENTHESIZED_INVALID_DETAILS )

#error Parenthesized invalid name and params recognized as not parenthesized
#endif

#if BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IS_VALID                         \
    ( PARENTHESIZED_INVALID_DETAILS )
#error Parenthesized invalid param list recognized as valid
#endif

#define VALID_DETAILS                                                          \
BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS                                      \
( ( some_concept_name )( some, params) )

#if !BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IS_VALID                        \
    ( VALID_DETAILS )
#error Valid param list recognized as invalid
#endif

#if !BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IS_PARENTHESIZED                \
    ( VALID_DETAILS )
#error Valid param list recognized as unparenthesized
#endif
