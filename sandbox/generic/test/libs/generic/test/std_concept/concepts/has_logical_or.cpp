/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_logical_or.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasLogicalOr;

BOOST_GENERIC_ASSERT( HasLogicalOr< int, int > );

BOOST_GENERIC_ASSERT( HasLogicalOr< float, float > );

struct a {};

struct logical_or_object_left {};
struct logical_or_object_right {};

bool operator ||( logical_or_object_left, logical_or_object_right );

a operator ||( logical_or_object_right, logical_or_object_left );

BOOST_GENERIC_ASSERT
( HasLogicalOr< logical_or_object_left, logical_or_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasLogicalOr< logical_or_object_left, logical_or_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasLogicalOr< logical_or_object_right, logical_or_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasLogicalOr< logical_or_object_right, logical_or_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasLogicalOr< logical_or_object_right, logical_or_object_left > );
