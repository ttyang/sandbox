/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_FLOATING_POINT_LIKE_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_FLOATING_POINT_LIKE_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/concept_map.hpp>

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <boost/generic/std_concept/concepts/arithmetic_like.hpp>
#endif

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/floating_point_like.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.arithmetic]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (FloatingPointLike)( (typename) T )
, ( public ArithmeticLike<T> )
)

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::FloatingPointLike)( float ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::FloatingPointLike)( double ) )

BOOST_GENERIC_CONCEPT_MAP
( (boost::generic::std_concept::FloatingPointLike)( long double ) )

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_FLOATING_POINT_LIKE_HPP
