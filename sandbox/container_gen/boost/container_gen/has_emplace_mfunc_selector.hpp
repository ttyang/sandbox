//=============================================================================
// Copyright (C) 2012-2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

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

#if !defined BOOST_NO_CXX11_RVALUE_REFERENCES
#include <boost/mpl/eval_if.hpp>
#endif

#include <boost/mpl/if.hpp>
#include <boost/container_gen/is_flat_assoc_selector.hpp>
#include <boost/container_gen/is_hashed_assoc_selector.hpp>
#include <boost/container_gen/is_heap_selector.hpp>
#include <boost/container_gen/selectors.hpp>

namespace boost {

    template <typename Selector>
    struct has_emplace_member_function_selector
#if defined BOOST_NO_CXX11_RVALUE_REFERENCES
      : ::boost::mpl::if_<
            is_flat_associative_selector<Selector>
          , ::boost::mpl::true_
          , is_hashed_associative_selector<Selector>
        >::type
#else
      : ::boost::mpl::eval_if<
            is_flat_associative_selector<Selector>
          , ::boost::mpl::true_
          , ::boost::mpl::if_<
                is_hashed_associative_selector<Selector>
              , ::boost::mpl::true_
              , is_heap_selector<Selector>
            >
        >::type
#endif  // BOOST_NO_CXX11_RVALUE_REFERENCES
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(
            1
          , has_emplace_member_function_selector
          , (Selector)
        )
    };

    template <typename T0, typename T1>
    struct has_emplace_member_function_selector<vector_selector<T0,T1> >
#if defined BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
      : ::boost::mpl::true_
#else
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::sequence_selector_signature::bind<T0,T1>::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
#endif  // BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
    {
    };

    template <typename T0, typename T1>
    struct has_emplace_member_function_selector<deque_selector<T0,T1> >
#if defined BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
      : ::boost::mpl::true_
#else
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::sequence_selector_signature::bind<T0,T1>::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
#endif  // BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
    {
    };

    template <typename T0, typename T1>
    struct has_emplace_member_function_selector<list_selector<T0,T1> >
#if defined BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
      : ::boost::mpl::true_
#else
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::sequence_selector_signature::bind<T0,T1>::type
              , ::boost::is_boost_not_std_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
#endif  // BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
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

    template <typename T0, typename T1, typename T2>
    struct has_emplace_member_function_selector<set_selector<T0,T1,T2> >
#if defined BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
      : ::boost::mpl::true_
#else
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::associative_selector_signature::bind<
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
#endif  // BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
    {
    };

    template <typename T0, typename T1, typename T2>
    struct has_emplace_member_function_selector<map_selector<T0,T1,T2> >
#if defined BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
      : ::boost::mpl::true_
#else
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::associative_selector_signature::bind<
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
#endif  // BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
    {
    };

    template <typename T0, typename T1, typename T2>
    struct has_emplace_member_function_selector<multiset_selector<T0,T1,T2> >
#if defined BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
      : ::boost::mpl::true_
#else
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::associative_selector_signature::bind<
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
#endif  // BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
    {
    };

    template <typename T0, typename T1, typename T2>
    struct has_emplace_member_function_selector<multimap_selector<T0,T1,T2> >
#if defined BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
      : ::boost::mpl::true_
#else
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::associative_selector_signature::bind<
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
#endif  // BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE
    {
    };
}  // namespace boost

#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_HAS_EMPLACE_MFUNC_SELECTOR_HPP_INCLUDED

