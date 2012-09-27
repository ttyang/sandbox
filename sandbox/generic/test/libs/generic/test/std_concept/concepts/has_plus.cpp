/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_plus.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasPlus;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasPlus< int, int > );
BOOST_GENERIC_ASSERT( HasPlus< short, int > );
BOOST_GENERIC_ASSERT( HasPlus< int, float > );
BOOST_GENERIC_ASSERT( HasPlus< double, float > );
BOOST_GENERIC_ASSERT( HasPlus< int*, int > );

BOOST_GENERIC_ASSERT( SameType< HasPlus< int, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasPlus< short, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasPlus< int, float >::result_type, float > );
BOOST_GENERIC_ASSERT( SameType< HasPlus< double, float >::result_type, double > );
BOOST_GENERIC_ASSERT( SameType< HasPlus< int*, int >::result_type, int* > );

BOOST_GENERIC_ASSERT_NOT( HasPlus< int*, int* > );
BOOST_GENERIC_ASSERT_NOT( HasPlus< double, int* > );

struct has_plus_object
{
  friend void operator +( has_plus_object, int );
};

BOOST_GENERIC_ASSERT( HasPlus< has_plus_object, int > );

BOOST_GENERIC_ASSERT( SameType< HasPlus< has_plus_object, int >::result_type, void > );

BOOST_GENERIC_ASSERT_NOT( HasPlus< int, has_plus_object > );

BOOST_GENERIC_ASSERT_NOT( HasPlus< double, void > );
BOOST_GENERIC_ASSERT_NOT( HasPlus< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasPlus< void, double > );
