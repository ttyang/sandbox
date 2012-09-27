/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_right_shift.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasRightShift;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasRightShift< int, int > );
BOOST_GENERIC_ASSERT( HasRightShift< short, int > );

BOOST_GENERIC_ASSERT( SameType< HasRightShift< int, int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasRightShift< short, int >::result_type, int > );

BOOST_GENERIC_ASSERT_NOT( HasRightShift< int, float > );
BOOST_GENERIC_ASSERT_NOT( HasRightShift< double, float > );
BOOST_GENERIC_ASSERT_NOT( HasRightShift< int*, int > );
BOOST_GENERIC_ASSERT_NOT( HasRightShift< int*, int* > );
BOOST_GENERIC_ASSERT_NOT( HasRightShift< double, int* > );

struct has_bitand_object
{
  friend void operator >>( has_bitand_object, int );
};

BOOST_GENERIC_ASSERT( HasRightShift< has_bitand_object, int > );

BOOST_GENERIC_ASSERT( SameType< HasRightShift< has_bitand_object, int >::result_type, void > );

BOOST_GENERIC_ASSERT_NOT( HasRightShift< int, has_bitand_object > );

BOOST_GENERIC_ASSERT_NOT( HasRightShift< double, void > );
BOOST_GENERIC_ASSERT_NOT( HasRightShift< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasRightShift< void, double > );
