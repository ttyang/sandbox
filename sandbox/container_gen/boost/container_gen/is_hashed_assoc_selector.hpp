//=============================================================================
// Copyright (C) 2011-2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_IS_HASHED_ASSOC_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_HASHED_ASSOC_SELECTOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if defined BOOST_NO_SFINAE || defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/mpl/bool.hpp>

namespace boost {

    template <typename Selector>
    struct is_hashed_associative_selector : ::boost::mpl::false_
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , is_hashed_associative_selector
          , (Selector)
        )
    };
}  // namespace boost

#include <boost/container_gen/selectors.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined BOOST_HAS_HASH

namespace boost {

    template <>
    struct is_hashed_associative_selector<hash_set_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_hashed_associative_selector<hash_map_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_hashed_associative_selector<hash_multiset_selector_base>
      : ::boost::mpl::true_
    {
    };

    template <>
    struct is_hashed_associative_selector<hash_multimap_selector_base>
      : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_HAS_HASH
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost {

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_hashed_associative_selector<hash_set_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_hashed_associative_selector<hash_map_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_hashed_associative_selector<hash_multiset_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_hashed_associative_selector<hash_multimap_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_hashed_associative_selector<ptr_hash_set_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_hashed_associative_selector<ptr_hash_map_selector<T0,T1,T2,T3> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_hashed_associative_selector<
        ptr_hash_multiset_selector<T0,T1,T2,T3>
    > : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_hashed_associative_selector<
        ptr_hash_multimap_selector<T0,T1,T2,T3>
    > : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#else  // !defined BOOST_NO_SFINAE && !defined BOOST_MPL_CFG_NO_HAS_XXX

#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/if.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/detail/metafunction/is_hashed_assoc_container.hpp>

namespace boost { namespace detail { namespace metafunction {

    template <typename Selector>
    struct is_hashed_associative_selector_impl
      : ::boost::detail::metafunction::is_hashed_associative_container<
            typename container_gen<Selector,int>::type
        >
    {
    };
}}}  // namespace boost::detail::metafunction

//[reference__is_hashed_associative_selector
namespace boost {

    template <typename Selector>
    struct is_hashed_associative_selector
        //<-
      : ::boost::mpl::if_<
            typename ::boost::mpl::aux::has_type<
                container_gen<Selector,int>
            >::type
          , detail::metafunction::is_hashed_associative_selector_impl<Selector>
          , ::boost::mpl::false_
        >::type
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , is_hashed_associative_selector
          , (Selector)
        )
        //->
    };
}  // namespace boost
//]

#endif  // BOOST_NO_SFINAE, BOOST_MPL_CFG_NO_HAS_XXX

#endif  // BOOST_CONTAINER_GEN_IS_HASHED_ASSOC_SELECTOR_HPP_INCLUDED

