/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/object_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::ObjectType;

BOOST_GENERIC_ASSERT( ObjectType< int > );
BOOST_GENERIC_ASSERT( ObjectType< char > );
BOOST_GENERIC_ASSERT( ObjectType< int* > );
BOOST_GENERIC_ASSERT( ObjectType< int[] > );
BOOST_GENERIC_ASSERT( ObjectType< int[2] > );

struct object_type {};

BOOST_GENERIC_ASSERT( ObjectType< object_type > );

BOOST_GENERIC_ASSERT_NOT( ObjectType< int& > );
BOOST_GENERIC_ASSERT_NOT( ObjectType< void > );
BOOST_GENERIC_ASSERT_NOT( ObjectType< int() > );
