// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_WEAK_COMPONENTS_HPP
#define BOOST_GRAPH_WEAK_COMPONENTS_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/tr1/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/vertex_property_map_gen.hpp>

//[reference__weak_components
namespace boost {

    template <typename InputGraph, typename ComponentMap>
    typename ::boost::property_traits<ComponentMap>::value_type
        weak_components(InputGraph const& graph, ComponentMap component_map);

    //<-
    template <typename InputGraph, typename ComponentMap>
    typename ::boost::property_traits<ComponentMap>::value_type
        weak_components(InputGraph const& graph, ComponentMap component_map)
    {
        if (num_vertices(graph) == 0)
        {
            return 0;
        }

        typedef adjacency_list<setS,vecS,undirectedS> UGraph;

        UGraph u_graph;
        typename vertex_property_map_gen<
            InputGraph
          , UGraph::vertex_descriptor
        >::type graph2u(graph);
        typename graph_traits<InputGraph>::vertex_iterator vi, vi_end;

        for (::std::tr1::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi)
        {
            put(graph2u, *vi, add_vertex(u_graph));
        }

        for (vi = vertices(graph).first; vi != vi_end; ++vi)
        {
            typename graph_traits<InputGraph>::out_edge_iterator ei, ei_end;

            for (
                ::std::tr1::tie(ei, ei_end) = out_edges(*vi, graph);
                ei != ei_end;
                ++ei
            )
            {
                add_edge(
                    get(graph2u, source(*ei, graph))
                  , get(graph2u, target(*ei, graph))
                  , u_graph
                );
            }
        }

        typedef typename ::boost::property_traits<ComponentMap>::value_type
                Result;

        typename vertex_property_map_gen<UGraph,Result>::type u_comp_map(
            u_graph
        );
        Result result = connected_components(u_graph, u_comp_map);

        for (vi = vertices(graph).first; vi != vi_end; ++vi)
        {
            put(component_map, *vi, get(u_comp_map, get(graph2u, *vi)));
        }

        return result;
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_WEAK_COMPONENTS_HPP

