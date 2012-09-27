/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/polymorphic_class.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::PolymorphicClass;

struct polymorphic_class { virtual void foo(); };
struct other_polymorphic_class : polymorphic_class {};

BOOST_GENERIC_ASSERT( PolymorphicClass< polymorphic_class > );
BOOST_GENERIC_ASSERT( PolymorphicClass< other_polymorphic_class > );

struct nonpolymorphic_class {};

BOOST_GENERIC_ASSERT_NOT( PolymorphicClass< nonpolymorphic_class > );
BOOST_GENERIC_ASSERT_NOT( PolymorphicClass< int > );
BOOST_GENERIC_ASSERT_NOT( PolymorphicClass< void > );
