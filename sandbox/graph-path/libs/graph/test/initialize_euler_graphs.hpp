// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_TEST_INITIALIZE_EULER_GRAPHS_HPP
#define LIBS_GRAPH_TEST_INITIALIZE_EULER_GRAPHS_HPP

#include <boost/graph/graph_traits.hpp>

template <typename Graph>
void initialize_two_triangles(Graph& g)
{
    boost::add_edge(boost::vertex(0, g), boost::vertex(1, g), g);
    boost::add_edge(boost::vertex(0, g), boost::vertex(2, g), g);
    boost::add_edge(boost::vertex(1, g), boost::vertex(2, g), g);
    boost::add_edge(boost::vertex(1, g), boost::vertex(3, g), g);
    boost::add_edge(boost::vertex(2, g), boost::vertex(3, g), g);
}

template <typename Graph>
void initialize_almost_complete_graph(Graph& g)
{
    typedef typename boost::graph_traits<Graph>::vertices_size_type Index;

    boost::add_edge(boost::vertex(0, g), boost::vertex(1, g), g);
    boost::add_edge(
        boost::vertex(1, g)
      , boost::vertex(boost::num_vertices(g) - 1, g)
      , g
    );

    for (Index j = 2; j < boost::num_vertices(g) - 1; ++j)
    {
        for (Index i = 1; i < j; ++i)
        {
            boost::add_edge(boost::vertex(i, g), boost::vertex(j, g), g);
            boost::add_edge(boost::vertex(j, g), boost::vertex(i, g), g);
        }
    }
}

#endif  // LIBS_GRAPH_TEST_INITIALIZE_EULER_GRAPHS_HPP

