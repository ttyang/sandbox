// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_TEST_TYPE_DEFINITIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_TEST_TYPE_DEFINITIONS_HPP_INCLUDED

#include <deque>
#include <set>
#include <map>
#include <boost/cstdint.hpp>
#include <boost/typeof/boost/tree_node/with_count.hpp>
#include <boost/typeof/boost/tree_node/with_height.hpp>
#include <boost/typeof/boost/tree_node/with_red_black_flag.hpp>
#include <boost/typeof/boost/tree_node/binary_node.hpp>

//[test__container_types
typedef std::deque<boost::int32_t>
        ValueSequence;
typedef std::set<boost::int32_t>
        ValueSet;
typedef std::map<boost::int32_t,boost::int32_t>
        ValueMap;
//]

//[test__node_types
typedef boost::tree_node::with_red_black_flag_gen<
            boost::tree_node::with_count_base_gen<
                boost::tree_node::binary_node_base_gen<>
            >
        >
        RedBlackNodeGen;
typedef boost::tree_node::with_height_gen<
            boost::tree_node::with_count_base_gen<
                boost::tree_node::binary_node_base_gen<>
            >
        >
        AVLNodeGen;
//]

#endif  // LIBS_TREE_NODE_TEST_TYPE_DEFINITIONS_HPP_INCLUDED

