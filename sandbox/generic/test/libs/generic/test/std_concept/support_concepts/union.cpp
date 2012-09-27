/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/union.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::Union;

union union_type
{
  int a;
  float b;
};

BOOST_GENERIC_ASSERT( Union< union_type > );

class class_type {};
struct struct_type {};

BOOST_GENERIC_ASSERT_NOT( Union< class_type > );
BOOST_GENERIC_ASSERT_NOT( Union< struct_type > );
BOOST_GENERIC_ASSERT_NOT( Union< int > );
BOOST_GENERIC_ASSERT_NOT( Union< void > );
BOOST_GENERIC_ASSERT_NOT( Union< int[] > );
BOOST_GENERIC_ASSERT_NOT( Union< class_type() > );
BOOST_GENERIC_ASSERT_NOT( Union< class_type& > );
