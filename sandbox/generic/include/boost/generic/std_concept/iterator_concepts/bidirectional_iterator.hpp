/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/concepts/has_dereference.hpp>
#include <boost/generic/std_concept/concepts/move_constructible.hpp>
#include <boost/generic/std_concept/iterator_concepts/forward_iterator.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/iterator_concepts/bidirectional_iterator.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [bidirectional.iterators]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (BidirectionalIterator)( (typename) X ), ( public ForwardIterator<X> )
, ( (MoveConstructible) postdecrement_result )
, ( requires HasDereference<postdecrement_result> )
, ( requires Convertible
             < typename HasDereference<postdecrement_result>::result_type
             , const typename ForwardIterator<X>::value_type&
             >
  )
, ( requires Convertible<postdecrement_result, const X&> )
, ( (X&)(operator predecrement)( (X&) ) )
, ( (postdecrement_result)(operator postdecrement)( (X&), (int) ) )
)

BOOST_GENERIC_CONCEPT_MAP
( ( template ( (class) T ) )
, ( boost::generic::std_concept::BidirectionalIterator )( T* )
, ( typedef T value_type )
, ( typedef std::ptrdiff_t difference_type )
, ( typedef T& reference )
, ( typedef T* pointer )
, ( typedef T* postincrement_result )
, ( typedef T* postdecrement_result )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP
