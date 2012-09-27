/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_minus.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>
#include <cstddef>

using boost::generic::std_concept::HasMinus;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasMinus< int, int > );
BOOST_GENERIC_ASSERT( HasMinus< short, int > );
BOOST_GENERIC_ASSERT( HasMinus< int, float > );
BOOST_GENERIC_ASSERT( HasMinus< double, float > );
BOOST_GENERIC_ASSERT( HasMinus< int*, int > );
BOOST_GENERIC_ASSERT( HasMinus< int*, int* > );

BOOST_GENERIC_ASSERT( SameType< HasMinus< int, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasMinus< short, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasMinus< int, float >::result_type, float > );
BOOST_GENERIC_ASSERT( SameType< HasMinus< double, float >::result_type, double > );
BOOST_GENERIC_ASSERT( SameType< HasMinus< int*, int >::result_type, int* > );
BOOST_GENERIC_ASSERT( SameType< HasMinus< int*, int* >::result_type, std::ptrdiff_t > );

BOOST_GENERIC_ASSERT_NOT( HasMinus< double, int* > );

struct has_minus_object
{
  friend void operator -( has_minus_object, int );
};

BOOST_GENERIC_ASSERT( HasMinus< has_minus_object, int > );

BOOST_GENERIC_ASSERT( SameType< HasMinus< has_minus_object, int >::result_type, void > );

BOOST_GENERIC_ASSERT_NOT( HasMinus< int, has_minus_object > );
