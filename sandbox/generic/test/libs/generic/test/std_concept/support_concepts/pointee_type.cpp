/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/pointee_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::PointeeType;

struct struct_type {};

BOOST_GENERIC_ASSERT( PointeeType< struct_type > );
BOOST_GENERIC_ASSERT( PointeeType< int > );
BOOST_GENERIC_ASSERT( PointeeType< void > );
BOOST_GENERIC_ASSERT( PointeeType< int[4] > );
BOOST_GENERIC_ASSERT( PointeeType< int() > );

BOOST_GENERIC_ASSERT_NOT( PointeeType< int& > );
BOOST_GENERIC_ASSERT_NOT( PointeeType< int&& > );
