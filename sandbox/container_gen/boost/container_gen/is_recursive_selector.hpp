//=======================================================================
// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_IS_RECURSIVE_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_RECURSIVE_SELECTOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container_gen/is_ptr_selector.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__is_recursive_selector
namespace boost {

    template <typename Selector>
    struct is_recursive_selector
        //<-
      : is_ptr_selector<Selector>
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_recursive_selector, (Selector))
        //->
    };
}  // namespace boost
//]

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/container_gen/is_hashed_assoc_selector.hpp>
#include <boost/container_gen/selectors.hpp>

namespace boost {

    template <typename Selector>
    struct is_recursive_selector
      : ::boost::mpl::if_<
            is_ptr_selector<Selector>
          , ::boost::mpl::true_
          , is_hashed_associative_selector<Selector>
        >::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_recursive_selector, (Selector))
    };

    template <typename IsBoost, typename AllocatorSelector>
    struct is_recursive_selector<vector_selector<IsBoost,AllocatorSelector> >
      : ::boost::mpl::if_<
            IsBoost
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename IsBoost, typename AllocatorSelector>
    struct is_recursive_selector<deque_selector<IsBoost,AllocatorSelector> >
      : ::boost::mpl::if_<
            IsBoost
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename IsBoost, typename AllocatorSelector>
    struct is_recursive_selector<list_selector<IsBoost,AllocatorSelector> >
      : ::boost::mpl::if_<
            IsBoost
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename AllocatorSelector>
    struct is_recursive_selector<stable_vector_selector<AllocatorSelector> >
      : ::boost::mpl::true_
    {
    };

    template <typename AllocatorSelector>
    struct is_recursive_selector<slist_selector<AllocatorSelector> >
      : ::boost::mpl::true_
    {
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_recursive_selector<
        set_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : ::boost::mpl::if_<
            IsBoost
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_recursive_selector<
        map_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : IsBoost
    {
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_recursive_selector<
        multiset_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : ::boost::mpl::if_<
            IsBoost
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <
        typename IsBoost
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_recursive_selector<
        multimap_selector<IsBoost,CompareSelector,AllocatorSelector>
    > : ::boost::mpl::if_<
            IsBoost
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct is_recursive_selector<
        flat_set_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct is_recursive_selector<
        flat_map_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct is_recursive_selector<
        flat_multiset_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct is_recursive_selector<
        flat_multimap_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_IS_RECURSIVE_SELECTOR_HPP_INCLUDED

