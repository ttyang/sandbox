/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_MEMBER_CONTAINER_HPP
#define BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_MEMBER_CONTAINER_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/concepts/unsigned_integral_like.hpp>
#include <boost/generic/std_concept/iterator_concepts/forward_iterator.hpp>
#include <boost/generic/std_concept/support_concepts/integral_type.hpp>
#include <boost/generic/std_concept/support_concepts/object_type.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/container_concepts/member_container.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [container.concepts.member]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (MemberContainer)( (typename) C )
, ( (ObjectType) value_type         , typename C::value_type )
, ( typename reference              , typename C::reference )
, ( typename const_reference        , typename C::const_reference )
, ( (UnsignedIntegralLike) size_type, typename C::size_type )

// TODO make this auto deduction work from the return type of begin
//, ( (ForwardIterator) iterator )
//, ( (ForwardIterator) const_iterator )

// NOTE: the standard doesn't have these defaults (they're deduced)
, ( (ForwardIterator) iterator      , typename C::iterator )
, ( (ForwardIterator) const_iterator, typename C::const_iterator )

, ( requires Convertible<reference, const_reference> )
, ( requires Convertible<reference, const value_type&> )
, ( requires Convertible<const_reference, const value_type&> )
, ( requires Convertible<iterator, const_iterator> )
, ( requires SameType<typename ForwardIterator<iterator>::value_type, value_type> )
, ( requires SameType<typename ForwardIterator<const_iterator>::value_type, value_type> )
, ( requires Convertible<typename ForwardIterator<iterator>::reference, reference> )
, ( requires Convertible<typename ForwardIterator<const_iterator>::reference, const_reference> )
, ( requires SameType<typename ForwardIterator<iterator>::difference_type,
                      typename ForwardIterator<const_iterator>::difference_type>
  )
, ( requires IntegralType<size_type> )
, ( requires Convertible<typename ForwardIterator<iterator>::difference_type, size_type> )

, ( (bool)(this(C) empty)() const, { return this->begin() == this->end(); } )
, ( (size_type)(this(C) size)() const, { return ::std::distance(this->begin(), this->end()); } )

, ( (iterator)(this(C) begin)() )
, ( (const_iterator)(this(C) begin)() const )
, ( (iterator)(this(C) end)() )
, ( (const_iterator)(this(C) end)() const )
, ( (const_iterator)(this(C) cbegin)() const, { return this->begin(); } )
, ( (const_iterator)(this(C) cend)() const, { return this->end(); } )
, ( (reference)(this(C) front)(), { return *this->begin(); } )
, ( (const_reference)(this(C) front)() const, { return *this->begin(); } )

, ( axiom MemberAccessFront(C c) {
      if (c.begin() != c.end()) c.front() == *c.begin();
    }
  )

, ( axiom MemberContainerSize(C c) {
      (c.begin() == c.end()) == c.empty();
      (c.begin() != c.end()) == (c.size() > 0);
    }
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

// TODO concept maps

#endif // BOOST_GENERIC_STD_CONCEPT_CONTAINER_CONCEPTS_MEMBER_CONTAINER_HPP
