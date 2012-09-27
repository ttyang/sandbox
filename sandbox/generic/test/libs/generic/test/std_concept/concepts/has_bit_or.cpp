/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_bit_or.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasBitOr;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasBitOr< int, int > );
BOOST_GENERIC_ASSERT( HasBitOr< short, int > );

BOOST_GENERIC_ASSERT( SameType< HasBitOr< int, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasBitOr< short, int >::result_type, int > );

BOOST_GENERIC_ASSERT_NOT( HasBitOr< int, float > );
BOOST_GENERIC_ASSERT_NOT( HasBitOr< double, float > );
BOOST_GENERIC_ASSERT_NOT( HasBitOr< int*, int > );
BOOST_GENERIC_ASSERT_NOT( HasBitOr< int*, int* > );
BOOST_GENERIC_ASSERT_NOT( HasBitOr< double, int* > );

struct has_bitor_object
{
  friend void operator |( has_bitor_object, int );
};

BOOST_GENERIC_ASSERT( HasBitOr< has_bitor_object, int > );

BOOST_GENERIC_ASSERT( SameType< HasBitOr< has_bitor_object, int >::result_type, void > );

BOOST_GENERIC_ASSERT_NOT( HasBitOr< int, has_bitor_object > );

BOOST_GENERIC_ASSERT_NOT( HasBitOr< double, void > );
BOOST_GENERIC_ASSERT_NOT( HasBitOr< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasBitOr< void, double > );
