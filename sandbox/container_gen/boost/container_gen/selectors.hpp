//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2010 Thomas Claveirole
// Copyright 2011-2012 Cromwell D. Enage
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Thomas Claveirole,
//          Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_SELECTORS_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_SELECTORS_HPP_INCLUDED

#include <functional>
#include <memory>
#include <utility>
#include <boost/mpl/if.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/functional/hash.hpp>
#include <boost/detail/metafunction/is_container.hpp>
#include <boost/detail/function/range_equal.hpp>
#include <boost/detail/function/range_less.hpp>

//[reference__template_argument_selectors
namespace boost {

    struct default_equivalence_selector
    {
        template <typename T>
        struct apply
        {
            typedef // implementation_defined
                    //<-
                    typename ::boost::mpl::if_<
                        ::boost::detail::metafunction::is_container<T>
                      , ::boost::detail::range_equal
                      , ::std::equal_to<T>
                    >::type
                    //->
                    type;
        };
    };

    struct default_ordering_selector
    {
        template <typename T>
        struct apply
        {
            typedef // implementation_defined
                    //<-
                    typename ::boost::mpl::if_<
                        ::boost::detail::metafunction::is_container<T>
                      , ::boost::detail::range_less
                      , ::std::less<T>
                    >::type
                    //->
                    type;
        };
    };

    struct boost_hash_selector
    {
        template <typename T>
        struct apply
        {
            typedef ::boost::hash<T> type;
        };
    };

    struct tr1_hash_selector
    {
        template <typename T>
        struct apply
        {
            typedef ::std::tr1::hash<T> type;
        };
    };

    struct std_allocator_selector
    {
        template <typename T1, typename T2 = void>
        struct apply
        {
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<T2>
                      , ::std::allocator<T1>
                      , ::std::allocator< ::std::pair<T1 const,T2> >
                    >::type
                    type;
        };
    };

    struct std_flat_allocator_selector
    {
        template <typename T1, typename T2 = void>
        struct apply
        {
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<T2>
                      , ::std::allocator<T1>
                      , ::std::allocator< ::std::pair<T1,T2> >
                    >::type
                    type;
        };
    };
}  // namespace boost
//]

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/ptr_container/clone_allocator.hpp>

  //===========================================================================
  // Selectors for the VertexList and EdgeList template parameters of
  // adjacency_list, and the container_gen metafunction which is used
  // to map the selectors to the container type used to implement the
  // graph.
  //===========================================================================

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <vector>
#include <deque>
#include <list>

#if !defined BOOST_NO_SLIST
#  if defined BOOST_SLIST_HEADER
#    include BOOST_SLIST_HEADER
#  else
#    include <slist>
#  endif
#endif

#if defined BOOST_HAS_HASH
#  if defined BOOST_HASH_SET_HEADER
#    include BOOST_HASH_SET_HEADER
#  else
#    include <hash_set>
#  endif
#  if defined BOOST_HASH_MAP_HEADER
#    include BOOST_HASH_MAP_HEADER
#  else
#    include <hash_map>
#  endif
#endif

#if !defined BOOST_MSVC
#include <boost/array.hpp>
#include <boost/tr1/array.hpp>
#include <boost/ptr_container/ptr_array.hpp>
#endif

#include <set>
#include <map>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>

#include <boost/mpl/apply_wrap.hpp>

namespace boost {

#if !defined BOOST_MSVC
    struct array_selector_base
    {
    };

    template <typename ConstantSize, typename IsTR1 = ::boost::mpl::false_>
    struct array_selector : array_selector_base
    {
        template <typename T, typename Unused>
        struct apply
        {
            typedef typename ::boost::mpl::if_<
                        IsTR1
                      , ::std::tr1::array<T,ConstantSize::value>
                      , ::boost::array<T,ConstantSize::value>
                    >::type
                    type;
        };
    };
#endif

    struct vector_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename AllocatorSelector = std_allocator_selector
    >
    struct vector_selector : vector_selector_base
    {
        template <typename T, typename Unused>
        struct apply
        {
            typedef ::std::vector<
                        T
                      , typename ::boost::mpl::apply_wrap1<
                            AllocatorSelector
                          , T
                        >::type
                    >
                    type;
        };
    };

    struct deque_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename AllocatorSelector = std_allocator_selector
    >
    struct deque_selector : deque_selector_base
    {
        template <typename T, typename Unused>
        struct apply
        {
            typedef ::std::deque<
                        T
                      , typename ::boost::mpl::apply_wrap1<
                            AllocatorSelector
                          , T
                        >::type
                    >
                    type;
        };
    };

    struct list_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename AllocatorSelector = std_allocator_selector
    >
    struct list_selector : list_selector_base
    {
        template <typename T, typename Unused>
        struct apply
        {
            typedef ::std::list<
                        T
                      , typename ::boost::mpl::apply_wrap1<
                            AllocatorSelector
                          , T
                        >::type
                    >
                    type;
        };
    };

#if !defined BOOST_NO_SLIST
    struct slist_selector_base
    {
    };

    template <typename AllocatorSelector = std_allocator_selector>
    struct slist_selector : slist_selector_base
    {
        template <typename T, typename Unused>
        struct apply
        {
            typedef ::BOOST_STD_EXTENSION_NAMESPACE::slist<
                        T
                      , typename ::boost::mpl::apply_wrap1<
                            AllocatorSelector
                          , T
                        >::type
                    >
                    type;
        };
    };
#endif

    struct set_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct set_selector : set_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;
            typedef typename ::boost::mpl::apply_wrap2<
                        AllocatorSelector
                      , Key
                      , Mapped
                    >::type
                    allocator_type;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::set<Key,comparator,allocator_type>
                      , ::std::map<Key,Mapped,comparator,allocator_type>
                    >::type
                    type;
        };
    };

    struct map_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct map_selector : map_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;
            typedef typename ::boost::mpl::apply_wrap2<
                        AllocatorSelector
                      , Key
                      , Mapped
                    >::type
                    allocator_type;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::set<Key,comparator,allocator_type>
                      , ::std::map<Key,Mapped,comparator,allocator_type>
                    >::type
                    type;
        };
    };

    struct multiset_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct multiset_selector : multiset_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;
            typedef typename ::boost::mpl::apply_wrap2<
                        AllocatorSelector
                      , Key
                      , Mapped
                    >::type
                    allocator_type;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::multiset<Key,comparator,allocator_type>
                      , ::std::multimap<Key,Mapped,comparator,allocator_type>
                    >::type
                    type;
        };
    };

    struct multimap_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct multimap_selector : multimap_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;
            typedef typename ::boost::mpl::apply_wrap2<
                        AllocatorSelector
                      , Key
                      , Mapped
                    >::type
                    allocator_type;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::multiset<Key,comparator,allocator_type>
                      , ::std::multimap<Key,Mapped,comparator,allocator_type>
                    >::type
                    type;
        };
    };

#if defined BOOST_HAS_HASH
    struct hash_set_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct hash_set_selector : hash_set_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        HashSelector
                      , Key
                    >::type
                    hasher;
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;
            typedef typename ::boost::mpl::apply_wrap1<
                        AllocatorSelector
                      , Key
                    >::type
                    allocator_type;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::BOOST_STD_EXTENSION_NAMESPACE::hash_set<
                            Key
                          , hasher
                          , comparator
                          , allocator_type
                        >
                      , ::BOOST_STD_EXTENSION_NAMESPACE::hash_map<
                            Key
                          , Mapped
                          , hasher
                          , comparator
                          , allocator_type
                        >
                    >::type
                    type;
        };
    };

    struct hash_map_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct hash_map_selector : hash_map_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        HashSelector
                      , Key
                    >::type
                    hasher;
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;
            typedef typename ::boost::mpl::apply_wrap1<
                        AllocatorSelector
                      , Key
                    >::type
                    allocator_type;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::BOOST_STD_EXTENSION_NAMESPACE::hash_set<
                            Key
                          , hasher
                          , comparator
                          , allocator_type
                        >
                      , ::BOOST_STD_EXTENSION_NAMESPACE::hash_map<
                            Key
                          , Mapped
                          , hasher
                          , comparator
                          , allocator_type
                        >
                    >::type
                    type;
        };
    };

    struct hash_multiset_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct hash_multiset_selector : hash_multiset_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        HashSelector
                      , Key
                    >::type
                    hasher;
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;
            typedef typename ::boost::mpl::apply_wrap1<
                        AllocatorSelector
                      , Key
                    >::type
                    allocator_type;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::BOOST_STD_EXTENSION_NAMESPACE::hash_multiset<
                            Key
                          , hasher
                          , comparator
                          , allocator_type
                        >
                      , ::BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<
                            Key
                          , Mapped
                          , hasher
                          , comparator
                          , allocator_type
                        >
                    >::type
                    type;
        };
    };

    struct hash_multimap_selector_base
    {
    };

    template <
        typename Ignored = ::boost::mpl::false_
      , typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct hash_multimap_selector : hash_multimap_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        HashSelector
                      , Key
                    >::type
                    hasher;
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;
            typedef typename ::boost::mpl::apply_wrap1<
                        AllocatorSelector
                      , Key
                    >::type
                    allocator_type;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::BOOST_STD_EXTENSION_NAMESPACE::hash_multiset<
                            Key
                          , hasher
                          , comparator
                          , allocator_type
                        >
                      , ::BOOST_STD_EXTENSION_NAMESPACE::hash_multimap<
                            Key
                          , Mapped
                          , hasher
                          , comparator
                          , allocator_type
                        >
                    >::type
                    type;
        };
    };
#endif  // BOOST_HAS_HASH

#if !defined BOOST_MSVC
    struct ptr_array_selector_base
    {
    };

    template <
        typename ConstantSize
      , typename CloneAllocator = ::boost::heap_clone_allocator
    >
    struct ptr_array_selector : ptr_array_selector_base
    {
        template <typename T, typename Unused>
        struct apply
        {
            typedef ::boost::ptr_array<
                        T
                      , ConstantSize::value
                      , CloneAllocator
                    >
                    type;
        };
    };
#endif

    struct ptr_vector_selector_base
    {
    };

    template <
        typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_vector_selector : ptr_vector_selector_base
    {
        template <typename T, typename Unused>
        struct apply
        {
            typedef ::boost::ptr_vector<T,CloneAllocator,Allocator> type;
        };
    };

    struct ptr_deque_selector_base
    {
    };

    template <
        typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_deque_selector : ptr_deque_selector_base
    {
        template <typename T, typename Unused>
        struct apply
        {
            typedef ::boost::ptr_deque<T,CloneAllocator,Allocator> type;
        };
    };

    struct ptr_list_selector_base
    {
    };

    template <
        typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_list_selector : ptr_list_selector_base
    {
        template <typename T, typename Unused>
        struct apply
        {
            typedef ::boost::ptr_list<T,CloneAllocator,Allocator> type;
        };
    };

    struct ptr_set_selector_base
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_set_selector : ptr_set_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::ptr_set<
                            Key
                          , comparator
                          , CloneAllocator
                          , Allocator
                        >
                      , ::boost::ptr_map<
                            Key
                          , Mapped
                          , comparator
                          , CloneAllocator
                          , Allocator
                        >
                    >::type
                    type;
        };
    };

    struct ptr_map_selector_base
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_map_selector : ptr_map_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::ptr_set<
                            Key
                          , comparator
                          , CloneAllocator
                          , Allocator
                        >
                      , ::boost::ptr_map<
                            Key
                          , Mapped
                          , comparator
                          , CloneAllocator
                          , Allocator
                        >
                    >::type
                    type;
        };
    };

    struct ptr_multiset_selector_base
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_multiset_selector : ptr_multiset_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::ptr_multiset<
                            Key
                          , comparator
                          , CloneAllocator
                          , Allocator
                        >
                      , ::boost::ptr_multimap<
                            Key
                          , Mapped
                          , comparator
                          , CloneAllocator
                          , Allocator
                        >
                    >::type
                    type;
        };
    };

    struct ptr_multimap_selector_base
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_multimap_selector : ptr_multimap_selector_base
    {
        template <typename Key, typename Mapped>
        struct apply
        {
         private:
            typedef typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , Key
                    >::type
                    comparator;

         public:
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::ptr_multiset<
                            Key
                          , comparator
                          , CloneAllocator
                          , Allocator
                        >
                      , ::boost::ptr_multimap<
                            Key
                          , Mapped
                          , comparator
                          , CloneAllocator
                          , Allocator
                        >
                    >::type
                    type;
        };
    };
}  // namespace boost

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__container_selector_templates
namespace boost {

    template <typename ConstantSize, typename IsTR1 = ::boost::mpl::false_>
    struct array_selector
    {
    };

    template <
        typename IsBoost = ::boost::mpl::false_
      , typename AllocatorSelector = std_allocator_selector
    >
    struct vector_selector
    {
    };

    template <typename AllocatorSelector = std_allocator_selector>
    struct stable_vector_selector
    {
    };

    template <
        typename IsBoost = ::boost::mpl::false_
      , typename AllocatorSelector = std_allocator_selector
    >
    struct deque_selector
    {
    };

    template <
        typename IsBoost = ::boost::mpl::false_
      , typename AllocatorSelector = std_allocator_selector
    >
    struct list_selector
    {
    };

    template <typename AllocatorSelector = std_allocator_selector>
    struct slist_selector
    {
    };

    template <
        typename IsBoost = ::boost::mpl::false_
      , typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct set_selector
    {
    };

    template <
        typename IsBoost = ::boost::mpl::false_
      , typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct map_selector
    {
    };

    template <
        typename IsBoost = ::boost::mpl::false_
      , typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct multiset_selector
    {
    };

    template <
        typename IsBoost = ::boost::mpl::false_
      , typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct multimap_selector
    {
    };

    template <
        typename IsTR1 = ::boost::mpl::false_
      , typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct hash_set_selector
    {
    };

    template <
        typename IsTR1 = ::boost::mpl::false_
      , typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct hash_map_selector
    {
    };

    template <
        typename IsTR1 = ::boost::mpl::false_
      , typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct hash_multiset_selector
    {
    };

    template <
        typename IsTR1 = ::boost::mpl::false_
      , typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename AllocatorSelector = std_allocator_selector
    >
    struct hash_multimap_selector
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_flat_allocator_selector
    >
    struct flat_set_selector
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_flat_allocator_selector
    >
    struct flat_map_selector
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_flat_allocator_selector
    >
    struct flat_multiset_selector
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename AllocatorSelector = std_flat_allocator_selector
    >
    struct flat_multimap_selector
    {
    };

    template <
        typename ConstantSize
      , typename CloneAllocator = ::boost::heap_clone_allocator
    >
    struct ptr_array_selector
    {
    };

    template <
        typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_vector_selector
    {
    };

    template <
        typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_deque_selector
    {
    };

    template <
        typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_list_selector
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_set_selector
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_map_selector
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_multiset_selector
    {
    };

    template <
        typename CompareSelector = default_ordering_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_multimap_selector
    {
    };

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_hash_set_selector
    {
    };

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_hash_map_selector
    {
    };

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_hash_multiset_selector
    {
    };

    template <
        typename HashSelector = boost_hash_selector
      , typename CompareSelector = default_equivalence_selector
      , typename CloneAllocator = ::boost::heap_clone_allocator
      , typename Allocator = ::std::allocator<void*>
    >
    struct ptr_hash_multimap_selector
    {
    };
}  // namespace boost
//]

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__container_selector_typedefs
namespace boost {

    typedef vector_selector<> vecS;
    typedef deque_selector<> dequeS;
    typedef list_selector<> listS;
//<-
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 || !defined BOOST_NO_SLIST
//->
    typedef slist_selector<> slistS;
//<-
#endif
//->
    typedef set_selector<> setS;
    typedef map_selector<> mapS;
    typedef multiset_selector<> multisetS;
    typedef multimap_selector<> multimapS;
//<-
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION || defined BOOST_HAS_HASH
//->
    typedef hash_set_selector<> hash_setS;
    typedef hash_map_selector<> hash_mapS;
    typedef hash_multiset_selector<> hash_multisetS;
    typedef hash_multimap_selector<> hash_multimapS;
//<-
#endif
//->
    typedef ptr_vector_selector<> ptr_vecS;
    typedef ptr_deque_selector<> ptr_dequeS;
    typedef ptr_list_selector<> ptr_listS;
    typedef ptr_set_selector<> ptr_setS;
    typedef ptr_map_selector<> ptr_mapS;
    typedef ptr_multiset_selector<> ptr_multisetS;
    typedef ptr_multimap_selector<> ptr_multimapS;
//<-
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//->
    typedef ptr_hash_set_selector<> ptr_hash_setS;
    typedef ptr_hash_map_selector<> ptr_hash_mapS;
    typedef ptr_hash_multiset_selector<> ptr_hash_multisetS;
    typedef ptr_hash_multimap_selector<> ptr_hash_multimapS;
    typedef stable_vector_selector<> stable_vecS;
    typedef flat_set_selector<> flat_setS;
    typedef flat_map_selector<> flat_mapS;
    typedef flat_multiset_selector<> flat_multisetS;
    typedef flat_multimap_selector<> flat_multimapS;
//<-
#endif
//->
}  // namespace boost
//]

#endif  // BOOST_CONTAINER_GEN_SELECTORS_HPP_INCLUDED

