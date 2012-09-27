/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_subscript.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>
#include <cstddef>

using boost::generic::std_concept::HasSubscript;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasSubscript< int[], std::ptrdiff_t > );
BOOST_GENERIC_ASSERT( SameType< HasSubscript< int[], std::ptrdiff_t >::result_type, int& > );

BOOST_GENERIC_ASSERT( HasSubscript< int[1], std::ptrdiff_t > );
BOOST_GENERIC_ASSERT( SameType< HasSubscript< int[1], std::ptrdiff_t >::result_type, int& > );

BOOST_GENERIC_ASSERT( HasSubscript< int*, std::ptrdiff_t > );
BOOST_GENERIC_ASSERT( SameType< HasSubscript< int*, std::ptrdiff_t >::result_type, int& > );

struct subscriptable_type
{
  char operator []( float ) const;
};

BOOST_GENERIC_ASSERT( HasSubscript< subscriptable_type, float > );
BOOST_GENERIC_ASSERT( SameType< HasSubscript< subscriptable_type, float >::result_type, char > );

struct no_subscript_type
{
};

BOOST_GENERIC_ASSERT_NOT( HasSubscript< no_subscript_type, float > );
BOOST_GENERIC_ASSERT_NOT( HasSubscript< int[], float > );
BOOST_GENERIC_ASSERT_NOT( HasSubscript< int, void > );
BOOST_GENERIC_ASSERT_NOT( HasSubscript< void, void > );
BOOST_GENERIC_ASSERT_NOT( HasSubscript< void, int > );
