/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_bit_xor.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasBitXor;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasBitXor< int, int > );
BOOST_GENERIC_ASSERT( HasBitXor< short, int > );

BOOST_GENERIC_ASSERT( SameType< HasBitXor< int, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasBitXor< short, int >::result_type, int > );

BOOST_GENERIC_ASSERT_NOT( HasBitXor< int, float > );
BOOST_GENERIC_ASSERT_NOT( HasBitXor< double, float > );
BOOST_GENERIC_ASSERT_NOT( HasBitXor< int*, int > );
BOOST_GENERIC_ASSERT_NOT( HasBitXor< int*, int* > );
BOOST_GENERIC_ASSERT_NOT( HasBitXor< double, int* > );

struct has_bitand_object
{
  friend void operator ^( has_bitand_object, int );
};

BOOST_GENERIC_ASSERT( HasBitXor< has_bitand_object, int > );

BOOST_GENERIC_ASSERT( SameType< HasBitXor< has_bitand_object, int >::result_type, void > );

BOOST_GENERIC_ASSERT_NOT( HasBitXor< int, has_bitand_object > );

BOOST_GENERIC_ASSERT_NOT( HasBitXor< double, void > );
BOOST_GENERIC_ASSERT_NOT( HasBitXor< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasBitXor< void, double > );
