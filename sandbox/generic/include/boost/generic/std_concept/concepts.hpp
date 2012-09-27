/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS

// [concept.transform]
#include <boost/generic/std_concept/concepts/identity_of.hpp>
#include <boost/generic/std_concept/concepts/rvalue_of.hpp>

// [concept.true]
#include <boost/generic/std_concept/concepts/true.hpp>

// [concept.classify]
#include <boost/generic/std_concept/concepts/lvalue_reference.hpp>
#include <boost/generic/std_concept/concepts/rvalue_reference.hpp>

// [concept.operator]
#include <boost/generic/std_concept/concepts/has_plus.hpp>
#include <boost/generic/std_concept/concepts/has_minus.hpp>
#include <boost/generic/std_concept/concepts/has_multiply.hpp>
#include <boost/generic/std_concept/concepts/has_divide.hpp>
#include <boost/generic/std_concept/concepts/has_modulus.hpp>
#include <boost/generic/std_concept/concepts/has_unary_plus.hpp>
#include <boost/generic/std_concept/concepts/has_negate.hpp>
#include <boost/generic/std_concept/concepts/has_less.hpp>
#include <boost/generic/std_concept/concepts/has_greater.hpp>
#include <boost/generic/std_concept/concepts/has_less_equal.hpp>
#include <boost/generic/std_concept/concepts/has_greater_equal.hpp>
#include <boost/generic/std_concept/concepts/has_equal_to.hpp>
#include <boost/generic/std_concept/concepts/has_not_equal_to.hpp>
#include <boost/generic/std_concept/concepts/has_logical_and.hpp>
#include <boost/generic/std_concept/concepts/has_logical_or.hpp>
#include <boost/generic/std_concept/concepts/has_logical_not.hpp>
#include <boost/generic/std_concept/concepts/has_bit_and.hpp>
#include <boost/generic/std_concept/concepts/has_bit_or.hpp>
#include <boost/generic/std_concept/concepts/has_bit_xor.hpp>
#include <boost/generic/std_concept/concepts/has_complement.hpp>
#include <boost/generic/std_concept/concepts/has_left_shift.hpp>
#include <boost/generic/std_concept/concepts/has_right_shift.hpp>
#include <boost/generic/std_concept/concepts/has_dereference.hpp>
#include <boost/generic/std_concept/concepts/has_address_of.hpp>
#include <boost/generic/std_concept/concepts/has_subscript.hpp>
#include <boost/generic/std_concept/concepts/callable.hpp>
#include <boost/generic/std_concept/concepts/has_assign.hpp>
#include <boost/generic/std_concept/concepts/has_plus_assign.hpp>
#include <boost/generic/std_concept/concepts/has_minus_assign.hpp>
#include <boost/generic/std_concept/concepts/has_multiply_assign.hpp>
#include <boost/generic/std_concept/concepts/has_divide_assign.hpp>
#include <boost/generic/std_concept/concepts/has_modulus_assign.hpp>
#include <boost/generic/std_concept/concepts/has_bit_and_assign.hpp>
#include <boost/generic/std_concept/concepts/has_bit_or_assign.hpp>
#include <boost/generic/std_concept/concepts/has_bit_xor_assign.hpp>
#include <boost/generic/std_concept/concepts/has_left_shift_assign.hpp>
#include <boost/generic/std_concept/concepts/has_right_shift_assign.hpp>
#include <boost/generic/std_concept/concepts/has_preincrement.hpp>
#include <boost/generic/std_concept/concepts/has_postincrement.hpp>
#include <boost/generic/std_concept/concepts/has_predecrement.hpp>
#include <boost/generic/std_concept/concepts/has_postdecrement.hpp>
#include <boost/generic/std_concept/concepts/has_comma.hpp>

// [concept.predicate]
#include <boost/generic/std_concept/concepts/predicate.hpp>

// [concept.comparison]
#include <boost/generic/std_concept/concepts/less_than_comparable.hpp>
#include <boost/generic/std_concept/concepts/equality_comparable.hpp>
#include <boost/generic/std_concept/concepts/strict_weak_order.hpp>
#include <boost/generic/std_concept/concepts/equivalence_relation.hpp>

// [concept.construct]
#include <boost/generic/std_concept/concepts/has_constructor.hpp>
#include <boost/generic/std_concept/concepts/constructible.hpp>
#include <boost/generic/std_concept/concepts/default_constructible.hpp>
#include <boost/generic/std_concept/concepts/trivially_default_constructible.hpp>

// [concept.destruct]
#include <boost/generic/std_concept/concepts/has_destructor.hpp>
#include <boost/generic/std_concept/concepts/has_virtual_destructor.hpp>
#include <boost/generic/std_concept/concepts/nothrow_destructible.hpp>
#include <boost/generic/std_concept/concepts/trivially_destructible.hpp>

// [concept.copymove]
#include <boost/generic/std_concept/concepts/move_constructible.hpp>
#include <boost/generic/std_concept/concepts/copy_constructible.hpp>
#include <boost/generic/std_concept/concepts/trivially_copy_constructible.hpp>
#include <boost/generic/std_concept/concepts/move_assignable.hpp>
#include <boost/generic/std_concept/concepts/copy_assignable.hpp>
#include <boost/generic/std_concept/concepts/trivially_copy_assignable.hpp>
#include <boost/generic/std_concept/concepts/has_swap.hpp>
#include <boost/generic/std_concept/concepts/swappable.hpp>

// [concept.memory]
#include <boost/generic/std_concept/concepts/free_store_allocatable.hpp>

// [concept.regular]
#include <boost/generic/std_concept/concepts/semiregular.hpp>
#include <boost/generic/std_concept/concepts/regular.hpp>

// [concept.convertible]
#include <boost/generic/std_concept/concepts/explicitly_convertible.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>

// [concept.arithmetic]
#include <boost/generic/std_concept/concepts/arithmetic_like.hpp>
#include <boost/generic/std_concept/concepts/integral_like.hpp>
#include <boost/generic/std_concept/concepts/signed_integral_like.hpp>
#include <boost/generic/std_concept/concepts/unsigned_integral_like.hpp>
#include <boost/generic/std_concept/concepts/floating_point_like.hpp>

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS
