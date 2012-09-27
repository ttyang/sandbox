/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_ITERATOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_ITERATOR_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/concepts/has_dereference.hpp>
#include <boost/generic/std_concept/concepts/move_constructible.hpp>
#include <boost/generic/std_concept/concepts/semiregular.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/iterator_concepts/iterator.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [iterator.iterators]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (Iterator)( (typename) X )
, ( public Semiregular<X> )
, ( (MoveConstructible) reference, typename X::reference )
, ( (MoveConstructible) postincrement_result )
, ( requires HasDereference< postincrement_result > )
, ( (reference)(operator dereference)( (X&) ) )
, ( (reference)(operator dereference)( (X&&) ) )
, ( (X&)(operator preincrement)( (X&) ) )
, ( (postincrement_result)(operator postincrement)( (X&), (int) ) )
)

BOOST_GENERIC_CONCEPT_MAP
( ( template ( (class) T ) )
, ( boost::generic::std_concept::Iterator )( T* )
, ( typedef T value_type )
, ( typedef std::ptrdiff_t difference_type )
, ( typedef T& reference )
, ( typedef T* pointer )
, ( typedef T* postincrement_result )
, ( typedef T* postdecrement_result )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

// These are included for the standard concept maps of Iterator refinements
//#include <boost/generic/std_concept/iterator_concepts/bidirectional_iterator.hpp>
//#include <boost/generic/std_concept/iterator_concepts/forward_iterator.hpp>
//#include <boost/generic/std_concept/iterator_concepts/input_iterator.hpp>
//#include <boost/generic/std_concept/iterator_concepts/output_iterator.hpp>
//#include <boost/generic/std_concept/iterator_concepts/random_access_iterator.hpp>
//#include <boost/generic/std_concept/iterator_concepts/shuffle_iterator.hpp>

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS

// ToDo: Move this to a separate header
#include <boost/generic/config/std_lib.hpp>

#if BOOST_GENERIC_STD_LIB_IS_KNOWN()

#include <boost/generic/concept_map.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/logical/compl.hpp>

#include <boost/generic/detail/std_forward_decl.hpp>
#include <cstddef>

#include BOOST_GENERIC_DETAIL_FORWARD_DECL_HEADER( array_iterator )
#include BOOST_GENERIC_DETAIL_FORWARD_DECL_HEADER( deque_iterator )
//#include BOOST_GENERIC_DETAIL_FORWARD_DECL_HEADER( vector_bool_iterator )
#include BOOST_GENERIC_DETAIL_FORWARD_DECL_HEADER( vector_iterator )

// ToDo: Handle bitset types

#if !BOOST_GENERIC_CONFIG_STD_LIB_ARRAY_ITERATOR_IS_POINTER()

// array iterator
BOOST_GENERIC_CONCEPT_MAP
( BOOST_GENERIC_DETAIL_FORWARD_DECL_PARAMS( array_iterator )
, ( boost::generic::std_concept::Iterator )
  ( BOOST_GENERIC_DETAIL_FORWARD_DECL_NAME( array_iterator ) )
)

#endif

#if    !BOOST_GENERIC_CONFIG_STD_LIB_VECTOR_ITERATOR_IS_ARRAY_ITERATOR()       \
    && !BOOST_GENERIC_CONFIG_STD_LIB_VECTOR_ITERATOR_IS_POINTER()

// vector iterator
BOOST_GENERIC_CONCEPT_MAP
( BOOST_GENERIC_DETAIL_FORWARD_DECL_PARAMS( vector_iterator )
, ( boost::generic::std_concept::Iterator )
  ( BOOST_GENERIC_DETAIL_FORWARD_DECL_NAME( vector_iterator ) )
)

#endif

// deque iterator
BOOST_GENERIC_CONCEPT_MAP
( BOOST_GENERIC_DETAIL_FORWARD_DECL_PARAMS( deque_iterator )
, ( boost::generic::std_concept::Iterator )
  ( BOOST_GENERIC_DETAIL_FORWARD_DECL_NAME( deque_iterator ) )
)

// vector< bool > iterator
//BOOST_GENERIC_CONCEPT_MAP
//( BOOST_GENERIC_DETAIL_FORWARD_DECL_PARAMS( vector_bool_iterator )
//  BOOST_PP_COMMA_IF
//  ( BOOST_PP_COMPL
//    ( BOOST_GENERIC_DETAIL_IS_EMPTY
//      ( BOOST_GENERIC_DETAIL_FORWARD_DECL_PARAMS( vector_bool_iterator ) )
//    )
//  )
//  ( boost::generic::std_concept::Iterator )
//  ( BOOST_GENERIC_DETAIL_FORWARD_DECL_NAME( vector_bool_iterator ) )
//)

#else

BOOST_GENERIC_ASSERT_STD_LIB_IS_NOT_SUPPORTED()

#endif

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_ITERATOR_HPP
