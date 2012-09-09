// Copyright (C) 2004-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_LOOP_ERASED_RANDOM_TREE_HPP
#define BOOST_GRAPH_LOOP_ERASED_RANDOM_TREE_HPP

#include <boost/config.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter/preprocessor.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/parameter.hpp>
#include <boost/ref.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/vertex_property_map_gen.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/keywords/input_graph.hpp>
#include <boost/graph/keywords/rng_engine.hpp>
#include <boost/graph/keywords/source_vertex.hpp>
#include <boost/graph/keywords/terminate_predicate.hpp>
#include <boost/graph/detail/loop_erased_random_tree_prm.hpp>
#include <boost/graph/detail/loop_erased_random_tree.hpp>
#include <boost/graph/detail/default_terminate_predicate.hpp>
#include <boost/detail/metafunction/data_type.hpp>

#if !defined BOOST_MSVC
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/graph/detail/metafunction/is_incidence_graph.hpp>
#include <boost/graph/detail/metafunction/is_vertex_list_graph.hpp>
#include <boost/graph/detail/metafunction/is_predecessor_map.hpp>
#include <boost/graph/detail/metafunction/is_vertex_property_map.hpp>
#include <boost/graph/detail/metafunction/is_vertex_descriptor.hpp>
#include <boost/detail/metafunction/has_event_filter.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/fusion/support/is_sequence.hpp>
#endif
#endif

namespace boost { namespace detail {

    template <typename InputGraph, typename Params>
    inline bool
        loop_erased_random_tree_dispatch(
            InputGraph const& input_graph
          , Params const& params
        )
    {
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)
        typedef typename ::boost::detail::metafunction::data_type<
                    typename ::boost::parameter::binding<
                        arg_pack_type
                      , ::boost::graph::keywords::tag::predecessor_map
                    >::type
                >::type
                OutputPredecessorMap;

        typename graph_traits<InputGraph>::vertex_descriptor root = arg_pack[
            ::boost::graph::keywords::_root_vertex
        ];
        typename graph_traits<InputGraph>::vertex_descriptor src = arg_pack[
            ::boost::graph::keywords::_source_vertex
        ];
        OutputPredecessorMap& out_pred_map = ::boost::unwrap_ref(
            arg_pack[::boost::graph::keywords::_predecessor_map]
        );

        if (root == graph_traits<InputGraph>::null_vertex())
        {
            if (src == graph_traits<InputGraph>::null_vertex())
            {
                return loop_erased_random_tree_impl(
                    input_graph
                  , out_pred_map
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
                  , out_pred_map
                  , arg_pack[::boost::graph::keywords::_color_map]
                  , arg_pack[::boost::graph::keywords::_visitor]
                  , arg_pack[::boost::graph::keywords::_terminate_predicate]
                  , arg_pack
                  , ::boost::mpl::false_()
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
                  , out_pred_map
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
                  , out_pred_map
                  , arg_pack[::boost::graph::keywords::_color_map]
                  , arg_pack[::boost::graph::keywords::_visitor]
                  , arg_pack[::boost::graph::keywords::_terminate_predicate]
                  , arg_pack
                  , ::boost::mpl::false_()
                  , ::boost::mpl::true_()
                );
            }
        }
    }
}}  // namespace boost::detail

//[reference__loop_erased_random_tree__prototype_old
namespace boost {

    template <typename InputGraph, typename Params>
    bool
        loop_erased_random_tree(
            InputGraph const& input_graph
          , Params const& params
        );

    //<-
    template <typename InputGraph, typename Params>
    inline bool
        loop_erased_random_tree(
            InputGraph const& input_graph
          , Params const& params
        )
    {
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)

        return detail::loop_erased_random_tree_dispatch(
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
            ).color_map(
                arg_pack[
                    ::boost::graph::keywords::_color_map
                  | make_vertex_property_map(input_graph, white_color)
                ]
            ).visitor(
                arg_pack[::boost::graph::keywords::_visitor | null_visitor()]
            )
        );
    }
    //->
}  // namespace boost
//]

#if BOOST_PP_LESS(7, BOOST_PARAMETER_MAX_ARITY)
namespace boost {

#if defined BOOST_MSVC
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , loop_erased_random_tree
      , ::boost::graph::keywords::tag
      , (required
            (input_graph
              , *
            )
            (in_out(rng_engine)
              , *
            )
            (out(predecessor_map)
              , *
            )
        )
        (optional
            (root_vertex
              , *
              , graph_traits<input_graph_type>::null_vertex()
            )
            (source_vertex
              , *
              , graph_traits<input_graph_type>::null_vertex()
            )
            (in_out(color_map)
              , *
              , make_vertex_property_map(input_graph, white_color)
            )
            (visitor
              , *
              , null_visitor()
            )
            (terminate_predicate
              , *
              , detail::default_terminate_predicate<input_graph_type>()
            )
        )
    )
#else  // Okay, we can impose type requirements.  Awesome.
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , loop_erased_random_tree
      , ::boost::graph::keywords::tag
      , (required
            (input_graph
              , *(
                    ::boost::mpl::and_<
                        detail::is_incidence_graph< ::boost::mpl::_>
                      , detail::is_vertex_list_graph< ::boost::mpl::_>
                    >
                )
            )
            (in_out(rng_engine)
              , *
            )
            (out(predecessor_map)
              , *(
                    ::boost::mpl::and_<
                        detail::is_vertex_property_map<
                            ::boost::mpl::_
                          , ::boost::graph::keywords::tag::input_graph::_
                        >
                      , detail::is_predecessor_map< ::boost::mpl::_>
                    >
                )
            )
        )
        (optional
            (root_vertex
              , *(
                    detail::is_vertex_descriptor<
                        ::boost::mpl::_
                      , ::boost::graph::keywords::tag::input_graph::_
                    >
                )
              , graph_traits<input_graph_type>::null_vertex()
            )
            (source_vertex
              , *(
                    detail::is_vertex_descriptor<
                        ::boost::mpl::_
                      , ::boost::graph::keywords::tag::input_graph::_
                    >
                )
              , graph_traits<input_graph_type>::null_vertex()
            )
        )
        (deduced  // Doesn't work yet.
            (optional
                (in_out(color_map)
                  , *(
                        ::boost::mpl::and_<
                            detail::is_vertex_property_map<
                                ::boost::mpl::_
                              , ::boost::graph::keywords::tag::input_graph::_
                            >
                          , ::boost::mpl::not_<
                                detail::is_predecessor_map< ::boost::mpl::_>
                            >
                        >
                    )
                  , make_vertex_property_map(input_graph, white_color)
                )
                (visitor
                  , *(
                        ::boost::detail::metafunction::has_event_filter<
                            ::boost::mpl::_
                        >
                    )
                  , null_visitor()
                )
            )
        )
        (optional
            (terminate_predicate
              , *
              , detail::default_terminate_predicate<input_graph_type>()
            )
        )
    )
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , loop_erased_random_tree
      , ::boost::graph::keywords::tag
      , (required
            (input_graph
              , *(
                    ::boost::mpl::and_<
                        detail::is_incidence_graph< ::boost::mpl::_>
                      , detail::is_vertex_list_graph< ::boost::mpl::_>
                    >
                )
            )
            (in_out(rng_engine)
              , *
            )
            (out(predecessor_map)
              , *(
                    ::boost::mpl::and_<
                        detail::is_vertex_property_map<
                            ::boost::mpl::_
                          , ::boost::graph::keywords::tag::input_graph::_
                        >
                      , detail::is_predecessor_map< ::boost::mpl::_>
                    >
                )
            )
        )
        (optional
            (root_vertex
              , *(
                    detail::is_vertex_descriptor<
                        ::boost::mpl::_
                      , ::boost::graph::keywords::tag::input_graph::_
                    >
                )
              , graph_traits<input_graph_type>::null_vertex()
            )
            (source_vertex
              , *(
                    detail::is_vertex_descriptor<
                        ::boost::mpl::_
                      , ::boost::graph::keywords::tag::input_graph::_
                    >
                )
              , graph_traits<input_graph_type>::null_vertex()
            )
        )
        (deduced  // Doesn't work yet.
            (optional
                (in_out(color_map)
                  , *(
                        ::boost::mpl::and_<
                            detail::is_vertex_property_map<
                                ::boost::mpl::_
                              , ::boost::graph::keywords::tag::input_graph::_
                            >
                          , ::boost::mpl::not_<
                                detail::is_predecessor_map< ::boost::mpl::_>
                            >
                        >
                    )
                  , make_vertex_property_map(input_graph, white_color)
                )
                (visitor
                  , *(
                        ::boost::mpl::or_<
                            ::boost::fusion::traits::is_sequence<
                                ::boost::mpl::_
                            >
                          , ::boost::detail::metafunction::has_event_filter<
                                ::boost::mpl::_
                            >
                        >
                    )
                  , null_visitor()
                )
            )
        )
        (optional
            (terminate_predicate
              , *
              , detail::default_terminate_predicate<input_graph_type>()
            )
        )
    )
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#endif  // BOOST_MSVC
    {
        if (root_vertex == graph_traits<input_graph_type>::null_vertex())
        {
            if (source_vertex == graph_traits<input_graph_type>::null_vertex())
            {
                return detail::loop_erased_random_tree_impl(
                    input_graph
                  , predecessor_map
                  , color_map
                  , visitor
                  , terminate_predicate
                  , args
                  , ::boost::mpl::false_()
                  , ::boost::mpl::true_()
                );
            }
            else
            {
                return detail::loop_erased_random_tree_impl(
                    input_graph
                  , source_vertex
                  , predecessor_map
                  , color_map
                  , visitor
                  , terminate_predicate
                  , args
                  , ::boost::mpl::false_()
                  , ::boost::mpl::false_()
                );
            }
        }
        else if (
            source_vertex == graph_traits<input_graph_type>::null_vertex()
        )
        {
            return detail::loop_erased_random_tree_impl(
                input_graph
              , root_vertex
              , predecessor_map
              , color_map
              , visitor
              , terminate_predicate
              , args
              , ::boost::mpl::false_()
              , ::boost::mpl::true_()
            );
        }
        else
        {
            return detail::loop_erased_random_tree_impl(
                input_graph
              , source_vertex
              , root_vertex
              , predecessor_map
              , color_map
              , visitor
              , terminate_predicate
              , args
              , ::boost::mpl::false_()
              , ::boost::mpl::true_()
            );
        }
    }
}  // namespace boost
#endif  // 7 < BOOST_PARAMETER_MAX_ARITY

#endif  // BOOST_GRAPH_LOOP_ERASED_RANDOM_TREE_HPP

