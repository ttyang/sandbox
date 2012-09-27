/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/lvalue_reference.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::LvalueReference;

BOOST_GENERIC_ASSERT( LvalueReference< int& > );
BOOST_GENERIC_ASSERT( LvalueReference< int const& > );

BOOST_GENERIC_ASSERT_NOT( LvalueReference< void > );
BOOST_GENERIC_ASSERT_NOT( LvalueReference< int > );
BOOST_GENERIC_ASSERT_NOT( LvalueReference< int&& > );
