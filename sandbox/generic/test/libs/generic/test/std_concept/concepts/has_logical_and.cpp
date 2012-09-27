/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_logical_and.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasLogicalAnd;

BOOST_GENERIC_ASSERT( HasLogicalAnd< int, int > );

BOOST_GENERIC_ASSERT( HasLogicalAnd< float, float > );

struct a {};

struct logical_and_object_left {};
struct logical_and_object_right {};

bool operator &&( logical_and_object_left, logical_and_object_right );

a operator &&( logical_and_object_right, logical_and_object_left );

BOOST_GENERIC_ASSERT
( HasLogicalAnd< logical_and_object_left, logical_and_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasLogicalAnd< logical_and_object_left, logical_and_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasLogicalAnd< logical_and_object_right, logical_and_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasLogicalAnd< logical_and_object_right, logical_and_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasLogicalAnd< logical_and_object_right, logical_and_object_left > );
