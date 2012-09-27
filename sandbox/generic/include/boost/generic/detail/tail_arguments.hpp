/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_HPP
#define BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_HPP

#include <boost/generic/detail/remove_paren.hpp>
#include <boost/preprocessor/array/data.hpp>
#include <boost/preprocessor/array/pop_front.hpp>
#include <boost/preprocessor/variadic/to_array.hpp>

#define BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( ... )                             \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_PP_ARRAY_DATA                                                          \
  ( BOOST_PP_ARRAY_POP_FRONT( BOOST_PP_VARIADIC_TO_ARRAY( __VA_ARGS__ ) ) )    \
)

#define BOOST_GENERIC_DETAIL_TAIL_WRAPPED_ARGUMENTS( params )                  \
BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS params

#define BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_AFTER_RESCAN( ... )                \
BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( __VA_ARGS__ )

#endif // BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_HPP
