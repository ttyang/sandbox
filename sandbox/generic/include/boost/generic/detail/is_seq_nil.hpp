/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_IS_SEQ_NIL_HPP
#define BOOST_GENERIC_DETAIL_IS_SEQ_NIL_HPP

#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>

#define BOOST_GENERIC_DETAIL_IS_SEQ_NIL( arg )                                 \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( arg )                 \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                      \
            , BOOST_GENERIC_DETAIL_IS_SEQ_NIL_IMPL                             \
            )( arg )

#define BOOST_GENERIC_DETAIL_IS_SEQ_NIL_IMPL( arg )                            \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN                                   \
  ( BOOST_PP_CAT( BOOST_GENERIC_DETAIL_IS_SEQ_NIL_IMPL, arg foo ) )            \
, 2                                                                            \
)

#define BOOST_GENERIC_DETAIL_IS_SEQ_NIL_IMPLBOOST_PP_SEQ_NIL ,

#endif // BOOST_GENERIC_DETAIL_IS_SEQ_NIL_HPP
