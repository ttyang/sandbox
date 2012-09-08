//=======================================================================
// Copyright (C) 2011-2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_HAS_STABLE_ITERS_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_HAS_STABLE_ITERS_SELECTOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container_gen/selectors.hpp>

#if defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/container_gen/is_random_access_selector.hpp>
#include <boost/container_gen/is_hashed_assoc_selector.hpp>

namespace boost {

    template <typename Selector>
    struct has_stable_iterators_selector
      : ::boost::mpl::and_<
            ::boost::mpl::not_<is_random_access_selector<Selector> >
          , ::boost::mpl::not_<is_hashed_associative_selector<Selector> >
        >
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , has_stable_iterators_selector
          , (Selector)
        )
    };
}  // namespace boost

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename AllocatorSelector>
    struct has_stable_iterators_selector<
        stable_vector_selector<AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct has_stable_iterators_selector<
        flat_set_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::false_
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct has_stable_iterators_selector<
        flat_map_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::false_
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct has_stable_iterators_selector<
        flat_multiset_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::false_
    {
    };

    template <typename CompareSelector, typename AllocatorSelector>
    struct has_stable_iterators_selector<
        flat_multimap_selector<CompareSelector,AllocatorSelector>
    > : ::boost::mpl::false_
    {
    };
}  // namespace boost

#endif  // !BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#else  // !defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/container_gen/container_gen.hpp>
#include <boost/detail/metafunction/has_stable_iterators.hpp>

//[reference__has_stable_iterators_selector
namespace boost {

    template <typename Selector>
    struct has_stable_iterators_selector
        //<-
      : ::boost::detail::metafunction::has_stable_iterators<
            typename container_gen<Selector,int>::type
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , has_stable_iterators_selector
          , (Selector)
        )
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_MPL_CFG_NO_HAS_XXX

#if !defined BOOST_MSVC
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <>
    struct has_stable_iterators_selector<array_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct has_stable_iterators_selector<ptr_array_selector_base>
      : ::boost::mpl::true_
    {
    };
}  // namespace boost

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename ConstantSize, typename IsTR1>
    struct has_stable_iterators_selector<array_selector<ConstantSize,IsTR1> >
      : ::boost::mpl::true_
    {
    };

    template <typename ConstantSize, typename CloneAllocator>
    struct has_stable_iterators_selector<
        ptr_array_selector<ConstantSize,CloneAllocator>
    > : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#endif  // BOOST_MSVC
#endif  // BOOST_CONTAINER_GEN_HAS_STABLE_ITERS_SELECTOR_HPP_INCLUDED

