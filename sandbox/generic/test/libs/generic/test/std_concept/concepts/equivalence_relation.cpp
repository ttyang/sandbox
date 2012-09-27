/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/equivalence_relation.hpp>

#include <boost/generic/assert.hpp>

struct a {}; struct b {}; struct c {}; struct d {};

struct equivalence_relation_model_a_b
{
  bool operator ()( a, a ) const;
  bool operator ()( b, b ) const;
  d operator ()( c, c ) const;
};

using boost::generic::std_concept::EquivalenceRelation;

BOOST_GENERIC_ASSERT( EquivalenceRelation< equivalence_relation_model_a_b, a > );
BOOST_GENERIC_ASSERT( EquivalenceRelation< equivalence_relation_model_a_b, b > );

BOOST_GENERIC_ASSERT_NOT( EquivalenceRelation< equivalence_relation_model_a_b, c > );
BOOST_GENERIC_ASSERT_NOT( EquivalenceRelation< equivalence_relation_model_a_b, d > );
BOOST_GENERIC_ASSERT_NOT( EquivalenceRelation< equivalence_relation_model_a_b, void > );
BOOST_GENERIC_ASSERT_NOT( EquivalenceRelation< void, void > );
BOOST_GENERIC_ASSERT_NOT( EquivalenceRelation< void, a > );
