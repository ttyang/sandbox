// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_LOOP_ERASED_RANDOM_TREE_HPP
#define BOOST_GRAPH_DETAIL_LOOP_ERASED_RANDOM_TREE_HPP

#include <vector>
#include <utility>
#include <iterator>
#include <algorithm>
#include <boost/tr1/tuple.hpp>
#include <boost/tr1/random.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/concept_check.hpp>
#include <boost/parameter.hpp>
#include <boost/ref.hpp>
#include <boost/function.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/call_visitors.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/keywords/rng_engine.hpp>
//#include <boost/graph/adjacency_list.hpp> must be included before this file.
#include <boost/detail/metafunction/data_type.hpp>

namespace boost {

    struct on_loop_erased_vertex
    {
    };

  namespace detail {

    template <
        typename EdgeIterator
      , typename ArgumentPack
      , typename HasEdgeWeights
    >
    ::std::size_t
        loop_erased_random_tree_edge_idx(
            EdgeIterator edge_itr
          , EdgeIterator edge_end
          , ArgumentPack const& args
          , HasEdgeWeights
        )
    {
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        ArgumentPack
                      , ::boost::graph::keywords::tag::weight_map
                    >::type
                >::type
                EdgeWeightMap;
        typedef typename property_traits<EdgeWeightMap>::value_type
                EdgeWeight;

        ::std::vector<EdgeWeight> weights;
        EdgeWeightMap const weight_map = args[
            ::boost::graph::keywords::_weight_map
        ];
        function2<EdgeWeight,EdgeWeight,EdgeWeight> combine = args[
            ::boost::graph::keywords::_distance_combine
        ];

        for (
            EdgeWeight weight = initialized_value;
            edge_itr != edge_end;
            ++edge_itr
        )
        {
            weights.push_back(
                weight = combine(weight, get(weight_map, *edge_itr))
            );
        }

        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        ArgumentPack
                      , ::boost::graph::keywords::tag::rng_engine
                    >::type
                >::type
                RNGEngine;
        typedef ::std::tr1::uniform_real<EdgeWeight>
                Distribution;

        ::std::tr1::variate_generator<RNGEngine&,Distribution> rng(
            ::boost::unwrap_ref(args[::boost::graph::keywords::_rng_engine])
          , Distribution(value_initialized<EdgeWeight>(), weights.back())
        );
        function2<bool,EdgeWeight,EdgeWeight> compare = args[
            ::boost::graph::keywords::_distance_compare
        ];

        return std::distance(
            weights.begin()
          , ::std::lower_bound(weights.begin(), weights.end(), rng(), compare)
        );
    }

    template <
        typename EdgeIterator
      , typename ArgumentPack
    >
    ::std::size_t
        loop_erased_random_tree_edge_idx(
            EdgeIterator edge_begin
          , EdgeIterator edge_end
          , ArgumentPack const& args
          , ::boost::mpl::false_
        )
    {
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        ArgumentPack
                      , ::boost::graph::keywords::tag::rng_engine
                    >::type
                >::type
                RNGEngine;
        typedef ::std::tr1::uniform_int< ::std::size_t>
                Distribution;

        return ::std::tr1::variate_generator<RNGEngine&,Distribution>(
            ::boost::unwrap_ref(args[::boost::graph::keywords::_rng_engine])
          , Distribution(0, ::std::distance(edge_begin, edge_end) - 1)
        )();
    }

    // The general-purpose RandomSuccessor() implementation;
    // also the undirected-graph RandomPredecessor() implementation.
    template <
        typename Graph
      , typename ArgumentPack
      , typename HasEdgeWeights
      , typename DirectionalCategory
      , typename IsLookingForSuccessor
    >
    ::std::pair<
        typename graph_traits<Graph>::vertex_descriptor
      , typename graph_traits<Graph>::edge_descriptor
    >
        loop_erased_random_tree_vertex_edge(
            typename graph_traits<Graph>::vertex_descriptor const vertex
          , Graph const& g
          , ArgumentPack const& args
          , HasEdgeWeights has_ew
          , DirectionalCategory
          , IsLookingForSuccessor
        )
    {
        typedef graph_traits<Graph>                     GraphTraits;
        typedef typename GraphTraits::vertex_descriptor Vertex;
        typedef typename GraphTraits::edge_descriptor   Edge;
        typedef ::std::pair<Vertex,Edge>                Result;

        // In an undirected graph, there is no functional difference
        // between the in-edges and the out-edges of a vertex.
        typename GraphTraits::out_edge_iterator ei, ei_end;

        ::std::tr1::tie(ei, ei_end) = out_edges(vertex, g);

        if (ei == ei_end)
        {
            return Result(GraphTraits::null_vertex(), Edge());
        }

        ::std::advance(
            ei
          , loop_erased_random_tree_edge_idx(ei, ei_end, args, has_ew)
        );

        // However, if the graph is undirected and we are looking for
        // predecessors, then the correct way to obtain the source vertex of
        // an in-edge is to treat it as an out-edge and find its target.
        return Result(target(*ei, g), *ei);
    }

    // The bidirectional-graph RandomPredecessor() implementation.
    template <
        typename Graph
      , typename ArgumentPack
      , typename HasEdgeWeights
    >
    ::std::pair<
        typename graph_traits<Graph>::vertex_descriptor
      , typename graph_traits<Graph>::edge_descriptor
    >
        loop_erased_random_tree_vertex_edge(
            typename graph_traits<Graph>::vertex_descriptor const vertex
          , Graph const& g
          , ArgumentPack const& args
          , HasEdgeWeights has_ew
          , bidirectional_tag
          , ::boost::mpl::false_
        )
    {
        typedef graph_traits<Graph>                     GraphTraits;
        typedef typename GraphTraits::vertex_descriptor Vertex;
        typedef typename GraphTraits::edge_descriptor   Edge;
        typedef ::std::pair<Vertex,Edge>                Result;

        typename GraphTraits::in_edge_iterator ei, ei_end;

        ::std::tr1::tie(ei, ei_end) = in_edges(vertex, g);

        if (ei == ei_end)
        {
            return Result(GraphTraits::null_vertex(), Edge());
        }

        ::std::advance(
            ei
          , loop_erased_random_tree_edge_idx(ei, ei_end, args, has_ew)
        );
        return Result(source(*ei, g), *ei);
    }

    // The directed-graph RandomPredecessor() implementation.
    template <
        typename Graph
      , typename ArgumentPack
      , typename HasEdgeWeights
    >
    ::std::pair<
        typename graph_traits<Graph>::vertex_descriptor
      , typename graph_traits<Graph>::edge_descriptor
    >
        loop_erased_random_tree_vertex_edge(
            typename graph_traits<Graph>::vertex_descriptor const vertex
          , Graph const& g
          , ArgumentPack const& args
          , HasEdgeWeights has_ew
          , directed_tag
          , ::boost::mpl::false_
        )
    {
        typedef graph_traits<Graph>                     GraphTraits;
        typedef typename GraphTraits::vertex_descriptor Vertex;
        typedef typename GraphTraits::edge_descriptor   Edge;
        typedef ::std::pair<Vertex,Edge>                Result;

        ::std::vector<Edge>                     edges;
        typename GraphTraits::vertex_iterator   vi, vi_end;
        typename GraphTraits::out_edge_iterator ei, ei_end;

        for (::std::tr1::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        {
            if (*vi != vertex)
            {
                for (
                    ::std::tr1::tie(ei, ei_end) = out_edges(*vi, g);
                    ei != ei_end;
                    ++ei
                )
                {
                    if (vertex == target(*ei, g))
                    {
                        edges.push_back(*ei);
                    }
                }
            }
        }

        if (edges.empty())
        {
            return Result(GraphTraits::null_vertex(), Edge());
        }

        typename ::std::vector<Edge>::iterator itr = edges.begin();
        typename ::std::vector<Edge>::iterator itr_end = edges.end();

        ::std::advance(
            itr
          , loop_erased_random_tree_edge_idx(itr, itr_end, args, has_ew)
        );
        return Result(source(*itr, g), *itr);
    }

    // Initializes the vertices and the specified property maps.
    template <
        typename Graph
      , typename OutputPredecessorMap
      , typename VertexColorMap
      , typename Vis
    >
    void
        loop_erased_random_tree_init(
            Graph const& g
          , OutputPredecessorMap out_pred_map
          , VertexColorMap vertex_color_map
          , Vis visitors
        )
    {
        typename graph_traits<Graph>::vertex_iterator vi, vend;

        for (::std::tr1::tie(vi, vend) = vertices(g); vi != vend; ++vi)
        {
            call_visitors<on_initialize_vertex>(visitors, *vi, g);
            put(out_pred_map, *vi, *vi);
            put(
                vertex_color_map
              , *vi
              , color_traits<
                    typename property_traits<VertexColorMap>::value_type
                >::white()
            );
        }
    }

    // The RandomTree() implementation.
    template <
        typename Graph
      , typename OutputPredecessorMap
      , typename VertexColorMap
      , typename Vis
      , typename TerminatorFunction
      , typename ArgumentPack
      , typename HasEdgeWeights
      , typename IsLookingForSuccessor
    >
    bool
        loop_erased_random_tree_impl(
            Graph const& g
          , OutputPredecessorMap out_pred_map
          , VertexColorMap vertex_color_map
          , Vis visitors
          , TerminatorFunction function
          , ArgumentPack const& args
          , HasEdgeWeights has_ew
          , IsLookingForSuccessor is_lfs
        )
    {
        typedef graph_traits<Graph>
                GraphTraits;
        typedef typename GraphTraits::vertex_descriptor
                Vertex;
        BOOST_CONCEPT_ASSERT((
            ReadWritePropertyMapConcept<OutputPredecessorMap,Vertex>
        ));
        typedef color_traits<
                    typename property_traits<VertexColorMap>::value_type
                >
                VertexColor;
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        ArgumentPack
                      , ::boost::graph::keywords::tag::rng_engine
                    >::type
                >::type
                RNGEngine;
        typedef ::std::tr1::uniform_real<>
                Distribution;
        typedef typename ::boost::unwrap_reference<TerminatorFunction>::type
                TF;

        ::std::tr1::variate_generator<RNGEngine&,Distribution> chance(
            ::boost::unwrap_ref(args[::boost::graph::keywords::_rng_engine])
          , Distribution(0.0, 1.0)
        );

        // This line is mainly for Borland compilers.
        TF& should_terminate = static_cast<TF&>(function);

        Vertex                                u, v, w;
        typename GraphTraits::vertex_iterator vi, vend;
        typename GraphTraits::edge_descriptor e;
        ::std::size_t                         root_count, dead_end_count;

        for (double epsilon = 0.5;;)
        {
            loop_erased_random_tree_init(
                g
              , out_pred_map
              , vertex_color_map
              , visitors
            );
            root_count = dead_end_count = 0;

            for (::std::tr1::tie(vi, vend) = vertices(g); vi != vend; ++vi)
            {
                v = *vi;

                while (get(vertex_color_map, v) != VertexColor::black())
                {
                    if (get(vertex_color_map, v) == VertexColor::white())
                    {
                        call_visitors<on_discover_vertex>(visitors, v, g);
                    }

                    put(vertex_color_map, v, VertexColor::gray());
                    call_visitors<on_examine_vertex>(visitors, v, g);

                    if (!dead_end_count && (chance() < epsilon))
                    {
                        ++root_count;
                        break;
                    }

                    ::std::tr1::tie(
                        u
                      , e
                    ) = loop_erased_random_tree_vertex_edge(
                        v
                      , g
                      , args
                      , has_ew
                      , typename GraphTraits::directed_category()
                      , is_lfs
                    );

                    if (u == GraphTraits::null_vertex())
                    {
                        if (++dead_end_count < 2)
                        {
                            ++root_count;
                        }
                        else
                        {
                            return false;
                        }

                        break;
                    }
                    else if (should_terminate(u, g))
                    {
                        // MAINTAINER:
                        // Find out if terminal vertices should be treated
                        // the same way as the null vertex.
                        if (++dead_end_count < 2)
                        {
                            ++root_count;
                        }
                        else
                        {
                            return false;
                        }

                        break;
                    }

                    call_visitors<on_examine_edge>(visitors, e, g);

                    if (get(vertex_color_map, u) == VertexColor::gray())
                    {
                        call_visitors<on_back_edge>(visitors, e, g);
                        put(out_pred_map, v, u);

                        // Erase the previous loop from the output.
                        for (w = get(out_pred_map, u); w != u; w = v)
                        {
                            v = get(out_pred_map, w);
                            put(out_pred_map, w, w);
                            put(vertex_color_map, w, VertexColor::red());
                            call_visitors<
                                on_loop_erased_vertex
                            >(visitors, w, g);
                        }

                        put(out_pred_map, v, v);
                        put(vertex_color_map, v, VertexColor::red());
                        call_visitors<
                            on_loop_erased_vertex
                        >(visitors, v, g);
                    }
                    else
                    {
                        call_visitors<on_tree_edge>(visitors, e, g);
                        put(out_pred_map, v, u);
                        v = u;
                    }
                }

                for (
                    v = *vi;
                    get(vertex_color_map, v) != VertexColor::black();
                    v = get(out_pred_map, v)
                )
                {
                    put(vertex_color_map, v, VertexColor::black());
                    call_visitors<on_finish_vertex>(visitors, v, g);
                }
            }

            if (1 < root_count)
            {
                epsilon *= 0.5;
            }
            else
            {
                break;
            }
        }

        return true;
    }

    // Initializes the vertices and the specified property maps.
    // Visitors will start at and discover the root vertex.
    template <
        typename Graph
      , typename OutputPredecessorMap
      , typename VertexColorMap
      , typename Vis
    >
    void
        loop_erased_random_tree_init(
            Graph const& g
          , typename graph_traits<Graph>::vertex_descriptor const root
          , OutputPredecessorMap out_pred_map
          , VertexColorMap vertex_color_map
          , Vis visitors
        )
    {
        loop_erased_random_tree_init(
            g
          , out_pred_map
          , vertex_color_map
          , visitors
        );
        call_visitors<on_start_vertex>(visitors, root, g);
        call_visitors<on_discover_vertex>(visitors, root, g);
        put(
            vertex_color_map
          , root
          , color_traits<
                typename property_traits<VertexColorMap>::value_type
            >::black()
        );
    }

    // Searches for a random path from vertex to root.
    template <
        typename Graph
      , typename OutputPredecessorMap
      , typename VertexColorMap
      , typename Vis
      , typename TerminatorFunction
      , typename ArgumentPack
      , typename HasEdgeWeights
      , typename IsLookingForSuccessor
    >
    bool
        loop_erased_random_tree_path(
            Graph const& g
          , typename graph_traits<Graph>::vertex_descriptor const root
          , typename graph_traits<Graph>::vertex_descriptor vertex
          , OutputPredecessorMap out_pred_map
          , VertexColorMap vertex_color_map
          , Vis visitors
          , TerminatorFunction function
          , ArgumentPack const& args
          , HasEdgeWeights has_ew
          , IsLookingForSuccessor is_lfs
        )
    {
        typedef graph_traits<Graph>
                GraphTraits;
        typedef color_traits<
                    typename property_traits<VertexColorMap>::value_type
                >
                VertexColor;
        typedef typename ::boost::unwrap_reference<TerminatorFunction>::type
                TF;

        typename GraphTraits::vertex_descriptor u, v = vertex, w;
        typename GraphTraits::edge_descriptor   e;
        bool                                    result = true;

        // This line is mainly for Borland compilers.
        TF& should_terminate = static_cast<TF&>(function);

        do
        {
            if (get(vertex_color_map, v) == VertexColor::white())
            {
                call_visitors<on_discover_vertex>(visitors, v, g);
            }

            put(vertex_color_map, v, VertexColor::gray());
            call_visitors<on_examine_vertex>(visitors, v, g);

            ::std::tr1::tie(u, e) = loop_erased_random_tree_vertex_edge(
                v
              , g
              , args
              , has_ew
              , typename GraphTraits::directed_category()
              , is_lfs
            );

            if (u == GraphTraits::null_vertex())
            {
                result = false;
                break;
            }
            else if (should_terminate(u, g))
            {
                result = false;
                break;
            }

            call_visitors<on_examine_edge>(visitors, e, g);

            if (get(vertex_color_map, u) == VertexColor::gray())
            {
                call_visitors<on_back_edge>(visitors, e, g);
                put(out_pred_map, v, u);

                // Erase the previous loop from the output.
                for (w = get(out_pred_map, u); w != u; w = v)
                {
                    v = get(out_pred_map, w);
                    put(out_pred_map, w, w);
                    put(vertex_color_map, w, VertexColor::red());
                    call_visitors<on_loop_erased_vertex>(visitors, w, g);
                }

                put(out_pred_map, v, v);
                put(vertex_color_map, v, VertexColor::red());
                call_visitors<on_loop_erased_vertex>(visitors, v, g);
            }
            else
            {
                call_visitors<on_tree_edge>(visitors, e, g);
                put(out_pred_map, v, u);
                v = u;
            }
        }
        while (get(vertex_color_map, v) != VertexColor::black());

        for (
            v = vertex;
            get(vertex_color_map, v) != VertexColor::black();
            v = get(out_pred_map, v)
        )
        {
            put(vertex_color_map, v, VertexColor::black());
            call_visitors<on_finish_vertex>(visitors, v, g);
        }

        return result;
    }

    // The RandomTreeWithRoot() implementation.
    template <
        typename Graph
      , typename OutputPredecessorMap
      , typename VertexColorMap
      , typename Vis
      , typename TerminatorFunction
      , typename ArgumentPack
      , typename HasEdgeWeights
      , typename IsLookingForSuccessor
    >
    bool
        loop_erased_random_tree_impl(
            Graph const& g
          , typename graph_traits<Graph>::vertex_descriptor const root
          , OutputPredecessorMap out_pred_map
          , VertexColorMap vertex_color_map
          , Vis visitors
          , TerminatorFunction function
          , ArgumentPack const& args
          , HasEdgeWeights has_ew
          , IsLookingForSuccessor is_lfs
        )
    {
        BOOST_CONCEPT_ASSERT((
            ReadWritePropertyMapConcept<
                OutputPredecessorMap
              , typename graph_traits<Graph>::vertex_descriptor
            >
        ));
        typedef typename ::boost::unwrap_reference<TerminatorFunction>::type
                TF;

        loop_erased_random_tree_init(
            g
          , root
          , out_pred_map
          , vertex_color_map
          , visitors
        );

        bool is_tree = true, has_path;
        typename graph_traits<Graph>::vertex_iterator vi, vend;

        // This line is mainly for Borland compilers.
        TF& should_terminate = static_cast<TF&>(function);

        for (std::tr1::tie(vi, vend) = vertices(g); vi != vend; ++vi)
        {
            if (
                !(root == *vi)
             && !should_terminate(*vi, g)
             && !(
                    get(vertex_color_map, *vi)
                 == color_traits<
                        typename property_traits<VertexColorMap>::value_type
                    >::black()
                )
            )
            {
                has_path = loop_erased_random_tree_path(
                    g
                  , root
                  , *vi
                  , out_pred_map
                  , vertex_color_map
                  , visitors
                  , function
                  , args
                  , has_ew
                  , is_lfs
                );

                if (is_tree)
                {
                    is_tree = has_path;
                }
            }
        }

        call_visitors<on_finish_vertex>(visitors, root, g);
        return is_tree;
    }

    // Random-walk implementation.
    template <
        typename Graph
      , typename OutputPredecessorMap
      , typename VertexColorMap
      , typename Vis
      , typename TerminatorFunction
      , typename ArgumentPack
      , typename HasEdgeWeights
      , typename IsLookingForSuccessor
    >
    bool
        loop_erased_random_tree_impl(
            Graph const& g
          , typename graph_traits<Graph>::vertex_descriptor const src
          , typename graph_traits<Graph>::vertex_descriptor const tgt
          , OutputPredecessorMap out_pred_map
          , VertexColorMap vertex_color_map
          , Vis visitors
          , TerminatorFunction function
          , ArgumentPack const& args
          , HasEdgeWeights has_ew
          , IsLookingForSuccessor is_lfs
        )
    {
        BOOST_CONCEPT_ASSERT((
            ReadWritePropertyMapConcept<
                OutputPredecessorMap
              , typename graph_traits<Graph>::vertex_descriptor
            >
        ));

        loop_erased_random_tree_init(
            g
          , tgt
          , out_pred_map
          , vertex_color_map
          , visitors
        );

        bool result = loop_erased_random_tree_path(
            g
          , tgt
          , src
          , out_pred_map
          , vertex_color_map
          , visitors
          , function
          , args
          , has_ew
          , is_lfs
        );

        call_visitors<on_finish_vertex>(visitors, tgt, g);
        return result;
    }
  }  // namespace detail
}  // namespace boost

#endif  // BOOST_GRAPH_DETAIL_LOOP_ERASED_RANDOM_TREE_HPP

