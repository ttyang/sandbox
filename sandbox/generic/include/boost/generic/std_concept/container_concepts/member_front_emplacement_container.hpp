/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_MEMBER_FRONT_EMPLACEMENT_CONTAINER_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_MEMBER_FRONT_EMPLACEMENT_CONTAINER_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/constructible.hpp>
#include <boost/generic/std_concept/container_concepts/member_container.hpp>
#include <boost/generic/std_concept/container_concepts/member_front_insertion_container.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/container_concepts/member_front_emplacement_container.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [container.concepts.member]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (MemberFrontEmplacementContainer)( (typename) C, (typename,,,) Args ), ( public MemberContainer<C> )
, ( (void)(this(C)  emplace_front)( (Args&&,,,) args ) )

// TODO support this
//, ( requires ( Constructible<typename MemberContainer<C>::value_type, Args...> )
//      axiom MemberFrontEmplacement(C c, Args... args) {
//        value_type(args...) == (c.emplace_front(args...), c.front());
//      }
//  )
//
//, ( requires ( MemberFrontInsertionContainer<C>, Constructible<value_type, Args...> )
//      axiom MemberFrontEmplacementPushEquivalence(C c, Args... args) {
//        (c.emplace_front(args...), c.front()) == (c.push_front(value_type(args...)), c.front());
//      }
//  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_MEMBER_FRONT_EMPLACEMENT_CONTAINER_HPP
