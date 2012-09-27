/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED_HPP
#define BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED_HPP

#include <boost/generic/detail/eat.hpp>
#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( ... )                           \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )         \
            , BOOST_GENERIC_DETAIL_IS_PARENTHESIZED_IMPL_STARTS_PAREN          \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                      \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_IS_PARENTHESIZED_IMPL_STARTS_PAREN( ... )         \
BOOST_GENERIC_DETAIL_IS_EMPTY( BOOST_GENERIC_DETAIL_EAT_WRAPPED( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( ... )                       \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN                                   \
  ( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED_IMPL                             \
      BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                        \
  )                                                                            \
, 2                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED_IMPL( ... ) _1, _2

#endif // BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED_HPP
