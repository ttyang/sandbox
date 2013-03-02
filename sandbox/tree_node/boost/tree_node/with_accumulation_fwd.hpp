// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_ACCUMULATION_FWD_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_ACCUMULATION_FWD_HPP_INCLUDED

#include <boost/config.hpp>

#if defined BOOST_NO_SFINAE
#error boost::tree_node::with_accumulation requires working boost::enable_if.
#endif

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#error boost::tree_node::with_accumulation uses Boost.Accumulators,
#error which requires working partial template specialization.
#endif

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/tree_node/key/accumulation.hpp>
#include <boost/tree_node/intrinsic/value_at_key.hpp>

namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    class with_accumulation_base;

    template <
        typename BaseGenerator
      , typename T1
      , typename T2 = void
      , typename AccumulationKey = default_accumulation_key
    >
    struct with_accumulation;
}}  // namespace boost::tree_node

//[reference__with_accumulation_base__at_key
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
      , typename AccumulationKey
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<
            accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
          , AccumulationKey
        >
      , typename ::boost::mpl::eval_if<
            ::std::tr1::is_void<Value>
          , result_of::value_at_key<
                with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >
              , Key
            >
          , ::boost::mpl::identity<Value>
        >::type const&
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
          , AccumulationKey const& key
        );

    template <
        typename AccumulationKey
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<
            accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
          , AccumulationKey
        >
      , typename ::boost::mpl::eval_if<
            ::std::tr1::is_void<Value>
          , result_of::value_at_key<
                with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >
              , Key
            >
          , ::boost::mpl::identity<Value>
        >::type const&
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
        );
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_ACCUMULATION_FWD_HPP_INCLUDED

