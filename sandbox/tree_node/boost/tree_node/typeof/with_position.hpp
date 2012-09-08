// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_TYPEOF_WITH_POSITION_HPP_INCLUDED
#define BOOST_TREE_NODE_TYPEOF_WITH_POSITION_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/tree_node/with_position.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_position_base, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_position, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_position, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::with_position_gen, 1)

#endif  // BOOST_TREE_NODE_TYPEOF_WITH_POSITION_HPP_INCLUDED

