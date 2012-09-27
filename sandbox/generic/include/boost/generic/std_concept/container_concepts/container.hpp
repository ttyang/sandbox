/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_CONTAINER_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_CONTAINER_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/concepts/unsigned_integral_like.hpp>
#include <boost/generic/std_concept/iterator_concepts/forward_iterator.hpp>
#include <boost/generic/std_concept/support_concepts/integral_type.hpp>
#include <boost/generic/std_concept/support_concepts/object_type.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/container_concepts/container.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [container.concepts.free]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (Container)( (typename) C )
, ( (ObjectType) value_type         , typename C::value_type )
, ( typename reference              , typename C::reference )
, ( typename const_reference        , typename C::const_reference )
, ( (UnsignedIntegralLike) size_type, typename C::size_type )

, ( (ForwardIterator) iterator )
, ( (ForwardIterator) const_iterator )

, ( requires Convertible<reference, const_reference> )
, ( requires Convertible<reference, const value_type&> )
, ( requires Convertible<reference, const value_type&> )
, ( requires Convertible<const_reference, const value_type&> )
, ( requires Convertible<iterator, const_iterator> )
, ( requires SameType<typename ForwardIterator<iterator>::value_type, value_type> )
, ( requires SameType<typename ForwardIterator<const_iterator>::value_type, value_type> )
, ( requires Convertible<typename ForwardIterator<iterator>::reference, reference> )
, ( requires Convertible<typename ForwardIterator<const_iterator>::reference, const_reference> )
, ( requires SameType<typename ForwardIterator<iterator>::difference_type,
                      typename ForwardIterator<const_iterator>::difference_type> )
, ( requires IntegralType<size_type> )
, ( requires Convertible<typename ForwardIterator<iterator>::difference_type, size_type> )

, ( (iterator)(begin)( (C&) ) )
, ( (const_iterator)(begin)( (const C&)) )
, ( (iterator)(end)( (C&) ) )
, ( (const_iterator)(end)( (const C&) ) )
, ( (const_iterator)(cbegin)( (const C&) c ), { return begin(c); } )
, ( (const_iterator)(cend)( (const C&) c ), { return end(c); } )
, ( (reference)(front)( (C&) c ), { return *begin(c); } )

, ( axiom AccessFront(C c) {
      if (begin(c) != end(c)) front(c) == *begin(c);
    }
  )

, ( axiom ContainerSize(C c) {
      (begin(c) == end(c)) == empty(c);
      (begin(c) != end(c)) == (size(c) > 0);
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_CONTAINER_HPP
