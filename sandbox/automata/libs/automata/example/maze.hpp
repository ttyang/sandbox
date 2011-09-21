// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_EXAMPLE_MAZE_HPP_INCLUDED
#define LIBS_AUTOMATA_EXAMPLE_MAZE_HPP_INCLUDED

#include <vector>
#include <iterator>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

//[example__make_maze__rng
template <typename Graph>
void make_maze(Graph& g)
{
    boost::mt19937
        rng_engine;
    boost::uniform_int<std::size_t>
        weight_range(1, 16384);
    boost::variate_generator<boost::mt19937&,boost::uniform_int<std::size_t> >
        random_weight(rng_engine, weight_range);
    //]

    //[example__make_maze__util_type
    typedef boost::adjacency_list<
                boost::vecS
              , boost::vecS  // Let the vertex_index_t property map be built-in.
              , boost::undirectedS
              , boost::no_property
              , boost::property<boost::edge_weight_t,std::size_t>
            >
            UtilityGraph;
    //]

    //[example__make_maze__util_graph
    UtilityGraph u_g(30);
    boost::graph_traits<UtilityGraph>::edge_descriptor e;
    bool b;

    for (std::size_t r = 0; r < 30; r += 5)
    {
        for (std::size_t c = r + 4; r < c; --c)
        {
            boost::tie(e, b)
              = boost::add_edge(
                    boost::vertex(c, u_g)
                  , boost::vertex(c - 1, u_g)
                  , u_g
                );

            if (b)
            {
                boost::put(
                    boost::get(boost::edge_weight, u_g)
                  , e
                  , random_weight()
                );
            }
        }
    }

    for (std::size_t i = 0; i < 25; ++i)
    {
        boost::tie(e, b)
           = boost::add_edge(
                 boost::vertex(i, u_g)
               , boost::vertex(i + 5, u_g)
               , u_g
             );

        if (b)
        {
            boost::put(
                boost::get(boost::edge_weight, u_g)
              , e
              , random_weight()
            );
        }
    }
    //]

    //[example__make_maze__do_it
    std::vector<boost::graph_traits<UtilityGraph>::edge_descriptor> edges;
    boost::kruskal_minimum_spanning_tree(u_g, std::back_inserter(edges));
    //]

    //[example__make_maze__finish
    for (std::size_t i = 0; i < 30; ++i)
    {
        boost::add_vertex(g);
    }

    for (std::size_t i = 0; i < edges.size(); ++i)
    {
        boost::add_edge(
            boost::vertex(
                boost::get(
                    boost::get(boost::vertex_index, u_g)
                  , boost::source(edges[i], u_g)
                )
              , g
            )
          , boost::vertex(
                boost::get(
                    boost::get(boost::vertex_index, u_g)
                  , boost::target(edges[i], u_g)
                )
              , g
            )
          , g
        );
    }
}
//]

#endif  // LIBS_AUTOMATA_EXAMPLE_MAZE_HPP_INCLUDED

