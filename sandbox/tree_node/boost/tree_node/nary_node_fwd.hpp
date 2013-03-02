// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_NARY_NODE_FWD_HPP_INCLUDED
#define BOOST_TREE_NODE_NARY_NODE_FWD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/key/data.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/utility/enable_if.hpp>
#include <boost/tr1/type_traits.hpp>
#endif

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/tree_node/intrinsic/has_key.hpp>
#endif

namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Selector>
    class nary_node_base;

    template <typename T, typename Selector = ::boost::ptr_dequeS>
    struct nary_node;
}}  // namespace boost::tree_node

//[reference__nary_node_base__at_data_key__const
namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Selector>
    typename nary_node_base<
        Derived
      , T
      , Selector
    >::traits::data_type const&
        get(
            nary_node_base<Derived,T,Selector> const& node
          , data_key const& key
        );

//<-
#if defined BOOST_NO_SFINAE
//->
    template <typename Key, typename Derived, typename T, typename Selector>
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,data_key>
      , typename nary_node_base<
            Derived
          , T
          , Selector
        >::traits::data_type const&
    >::type
        get(nary_node_base<Derived,T,Selector> const& node);
//<-
#endif  // BOOST_NO_SFINAE
//->
}}  // namespace boost::tree_node
//]

//[reference__nary_node_base__at_data_key
namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Selector>
    typename nary_node_base<Derived,T,Selector>::traits::data_type&
        get(nary_node_base<Derived,T,Selector>& node, data_key const& key);

//<-
#if defined BOOST_NO_SFINAE
//->
    template <typename Key, typename Derived, typename T, typename Selector>
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,data_key>
      , typename nary_node_base<
            Derived
          , T
          , Selector
        >::traits::data_type&
    >::type
        get(nary_node_base<Derived,T,Selector>& node);
//<-
#endif  // BOOST_NO_SFINAE
//->
}}  // namespace boost::tree_node
//]

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
//[reference__nary_node_base__at_key__const
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename T
      , typename Selector
      , typename FusionKey
    >
    typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T const,FusionKey>
    >::type
        get(
            nary_node_base<Derived,T,Selector> const& node
          , FusionKey const& key
        );

    template <
        typename FusionKey
      , typename Derived
      , typename T
      , typename Selector
    >
    typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T const,FusionKey>
    >::type
        get(nary_node_base<Derived,T,Selector> const& node);
}}  // namespace boost::tree_node
//]

//[reference__nary_node_base__at_key
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename T
      , typename Selector
      , typename FusionKey
    >
    typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T,FusionKey>
    >::type
        get(nary_node_base<Derived,T,Selector>& node, FusionKey const& key);

    template <
        typename FusionKey
      , typename Derived
      , typename T
      , typename Selector
    >
    typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T,FusionKey>
    >::type
        get(nary_node_base<Derived,T,Selector>& node);
}}  // namespace boost::tree_node
//]
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

//[reference__nary_node_base__put_data
namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Selector, typename V>
    void
        put(
            nary_node_base<Derived,T,Selector>& node
          , data_key const& key
          , V const& value
        );
}}  // namespace boost::tree_node
//]

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
//[reference__nary_node_base__put
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename T
      , typename Selector
      , typename FusionKey
      , typename V
    >
    void
        put(
            nary_node_base<Derived,T,Selector>& node
          , FusionKey const& key
          , V const& value
          , typename ::boost::enable_if<
              typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                  typename ::boost::fusion::traits::is_sequence<T>::type
                , ::boost::fusion::traits::is_associative<T>
                , ::boost::mpl::false_
                >::type
              , result_of::has_key<
                  nary_node_base<Derived,T,Selector>
                , FusionKey
                >
              , ::boost::mpl::false_
              >::type
            , ::boost::mpl::true_
            >::type = ::boost::mpl::true_()
        );
}}  // namespace boost::tree_node
//]
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

#endif  // BOOST_TREE_NODE_NARY_NODE_FWD_HPP_INCLUDED

