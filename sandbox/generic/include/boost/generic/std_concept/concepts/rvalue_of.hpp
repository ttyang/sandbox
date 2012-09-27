/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONCEPTS_RVALUE_OF_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONCEPTS_RVALUE_OF_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/concepts/explicitly_convertible.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/concepts/rvalue_of.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [concept.transform]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (RvalueOf)( (typename) T )
, ( typename type, T&& )
, ( requires ExplicitlyConvertible<T&, type> )
//, ( requires Convertible<T&&, type> ) // NOTE: This is commented out because it implies implicit conversion from T& to T&&, which correctly fails. Standard error??const T&
, ( requires ExplicitlyConvertible<T&&, type> ) // NOTE: This is not in the standard and replaces the above line.
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONCEPTS_RVALUE_OF_HPP
