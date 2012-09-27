/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PARENTHESES_HPP
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PARENTHESES_HPP

#include <boost/generic/detail/param_id.hpp>
#include <boost/preprocessor/cat.hpp>

// A macro that assigns a unique value to each different parameter kind
// This macro takes the entire argument including the name
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PARENTHESES( arg_in_paren )      \
BOOST_PP_CAT                                                                   \
( BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_                                 \
, BOOST_GENERIC_DETAIL_PARAM_ID( arg_in_paren )                                \
)

#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_const       1
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_for         1
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_for_typedef 1
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_if          1
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_if_not      1
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_if_typedef  1
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_public      1
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_try         1
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_typename    1
#define BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PAREN_using       1

#endif // BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PARENTHESES_HPP
