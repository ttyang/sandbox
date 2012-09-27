/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/class_type.hpp>

#include <boost/generic/assert.hpp>

class class_type;
struct struct_type;

using boost::generic::std_concept::ClassType;

union union_type
{
  int a;
  float b;
};

BOOST_GENERIC_ASSERT( ClassType< class_type > );
BOOST_GENERIC_ASSERT( ClassType< struct_type > );
BOOST_GENERIC_ASSERT( ClassType< union_type > );

BOOST_GENERIC_ASSERT_NOT( ClassType< int > );
BOOST_GENERIC_ASSERT_NOT( ClassType< void > );
BOOST_GENERIC_ASSERT_NOT( ClassType< int[] > );
BOOST_GENERIC_ASSERT_NOT( ClassType< class_type() > );
BOOST_GENERIC_ASSERT_NOT( ClassType< class_type& > );
