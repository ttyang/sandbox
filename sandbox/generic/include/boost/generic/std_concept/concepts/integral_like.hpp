/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_INTEGRAL_LIKE_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_INTEGRAL_LIKE_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/concepts/arithmetic_like.hpp>
#include <boost/generic/std_concept/concepts/has_complement.hpp>
#include <boost/generic/std_concept/concepts/has_modulus.hpp>
#include <boost/generic/std_concept/concepts/has_bit_and.hpp>
#include <boost/generic/std_concept/concepts/has_bit_xor.hpp>
#include <boost/generic/std_concept/concepts/has_bit_or.hpp>
#include <boost/generic/std_concept/concepts/has_left_shift.hpp>
#include <boost/generic/std_concept/concepts/has_right_shift.hpp>
#include <boost/generic/std_concept/concepts/has_modulus_assign.hpp>
#include <boost/generic/std_concept/concepts/has_left_shift_assign.hpp>
#include <boost/generic/std_concept/concepts/has_right_shift_assign.hpp>
#include <boost/generic/std_concept/concepts/has_bit_and_assign.hpp>
#include <boost/generic/std_concept/concepts/has_bit_xor_assign.hpp>
#include <boost/generic/std_concept/concepts/has_bit_or_assign.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/integral_like.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.arithmetic]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (IntegralLike)( (typename) T )
, ( public (ArithmeticLike<T>) (HasComplement<T>) (HasModulus<T, T>)
           (HasBitAnd<T, T>) (HasBitXor<T, T>) (HasBitOr<T, T>) (HasLeftShift<T, T>)
           (HasRightShift<T, T>) (HasModulusAssign<T, const T&>)
           (HasLeftShiftAssign<T, const T&>) (HasRightShiftAssign<T, const T&>)
           (HasBitAndAssign<T, const T&>) (HasBitXorAssign<T, const T&>)
           (HasBitOrAssign<T, const T&>)
  )
, ( requires Convertible<typename HasComplement<T>::result_type, T> )
, ( requires Convertible<typename HasModulus<T, T>::result_type, T> )
, ( requires Convertible<typename HasBitAnd<T, T>::result_type, T> )
, ( requires Convertible<typename HasBitXor<T, T>::result_type, T> )
, ( requires Convertible<typename HasBitOr<T, T>::result_type, T> )
, ( requires Convertible<typename HasLeftShift<T, T>::result_type, T> )
, ( requires Convertible<typename HasRightShift<T, T>::result_type, T> )
, ( requires SameType<typename HasModulusAssign<T, const T&>::result_type, T&> )
, ( requires SameType<typename HasLeftShiftAssign<T,const T&>::result_type,T&> )
, ( requires SameType<typename HasRightShiftAssign<T,const T&>::result_type,T&>)
, ( requires SameType<typename HasBitAndAssign<T, const T&>::result_type, T&> )
, ( requires SameType<typename HasBitXorAssign<T, const T&>::result_type, T&> )
, ( requires SameType<typename HasBitOrAssign<T, const T&>::result_type, T&> )
)

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::IntegralLike)( signed char ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::IntegralLike)( short int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::IntegralLike)( int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::IntegralLike)( long int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::IntegralLike)( long long int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::IntegralLike)( unsigned char ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::IntegralLike)( unsigned short int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::IntegralLike)( unsigned int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::IntegralLike)( unsigned long int ) )

BOOST_GENERIC_CONCEPT_MAP
((boost::generic::std_concept::IntegralLike)( unsigned long long int ))

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

// ToDo: Possibly make maps for bool, etc. (not mentioned in standard)

// These are included in order to bring in the concept maps for built-in types
//#include <boost/generic/std_concept/concepts/signed_integral_like.hpp>
//#include <boost/generic/std_concept/concepts/unsigned_integral_like.hpp>

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_INTEGRAL_LIKE_HPP
