// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_TREE_NODE_ASSOCIATIVE_NODE_HPP
#define BOOST_TYPEOF_BOOST_TREE_NODE_ASSOCIATIVE_NODE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/ptr_container/ptr_map.hpp>
#include <boost/typeof/boost/container_gen/selectors.hpp>
#include <boost/tree_node/associative_node.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::associative_node_base, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::tree_node::associative_node_base_gen
  , 1
)
BOOST_TYPEOF_REGISTER_TYPE(
    ::boost::tree_node::associative_node_base_default_gen
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::associative_node, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::associative_node, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::associative_node_gen, 1)
BOOST_TYPEOF_REGISTER_TYPE(::boost::tree_node::associative_node_default_gen)

#endif  // BOOST_TYPEOF_BOOST_TREE_NODE_ASSOCIATIVE_NODE_HPP

