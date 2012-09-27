/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_MEMBER_STACK_LIKE_CONTAINER_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_MEMBER_STACK_LIKE_CONTAINER_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/container_concepts/member_back_insertion_container.hpp>
#include <boost/generic/std_concept/iterator_concepts/bidirectional_iterator.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/container_concepts/member_stack_like_container.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [container.concepts.member]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (MemberStackLikeContainer)( (typename) C ), ( public MemberBackInsertionContainer<C> )
, ( (typename MemberBackInsertionContainer<C>::reference)(this(C) back)() )
, ( (typename MemberBackInsertionContainer<C>::const_reference)(this(C) back)() const )
, ( (void)(this(C) pop_back)() )

// TODO support this
//, ( requires ( BidirectionalIterator<typename MemberBackInsertionContainer<C>::iterator> )
//      axiom MemberAccessBack(C c) {
//        if (c.begin() != c.end()) c.back() == *(--c.end());
//      }
//  )

, ( axiom MemberBackInsertion(C c, typename MemberBackInsertionContainer<C>::value_type x) {
      x == (c.push_back(x), c.back());
    }
  )

, ( axiom MemberBackRemoval(C c, typename MemberBackInsertionContainer<C>::value_type x) {
      c == (c.push_back(x), c.pop_back(), c);
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_MEMBER_STACK_LIKE_CONTAINER_HPP
