/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN_HPP
#define BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN_HPP

#include <boost/generic/detail/head_argument.hpp>

// Takes text of the form ( data ) post_paren_data
// yields ( data )
// post_paren_data may be no text
#define BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( ... )                       \
BOOST_GENERIC_DETAIL_FIRST_PARAM_AFTER_RESCAN                                  \
( BOOST_GENERIC_DETAIL_PARAM_COMMA_SECOND( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_FIRST_PARAM_AFTER_RESCAN( ... )                   \
BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_SELF_COMMA( ... ) ( __VA_ARGS__ ),

#define BOOST_GENERIC_DETAIL_PARAM_COMMA_SECOND( ... )                         \
BOOST_GENERIC_DETAIL_SELF_COMMA __VA_ARGS__

#endif // BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN_HPP
