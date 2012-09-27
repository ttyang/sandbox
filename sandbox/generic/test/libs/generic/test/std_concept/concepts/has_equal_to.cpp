/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_equal_to.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasEqualTo;

BOOST_GENERIC_ASSERT( HasEqualTo< int, int > );

BOOST_GENERIC_ASSERT( HasEqualTo< float, float > );

struct a {};

struct equal_to_object_left {};
struct equal_to_object_right {};

bool operator ==( equal_to_object_left, equal_to_object_right );

a operator ==( equal_to_object_right, equal_to_object_left );

BOOST_GENERIC_ASSERT
( HasEqualTo< equal_to_object_left, equal_to_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasEqualTo< equal_to_object_left, equal_to_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasEqualTo< equal_to_object_right, equal_to_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasEqualTo< equal_to_object_right, equal_to_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasEqualTo< equal_to_object_right, equal_to_object_left > );
