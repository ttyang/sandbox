/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_UNION_HPP
#define BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_UNION_HPP

#include <boost/generic/auto_concept.hpp>

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <boost/generic/std_concept/concepts/true.hpp>
#include <boost/generic/std_concept/support_concepts/class_type.hpp>
#include <boost/generic/std_concept/support_concepts/value_type.hpp>
#include <type_traits>
#endif

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/support_concepts/union.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.support]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (Union)( (typename) T ), ( public (ClassType< T >) (ValueType< T >) )
, ( requires True< std::is_union< T >::value > )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPTS_SUPPORT_CONCEPTS_UNION_HPP
