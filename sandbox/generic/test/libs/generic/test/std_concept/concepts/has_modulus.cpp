/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_modulus.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasModulus;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasModulus< int, int > );
BOOST_GENERIC_ASSERT( HasModulus< short, int > );

BOOST_GENERIC_ASSERT( SameType< HasModulus< int, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasModulus< short, int >::result_type, int > );

BOOST_GENERIC_ASSERT_NOT( HasModulus< int, float > );
BOOST_GENERIC_ASSERT_NOT( HasModulus< double, float > );
BOOST_GENERIC_ASSERT_NOT( HasModulus< int*, int > );
BOOST_GENERIC_ASSERT_NOT( HasModulus< int*, int* > );
BOOST_GENERIC_ASSERT_NOT( HasModulus< double, int* > );

struct has_modulus_object
{
  friend void operator %( has_modulus_object, int );
};

BOOST_GENERIC_ASSERT( HasModulus< has_modulus_object, int > );

BOOST_GENERIC_ASSERT( SameType< HasModulus< has_modulus_object, int >::result_type, void > );

BOOST_GENERIC_ASSERT_NOT( HasModulus< int, has_modulus_object > );

BOOST_GENERIC_ASSERT_NOT( HasModulus< double, void > );
BOOST_GENERIC_ASSERT_NOT( HasModulus< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasModulus< void, double > );
