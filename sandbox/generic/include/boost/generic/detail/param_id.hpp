/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PARAM_ID_HPP
#define BOOST_GENERIC_DETAIL_PARAM_ID_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/split_param_id_and_param.hpp>
#include <boost/preprocessor/cat.hpp>

// A macro that assigns a single-token name to each parambased on its param id
// (it removes spaces from multiword param ids and replaces them with _)
#define BOOST_GENERIC_DETAIL_PARAM_ID( arg_in_paren )                          \
BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_AFTER_RESCAN                                \
( BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM( arg_in_paren ) )

#define BOOST_GENERIC_DETAIL_SPACED_ID( param_id )                             \
BOOST_PP_CAT( BOOST_GENERIC_DETAIL_SPACED_ID_, param_id )

#define BOOST_GENERIC_DETAIL_SPACED_ID_const       const
#define BOOST_GENERIC_DETAIL_SPACED_ID_for         for
#define BOOST_GENERIC_DETAIL_SPACED_ID_for_typedef for typedef
#define BOOST_GENERIC_DETAIL_SPACED_ID_if          if
#define BOOST_GENERIC_DETAIL_SPACED_ID_if_not      if not
#define BOOST_GENERIC_DETAIL_SPACED_ID_if_typedef  if typedef
#define BOOST_GENERIC_DETAIL_SPACED_ID_public      public
#define BOOST_GENERIC_DETAIL_SPACED_ID_try         try
#define BOOST_GENERIC_DETAIL_SPACED_ID_typename    typename
#define BOOST_GENERIC_DETAIL_SPACED_ID_using       using

#endif // BOOST_GENERIC_DETAIL_PARAM_ID_HPP
