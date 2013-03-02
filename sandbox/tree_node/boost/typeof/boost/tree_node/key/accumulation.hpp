// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_TREE_NODE_KEY_ACCUMULATION_HPP
#define BOOST_TYPEOF_BOOST_TREE_NODE_KEY_ACCUMULATION_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/typeof/boost/accumulators/statistics/sum.hpp>
#include <boost/typeof/boost/tree_node/key/data.hpp>
#include <boost/tree_node/key/accumulation.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(::boost::tree_node::default_accumulation_key)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::accumulation_key, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::accumulation_key, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::accumulation_key, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::accumulation_key, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::tree_node::accumulation_key, 5)

#endif  // BOOST_TYPEOF_BOOST_TREE_NODE_KEY_ACCUMULATION_HPP

