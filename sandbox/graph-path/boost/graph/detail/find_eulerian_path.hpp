// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_FIND_EULERIAN_PATH_HPP
#define BOOST_GRAPH_DETAIL_FIND_EULERIAN_PATH_HPP

#include <algorithm>
#include <list>
#include <set>
#include <utility>
#include <boost/property_map/property_map.hpp>
#include <boost/tr1/tuple.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/call_visitors.hpp>
#include <boost/graph/vertex_property_map_gen.hpp>

namespace boost { namespace detail {

    template <typename InputGraph>
    struct eulerian_vertex;

    template <typename InputGraph>
    struct eulerian_edge
    {
        typename graph_traits<InputGraph>::edge_descriptor edge;
        eulerian_vertex<InputGraph>* source;
        eulerian_vertex<InputGraph>* target;
    };

    template <typename InputGraph>
    inline bool
        operator<(
            eulerian_edge<InputGraph> const& lhs
          , eulerian_edge<InputGraph> const& rhs
        )
    {
        return (lhs.edge) < (rhs.edge);
    }

    template <typename InputGraph>
    struct eulerian_vertex
    {
        typedef ::std::list<eulerian_edge<InputGraph> > edge_list;

        ::boost::intrusive::list_member_hook<> hook;
        edge_list edges;
        typename graph_traits<InputGraph>::vertex_descriptor vertex;
        typename edge_list::iterator in_edge_itr;

        eulerian_vertex();
    };

    template <typename InputGraph>
    eulerian_vertex<InputGraph>::eulerian_vertex()
      : hook()
      , edges()
      , vertex(graph_traits<InputGraph>::null_vertex())
      , in_edge_itr()
    {
    }

    template <typename InputGraph, typename OutIterator, typename Visitors>
    void
        find_eulerian_path_impl(
            InputGraph const& graph
          , OutIterator output_edges
          , typename graph_traits<InputGraph>::vertex_descriptor start
          , Visitors visitors
          , undirected_tag
        )
    {
        typedef eulerian_edge<InputGraph> EulerEdge;
        typedef eulerian_vertex<InputGraph> EulerVertex;
        typedef ::std::multiset<EulerEdge> AllEdges;
        typedef typename EulerVertex::edge_list PathEdges;
        typedef ::boost::intrusive::list<
                    EulerVertex
                  , ::boost::intrusive::member_hook<
                        EulerVertex
                      , ::boost::intrusive::list_member_hook<>
                      , &EulerVertex::hook
                    >
                >
                VertexRefs;

        typename vertex_property_map_gen<
            InputGraph
          , EulerVertex
        >::type euler_map(graph);
        VertexRefs path_vertices;
        AllEdges all_edges;
        typename VertexRefs::iterator path_vertex_itr;
        typename graph_traits<InputGraph>::vertex_iterator vi, vi_end;

        for (::std::tr1::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi)
        {
            EulerVertex& e_u = get(euler_map, *vi);

            e_u.vertex = *vi;
            call_visitors<on_initialize_vertex>(visitors, *vi, graph);

            if (*vi == start)
            {
                path_vertex_itr = path_vertices.insert(
                    path_vertices.end()
                  , e_u
                );
            }

            typename graph_traits<InputGraph>::out_edge_iterator ei, ei_end;

            for (
                ::std::tr1::tie(ei, ei_end) = out_edges(*vi, graph);
                ei != ei_end;
                ++ei
            )
            {
                EulerEdge e_edge;
                EulerVertex& e_v = get(euler_map, target(*ei, graph));

                e_edge.edge = *ei;
                e_edge.source = &e_u;
                e_edge.target = &e_v;
                e_u.edges.push_back(e_edge);
                all_edges.insert(e_edge);
            }
        }

        call_visitors<on_start_vertex>(visitors, start, graph);

        PathEdges path_edges;
        typename PathEdges::iterator path_edge_itr = path_edges.insert(
            path_edges.end()
          , path_vertex_itr->edges.front()
        );

        path_vertex_itr->edges.pop_front();
        call_visitors<on_examine_edge>(
            visitors
          , path_edge_itr->edge
          , graph
        );
        path_vertex_itr->in_edge_itr = path_edges.begin();
        all_edges.erase(
            all_edges.lower_bound(*path_edge_itr)
          , all_edges.upper_bound(*path_edge_itr)
        );

        if (path_vertex_itr->edges.empty())
        {
            call_visitors<on_finish_vertex>(
                visitors
              , path_vertex_itr->vertex
              , graph
            );
            path_vertex_itr = path_vertices.erase(path_vertex_itr);
        }

        path_vertex_itr = path_vertices.insert(
            path_vertex_itr
          , *path_edge_itr->target
        );
        path_vertex_itr->in_edge_itr = path_edge_itr;

        for (;;)
        {
            if (path_vertex_itr->edges.empty())
            {
                call_visitors<on_finish_vertex>(
                    visitors
                  , path_vertex_itr->vertex
                  , graph
                );
                path_vertices.erase(path_vertex_itr);

                if (path_vertices.empty())
                {
                    break;
                }
                else
                {
                    path_vertex_itr = path_vertices.begin();
                    path_edge_itr = path_vertex_itr->in_edge_itr;
                    call_visitors<on_start_vertex>(
                        visitors
                      , path_vertex_itr->vertex
                      , graph
                    );
                    continue;
                }
            }

            EulerEdge& e_edge = path_vertex_itr->edges.front();
            typename AllEdges::iterator e_itr = all_edges.lower_bound(e_edge);
            typename AllEdges::iterator e_end = all_edges.upper_bound(e_edge);

            if (e_itr == e_end)
            {
                path_vertex_itr->edges.pop_front();
                continue;
            }
            else
            {
                path_edge_itr = path_edges.insert(
                    path_vertex_itr->in_edge_itr
                  , e_edge
                );
                call_visitors<on_examine_edge>(
                    visitors
                  , path_edge_itr->edge
                  , graph
                );
                all_edges.erase(e_itr, e_end);
                path_vertex_itr->edges.pop_front();
            }

            if (path_vertex_itr->edges.empty())
            {
                path_vertex_itr = path_vertices.erase(path_vertex_itr);
            }

            EulerVertex& e_v = *path_edge_itr->target;

            if (e_v.hook.is_linked())
            {
                path_vertex_itr = path_vertices.iterator_to(e_v);
            }
            else
            {
                path_vertex_itr = path_vertices.insert(path_vertex_itr, e_v);
            }

            path_vertex_itr->in_edge_itr = path_edge_itr;
        }

        for (
            typename PathEdges::reverse_iterator r_itr = path_edges.rbegin();
            r_itr != path_edges.rend();
            ++r_itr
        )
        {
            *output_edges = r_itr->edge;
            ++output_edges;
        }
    }

    template <typename InputGraph, typename OutIterator, typename Visitors>
    void
        find_eulerian_path_impl(
            InputGraph const& graph
          , OutIterator output_edges
          , typename graph_traits<InputGraph>::vertex_descriptor start
          , Visitors visitors
          , directed_tag
        )
    {
        typedef eulerian_edge<InputGraph> EulerEdge;
        typedef eulerian_vertex<InputGraph> EulerVertex;
        typedef typename EulerVertex::edge_list PathEdges;
        typedef ::boost::intrusive::list<
                    EulerVertex
                  , ::boost::intrusive::member_hook<
                        EulerVertex
                      , ::boost::intrusive::list_member_hook<>
                      , &EulerVertex::hook
                    >
                >
                VertexRefs;

        typename vertex_property_map_gen<
            InputGraph
          , EulerVertex
        >::type euler_map(graph);
        VertexRefs path_vertices;
        typename VertexRefs::iterator path_vertex_itr;
        typename graph_traits<InputGraph>::vertex_iterator vi, vi_end;

        for (::std::tr1::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi)
        {
            EulerVertex& e_u = get(euler_map, *vi);

            e_u.vertex = *vi;
            call_visitors<on_initialize_vertex>(visitors, *vi, graph);

            if (*vi == start)
            {
                path_vertex_itr = path_vertices.insert(
                    path_vertices.end()
                  , e_u
                );
            }

            typename graph_traits<InputGraph>::out_edge_iterator ei, ei_end;

            for (
                ::std::tr1::tie(ei, ei_end) = out_edges(*vi, graph);
                ei != ei_end;
                ++ei
            )
            {
                EulerEdge e_edge;
                EulerVertex& e_v = get(euler_map, target(*ei, graph));

                e_edge.edge = *ei;
                e_edge.source = &e_u;
                e_edge.target = &e_v;
                e_u.edges.push_back(e_edge);
            }
        }

        call_visitors<on_start_vertex>(visitors, start, graph);

        PathEdges path_edges;
        typename PathEdges::iterator path_edge_itr = path_edges.insert(
            path_edges.end()
          , path_vertex_itr->edges.front()
        );

        call_visitors<on_examine_edge>(
            visitors
          , path_edge_itr->edge
          , graph
        );
        path_vertex_itr->in_edge_itr = path_edges.begin();
        path_vertex_itr->edges.pop_front();

        if (path_vertex_itr->edges.empty())
        {
            call_visitors<on_finish_vertex>(
                visitors
              , path_vertex_itr->vertex
              , graph
            );
            path_vertex_itr = path_vertices.erase(path_vertex_itr);
        }

        path_vertex_itr = path_vertices.insert(
            path_vertex_itr
          , *path_edge_itr->target
        );
        path_vertex_itr->in_edge_itr = path_edge_itr;

        for (;;)
        {
            if (path_vertex_itr->edges.empty())
            {
                call_visitors<on_finish_vertex>(
                    visitors
                  , path_vertex_itr->vertex
                  , graph
                );
                path_vertices.erase(path_vertex_itr);

                if (path_vertices.empty())
                {
                    break;
                }
                else
                {
                    path_vertex_itr = path_vertices.begin();
                    path_edge_itr = path_vertex_itr->in_edge_itr;
                    call_visitors<on_start_vertex>(
                        visitors
                      , path_vertex_itr->vertex
                      , graph
                    );
                    continue;
                }
            }

            path_edge_itr = path_edges.insert(
                path_vertex_itr->in_edge_itr
              , path_vertex_itr->edges.front()
            );
            call_visitors<on_examine_edge>(
                visitors
              , path_edge_itr->edge
              , graph
            );
            path_vertex_itr->edges.pop_front();

            if (path_vertex_itr->edges.empty())
            {
                path_vertex_itr = path_vertices.erase(path_vertex_itr);
            }

            EulerVertex& e_v = *path_edge_itr->target;

            if (e_v.hook.is_linked())
            {
                path_vertex_itr = path_vertices.iterator_to(e_v);
            }
            else
            {
                path_vertex_itr = path_vertices.insert(path_vertex_itr, e_v);
            }

            path_vertex_itr->in_edge_itr = path_edge_itr;
        }

        for (
            typename PathEdges::reverse_iterator r_itr = path_edges.rbegin();
            r_itr != path_edges.rend();
            ++r_itr
        )
        {
            *output_edges = r_itr->edge;
            ++output_edges;
        }
    }
}}  // namespace boost::detail

#endif  // BOOST_GRAPH_DETAIL_FIND_EULERIAN_PATH_HPP

