/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_divide.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasDivide;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasDivide< int, int > );
BOOST_GENERIC_ASSERT( HasDivide< short, int > );
BOOST_GENERIC_ASSERT( HasDivide< int, float > );
BOOST_GENERIC_ASSERT( HasDivide< double, float > );

BOOST_GENERIC_ASSERT( SameType< HasDivide< int, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasDivide< short, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasDivide< int, float >::result_type, float > );
BOOST_GENERIC_ASSERT( SameType< HasDivide< double, float >::result_type, double > );

BOOST_GENERIC_ASSERT_NOT( HasDivide< int*, int > );
BOOST_GENERIC_ASSERT_NOT( HasDivide< int*, int* > );
BOOST_GENERIC_ASSERT_NOT( HasDivide< double, int* > );

struct has_divide_object
{
  friend void operator /( has_divide_object, int );
};

BOOST_GENERIC_ASSERT( HasDivide< has_divide_object, int > );

BOOST_GENERIC_ASSERT( SameType< HasDivide< has_divide_object, int >::result_type, void > );

BOOST_GENERIC_ASSERT_NOT( HasDivide< int, has_divide_object > );

BOOST_GENERIC_ASSERT_NOT( HasDivide< double, void > );
BOOST_GENERIC_ASSERT_NOT( HasDivide< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasDivide< void, double > );
