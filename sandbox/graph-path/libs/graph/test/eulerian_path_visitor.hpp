// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_TEST_EULERIAN_PATH_HPP
#define LIBS_GRAPH_TEST_EULERIAN_PATH_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/visitors.hpp>

template <typename PropertyMap>
class eulerian_path_test_visitor
{
    unsigned int& _edge_count;
    PropertyMap& _p_map;

 public:
    typedef boost::on_examine_edge event_filter;

    eulerian_path_test_visitor(unsigned int& count, PropertyMap& p_map)
      : _edge_count(count), _p_map(p_map)
    {
    }

    template <typename Graph>
    inline void
        operator()(
            typename boost::graph_traits<Graph>::edge_descriptor e
          , Graph& graph
        )
    {
        boost::put(_p_map, e, boost::get(_p_map, e) + 1);
        ++_edge_count;
    }
};

#endif  // LIBS_GRAPH_TEST_EULERIAN_PATH_HPP

