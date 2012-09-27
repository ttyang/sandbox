/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/swappable.hpp>

#include <boost/generic/assert.hpp>

struct swappable_type {};

char swap( swappable_type, swappable_type );

using boost::generic::std_concept::Swappable;

BOOST_GENERIC_ASSERT( Swappable< swappable_type > );

BOOST_GENERIC_ASSERT_NOT( Swappable< void > );
BOOST_GENERIC_ASSERT_NOT( Swappable< int() > );

// TODO figure out a nice way to test these
//BOOST_GENERIC_ASSERT( Swappable< int, int > );
