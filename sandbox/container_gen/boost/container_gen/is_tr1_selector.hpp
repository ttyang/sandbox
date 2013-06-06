//=============================================================================
// Copyright (C) 2012-2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=============================================================================

#ifndef BOOST_CONTAINER_GEN_IS_TR1_SELECTOR_HPP_INCLUDED
#define BOOST_CONTAINER_GEN_IS_TR1_SELECTOR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/container_gen/selectors.hpp>

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

    template <>
    struct is_tr1_selector<tr1_hash_selector> : ::boost::mpl::true_
    {
    };
}  // namespace boost
//]

#include <boost/config.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#include <boost/mpl/if.hpp>
#include <boost/parameter.hpp>
#include <boost/container_gen/selector_keywords.hpp>
#include <boost/container_gen/detail/selector_signatures.hpp>

namespace boost {

#if !defined BOOST_MSVC
    template <typename T0, typename T1>
    struct is_tr1_selector<array_selector<T0,T1> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::array_selector_signature::bind<T0,T1>::type
              , ::boost::is_tr1_not_boost_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
#endif

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_tr1_selector<hash_set_selector<T0,T1,T2,T3> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::hashed_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
              , ::boost::is_tr1_not_boost_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_tr1_selector<hash_map_selector<T0,T1,T2,T3> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::hashed_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
              , ::boost::is_tr1_not_boost_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_tr1_selector<hash_multiset_selector<T0,T1,T2,T3> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::hashed_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
              , ::boost::is_tr1_not_boost_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };

    template <typename T0, typename T1, typename T2, typename T3>
    struct is_tr1_selector<hash_multimap_selector<T0,T1,T2,T3> >
      : ::boost::mpl::if_<
            typename ::boost::parameter::value_type<
                typename detail::hashed_associative_selector_signature::bind<
                    T0
                  , T1
                  , T2
                  , T3
                >::type
              , ::boost::is_tr1_not_boost_tag
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
}  // namespace boost

#endif  // !BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_CONTAINER_GEN_IS_TR1_SELECTOR_HPP_INCLUDED

