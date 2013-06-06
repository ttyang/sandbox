//=============================================================================
// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_IS_CONTAINER_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_CONTAINER_SELECTOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if defined BOOST_MPL_CFG_NO_HAS_XXX

namespace boost {

    template <typename Selector>
    struct is_container_selector : ::boost::mpl::false_
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_container_selector,(Selector))
    };
}  // namespace boost

#include <boost/container_gen/selectors_fwd.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

#if !defined BOOST_MSVC
    template <>
    struct is_container_selector<array_selector_base> : ::boost::mpl::true_
    {
    };
#endif

    template <>
    struct is_container_selector<vector_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<deque_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<list_selector_base> : ::boost::mpl::true_
    {
    };

#if !defined BOOST_NO_SLIST
    template <>
    struct is_container_selector<slist_selector_base> : ::boost::mpl::true_
    {
    };
#endif

    template <>
    struct is_container_selector<set_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<map_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<multiset_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<multimap_selector_base> : ::boost::mpl::true_
    {
    };

#if defined BOOST_HAS_HASH
    template <>
    struct is_container_selector<hash_set_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<hash_map_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<hash_multiset_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<hash_multimap_selector_base>
      : ::boost::mpl::true_
    {
    };
#endif  // BOOST_HAS_HASH

#if !defined BOOST_MSVC
    template <>
    struct is_container_selector<ptr_array_selector_base> : ::boost::mpl::true_
    {
    };
#endif

    template <>
    struct is_container_selector<ptr_vector_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<ptr_deque_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<ptr_list_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<ptr_set_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<ptr_map_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<ptr_multiset_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<ptr_multimap_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<stack_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<queue_selector_base> : ::boost::mpl::true_
    {
    };

    template <>
    struct is_container_selector<std_heap_selector_base> : ::boost::mpl::true_
    {
    };
}  // namespace boost

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

#if !defined BOOST_MSVC
    template <typename T0, typename T1>
    struct is_container_selector<array_selector<T0,T1> > : ::boost::mpl::true_
    {
    };
#endif

    template <typename T0, typename T1>
    struct is_container_selector<vector_selector<T0,T1> > : ::boost::mpl::true_
    {
    };

    template <typename AllocatorSelector>
    struct is_container_selector<stable_vector_selector<AllocatorSelector> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_container_selector<deque_selector<T0,T1> > : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_container_selector<list_selector<T0,T1> > : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_container_selector<set_selector<T0,T1,T2> > : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_container_selector<map_selector<T0,T1,T2> > : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_container_selector<multiset_selector<T0,T1,T2> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_container_selector<multimap_selector<T0,T1,T2> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_container_selector<flat_set_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_container_selector<flat_map_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_container_selector<flat_multiset_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_container_selector<flat_multimap_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<hash_set_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<hash_map_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<hash_multiset_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<hash_multimap_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

#if !defined BOOST_MSVC
    template <typename T0, typename T1>
    struct is_container_selector<ptr_array_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };
#endif

    template <typename T0, typename T1>
    struct is_container_selector<ptr_vector_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_container_selector<ptr_deque_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_container_selector<ptr_list_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_container_selector<ptr_set_selector<T0,T1,T2> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_container_selector<ptr_map_selector<T0,T1,T2> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_container_selector<ptr_multiset_selector<T0,T1,T2> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_container_selector<ptr_multimap_selector<T0,T1,T2> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<ptr_hash_set_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<ptr_hash_map_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<ptr_hash_multiset_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<ptr_hash_multimap_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename SequenceSelector>
    struct is_container_selector<stack_selector<SequenceSelector> >
      : ::boost::mpl::true_
    {
    };

    template <typename SequenceSelector>
    struct is_container_selector<queue_selector<SequenceSelector> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_container_selector<std_heap_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<priority_queue_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
    >
    struct is_container_selector<d_ary_heap_selector<T0,T1,T2,T3,T4,T5> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_container_selector<binomial_heap_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    struct is_container_selector<fibonacci_heap_selector<T0,T1,T2,T3,T4> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    struct is_container_selector<pairing_heap_selector<T0,T1,T2,T3,T4> >
      : ::boost::mpl::true_
    {
    };

    template <
        typename T0
      , typename T1
      , typename T2
      , typename T3
      , typename T4
      , typename T5
      , typename T6
    >
    struct is_container_selector<skew_heap_selector<T0,T1,T2,T3,T4,T5,T6> >
      : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#else  // !defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/mpl/aux_/has_type.hpp>
#include <boost/container_gen/container_gen_fwd.hpp>

//[reference__is_container_selector
namespace boost {

    template <typename Selector>
    struct is_container_selector
        //<-
      : ::boost::mpl::aux::has_type<
            container_gen<Selector,int>
          , ::boost::mpl::false_
        >::type
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_container_selector,(Selector))
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_MPL_CFG_NO_HAS_XXX

#endif  // BOOST_CONTAINER_GEN_IS_CONTAINER_SELECTOR_HPP_INCLUDED

