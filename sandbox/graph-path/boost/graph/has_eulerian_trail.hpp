// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_HAS_EULERIAN_TRAIL_HPP
#define BOOST_GRAPH_HAS_EULERIAN_TRAIL_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/tr1/tuple.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/weak_components.hpp>
#include <boost/graph/vertex_property_map_gen.hpp>

namespace boost { namespace detail {

    template <typename InputGraph>
    bool has_eulerian_trail_impl(InputGraph const& graph, undirected_tag)
    {
        typedef typename graph_traits<InputGraph>::vertices_size_type Count;

        Count odd_count = 0;
        typename graph_traits<InputGraph>::vertex_iterator vi, vi_end;

        for (::std::tr1::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi)
        {
            if (out_degree(*vi, graph) & 1)
            {
                if (2 < ++odd_count)
                {
                    return false;
                }
            }
        }

        typename vertex_property_map_gen<InputGraph,Count>::type component_map(
            graph
        );

        return 1 == connected_components(graph, component_map);
    }

    template <typename InputGraph>
    bool has_eulerian_trail_impl(InputGraph const& graph, bidirectional_tag)
    {
        typedef typename graph_traits<InputGraph>::vertices_size_type Count;

        Count in_count = 0, out_count = 0;
        typename graph_traits<InputGraph>::vertex_iterator vi, vi_end;
        typename graph_traits<InputGraph>::degree_size_type d_in, d_out;

        for (::std::tr1::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi)
        {
            d_in = in_degree(*vi, graph);
            d_out = out_degree(*vi, graph);

            if (d_out + 1 < d_in)
            {
                return false;
            }
            else if (d_out + 1 == d_in)
            {
                if (1 < ++in_count)
                {
                    return false;
                }
            }

            if (d_in + 1 < d_out)
            {
                return false;
            }
            else if (d_in + 1 == d_out)
            {
                if (1 < ++out_count)
                {
                    return false;
                }
            }
        }

        typename vertex_property_map_gen<InputGraph,Count>::type component_map(
            graph
        );

        return 1 == weak_components(graph, component_map);
    }

    template <typename InputGraph>
    bool has_eulerian_trail_impl(InputGraph const& graph, directed_tag)
    {
        typedef typename graph_traits<InputGraph>::degree_size_type Degree;

        typename vertex_property_map_gen<InputGraph,Degree>::type in_deg(
            graph
        );
        typename graph_traits<InputGraph>::vertex_iterator vi, vi_end;

        for (::std::tr1::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi)
        {
            put(in_deg, *vi, 0);
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
                typename graph_traits<InputGraph>::vertex_descriptor
                    u = target(*ei, graph);

                put(in_deg, u, 1 + get(in_deg, u));
            }
        }

        typedef typename graph_traits<InputGraph>::vertices_size_type Count;

        Count in_count = 0, out_count = 0;

        for (vi = vertices(graph).first; vi != vi_end; ++vi)
        {
            Degree d_in = get(in_deg, *vi), d_out = out_degree(*vi, graph);

            if (d_out + 1 < d_in)
            {
                return false;
            }
            else if (d_out + 1 == d_in)
            {
                if (1 < ++in_count)
                {
                    return false;
                }
            }

            if (d_in + 1 < d_out)
            {
                return false;
            }
            else if (d_in + 1 == d_out)
            {
                if (1 < ++out_count)
                {
                    return false;
                }
            }
        }

        typename vertex_property_map_gen<InputGraph,Count>::type component_map(
            graph
        );

        return 1 == weak_components(graph, component_map);
    }
}}  // namespace boost::detail

//[reference__has_eulerian_trail
namespace boost {

    template <typename InputGraph>
    bool has_eulerian_trail(InputGraph const& input_graph);

    //<-
    template <typename InputGraph>
    inline bool has_eulerian_trail(InputGraph const& input_graph)
    {
        return detail::has_eulerian_trail_impl(
            input_graph
          , typename graph_traits<InputGraph>::directed_category()
        );
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_HAS_EULERIAN_TRAIL_HPP

