/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_ARE_VALID_PARAMS_HPP
#define BOOST_GENERIC_DETAIL_ARE_VALID_PARAMS_HPP

#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/params_to_list.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/list/fold_left.hpp>

#define BOOST_GENERIC_DETAIL_ARE_VALID_PARAMS( params )                        \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( params )                          \
, BOOST_GENERIC_DETAIL_ARE_VALID_PARAMS_IMPL                                   \
, BOOST_GENERIC_DETAIL_ALWAYS_0                                                \
)( params )

#define BOOST_GENERIC_DETAIL_ARE_VALID_PARAMS_IMPL( params )                   \
BOOST_PP_LIST_FOLD_LEFT                                                        \
( BOOST_GENERIC_DETAIL_ARE_VALID_PARAMS_IMPL_MACRO, 1                          \
, BOOST_GENERIC_DETAIL_PARAMS_TO_LIST( params )                                \
)

#define BOOST_GENERIC_DETAIL_ARE_VALID_PARAMS_IMPL_MACRO( s, state, elem )     \
BOOST_PP_IIF( state                                                            \
            , BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                        \
            , BOOST_GENERIC_DETAIL_ALWAYS_0                                    \
            )( elem () ) // () necessary to consider no params as valid

#define BOOST_GENERIC_DETAIL_ALWAYS_0( ... ) 0
#define BOOST_GENERIC_DETAIL_ALWAYS_1( ... ) 1

#endif // BOOST_GENERIC_DETAIL_ARE_VALID_PARAMS_HPP
