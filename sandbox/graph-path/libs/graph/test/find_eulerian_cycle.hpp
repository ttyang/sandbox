// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_TEST_FIND_EULERIAN_CYCLE_HPP
#define LIBS_GRAPH_TEST_FIND_EULERIAN_CYCLE_HPP

#include <iterator>
#include <list>
#include <boost/tr1/tuple.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/find_eulerian_cycle.hpp>
#include "initialize_complete_graph.hpp"
#include "eulerian_path_visitor.hpp"

template <typename Graph>
void
    find_eulerian_cycle_test(
        typename boost::graph_traits<Graph>::vertices_size_type vertex_count
    )
{
    typedef std::list<typename boost::graph_traits<Graph>::edge_descriptor>
            EdgeList;
    typedef typename boost::property_map<Graph,boost::edge_weight_t>::type
            EdgeMap;

    Graph g(vertex_count);
    typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end, ui;
    typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;
    EdgeMap edge_map = boost::get(boost::edge_weight, g);

    initialize_complete_graph(g);

    for (std::tr1::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
    {
        EdgeList path;
        unsigned int edge_count = 0;

        for (ui = boost::vertices(g).first; ui != vi_end; ++ui)
        {
            for (
                std::tr1::tie(ei, ei_end) = boost::out_edges(*ui, g);
                ei != ei_end;
                ++ei
            )
            {
                boost::put(edge_map, *ei, 0);
            }
        }

        boost::find_eulerian_cycle(
            g
          , std::back_inserter(path)
          , boost::visitor(
                eulerian_path_test_visitor<EdgeMap>(edge_count, edge_map)
            ).root_vertex(*vi)
        );

        BOOST_CHECK(path.size() == edge_count);
        BOOST_CHECK(edge_count == boost::num_edges(g));
        BOOST_CHECK(*vi == boost::source(path.front(), g));
        BOOST_CHECK(*vi == boost::target(path.back(), g));

        typename EdgeList::const_iterator p_itr = path.begin();
        typename EdgeList::const_iterator p_end = path.end();

        for (
            typename EdgeList::const_iterator c_itr = path.begin();
            ++c_itr != p_end;
            ++p_itr
        )
        {
            BOOST_CHECK(boost::target(*p_itr, g) == boost::source(*c_itr, g));
        }

        for (ui = boost::vertices(g).first; ui != vi_end; ++ui)
        {
            for (
                std::tr1::tie(ei, ei_end) = boost::out_edges(*ui, g);
                ei != ei_end;
                ++ei
            )
            {
                BOOST_CHECK(1 == boost::get(edge_map, *ei));
            }
        }
    }
}

#endif  // LIBS_GRAPH_TEST_FIND_EULERIAN_CYCLE_HPP

