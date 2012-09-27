/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_RANGE_HPP
#define BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_RANGE_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/concept_map.hpp>

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <boost/generic/std_concept/iterator_concepts/input_iterator.hpp>
#include <type_traits>
#endif

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/iterator_concepts/range.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [iterator.concepts.range]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (Range)( (typename) T )
, ( (InputIterator) iterator )
, ( (iterator)(begin)( (T&) ) )
, ( (iterator)(end)( (T&) ) )
)

BOOST_GENERIC_CONCEPT_MAP
( ( template ( (class) T, (std::size_t) N ) )
, (boost::generic::std_concept::Range)( T[N] )
, ( typedef T* iterator )
, ( (iterator)(begin)( (typename std::add_lvalue_reference<T[N]>::type) a ), {
      return a;
    }
  )
, ( (iterator)(end)( (typename std::add_lvalue_reference<T[N]>::type) a ), {
      return a + N;
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_RANGE_HPP
