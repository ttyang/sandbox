// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <map>
#include <bitset>
#include <boost/mpl/int.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/basic_vert_insert_iterator.hpp>
#include <boost/graph/basic_add_edge_function.hpp>
#include <boost/graph/set_bitset_grid_layout.hpp>

//[example__bitset_grid_layouts__static
int main()
{
    typedef boost::adjacency_list<boost::vecS,boost::setS,boost::directedS>
            MidGraph;
    typedef std::map<
                boost::graph_traits<MidGraph>::vertex_descriptor
              , std::bitset<4>
            >
            Vertex2BitsMap;

    Vertex2BitsMap v2b_map;
    boost::associative_property_map<Vertex2BitsMap> pos_map(v2b_map);
    MidGraph mid_graph(boost::count_bitset_grid_layout_vertices(pos_map));

    boost::set_bitset_grid_layout(
        boost::vertices(mid_graph).first
      , boost::basic_2way_edge_adder(mid_graph)
      , boost::position_map(pos_map)
    );
    boost::print_graph(mid_graph, pos_map);
    std::cout << std::endl;
    //]

    //[example__bitset_grid_layouts__dynamic
    typedef boost::vertex_distance_t PositionTag;

    boost::mpl::int_<5> bit_count;
    boost::adjacency_list<
        boost::multisetS
      , boost::listS
      , boost::undirectedS
      , boost::property<PositionTag,boost::dynamic_bitset<> >
    > big_graph(
        boost::count_bitset_grid_layout_vertices(bit_count)
    );

    boost::set_bitset_grid_layout(
        boost::vertices(big_graph).first
      , boost::basic_edge_adder(big_graph)
      , boost::get(PositionTag(), big_graph)
      , bit_count
    );
    boost::print_graph(big_graph, boost::get(PositionTag(), big_graph));

    return 0;
}
//]

