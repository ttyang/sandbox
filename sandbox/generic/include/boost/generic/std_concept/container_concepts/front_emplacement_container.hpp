/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_FRONT_EMPLACEMENT_CONTAINER_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_FRONT_EMPLACEMENT_CONTAINER_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/concepts/constructible.hpp>
#include <boost/generic/std_concept/container_concepts/container.hpp>
#include <boost/generic/std_concept/container_concepts/front_insertion_container.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/container_concepts/front_emplacement_container.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [container.concepts.free]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (FrontEmplacementContainer)( (typename) C, (typename,,,) Args ), ( public Container<C> )
, ( (void)(emplace_front)( (C&) c, (Args&&,,,) args) )

, ( requires Constructible<typename Container<C>::value_type, Args...> )
, ( axiom FrontEmplacement(C c, Args... args) {
      value_type(args...) == (emplace_front(c, args...), front(c));
    }
  )

, ( requires FrontInsertionContainer<C> )
, ( requires Constructible<typename Container<C>::value_type, Args...> )
, ( axiom FrontEmplacementPushEquivalence(C c, Args... args) {
      (emplace_front(c, args...), front(c)) == (push_front(c, value_type(args...)), front(c));
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_FRONT_EMPLACEMENT_CONTAINER_HPP
