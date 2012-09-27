/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_ARITHMETIC_LIKE_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_ARITHMETIC_LIKE_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <cstdint>
#endif

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/concepts/regular.hpp>
#include <boost/generic/std_concept/concepts/less_than_comparable.hpp>
#include <boost/generic/std_concept/concepts/has_unary_plus.hpp>
#include <boost/generic/std_concept/concepts/has_negate.hpp>
#include <boost/generic/std_concept/concepts/has_plus.hpp>
#include <boost/generic/std_concept/concepts/has_minus.hpp>
#include <boost/generic/std_concept/concepts/has_multiply.hpp>
#include <boost/generic/std_concept/concepts/has_divide.hpp>
#include <boost/generic/std_concept/concepts/has_preincrement.hpp>
#include <boost/generic/std_concept/concepts/has_postincrement.hpp>
#include <boost/generic/std_concept/concepts/has_predecrement.hpp>
#include <boost/generic/std_concept/concepts/has_postdecrement.hpp>
#include <boost/generic/std_concept/concepts/has_plus_assign.hpp>
#include <boost/generic/std_concept/concepts/has_minus_assign.hpp>
#include <boost/generic/std_concept/concepts/has_multiply_assign.hpp>
#include <boost/generic/std_concept/concepts/has_divide_assign.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/arithmetic_like.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.arithmetic]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (ArithmeticLike)( (typename) T )
, ( public (Regular<T>) (LessThanComparable<T>) (HasUnaryPlus<T>) (HasNegate<T>)
           (HasPlus<T, T>) (HasMinus<T, T>) (HasMultiply<T, T>) (HasDivide<T, T>)
           (HasPreincrement<T>) (HasPostincrement<T>) (HasPredecrement<T>)
           (HasPostdecrement<T>) (HasPlusAssign<T, const T&>)
           (HasMinusAssign<T, const T&>) (HasMultiplyAssign<T, const T&>)
           (HasDivideAssign<T, const T&>)
  )
, ( explicit (this(T))( (::std::intmax_t) ) )
, ( explicit (this(T))( (::std::uintmax_t) ) )
, ( explicit (this(T))( (long double) ) )
, ( requires Convertible<typename HasUnaryPlus<T>::result_type, T> )
, ( requires Convertible<typename HasNegate<T>::result_type, T> )
, ( requires Convertible<typename HasPlus<T, T>::result_type, T> )
, ( requires Convertible<typename HasMinus<T, T>::result_type, T> )
, ( requires Convertible<typename HasMultiply<T, T>::result_type, T> )
, ( requires Convertible<typename HasDivide<T, T>::result_type, T> )
, ( requires SameType<typename HasPreincrement<T>::result_type, T&> )
, ( requires SameType<typename HasPostincrement<T>::result_type, T> )
, ( requires SameType<typename HasPredecrement<T>::result_type, T&> )
, ( requires SameType<typename HasPostdecrement<T>::result_type, T> )
, ( requires SameType<typename HasPlusAssign<T, const T&>::result_type, T&> )
, ( requires SameType<typename HasMinusAssign<T, const T&>::result_type, T&> )
, ( requires SameType<typename HasMultiplyAssign<T,const T&>::result_type, T&> )
, ( requires SameType<typename HasDivideAssign<T, const T&>::result_type, T&> )
)

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( float ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( double ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( long double ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( signed char ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( short int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( long int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( long long int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( unsigned char ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( unsigned short int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( unsigned int ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::ArithmeticLike)( unsigned long int ) )

BOOST_GENERIC_CONCEPT_MAP
((boost::generic::std_concept::ArithmeticLike)( unsigned long long int ))

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

// These are included in order to bring in the concept maps for built-in types
//#include <boost/generic/std_concept/concepts/floating_point_like.hpp>
//#include <boost/generic/std_concept/concepts/integral_like.hpp>

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_ARITHMETIC_LIKE_HPP
