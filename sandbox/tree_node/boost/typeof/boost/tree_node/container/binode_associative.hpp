// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_TREE_NODE_CONTAINER_BINODE_ASSOCIATIVE_HPP
#define BOOST_TYPEOF_BOOST_TREE_NODE_CONTAINER_BINODE_ASSOCIATIVE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/container_gen/selectors.hpp>
#include <boost/typeof/boost/tree_node/balancer/red_black.hpp>
#include <boost/tree_node/container/binode_associative.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::tree_node::binode_associative_container
  , 6
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_set, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_set, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_set, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_set, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_multiset, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_multiset, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_multiset, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_multiset, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_map, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_map, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_map, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_map, 5)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_multimap, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_multimap, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_multimap, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::binode_multimap, 5)

#endif  // BOOST_TYPEOF_BOOST_TREE_NODE_CONTAINER_BINODE_ASSOCIATIVE_HPP

