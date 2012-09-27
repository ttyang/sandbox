/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/concepts/has_assign.hpp>
#include <boost/generic/std_concept/concepts/has_dereference.hpp>
#include <boost/generic/std_concept/iterator_concepts/iterator.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/iterator_concepts/output_iterator.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// TODO make sure that this is supposed to be nd auto concept

// [output.iterators]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (OutputIterator)( (typename) X, (typename) Value )
, ( requires Iterator<X> )
, ( typename reference, typename Iterator<X>::reference )
, ( typename postincrement_result, typename Iterator<X>::postincrement_result )
, ( requires SameType< reference, typename Iterator<X>::reference > )
, ( requires SameType< postincrement_result
                     , typename Iterator<X>::postincrement_result
                     >
  )
, ( requires Convertible< postincrement_result, const X& > )
, ( requires HasAssign< reference, Value > )
, ( requires HasAssign
             < typename HasDereference<postincrement_result>::result_type
             , Value
             >
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP
