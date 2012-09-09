// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/properties.hpp>
#include "find_eulerian_cycle.hpp"

int test_main(int argc, char** argv)
{
    find_eulerian_cycle_test<
        boost::adjacency_list<
            boost::listS
          , boost::vecS
          , boost::undirectedS
          , boost::no_property
          , boost::property<boost::edge_weight_t,unsigned int>
        >
    >(5);
    find_eulerian_cycle_test<
        boost::adjacency_list<
            boost::listS
          , boost::vecS
          , boost::directedS
          , boost::no_property
          , boost::property<boost::edge_weight_t,unsigned int>
        >
    >(5);
    find_eulerian_cycle_test<
        boost::adjacency_list<
            boost::listS
          , boost::vecS
          , boost::bidirectionalS
          , boost::no_property
          , boost::property<boost::edge_weight_t,unsigned int>
        >
    >(5);
    return 0;
}

