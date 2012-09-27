/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_unary_plus.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasUnaryPlus;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasUnaryPlus< int > );
BOOST_GENERIC_ASSERT( HasUnaryPlus< long > );
BOOST_GENERIC_ASSERT( HasUnaryPlus< short > );
BOOST_GENERIC_ASSERT( HasUnaryPlus< unsigned > );

BOOST_GENERIC_ASSERT( SameType< HasUnaryPlus< int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasUnaryPlus< long >::result_type, long > );
BOOST_GENERIC_ASSERT( SameType< HasUnaryPlus< short >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasUnaryPlus< unsigned >::result_type, unsigned > );

struct non_unary_plus_object {};

BOOST_GENERIC_ASSERT_NOT( HasUnaryPlus< non_unary_plus_object > );

struct unary_plus_result {};

struct unary_plus_object
{
  unary_plus_result operator +() const;
};

BOOST_GENERIC_ASSERT( HasUnaryPlus< unary_plus_object > );

BOOST_GENERIC_ASSERT
( SameType
  < HasUnaryPlus< unary_plus_object >::result_type, unary_plus_result >
);

struct unary_plus_void_object
{
  void operator +() const;
};

BOOST_GENERIC_ASSERT( HasUnaryPlus< unary_plus_void_object > );

BOOST_GENERIC_ASSERT
( SameType< HasUnaryPlus< unary_plus_void_object >::result_type, void > );
