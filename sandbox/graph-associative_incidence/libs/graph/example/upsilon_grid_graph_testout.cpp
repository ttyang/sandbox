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
#include <boost/graph/vertex_dimension_trait.hpp>
#include <boost/graph/vertex_coordinate_trait.hpp>
#include <boost/graph/edge_key_trait.hpp>
#include <boost/graph/upsilon_grid_graph.hpp>

typedef boost::upsilon_grid_graph<> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::degree_size_type DegreeIndex;
typedef boost::vertex_dimension_trait<Graph>::type DimensionT;
typedef boost::vertex_coordinate_trait<Graph>::type Coordinate;
typedef boost::edge_key_trait<Graph>::type EdgeKey;

void out_with_it(Graph const& graph)
{
    std::cout << "    // Verify that all vertices are within bounds.";
    std::cout << std::endl << "    BOOST_FOREACH(Vertex v, boost::vertices";
    std::cout << "(graph))" << std::endl << "    {" << std::endl;
    std::cout << "        for (DimensionT d = 0; d < 2; ++d)" << std::endl;
    std::cout << "        {" << std::endl << "            BOOST_CHECK(v[d] < ";
    std::cout << "graph.length(d));" << std::endl << "        }" << std::endl;
    std::cout << "    }" << std::endl << std::endl << "    test_indices_and_";
    std::cout << "incidence(graph);" << std::endl << std::endl << "    // ";
    std::cout << "Verify structure." << std::endl << "    BOOST_CHECK(";
    std::cout << boost::num_vertices(graph) << " == boost::num_vertices";
    std::cout << "(graph));" << std::endl << std::endl;

    boost::property_map<Graph,boost::vertex_index_t>::type
        v_index_map = boost::get(boost::vertex_index, graph);

    BOOST_FOREACH(Vertex v, boost::vertices(graph))
    {
        std::cout << "    test_vertex(" << boost::get(v_index_map, v);
        std::cout << ", graph, " << v[0] << ", " << v[1] << ");" << std::endl;
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

    Coordinate const max_distance = (std::max)(
        graph.length(0)
      , graph.length(1)
    ) << 1;

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

            for (
                DimensionT distance = boost::initialized_value;
                distance < max_distance;
                ++distance
            )
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

    std::cout << '}' << std::endl;
}

void out_3_3_f_f_o()
{
    Vertex dimensions = {{3, 3}};
    Graph g(dimensions, false, true);

    std::cout << std::endl << "void out_3_3_f_f_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 3}};" << std::endl;
    std::cout << "    Graph graph(dimensions, false, true);" << std::endl;
    std::cout << std::endl << "    BOOST_CHECK(" << boost::num_edge_keys(g);
    std::cout << " == boost::num_edge_keys(graph));" << std::endl << std::endl;

    for (
        DegreeIndex i = boost::initialized_value;
        i < boost::num_edge_keys(g);
        ++i
    )
    {
        EdgeKey const k = boost::edge_key(i, g);

        std::cout << "    test_edge_key(" << i << ", graph, " << int(k[0]);
        std::cout << ", " << int(k[1]) << ");" << std::endl;
    }

    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(!graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_3_3_t_f_o()
{
    Vertex dimensions = {{3, 3}};
    std::tr1::array<bool,2> wraparound = {{true, false}};
    Graph graph(dimensions, wraparound, true);

    std::cout << std::endl << "void out_3_3_t_f_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 3}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{true, false}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_3_3_f_t_o()
{
    Vertex dimensions = {{3, 3}};
    std::tr1::array<bool,2> wraparound = {{false, true}};
    Graph graph(dimensions, wraparound, true);

    std::cout << std::endl << "void out_3_3_f_t_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 3}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{false, true}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_3_3_t_t_o()
{
    Vertex dimensions = {{3, 3}};
    Graph g(dimensions, true, true);

    std::cout << std::endl << "void out_3_3_t_t_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 3}};" << std::endl;
    std::cout << "    Graph graph(dimensions, true, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_3_3_f_f_s()
{
    Vertex dimensions = {{3, 3}};
    Graph g(dimensions, false, false);

    std::cout << std::endl << "void out_3_3_f_f_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 3}};" << std::endl;
    std::cout << "    Graph graph(dimensions, false, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(!graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_3_3_t_f_s()
{
    Vertex dimensions = {{3, 3}};
    std::tr1::array<bool,2> wraparound = {{true, false}};
    Graph graph(dimensions, wraparound, false);

    std::cout << std::endl << "void out_3_3_t_f_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 3}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{true, false}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_3_3_f_t_s()
{
    Vertex dimensions = {{3, 3}};
    std::tr1::array<bool,2> wraparound = {{false, true}};
    Graph graph(dimensions, wraparound, false);

    std::cout << std::endl << "void out_3_3_f_t_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 3}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{false, true}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_3_3_t_t_s()
{
    Vertex dimensions = {{3, 3}};
    Graph g(dimensions, true, false);

    std::cout << std::endl << "void out_3_3_t_t_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 3}};" << std::endl;
    std::cout << "    Graph graph(dimensions, true, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_3_4_f_f_o()
{
    Vertex dimensions = {{3, 4}};
    Graph g(dimensions, false, true);

    std::cout << std::endl << "void out_3_4_f_f_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 4}};" << std::endl;
    std::cout << "    Graph graph(dimensions, false, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(!graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_3_4_t_f_o()
{
    Vertex dimensions = {{3, 4}};
    std::tr1::array<bool,2> wraparound = {{true, false}};
    Graph graph(dimensions, wraparound, true);

    std::cout << std::endl << "void out_3_4_t_f_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 4}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{true, false}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_3_4_f_t_o()
{
    Vertex dimensions = {{3, 4}};
    std::tr1::array<bool,2> wraparound = {{false, true}};
    Graph graph(dimensions, wraparound, true);

    std::cout << std::endl << "void out_3_4_f_t_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 4}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{false, true}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_3_4_t_t_o()
{
    Vertex dimensions = {{3, 4}};
    Graph g(dimensions, true, true);

    std::cout << std::endl << "void out_3_4_t_t_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 4}};" << std::endl;
    std::cout << "    Graph graph(dimensions, true, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_3_4_f_f_s()
{
    Vertex dimensions = {{3, 4}};
    Graph g(dimensions, false, false);

    std::cout << std::endl << "void out_3_4_f_f_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 4}};" << std::endl;
    std::cout << "    Graph graph(dimensions, false, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(!graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_3_4_t_f_s()
{
    Vertex dimensions = {{3, 4}};
    std::tr1::array<bool,2> wraparound = {{true, false}};
    Graph graph(dimensions, wraparound, false);

    std::cout << std::endl << "void out_3_4_t_f_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 4}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{true, false}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_3_4_f_t_s()
{
    Vertex dimensions = {{3, 4}};
    std::tr1::array<bool,2> wraparound = {{false, true}};
    Graph graph(dimensions, wraparound, false);

    std::cout << std::endl << "void out_3_4_f_t_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 4}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{false, true}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_3_4_t_t_s()
{
    Vertex dimensions = {{3, 4}};
    Graph g(dimensions, true, false);

    std::cout << std::endl << "void out_3_4_t_t_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{3, 4}};" << std::endl;
    std::cout << "    Graph graph(dimensions, true, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_4_3_f_f_o()
{
    Vertex dimensions = {{4, 3}};
    Graph g(dimensions, false, true);

    std::cout << std::endl << "void out_4_3_f_f_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 3}};" << std::endl;
    std::cout << "    Graph graph(dimensions, false, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(!graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_4_3_t_f_o()
{
    Vertex dimensions = {{4, 3}};
    std::tr1::array<bool,2> wraparound = {{true, false}};
    Graph graph(dimensions, wraparound, true);

    std::cout << std::endl << "void out_4_3_t_f_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 3}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{true, false}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_4_3_f_t_o()
{
    Vertex dimensions = {{4, 3}};
    std::tr1::array<bool,2> wraparound = {{false, true}};
    Graph graph(dimensions, wraparound, true);

    std::cout << std::endl << "void out_4_3_f_t_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 3}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{false, true}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_4_3_t_t_o()
{
    Vertex dimensions = {{4, 3}};
    Graph g(dimensions, true, true);

    std::cout << std::endl << "void out_4_3_t_t_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 3}};" << std::endl;
    std::cout << "    Graph graph(dimensions, true, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_4_3_f_f_s()
{
    Vertex dimensions = {{4, 3}};
    Graph g(dimensions, false, false);

    std::cout << std::endl << "void out_4_3_f_f_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 3}};" << std::endl;
    std::cout << "    Graph graph(dimensions, false, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(!graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_4_3_t_f_s()
{
    Vertex dimensions = {{4, 3}};
    std::tr1::array<bool,2> wraparound = {{true, false}};
    Graph graph(dimensions, wraparound, false);

    std::cout << std::endl << "void out_4_3_t_f_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 3}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{true, false}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_4_3_f_t_s()
{
    Vertex dimensions = {{4, 3}};
    std::tr1::array<bool,2> wraparound = {{false, true}};
    Graph graph(dimensions, wraparound, false);

    std::cout << std::endl << "void out_4_3_f_t_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 3}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{false, true}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_4_3_t_t_s()
{
    Vertex dimensions = {{4, 3}};
    Graph g(dimensions, true, false);

    std::cout << std::endl << "void out_4_3_t_t_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 3}};" << std::endl;
    std::cout << "    Graph graph(dimensions, true, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_4_4_f_f_o()
{
    Vertex dimensions = {{4, 4}};
    Graph g(dimensions, false, true);

    std::cout << std::endl << "void out_4_4_f_f_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 4}};" << std::endl;
    std::cout << "    Graph graph(dimensions, false, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(!graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_4_4_t_f_o()
{
    Vertex dimensions = {{4, 4}};
    std::tr1::array<bool,2> wraparound = {{true, false}};
    Graph graph(dimensions, wraparound, true);

    std::cout << std::endl << "void out_4_4_t_f_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 4}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{true, false}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_4_4_f_t_o()
{
    Vertex dimensions = {{4, 4}};
    std::tr1::array<bool,2> wraparound = {{false, true}};
    Graph graph(dimensions, wraparound, true);

    std::cout << std::endl << "void out_4_4_f_t_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 4}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{false, true}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_4_4_t_t_o()
{
    Vertex dimensions = {{4, 4}};
    Graph g(dimensions, true, true);

    std::cout << std::endl << "void out_4_4_t_t_o()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 4}};" << std::endl;
    std::cout << "    Graph graph(dimensions, true, true);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_4_4_f_f_s()
{
    Vertex dimensions = {{4, 4}};
    Graph g(dimensions, false, false);

    std::cout << std::endl << "void out_4_4_f_f_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 4}};" << std::endl;
    std::cout << "    Graph graph(dimensions, false, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(!graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

void out_4_4_t_f_s()
{
    Vertex dimensions = {{4, 4}};
    std::tr1::array<bool,2> wraparound = {{true, false}};
    Graph graph(dimensions, wraparound, false);

    std::cout << std::endl << "void out_4_4_t_f_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 4}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{true, false}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_4_4_f_t_s()
{
    Vertex dimensions = {{4, 4}};
    std::tr1::array<bool,2> wraparound = {{false, true}};
    Graph graph(dimensions, wraparound, false);

    std::cout << std::endl << "void out_4_4_f_t_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 4}};";
    std::cout << std::endl << "    std::tr1::array<bool,2> wraparound = ";
    std::cout << "{{false, true}};" << std::endl << "    Graph graph";
    std::cout << "(dimensions, wraparound, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_4_4_t_t_s()
{
    Vertex dimensions = {{4, 4}};
    Graph g(dimensions, true, false);

    std::cout << std::endl << "void out_4_4_t_t_s()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{4, 4}};" << std::endl;
    std::cout << "    Graph graph(dimensions, true, false);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 2; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(di";
    std::cout << "mensions[d] == graph.length(d));" << std::endl << "        ";
    std::cout << "BOOST_CHECK(graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(g);
}

int main(int argc, char** argv)
{
    std::cout << "// Copyright (C) 2012 Cromwell D. Enage" << std::endl;
    std::cout << "// Distributed under the Boost Software License, ";
    std::cout << "Version 1.0." << std::endl << "// (See accompanying ";
    std::cout << "file LICENSE_1_0.txt or copy at" << std::endl;
    std::cout << "// http://www.boost.org/LICENSE_1_0.txt)" << std::endl;
    std::cout << std::endl << "#include <boost/foreach.hpp>" << std::endl;
    std::cout << "#include <boost/utility/value_init.hpp>" << std::endl;
    std::cout << "#include <boost/tr1/array.hpp>" << std::endl << "#include ";
    std::cout << "<boost/graph/graph_traits.hpp>" << std::endl << "#include ";
    std::cout << "<boost/graph/vertex_dimension_trait.hpp>" << std::endl;
    std::cout << "#include <boost/graph/edge_key_trait.hpp>" << std::endl;
    std::cout << "#include <boost/graph/upsilon_grid_graph.hpp>" << std::endl;
    std::cout << "#include <boost/test/minimal.hpp>" << std::endl;
    std::cout << "#include \"assoc_incidence_graph.hpp\"" << std::endl;
    std::cout << std::endl << "typedef boost::upsilon_grid_graph<> Graph;";
    std::cout << std::endl << "typedef boost::graph_traits<Graph>::vertex_des";
    std::cout << "criptor Vertex;" << std::endl << "typedef boost::graph_";
    std::cout << "traits<Graph>::vertices_size_type VertexIndex;" << std::endl;
    std::cout << "typedef boost::graph_traits<Graph>::edge_descriptor Edge;";
    std::cout << std::endl << "typedef boost::graph_traits<Graph>::edges_size";
    std::cout << "_type EdgeIndex;" << std::endl << "typedef boost::graph_tra";
    std::cout << "its<Graph>::degree_size_type DegreeIndex;" << std::endl;
    std::cout << "typedef boost::vertex_dimension_trait<Graph>::type";
    std::cout << " DimensionT;" << std::endl << "typedef boost::edge_key";
    std::cout << "_trait<Graph>::type EdgeKey;" << std::endl;
    out_3_3_f_f_o();
    out_3_3_t_f_o();
    out_3_3_f_t_o();
    out_3_3_t_t_o();
    out_3_3_f_f_s();
    out_3_3_t_f_s();
    out_3_3_f_t_s();
    out_3_3_t_t_s();
    out_3_4_f_f_o();
    out_3_4_t_f_o();
    out_3_4_f_t_o();
    out_3_4_t_t_o();
    out_3_4_f_f_s();
    out_3_4_t_f_s();
    out_3_4_f_t_s();
    out_3_4_t_t_s();
    out_4_3_f_f_o();
    out_4_3_t_f_o();
    out_4_3_f_t_o();
    out_4_3_t_t_o();
    out_4_3_f_f_s();
    out_4_3_t_f_s();
    out_4_3_f_t_s();
    out_4_3_t_t_s();
    out_4_4_f_f_o();
    out_4_4_t_f_o();
    out_4_4_f_t_o();
    out_4_4_t_t_o();
    out_4_4_f_f_s();
    out_4_4_t_f_s();
    out_4_4_f_t_s();
    out_4_4_t_t_s();
    std::cout << std::endl << "int test_main(int argc, char** argv)";
    std::cout << std::endl << '{' << std::endl;

    for (unsigned int i = 3; i < 5; ++i)
    {
        for (unsigned int j = 3; j < 5; ++j)
        {
            std::cout << "    out_" << i << '_' << j << "_f_f_o();";
            std::cout << std::endl << "    out_" << i << '_' << j;
            std::cout << "_t_f_o();" << std::endl << "    out_" << i << '_';
            std::cout << j << "_f_t_o();" << std::endl << "    out_" << i;
            std::cout << '_' << j << "_t_t_o();" << std::endl << "    out_";
            std::cout << i << '_' << j << "_f_f_s();" << std::endl;
            std::cout << "    out_" << i << '_' << j << "_t_f_s();";
            std::cout << std::endl << "    out_" << i << '_' << j;
            std::cout << "_f_t_s();" << std::endl << "    out_" << i << '_';
            std::cout << j << "_t_t_s();" << std::endl;
        }
    }

    std::cout << "    return 0;" << std::endl << '}' << std::endl << std::endl;

    return 0;
}

