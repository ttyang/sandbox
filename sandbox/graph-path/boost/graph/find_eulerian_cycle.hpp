// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_FIND_EULERIAN_CYCLE_HPP
#define BOOST_GRAPH_FIND_EULERIAN_CYCLE_HPP

#include <boost/config.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/parameter/preprocessor.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/keywords/input_graph.hpp>
#include <boost/graph/keywords/result.hpp>
#include <boost/graph/detail/find_eulerian_path.hpp>
#include <boost/graph/has_eulerian_cycle.hpp>
#include <boost/assert.hpp>

#if !defined BOOST_MSVC
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/graph/detail/metafunction/is_incidence_graph.hpp>
#include <boost/graph/detail/metafunction/is_vertex_list_graph.hpp>
#include <boost/graph/detail/metafunction/is_vertex_descriptor.hpp>
#include <boost/detail/metafunction/is_output_iterator.hpp>
#include <boost/detail/metafunction/has_event_filter.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/pair.hpp>
#endif
#endif

namespace boost { namespace detail {

    template <typename InputGraph, typename OutputIterator, typename Params>
    inline bool
        find_eulerian_cycle_dispatch(
            InputGraph const& input_graph
          , OutputIterator result
          , Params const& params
        )
    {
        BOOST_ASSERT(has_eulerian_cycle(input_graph));

        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)

        find_eulerian_path_impl(
            input_graph
          , result
          , arg_pack[::boost::graph::keywords::_root_vertex]
          , arg_pack[::boost::graph::keywords::_visitor]
          , typename graph_traits<InputGraph>::directed_category()
        );
        return true;
    }
}}  // namespace boost::detail

//[reference__find_eulerian_cycle
namespace boost {

    template <
        typename InputGraph
      , typename OutputIterator
      , typename P
      , typename T
      , typename R
    >
    bool
        find_eulerian_cycle(
            InputGraph const& input_graph
          , OutputIterator result
          , bgl_named_params<P,T,R> const& params
        );

    //<-
    template <
        typename InputGraph
      , typename OutputIterator
      , typename P
      , typename T
      , typename R
    >
    inline bool
        find_eulerian_cycle(
            InputGraph const& input_graph
          , OutputIterator result
          , bgl_named_params<P,T,R> const& params
        )
    {
        typedef bgl_named_params<P,T,R> Params;
        BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(Params, params)

        return detail::find_eulerian_cycle_dispatch(
            input_graph
          , result
          , ::boost::root_vertex(
                arg_pack[
                    ::boost::graph::keywords::_root_vertex
                  | *vertices(input_graph).first
                ]
            ).visitor(
                arg_pack[
                    ::boost::graph::keywords::_visitor
                  | null_visitor()
                ]
            )
        );
    }
    //->
}  // namespace boost
//]

#if BOOST_PP_LESS(3, BOOST_PARAMETER_MAX_ARITY)
namespace boost {

#if defined BOOST_MSVC
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , find_eulerian_cycle
      , ::boost::graph::keywords::tag
      , (required
            (input_graph
              , *
            )
            (out(result)
              , *
            )
        )
        (optional
            (root_vertex
              , *
              , (*(vertices(input_graph).first))
            )
            (visitor
              , *
              , null_visitor()
            )
        )
    )
#else  // Okay, we can impose type requirements.  Awesome.
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , find_eulerian_cycle
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
            (out(result)
              , *(
                    ::boost::detail::metafunction::is_output_iterator<
                        ::boost::mpl::_
                    >
                )
            )
        )
        (deduced
            (optional
                (root_vertex
                  , *(
                        detail::is_vertex_descriptor<
                            ::boost::mpl::_
                          , ::boost::graph::keywords::tag::input_graph::_
                        >
                    )
                  , (*(vertices(input_graph).first))
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
    )
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_PARAMETER_FUNCTION(
        (bool)
      , find_eulerian_cycle
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
            (out(result)
              , *(
                    ::boost::detail::metafunction::is_output_iterator<
                        ::boost::mpl::_
                    >
                )
            )
        )
        (deduced
            (optional
                (root_vertex
                  , *(
                        detail::is_vertex_descriptor<
                            ::boost::mpl::_
                          , ::boost::graph::keywords::tag::input_graph::_
                        >
                    )
                  , (*(vertices(input_graph).first))
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
    )
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#endif  // BOOST_MSVC
    {
        return detail::find_eulerian_cycle_dispatch(
            input_graph
          , result
          , ::boost::root_vertex(root_vertex).visitor(visitor)
        );
    }
}  // namespace boost
#endif  // 3 < BOOST_PARAMETER_MAX_ARITY

#endif  // BOOST_GRAPH_FIND_EULERIAN_CYCLE_HPP

