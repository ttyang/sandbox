/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_constructor.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasConstructor;

struct a {}; struct b {}; struct c {};

struct type_with_constructors
{
  type_with_constructors( int );
  type_with_constructors( a );
  type_with_constructors( a, b );
  type_with_constructors( a, b, c );
};

BOOST_GENERIC_ASSERT( HasConstructor< int > );
BOOST_GENERIC_ASSERT( HasConstructor< int, char > );
BOOST_GENERIC_ASSERT( HasConstructor< type_with_constructors, int > );
BOOST_GENERIC_ASSERT( HasConstructor< type_with_constructors, a > );
BOOST_GENERIC_ASSERT( HasConstructor< type_with_constructors, a, b > );
BOOST_GENERIC_ASSERT( HasConstructor< type_with_constructors, a, b, c > );

BOOST_GENERIC_ASSERT_NOT( HasConstructor< type_with_constructors > );
BOOST_GENERIC_ASSERT_NOT( HasConstructor< type_with_constructors, b > );
BOOST_GENERIC_ASSERT_NOT( HasConstructor< type_with_constructors, b, b > );
BOOST_GENERIC_ASSERT_NOT( HasConstructor< type_with_constructors, b, c, a > );
BOOST_GENERIC_ASSERT_NOT( HasConstructor< void > );
BOOST_GENERIC_ASSERT_NOT( HasConstructor< void, int > );
BOOST_GENERIC_ASSERT_NOT( HasConstructor< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasConstructor< int, int, int > );
