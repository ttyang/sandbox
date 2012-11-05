// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_TEST_ASSOC_INCIDENCE_GRAPH_HPP
#define LIBS_GRAPH_TEST_ASSOC_INCIDENCE_GRAPH_HPP

#include <set>
#include <utility>
#include <boost/foreach.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/vertex_coordinate_trait.hpp>
#include <boost/graph/edge_key_trait.hpp>
#include <boost/graph/graph_utility.hpp>

template <typename Graph>
void
    test_vertex(
        typename boost::graph_traits<Graph>::vertices_size_type const& i
      , Graph const& g
      , typename boost::vertex_coordinate_trait<Graph>::type const& d0
      , typename boost::vertex_coordinate_trait<Graph>::type const& d1
    )
{
    typename boost::graph_traits<Graph>::vertex_descriptor
        v = boost::vertex(i, g);

    BOOST_CHECK(v[0] == d0);
    BOOST_CHECK(v[1] == d1);
}

template <typename Graph>
void
    test_vertex(
        typename boost::graph_traits<Graph>::vertices_size_type const& i
      , Graph const& g
      , typename boost::vertex_coordinate_trait<Graph>::type const& d0
      , typename boost::vertex_coordinate_trait<Graph>::type const& d1
      , typename boost::vertex_coordinate_trait<Graph>::type const& d2
    )
{
    typename boost::graph_traits<Graph>::vertex_descriptor
        v = boost::vertex(i, g);

    BOOST_CHECK(v[0] == d0);
    BOOST_CHECK(v[1] == d1);
    BOOST_CHECK(v[2] == d2);
}

template <typename Graph>
void
    test_vertex(
        typename boost::graph_traits<Graph>::vertices_size_type const& i
      , Graph const& g
      , typename boost::vertex_coordinate_trait<Graph>::type const& d0
      , typename boost::vertex_coordinate_trait<Graph>::type const& d1
      , typename boost::vertex_coordinate_trait<Graph>::type const& d2
      , typename boost::vertex_coordinate_trait<Graph>::type const& d3
    )
{
    typename boost::graph_traits<Graph>::vertex_descriptor
        v = boost::vertex(i, g);

    BOOST_CHECK(v[0] == d0);
    BOOST_CHECK(v[1] == d1);
    BOOST_CHECK(v[2] == d2);
    BOOST_CHECK(v[3] == d3);
}

template <typename Graph>
void
    test_edge(
        typename boost::graph_traits<Graph>::vertices_size_type const& i
      , typename boost::graph_traits<Graph>::vertices_size_type const& j
      , Graph const& g
      , bool const b
    )
{
    BOOST_CHECK(
        b == boost::is_adjacent(g, boost::vertex(i, g), boost::vertex(j, g))
    );
    BOOST_CHECK(
        b == boost::is_adjacent(g, boost::vertex(j, g), boost::vertex(i, g))
    );
    BOOST_CHECK(
        b == boost::edge(boost::vertex(i, g), boost::vertex(j, g), g).second
    );
    BOOST_CHECK(
        b == boost::edge(boost::vertex(j, g), boost::vertex(i, g), g).second
    );
}

template <typename Graph>
void test_edge_list(Graph const& g)
{
    typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
    typedef typename boost::graph_traits<Graph>::edges_size_type EdgeIndex;

    typename boost::property_map<Graph,boost::vertex_index_t>::type
        v_index_map = boost::get(boost::vertex_index, g);
    typename boost::property_map<Graph,boost::edge_index_t>::type
        e_index_map = boost::get(boost::edge_index, g);
    std::set<EdgeIndex> edge_indices;

    BOOST_FOREACH(Edge e, boost::edges(g))
    {
        test_edge(
            boost::get(v_index_map, source(e, g))
          , boost::get(v_index_map, target(e, g))
          , g
          , true
        );
        EdgeIndex const edge_index = boost::get(e_index_map, e);
        BOOST_CHECK(edge_index < boost::num_edges(g));
        bool const inserted = edge_indices.insert(edge_index).second;
        BOOST_CHECK(inserted);
    }

    BOOST_CHECK(boost::num_edges(g) == edge_indices.size());
}

template <typename Graph, typename DiffT>
void
    test_edge_key(
        typename boost::graph_traits<Graph>::degree_size_type k_i
      , Graph const& g
      , DiffT d0
      , DiffT d1
    )
{
    typename boost::edge_key_trait<Graph>::type k = boost::edge_key(k_i, g);
    BOOST_CHECK(k[0] == d0);
    BOOST_CHECK(k[1] == d1);
}

template <typename Graph, typename DiffT>
void
    test_edge_key(
        typename boost::graph_traits<Graph>::degree_size_type k_i
      , Graph const& g
      , DiffT d0
      , DiffT d1
      , DiffT d2
    )
{
    typename boost::edge_key_trait<Graph>::type k = boost::edge_key(k_i, g);
    BOOST_CHECK(k[0] == d0);
    BOOST_CHECK(k[1] == d1);
    BOOST_CHECK(k[2] == d2);
}

template <typename Graph, typename DiffT>
void
    test_edge_key(
        typename boost::graph_traits<Graph>::degree_size_type k_i
      , Graph const& g
      , DiffT d0
      , DiffT d1
      , DiffT d2
      , DiffT d3
    )
{
    typename boost::edge_key_trait<Graph>::type k = boost::edge_key(k_i, g);
    BOOST_CHECK(k[0] == d0);
    BOOST_CHECK(k[1] == d1);
    BOOST_CHECK(k[2] == d2);
    BOOST_CHECK(k[3] == d3);
}

template <typename Graph>
void
    test_next_previous(
        typename boost::graph_traits<Graph>::vertices_size_type i
      , typename boost::graph_traits<Graph>::degree_size_type k_i
      , Graph const& g
      , typename boost::graph_traits<Graph>::vertices_size_type n
      , typename boost::graph_traits<Graph>::vertices_size_type p
    )
{
    typename boost::edge_key_trait<Graph>::type k = boost::edge_key(k_i, g);
    BOOST_CHECK(boost::vertex(n, g) == g.next(boost::vertex(i, g), k));
    BOOST_CHECK(boost::vertex(p, g) == g.previous(boost::vertex(i, g), k));
}

template <typename Graph>
void
    test_next_previous(
        typename boost::graph_traits<Graph>::vertices_size_type i
      , typename boost::graph_traits<Graph>::degree_size_type k_i
      , typename boost::vertex_coordinate_trait<Graph>::type d
      , Graph const& g
      , typename boost::graph_traits<Graph>::vertices_size_type n
      , typename boost::graph_traits<Graph>::vertices_size_type p
    )
{
    typename boost::edge_key_trait<Graph>::type k = boost::edge_key(k_i, g);
    typename boost::graph_traits<Graph>::vertex_descriptor
        s = boost::vertex(i, g),
        u = boost::vertex(n, g),
        v = boost::vertex(p, g);
    BOOST_CHECK(u == g.next(s, k, d));
    BOOST_CHECK(v == g.previous(s, k, d));
    typename boost::vertex_coordinate_trait<Graph>::type d_i = (
        boost::initialized_value
    );

    while (++d_i < d)
    {
        typename boost::graph_traits<Graph>::vertex_descriptor
           w = g.next(s, k, d_i);
        typename boost::graph_traits<Graph>::vertex_descriptor
           x = g.next(w, k, d - d_i);
        BOOST_CHECK(u == x);
        w = g.previous(s, k, d_i);
        x = g.previous(w, k, d - d_i);
        BOOST_CHECK(v == x);
    }
}

template <typename Graph>
void test_indices_and_incidence(Graph const& graph)
{
    typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef typename boost::graph_traits<Graph>::vertices_size_type VertIndex;
    typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
    typedef typename boost::graph_traits<Graph>::edges_size_type EdgeIndex;
    typedef typename boost::graph_traits<Graph>::degree_size_type DegreeIndex;
    typedef typename boost::edge_key_trait<Graph>::type EdgeKey;

    // Verify matching indices.
    for (
        VertIndex v_idx = boost::initialized_value;
        v_idx < boost::num_vertices(graph);
        ++v_idx
    )
    {
        Vertex const v = boost::vertex(v_idx, graph);
        BOOST_CHECK(v_idx == boost::get(boost::vertex_index, graph, v));
    }

    typename boost::property_map<Graph,boost::vertex_index_t>::type
        v_index_map = boost::get(boost::vertex_index, graph);

    BOOST_FOREACH(Vertex v, boost::vertices(graph))
    {
        // Verify one-to-one vertex-index mapping.
        BOOST_CHECK(v == boost::vertex(boost::get(v_index_map, v), graph));

        // Verify that v's out-edges are within bounds.
        std::set<VertIndex> target_indices;

        BOOST_FOREACH(Edge e, boost::out_edges(v, graph))
        {
            VertIndex const t_idx = boost::get(v_index_map, target(e, graph));
            bool const inserted = target_indices.insert(t_idx).second;
            BOOST_CHECK(inserted);
        }

        // Verify that v's in-edges are within bounds.
        BOOST_FOREACH(Edge e, boost::in_edges(v, graph))
        {
            VertIndex const s_idx = boost::get(v_index_map, source(e, graph));
            BOOST_CHECK(target_indices.find(s_idx) != target_indices.end());
        }

        // Verify correctness of degree functions.
        BOOST_CHECK(target_indices.size() == boost::out_degree(v, graph));
        BOOST_CHECK(boost::out_degree(v, graph) == boost::in_degree(v, graph));
        BOOST_CHECK(
            boost::degree(v, graph) == (
                boost::out_degree(v, graph) + boost::in_degree(v, graph)
            )
        );

        // Verify that v's adjacent vertices are within bounds.
        std::size_t adjacent_count = boost::initialized_value;

        BOOST_FOREACH(Vertex u, boost::adjacent_vertices(v, graph))
        {
            VertIndex const u_idx = boost::get(v_index_map, u);
            BOOST_CHECK(target_indices.find(u_idx) != target_indices.end());
            ++adjacent_count;
        }

        BOOST_CHECK(adjacent_count == target_indices.size());

        // Verify that v's edges and non-adjacent vertices are within bounds
        // via AdjacenyMatrix access.
        BOOST_FOREACH(Vertex u, boost::vertices(graph))
        {
            if (
                target_indices.find(
                    boost::get(v_index_map, u)
                ) == target_indices.end()
            )
            {
                std::pair<Edge,bool> e_b = boost::edge(u, v, graph);
                BOOST_CHECK(!e_b.second);
                e_b = boost::edge(v, u, graph);
                BOOST_CHECK(!e_b.second);
            }
            else
            {
                std::pair<Edge,bool> e_b = boost::edge(u, v, graph);
                BOOST_CHECK(e_b.second);
                e_b = boost::edge(v, u, graph);
                BOOST_CHECK(e_b.second);
            }
        }

        // Verify that v's next and previous vertices are within bounds.
        for (
            DegreeIndex d_i = boost::initialized_value;
            d_i < boost::num_edge_keys(graph);
            ++d_i
        )
        {
            EdgeKey k = boost::edge_key(d_i, graph);
            Vertex u = graph.next(v, k);

            BOOST_CHECK(
                (v == u) == (
                    target_indices.find(
                        boost::get(v_index_map, u)
                    ) == target_indices.end()
                )
            );

            u = graph.previous(v, k);

            BOOST_CHECK(
                (v == u) == (
                    target_indices.find(
                        boost::get(v_index_map, u)
                    ) == target_indices.end()
                )
            );
        }
    }
}

#endif  // LIBS_GRAPH_TEST_ASSOC_INCIDENCE_GRAPH_HPP

