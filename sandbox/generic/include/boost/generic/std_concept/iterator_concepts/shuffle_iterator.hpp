/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_SHUFFLE_ITERATOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_SHUFFLE_ITERATOR_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/constructible.hpp>
#include <boost/generic/std_concept/concepts/has_assign.hpp>
#include <boost/generic/std_concept/concepts/has_swap.hpp>
#include <boost/generic/std_concept/concepts/move_assignable.hpp>
#include <boost/generic/std_concept/concepts/move_constructible.hpp>
#include <boost/generic/std_concept/concepts/rvalue_of.hpp>
#include <boost/generic/std_concept/concepts/swappable.hpp>
#include <boost/generic/std_concept/iterator_concepts/forward_iterator.hpp>
#include <boost/generic/std_concept/iterator_concepts/output_iterator.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/iterator_concepts/shuffle_iterator.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [shuffle.iterators]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (ShuffleIterator)( (typename) X )
, ( requires ForwardIterator<X> )
, ( requires OutputIterator
             < X
             , typename RvalueOf
               < typename ForwardIterator<X>::value_type >::type
             >
  )
, ( requires OutputIterator
             < X
             , typename RvalueOf< typename ForwardIterator<X>::reference >::type
             >
  )
, ( requires Constructible
             < typename ForwardIterator<X>::value_type
             , typename RvalueOf< typename ForwardIterator<X>::reference >::type
             >
  )
, ( requires MoveConstructible< typename ForwardIterator<X>::value_type > )
, ( requires MoveAssignable< typename ForwardIterator<X>::value_type > )
, ( requires Swappable< typename ForwardIterator<X>::value_type > )
, ( requires HasAssign
             < typename ForwardIterator<X>::value_type
             , typename RvalueOf< typename ForwardIterator<X>::reference >::type
             >
  )
, ( requires HasSwap< typename ForwardIterator<X>::reference
                    , typename ForwardIterator<X>::reference
                    >
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_ITERATOR_CONCEPTS_SHUFFLE_ITERATOR_HPP
