/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_NUM_ARGS_HPP
#define BOOST_GENERIC_DETAIL_NUM_ARGS_HPP

#include <boost/generic/detail/is_empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/variadic/size.hpp>

// Special thanks to Jens Gustedt for handling the 0-argument case

// Original implementation based on macros by Laurent Deniau

#define BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( args )                          \
BOOST_GENERIC_DETAIL_NUM_ARGS args

#define BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN( ... )                      \
BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NUM_ARGS( ... )                                   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_EMPTY( __VA_ARGS__ )                     \
            , BOOST_PP_IDENTITY( 0 )                                           \
            , BOOST_PP_VARIADIC_SIZE                                           \
            )( __VA_ARGS__ )

#endif // BOOST_GENERIC_DETAIL_NUM_ARGS_HPP
