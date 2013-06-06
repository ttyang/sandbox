//=============================================================================
// Copyright (C) 2011-2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_IS_RANDOM_ACCESS_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_RANDOM_ACCESS_SELECTOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/bool.hpp>

#if defined BOOST_NO_SFINAE || defined BOOST_MPL_CFG_NO_HAS_XXX

namespace boost {

    template <typename Selector>
    struct is_random_access_selector : ::boost::mpl::false_
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_random_access_selector,(Selector))
    };
}  // namespace boost

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
    template <typename T0, typename T1>
    struct is_random_access_selector<array_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };
#endif

    template <typename T0, typename T1>
    struct is_random_access_selector<vector_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename AllocatorSelector>
    struct is_random_access_selector<
        stable_vector_selector<AllocatorSelector>
    > : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_random_access_selector<deque_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

#if !defined BOOST_MSVC
    template <typename T0, typename T1>
    struct is_random_access_selector<ptr_array_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };
#endif

    template <typename T0, typename T1>
    struct is_random_access_selector<ptr_vector_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_random_access_selector<ptr_deque_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#else  // !defined BOOST_NO_SFINAE && !defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/if.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/detail/metafunction/is_random_access_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename Selector>
    struct is_random_access_selector_impl
      : ::boost::detail::metafunction::is_random_access_container<
            typename container_gen<Selector,int>::type
        >
    {
    };
}}}  // namespace boost::detail::metafunction

//[reference__is_random_access_selector
namespace boost {

    template <typename Selector>
    struct is_random_access_selector
        //<-
      : ::boost::mpl::if_<
            typename ::boost::mpl::aux::has_type<
                container_gen<Selector,int>
            >::type
          , detail::metafunction::is_random_access_selector_impl<Selector>
          , ::boost::mpl::false_
        >::type
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_random_access_selector,(Selector))
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_NO_SFINAE, BOOST_MPL_CFG_NO_HAS_XXX

#endif  // BOOST_CONTAINER_GEN_IS_RANDOM_ACCESS_SELECTOR_HPP_INCLUDED

