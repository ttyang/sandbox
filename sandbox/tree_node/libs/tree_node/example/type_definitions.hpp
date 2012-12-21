// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_TYPE_DEFINITIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_TYPE_DEFINITIONS_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/accumulators/statistics/sum_kahan.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/tree_node/count_key.hpp>
#include <boost/tree_node/height_key.hpp>
#include <boost/tree_node/accumulation_key.hpp>

typedef boost::tree_node::accumulation_key<
            boost::tree_node::count_key
          , boost::accumulators::tag::sum_kahan
        >
        AccuCountKey;
typedef boost::tree_node::accumulation_key<
            boost::tree_node::height_key
          , boost::accumulators::tag::max
          , boost::mpl::false_
          , boost::mpl::false_
        >
        AccuHeightKey;
typedef boost::tree_node::accumulation_key<
            boost::tree_node::accumulation_key<>
          , boost::accumulators::tag::mean
        >
        AccuAccuKey;

namespace example_keys {

    struct your_uint
    {
    };

    struct your_char
    {
    };
}

typedef boost::tree_node::accumulation_key<example_keys::your_uint>
        AccuYourUintKey;

#include <boost/tree_node/preprocessor.hpp>
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
#include <boost/fusion/container/map.hpp>

typedef boost::fusion::map<
            boost::fusion::pair<example_keys::your_uint,unsigned int>
          , boost::fusion::pair<example_keys::your_char,char>
        >
        DataMap;
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

#endif  // LIBS_TREE_NODE_EXAMPLE_TYPE_DEFINITIONS_HPP_INCLUDED

