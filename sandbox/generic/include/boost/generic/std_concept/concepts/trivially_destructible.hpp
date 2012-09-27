/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_TRIVIALLY_DESTRUCTIBLE_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_TRIVIALLY_DESTRUCTIBLE_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/nothrow_destructible.hpp>
#include <boost/generic/std_concept/concepts/true.hpp>

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <boost/type_traits/has_trivial_destructor.hpp>
#endif

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/trivially_destructible.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.destruct]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (TriviallyDestructible)( (typename) T )
, ( public NothrowDestructible< T > )
 , ( requires True< has_trivial_destructor< T >::value > )
// , ( requires True< std::is_trivially_destructible< T >::value > )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif


#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_TRIVIALLY_DESTRUCTIBLE_HPP
