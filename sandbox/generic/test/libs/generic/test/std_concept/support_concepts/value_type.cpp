/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/value_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::ValueType;

BOOST_GENERIC_ASSERT( ValueType< int > );
BOOST_GENERIC_ASSERT( ValueType< int* > );

struct value_type {};

BOOST_GENERIC_ASSERT( ValueType< value_type > );

struct not_value_type { virtual void make_abstract() = 0; };

BOOST_GENERIC_ASSERT_NOT( ValueType< not_value_type > );
BOOST_GENERIC_ASSERT_NOT( ValueType< void > );
BOOST_GENERIC_ASSERT_NOT( ValueType< int() > );
