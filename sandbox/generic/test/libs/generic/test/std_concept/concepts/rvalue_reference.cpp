/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/rvalue_reference.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::RvalueReference;

BOOST_GENERIC_ASSERT( RvalueReference< int&& > );
BOOST_GENERIC_ASSERT( RvalueReference< int const&& > );

BOOST_GENERIC_ASSERT_NOT( RvalueReference< void > );
BOOST_GENERIC_ASSERT_NOT( RvalueReference< int > );
BOOST_GENERIC_ASSERT_NOT( RvalueReference< int& > );
