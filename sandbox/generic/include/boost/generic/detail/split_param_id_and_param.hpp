/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_HPP
#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/config.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_GENERIC_DETAIL_EAT_FOR_for

#define BOOST_GENERIC_DETAIL_EAT_IF_if

// Macros that combine "for" with its secondary param ID and separates
// the param ID from the parameter by a comma
#define BOOST_GENERIC_DETAIL_SPLIT_FOR_PARAM_ID_AND_PARAM_typedef for_typedef,

// Macros that combine "if" with its secondary param ID and separates
// the param ID from the parameter by a comma
#define BOOST_GENERIC_DETAIL_SPLIT_IF_PARAM_ID_AND_PARAM_not     if_not,
#define BOOST_GENERIC_DETAIL_SPLIT_IF_PARAM_ID_AND_PARAM_typedef if_typedef,

// Macros that separate 1 word param IDs from the parameter by a comma
#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_try      try,
#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_typename typename,
#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_public    public,

// Macros that determine if "for" is the first word of a param ID
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_FOR_for        1,
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_FOR_if         0,
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_FOR_try        0,
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_FOR_typename   0,
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_FOR_public      0,

// Macros that determine if "if" is the first word of a param ID
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_IF_for        0,
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_IF_if         1,
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_IF_try        0,
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_IF_typename   0,
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_IF_public      0,

// Implementation for exactly for and exactly if
#define BOOST_GENERIC_DETAIL_FOR_COMMA_for for,
#define BOOST_GENERIC_DETAIL_IF_COMMA_if   if,

#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_EXACTLY_IF_IMPL( ... )   \
BOOST_GENERIC_DETAIL_IF_COMMA_ ## __VA_ARGS__

#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_EXACTLY_FOR_IMPL( ... )  \
BOOST_GENERIC_DETAIL_FOR_COMMA_ ## __VA_ARGS__

#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_NOT_EXACTLY_FOR_IMPL(...)\
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_SPLIT_FOR_PARAM_ID_AND_PARAM_                           \
, BOOST_GENERIC_DETAIL_EAT_FOR_ ## __VA_ARGS__                                 \
)

#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_NOT_EXACTLY_IF_IMPL(...) \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_SPLIT_IF_PARAM_ID_AND_PARAM_                            \
, BOOST_GENERIC_DETAIL_EAT_IF_ ## __VA_ARGS__                                  \
)

// Combines "for" with the secondary param ID and separates the full ID
// from the parameter by a comma
#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_FOR_IMPL( ... )          \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                    \
  ( BOOST_GENERIC_DETAIL_EAT_FOR_ ## __VA_ARGS__ )                             \
, BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_EXACTLY_FOR_IMPL               \
, BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_NOT_EXACTLY_FOR_IMPL           \
)( __VA_ARGS__ )

// Combines "if" with the secondary param ID and separates the full ID
// from the parameter by a comma
#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_IF_IMPL(...)             \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                    \
  ( BOOST_GENERIC_DETAIL_EAT_IF_ ## __VA_ARGS__ )                              \
, BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_EXACTLY_IF_IMPL                \
, BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_NOT_EXACTLY_IF_IMPL            \
)( __VA_ARGS__ )

// Yields 1 if the parameter id starts with "for"
// otherwise yields 0
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_FOR( ... )                           \
BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_AFTER_RESCAN                                \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_HAS_FOR_                                     \
  , __VA_ARGS__                                                                \
  )                                                                            \
)

// Yields 1 if the parameter id starts with "virtual"
// otherwise yields 0
#define BOOST_GENERIC_DETAIL_PARAM_ID_HAS_IF( ... )                            \
BOOST_GENERIC_DETAIL_HEAD_ARGUMENT_AFTER_RESCAN                                \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_HAS_IF_                                      \
  , __VA_ARGS__                                                                \
  )                                                                            \
)

// Separates a param id from the parameter by a comma
#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_ONE_WORD_IMPL( ... )     \
BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_ ## __VA_ARGS__

// Separates a param id from the parameter by a comma
// If the parameter ID is multiple words, it combines them and replaces spaces
// with underscores
#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM( arg_in_paren )          \
BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_IMPL arg_in_paren

#define BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_IMPL( ... )              \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_PARAM_ID_HAS_FOR( __VA_ARGS__ )                         \
, BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_FOR_IMPL                       \
, BOOST_PP_IIF                                                                 \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_HAS_IF( __VA_ARGS__ )                        \
  , BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_IF_IMPL                      \
  , BOOST_GENERIC_DETAIL_SPLIT_PARAM_ID_AND_PARAM_ONE_WORD_IMPL                \
  )                                                                            \
)( __VA_ARGS__ BOOST_GENERIC_DETAIL_VARIADIC_EMPTY )

#endif //BOOST_GENERIC_DETAIL_SPLIT_SPLIT_PARAM_ID_AND_PARAM_AND_PARAM_HPP
