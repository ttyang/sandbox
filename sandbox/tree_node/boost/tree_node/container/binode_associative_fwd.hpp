// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_CONTAINER_BINODE_ASSOCIATIVE_FWD_HPP_INCLUDED
#define BOOST_TREE_NODE_CONTAINER_BINODE_ASSOCIATIVE_FWD_HPP_INCLUDED

#include <boost/container_gen/selectors.hpp>
#include <boost/tree_node/balancer/red_black.hpp>

namespace boost { namespace tree_node {

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    class binode_associative_container;

    template <
        typename NodeGenerator
      , typename T
      , typename CompareSelector = ::boost::default_ordering_selector
      , typename Balancer = red_black_balancer
    >
    class binode_set;

    template <
        typename NodeGenerator
      , typename T
      , typename CompareSelector = ::boost::default_ordering_selector
      , typename Balancer = red_black_balancer
    >
    class binode_multiset;

    template <
        typename NodeGenerator
      , typename Key
      , typename Mapped
      , typename CompareSelector = ::boost::default_ordering_selector
      , typename Balancer = red_black_balancer
    >
    class binode_map;

    template <
        typename NodeGenerator
      , typename Key
      , typename Mapped
      , typename CompareSelector = ::boost::default_ordering_selector
      , typename Balancer = red_black_balancer
    >
    class binode_multimap;
}}  // namespace boost::tree_node

#endif  // BOOST_TREE_NODE_CONTAINER_BINODE_ASSOCIATIVE_FWD_HPP_INCLUDED

