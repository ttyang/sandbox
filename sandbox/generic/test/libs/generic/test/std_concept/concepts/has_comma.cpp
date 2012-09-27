/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_comma.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasComma;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasComma< int, float > );
BOOST_GENERIC_ASSERT( SameType< HasComma< int, float >::result_type, float const& > );

BOOST_GENERIC_ASSERT_NOT( HasComma< void, int > );
BOOST_GENERIC_ASSERT_NOT( HasComma< int, void > );
BOOST_GENERIC_ASSERT_NOT( HasComma< void, void > );

struct overloaded_comma_type {};

float operator,( overloaded_comma_type, int );

overloaded_comma_type const& operator,( overloaded_comma_type, overloaded_comma_type ) = delete;

BOOST_GENERIC_ASSERT( HasComma< overloaded_comma_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasComma< overloaded_comma_type, int >::result_type, float > );

BOOST_GENERIC_ASSERT( HasComma< int, overloaded_comma_type > );
BOOST_GENERIC_ASSERT( SameType< HasComma< int, overloaded_comma_type >::result_type, overloaded_comma_type const& > );

BOOST_GENERIC_ASSERT_NOT( HasComma< overloaded_comma_type, overloaded_comma_type > );
