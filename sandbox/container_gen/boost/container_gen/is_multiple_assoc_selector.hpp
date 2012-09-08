//=======================================================================
// Copyright (C) 2011-2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_IS_MULTIPLE_ASSOC_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_MULTIPLE_ASSOC_SELECTOR_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/typeof/typeof.hpp>

#if defined BOOST_MPL_CFG_NO_HAS_XXX || defined BOOST_TYPEOF_EMULATION

#include <boost/mpl/bool.hpp>

namespace boost {

    template <typename Selector>
    struct is_multiple_associative_selector : ::boost::mpl::false_
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , is_multiple_associative_selector
          , (Selector)
        )
    };
}  // namespace boost

#include <boost/config.hpp>
#include <boost/container_gen/selectors.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <>
    struct is_multiple_associative_selector<multiset_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_multiple_associative_selector<multimap_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_multiple_associative_selector<ptr_multiset_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_multiple_associative_selector<ptr_multimap_selector_base>
      : ::boost::mpl::true_
    {
    };

#if defined BOOST_HAS_HASH
    template <>
    struct is_multiple_associative_selector<hash_multiset_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_multiple_associative_selector<hash_multimap_selector_base>
      : ::boost::mpl::true_
    {
    };
#endif  // BOOST_HAS_HASH
}  // namespace boost

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_multiple_associative_selector<
        multiset_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_multiple_associative_selector<
        multimap_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct is_multiple_associative_selector<
        flat_multiset_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct is_multiple_associative_selector<
        flat_multimap_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_multiple_associative_selector<
        hash_multiset_selector<
            IsTR1
          , HashSelector
          , CompareSelector
          , AllocatorSelector
        >
    > : ::boost::mpl::true_
    {
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_multiple_associative_selector<
        hash_multimap_selector<
            IsTR1
          , HashSelector
          , CompareSelector
          , AllocatorSelector
        >
    > : ::boost::mpl::true_
    {
    };

    template <
        typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
    >
    struct is_multiple_associative_selector<
        ptr_multiset_selector<CompareSelector,CloneAllocator,Allocator>
    > : ::boost::mpl::true_
    {
    };

    template <
        typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
    >
    struct is_multiple_associative_selector<
        ptr_multimap_selector<CompareSelector,CloneAllocator,Allocator>
    > : ::boost::mpl::true_
    {
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
    >
    struct is_multiple_associative_selector<
        ptr_hash_multiset_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
    > : ::boost::mpl::true_
    {
    };

    template <
        typename HashSelector
      , typename CompareSelector
      , typename CloneAllocator
      , typename Allocator
    >
    struct is_multiple_associative_selector<
        ptr_hash_multimap_selector<
            HashSelector
          , CompareSelector
          , CloneAllocator
          , Allocator
        >
    > : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#else  // !defined BOOST_MPL_CFG_NO_HAS_XXX && !defined BOOST_TYPEOF_EMULATION

#include <boost/container_gen/container_gen.hpp>
#include <boost/detail/metafunction/is_multi_assoc_container.hpp>

//[reference__is_multiple_associative_selector
namespace boost {

    template <typename Selector>
    struct is_multiple_associative_selector
        //<-
      : ::boost::detail::metafunction::is_multiple_associative_container<
            typename container_gen<Selector,int>::type
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , is_multiple_associative_selector
          , (Selector)
        )
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_MPL_CFG_NO_HAS_XXX, BOOST_TYPEOF_EMULATION

#endif  // BOOST_CONTAINER_GEN_IS_MULTIPLE_ASSOC_SELECTOR_HPP_INCLUDED

