/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/less_than_comparable.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::LessThanComparable;

BOOST_GENERIC_ASSERT( LessThanComparable< int > );
BOOST_GENERIC_ASSERT( LessThanComparable< int* > );
BOOST_GENERIC_ASSERT( LessThanComparable< void* > );
BOOST_GENERIC_ASSERT( LessThanComparable< float > );

struct less_than_comparable_type {};

bool operator <( less_than_comparable_type, less_than_comparable_type );
bool operator <=( less_than_comparable_type, less_than_comparable_type );
bool operator >( less_than_comparable_type, less_than_comparable_type );
bool operator >=( less_than_comparable_type, less_than_comparable_type );

BOOST_GENERIC_ASSERT( LessThanComparable< less_than_comparable_type > );

struct not_less_than_comparable_type {};

bool operator <( not_less_than_comparable_type, not_less_than_comparable_type );
void operator <=( not_less_than_comparable_type, not_less_than_comparable_type );
bool operator >( not_less_than_comparable_type, not_less_than_comparable_type );
bool operator >=( not_less_than_comparable_type, not_less_than_comparable_type );

BOOST_GENERIC_ASSERT_NOT( LessThanComparable< not_less_than_comparable_type > );
BOOST_GENERIC_ASSERT_NOT( LessThanComparable< void > );
