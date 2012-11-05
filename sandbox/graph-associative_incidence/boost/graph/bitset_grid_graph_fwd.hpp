// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_BITSET_GRID_GRAPH_FWD_HPP
#define BOOST_GRAPH_BITSET_GRID_GRAPH_FWD_HPP

#include <utility>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/edge_key_trait.hpp>

#define BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS \
typename BitCount, typename VertexIndex, typename EdgeIndex, typename AllocSel

#define BOOST_GRAPH_BITSET_GRID_TYPE \
bitset_grid_graph<BitCount,VertexIndex,EdgeIndex,AllocSel>

#define BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(mem) \
typename graph_traits<BOOST_GRAPH_BITSET_GRID_TYPE>::mem

namespace boost {

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    class bitset_grid_graph;

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
        num_edge_keys(BOOST_GRAPH_BITSET_GRID_TYPE const& graph);

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    typename edge_key_trait<BOOST_GRAPH_BITSET_GRID_TYPE>::type
        edge_key(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_iterator)
    >
        vertices(BOOST_GRAPH_BITSET_GRID_TYPE const& graph);

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertices_size_type) const&
        num_vertices(BOOST_GRAPH_BITSET_GRID_TYPE const& graph);

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor)
        vertex(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertices_size_type) const& index
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_iterator)
    >
        edges(BOOST_GRAPH_BITSET_GRID_TYPE const& graph);

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edges_size_type) const&
        num_edges(BOOST_GRAPH_BITSET_GRID_TYPE const& graph);

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)
        edge_at(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edges_size_type) const& index
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(out_edge_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(out_edge_iterator)
    >
        out_edges(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
        out_degree(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)
        out_edge_at(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(adjacency_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(adjacency_iterator)
    >
        adjacent_vertices(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    ::std::pair<
        BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(in_edge_iterator)
      , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(in_edge_iterator)
    >
        in_edges(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
        in_degree(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type)
        degree(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor)
        in_edge_at(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(degree_size_type) const& index
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    ::std::pair<BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor),bool>
        edge(
            BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& u
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    typename ::boost::property_map<
        BOOST_GRAPH_BITSET_GRID_TYPE
      , vertex_index_t
    >::type
        get(vertex_index_t, BOOST_GRAPH_BITSET_GRID_TYPE const& graph);

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertices_size_type)
        get(
            vertex_index_t
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(vertex_descriptor) const& v
        );

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    typename ::boost::property_map<
        BOOST_GRAPH_BITSET_GRID_TYPE
      , edge_index_t
    >::type
        get(edge_index_t, BOOST_GRAPH_BITSET_GRID_TYPE const& graph);

    template <BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS>
    BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edges_size_type)
        get(
            edge_index_t
          , BOOST_GRAPH_BITSET_GRID_TYPE const& graph
          , BOOST_GRAPH_BITSET_GRID_TRAITS_MEM(edge_descriptor) const& v
        );
}  // namespace boost

#undef BOOST_GRAPH_BITSET_GRID_TRAITS_MEM
#undef BOOST_GRAPH_BITSET_GRID_TYPE
#undef BOOST_GRAPH_BITSET_GRID_TEMPLATE_PARAMS

#endif  // BOOST_GRAPH_BITSET_GRID_GRAPH_FWD_HPP

