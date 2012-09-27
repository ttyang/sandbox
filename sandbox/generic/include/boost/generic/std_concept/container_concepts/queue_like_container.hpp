/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_QUEUE_LIKE_CONTAINER_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_QUEUE_LIKE_CONTAINER_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/container_concepts/back_insertion_container.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/container_concepts/queue_like_container.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [container.concepts.free]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (QueueLikeContainer)( (typename) C ), ( public BackInsertionContainer<C> )
, ( (void)(pop_front)( (C&) ) )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_QUEUE_LIKE_CONTAINER_HPP
