/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_STD_CONCEPT_MEMORY_CONCEPTS_ALLOCATOR_HPP
#define BOOST_GENERIC_STD_CONCEPT_MEMORY_CONCEPTS_ALLOCATOR_HPP

#include <boost/generic/concept.hpp>
#include <boost/generic/detail/always_void.hpp>
#include <boost/generic/std_concept/concepts/copy_constructible.hpp>
#include <boost/generic/std_concept/concepts/equality_comparable.hpp>
#include <boost/generic/std_concept/concepts/free_store_allocatable.hpp>
#include <boost/generic/std_concept/concepts/has_dereference.hpp>
#include <boost/generic/std_concept/concepts/signed_integral_like.hpp>
#include <boost/generic/std_concept/concepts/unsigned_integral_like.hpp>
#include <boost/generic/std_concept/concepts/has_destructor.hpp>
#include <boost/generic/std_concept/concepts/convertible.hpp>
#include <boost/generic/std_concept/iterator_concepts/random_access_iterator.hpp>
#include <boost/generic/std_concept/support_concepts/object_type.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>
#include <cstddef>
#include <limits>
#include <utility>

namespace boost { namespace generic { namespace std_concept { namespace detail {

struct unspecified_type {};

template< class T, class Enabler = void >
struct allocator_pointer_default
{
  typedef T* type;
};

template< class T >
struct allocator_pointer_default
       < T, typename generic::detail::always_void< typename T::pointer >::type >
{
  typedef typename T::pointer type;
};

template< class T, class Enabler = void >
struct allocator_const_pointer_default
{
  typedef T const* type;
};

template< class T >
struct allocator_const_pointer_default
       < T, typename generic::detail::always_void
            < typename T::const_pointer >::type
       >
{
  typedef typename T::const_pointer type;
};

template< class T, class Enabler = void >
struct allocator_generic_pointer_default
{
  typedef void* type;
};

template< class T >
struct allocator_generic_pointer_default
       < T, typename generic::detail::always_void
            < typename T::generic_pointer >::type
       >
{
  typedef typename T::generic_pointer type;
};

template< class T, class Enabler = void >
struct allocator_const_generic_pointer_default
{
  typedef void const* type;
};

template< class T >
struct allocator_const_generic_pointer_default
       < T, typename generic::detail::always_void
            < typename T::const_generic_pointer >::type
       >
{
  typedef typename T::const_generic_pointer type;
};

template< class T, class Enabler = void >
struct allocator_size_type_default
{
  typedef ::std::size_t type;
};

template< class T >
struct allocator_size_type_default
       < T, typename generic::detail::always_void
            < typename T::size_type >::type
       >
{
  typedef typename T::size_type type;
};

} } } }

#include <boost/generic/detail/std_concept_preprocessing_utilities.hpp>

#define BOOST_GENERIC_PREPROCESSED_HEADER_NAME concept/memory_concepts/allocator.h

#ifdef BOOST_GENERIC_USE_PREPROCESSED_HEADERS
#include BOOST_GENERIC_PREPROCESSED_HEADER
#else

#include <boost/generic/detail/preprocess_header_begin.hpp>
BOOST_GENERIC_CREATE_LINE_DIRECTIVE( __LINE__ )

// [allocator.concepts]
BOOST_GENERIC_CONCEPT
( ( namespace boost, generic, std_concept )
, (Allocator)( (typename) X )
, ( public (CopyConstructible<X>) (EqualityComparable<X>) )
, ( (ObjectType) value_type, typename X::value_type )
, ( requires FreeStoreAllocatable<value_type> )
, ( (HasDereference) pointer,
      typename generic::detail::allocator_pointer_default< X >::type
  )
, ( (HasDereference) const_pointer,
      typename generic::detail::allocator_const_pointer_default< X >::type
  )
, ( requires RandomAccessIterator<pointer> )
, ( requires RandomAccessIterator<const_pointer> )
, ( (SignedIntegralLike) difference_type,
      typename RandomAccessIterator<pointer>::difference_type
  )
, ( typename generic_pointer,
      typename generic::detail::allocator_generic_pointer_default< X >::type
  )
, ( typename const_generic_pointer,
      typename generic::detail::allocator_generic_const_pointer_default< X >
      ::type
  )
, ( typename reference, value_type& )
, ( typename const_reference, const value_type& )
, ( (UnsignedIntegralLike) size_type, )
, ( template ( ((ObjectType)) T ) class rebind_type )
, ( requires HasDestructor<value_type> )
, ( requires Convertible<pointer,const_pointer> )
, ( requires Convertible<pointer,generic_pointer> )
, ( requires SameType< typename HasDereference< pointer >::result_type
                     , value_type&
                     >
  )
, ( requires SameType< typename HasDereference< pointer >::result_type
                     , reference
                     >
  )
, ( requires Convertible<const_pointer,const_generic_pointer> )
, ( requires SameType< typename HasDereference< const_pointer >::result_type
                     , const value_type&
                     >
  )
, ( requires SameType< typename HasDereference< const_pointer >::result_type
                     , const_reference
                     >
  )
, ( requires SameType< rebind_type<value_type>, X > )
, ( requires SameType< generic_pointer
                     , typename rebind_type< detail::unspecified_type >
                       ::generic_pointer
                     >
  )
, ( requires SameType< const_generic_pointer
                     , typename rebind_type< detail::unspecified_type >
                       ::const_generic_pointer
                     >
  )
, ( (pointer)(this(X) allocate)( (size_type) n ) )
, ( (pointer)(this(X) allocate)( (size_type) n, (const_generic_pointer) p ) )
, ( (void)(this(X) deallocate)( (pointer) p, (size_type) n ) )
, ( (size_type)(this(X) max_size)() const,
     { return ::std::numeric_limits<size_type>::max(); }
  )
, ( template ( ((ObjectType)) T ) (this(T))( const rebind_type<T>& y ) )
, ( (pointer)(this(X) addressof)( (reference) r ) const, {
      return addressof(r); // ToDo: Make this work, refer to working paper
    }
  )
, ( (const_pointer)(this(X) addressof)( (const_reference) r ) const, {
      return addressof(r); // ToDo: Make this work, refer to working paper
    }
  )
, ( (X)(select_on_container_copy_construction)( (const X&) x ), { return x; } )
, ( (X)(select_on_container_move_construction)( (X&&) x ), {
      return std::move( x );
    }
  )
, ( (void)(do_on_container_copy_assignment)( (X&) to, (const X&) from ), {} )
, ( (void)(do_on_container_move_assignment)( (X&) to, (X&&) from ), {} )
, ( (void)(do_on_container_swap)( (X&) a, (X&) b ), {} )
)

} } }

#ifndef BOOST_GENERIC_GENERATE_PREPROCESSED_HEADERS
#include <boost/generic/std_concept/memory_concepts/legacy_allocator.hpp>
#endif

#include <boost/generic/concept_map.hpp>

BOOST_GENERIC_CONCEPT_MAP
( ( template ( ((LegacyAllocator)) X ) )
, (Allocator)(X)
, ( typedef typename X::value_type value_type )
, ( typedef typename X::pointer pointer )
, ( typedef typename X::const_pointer const_pointer )
, ( typedef typename X::generic_pointer generic_pointer )
, ( typedef typename X::const_generic_pointer const_generic_pointer )
, ( typedef typename X::difference_type difference_type )
, ( typedef typename X::size_type size_type )
, ( typedef typename X::reference reference )
, ( typedef typename X::const_reference const_reference )
, ( template ( ((ObjectType)) )
    using rebind_type, typename X::template rebind // ToDo: Verify this is proper implementation
  )
)

#include <boost/generic/detail/preprocess_header_end.hpp>

#endif

#endif // BOOST_GENERIC_STD_CONCEPT_MEMORY_CONCEPTS_ALLOCATOR_HPP
