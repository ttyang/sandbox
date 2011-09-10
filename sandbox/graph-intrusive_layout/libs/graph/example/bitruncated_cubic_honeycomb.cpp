// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_PARAMETER_MAX_ARITY 9

#include <iostream>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/array.hpp>
#include <boost/phoenix/core/value.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/basic_vert_insert_iterator.hpp>
#include <boost/graph/basic_add_edge_function.hpp>
#include <boost/graph/set_bt_cubic_hcomb_layout.hpp>

//[example__bitruncated_cubic_honeycomb
int main()
{
    typedef boost::numeric::ublas::vector<double> Point;
    typedef boost::vertex_distance_t PositionTag;

    Point dimensions(3);

    dimensions(0) = dimensions(1) = 7.0;
    dimensions(2) = 8.0;

    boost::adjacency_list<
        boost::multisetS
      , boost::listS
      , boost::undirectedS
      , boost::property<PositionTag,Point>
    > graph(
        boost::count_bitruncated_cubic_honeycomb_layout_vertices(dimensions)
    );
    boost::array<bool,3> wraparound_policy = {{false, true, true}};

#ifdef BOOST_GRAPH_SET_BITRUNCATED_CUBIC_HONEYCOMB_TAKES_ALL_PARAMS
    boost::set_bitruncated_cubic_honeycomb_layout(
        boost::vertices(graph).first
      , boost::basic_2way_edge_adder(graph)
      , dimensions
      , boost::graph::keywords::_wraparound_policy = wraparound_policy
      , boost::graph::keywords::_point_factory = boost::phoenix::val(Point(3))
      , boost::graph::keywords::_position_map = boost::get(
            PositionTag()
          , graph
        )
    );
#else  // !BOOST_GRAPH_SET_BITRUNCATED_CUBIC_HONEYCOMB_TAKES_ALL_PARAMS
    boost::set_bitruncated_cubic_honeycomb_layout(
        boost::vertices(graph).first
      , boost::basic_2way_edge_adder(graph)
      , boost::dimensions(
            dimensions
        ).wraparound_policy(
            wraparound_policy
        ).point_factory(
            boost::phoenix::val(Point(3))
        ).position_map(
            boost::get(PositionTag(), graph)
        )
    );
#endif  // BOOST_GRAPH_SET_BITRUNCATED_CUBIC_HONEYCOMB_TAKES_ALL_PARAMS
    boost::print_graph(graph, boost::get(PositionTag(), graph));

    return 0;
}
//]

