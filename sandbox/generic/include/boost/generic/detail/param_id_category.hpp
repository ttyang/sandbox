/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_HPP
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_HPP

#include <boost/generic/detail/param_id.hpp>
#include <boost/preprocessor/cat.hpp>

// Whenever a category is added, the value macros must also be updated in
// <boost/generic/detail/param_id_category_value.hpp>

#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY( arg_in_paren )                 \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_                          \
            , BOOST_GENERIC_DETAIL_PARAM_ID( arg_in_paren )                    \
            )

// Macros that associate param IDs with the category that they belong to
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_const       const
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_for         for
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_for_typedef for_typedef
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_if          if
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_if_not      if_not
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_if_typedef  if_typedef
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_public      public
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_try         try
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_typename    typename
#define BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_using       using

#endif // BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_HPP
