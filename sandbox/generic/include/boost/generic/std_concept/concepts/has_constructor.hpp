/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_HAS_CONSTRUCTOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_HAS_CONSTRUCTOR_HPP

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <type_traits>
#endif

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/true.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/has_constructor.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.construct]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (HasConstructor)( (typename) T, (typename,,,) Args )
, ( (this(T))( (Args,,,) ) )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_HAS_CONSTRUCTOR_HPP
