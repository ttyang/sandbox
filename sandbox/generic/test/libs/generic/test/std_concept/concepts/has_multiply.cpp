/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_multiply.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasMultiply;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasMultiply< int, int > );
BOOST_GENERIC_ASSERT( HasMultiply< short, int > );
BOOST_GENERIC_ASSERT( HasMultiply< int, float > );
BOOST_GENERIC_ASSERT( HasMultiply< double, float > );

BOOST_GENERIC_ASSERT( SameType< HasMultiply< int, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasMultiply< short, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasMultiply< int, float >::result_type, float > );
BOOST_GENERIC_ASSERT( SameType< HasMultiply< double, float >::result_type, double > );

BOOST_GENERIC_ASSERT_NOT( HasMultiply< int*, int > );
BOOST_GENERIC_ASSERT_NOT( HasMultiply< int*, int* > );
BOOST_GENERIC_ASSERT_NOT( HasMultiply< double, int* > );

struct has_multiply_object
{
  friend void operator *( has_multiply_object, int );
};

BOOST_GENERIC_ASSERT( HasMultiply< has_multiply_object, int > );

BOOST_GENERIC_ASSERT( SameType< HasMultiply< has_multiply_object, int >::result_type, void > );

BOOST_GENERIC_ASSERT_NOT( HasMultiply< int, has_multiply_object > );

BOOST_GENERIC_ASSERT_NOT( HasMultiply< double, void > );
BOOST_GENERIC_ASSERT_NOT( HasMultiply< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasMultiply< void, double > );
