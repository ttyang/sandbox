/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/trivially_default_constructible.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::TriviallyDefaultConstructible;

BOOST_GENERIC_ASSERT( TriviallyDefaultConstructible< int > );
BOOST_GENERIC_ASSERT( TriviallyDefaultConstructible< int* > );
//BOOST_GENERIC_ASSERT( TriviallyDefaultConstructible< int[4] > ); // TODO figure out if this should succeed

struct trivially_constructible {};
struct default_trivially_constructible
{
  default_trivially_constructible() = default;
};

BOOST_GENERIC_ASSERT( TriviallyDefaultConstructible< trivially_constructible > );
BOOST_GENERIC_ASSERT( TriviallyDefaultConstructible< default_trivially_constructible > );

struct not_trivially_constructible
{
  not_trivially_constructible();
};

BOOST_GENERIC_ASSERT_NOT( TriviallyDefaultConstructible< not_trivially_constructible > );

BOOST_GENERIC_ASSERT_NOT( TriviallyDefaultConstructible< int& > );
BOOST_GENERIC_ASSERT_NOT( TriviallyDefaultConstructible< int() > );
BOOST_GENERIC_ASSERT_NOT( TriviallyDefaultConstructible< void > );
