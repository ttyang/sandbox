/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_STACK_LIKE_CONTAINER_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_STACK_LIKE_CONTAINER_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/container_concepts/back_insertion_container.hpp>
#include <boost/generic/std_concept/iterator_concepts/bidirectional_iterator.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/container_concepts/stack_like_container.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [container.concepts.free]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (StackLikeContainer)( (typename) C ), ( public BackInsertionContainer<C> )
, ( (typename BackInsertionContainer<C>::reference)(back)( (C&) ) )
, ( (typename BackInsertionContainer<C>::const_reference)(back)( (const C&) ) )

, ( (void)(pop_back)( (C&) ) )

// TODO support this syntax for requirement-dependent axioms
//, ( requires ( BidirectionalIterator<typename BackInsertionContainer<C>::iterator> )
//      axiom AccessBack(C c) {
//        if (begin(c) != end(c)) back(c) == *(--end(c));
//      }
//  )

, ( axiom BackInsertion(C c, value_type x) {
      x == (push_back(c, x), back(c));
    }
  )

, ( axiom BackRemoval(C c, value_type x) {
      c == (push_back(c, x), pop_back(c), c);
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_STACK_LIKE_CONTAINER_HPP
