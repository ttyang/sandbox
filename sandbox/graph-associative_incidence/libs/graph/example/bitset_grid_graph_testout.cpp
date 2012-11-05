// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <iomanip>
#include <boost/foreach.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/edge_key_trait.hpp>
#include <boost/graph/bitset_grid_graph.hpp>

int main(int argc, char** argv)
{
    std::cout << "// Copyright (C) 2012 Cromwell D. Enage" << std::endl;
    std::cout << "// Distributed under the Boost Software License, ";
    std::cout << "Version 1.0." << std::endl << "// (See accompanying ";
    std::cout << "file LICENSE_1_0.txt or copy at" << std::endl;
    std::cout << "// http://www.boost.org/LICENSE_1_0.txt)" << std::endl;
    std::cout << std::endl << "#include <boost/mpl/size_t.hpp>" << std::endl;
    std::cout << "#include <boost/graph/bitset_grid_graph.hpp>" << std::endl;
    std::cout << "#include <boost/test/minimal.hpp>" << std::endl;
    std::cout << "#include \"assoc_incidence_graph.hpp\"" << std::endl;
    std::cout << std::endl << "int test_main(int argc, char** argv)";
    std::cout << std::endl << '{' << std::endl << "    boost::bitset_grid_gra";
    std::cout << "ph<boost::mpl::size_t<4> > graph;" << std::endl << std::endl;
    std::cout << "    test_indices_and_incidence(graph);" << std::endl;
    std::cout << "    test_edge_list(graph);" << std::endl << std::endl;
    std::cout << "    // Verify structure." << std::endl << "    BOOST_CHECK";
    std::cout << "(16 == boost::num_vertices(graph));" << std::endl << "    ";
    std::cout << "BOOST_CHECK(4 == boost::num_edge_keys(graph));" << std::endl;
    std::cout << "    BOOST_CHECK(64 == boost::num_edges(graph));";
    std::cout << std::endl << std::endl << std::boolalpha;

    typedef boost::mpl::size_t<4> BitCount;
    typedef boost::bitset_grid_graph<BitCount> Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<Graph>::degree_size_type DegreeIndex;
    typedef boost::edge_key_trait<Graph>::type EdgeKey;

    Graph graph;
    boost::property_map<Graph,boost::vertex_index_t>::type
        v_index_map = boost::get(boost::vertex_index, graph);

    BOOST_FOREACH(Vertex v, boost::vertices(graph))
    {
        std::cout << "    test_vertex(" << boost::get(v_index_map, v);
        std::cout << ", graph, " << v[0] << ", " << v[1] << ", " << v[2];
        std::cout << ", " << v[3] << ");" << std::endl;
    }

    std::cout << std::endl;

    for (std::size_t i = 0; i + 1 < boost::num_vertices(graph); ++i)
    {
        for (std::size_t j = i + 1; j < boost::num_vertices(graph); ++j)
        {
            std::cout << "    test_edge(" << i << ", " << j << ", graph, " << (
                boost::edge(
                    boost::vertex(i, graph)
                  , boost::vertex(j, graph)
                  , graph
                ).second ? "true" : "false"
            ) << ");" << std::endl;
        }
    }

    std::cout << std::endl;

    for (std::size_t i = 0; i < boost::num_vertices(graph); ++i)
    {
        Vertex const v = boost::vertex(i, graph);

        for (
            DegreeIndex k_i = boost::initialized_value;
            k_i < boost::num_edge_keys(graph);
            ++k_i
        )
        {
            EdgeKey const key = boost::edge_key(k_i, graph);

            std::cout << "    test_next_previous(" << i << ", " << k_i;
            std::cout << ", graph, " << boost::get(
                v_index_map
              , graph.next(v, key)
            ) << ", " << boost::get(v_index_map, graph.previous(v, key));
            std::cout << ");" << std::endl;
        }
    }

    std::cout << std::endl << "    return 0;" << std::endl << '}' << std::endl;
    std::cout << std::endl;

    return 0;
}

