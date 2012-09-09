// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_FIND_EULERIAN_TRAIL_HPP
#define BOOST_GRAPH_FIND_EULERIAN_TRAIL_HPP

#include <boost/tr1/tuple.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/detail/find_eulerian_path.hpp>
#include <boost/graph/has_eulerian_trail.hpp>
#include <boost/graph/vertex_property_map_gen.hpp>
#include <boost/assert.hpp>

namespace boost { namespace detail {

    template <typename InputGraph>
    typename graph_traits<InputGraph>::vertex_descriptor
        find_eulerian_trail_root(
            InputGraph const& graph
          , undirected_tag
        )
    {
        typename graph_traits<InputGraph>::vertex_iterator vi, vi_end;

        ::std::tr1::tie(vi, vi_end) = vertices(graph);

        typename graph_traits<InputGraph>::vertex_descriptor result = *vi;

        while (++vi != vi_end)
        {
            if (out_degree(*vi, graph) & 1)
            {
                result = *vi;
                break;
            }
        }

        return result;
    }

    template <typename InputGraph>
    typename graph_traits<InputGraph>::vertex_descriptor
        find_eulerian_trail_root(
            InputGraph const& graph
          , bidirectional_tag
        )
    {
        typename graph_traits<InputGraph>::vertex_iterator vi, vi_end;

        ::std::tr1::tie(vi, vi_end) = vertices(graph);

        typename graph_traits<InputGraph>::vertex_descriptor result = *vi;

        while (++vi != vi_end)
        {
            if (in_degree(*vi, graph) < out_degree(*vi, graph))
            {
                result = *vi;
                break;
            }
        }

        return result;
    }

    template <typename InputGraph>
    typename graph_traits<InputGraph>::vertex_descriptor
        find_eulerian_trail_root(
            InputGraph const& graph
          , directed_tag
        )
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

        vi = vertices(graph).first;

        typename graph_traits<InputGraph>::vertex_descriptor result = *vi;

        while (++vi != vi_end)
        {
            if (get(in_deg, *vi) < out_degree(*vi, graph))
            {
                result = *vi;
                break;
            }
        }

        return result;
    }
}}  // namespace boost::detail

//[reference__find_eulerian_trail
namespace boost {

    template <typename InputGraph, typename OutputIterator, typename Visitor>
    bool
        find_eulerian_trail(
            InputGraph const& input_graph
          , OutputIterator result
          , Visitor visitor
        );

    //<-
    template <typename InputGraph, typename OutputIterator, typename Visitor>
    inline bool
        find_eulerian_trail(
            InputGraph const& input_graph
          , OutputIterator result
          , Visitor visitor
        )
    {
        BOOST_ASSERT(has_eulerian_trail(input_graph));

        detail::find_eulerian_path_impl(
            input_graph
          , result
          , detail::find_eulerian_trail_root(
                input_graph
              , typename graph_traits<InputGraph>::directed_category()
            )
          , visitor
          , typename graph_traits<InputGraph>::directed_category()
        );
        return true;
    }
    //->

    template <typename InputGraph, typename OutputIterator>
    bool
        find_eulerian_trail(
            InputGraph const& input_graph
          , OutputIterator result
        );

    //<-
    template <typename InputGraph, typename OutputIterator>
    inline bool
        find_eulerian_trail(
            InputGraph const& input_graph
          , OutputIterator result
        )
    {
        return find_eulerian_trail(input_graph, result, null_visitor());
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_FIND_EULERIAN_TRAIL_HPP

