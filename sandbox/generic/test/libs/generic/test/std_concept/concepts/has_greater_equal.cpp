/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_greater_equal.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasGreaterEqual;

BOOST_GENERIC_ASSERT( HasGreaterEqual< int, int > );

BOOST_GENERIC_ASSERT( HasGreaterEqual< float, float > );

struct a {};

struct greater_equal_object_left {};
struct greater_equal_object_right {};

bool operator >=( greater_equal_object_left, greater_equal_object_right );

a operator >=( greater_equal_object_right, greater_equal_object_left );

BOOST_GENERIC_ASSERT
( HasGreaterEqual< greater_equal_object_left, greater_equal_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasGreaterEqual< greater_equal_object_left, greater_equal_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasGreaterEqual< greater_equal_object_right, greater_equal_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasGreaterEqual< greater_equal_object_right, greater_equal_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasGreaterEqual< greater_equal_object_right, greater_equal_object_left > );
