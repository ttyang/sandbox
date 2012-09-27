/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_not_equal_to.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasNotEqualTo;

BOOST_GENERIC_ASSERT( HasNotEqualTo< int, int > );

BOOST_GENERIC_ASSERT( HasNotEqualTo< float, float > );

struct a {};

struct not_equal_to_object_left {};
struct not_equal_to_object_right {};

bool operator !=( not_equal_to_object_left, not_equal_to_object_right );

a operator !=( not_equal_to_object_right, not_equal_to_object_left );

BOOST_GENERIC_ASSERT
( HasNotEqualTo< not_equal_to_object_left, not_equal_to_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasNotEqualTo< not_equal_to_object_left, not_equal_to_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasNotEqualTo< not_equal_to_object_right, not_equal_to_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasNotEqualTo< not_equal_to_object_right, not_equal_to_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasNotEqualTo< not_equal_to_object_right, not_equal_to_object_left > );
