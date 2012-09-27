/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/derived_from.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::DerivedFrom;

BOOST_GENERIC_ASSERT_NOT( DerivedFrom< int, int > );

struct simple_type {};

BOOST_GENERIC_ASSERT( DerivedFrom< simple_type, simple_type > );

struct public_base_type {};
struct private_base_type {};
struct protected_base_type {};

struct left_base_type : public_base_type {};
struct right_base_type : public_base_type {};

struct derived_from_type : public_base_type {};
struct private_derived_from_type : private public_base_type {};
struct protected_derived_from_type : protected public_base_type {};

struct ambiguous_derived_from_type : left_base_type, right_base_type {};

struct private_public_derived_from_type : left_base_type, private right_base_type {};

BOOST_GENERIC_ASSERT( DerivedFrom< derived_from_type, public_base_type > );
BOOST_GENERIC_ASSERT_NOT( DerivedFrom< private_derived_from_type, public_base_type > );
BOOST_GENERIC_ASSERT_NOT( DerivedFrom< protected_derived_from_type, public_base_type > );
BOOST_GENERIC_ASSERT_NOT( DerivedFrom< ambiguous_derived_from_type, public_base_type > );
BOOST_GENERIC_ASSERT_NOT( DerivedFrom< private_public_derived_from_type, public_base_type > );

BOOST_GENERIC_ASSERT_NOT( DerivedFrom< void, public_base_type > );
BOOST_GENERIC_ASSERT_NOT( DerivedFrom< private_public_derived_from_type, void > );
BOOST_GENERIC_ASSERT_NOT( DerivedFrom< void, void > );
