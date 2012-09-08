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

#ifndef BOOST_CONTAINER_GEN_CONTAINER_GEN_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_CONTAINER_GEN_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

  //===========================================================================
  // The main container_gen metafunction uses partial specialization,
  // so we also include a workaround.
  //===========================================================================

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

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_CONTAINER_GEN_HPP_INCLUDED

