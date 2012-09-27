/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONTAINER_CONTAINER_CONCEPTS_MEMBER_EMPLACEMENT_CONTAINER_HPP
#define BOOST_GENERIC_STD_CONTAINER_CONTAINER_CONCEPTS_MEMBER_EMPLACEMENT_CONTAINER_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/constructible.hpp>
#include <boost/generic/std_concept/container_concepts/member_insertion_container.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/container_concepts/member_emplacement_container.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [container.concepts.member]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (MemberEmplacementContainer)( (typename) C, (typename,,,) Args ), ( public MemberInsertionContainer<C> )
, ( (void)(this(C) emplace)( (typename MemberInsertionContainer<C>::const_iterator) position, (Args&&,,,) args ) )

// TODO support this NOTE the standard has a redundant MemberInsertionContainer requirement on the second conditional axiom
//, ( requires ( Constructible<typename MemberInsertionContainer<C>::value_type, Args...> )
//      axiom MemberEmplacement(C c, typename MemberInsertionContainer<C>::const_iterator position, Args... args) {
//        typename MemberInsertionContainer<C>::value_type(args...) == *c.emplace(position, args...);
//      }
//  )
//, ( requires ( MemberInsertionContainer<C>, Constructible<typename MemberInsertionContainer<C>::value_type, Args...> )
//      axiom MemberEmplacementPushEquivalence(C c, typename MemberInsertionContainer<C>::const_iterator position, Args... args) {
//        *c.emplace(position, args...) == *c.insert(position, typename MemberInsertionContainer<C>::value_type(args...));
//      }
//  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONTAINER_CONTAINER_CONCEPTS_MEMBER_EMPLACEMENT_CONTAINER_HPP
