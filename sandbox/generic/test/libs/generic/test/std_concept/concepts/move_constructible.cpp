/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/move_constructible.hpp>

#include <boost/generic/assert.hpp>

struct nonmovable_type
{
private:
  nonmovable_type( nonmovable_type&& ) = delete;
};

using boost::generic::std_concept::MoveConstructible;

BOOST_GENERIC_ASSERT( MoveConstructible< int > );

BOOST_GENERIC_ASSERT_NOT( MoveConstructible< nonmovable_type > );
BOOST_GENERIC_ASSERT_NOT( MoveConstructible< void > );

