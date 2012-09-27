/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/rvalue_of.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::RvalueOf;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( RvalueOf< int > );
BOOST_GENERIC_ASSERT( SameType< RvalueOf< int >::type, int&& > );

BOOST_GENERIC_ASSERT( RvalueOf< int const > );
BOOST_GENERIC_ASSERT( SameType< RvalueOf< int const >::type, int const&& > );

BOOST_GENERIC_ASSERT( RvalueOf< int& > );
BOOST_GENERIC_ASSERT( SameType< RvalueOf< int& >::type, int& > );

BOOST_GENERIC_ASSERT( RvalueOf< int&& > );
BOOST_GENERIC_ASSERT( SameType< RvalueOf< int&& >::type, int&& > );

BOOST_GENERIC_ASSERT( RvalueOf< int const&& > );
BOOST_GENERIC_ASSERT( SameType< RvalueOf< int const&& >::type, int const&& > );

BOOST_GENERIC_ASSERT_NOT( RvalueOf< void > );
