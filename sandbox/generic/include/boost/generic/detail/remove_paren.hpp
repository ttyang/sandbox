/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_REMOVE_PAREN_HPP
#define BOOST_GENERIC_DETAIL_REMOVE_PAREN_HPP

#include <boost/generic/detail/eat_part_after_paren.hpp>

#define BOOST_GENERIC_DETAIL_REMOVE_PAREN_IMPL( ... ) __VA_ARGS__

#define BOOST_GENERIC_DETAIL_REMOVE_PAREN( arg )                               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN_IMPL arg

#define BOOST_GENERIC_DETAIL_REMOVE_PAREN_AND_EXTRA_DATA( ... )                \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_GENERIC_DETAIL_EAT_PART_AFTER_PAREN( __VA_ARGS__ ) )

#endif // BOOST_GENERIC_DETAIL_REMOVE_PAREN_HPP
