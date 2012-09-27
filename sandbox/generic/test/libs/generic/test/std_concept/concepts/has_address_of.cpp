/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_address_of.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

struct no_address_of_object
{
  no_address_of_object* operator&() = delete;
};

struct a {};

struct overloaded_address_of_object
{
  a operator&();
};

using boost::generic::std_concept::HasAddressOf;

BOOST_GENERIC_ASSERT( HasAddressOf< int > );
BOOST_GENERIC_ASSERT( HasAddressOf< float > );
BOOST_GENERIC_ASSERT( HasAddressOf< int() > );
BOOST_GENERIC_ASSERT( HasAddressOf< int[] > );
BOOST_GENERIC_ASSERT( HasAddressOf< int[4] > );
BOOST_GENERIC_ASSERT( HasAddressOf< overloaded_address_of_object > );

BOOST_GENERIC_ASSERT_NOT( HasAddressOf< no_address_of_object > );
BOOST_GENERIC_ASSERT_NOT( HasAddressOf< void > );

using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( SameType< HasAddressOf< int >::result_type, int* > );
BOOST_GENERIC_ASSERT( SameType< HasAddressOf< float >::result_type, float* > );
BOOST_GENERIC_ASSERT( SameType< HasAddressOf< int() >::result_type, int(*)() > );
BOOST_GENERIC_ASSERT( SameType< HasAddressOf< int[] >::result_type, int (*)[] > );
BOOST_GENERIC_ASSERT( SameType< HasAddressOf< int[4] >::result_type, int(*)[4] > );
BOOST_GENERIC_ASSERT( SameType< HasAddressOf< overloaded_address_of_object >::result_type, a > );
