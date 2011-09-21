// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_BUILDER_FROM_GRAPH_SINGLE_FINAL_STATE_HPP_INCLUDED
#define BOOST_AUTOMATA_BUILDER_FROM_GRAPH_SINGLE_FINAL_STATE_HPP_INCLUDED

#include <boost/mpl/void.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/automata/keys/observer.hpp>

//[reference__single_final_state_builder_from_graph
namespace boost { namespace automata {

    template <typename Vertex, unsigned long Uid = 0UL>
    class single_final_state_builder_from_graph
    {
     public:
        typedef single_final_state_key<Uid> key_type;

     private:
        Vertex _target;

     public:
        explicit single_final_state_builder_from_graph(Vertex const& target);

        template <
            typename Graph
          , typename VertexStateMap
          , typename EdgeInputMap = ::boost::mpl::void_
        >
        struct apply
        {
            class type
            {
                typedef single_final_state_builder_from_graph<
                            typename ::boost::graph_traits<
                                Graph
                            >::vertex_descriptor
                        >
                        Builder;

                Builder _builder;
                VertexStateMap const& _vertex_state_map;

             public:
                type(
                    Builder const& builder
                  , Graph const& graph
                  , VertexStateMap const& vertex_state_map
                  , EdgeInputMap const& edge_input_map
                );

                type(
                    Builder const& builder
                  , Graph const& graph
                  , VertexStateMap const& vertex_state_map
                );

                typename property_traits<VertexStateMap>::value_type
                    get_final_state() const;
            };
        };
    };

    template <typename Vertex, unsigned long Uid>
    single_final_state_builder_from_graph<Vertex,Uid>
      ::single_final_state_builder_from_graph(Vertex const& target)
      : _target(target)
    {
    }

    template <typename Vertex, unsigned long Uid>
    template <typename Graph, typename VertexStateMap, typename EdgeInputMap>
    single_final_state_builder_from_graph<Vertex,Uid>::apply<
        Graph
      , VertexStateMap
      , EdgeInputMap
    >::type::type(
        Builder const& builder
      , Graph const& graph
      , VertexStateMap const& vertex_state_map
      , EdgeInputMap const& edge_input_map
    ) : _builder(builder), _vertex_state_map(vertex_state_map)
    {
    }

    template <typename Vertex, unsigned long Uid>
    template <typename Graph, typename VertexStateMap, typename EdgeInputMap>
    single_final_state_builder_from_graph<Vertex,Uid>::apply<
        Graph
      , VertexStateMap
      , EdgeInputMap
    >::type::type(
        Builder const& builder
      , Graph const& graph
      , VertexStateMap const& vertex_state_map
    ) : _builder(builder), _vertex_state_map(vertex_state_map)
    {
    }

    template <typename Vertex, unsigned long Uid>
    template <typename Graph, typename VertexStateMap, typename EdgeInputMap>
    inline typename property_traits<VertexStateMap>::value_type
        single_final_state_builder_from_graph<Vertex,Uid>::apply<
            Graph
          , VertexStateMap
          , EdgeInputMap
        >::type::get_final_state()
        const
    {
        return get(_vertex_state_map, _builder._target);
    }
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_BUILDER_FROM_GRAPH_SINGLE_FINAL_STATE_HPP_INCLUDED

