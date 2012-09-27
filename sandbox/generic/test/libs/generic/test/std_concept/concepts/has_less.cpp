/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_less.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasLess;

BOOST_GENERIC_ASSERT( HasLess< int, int > );

BOOST_GENERIC_ASSERT( HasLess< float, float > );

struct a {};

struct less_object_left {};
struct less_object_right {};

bool operator <( less_object_left, less_object_right );

a operator <( less_object_right, less_object_left );

BOOST_GENERIC_ASSERT
( HasLess< less_object_left, less_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasLess< less_object_left, less_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasLess< less_object_right, less_object_right > );

BOOST_GENERIC_ASSERT_NOT
( HasLess< less_object_right, less_object_left > );

BOOST_GENERIC_ASSERT_NOT
( HasLess< less_object_right, less_object_left > );
