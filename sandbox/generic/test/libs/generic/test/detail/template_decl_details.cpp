/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/template_decl_details.hpp>

/////////////////////////
// Prepare Test Inputs //
/////////////////////////
#define UNPARENTHESIZED_INVALID_PARAM_LIST_DETAILS                             \
BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS( template ( (class) X ) )

#define PARENTHESIZED_INVALID_TEMPLATE_DECL                                    \
BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS( ( some mistake ( (class) X ) ) )

#define PARENTHESIZED_INVALID_PARAM_LIST_DETAILS                               \
BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS( ( template ( class X ) ) )

#define INVALID_POST_PARAM_LIST                                                \
BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS                                     \
( ( template ( (class) X ) erroneous ) )

#define VALID_TEMPLATE_DECL                                                    \
BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS( ( template ( (class) X ) ) )

#define VALID_NULLARY_TEMPLATE_DECL                                            \
BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETAILS( ( template () ) )

//////////////////
// Begin Tests  //
//////////////////
#if BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID(                          \
UNPARENTHESIZED_INVALID_PARAM_LIST_DETAILS )
#error Unparenthesized template param list recognized as valid.
#endif

#if BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID(                          \
PARENTHESIZED_INVALID_TEMPLATE_DECL )
#error Parenthesized invalid template declaration recognized as valid.
#endif

#if BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID(                          \
PARENTHESIZED_INVALID_PARAM_LIST_DETAILS )
#error Parenthesized invalid template param list recognized as valid.
#endif

#if BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID(                          \
INVALID_POST_PARAM_LIST )
#error Parenthesized template param list with specifiers recognized as valid.
#endif

#if !BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID(                         \
VALID_TEMPLATE_DECL )
#error Valid template param list recognized as invalid.
#endif

#if !BOOST_GENERIC_DETAIL_TEMPLATE_DECL_DETS_IS_VALID(                         \
VALID_NULLARY_TEMPLATE_DECL )
#error Valid nullary template param list recognized as invalid.
#endif
