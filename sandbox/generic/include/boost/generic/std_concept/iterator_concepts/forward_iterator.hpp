/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_FORWARD_ITERATOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_FORWARD_ITERATOR_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/concepts/regular.hpp>
#include <boost/generic/std_concept/iterator_concepts/input_iterator.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/iterator_concepts/forward_iterator.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [forward.iterators]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (ForwardIterator)( (typename) X ), ( public (InputIterator<X>) (Regular<X>) )
, ( requires Convertible< typename InputIterator<X>::postincrement_result
                        , const X&
                        >
  )
, ( axiom MultiPass(X a, X b) {
      if (a == b) *a == *b;
      if (a == b) ++a == ++b;
    }
  )
)

BOOST_GENERIC_CONCEPT_MAP
( ( template ( (class) T ) )
, ( boost::generic::std_concept::ForwardIterator )( T* )
, ( typedef T value_type )
, ( typedef std::ptrdiff_t difference_type )
, ( typedef T& reference )
, ( typedef T* pointer )
, ( typedef T* postincrement_result )
, ( typedef T* postdecrement_result )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_FORWARD_ITERATOR_HPP
