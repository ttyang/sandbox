/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/trivially_destructible.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::TriviallyDestructible;

BOOST_GENERIC_ASSERT( TriviallyDestructible< int > );
BOOST_GENERIC_ASSERT( TriviallyDestructible< int* > );
BOOST_GENERIC_ASSERT( TriviallyDestructible< int& > );
// BOOST_GENERIC_ASSERT( TriviallyDestructible< int[4] > ); // TODO Figure out if this should actually succeed

struct trivially_destructible {};
struct default_trivially_destructible
{
  ~default_trivially_destructible() = default;
};

BOOST_GENERIC_ASSERT( TriviallyDestructible< trivially_destructible > );
BOOST_GENERIC_ASSERT( TriviallyDestructible< default_trivially_destructible > );

struct not_trivially_destructible
{
  ~not_trivially_destructible();
};

BOOST_GENERIC_ASSERT_NOT( TriviallyDestructible< not_trivially_destructible > );

BOOST_GENERIC_ASSERT_NOT( TriviallyDestructible< int() > );
BOOST_GENERIC_ASSERT_NOT( TriviallyDestructible< void > );
