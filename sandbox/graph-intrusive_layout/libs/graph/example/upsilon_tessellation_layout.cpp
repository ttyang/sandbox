// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_PARAMETER_MAX_ARITY 10

#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/tr1/tuple.hpp>
#include <boost/array.hpp>
#include <boost/phoenix/core/value.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/basic_add_edge_function.hpp>
#include <boost/graph/set_upsilon_tessel_layout.hpp>

//[example__upsilon_tessellation_layout
int main()
{
    typedef boost::numeric::ublas::vector<double> Point;
    typedef boost::vertex_distance_t PositionTag;
    typedef boost::adjacency_list<
                boost::multisetS
              , boost::listS
              , boost::undirectedS
              , boost::property<PositionTag,Point>
            >
            Graph;

    Point dimensions(2);

    dimensions(0) = 5.0;
    dimensions(1) = 4.0;

    Graph g(boost::count_upsilon_tessellation_layout_vertices(dimensions));
    boost::array<bool,2> wraparound_policy = {{true, false}};

    boost::set_upsilon_tessellation_layout(
        boost::vertices(g).first
      , boost::basic_2way_edge_adder(g)
      , boost::dimensions(
            dimensions
        ).has_square_origin(
            true
        ).wraparound_policy(
            wraparound_policy
        ).point_factory(
            boost::phoenix::val(Point(2))
        ).position_map(
            boost::get(PositionTag(), g)
        )
    );
    boost::print_graph(g, boost::get(PositionTag(), g));
    std::cout << std::endl;

    boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

    for (std::tr1::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
    {
        boost::clear_vertex(*vi, g);
    }

    wraparound_policy[1] = true;
    boost::set_upsilon_tessellation_layout(
        boost::vertices(g).first
      , boost::basic_2way_edge_adder(g)
      , dimensions
      , boost::graph::keywords::_wraparound_policy = wraparound_policy
      , boost::graph::keywords::_point_factory = boost::phoenix::val(Point(2))
      , boost::graph::keywords::_position_map = boost::get(PositionTag(), g)
    );
    boost::print_graph(g, boost::get(PositionTag(), g));

    return 0;
}
//]

