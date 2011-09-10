// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_HPP
#define BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_HPP

#include <vector>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter/preprocessor.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/vertex_property_map_gen.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/detail/loop_erased_random_tree_params.hpp>
#include <boost/graph/keywords/input_graph.hpp>
#include <boost/graph/keywords/rng_engine.hpp>
#include <boost/graph/keywords/source_vertex.hpp>
#include <boost/graph/keywords/terminate_predicate.hpp>
#include <boost/graph/detail/loop_erased_random_tree.hpp>
#include <boost/graph/detail/null_vertex.hpp>
#include <boost/graph/detail/default_combine_function.hpp>
#include <boost/graph/detail/default_compare_predicate.hpp>
#include <boost/graph/detail/default_terminate_predicate.hpp>

#if BOOST_PP_LESS(10, BOOST_PARAMETER_MAX_ARITY)
#define BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_ALL_PARAMS
#elif BOOST_PP_LESS(4, BOOST_PARAMETER_MAX_ARITY)
#define BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_5_PARAMS
#endif

namespace boost { namespace detail {

    template <typename InputGraph, typename Params>
    inline bool
        loop_erased_random_weighted_tree_dispatch(
            InputGraph const& input_graph
          , Params const& params
        )
    {
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)
        typename graph_traits<InputGraph>::vertex_descriptor root = arg_pack[
            ::boost::graph::keywords::_root_vertex
        ];
        typename graph_traits<InputGraph>::vertex_descriptor src = arg_pack[
            ::boost::graph::keywords::_source_vertex
        ];

        if (root == graph_traits<InputGraph>::null_vertex())
        {
            if (src == graph_traits<InputGraph>::null_vertex())
            {
                return loop_erased_random_tree_impl(
                    input_graph
                  , arg_pack[::boost::graph::keywords::_predecessor_map]
                  , arg_pack[::boost::graph::keywords::_color_map]
                  , arg_pack[::boost::graph::keywords::_visitor]
                  , arg_pack[::boost::graph::keywords::_terminate_predicate]
                  , arg_pack
                  , ::boost::mpl::true_()
                  , ::boost::mpl::true_()
                );
            }
            else
            {
                return loop_erased_random_tree_impl(
                    input_graph
                  , src
                  , arg_pack[::boost::graph::keywords::_predecessor_map]
                  , arg_pack[::boost::graph::keywords::_color_map]
                  , arg_pack[::boost::graph::keywords::_visitor]
                  , arg_pack[::boost::graph::keywords::_terminate_predicate]
                  , arg_pack
                  , ::boost::mpl::true_()
                  , ::boost::mpl::false_()
                );
            }
        }
        else
        {
            if (src == graph_traits<InputGraph>::null_vertex())
            {
                return loop_erased_random_tree_impl(
                    input_graph
                  , root
                  , arg_pack[::boost::graph::keywords::_predecessor_map]
                  , arg_pack[::boost::graph::keywords::_color_map]
                  , arg_pack[::boost::graph::keywords::_visitor]
                  , arg_pack[::boost::graph::keywords::_terminate_predicate]
                  , arg_pack
                  , ::boost::mpl::false_()
                  , ::boost::mpl::true_()
                );
            }
            else
            {
                return loop_erased_random_tree_impl(
                    input_graph
                  , src
                  , root
                  , arg_pack[::boost::graph::keywords::_predecessor_map]
                  , arg_pack[::boost::graph::keywords::_color_map]
                  , arg_pack[::boost::graph::keywords::_visitor]
                  , arg_pack[::boost::graph::keywords::_terminate_predicate]
                  , arg_pack
                  , ::boost::mpl::true_()
                  , ::boost::mpl::true_()
                );
            }
        }
    }
}}  // namespace boost::detail

//[reference__loop_erased_random_weighted_tree__prototype_old
namespace boost {

    template <typename InputGraph, typename Params>
    bool
        loop_erased_random_weighted_tree(
            InputGraph const& input_graph
          , Params const& params
        );

    //<-
    template <typename InputGraph, typename Params>
    inline bool
        loop_erased_random_weighted_tree(
            InputGraph const& input_graph
          , Params const& params
        )
    {
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)
        typedef typename ::boost::detail::data_type<
                    typename ::boost::parameter::binding<
                        arg_pack_type
                      , ::boost::graph::keywords::tag::weight_map
                      , typename property_map<
                            InputGraph
                          , edge_weight_t
                        >::const_type
                    >::type
                >::type
                EdgeWeightMap;

        EdgeWeightMap weight_map = arg_pack[
            ::boost::graph::keywords::_weight_map
          | get(edge_weight, input_graph)
        ];

        return detail::loop_erased_random_weighted_tree_dispatch(
            input_graph
          , make_loop_erased_random_tree_params().rng_engine(
                arg_pack[::boost::graph::keywords::_rng_engine]
            ).source_vertex(
                arg_pack[
                    ::boost::graph::keywords::_source_vertex
                  | graph_traits<InputGraph>::null_vertex()
                ]
            ).terminate_predicate(
                arg_pack[
                    ::boost::graph::keywords::_terminate_predicate
                  | detail::default_terminate_predicate<InputGraph>()
                ]
            ).predecessor_map(
                arg_pack[::boost::graph::keywords::_predecessor_map]
            ).root_vertex(
                arg_pack[
                    ::boost::graph::keywords::_root_vertex
                  | graph_traits<InputGraph>::null_vertex()
                ]
            ).weight_map(
                weight_map
            ).color_map(
                arg_pack[
                    ::boost::graph::keywords::_color_map
                  | make_vertex_property_map(input_graph, white_color)
                ]
            ).visitor(
                arg_pack[::boost::graph::keywords::_visitor | null_visitor()]
            ).distance_compare(
                arg_pack[
                    ::boost::graph::keywords::_distance_compare
                  | detail::make_default_compare_predicate(weight_map)
                ]
            ).distance_combine(
                arg_pack[
                    ::boost::graph::keywords::_distance_combine
                  | detail::make_default_combine_function(weight_map)
                ]
            )
        );
    }
    //->
}  // namespace boost
//]

namespace boost {

#if defined(BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_ALL_PARAMS)
  namespace detail {

    BOOST_PARAMETER_FUNCTION(
        (bool)
      , loop_erased_random_weighted_tree_dispatch
      , ::boost::graph::keywords::tag
      , (required
            (input_graph, *)
            (in_out(rng_engine), *)
            (out(predecessor_map), *)
            (root_vertex, *)
            (source_vertex, *)
            (weight_map, *)
            (in_out(color_map), *)
            (visitor, *)
            (distance_compare, *)
            (distance_combine, *)
            (terminate_predicate, *)
        )
    )
    {
        if (root_vertex == null_vertex(input_graph))
        {
            if (source_vertex == null_vertex(input_graph))
            {
                return loop_erased_random_tree_impl(
                    input_graph
                  , predecessor_map
                  , color_map
                  , visitor
                  , terminate_predicate
                  , args
                  , ::boost::mpl::true_()
                  , ::boost::mpl::true_()
                );
            }
            else
            {
                return loop_erased_random_tree_impl(
                    input_graph
                  , source_vertex
                  , predecessor_map
                  , color_map
                  , visitor
                  , terminate_predicate
                  , args
                  , ::boost::mpl::true_()
                  , ::boost::mpl::false_()
                );
            }
        }
        else if (source_vertex == null_vertex(input_graph))
        {
            return loop_erased_random_tree_impl(
                input_graph
              , root_vertex
              , predecessor_map
              , color_map
              , visitor
              , terminate_predicate
              , args
              , ::boost::mpl::true_()
              , ::boost::mpl::true_()
            );
        }
        else
        {
            return loop_erased_random_tree_impl(
                input_graph
              , source_vertex
              , root_vertex
              , predecessor_map
              , color_map
              , visitor
              , terminate_predicate
              , args
              , ::boost::mpl::true_()
              , ::boost::mpl::true_()
            );
        }
    }
  }  // namespace detail

    BOOST_PARAMETER_FUNCTION(
        (bool)
      , loop_erased_random_weighted_tree
      , graph::keywords::tag
      , (required
            (input_graph, *)
            (in_out(rng_engine), *)
            (out(predecessor_map), *)
        )
        (optional
            (root_vertex
              , *
              , detail::null_vertex(input_graph)
            )
            (source_vertex
              , *
              , detail::null_vertex(input_graph)
            )
            (weight_map
              , *
              , get(edge_weight_t(), input_graph)
            )
            (in_out(color_map)
              , *
              , make_vertex_property_map(input_graph, white_color)
            )
            (visitor
              , *
              , null_visitor()
            )
            (distance_compare
              , *
              , detail::make_default_compare_predicate(weight_map)
            )
            (distance_combine
              , *
              , detail::make_default_combine_function(weight_map)
            )
            (terminate_predicate
              , *
              , detail::make_default_terminate_predicate(input_graph)
            )
        )
    )
    {
        return detail::loop_erased_random_weighted_tree_dispatch(
            input_graph
          , rng_engine
          , predecessor_map
          , root_vertex
          , source_vertex
          , weight_map
          , color_map
          , visitor
          , distance_compare
          , distance_combine
          , terminate_predicate
        );
    }
#elif defined(BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_5_PARAMS)
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , loop_erased_random_weighted_tree
      , ::boost::graph::keywords::tag
      , (required
            (input_graph, *)
            (in_out(rng_engine), *)
            (out(predecessor_map), *)
        )
        (optional
            (root_vertex
              , *
              , detail::null_vertex(input_graph)
            )
            (source_vertex
              , *
              , detail::null_vertex(input_graph)
            )
        )
    )
    {
        return loop_erased_random_weighted_tree(
            input_graph
          , make_loop_erased_random_tree_params().rng_engine(
                rng_engine
            ).source_vertex(
                source_vertex
            ).predecessor_map(
                predecessor_map
            ).root_vertex(
                root_vertex
            )
        );
    }
#endif  // BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_*_PARAMS
}  // namespace boost

#endif  // BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_HPP

