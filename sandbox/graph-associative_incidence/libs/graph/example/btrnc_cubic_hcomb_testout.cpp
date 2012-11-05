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
#include <boost/graph/btrnc_cubic_hcomb_graph.hpp>

typedef boost::bitruncated_cubic_honeycomb_graph<> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::degree_size_type DegreeIndex;
typedef boost::vertex_dimension_trait<Graph>::type DimensionT;
typedef boost::vertex_coordinate_trait<Graph>::type Coordinate;
typedef boost::edge_key_trait<Graph>::type EdgeKey;

void out_with_it(Graph const& graph)
{
    std::cout << "    // Verify that all vertices are within bounds.";
    std::cout << std::endl << "    BOOST_FOREACH(Vertex v, boost::vertices";
    std::cout << "(graph))" << std::endl << "    {" << std::endl << "        ";
    std::cout << "for (DimensionT d = 0; d < 3; ++d)" << std::endl << "      ";
    std::cout << "  {" << std::endl << "            BOOST_CHECK(v[d] < graph";
    std::cout << ".length(d));" << std::endl << "        }" << std::endl;
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
        std::cout << ", graph, " << v[0] << ", " << v[1] << ", " << v[2];
        std::cout << ");" << std::endl;
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
        (std::max)(graph.length(0), graph.length(1))
      , graph.length(2)
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

void out_2_2_2_f_f_f()
{
    Vertex dimensions = {{2, 2, 2}};
    std::tr1::array<bool,3> wraparound = {{false, false, false}};
    Graph graph(dimensions, wraparound);

    std::cout << std::endl << "void out_2_2_2_f_f_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{2, 2, 2}};";
    std::cout << std::endl << "    Graph graph(dimensions, false);";
    std::cout << std::endl << std::endl << "    BOOST_CHECK(";
    std::cout << boost::num_edge_keys(graph);
    std::cout << " == boost::num_edge_keys(graph));" << std::endl << std::endl;

    for (
        DegreeIndex i = boost::initialized_value;
        i < boost::num_edge_keys(graph);
        ++i
    )
    {
        EdgeKey const k = boost::edge_key(i, graph);

        std::cout << "    test_edge_key(" << i << ", graph, ";
        std::cout << int(k[0]) << ", " << int(k[1]) << ", ";
        std::cout << int(k[2]) << ");" << std::endl;
    }

    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 3; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(";
    std::cout << "dimensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(!graph.wrapped(d));" << std::endl;
    std::cout << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_5_5_5_f_f_f()
{
    Vertex dimensions = {{5, 5, 5}};
    Graph graph(dimensions, false);

    std::cout << std::endl << "void out_5_5_5_f_f_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{5, 5, 5}};";
    std::cout << std::endl << "    Graph graph(dimensions, false);";
    std::cout << std::endl << std::endl << "    // Verify dimension lengths ";
    std::cout << "and wrapping." << std::endl << "    for (DimensionT d = 0;";
    std::cout << " d < 3; ++d)" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_CHECK(dimensions[d] == graph.length(d));";
    std::cout << std::endl << "        BOOST_CHECK(!graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_5_5_5_t_f_f()
{
    Vertex dimensions = {{5, 5, 5}};
    std::tr1::array<bool,3> wraparound = {{true, false, false}};
    Graph graph(dimensions, wraparound);

    std::cout << std::endl << "void out_5_5_5_t_f_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{5, 5, 5}};";
    std::cout << std::endl << "    std::tr1::array<bool,3> wraparound = ";
    std::cout << "{{true, false, false}};" << std::endl;
    std::cout << "    Graph graph(dimensions, wraparound);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 3; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(";
    std::cout << "dimensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_5_5_5_t_t_f()
{
    Vertex dimensions = {{5, 5, 5}};
    std::tr1::array<bool,3> wraparound = {{true, true, false}};
    Graph graph(dimensions, wraparound);

    std::cout << std::endl << "void out_5_5_5_t_t_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{5, 5, 5}};";
    std::cout << std::endl << "    std::tr1::array<bool,3> wraparound = ";
    std::cout << "{{true, true, false}};" << std::endl;
    std::cout << "    Graph graph(dimensions, wraparound);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 3; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(";
    std::cout << "dimensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_5_5_5_t_t_t()
{
    Vertex dimensions = {{5, 5, 5}};
    Graph graph(dimensions, true);

    std::cout << std::endl << "void out_5_5_5_t_t_t()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{5, 5, 5}};";
    std::cout << std::endl << "    Graph graph(dimensions, true);";
    std::cout << std::endl << std::endl << "    // Verify dimension lengths ";
    std::cout << "and wrapping." << std::endl << "    for (DimensionT d = 0;";
    std::cout << " d < 3; ++d)" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_CHECK(dimensions[d] == graph.length(d));";
    std::cout << std::endl << "        BOOST_CHECK(graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_5_5_f_f_f()
{
    Vertex dimensions = {{6, 5, 5}};
    Graph graph(dimensions, false);

    std::cout << std::endl << "void out_6_5_5_f_f_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 5, 5}};";
    std::cout << std::endl << "    Graph graph(dimensions, false);";
    std::cout << std::endl << std::endl << "    // Verify dimension lengths ";
    std::cout << "and wrapping." << std::endl << "    for (DimensionT d = 0;";
    std::cout << " d < 3; ++d)" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_CHECK(dimensions[d] == graph.length(d));";
    std::cout << std::endl << "        BOOST_CHECK(!graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_5_5_t_f_f()
{
    Vertex dimensions = {{6, 5, 5}};
    std::tr1::array<bool,3> wraparound = {{true, false, false}};
    Graph graph(dimensions, wraparound);

    std::cout << std::endl << "void out_6_5_5_t_f_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 5, 5}};";
    std::cout << std::endl << "    std::tr1::array<bool,3> wraparound = ";
    std::cout << "{{true, false, false}};" << std::endl;
    std::cout << "    Graph graph(dimensions, wraparound);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 3; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(";
    std::cout << "dimensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_5_5_t_t_f()
{
    Vertex dimensions = {{6, 5, 5}};
    std::tr1::array<bool,3> wraparound = {{true, true, false}};
    Graph graph(dimensions, wraparound);

    std::cout << std::endl << "void out_6_5_5_t_t_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 5, 5}};";
    std::cout << std::endl << "    std::tr1::array<bool,3> wraparound = ";
    std::cout << "{{true, true, false}};" << std::endl;
    std::cout << "    Graph graph(dimensions, wraparound);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 3; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(";
    std::cout << "dimensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_5_5_t_t_t()
{
    Vertex dimensions = {{6, 5, 5}};
    Graph graph(dimensions, true);

    std::cout << std::endl << "void out_6_5_5_t_t_t()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 5, 5}};";
    std::cout << std::endl << "    Graph graph(dimensions, true);";
    std::cout << std::endl << std::endl << "    // Verify dimension lengths ";
    std::cout << "and wrapping." << std::endl << "    for (DimensionT d = 0;";
    std::cout << " d < 3; ++d)" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_CHECK(dimensions[d] == graph.length(d));";
    std::cout << std::endl << "        BOOST_CHECK(graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_6_5_f_f_f()
{
    Vertex dimensions = {{6, 6, 5}};
    Graph graph(dimensions, false);

    std::cout << std::endl << "void out_6_6_5_f_f_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 6, 5}};";
    std::cout << std::endl << "    Graph graph(dimensions, false);";
    std::cout << std::endl << std::endl << "    // Verify dimension lengths ";
    std::cout << "and wrapping." << std::endl << "    for (DimensionT d = 0;";
    std::cout << " d < 3; ++d)" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_CHECK(dimensions[d] == graph.length(d));";
    std::cout << std::endl << "        BOOST_CHECK(!graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_6_5_t_f_f()
{
    Vertex dimensions = {{6, 6, 5}};
    std::tr1::array<bool,3> wraparound = {{true, false, false}};
    Graph graph(dimensions, wraparound);

    std::cout << std::endl << "void out_6_6_5_t_f_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 6, 5}};";
    std::cout << std::endl << "    std::tr1::array<bool,3> wraparound = ";
    std::cout << "{{true, false, false}};" << std::endl;
    std::cout << "    Graph graph(dimensions, wraparound);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 3; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(";
    std::cout << "dimensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_6_5_t_t_f()
{
    Vertex dimensions = {{6, 6, 5}};
    std::tr1::array<bool,3> wraparound = {{true, true, false}};
    Graph graph(dimensions, wraparound);

    std::cout << std::endl << "void out_6_6_5_t_t_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 6, 5}};";
    std::cout << std::endl << "    std::tr1::array<bool,3> wraparound = ";
    std::cout << "{{true, true, false}};" << std::endl;
    std::cout << "    Graph graph(dimensions, wraparound);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 3; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(";
    std::cout << "dimensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_6_5_t_t_t()
{
    Vertex dimensions = {{6, 6, 5}};
    Graph graph(dimensions, true);

    std::cout << std::endl << "void out_6_6_5_t_t_t()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 6, 5}};";
    std::cout << std::endl << "    Graph graph(dimensions, true);";
    std::cout << std::endl << std::endl << "    // Verify dimension lengths ";
    std::cout << "and wrapping." << std::endl << "    for (DimensionT d = 0;";
    std::cout << " d < 3; ++d)" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_CHECK(dimensions[d] == graph.length(d));";
    std::cout << std::endl << "        BOOST_CHECK(graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_6_6_f_f_f()
{
    Vertex dimensions = {{6, 6, 6}};
    Graph graph(dimensions, false);

    std::cout << std::endl << "void out_6_6_6_f_f_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 6, 6}};";
    std::cout << std::endl << "    Graph graph(dimensions, false);";
    std::cout << std::endl << std::endl << "    // Verify dimension lengths ";
    std::cout << "and wrapping." << std::endl << "    for (DimensionT d = 0;";
    std::cout << " d < 3; ++d)" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_CHECK(dimensions[d] == graph.length(d));";
    std::cout << std::endl << "        BOOST_CHECK(!graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_6_6_t_f_f()
{
    Vertex dimensions = {{6, 6, 6}};
    std::tr1::array<bool,3> wraparound = {{true, false, false}};
    Graph graph(dimensions, wraparound);

    std::cout << std::endl << "void out_6_6_6_t_f_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 6, 6}};";
    std::cout << std::endl << "    std::tr1::array<bool,3> wraparound = ";
    std::cout << "{{true, false, false}};" << std::endl;
    std::cout << "    Graph graph(dimensions, wraparound);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 3; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(";
    std::cout << "dimensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_6_6_t_t_f()
{
    Vertex dimensions = {{6, 6, 6}};
    std::tr1::array<bool,3> wraparound = {{true, true, false}};
    Graph graph(dimensions, wraparound);

    std::cout << std::endl << "void out_6_6_6_t_t_f()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 6, 6}};";
    std::cout << std::endl << "    std::tr1::array<bool,3> wraparound = ";
    std::cout << "{{true, true, false}};" << std::endl;
    std::cout << "    Graph graph(dimensions, wraparound);" << std::endl;
    std::cout << std::endl << "    // Verify dimension lengths and wrapping.";
    std::cout << std::endl << "    for (DimensionT d = 0; d < 3; ++d)";
    std::cout << std::endl << "    {" << std::endl << "        BOOST_CHECK(";
    std::cout << "dimensions[d] == graph.length(d));" << std::endl;
    std::cout << "        BOOST_CHECK(wraparound[d] == graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

void out_6_6_6_t_t_t()
{
    Vertex dimensions = {{6, 6, 6}};
    Graph graph(dimensions, true);

    std::cout << std::endl << "void out_6_6_6_t_t_t()" << std::endl << '{';
    std::cout << std::endl << "    Vertex dimensions = {{6, 6, 6}};";
    std::cout << std::endl << "    Graph graph(dimensions, true);";
    std::cout << std::endl << std::endl << "    // Verify dimension lengths ";
    std::cout << "and wrapping." << std::endl << "    for (DimensionT d = 0;";
    std::cout << " d < 3; ++d)" << std::endl << "    {" << std::endl;
    std::cout << "        BOOST_CHECK(dimensions[d] == graph.length(d));";
    std::cout << std::endl << "        BOOST_CHECK(graph.wrapped(d));";
    std::cout << std::endl << "    }" << std::endl << std::endl;
    out_with_it(graph);
}

int main(int argc, char** argv)
{
    std::cout << "// Copyright (C) 2012 Cromwell D. Enage" << std::endl;
    std::cout << "// Distributed under the Boost Software License, ";
    std::cout << "Version 1.0." << std::endl << "// (See accompanying ";
    std::cout << "file LICENSE_1_0.txt or copy at" << std::endl;
    std::cout << "// http://www.boost.org/LICENSE_1_0.txt)" << std::endl;
    std::cout << std::endl << "#include <boost/foreach.hpp>" << std::endl;
    std::cout << "#include <boost/tr1/array.hpp>" << std::endl << "#include ";
    std::cout << "<boost/graph/graph_traits.hpp>" << std::endl << "#include ";
    std::cout << "<boost/graph/vertex_dimension_trait.hpp>" << std::endl;
    std::cout << "#include <boost/graph/edge_key_trait.hpp>" << std::endl;
    std::cout << "#include <boost/graph/btrnc_cubic_hcomb_graph.hpp>";
    std::cout << std::endl << "#include <boost/test/minimal.hpp>";
    std::cout << std::endl << "#include \"assoc_incidence_graph.hpp\"";
    std::cout << std::endl << std::endl;
    std::cout << "typedef boost::bitruncated_cubic_honeycomb_graph<> Graph;";
    std::cout << std::endl << "typedef boost::graph_traits<Graph>::vertex_";
    std::cout << "descriptor Vertex;" << std::endl << "typedef boost::";
    std::cout << "graph_traits<Graph>::vertices_size_type VertexIndex;";
    std::cout << std::endl << "typedef boost::graph_traits<Graph>::edge_";
    std::cout << "descriptor Edge;" << std::endl << "typedef boost::graph_";
    std::cout << "traits<Graph>::edges_size_type EdgeIndex;" << std::endl;
    std::cout << "typedef boost::graph_traits<Graph>::degree_size_type Degree";
    std::cout << "Index;" << std::endl << "typedef boost::vertex_dimension_";
    std::cout << "trait<Graph>::type DimensionT;" << std::endl << "typedef ";
    std::cout << "boost::edge_key_trait<Graph>::type EdgeKey;" << std::endl;
    out_2_2_2_f_f_f();
    out_5_5_5_f_f_f();
    out_5_5_5_t_f_f();
    out_5_5_5_t_t_f();
    out_5_5_5_t_t_t();
    out_6_5_5_f_f_f();
    out_6_5_5_t_f_f();
    out_6_5_5_t_t_f();
    out_6_5_5_t_t_t();
    out_6_6_5_f_f_f();
    out_6_6_5_t_f_f();
    out_6_6_5_t_t_f();
    out_6_6_5_t_t_t();
    out_6_6_6_f_f_f();
    out_6_6_6_t_f_f();
    out_6_6_6_t_t_f();
    out_6_6_6_t_t_t();
    std::cout << std::endl << "int test_main(int argc, char** argv)";
    std::cout << std::endl << '{' << std::endl;

    std::cout << "    out_2_2_2_f_f_f();" << std::endl;
    std::cout << "    out_5_5_5_f_f_f();" << std::endl;
    std::cout << "    out_5_5_5_t_f_f();" << std::endl;
    std::cout << "    out_5_5_5_t_t_f();" << std::endl;
    std::cout << "    out_5_5_5_t_t_t();" << std::endl;
    std::cout << "    out_6_5_5_f_f_f();" << std::endl;
    std::cout << "    out_6_5_5_t_f_f();" << std::endl;
    std::cout << "    out_6_5_5_t_t_f();" << std::endl;
    std::cout << "    out_6_5_5_t_t_t();" << std::endl;
    std::cout << "    out_6_6_5_f_f_f();" << std::endl;
    std::cout << "    out_6_6_5_t_f_f();" << std::endl;
    std::cout << "    out_6_6_5_t_t_f();" << std::endl;
    std::cout << "    out_6_6_5_t_t_t();" << std::endl;
    std::cout << "    out_6_6_6_f_f_f();" << std::endl;
    std::cout << "    out_6_6_6_t_f_f();" << std::endl;
    std::cout << "    out_6_6_6_t_t_f();" << std::endl;
    std::cout << "    out_6_6_6_t_t_t();" << std::endl;

    std::cout << "    return 0;" << std::endl << '}' << std::endl << std::endl;

    return 0;
}

