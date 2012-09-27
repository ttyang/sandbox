/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/scalar_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::ScalarType;

BOOST_GENERIC_ASSERT( ScalarType< int > );
BOOST_GENERIC_ASSERT( ScalarType< char > );
BOOST_GENERIC_ASSERT( ScalarType< float > );
BOOST_GENERIC_ASSERT( ScalarType< int* > );

struct struct_type {};

BOOST_GENERIC_ASSERT( ScalarType< int(struct_type::*) > );
BOOST_GENERIC_ASSERT( ScalarType< int(struct_type::*)() > );

enum enumeration_type { a = 0 };

BOOST_GENERIC_ASSERT( ScalarType< enumeration_type > );

BOOST_GENERIC_ASSERT_NOT( ScalarType< void > );
BOOST_GENERIC_ASSERT_NOT( ScalarType< void() > );
BOOST_GENERIC_ASSERT_NOT( ScalarType< int& > );
BOOST_GENERIC_ASSERT_NOT( ScalarType< int[4] > );
BOOST_GENERIC_ASSERT_NOT( ScalarType< int[] > );
