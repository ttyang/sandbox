// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_BASIC_ADD_EDGE_FUNCTION_HPP
#define BOOST_GRAPH_BASIC_ADD_EDGE_FUNCTION_HPP

#include <boost/tr1/type_traits.hpp>
#include <boost/graph/graph_traits.hpp>

//[reference__basic_add_edge_function__definition
namespace boost {

    template <typename Graph, bool Is2Way>
    class basic_add_edge_function
    {
        //<-
        Graph& _graph;
        //->

     public:
        explicit basic_add_edge_function(Graph& graph);

        void
            operator()(
                typename graph_traits<Graph>::vertex_descriptor u
              , typename graph_traits<Graph>::vertex_descriptor v
            );
    };

    //<-
    template <typename Graph, bool Is2Way>
    basic_add_edge_function<Graph,Is2Way>::basic_add_edge_function(
        Graph& graph
    ) : _graph(graph)
    {
    }

    template <typename Graph, bool Is2Way>
    inline void
        basic_add_edge_function<Graph,Is2Way>::operator()(
            typename graph_traits<Graph>::vertex_descriptor u
          , typename graph_traits<Graph>::vertex_descriptor v
        )
    {
        add_edge(u, v, _graph);

        if (
            Is2Way && ::std::tr1::is_base_of<
                directed_tag
              , typename graph_traits<Graph>::directed_category
            >::value
        )
        {
            add_edge(v, u, _graph);
        }
    }
    //->
}  // namespace boost
//]

//[reference__basic_2way_edge_adder__prototype
namespace boost {

    template <typename Graph>
    basic_add_edge_function<Graph,true> basic_2way_edge_adder(Graph& graph);

    //<-
    template <typename Graph>
    inline basic_add_edge_function<Graph,true>
        basic_2way_edge_adder(Graph& graph)
    {
        return basic_add_edge_function<Graph,true>(graph);
    }
    //->
}  // namespace boost
//]

//[reference__basic_edge_adder__prototype
namespace boost {

    template <typename Graph>
    basic_add_edge_function<Graph,false> basic_edge_adder(Graph& graph);

    //<-
    template <typename Graph>
    inline basic_add_edge_function<Graph,false> basic_edge_adder(Graph& graph)
    {
        return basic_add_edge_function<Graph,false>(graph);
    }
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_BASIC_ADD_EDGE_FUNCTION_HPP

