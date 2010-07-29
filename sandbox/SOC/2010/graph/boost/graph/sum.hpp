//
//=======================================================================
// Copyright 1997-2001 University of Notre Dame.
// Authors: Jeremy G. Siek, Lie-Quan Lee, Andrew Lumsdaine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_GRAPH_SUM_HPP
#define BOOST_GRAPH_SUM_HPP

#include <utility>
#include <boost/graph/global_vertex_mapping.hpp>
#include <boost/graph/graph_traits.hpp>

namespace boost {

  template <class VertexListGraph, class MutableGraph> 
  void graph_sum(const VertexListGraph& g1, const VertexListGraph& g2, MutableGraph& g_out)
  {
    typedef typename graph_traits<VertexListGraph>::vertex_descriptor InVertex;
    typedef typename graph_traits<MutableGraph>::vertex_descriptor OutVertex;
    
    detail::vertex_copier<VertexListGraph, MutableGraph>
      copy_vertex1 = detail::make_vertex_copier(g1, g_out), copy_vertex2 = detail::make_vertex_copier(g2, g_out);
    detail::edge_copier<VertexListGraph, MutableGraph>
      copy_edge1 = detail::make_edge_copier(g1, g_out), copy_edge2 = detail::make_edge_copier(g2, g_out);

    auto & gl1 = get_property(g1, graph_label).hack->vertices; // c++ 0x
    auto & gl2 = get_property(g2, graph_label).hack->vertices;
    auto & gl_out  = get_property(g_out, graph_label).hack->vertices;
    auto & gl_oute = get_property(g_out, graph_label).hack->edges;

    typename graph_traits < VertexListGraph >::vertex_iterator vi, vi_end;
    // copy vertices from g1
    for (tie(vi, vi_end) = vertices(g1); vi != vi_end; ++vi) {
      OutVertex new_v = add_vertex(g_out);
      copy_vertex1(*vi, new_v);
      assert( g_out[new_v].name == g1[*vi].name); // copy_vertex already did it
      gl_out[ g1[*vi].name ] = new_v;
    }
    // copy vertices from (g2 - g1)
    for (tie(vi, vi_end) = vertices(g2); vi != vi_end; ++vi) {
      if ( gl1.find ( g2[*vi].name ) == gl1.end() ) { // if vi is not in g1
        OutVertex new_v = add_vertex(g_out);
        copy_vertex2(*vi, new_v);
        assert( g_out[new_v].name == g2[*vi].name ); // copy_vertex already did it
        gl_out[ g2[*vi].name ] = new_v;
      }
    }

    typename graph_traits < VertexListGraph >::edge_iterator ei, ei_end;
    typename graph_traits < MutableGraph >::edge_descriptor new_e;
    bool inserted;

    // copy edges from g1
    for (tie(ei, ei_end) = edges(g1); ei != ei_end; ++ei) {
      auto src  = g1[source(*ei, g1)].name;
      auto targ = g1[target(*ei, g1)].name;

      assert( gl_out.find(src)  != gl_out.end() );
      assert( gl_out.find(targ) != gl_out.end() );

      boost::tie(new_e, inserted) = add_edge(gl_out[src], gl_out[targ], g_out);
      copy_edge1(*ei, new_e);
      assert( g_out[new_e].name == g1[*ei].name ); // copy_edge already did it
      get_property(g_out, graph_label).hack->edges[ g1[*ei].name ] = new_e;
    }
    // copy edges from g2 if it is *not* already there
    for (tie(ei, ei_end) = edges(g2); ei != ei_end; ++ei) {
      auto src  = g2[source(*ei, g2)].name;
      auto targ = g2[target(*ei, g2)].name;

      assert( gl_out.find(src)  != gl_out.end() );
      assert( gl_out.find(targ) != gl_out.end() );

      if ( gl_oute.find( g2[*ei].name ) == gl_oute.end() ) { // ei is not yet in g_out
        boost::tie(new_e, inserted) = add_edge(gl_out[src], gl_out[targ], g_out);
        copy_edge2(*ei, new_e);
        assert( g_out[new_e].name == g2[*ei].name ); // copy_edge already did it
        get_property(g_out, graph_label).hack->edges[ g2[*ei].name ] = new_e;
      }
    }
  }

  // Version with globalVertexMapping
  template <class VertexListGraph, class MutableGraph, class globalVertexMapping> 
  void gvm_graph_sum(const VertexListGraph& g1, const VertexListGraph& g2, globalVertexMapping m, MutableGraph& g_out)
  {
    typedef typename graph_traits<VertexListGraph>::vertex_descriptor InVertex;
    typedef typename graph_traits<MutableGraph>::vertex_descriptor OutVertex;
    typedef typename globalVertexMapping::global_id_type id_type;

    detail::vertex_copier<VertexListGraph, MutableGraph>
      copy_vertex1 = detail::make_vertex_copier(g1, g_out), copy_vertex2 = detail::make_vertex_copier(g2, g_out);
    detail::edge_copier<VertexListGraph, MutableGraph>
      copy_edge1 = detail::make_edge_copier(g1, g_out), copy_edge2 = detail::make_edge_copier(g2, g_out);


    typename graph_traits < VertexListGraph >::vertex_iterator vi, vi_end;
    // copy vertices from g1
    for (tie(vi, vi_end) = vertices(g1); vi != vi_end; ++vi) {
      OutVertex new_v = add_vertex(g_out);
      copy_vertex1(*vi, new_v);
      std::pair < typename globalVertexMapping::global_id_type, bool > id = m.get_id(g1, *vi);
      assert (id.second == true);
      m.associate(g_out, new_v, id.first);
    }
    // copy vertices from (g2 - g1)
    for (tie(vi, vi_end) = vertices(g2); vi != vi_end; ++vi) {
      std::pair < InVertex, bool > v = m.find_vertex( g2, *vi, g1 ); // search for vi in g1
      if (v.second == false) { // vi is not in g1
        OutVertex new_v = add_vertex(g_out);
        copy_vertex2(*vi, new_v);
        std::pair < id_type, bool > id = m.get_id(g2, *vi);
        assert (id.second == true);
        m.associate(g_out, new_v, id.first);
      }
    }

    typename graph_traits < VertexListGraph >::edge_iterator ei, ei_end;
    // copy edges from g1
    for (tie(ei, ei_end) = edges(g1); ei != ei_end; ++ei) {
      std::pair < OutVertex, bool > out_s, out_t;
      out_s = m.find_vertex( g1, source(*ei, g1), g_out );
      out_t = m.find_vertex( g1, target(*ei, g1), g_out );
      assert(out_s.second == true && out_t.second == true);

      typename graph_traits<MutableGraph>::edge_descriptor new_e;
      bool inserted;
      boost::tie(new_e, inserted) = add_edge(out_s.first, out_t.first, g_out);
      copy_edge1(*ei, new_e);
    }
    // copy edges from g2
    for (tie(ei, ei_end) = edges(g2); ei != ei_end; ++ei) {
      std::pair < OutVertex, bool > out_s, out_t;
      out_s = m.find_vertex( g2, source(*ei, g2), g_out );
      out_t = m.find_vertex( g2, target(*ei, g2), g_out );
      assert(out_s.second == true && out_t.second == true);

      typename graph_traits<MutableGraph>::edge_descriptor new_e;
      bool inserted;
      boost::tie(new_e, inserted) = add_edge(out_s.first, out_t.first, g_out);
      copy_edge2(*ei, new_e);
    }
  }

} // namespace boost

#endif // BOOST_GRAPH_SUM_HPP
