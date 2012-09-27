/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/concepts/equality_comparable.hpp>

struct nondefault_equality_comparable
{
};

using boost::generic::std_concept::EqualityComparable;

BOOST_GENERIC_ASSERT( EqualityComparable< int > );

BOOST_GENERIC_ASSERT( EqualityComparable< int& > );

BOOST_GENERIC_ASSERT( EqualityComparable< int* > );

BOOST_GENERIC_ASSERT_NOT
( EqualityComparable< nondefault_equality_comparable > );


struct not_equal_isnt_bool_equality_comparable
{
  friend bool operator ==( not_equal_isnt_bool_equality_comparable, not_equal_isnt_bool_equality_comparable );
  friend void operator!=( not_equal_isnt_bool_equality_comparable, not_equal_isnt_bool_equality_comparable );
};

BOOST_GENERIC_ASSERT_NOT( EqualityComparable< not_equal_isnt_bool_equality_comparable > );

BOOST_GENERIC_ASSERT_NOT( EqualityComparable< void > );
