//=============================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2010 Thomas Claveirole
// Copyright 2011-2013 Cromwell D. Enage
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Thomas Claveirole,
//          Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_CONTAINER_GEN_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_CONTAINER_GEN_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//=============================================================================
// The main container_gen metafunction uses partial specialization,
// so we also include a workaround.
//=============================================================================

//[reference__container_gen
namespace boost {

    template <typename Selector, typename T1, typename T2 = void>
    struct container_gen
        //<-
      : ::boost::mpl::apply_wrap2<Selector,T1,T2>
        //->
    {
        // typedef .... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(3, container_gen, (Selector, T1, T2))
        //->
    };
}  // namespace boost
//]

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>

#if !defined BOOST_MSVC
#include <boost/array.hpp>
#include <boost/tr1/array.hpp>
#include <boost/ptr_container/ptr_array.hpp>
#endif

#include <boost/unordered/unordered_set.hpp>
#include <boost/unordered/unordered_map.hpp>

#include <boost/tr1/unordered_set.hpp>
#include <boost/tr1/unordered_map.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>

#include <boost/container/vector.hpp>
#include <boost/container/stable_vector.hpp>
#include <boost/container/deque.hpp>
#include <boost/container/list.hpp>
#include <boost/container/slist.hpp>
#include <boost/container/set.hpp>
#include <boost/container/map.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/container/flat_map.hpp>

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/container_gen/selectors.hpp>

//[reference__container_gen__multimap_specialization
namespace boost {

    //<-
    template <typename Selector, typename T1, typename T2 = void>
    struct container_gen
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(3, container_gen, (Selector, T1, T2))
    };

#if !defined BOOST_MSVC
    template <typename ConstantSize, typename IsTR1, typename ValueType>
    struct container_gen<array_selector<ConstantSize,IsTR1>,ValueType,void>
      : ::boost::mpl::if_<
            IsTR1
          , ::std::tr1::array<ValueType,ConstantSize::value>
          , ::boost::array<ValueType,ConstantSize::value>
        >
    {
    };
#endif

    template <typename IsBoost, typename AllocatorSelector, typename ValueType>
    struct container_gen<
        vector_selector<IsBoost,AllocatorSelector>
      , ValueType
      , void
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    AllocatorSelector
                  , ValueType
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    IsBoost
                  , ::boost::container::vector<ValueType,_allocator>
                  , ::std::vector<ValueType,_allocator>
                >::type
                type;
    };

    template <typename AllocatorSelector, typename ValueType>
    struct container_gen<
        stable_vector_selector<AllocatorSelector>
      , ValueType
      , void
    >
    {
        typedef ::boost::container::stable_vector<
                    ValueType
                  , typename ::boost::mpl::apply_wrap1<
                        AllocatorSelector
                      , ValueType
                    >::type
                >
                type;
    };

    template <typename IsBoost, typename AllocatorSelector, typename ValueType>
    struct container_gen<
        deque_selector<IsBoost,AllocatorSelector>
      , ValueType
      , void
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    AllocatorSelector
                  , ValueType
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    IsBoost
                  , ::boost::container::deque<ValueType,_allocator>
                  , ::std::deque<ValueType,_allocator>
                >::type
                type;
    };

    template <typename IsBoost, typename AllocatorSelector, typename ValueType>
    struct container_gen<
        list_selector<IsBoost,AllocatorSelector>
      , ValueType
      , void
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    AllocatorSelector
                  , ValueType
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    IsBoost
                  , ::boost::container::list<ValueType,_allocator>
                  , ::std::list<ValueType,_allocator>
                >::type
                type;
    };

    template <typename AllocatorSelector, typename ValueType>
    struct container_gen<slist_selector<AllocatorSelector>,ValueType,void>
    {
        typedef ::boost::container::slist<
                    ValueType
                  , typename ::boost::mpl::apply_wrap1<
                        AllocatorSelector
                      , ValueType
                    >::type
                >
                type;
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        set_selector<IsBoost,CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    AllocatorSelector
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    IsBoost
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::container::set<Key,_comparator,_allocator>
                      , ::boost::container::map<
                            Key
                          , Mapped
                          , _comparator
                          , _allocator
                        >
                    >
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::set<Key,_comparator,_allocator>
                      , ::std::map<Key,Mapped,_comparator,_allocator>
                    >
                >::type
                type;
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        map_selector<IsBoost,CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    AllocatorSelector
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    IsBoost
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::container::set<Key,_comparator,_allocator>
                      , ::boost::container::map<
                            Key
                          , Mapped
                          , _comparator
                          , _allocator
                        >
                    >
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::set<Key,_comparator,_allocator>
                      , ::std::map<Key,Mapped,_comparator,_allocator>
                    >
                >::type
                type;
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        multiset_selector<IsBoost,CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    AllocatorSelector
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    IsBoost
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::container::multiset<
                            Key
                          , _comparator
                          , _allocator
                        >
                      , ::boost::container::multimap<
                            Key
                          , Mapped
                          , _comparator
                          , _allocator
                        >
                    >
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::multiset<Key,_comparator,_allocator>
                      , ::std::multimap<Key,Mapped,_comparator,_allocator>
                    >
                >::type
                type;
    };
    //->

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        multimap_selector<IsBoost,CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    AllocatorSelector
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    IsBoost
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::container::multiset<
                            Key
                          , _comparator
                          , _allocator
                        >
                      , ::boost::container::multimap<
                            Key
                          , Mapped
                          , _comparator
                          , _allocator
                        >
                    >
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::multiset<Key,_comparator,_allocator>
                      , ::std::multimap<Key,Mapped,_comparator,_allocator>
                    >
                >::type
                type;
    };

    //<-
    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        hash_set_selector<IsTR1,HashSelector,CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    HashSelector
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap1<
                    AllocatorSelector
                  , Key
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    IsTR1
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::tr1::unordered_set<
                            Key
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                      , ::std::tr1::unordered_map<
                            Key
                          , Mapped
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                    >
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::unordered_set<
                            Key
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                      , ::boost::unordered_map<
                            Key
                          , Mapped
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                    >
                >::type
                type;
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        hash_map_selector<IsTR1,HashSelector,CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    HashSelector
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap1<
                    AllocatorSelector
                  , Key
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    IsTR1
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::tr1::unordered_set<
                            Key
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                      , ::std::tr1::unordered_map<
                            Key
                          , Mapped
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                    >
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::unordered_set<
                            Key
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                      , ::boost::unordered_map<
                            Key
                          , Mapped
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                    >
                >::type
                type;
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        hash_multiset_selector<
            IsTR1
          , HashSelector
          , CompareSelector
          , AllocatorSelector
        >
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    HashSelector
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap1<
                    AllocatorSelector
                  , Key
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    IsTR1
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::tr1::unordered_multiset<
                            Key
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                      , ::std::tr1::unordered_multimap<
                            Key
                          , Mapped
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                    >
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::unordered_multiset<
                            Key
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                      , ::boost::unordered_multimap<
                            Key
                          , Mapped
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                    >
                >::type
                type;
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        hash_multimap_selector<
            IsTR1
          , HashSelector
          , CompareSelector
          , AllocatorSelector
        >
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    HashSelector
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap1<
                    AllocatorSelector
                  , Key
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    IsTR1
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::std::tr1::unordered_multiset<
                            Key
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                      , ::std::tr1::unordered_multimap<
                            Key
                          , Mapped
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                    >
                  , ::boost::mpl::if_<
                        ::std::tr1::is_void<Mapped>
                      , ::boost::unordered_multiset<
                            Key
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                      , ::boost::unordered_multimap<
                            Key
                          , Mapped
                          , _hasher
                          , _comparator
                          , _allocator
                        >
                    >
                >::type
                type;
    };

    template <
        typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        flat_set_selector<CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    AllocatorSelector
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::container::flat_set<Key,_comparator,_allocator>
                  , ::boost::container::flat_map<
                        Key
                      , Mapped
                      , _comparator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        flat_map_selector<CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    AllocatorSelector
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::container::flat_set<Key,_comparator,_allocator>
                  , ::boost::container::flat_map<
                        Key
                      , Mapped
                      , _comparator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        flat_multiset_selector<CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    AllocatorSelector
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::container::flat_multiset<
                        Key
                      , _comparator
                      , _allocator
                    >
                  , ::boost::container::flat_multimap<
                        Key
                      , Mapped
                      , _comparator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename CompareSelector
      , typename AllocatorSelector
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        flat_multimap_selector<CompareSelector,AllocatorSelector>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    AllocatorSelector
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::container::flat_multiset<
                        Key
                      , _comparator
                      , _allocator
                    >
                  , ::boost::container::flat_multimap<
                        Key
                      , Mapped
                      , _comparator
                      , _allocator
                    >
                >::type
                type;
    };

#if !defined BOOST_MSVC
    template <
        typename ConstantSize
      , typename CloneAllocator
      , typename ValueType
    >
    struct container_gen<
        ptr_array_selector<ConstantSize,CloneAllocator>
      , ValueType
      , void
    >
    {
        typedef ::boost::ptr_array<
                    ValueType
                  , ConstantSize::value
                  , CloneAllocator
                >
                type;
    };
#endif

    template <
        typename CloneAllocator
      , typename Allocator
      , typename ValueType
    >
    struct container_gen<
        ptr_vector_selector<CloneAllocator,Allocator>
      , ValueType
      , void
    >
    {
        typedef ::boost::ptr_vector<ValueType,CloneAllocator,Allocator> type;
    };

    template <
        typename CloneAllocator
      , typename Allocator
      , typename ValueType
    >
    struct container_gen<
        ptr_deque_selector<CloneAllocator,Allocator>
      , ValueType
      , void
    >
    {
        typedef ::boost::ptr_deque<ValueType,CloneAllocator,Allocator> type;
    };

    template <
        typename CloneAllocator
      , typename Allocator
      , typename ValueType
    >
    struct container_gen<
        ptr_list_selector<CloneAllocator,Allocator>
      , ValueType
      , void
    >
    {
        typedef ::boost::ptr_list<ValueType,CloneAllocator,Allocator> type;
    };

    template <
        typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        ptr_set_selector<CompareSelector,CloneAllocator,Allocator>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_set<Key,_comparator,CloneAllocator,Allocator>
                  , ::boost::ptr_map<
                        Key
                      , Mapped
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                >::type
                type;
    };

    template <
        typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        ptr_map_selector<CompareSelector,CloneAllocator,Allocator>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_set<Key,_comparator,CloneAllocator,Allocator>
                  , ::boost::ptr_map<
                        Key
                      , Mapped
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                >::type
                type;
    };

    template <
        typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        ptr_multiset_selector<CompareSelector,CloneAllocator,Allocator>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_multiset<
                        Key
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                  , ::boost::ptr_multimap<
                        Key
                      , Mapped
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                >::type
                type;
    };

    template <
        typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        ptr_multimap_selector<CompareSelector,CloneAllocator,Allocator>
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_multiset<
                        Key
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                  , ::boost::ptr_multimap<
                        Key
                      , Mapped
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                >::type
                type;
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        ptr_hash_set_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    HashSelector
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_unordered_set<
                        Key
                      , _hasher
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                  , ::boost::ptr_unordered_map<
                        Key
                      , Mapped
                      , _hasher
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                >::type
                type;
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        ptr_hash_map_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    HashSelector
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_unordered_set<
                        Key
                      , _hasher
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                  , ::boost::ptr_unordered_map<
                        Key
                      , Mapped
                      , _hasher
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                >::type
                type;
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        ptr_hash_multiset_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    HashSelector
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_unordered_multiset<
                        Key
                      , _hasher
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                  , ::boost::ptr_unordered_multimap<
                        Key
                      , Mapped
                      , _hasher
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                >::type
                type;
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
      , typename Key
      , typename Mapped
    >
    struct container_gen<
        ptr_hash_multimap_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
      , Key
      , Mapped
    >
    {
     private:
        typedef typename ::boost::mpl::apply_wrap1<
                    HashSelector
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , Key
                >::type
                _comparator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_unordered_multiset<
                        Key
                      , _hasher
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                  , ::boost::ptr_unordered_multimap<
                        Key
                      , Mapped
                      , _hasher
                      , _comparator
                      , CloneAllocator
                      , Allocator
                    >
                >::type
                type;
    };
    //->
}  // namespace boost
//]

#include <stack>
#include <queue>

#include <boost/heap/priority_queue.hpp>
#include <boost/heap/d_ary_heap.hpp>
#include <boost/heap/binomial_heap.hpp>
#include <boost/heap/fibonacci_heap.hpp>
#include <boost/heap/pairing_heap.hpp>
#include <boost/heap/skew_heap.hpp>

#include <boost/parameter.hpp>
#include <boost/cstdint.hpp>

#include <boost/container_gen/selector_keywords.hpp>
#include <boost/container_gen/detail/selector_signatures.hpp>

namespace boost {

    template <typename SequenceSelector, typename ValueType>
    struct container_gen<
        stack_selector<SequenceSelector>
      , ValueType
      , void
    >
    {
        typedef ::std::stack<
                    ValueType
                  , typename container_gen<SequenceSelector,ValueType>::type
                >
                type;
    };

    template <typename SequenceSelector, typename ValueType>
    struct container_gen<
        queue_selector<SequenceSelector>
      , ValueType
      , void
    >
    {
        typedef ::std::queue<
                    ValueType
                  , typename container_gen<SequenceSelector,ValueType>::type
                >
                type;
    };

    template <
        typename CompareSelector
      , typename SequenceSelector
      , typename ValueType
    >
    struct container_gen<
        std_heap_selector<CompareSelector,SequenceSelector>
      , ValueType
      , void
    >
    {
        typedef ::std::priority_queue<
                    ValueType
                  , typename container_gen<SequenceSelector,ValueType>::type
                  , typename ::boost::mpl::apply_wrap1<
                        CompareSelector
                      , ValueType
                    >::type
                >
                type;
    };

    template <
        typename A0
      , typename A1
      , typename A2
      , typename A3
      , typename ValueType
    >
    struct container_gen<
        priority_queue_selector<A0,A1,A2,A3>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::priority_queue_selector_signature::bind<
                    A0
                  , A1
                  , A2
                  , A3
                >::type
                _arg_pack;

     public:
        typedef ::boost::heap::priority_queue<
                    ValueType
                  , ::boost::heap::compare<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , compare_selector_tag
                              , less_than_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::allocator<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , allocator_selector_tag
                              , std_allocator_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::stable<
                        ::boost::heap::detail::extract_stable<_arg_pack>::value
                    >
                  , ::boost::heap::stability_counter_type<
                        typename ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::stability_counter_type
                          , ::boost::uintmax_t
                        >::type
                    >
                >
                type;
    };

    template <
        typename A0
      , typename A1
      , typename A2
      , typename A3
      , typename A4
      , typename A5
      , typename ValueType
    >
    struct container_gen<
        d_ary_heap_selector<A0,A1,A2,A3,A4,A5>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::d_ary_heap_selector_signature::bind<
                    A0
                  , A1
                  , A2
                  , A3
                  , A4
                  , A5
                >::type
                _arg_pack;

     public:
        typedef ::boost::heap::d_ary_heap<
                    ValueType
                  , ::boost::heap::arity<
                        ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::arity
                        >::type::value
                    >
                  , ::boost::heap::compare<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , compare_selector_tag
                              , less_than_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::allocator<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , allocator_selector_tag
                              , std_allocator_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::stable<
                        ::boost::heap::detail::extract_stable<_arg_pack>::value
                    >
                  , ::boost::heap::stability_counter_type<
                        typename ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::stability_counter_type
                          , ::boost::uintmax_t
                        >::type
                    >
                  , ::boost::heap::mutable_<
                        ::boost::heap::detail::extract_mutable<_arg_pack>::value
                    >
                >
                type;
    };

    template <
        typename A0
      , typename A1
      , typename A2
      , typename A3
      , typename ValueType
    >
    struct container_gen<
        binomial_heap_selector<A0,A1,A2,A3>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::binomial_heap_selector_signature::bind<
                    A0
                  , A1
                  , A2
                  , A3
                >::type
                _arg_pack;

     public:
        typedef ::boost::heap::binomial_heap<
                    ValueType
                  , ::boost::heap::compare<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , compare_selector_tag
                              , less_than_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::allocator<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , allocator_selector_tag
                              , std_allocator_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::stable<
                        ::boost::heap::detail::extract_stable<_arg_pack>::value
                    >
                  , ::boost::heap::stability_counter_type<
                        typename ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::stability_counter_type
                          , ::boost::uintmax_t
                        >::type
                    >
                >
                type;
    };

    template <
        typename A0
      , typename A1
      , typename A2
      , typename A3
      , typename A4
      , typename ValueType
    >
    struct container_gen<
        fibonacci_heap_selector<A0,A1,A2,A3,A4>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::fibonacci_heap_selector_signature::bind<
                    A0
                  , A1
                  , A2
                  , A3
                  , A4
                >::type
                _arg_pack;

     public:
        typedef ::boost::heap::fibonacci_heap<
                    ValueType
                  , ::boost::heap::compare<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , compare_selector_tag
                              , less_than_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::allocator<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , allocator_selector_tag
                              , std_allocator_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::stable<
                        ::boost::heap::detail::extract_stable<_arg_pack>::value
                    >
                  , ::boost::heap::stability_counter_type<
                        typename ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::stability_counter_type
                          , ::boost::uintmax_t
                        >::type
                    >
                  , ::boost::heap::constant_time_size<
                        ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::constant_time_size
                          , ::boost::mpl::true_
                        >::type::value
                    >
                >
                type;
    };

    template <
        typename A0
      , typename A1
      , typename A2
      , typename A3
      , typename A4
      , typename ValueType
    >
    struct container_gen<
        pairing_heap_selector<A0,A1,A2,A3,A4>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::pairing_heap_selector_signature::bind<
                    A0
                  , A1
                  , A2
                  , A3
                  , A4
                >::type
                _arg_pack;

     public:
        typedef ::boost::heap::pairing_heap<
                    ValueType
                  , ::boost::heap::compare<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , compare_selector_tag
                              , less_than_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::allocator<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , allocator_selector_tag
                              , std_allocator_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::stable<
                        ::boost::heap::detail::extract_stable<_arg_pack>::value
                    >
                  , ::boost::heap::stability_counter_type<
                        typename ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::stability_counter_type
                          , ::boost::uintmax_t
                        >::type
                    >
                  , ::boost::heap::constant_time_size<
                        ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::constant_time_size
                          , ::boost::mpl::true_
                        >::type::value
                    >
                >
                type;
    };

    template <
        typename A0
      , typename A1
      , typename A2
      , typename A3
      , typename A4
      , typename A5
      , typename A6
      , typename ValueType
    >
    struct container_gen<
        skew_heap_selector<A0,A1,A2,A3,A4,A5,A6>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::skew_heap_selector_signature::bind<
                    A0
                  , A1
                  , A2
                  , A3
                  , A4
                  , A5
                  , A6
                >::type
                _arg_pack;

     public:
        typedef ::boost::heap::skew_heap<
                    ValueType
                  , ::boost::heap::compare<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , compare_selector_tag
                              , less_than_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::allocator<
                        typename ::boost::mpl::apply_wrap1<
                            typename ::boost::parameter::value_type<
                                _arg_pack
                              , allocator_selector_tag
                              , std_allocator_selector
                            >::type
                          , ValueType
                        >::type
                    >
                  , ::boost::heap::stable<
                        ::boost::heap::detail::extract_stable<_arg_pack>::value
                    >
                  , ::boost::heap::store_parent_pointer<
                        ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::store_parent_pointer
                          , ::boost::mpl::false_
                        >::type::value
                    >
                  , ::boost::heap::stability_counter_type<
                        typename ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::stability_counter_type
                          , ::boost::uintmax_t
                        >::type
                    >
                  , ::boost::heap::constant_time_size<
                        ::boost::parameter::binding<
                            _arg_pack
                          , ::boost::heap::tag::constant_time_size
                          , ::boost::mpl::true_
                        >::type::value
                    >
                  , ::boost::heap::mutable_<
                        ::boost::heap::detail::extract_mutable<_arg_pack>::value
                    >
                >
                type;
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_CONTAINER_GEN_HPP_INCLUDED

