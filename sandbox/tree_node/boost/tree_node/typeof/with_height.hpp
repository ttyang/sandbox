// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_TYPEOF_WITH_HEIGHT_HPP_INCLUDED
#define BOOST_TREE_NODE_TYPEOF_WITH_HEIGHT_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/tree_node/with_height.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_height_base, 5)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_height, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_height, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_height, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_height_gen, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_height_gen, 2)

#endif  // BOOST_TREE_NODE_TYPEOF_WITH_HEIGHT_HPP_INCLUDED

