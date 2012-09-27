/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_HPP
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_HPP

#include <boost/generic/detail/param_id.hpp>
#include <boost/preprocessor/cat.hpp>

// A macro that assigns a unique value to each different parameter kind
// This macro takes the entire argument including the name
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE( arg_in_paren )                    \
BOOST_PP_CAT                                                                   \
( BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_                                         \
, BOOST_GENERIC_DETAIL_PARAM_ID( arg_in_paren )                                \
)

#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_const       0
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_for         1
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_for_typedef 2
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_if          3
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_if_not      4
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_if_typedef  5
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_public      6
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_try         7
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_typename    8
#define BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_using       9

#endif // BOOST_GENERIC_DETAIL_PARAM_ID_VALUE_HPP
