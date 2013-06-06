//=============================================================================
// Copyright (C) 2012-2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

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
#include <boost/parameter.hpp>
#include <boost/container_gen/is_hashed_assoc_selector.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/selector_keywords.hpp>
#include <boost/container_gen/detail/selector_signatures.hpp>

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

    template <typename T0, typename T1>
    struct is_recursive_selector<vector_selector<T0,T1> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::sequence_selector_signature::bind<T0,T1>::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T0, typename T1>
    struct is_recursive_selector<deque_selector<T0,T1> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::sequence_selector_signature::bind<T0,T1>::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T0, typename T1>
    struct is_recursive_selector<list_selector<T0,T1> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::sequence_selector_signature::bind<T0,T1>::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
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

    template <typename T0, typename T1, typename T2>
    struct is_recursive_selector<set_selector<T0,T1,T2> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::boost_or_std_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_recursive_selector<map_selector<T0,T1,T2> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::boost_or_std_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_recursive_selector<multiset_selector<T0,T1,T2> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::boost_or_std_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T0, typename T1, typename T2>
    struct is_recursive_selector<multimap_selector<T0,T1,T2> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::boost_or_std_assoc_selector_signature::bind<
                    T0
                  , T1
                  , T2
                >::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T0, typename T1>
    struct is_recursive_selector<flat_set_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_recursive_selector<flat_map_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_recursive_selector<flat_multiset_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };

    template <typename T0, typename T1>
    struct is_recursive_selector<flat_multimap_selector<T0,T1> >
      : ::boost::mpl::true_
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_IS_RECURSIVE_SELECTOR_HPP_INCLUDED

