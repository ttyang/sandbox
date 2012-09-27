/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_INPUT_ITERATOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_INPUT_ITERATOR_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/concepts/equality_comparable.hpp>
#include <boost/generic/std_concept/concepts/has_dereference.hpp>
#include <boost/generic/std_concept/concepts/move_constructible.hpp>
#include <boost/generic/std_concept/concepts/signed_integral_like.hpp>
#include <boost/generic/std_concept/concepts/has_dereference.hpp>
#include <boost/generic/std_concept/iterator_concepts/iterator.hpp>
#include <boost/generic/std_concept/support_concepts/integral_type.hpp>
#include <boost/generic/std_concept/support_concepts/object_type.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/iterator_concepts/input_iterator.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [input.iterators]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (InputIterator)( (typename) X ), ( public (Iterator<X>) (EqualityComparable<X>) )
, ( (ObjectType) value_type, typename X::value_type )
, ( (MoveConstructible) pointer, typename X::pointer )
, ( (SignedIntegralLike) difference_type, typename X::difference_type )
, ( requires IntegralType< difference_type > )
, ( requires Convertible< typename Iterator<X>::reference, const value_type &> )
, ( requires Convertible< pointer, const value_type* > )
, ( requires Convertible
             < typename HasDereference
               < typename Iterator<X>::postincrement_result >::result_type
             , const value_type&
             >
  )
, ( (pointer)(operator arrow)( (const X&) ) )
)

BOOST_GENERIC_CONCEPT_MAP
( ( template ( (class) T ) )
, ( boost::generic::std_concept::InputIterator )( T* )
, ( typedef T value_type )
, ( typedef std::ptrdiff_t difference_type )
, ( typedef T& reference )
, ( typedef T* pointer )
, ( typedef T* postincrement_result )
, ( typedef T* postdecrement_result )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_INPUT_ITERATOR_HPP
