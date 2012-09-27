/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_bit_and.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasBitAnd;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasBitAnd< int, int > );
BOOST_GENERIC_ASSERT( HasBitAnd< short, int > );

BOOST_GENERIC_ASSERT( SameType< HasBitAnd< int, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasBitAnd< short, int >::result_type, int > );

BOOST_GENERIC_ASSERT_NOT( HasBitAnd< int, float > );
BOOST_GENERIC_ASSERT_NOT( HasBitAnd< double, float > );
BOOST_GENERIC_ASSERT_NOT( HasBitAnd< int*, int > );
BOOST_GENERIC_ASSERT_NOT( HasBitAnd< int*, int* > );
BOOST_GENERIC_ASSERT_NOT( HasBitAnd< double, int* > );

struct has_bitand_object
{
  friend void operator &( has_bitand_object, int );
};

BOOST_GENERIC_ASSERT( HasBitAnd< has_bitand_object, int > );

BOOST_GENERIC_ASSERT( SameType< HasBitAnd< has_bitand_object, int >::result_type, void > );

BOOST_GENERIC_ASSERT_NOT( HasBitAnd< int, has_bitand_object > );

BOOST_GENERIC_ASSERT_NOT( HasBitAnd< double, void > );
BOOST_GENERIC_ASSERT_NOT( HasBitAnd< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasBitAnd< void, double > );
