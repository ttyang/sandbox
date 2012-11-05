// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/foreach.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/tr1/array.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/vertex_coordinate_trait.hpp>
#include <boost/graph/edge_key_trait.hpp>
#include <boost/graph/zeta_grid_graph.hpp>

int main(int argc, char** argv)
{
    std::cout << "// Copyright (C) 2012 Cromwell D. Enage" << std::endl;
    std::cout << "// Distributed under the Boost Software License, ";
    std::cout << "Version 1.0." << std::endl << "// (See accompanying ";
    std::cout << "file LICENSE_1_0.txt or copy at" << std::endl;
    std::cout << "// http://www.boost.org/LICENSE_1_0.txt)" << std::endl;
    std::cout << std::endl << "#include <boost/foreach.hpp>" << std::endl;
    std::cout << "#include <boost/utility/value_init.hpp>" << std::endl;
    std::cout << "#include <boost/tr1/array.hpp>" << std::endl;
    std::cout << "#include <boost/graph/graph_traits.hpp>" << std::endl;
    std::cout << "#include <boost/graph/vertex_dimension_trait.hpp>";
    std::cout << std::endl << "#include <boost/graph/edge_key_trait.hpp>";
    std::cout << std::endl << "#include <boost/graph/zeta_grid_graph.hpp>";
    std::cout << std::endl << "#include <boost/test/minimal.hpp>" << std::endl;
    std::cout << "#include \"assoc_incidence_graph.hpp\"" << std::endl;
    std::cout << std::endl << "int test_main(int argc, char** argv)";
    std::cout << std::endl << '{' << std::endl << "    typedef boost::zeta_";
    std::cout << "grid_graph<4> Graph;" << std::endl << "    typedef boost::";
    std::cout << "graph_traits<Graph>::vertex_descriptor Vertex;";
    std::cout << std::endl << "    typedef boost::graph_traits<Graph>::";
    std::cout << "vertices_size_type VertexIndex;" << std::endl;
    std::cout << "    typedef boost::graph_traits<Graph>::edge_descriptor ";
    std::cout << "Edge;" << std::endl << "    typedef boost::graph_traits";
    std::cout << "<Graph>::edges_size_type EdgeIndex;" << std::endl << "    ";
    std::cout << "typedef boost::graph_traits<Graph>::degree_size_type ";
    std::cout << "DegreeIndex;" << std::endl << "    typedef boost::vertex_";
    std::cout << "dimension_trait<Graph>::type DimensionT;" << std::endl;
    std::cout << "    typedef boost::edge_key_trait<Graph>::type EdgeKey;";
    std::cout << std::endl << std::endl << "    Vertex dimensions = ";
    std::cout << "{{3, 3, 3, 3}};" << std::endl << "    std::tr1::array<bool,";
    std::cout << "4> wraparound = {{false, false, true, true}};" << std::endl;
    std::cout << "    Graph graph(dimensions, wraparound);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (" << std::endl << "        DimensionT";
    std::cout << " d = boost::initialized_value;" << std::endl << "        d ";
    std::cout << "< graph.dimensions();" << std::endl << "        ++d";
    std::cout << std::endl << "    )" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_CHECK(dimensions[d] == graph.length(d));";
    std::cout << std::endl << "        BOOST_CHECK(wraparound[d] == graph.wra";
    std::cout << "pped(d));" << std::endl << "    }" << std::endl << std::endl;
    std::cout << "    // Verify that all vertices are within bounds.";
    std::cout << std::endl << "    BOOST_FOREACH(Vertex v, boost::vertices";
    std::cout << "(graph))" << std::endl << "    {" << std::endl << "        ";
    std::cout << "for (" << std::endl << "            DimensionT d = ";
    std::cout << "boost::initialized_value;" << std::endl << "            d <";
    std::cout << " graph.dimensions();" << std::endl << "            ++d";
    std::cout << std::endl << "        )" << std::endl << "        {";
    std::cout << std::endl << "            BOOST_CHECK(v[d] < graph.length";
    std::cout << "(d));" << std::endl << "        }" << std::endl << "    }";
    std::cout << std::endl << std::endl << "    test_indices_and_incidence(gr";
    std::cout << "aph);" << std::endl << std::endl << "    // Verify structur";
    std::cout << "e." << std::endl << "    BOOST_CHECK(81 == boost::num_verti";
    std::cout << "ces(graph));" << std::endl << "    BOOST_CHECK(80 == boost";
    std::cout << "::num_edge_keys(graph));" << std::endl << std::endl;

    typedef boost::zeta_grid_graph<4> Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<Graph>::degree_size_type DegreeIndex;
    typedef boost::vertex_coordinate_trait<Graph>::type Coordinate;
    typedef boost::edge_key_trait<Graph>::type EdgeKey;

    Vertex dimensions = {{3, 3, 3, 3}};
    std::tr1::array<bool,4> wraparound = {{false, false, true, true}};
    Graph graph(dimensions, wraparound);
    boost::property_map<Graph,boost::vertex_index_t>::type
        v_index_map = boost::get(boost::vertex_index, graph);

    BOOST_FOREACH(Vertex v, boost::vertices(graph))
    {
        std::cout << "    test_vertex(" << boost::get(v_index_map, v);
        std::cout << ", graph, " << v[0] << ", " << v[1] << ", " << v[2];
        std::cout << ", " << v[3] << ");" << std::endl;
    }

    std::cout << std::endl;

    for (
        DegreeIndex i = boost::initialized_value;
        i < boost::num_edge_keys(graph);
        ++i
    )
    {
        EdgeKey const k = boost::edge_key(i, graph);

        std::cout << "    test_edge_key(" << i << ", graph, " << int(k[0]);
        std::cout << ", " << int(k[1]) << ", " << int(k[2]) << ", ";
        std::cout << int(k[3]) << ");" << std::endl;
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

            for (Coordinate distance = 0; distance < 6; ++distance)
            {
                std::cout << "    test_next_previous(" << i << ", " << k_i;
                std::cout << ", " << distance << ", graph, " << boost::get(
                    v_index_map
                  , graph.next(v, key, distance)
                ) << ", " << boost::get(
                    v_index_map
                  , graph.previous(v, key, distance)
                ) << ");" << std::endl;
            }
        }
    }

    std::cout << std::endl << "    return 0;" << std::endl << '}' << std::endl;
    std::cout << std::endl;

    return 0;
}

