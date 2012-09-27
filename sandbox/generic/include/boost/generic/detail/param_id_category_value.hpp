/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_HPP
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_HPP

#include <boost/generic/detail/param_id_category.hpp>
#include <boost/preprocessor/cat.hpp>

// Whenever a category value is added, the category macros must also be updated
// in <boost/generic/detail/param_id_category.hpp>

#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( arg_in_paren )           \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_                    \
            , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY( arg_in_paren )           \
            )

// Macros that associate each param category ID with a unique value
// Note: If a category is added, it is important to update
// BOOST_GENERIC_DETAIL_NUM_PARAM_CATEGORIES as well
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_const       0
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_for         1
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_for_typedef 2
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_if          3
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_if_not      4
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_if_typedef  5
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_public      6
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_try         7
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_typename    8
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_using       9

// Update this whenever a new category is added
#define BOOST_GENERIC_DETAIL_NUM_PARAM_CATEGORIES 10

#endif // BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE_HPP
