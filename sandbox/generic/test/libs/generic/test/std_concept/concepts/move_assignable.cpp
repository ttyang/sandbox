/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/move_assignable.hpp>

#include <boost/generic/assert.hpp>

struct nonmove_assignable_type
{
private:
  nonmove_assignable_type& operator =( nonmove_assignable_type&& ) = delete;
};

using boost::generic::std_concept::MoveAssignable;

BOOST_GENERIC_ASSERT( MoveAssignable< int > );

BOOST_GENERIC_ASSERT_NOT( MoveAssignable< nonmove_assignable_type > );
BOOST_GENERIC_ASSERT_NOT( MoveAssignable< void > );

