// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_TYPEOF_HPP_INCLUDED
#define BOOST_TREE_NODE_TYPEOF_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/tree_node.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(boost::tree_node::traversal_state)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::breadth_first_iterator, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::pre_order_iterator, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::post_order_iterator, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::depth_first_iterator, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::in_order_iterator, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::factory, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::tree_node_base, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::shared_tree_node_base, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_binary_node_base, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_binary_node, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::tree_node::raw_binary_node_gen)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_node_base, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_node, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_node_gen, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::simple_node_base, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::simple_node, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::simple_node_gen, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_associative_node_base, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_associative_node, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_associative_node_gen, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::tree_node::simple_associative_node_base
  , 4
)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::simple_associative_node, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::tree_node::simple_associative_node_gen
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::tree_node::with_child_range_access_base
  , 4
)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::with_child_range_access, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::tree_node::with_child_range_access_gen
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::with_depth_base, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::with_depth, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::with_depth_gen, 1)

#endif  // BOOST_TREE_NODE_TYPEOF_HPP_INCLUDED

