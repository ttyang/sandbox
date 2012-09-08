//=======================================================================
// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CONTAINER_GEN_IS_TR1_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_TR1_SELECTOR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

//[reference__is_tr1_selector
namespace boost {

    template <typename Selector>
    struct is_tr1_selector
        //<-
      : ::boost::mpl::false_
        //->
    {
        // typedef ... type;
        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_tr1_selector, (Selector))
        //->
    };
}  // namespace boost
//]

#include <boost/config.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <boost/mpl/if.hpp>
#include <boost/container_gen/selectors.hpp>

namespace boost {

#if !defined BOOST_MSVC
    template <typename ConstantSize, typename IsTR1>
    struct is_tr1_selector<array_selector<ConstantSize,IsTR1> >
      : ::boost::mpl::if_<IsTR1,::boost::mpl::true_,::boost::mpl::false_>::type
    {
    };
#endif

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_tr1_selector<
        hash_set_selector<IsTR1,HashSelector,CompareSelector,AllocatorSelector>
    > : ::boost::mpl::if_<IsTR1,::boost::mpl::true_,::boost::mpl::false_>::type
    {
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_tr1_selector<
        hash_map_selector<IsTR1,HashSelector,CompareSelector,AllocatorSelector>
    > : ::boost::mpl::if_<IsTR1,::boost::mpl::true_,::boost::mpl::false_>::type
    {
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_tr1_selector<
        hash_multiset_selector<
            IsTR1
          , HashSelector
          , CompareSelector
          , AllocatorSelector
        >
    > : ::boost::mpl::if_<IsTR1,::boost::mpl::true_,::boost::mpl::false_>::type
    {
    };

    template <
        typename IsTR1
      , typename HashSelector
      , typename CompareSelector
      , typename AllocatorSelector
    >
    struct is_tr1_selector<
        hash_multimap_selector<
            IsTR1
          , HashSelector
          , CompareSelector
          , AllocatorSelector
        >
    > : ::boost::mpl::if_<IsTR1,::boost::mpl::true_,::boost::mpl::false_>::type
    {
    };
}  // namespace boost

#endif  // !BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_IS_TR1_SELECTOR_HPP_INCLUDED

