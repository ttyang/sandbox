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

#ifndef BOOST_GRAPH_INTERSECTION_HPP
#define BOOST_GRAPH_INTERSECTION_HPP

#include <boost/config.hpp>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/type_traits/conversion_traits.hpp>

namespace boost {

  template <class VertexListGraph, class MutableGraph> 
  void intersection(const VertexListGraph& G1, const VertexListGraph& G2, MutableGraph& G)
  {
    typename graph_traits < MutableGraph >::edge_iterator ei, ei_end;
    typename property_map < MutableGraph, vertex_name_t >::type name_map_G = get(vertex_name, G);
    //    typename property_map < VertexListGraph, vertex_name_t >::type name_map_G1 = get(vertex_name, G1);


    for (tie(ei, ei_end) = edges(G1); ei != ei_end; ++ei)
      if (edge(source(*ei, G1), target(*ei, G1), G2).second == true)
        add_edge(source(*ei, G1), target(*ei, G1), G);

  }

} // namespace boost

#endif // BOOST_GRAPH_INTERSECTION_HPP
