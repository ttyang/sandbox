// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_PARAMETER_MAX_ARITY 11

#include <iostream>
#include <boost/mpl/int.hpp>
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
#include <boost/graph/set_orthogonal_grid_layout.hpp>

//[example__orthogonal_grid_layouts
int main()
{
    typedef boost::numeric::ublas::vector<double> Point;
    typedef boost::vertex_distance_t PositionTag;

    Point origin(3), scale(3), dimensions(3);

    scale(0) = 2.0;
    scale(1) = scale(2) = 1.0;
    dimensions(0) = dimensions(1) = 6.0;
    dimensions(2) = 3.0;

    boost::adjacency_list<
        boost::multisetS
      , boost::listS
      , boost::undirectedS
      , boost::property<PositionTag,Point>
    > graph(
        boost::count_orthogonal_grid_layout_vertices(
            dimensions
          , boost::mpl::int_<3>()
          , boost::graph::keywords::_scale = scale
        )
    );
    boost::array<bool,3> wraparound_policy = {{true, false, true}};

    origin(0) = -2.0;
    origin(1) = -2.5;
    origin(2) = -1.0;
    boost::set_orthogonal_grid_layout(
        boost::vertices(graph).first
      , boost::basic_2way_edge_adder(graph)
      , boost::position_map(
            boost::get(PositionTag(), graph)
        ).is_zeta(
            true
        ).dimension_count(
            boost::mpl::int_<3>()
        ).dimensions(
            dimensions
        ).scale(
            scale
        ).origin(
            origin
        ).point_factory(
            boost::phoenix::val(Point(3))
        ).wraparound_policy(
            wraparound_policy
        )
    );
    boost::print_graph(graph, boost::get(PositionTag(), graph));
    std::cout << std::endl;
    graph.clear();
    boost::set_orthogonal_grid_layout(
        boost::basic_vertex_inserter(graph)
      , boost::basic_2way_edge_adder(graph)
      , dimensions
      , boost::graph::keywords::_scale = scale
      , boost::graph::keywords::_origin = origin
      , boost::graph::keywords::_position_map = boost::get(
            PositionTag()
          , graph
        )
      , boost::graph::keywords::_point_factory = boost::phoenix::val(Point(2))
      , boost::graph::keywords::_wraparound_policy = wraparound_policy
    );
    boost::print_graph(graph, boost::get(PositionTag(), graph));

    return 0;
}
//]

