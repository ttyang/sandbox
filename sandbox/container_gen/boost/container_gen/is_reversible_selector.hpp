//=============================================================================
// Copyright (C) 2012-2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_IS_REVERSIBLE_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_REVERSIBLE_SELECTOR_HPP_INCLUDED

#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/mpl/bool.hpp>

namespace boost {

    template <typename Selector>
    struct is_reversible_selector : ::boost::mpl::true_
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_reversible_selector,(Selector))
    };
}  // namespace boost

#include <boost/config.hpp>
#include <boost/container_gen/selectors.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

#if !defined BOOST_NO_SLIST
    template <>
    struct is_reversible_selector<slist_selector_base>
      : ::boost::mpl::false_
    {
    };
#endif

#if defined BOOST_HAS_HASH
    template <>
    struct is_reversible_selector<hash_set_selector_base>
      : ::boost::mpl::false_
    {
    };

    template <>
    struct is_reversible_selector<hash_map_selector_base>
      : ::boost::mpl::false_
    {
    };

    template <>
    struct is_reversible_selector<hash_multiset_selector_base>
      : ::boost::mpl::false_
    {
    };

    template <>
    struct is_reversible_selector<hash_multimap_selector_base>
      : ::boost::mpl::false_
    {
    };
#endif  // BOOST_HAS_HASH

    template <>
    struct is_reversible_selector<stack_selector_base>
      : ::boost::mpl::false_
    {
    };

    template <>
    struct is_reversible_selector<queue_selector_base>
      : ::boost::mpl::false_
    {
    };

    template <>
    struct is_reversible_selector<std_heap_selector_base>
      : ::boost::mpl::false_
    {
    };
}  // namespace boost

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename AllocatorSelector>
    struct is_reversible_selector<slist_selector<AllocatorSelector> >
      : ::boost::mpl::false_
    {
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_reversible_selector<
        hash_set_selector<IsTR1,HashSelector,CompareSelector,AllocatorSelector>
    > : ::boost::mpl::false_
    {
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_reversible_selector<
        hash_map_selector<IsTR1,HashSelector,CompareSelector,AllocatorSelector>
    > : ::boost::mpl::false_
    {
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_reversible_selector<
        hash_multiset_selector<
            IsTR1
          , HashSelector
          , CompareSelector
          , AllocatorSelector
        >
    > : ::boost::mpl::false_
    {
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_reversible_selector<
        hash_multimap_selector<
            IsTR1
          , HashSelector
          , CompareSelector
          , AllocatorSelector
        >
    > : ::boost::mpl::false_
    {
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
    >
    struct is_reversible_selector<
        ptr_hash_set_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
    > : ::boost::mpl::false_
    {
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
    >
    struct is_reversible_selector<
        ptr_hash_map_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
    > : ::boost::mpl::false_
    {
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
    >
    struct is_reversible_selector<
        ptr_hash_multiset_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
    > : ::boost::mpl::false_
    {
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
    >
    struct is_reversible_selector<
        ptr_hash_multimap_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
    > : ::boost::mpl::false_
    {
    };

    template <typename ContainerSelector>
    struct is_reversible_selector<
        stack_selector<ContainerSelector>
    > : ::boost::mpl::false_
    {
    };

    template <typename ContainerSelector>
    struct is_reversible_selector<
        queue_selector<ContainerSelector>
    > : ::boost::mpl::false_
    {
    };

    template <typename CompareSelector, typename ContainerSelector>
    struct is_reversible_selector<
        std_heap_selector<CompareSelector,ContainerSelector>
    > : ::boost::mpl::false_
    {
    };

    template <typename A0, typename A1, typename A2, typename A3>
    struct is_reversible_selector<
        priority_queue_selector<A0,A1,A2,A3>
    > : ::boost::mpl::false_
    {
    };

    template <
        typename A0
      , typename A1
      , typename A2
      , typename A3
      , typename A4
      , typename A5
    >
    struct is_reversible_selector<
        d_ary_heap_selector<A0,A1,A2,A3,A4,A5>
    > : ::boost::mpl::false_
    {
    };

    template <typename A0, typename A1, typename A2, typename A3>
    struct is_reversible_selector<
        binomial_heap_selector<A0,A1,A2,A3>
    > : ::boost::mpl::false_
    {
    };

    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    struct is_reversible_selector<
        fibonacci_heap_selector<A0,A1,A2,A3,A4>
    > : ::boost::mpl::false_
    {
    };

    template <typename A0, typename A1, typename A2, typename A3, typename A4>
    struct is_reversible_selector<
        pairing_heap_selector<A0,A1,A2,A3,A4>
    > : ::boost::mpl::false_
    {
    };

    template <
        typename A0
      , typename A1
      , typename A2
      , typename A3
      , typename A4
      , typename A5
      , typename A6
    >
    struct is_reversible_selector<
        skew_heap_selector<A0,A1,A2,A3,A4,A5,A6>
    > : ::boost::mpl::false_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#else  // !defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/container_gen/container_gen.hpp>
#include <boost/detail/metafunction/is_reversible_container.hpp>

//[reference__is_reversible_selector
namespace boost {

    template <typename Selector>
    struct is_reversible_selector
        //<-
      : ::boost::detail::metafunction::is_reversible_container<
            typename container_gen<Selector,int>::type
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_reversible_selector,(Selector))
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_MPL_CFG_NO_HAS_XXX

#endif  // BOOST_CONTAINER_GEN_IS_REVERSIBLE_SELECTOR_HPP_INCLUDED

