/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/class.hpp>

#include <boost/generic/assert.hpp>

class class_type;
struct struct_type;

using boost::generic::std_concept::Class;

BOOST_GENERIC_ASSERT( Class< class_type > );
BOOST_GENERIC_ASSERT( Class< struct_type > );

union union_type
{
  int a;
  float b;
};

BOOST_GENERIC_ASSERT_NOT( Class< int > );
BOOST_GENERIC_ASSERT_NOT( Class< union_type > );
BOOST_GENERIC_ASSERT_NOT( Class< void > );
BOOST_GENERIC_ASSERT_NOT( Class< int[] > );
BOOST_GENERIC_ASSERT_NOT( Class< class_type() > );
BOOST_GENERIC_ASSERT_NOT( Class< class_type& > );
