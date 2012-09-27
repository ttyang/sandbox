/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_complement.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasComplement;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasComplement< int > );
BOOST_GENERIC_ASSERT( HasComplement< long > );
BOOST_GENERIC_ASSERT( HasComplement< short > );
BOOST_GENERIC_ASSERT( HasComplement< unsigned > );

BOOST_GENERIC_ASSERT( SameType< HasComplement< int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasComplement< long >::result_type, long > );
BOOST_GENERIC_ASSERT( SameType< HasComplement< short >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasComplement< unsigned >::result_type, unsigned > );

struct non_complement_object {};

BOOST_GENERIC_ASSERT_NOT( HasComplement< non_complement_object > );

BOOST_GENERIC_ASSERT_NOT( HasComplement< float > );
BOOST_GENERIC_ASSERT_NOT( HasComplement< double > );
BOOST_GENERIC_ASSERT_NOT( HasComplement< void > );

struct complement_result {};

struct complement_object
{
  complement_result operator ~() const;
};

BOOST_GENERIC_ASSERT( HasComplement< complement_object > );

BOOST_GENERIC_ASSERT
( SameType
  < HasComplement< complement_object >::result_type, complement_result >
);

struct complement_void_object
{
  void operator ~() const;
};

BOOST_GENERIC_ASSERT( HasComplement< complement_void_object > );

BOOST_GENERIC_ASSERT
( SameType< HasComplement< complement_void_object >::result_type, void > );
