// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/properties.hpp>
#include "initialize_euler_graphs.hpp"
#include "find_eulerian_trail.hpp"

int test_main(int argc, char** argv)
{
    boost::adjacency_list<
        boost::listS
      , boost::vecS
      , boost::undirectedS
      , boost::no_property
      , boost::property<boost::edge_weight_t,unsigned int>
    > paper_clip(4);
    boost::adjacency_list<
        boost::listS
      , boost::vecS
      , boost::directedS
      , boost::no_property
      , boost::property<boost::edge_weight_t,unsigned int>
    > digraph(5);
    boost::adjacency_list<
        boost::listS
      , boost::vecS
      , boost::bidirectionalS
      , boost::no_property
      , boost::property<boost::edge_weight_t,unsigned int>
    > bidigraph(5);

    initialize_two_triangles(paper_clip);
    initialize_almost_complete_graph(bidigraph);
    initialize_almost_complete_graph(digraph);
    find_eulerian_trail_test(paper_clip);
    find_eulerian_trail_test(digraph);
    find_eulerian_trail_test(bidigraph);

    return 0;
}

