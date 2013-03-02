// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_TYPE_DEFINITIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_TYPE_DEFINITIONS_HPP_INCLUDED

#include <boost/tree_node/preprocessor.hpp>

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/typeof/boost/accumulators/statistics/sum_kahan.hpp>
#include <boost/typeof/boost/accumulators/statistics/max.hpp>
#include <boost/typeof/boost/accumulators/statistics/mean.hpp>
#include <boost/typeof/boost/accumulators/statistics/min.hpp>
#include <boost/typeof/boost/tree_node/key/count.hpp>
#include <boost/typeof/boost/tree_node/key/height.hpp>
#include <boost/typeof/boost/tree_node/key/accumulation.hpp>
#include <boost/fusion/container/map.hpp>

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
typedef boost::fusion::map<
            boost::fusion::pair<example_keys::your_uint,unsigned int>
          , boost::fusion::pair<example_keys::your_char,char>
        >
        DataMap;

//[example__gui__types
namespace example_keys {

    struct row_location
    {
    };

    struct row_height
    {
    };

    struct row_priority
    {
    };
}

typedef boost::tree_node::accumulation_key<
            example_keys::row_height
          , boost::accumulators::tag::sum
        >
        HeightSumKey;
typedef boost::tree_node::accumulation_key<
            example_keys::row_priority
          , boost::accumulators::tag::min
        >
        MinPriorityKey;
typedef boost::fusion::map<
            boost::fusion::pair<example_keys::row_location,unsigned int>
          , boost::fusion::pair<example_keys::row_height,unsigned int>
          , boost::fusion::pair<example_keys::row_priority,unsigned int>
        >
        GUITable;
//]

#if defined BOOST_TYPEOF_COMPLIANT
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(example_keys::your_uint)
BOOST_TYPEOF_REGISTER_TYPE(example_keys::your_char)
BOOST_TYPEOF_REGISTER_TYPE(example_keys::row_location)
BOOST_TYPEOF_REGISTER_TYPE(example_keys::row_height)
BOOST_TYPEOF_REGISTER_TYPE(example_keys::row_priority)
#endif

#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

#endif  // LIBS_TREE_NODE_EXAMPLE_TYPE_DEFINITIONS_HPP_INCLUDED

