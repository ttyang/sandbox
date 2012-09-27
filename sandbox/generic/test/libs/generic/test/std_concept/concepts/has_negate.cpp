/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_negate.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasNegate;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasNegate< int > );
BOOST_GENERIC_ASSERT( HasNegate< long > );
BOOST_GENERIC_ASSERT( HasNegate< short > );
BOOST_GENERIC_ASSERT( HasNegate< unsigned > );

BOOST_GENERIC_ASSERT( SameType< HasNegate< int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasNegate< long >::result_type, long > );
BOOST_GENERIC_ASSERT( SameType< HasNegate< short >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasNegate< unsigned >::result_type, unsigned > );

struct non_negate_object {};

BOOST_GENERIC_ASSERT_NOT( HasNegate< non_negate_object > );

struct negate_result {};

struct negate_object
{
  negate_result operator -() const;
};

BOOST_GENERIC_ASSERT( HasNegate< negate_object > );

BOOST_GENERIC_ASSERT
( SameType
  < HasNegate< negate_object >::result_type, negate_result >
);

struct negate_void_object
{
  void operator -() const;
};

BOOST_GENERIC_ASSERT( HasNegate< negate_void_object > );

BOOST_GENERIC_ASSERT
( SameType< HasNegate< negate_void_object >::result_type, void > );

