/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_greater.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasGreater;

BOOST_GENERIC_ASSERT( HasGreater< int, int > );

BOOST_GENERIC_ASSERT( HasGreater< float, float > );

struct a {};

struct greater_object_left {};
struct greater_object_right {};

bool operator >( greater_object_left, greater_object_right );

a operator >( greater_object_right, greater_object_left );

BOOST_GENERIC_ASSERT
( HasGreater< greater_object_left, greater_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasGreater< greater_object_left, greater_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasGreater< greater_object_right, greater_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasGreater< greater_object_right, greater_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasGreater< greater_object_right, greater_object_left > );
