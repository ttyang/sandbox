/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONTAINER_CONTAINER_CONCEPTS_EMPLACEMENT_CONTAINER_HPP
#define BOOST_GENERIC_STD_CONTAINER_CONTAINER_CONCEPTS_EMPLACEMENT_CONTAINER_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/concepts/constructible.hpp>
#include <boost/generic/std_concept/container_concepts/container.hpp>
#include <boost/generic/std_concept/container_concepts/insertion_container.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/container_concepts/emplacement_container.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [container.concepts.free]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (EmplacementContainer)( (typename) C, (typename,,,) Args ), ( public Container<C> )
, ( (typename Container<C>::iterator)(emplace)( (C&) c, (typename Container<C>::const_iterator) position, (Args&&,,,) args) )

// TODO support this
//, ( requires ( Constructible<typename Container<C>::value_type, Args...> )
//      axiom Emplacement(C c, const_iterator position, Args... args) {
//        typename Container<C>::value_type(args...) == *emplace(c, position, args...);
//      }
//  )
//
//, ( requires ( InsertionContainer<C>, Constructible<typename Container<C>::value_type, Args...> )
//      axiom EmplacementPushEquivalence(C c, const_iterator position, Args... args) {
//        *emplace(c, position, args...) == *insert(c, position, value_type(args...));
//    }
//  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONTAINER_CONTAINER_CONCEPTS_EMPLACEMENT_CONTAINER_HPP
