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

namespace boost {

    template <typename Selector, typename T1, typename T2>
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

#include <boost/parameter.hpp>

#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/selector_keywords.hpp>
#include <boost/container_gen/detail/selector_signatures.hpp>

//[reference__container_gen__stable_vector_specialization
namespace boost {

    //<-
    template <typename Selector, typename T1, typename T2>
    struct container_gen
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(3, container_gen, (Selector, T1, T2))
    };

#if !defined BOOST_MSVC
    template <typename T0, typename T1, typename ValueType>
    struct container_gen<array_selector<T0,T1>,ValueType,void>
    {
     private:
        typedef typename detail::array_selector_signature::bind<T0,T1>::type
                _arg_pack;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , constant_size_tag
                >::type
                _constant_size;

     public:
        typedef typename ::boost::mpl::if_<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , is_tr1_not_boost_tag
                      , ::boost::mpl::false_
                    >::type
                  , ::std::tr1::array<ValueType,_constant_size::value>
                  , ::boost::array<ValueType,_constant_size::value>
                >::type
                type;
    };
#endif  // BOOST_MSVC

    template <typename T0, typename T1, typename ValueType>
    struct container_gen<vector_selector<T0,T1>,ValueType,void>
    {
     private:
        typedef typename detail::sequence_selector_signature::bind<T0,T1>::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , ValueType
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , is_boost_not_std_tag
                      , ::boost::mpl::false_
                    >::type
                  , ::boost::container::vector<ValueType,_allocator>
                  , ::std::vector<ValueType,_allocator>
                >::type
                type;
    };
    //->

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

    //<-
    template <typename T0, typename T1, typename ValueType>
    struct container_gen<deque_selector<T0,T1>,ValueType,void>
    {
     private:
        typedef typename detail::sequence_selector_signature::bind<T0,T1>::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , ValueType
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , is_boost_not_std_tag
                      , ::boost::mpl::false_
                    >::type
                  , ::boost::container::deque<ValueType,_allocator>
                  , ::std::deque<ValueType,_allocator>
                >::type
                type;
    };

    template <typename T0, typename T1, typename ValueType>
    struct container_gen<list_selector<T0,T1>,ValueType,void>
    {
     private:
        typedef typename detail::sequence_selector_signature::bind<T0,T1>::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , ValueType
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , is_boost_not_std_tag
                      , ::boost::mpl::false_
                    >::type
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
        typename T0
      , typename T1
      , typename T2
      , typename Key
      , typename Mapped
    >
    struct container_gen<set_selector<T0,T1,T2>,Key,Mapped>
    {
     private:
        typedef typename detail::boost_or_std_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , is_boost_not_std_tag
                      , ::boost::mpl::false_
                    >::type
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
        typename T0
      , typename T1
      , typename T2
      , typename Key
      , typename Mapped
    >
    struct container_gen<map_selector<T0,T1,T2>,Key,Mapped>
    {
     private:
        typedef typename detail::boost_or_std_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , is_boost_not_std_tag
                      , ::boost::mpl::false_
                    >::type
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
        typename T0
      , typename T1
      , typename T2
      , typename Key
      , typename Mapped
    >
    struct container_gen<multiset_selector<T0,T1,T2>,Key,Mapped>
    {
     private:
        typedef typename detail::boost_or_std_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , is_boost_not_std_tag
                      , ::boost::mpl::false_
                    >::type
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

    template <
        typename T0
      , typename T1
      , typename T2
      , typename Key
      , typename Mapped
    >
    struct container_gen<multimap_selector<T0,T1,T2>,Key,Mapped>
    {
     private:
        typedef typename detail::boost_or_std_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , Key
                  , Mapped
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , is_boost_not_std_tag
                      , ::boost::mpl::false_
                    >::type
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

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename Key
      , typename Mapped
    >
    struct container_gen<hash_set_selector<T0,T1,T2,T3>,Key,Mapped>
    {
     private:
        typedef typename detail::hashed_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
                _arg_pack;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , is_tr1_not_boost_tag
                  , ::boost::mpl::false_
                >::type
                _is_tr1;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , hasher_selector_tag
                      , typename ::boost::mpl::if_<
                            _is_tr1
                          , tr1_hash_selector
                          , boost_hash_selector
                        >::type
                    >::type
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , equal_to_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , Key
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    _is_tr1
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
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename Key
      , typename Mapped
    >
    struct container_gen<hash_map_selector<T0,T1,T2,T3>,Key,Mapped>
    {
     private:
        typedef typename detail::hashed_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
                _arg_pack;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , is_tr1_not_boost_tag
                  , ::boost::mpl::false_
                >::type
                _is_tr1;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , hasher_selector_tag
                      , typename ::boost::mpl::if_<
                            _is_tr1
                          , tr1_hash_selector
                          , boost_hash_selector
                        >::type
                    >::type
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , equal_to_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , Key
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    _is_tr1
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
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename Key
      , typename Mapped
    >
    struct container_gen<hash_multiset_selector<T0,T1,T2,T3>,Key,Mapped>
    {
     private:
        typedef typename detail::hashed_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
                _arg_pack;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , is_tr1_not_boost_tag
                  , ::boost::mpl::false_
                >::type
                _is_tr1;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , hasher_selector_tag
                      , typename ::boost::mpl::if_<
                            _is_tr1
                          , tr1_hash_selector
                          , boost_hash_selector
                        >::type
                    >::type
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , equal_to_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , Key
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    _is_tr1
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
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename Key
      , typename Mapped
    >
    struct container_gen<hash_multimap_selector<T0,T1,T2,T3>,Key,Mapped>
    {
     private:
        typedef typename detail::hashed_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
                _arg_pack;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , is_tr1_not_boost_tag
                  , ::boost::mpl::false_
                >::type
                _is_tr1;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , hasher_selector_tag
                      , typename ::boost::mpl::if_<
                            _is_tr1
                          , tr1_hash_selector
                          , boost_hash_selector
                        >::type
                    >::type
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , equal_to_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_allocator_selector
                    >::type
                  , Key
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::eval_if<
                    _is_tr1
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

    template <typename T0, typename T1, typename Key, typename Mapped>
    struct container_gen<flat_set_selector<T0,T1>,Key,Mapped>
    {
     private:
        typedef typename detail::associative_selector_signature::bind<
                    T0
                  , T1
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_flat_allocator_selector
                    >::type
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

    template <typename T0, typename T1, typename Key, typename Mapped>
    struct container_gen<flat_map_selector<T0,T1>,Key,Mapped>
    {
     private:
        typedef typename detail::associative_selector_signature::bind<
                    T0
                  , T1
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_flat_allocator_selector
                    >::type
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

    template <typename T0, typename T1, typename Key, typename Mapped>
    struct container_gen<flat_multiset_selector<T0,T1>,Key,Mapped>
    {
     private:
        typedef typename detail::associative_selector_signature::bind<
                    T0
                  , T1
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_flat_allocator_selector
                    >::type
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

    template <typename T0, typename T1, typename Key, typename Mapped>
    struct container_gen<flat_multimap_selector<T0,T1>,Key,Mapped>
    {
     private:
        typedef typename detail::associative_selector_signature::bind<
                    T0
                  , T1
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::mpl::apply_wrap2<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , allocator_selector_tag
                      , std_flat_allocator_selector
                    >::type
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
    template <typename T0, typename T1, typename ValueType>
    struct container_gen<ptr_array_selector<T0,T1>,ValueType,void>
    {
     private:
        typedef typename detail::ptr_array_selector_signature::bind<
                    T0
                  , T1
                >::type
                _arg_pack;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , constant_size_tag
                >::type
                _constant_size;

     public:
        typedef ::boost::ptr_array<
                    ValueType
                  , _constant_size::value
                  , typename ::boost::parameter::value_type<
                        _arg_pack
                      , ptr_clone_allocator_tag
                      , ::boost::heap_clone_allocator
                    >::type
                >
                type;
    };
#endif  // BOOST_MSVC

    template <typename T0, typename T1, typename ValueType>
    struct container_gen<ptr_vector_selector<T0,T1>,ValueType,void>
    {
     private:
        typedef typename detail::ptr_sequence_selector_signature::bind<
                    T0
                  , T1
                >::type
                _arg_pack;

     public:
        typedef ::boost::ptr_vector<
                    ValueType
                  , typename ::boost::parameter::value_type<
                        _arg_pack
                      , ptr_clone_allocator_tag
                      , ::boost::heap_clone_allocator
                    >::type
                  , typename ::boost::parameter::value_type<
                        _arg_pack
                      , ptr_allocator_tag
                      , ::std::allocator<void*>
                    >::type
                >
                type;
    };

    template <typename T0, typename T1, typename ValueType>
    struct container_gen<ptr_deque_selector<T0,T1>,ValueType,void>
    {
     private:
        typedef typename detail::ptr_sequence_selector_signature::bind<
                    T0
                  , T1
                >::type
                _arg_pack;

     public:
        typedef ::boost::ptr_deque<
                    ValueType
                  , typename ::boost::parameter::value_type<
                        _arg_pack
                      , ptr_clone_allocator_tag
                      , ::boost::heap_clone_allocator
                    >::type
                  , typename ::boost::parameter::value_type<
                        _arg_pack
                      , ptr_allocator_tag
                      , ::std::allocator<void*>
                    >::type
                >
                type;
    };

    template <typename T0, typename T1, typename ValueType>
    struct container_gen<ptr_list_selector<T0,T1>,ValueType,void>
    {
     private:
        typedef typename detail::ptr_sequence_selector_signature::bind<
                    T0
                  , T1
                >::type
                _arg_pack;

     public:
        typedef ::boost::ptr_list<
                    ValueType
                  , typename ::boost::parameter::value_type<
                        _arg_pack
                      , ptr_clone_allocator_tag
                      , ::boost::heap_clone_allocator
                    >::type
                  , typename ::boost::parameter::value_type<
                        _arg_pack
                      , ptr_allocator_tag
                      , ::std::allocator<void*>
                    >::type
                >
                type;
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename Key
      , typename Mapped
    >
    struct container_gen<ptr_set_selector<T0,T1,T2>,Key,Mapped>
    {
     private:
        typedef typename detail::ptr_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_clone_allocator_tag
                  , ::boost::heap_clone_allocator
                >::type
                _clone_allocator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_allocator_tag
                  , ::std::allocator<void*>
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_set<
                        Key
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                  , ::boost::ptr_map<
                        Key
                      , Mapped
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename Key
      , typename Mapped
    >
    struct container_gen<ptr_map_selector<T0,T1,T2>,Key,Mapped>
    {
     private:
        typedef typename detail::ptr_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_clone_allocator_tag
                  , ::boost::heap_clone_allocator
                >::type
                _clone_allocator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_allocator_tag
                  , ::std::allocator<void*>
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_set<
                        Key
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                  , ::boost::ptr_map<
                        Key
                      , Mapped
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename Key
      , typename Mapped
    >
    struct container_gen<ptr_multiset_selector<T0,T1,T2>,Key,Mapped>
    {
     private:
        typedef typename detail::ptr_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_clone_allocator_tag
                  , ::boost::heap_clone_allocator
                >::type
                _clone_allocator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_allocator_tag
                  , ::std::allocator<void*>
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_multiset<
                        Key
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                  , ::boost::ptr_multimap<
                        Key
                      , Mapped
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename Key
      , typename Mapped
    >
    struct container_gen<ptr_multimap_selector<T0,T1,T2>,Key,Mapped>
    {
     private:
        typedef typename detail::ptr_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , less_than_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_clone_allocator_tag
                  , ::boost::heap_clone_allocator
                >::type
                _clone_allocator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_allocator_tag
                  , ::std::allocator<void*>
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_multiset<
                        Key
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                  , ::boost::ptr_multimap<
                        Key
                      , Mapped
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename Key
      , typename Mapped
    >
    struct container_gen<ptr_hash_set_selector<T0,T1,T2,T3>,Key,Mapped>
    {
     private:
        typedef typename detail::ptr_hashed_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , hasher_selector_tag
                      , boost_hash_selector
                    >::type
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , equal_to_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_clone_allocator_tag
                  , ::boost::heap_clone_allocator
                >::type
                _clone_allocator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_allocator_tag
                  , ::std::allocator<void*>
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_unordered_set<
                        Key
                      , _hasher
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                  , ::boost::ptr_unordered_map<
                        Key
                      , Mapped
                      , _hasher
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename Key
      , typename Mapped
    >
    struct container_gen<ptr_hash_map_selector<T0,T1,T2,T3>,Key,Mapped>
    {
     private:
        typedef typename detail::ptr_hashed_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , hasher_selector_tag
                      , boost_hash_selector
                    >::type
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , equal_to_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_clone_allocator_tag
                  , ::boost::heap_clone_allocator
                >::type
                _clone_allocator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_allocator_tag
                  , ::std::allocator<void*>
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_unordered_set<
                        Key
                      , _hasher
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                  , ::boost::ptr_unordered_map<
                        Key
                      , Mapped
                      , _hasher
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename Key
      , typename Mapped
    >
    struct container_gen<ptr_hash_multiset_selector<T0,T1,T2,T3>,Key,Mapped>
    {
     private:
        typedef typename detail::ptr_hashed_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , hasher_selector_tag
                      , boost_hash_selector
                    >::type
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , equal_to_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_clone_allocator_tag
                  , ::boost::heap_clone_allocator
                >::type
                _clone_allocator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_allocator_tag
                  , ::std::allocator<void*>
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_unordered_multiset<
                        Key
                      , _hasher
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                  , ::boost::ptr_unordered_multimap<
                        Key
                      , Mapped
                      , _hasher
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                >::type
                type;
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename Key
      , typename Mapped
    >
    struct container_gen<ptr_hash_multimap_selector<T0,T1,T2,T3>,Key,Mapped>
    {
     private:
        typedef typename detail::ptr_hashed_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
                _arg_pack;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , hasher_selector_tag
                      , boost_hash_selector
                    >::type
                  , Key
                >::type
                _hasher;
        typedef typename ::boost::mpl::apply_wrap1<
                    typename ::boost::parameter::value_type<
                        _arg_pack
                      , compare_selector_tag
                      , equal_to_selector
                    >::type
                  , Key
                >::type
                _comparator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_clone_allocator_tag
                  , ::boost::heap_clone_allocator
                >::type
                _clone_allocator;
        typedef typename ::boost::parameter::value_type<
                    _arg_pack
                  , ptr_allocator_tag
                  , ::std::allocator<void*>
                >::type
                _allocator;

     public:
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<Mapped>
                  , ::boost::ptr_unordered_multiset<
                        Key
                      , _hasher
                      , _comparator
                      , _clone_allocator
                      , _allocator
                    >
                  , ::boost::ptr_unordered_multimap<
                        Key
                      , Mapped
                      , _hasher
                      , _comparator
                      , _clone_allocator
                      , _allocator
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

#include <boost/cstdint.hpp>

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

    template <typename T0, typename T1, typename ValueType>
    struct container_gen<
        std_heap_selector<T0,T1>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::std_heap_selector_signature::bind<T0,T1>::type
                _arg_pack;

     public:
        typedef ::std::priority_queue<
                    ValueType
                  , typename container_gen<
                        typename ::boost::parameter::value_type<
                            _arg_pack
                          , sequence_selector_tag
                          , dequeS
                        >::type
                      , ValueType
                    >::type
                  , typename ::boost::mpl::apply_wrap1<
                        typename ::boost::parameter::value_type<
                            _arg_pack
                          , compare_selector_tag
                          , less_than_selector
                        >::type
                      , ValueType
                    >::type
                >
                type;
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename ValueType
    >
    struct container_gen<
        priority_queue_selector<T0,T1,T2,T3>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::priority_queue_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
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
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
      , typename ValueType
    >
    struct container_gen<
        d_ary_heap_selector<T0,T1,T2,T3,T4,T5>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::d_ary_heap_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                  , T4
                  , T5
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
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename ValueType
    >
    struct container_gen<
        binomial_heap_selector<T0,T1,T2,T3>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::binomial_heap_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
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
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename ValueType
    >
    struct container_gen<
        fibonacci_heap_selector<T0,T1,T2,T3,T4>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::fibonacci_heap_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                  , T4
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
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename ValueType
    >
    struct container_gen<
        pairing_heap_selector<T0,T1,T2,T3,T4>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::pairing_heap_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                  , T4
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
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
      , typename T6
      , typename ValueType
    >
    struct container_gen<
        skew_heap_selector<T0,T1,T2,T3,T4,T5,T6>
      , ValueType
      , void
    >
    {
     private:
        typedef typename detail::skew_heap_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                  , T4
                  , T5
                  , T6
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

