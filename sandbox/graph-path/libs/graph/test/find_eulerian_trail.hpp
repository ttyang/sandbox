// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_TEST_FIND_EULERIAN_TRAIL_HPP
#define LIBS_GRAPH_TEST_FIND_EULERIAN_TRAIL_HPP

#include <iterator>
#include <list>
#include <boost/tr1/tuple.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/find_eulerian_trail.hpp>
#include "eulerian_path_visitor.hpp"

template <typename Graph>
void find_eulerian_trail_test(Graph& g)
{
    typedef std::list<typename boost::graph_traits<Graph>::edge_descriptor>
            EdgeList;
    typedef typename boost::property_map<Graph,boost::edge_weight_t>::type
            EdgeMap;

    EdgeList path;
    unsigned int edge_count = 0;
    typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
    typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;
    EdgeMap edge_map = boost::get(boost::edge_weight, g);

    for (std::tr1::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
    {
        for (
            std::tr1::tie(ei, ei_end) = boost::out_edges(*vi, g);
            ei != ei_end;
            ++ei
        )
        {
            boost::put(edge_map, *ei, 0);
        }
    }

    boost::find_eulerian_trail(
        g
      , std::back_inserter(path)
      , eulerian_path_test_visitor<EdgeMap>(edge_count, edge_map)
    );

    BOOST_CHECK(path.size() == edge_count);
    BOOST_CHECK(edge_count == boost::num_edges(g));

    typename EdgeList::const_iterator p_itr = path.begin(), p_end = path.end();

    for (
        typename EdgeList::const_iterator c_itr = path.begin();
        ++c_itr != p_end;
        ++p_itr
    )
    {
        BOOST_CHECK(boost::target(*p_itr, g) == boost::source(*c_itr, g));
    }

    for (std::tr1::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
    {
        for (
            std::tr1::tie(ei, ei_end) = boost::out_edges(*vi, g);
            ei != ei_end;
            ++ei
        )
        {
            BOOST_CHECK(1 == boost::get(edge_map, *ei));
        }
    }
}

#endif  // LIBS_GRAPH_TEST_FIND_EULERIAN_TRAIL_HPP

