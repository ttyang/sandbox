/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/same_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::SameType;

struct a {};

BOOST_GENERIC_ASSERT( SameType< int, int > );
BOOST_GENERIC_ASSERT( SameType< a, a > );
BOOST_GENERIC_ASSERT( SameType< void, void > );

BOOST_GENERIC_ASSERT_NOT( SameType< void, void* > );
BOOST_GENERIC_ASSERT_NOT( SameType< int, a > );
BOOST_GENERIC_ASSERT_NOT( SameType< int, const int > );
