/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_IS_EMPTY_HPP
#define BOOST_GENERIC_DETAIL_IS_EMPTY_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/preprocessor/logical/compl.hpp>

#include <boost/variadic_macro_data/vmd_is_empty.hpp>

// Checks if the first argument is empty
#define BOOST_GENERIC_DETAIL_STARTS_EMPTY( ... )                               \
BOOST_GENERIC_DETAIL_IS_EMPTY                                                  \
( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )

// Checks if the argument is not empty
#define BOOST_GENERIC_DETAIL_IS_NOT_EMPTY( ... )                               \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
)

#define BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY( ... )                           \
BOOST_GENERIC_DETAIL_IS_EMPTY __VA_ARGS__

#define BOOST_GENERIC_DETAIL_IS_EMPTY BOOST_VMD_IS_EMPTY

#define BOOST_GENERIC_DETAIL_IS_EMPTY_AFTER_RESCAN( ... )                      \
BOOST_GENERIC_DETAIL_IS_EMPTY_AFTER_RESCAN_( (__VA_ARGS__) )

#define BOOST_GENERIC_DETAIL_IS_EMPTY_AFTER_RESCAN_( ... )                     \
BOOST_GENERIC_DETAIL_IS_EMPTY __VA_ARGS__

#endif // BOOST_GENERIC_DETAIL_IS_EMPTY_HPP
