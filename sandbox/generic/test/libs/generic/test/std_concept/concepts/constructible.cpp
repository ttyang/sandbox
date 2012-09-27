/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/constructible.hpp>

#include <boost/generic/assert.hpp>

struct a {}; struct b {}; struct c {};

struct constructible_type
{
  constructible_type();
  constructible_type( a const& );
  constructible_type( a const&, b const& );
  constructible_type( a const&, b const&, c const& );
};

using boost::generic::std_concept::Constructible;

BOOST_GENERIC_ASSERT( Constructible< constructible_type > );
BOOST_GENERIC_ASSERT( Constructible< constructible_type, a > );
BOOST_GENERIC_ASSERT( Constructible< constructible_type, a, b > );
BOOST_GENERIC_ASSERT( Constructible< constructible_type, a, b, c > );

BOOST_GENERIC_ASSERT_NOT( Constructible< constructible_type, b > );
BOOST_GENERIC_ASSERT_NOT( Constructible< constructible_type, c > );
BOOST_GENERIC_ASSERT_NOT( Constructible< constructible_type, b, a > );
BOOST_GENERIC_ASSERT_NOT( Constructible< constructible_type, b, c, a > );
BOOST_GENERIC_ASSERT_NOT( Constructible< constructible_type, void > );

BOOST_GENERIC_ASSERT( Constructible< int, int > );
BOOST_GENERIC_ASSERT( Constructible< int, char > );

BOOST_GENERIC_ASSERT_NOT( Constructible< void > );
BOOST_GENERIC_ASSERT_NOT( Constructible< void, a > );
BOOST_GENERIC_ASSERT_NOT( Constructible< void, void > );
BOOST_GENERIC_ASSERT_NOT( Constructible< void, void, void > );
