/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_MEMORY_CONCEPTS_HAS_ALLOCATOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_MEMORY_CONCEPTS_HAS_ALLOCATOR_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/memory_concepts/allocator.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/memory_concepts/has_allocator.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [allocator.element.concepts]
BOOST_GENERIC_AUTO_CONCEPT
( (HasAllocatorType)( (typename) T )
, ( typename allocator_type, typename T::allocator_type )
, ( requires Allocator<allocator_type> )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_MEMORY_CONCEPTS_HAS_ALLOCATOR_HPP
