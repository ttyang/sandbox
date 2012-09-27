/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_NUM_ARGS_IS_1_HPP
#define BOOST_GENERIC_DETAIL_NUM_ARGS_IS_1_HPP

#include <boost/generic/detail/num_args.hpp>
#include <boost/preprocessor/comparison/equal.hpp>

#define BOOST_GENERIC_DETAIL_NUM_ARGS_IS_1( ... )                              \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ ), 1 )

#define BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN_IS_1( ... )                 \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN( __VA_ARGS__ ), 1 )

#define BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS_IS_1( ... )                      \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( __VA_ARGS__ ), 1 )

#endif // BOOST_GENERIC_DETAIL_NUM_ARGS_IS_1_HPP
