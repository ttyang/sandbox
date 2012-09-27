/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/concepts/default_constructible.hpp>

struct nondefault_constructible_type
{
  nondefault_constructible_type() = delete;
};

using boost::generic::std_concept::DefaultConstructible;

BOOST_GENERIC_ASSERT( DefaultConstructible< int > );

BOOST_GENERIC_ASSERT_NOT( DefaultConstructible< int& > );

BOOST_GENERIC_ASSERT_NOT
( DefaultConstructible< nondefault_constructible_type > );

BOOST_GENERIC_ASSERT_NOT( DefaultConstructible< int[] > );
BOOST_GENERIC_ASSERT_NOT( DefaultConstructible< int() > );
BOOST_GENERIC_ASSERT_NOT( DefaultConstructible< void > );
