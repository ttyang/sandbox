/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/


#include <boost/generic/std_concept/concepts/explicitly_convertible.hpp>

#include <boost/generic/archetype/null_archetype.hpp>
#include <boost/generic/assert.hpp>

using boost::generic::std_concept::ExplicitlyConvertible;

BOOST_GENERIC_ASSERT( ExplicitlyConvertible< int, float > );

BOOST_GENERIC_ASSERT( ExplicitlyConvertible< int[1], int* > );
BOOST_GENERIC_ASSERT( ExplicitlyConvertible< int[], int* > );

BOOST_GENERIC_ASSERT( ExplicitlyConvertible< int*, void* > );
BOOST_GENERIC_ASSERT( ExplicitlyConvertible< void*, int* > );
BOOST_GENERIC_ASSERT( ExplicitlyConvertible< char*, int* > );

BOOST_GENERIC_ASSERT( ExplicitlyConvertible< int&&, int&& > );

BOOST_GENERIC_ASSERT_NOT( ExplicitlyConvertible< int(), int[] > );
BOOST_GENERIC_ASSERT_NOT( ExplicitlyConvertible< int[], int() > );

struct convertible_to_a
{
};

struct convertible_from_a
  : boost::generic::null_archetype
{
  operator convertible_to_a() const;
};

BOOST_GENERIC_ASSERT( ExplicitlyConvertible< convertible_from_a, convertible_to_a > );
BOOST_GENERIC_ASSERT_NOT( ExplicitlyConvertible< convertible_to_a, convertible_from_a > );


struct only_explicitly_convertible_from_a
  : boost::generic::null_archetype
{
  explicit operator convertible_to_a() const;
};

BOOST_GENERIC_ASSERT( ExplicitlyConvertible< only_explicitly_convertible_from_a, convertible_to_a > );

struct convertible_from_b
  : boost::generic::null_archetype
{
};

struct convertible_to_b
{
  convertible_to_b( convertible_from_b const& );
};

BOOST_GENERIC_ASSERT( ExplicitlyConvertible< convertible_from_b, convertible_to_b > );
BOOST_GENERIC_ASSERT_NOT( ExplicitlyConvertible< convertible_to_b, convertible_from_b > );
BOOST_GENERIC_ASSERT_NOT( ExplicitlyConvertible< void, convertible_from_b > );

// TODO determine if these should succeed or if this is a test failure
BOOST_GENERIC_ASSERT_NOT( ExplicitlyConvertible< convertible_to_b, void > );
BOOST_GENERIC_ASSERT_NOT( ExplicitlyConvertible< void, void > );
