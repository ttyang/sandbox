/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_assign.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

struct a {}; struct b {};

struct assignable_type
{
  a operator =( assignable_type ) const;
  b operator =( a ) const;
};

using boost::generic::std_concept::HasAssign;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasAssign< assignable_type, assignable_type > );
BOOST_GENERIC_ASSERT( SameType< HasAssign< assignable_type, assignable_type >::result_type, a > );

BOOST_GENERIC_ASSERT( HasAssign< assignable_type, a > );
BOOST_GENERIC_ASSERT( SameType< HasAssign< assignable_type, a >::result_type, b > );

BOOST_GENERIC_ASSERT( HasAssign< int, int > );
BOOST_GENERIC_ASSERT( SameType< HasAssign< int, int >::result_type, int& > );

BOOST_GENERIC_ASSERT_NOT( HasAssign< assignable_type, b > );
BOOST_GENERIC_ASSERT_NOT( HasAssign< a, b > );
