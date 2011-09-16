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
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_node, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::simple_node, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::raw_assocoative_node, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tree_node::simple_assocoative_node, 3)

#endif  // BOOST_TREE_NODE_TYPEOF_HPP_INCLUDED

