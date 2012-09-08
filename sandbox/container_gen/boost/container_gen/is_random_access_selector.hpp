//=======================================================================
// Copyright (C) 2011-2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_IS_RANDOM_ACCESS_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_RANDOM_ACCESS_SELECTOR_HPP_INCLUDED

#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/mpl/bool.hpp>

namespace boost {

    template <typename Selector>
    struct is_random_access_selector : ::boost::mpl::false_
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_random_access_selector,(Selector))
    };
}  // namespace boost

#include <boost/config.hpp>
#include <boost/container_gen/selectors.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

#if !defined BOOST_MSVC
    template <>
    struct is_random_access_selector<array_selector_base>
      : ::boost::mpl::true_
    {
    };
#endif

    template <>
    struct is_random_access_selector<vector_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_random_access_selector<deque_selector_base>
      : ::boost::mpl::true_
    {
    };

#if !defined BOOST_MSVC
    template <>
    struct is_random_access_selector<ptr_array_selector_base>
      : ::boost::mpl::true_
    {
    };
#endif

    template <>
    struct is_random_access_selector<ptr_vector_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_random_access_selector<ptr_deque_selector_base>
      : ::boost::mpl::true_
    {
    };
}  // namespace boost

#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

#if !defined BOOST_MSVC
    template <typename ConstantSize, typename IsTR1>
    struct is_random_access_selector<array_selector<ConstantSize,IsTR1> >
      : ::boost::mpl::true_
    {
    };
#endif

    template <typename IsBoost, typename AllocatorSelector>
    struct is_random_access_selector<
        vector_selector<IsBoost,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename AllocatorSelector>
    struct is_random_access_selector<
        stable_vector_selector<AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename IsBoost, typename AllocatorSelector>
    struct is_random_access_selector<
        deque_selector<IsBoost,AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

#if !defined BOOST_MSVC
    template <typename ConstantSize, typename CloneAllocator>
    struct is_random_access_selector<
        ptr_array_selector<ConstantSize,CloneAllocator>
    > : ::boost::mpl::true_
    {
    };
#endif

    template <typename CloneAllocator, typename Allocator>
    struct is_random_access_selector<
        ptr_vector_selector<CloneAllocator,Allocator>
    > : ::boost::mpl::true_
    {
    };

    template <typename CloneAllocator, typename Allocator>
    struct is_random_access_selector<
        ptr_deque_selector<CloneAllocator,Allocator>
    > : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#else  // !defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/container_gen/container_gen.hpp>
#include <boost/detail/metafunction/is_random_access_container.hpp>

//[reference__is_random_access_selector
namespace boost {

    template <typename Selector>
    struct is_random_access_selector
        //<-
      : ::boost::detail::metafunction::is_random_access_container<
            typename container_gen<Selector,int>::type
        >
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_random_access_selector,(Selector))
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_MPL_CFG_NO_HAS_XXX

#endif  // BOOST_CONTAINER_GEN_IS_RANDOM_ACCESS_SELECTOR_HPP_INCLUDED

