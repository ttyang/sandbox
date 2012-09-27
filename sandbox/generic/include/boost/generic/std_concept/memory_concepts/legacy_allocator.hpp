/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_MEMORY_CONCEPTS_LEGACY_ALLOCATOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_MEMORY_CONCEPTS_LEGACY_ALLOCATOR_HPP

#include <boost/generic/auto_concept.hpp>
#include <boost/generic/std_concept/concepts/default_constructible.hpp>
#include <boost/generic/std_concept/concepts/copy_constructible.hpp>
#include <boost/generic/std_concept/concepts/equality_comparable.hpp>
#include <boost/generic/std_concept/concepts/has_dereference.hpp>
#include <boost/generic/std_concept/concepts/unsigned_integral_like.hpp>
#include <boost/generic/std_concept/concepts/signed_integral_like.hpp>
#include <boost/generic/std_concept/concepts/has_destructor.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/iterator_concepts/random_access_iterator.hpp>
#include <boost/generic/std_concept/support_concepts/object_type.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>
#include <boost/generic/std_concept/support_concepts/integral_type.hpp>

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/memory_concepts/legacy_allocator.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [allocator.concepts.legacy]
BOOST_GENERIC_AUTO_CONCEPT
( ( namespace boost, generic, std_concept )
, (LegacyAllocator)(X)
, ( public (DefaultConstructible<X>) (CopyConstructible<X>)
           (EqualityComparable<X>)
  )
, ( (HasDereference) pointer, typename X::pointer )
, ( (HasDereference) const_pointer, typename X::const_pointer )
, ( typename generic_pointer, void* )
, ( typename const_generic_pointer, const void* )
, ( typename reference, typename X::reference )
, ( typename const_reference, typename X::const_reference )
, ( (ObjectType) value_type, typename X::value_type )
, ( (UnsignedIntegralLike) size_type, typename X::size_type )
, ( (SignedIntegralLike) difference_type, typename X::difference_type )
//, ( template ( ((ObjectType)) T ) class rebind, // ToDo: Implement
//  )
, ( requires HasDestructor<value_type> )
, ( requires RandomAccessIterator<pointer> )
, ( requires RandomAccessIterator<const_pointer> )
, ( requires Convertible<pointer, const_pointer> )
, ( requires Convertible<pointer, generic_pointer> )
, ( requires SameType< typename HasDereference<pointer>::result_type
                     , value_type&
                     >
  )
, ( requires SameType< typename HasDereference<pointer>::result_type
                     , reference
                     >
  )
, ( requires Convertible<const_pointer, const_generic_pointer> )
, ( requires SameType< typename HasDerefence<const_pointer>::result_type
                     , const value_type&
                     >
  )
, ( requires SameType< typename HasDerefence<const_pointer>::result_type
                     , const_reference
                     >
  )
, ( requires IntegralType<size_type> )
, ( requires IntegralType<difference_type> )
, ( (pointer)(this(X) address)( (reference) r ) const )
, ( (const_pointer)(this(X) address)( (const_reference) r ) const )
, ( (pointer)(this(X) allocate)( (size_type) n ) )
, ( (pointer)(this(X) allocate)( (size_type) n, (generic_pointer) p ), {
      return X::allocate(n);
    }
  )
, ( (void)(this(X) deallocate)( (pointer) p, (const value_type&) ) )
, ( (size_type)(this(X) max_size)() const )
, ( template ( ((ObjectType)) T ) // ToDo: Add requires as in working paper
    (this(X))( (const typename rebind<T>::other&) y)
  )
, ( requires CopyConstructible<value_type> )
, ( (void)(this(X) construct)( (pointer) p, (const value_type&) ) )
, ( (void)(this(X) destroy)( (pointer) p ) )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_MEMORY_CONCEPTS_LEGACY_ALLOCATOR_HPP
