/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_modulus_assign.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

struct a {}; struct b {};

struct modulus_assign_type
{
  a operator %=( modulus_assign_type ) const;
  b operator %=( a ) const;
};

using boost::generic::std_concept::HasModulusAssign;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( HasModulusAssign< modulus_assign_type, modulus_assign_type > );
BOOST_GENERIC_ASSERT( SameType< HasModulusAssign< modulus_assign_type, modulus_assign_type >::result_type, a > );

BOOST_GENERIC_ASSERT( HasModulusAssign< modulus_assign_type, a > );
BOOST_GENERIC_ASSERT( SameType< HasModulusAssign< modulus_assign_type, a >::result_type, b > );

BOOST_GENERIC_ASSERT( HasModulusAssign< int, int > );
BOOST_GENERIC_ASSERT( SameType< HasModulusAssign< int, int >::result_type, int& > );

BOOST_GENERIC_ASSERT_NOT( HasModulusAssign< modulus_assign_type, b > );
BOOST_GENERIC_ASSERT_NOT( HasModulusAssign< a, b > );
BOOST_GENERIC_ASSERT_NOT( HasModulusAssign< float, float > );
