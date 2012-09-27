/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_IS_RECOGNIZED_ARG_HPP
#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_ARG_HPP

#include <boost/generic/detail/128_args.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/param_id.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/greater.hpp>

// This macro "works" in a very hackish way. It concatenates a base macro name
// with the argument. If it's a recognized name, this will produce an invocation
// that yields text with at least 127 top-level commas (top-level meaning not
// surrounded by parentheses). How many top-level args are then checked and if
// the number is greater than 127, we assume that the param id was correctly
// identified. Note that this can fail if the produced comma-separated list has
// more commas than can be handled by the macro which checks how many arguments
// are passed. In practice this will likely never come up, but if it does, the
// number of arguments supported by the size-checking macro can be easily
// increased. One possible place this may cause a problem is if someone has an
// initializer list in a "do" with over 128 elements.
#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_ARG( arg_in_paren )                 \
BOOST_PP_GREATER                                                               \
( BOOST_GENERIC_DETAIL_NUM_ARGS                                                \
  ( BOOST_PP_CAT                                                               \
    ( BOOST_GENERIC_DETAIL_IS_RECOGNIZED_                                      \
    , BOOST_GENERIC_DETAIL_PARAM_ID( arg_in_paren )                            \
    )                                                                          \
  )                                                                            \
, 127                                                                          \
)
#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_for                                 \
BOOST_GENERIC_DETAIL_128_ARGS()

#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_for_typedef                         \
BOOST_GENERIC_DETAIL_128_ARGS()

#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_if                                  \
BOOST_GENERIC_DETAIL_128_ARGS()

#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_if_not                              \
BOOST_GENERIC_DETAIL_128_ARGS()

#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_if_typedef                          \
BOOST_GENERIC_DETAIL_128_ARGS()

#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_try                                 \
BOOST_GENERIC_DETAIL_128_ARGS()

#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_typename                            \
BOOST_GENERIC_DETAIL_128_ARGS()

#define BOOST_GENERIC_DETAIL_IS_RECOGNIZED_public                               \
BOOST_GENERIC_DETAIL_128_ARGS()

#endif // BOOST_GENERIC_DETAIL_IS_RECOGNIZED_ARG_HPP
