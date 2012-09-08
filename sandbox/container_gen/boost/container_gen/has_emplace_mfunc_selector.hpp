//=======================================================================
// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_HAS_EMPLACE_MFUNC_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_HAS_EMPLACE_MFUNC_SELECTOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__has_emplace_member_function_selector
namespace boost {

    template <typename Selector>
    struct has_emplace_member_function_selector
        //<-
      : ::boost::mpl::false_
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , has_emplace_member_function_selector
          , (Selector)
        )
        //->
    };
}  // namespace boost
//]

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <boost/mpl/if.hpp>
#include <boost/container_gen/is_flat_assoc_selector.hpp>
#include <boost/container_gen/is_hashed_assoc_selector.hpp>
#include <boost/container_gen/selectors.hpp>

#if defined BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
#define BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE ::boost::mpl::true_
#else
#define BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE \
::boost::mpl::if_<IsBoost,::boost::mpl::true_,::boost::mpl::false_>::type
#endif

namespace boost {

    template <typename Selector>
    struct has_emplace_member_function_selector
      : ::boost::mpl::if_<
            is_flat_associative_selector<Selector>
          , ::boost::mpl::true_
          , is_hashed_associative_selector<Selector>
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , has_emplace_member_function_selector
          , (Selector)
        )
    };

    template <typename IsBoost, typename AllocatorSelector>
    struct has_emplace_member_function_selector<
        vector_selector<IsBoost,AllocatorSelector>
    > : BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE
    {
    };

    template <typename IsBoost, typename AllocatorSelector>
    struct has_emplace_member_function_selector<
        deque_selector<IsBoost,AllocatorSelector>
    > : BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE
    {
    };

    template <typename IsBoost, typename AllocatorSelector>
    struct has_emplace_member_function_selector<
        list_selector<IsBoost,AllocatorSelector>
    > : BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE
    {
    };

    template <typename AllocatorSelector>
    struct has_emplace_member_function_selector<
        stable_vector_selector<AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename AllocatorSelector>
    struct has_emplace_member_function_selector<
        slist_selector<AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct has_emplace_member_function_selector<
        set_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE
    {
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct has_emplace_member_function_selector<
        map_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE
    {
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct has_emplace_member_function_selector<
        multiset_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE
    {
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct has_emplace_member_function_selector<
        multimap_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE
    {
    };
}  // namespace boost

#undef BOOST_HAS_EMPLACE_MFUNC_SELECTOR_SPEC_BASE

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_HAS_EMPLACE_MFUNC_SELECTOR_HPP_INCLUDED

