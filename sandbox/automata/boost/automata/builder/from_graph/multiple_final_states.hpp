// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_BUILDER_FROM_GRAPH_MULTIPLE_FINAL_STATES_HPP_INCLUDED
#define BOOST_AUTOMATA_BUILDER_FROM_GRAPH_MULTIPLE_FINAL_STATES_HPP_INCLUDED

#include <algorithm>
#include <iterator>
#include <boost/mpl/void.hpp>
#include <boost/range.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/automata/keys/observer.hpp>

//[reference__multiple_final_states_builder_from_graph
namespace boost { namespace automata {

    template <typename Targets, unsigned long Uid = 0UL>
    class multiple_final_states_builder_from_graph
    {
     public:
        typedef single_final_state_key<Uid> key_type;

     private:
        Targets _targets;

     public:
        explicit multiple_final_states_builder_from_graph(
            Targets const& targets
        );

        template <
            typename Graph
          , typename VertexStateMap
          , typename EdgeInputMap = ::boost::mpl::void_
        >
        struct apply
        {
            class type
            {
                multiple_final_states_builder_from_graph _builder;
                VertexStateMap const& _vertex_state_map;

             public:
                type(
                    multiple_final_states_builder_from_graph const& builder
                  , Graph const& graph
                  , VertexStateMap const& vertex_state_map
                  , EdgeInputMap const& edge_input_map
                );

                type(
                    multiple_final_states_builder_from_graph const& builder
                  , Graph const& graph
                  , VertexStateMap const& vertex_state_map
                );

                template <typename States>
                void make_final_states(States& states) const;
            };
        };
    };

    template <typename Targets, unsigned long Uid>
    multiple_final_states_builder_from_graph<Targets,Uid>
      ::multiple_final_states_builder_from_graph(Targets const& targets)
      : _targets(targets)
    {
    }

    template <typename Targets, unsigned long Uid>
    template <typename Graph, typename VertexStateMap, typename EdgeInputMap>
    multiple_final_states_builder_from_graph<Targets,Uid>::apply<
        Graph
      , VertexStateMap
      , EdgeInputMap
    >::type::type(
        multiple_final_states_builder_from_graph const& builder
      , Graph const& graph
      , VertexStateMap const& vertex_state_map
      , EdgeInputMap const& edge_input_map
    ) : _builder(builder), _vertex_state_map(vertex_state_map)
    {
    }

    template <typename Targets, unsigned long Uid>
    template <typename Graph, typename VertexStateMap, typename EdgeInputMap>
    multiple_final_states_builder_from_graph<Targets,Uid>::apply<
        Graph
      , VertexStateMap
      , EdgeInputMap
    >::type::type(
        multiple_final_states_builder_from_graph const& builder
      , Graph const& graph
      , VertexStateMap const& vertex_state_map
    ) : _builder(builder), _vertex_state_map(vertex_state_map)
    {
    }

    template <typename Targets, unsigned long Uid>
    template <typename Graph, typename VertexStateMap, typename EdgeInputMap>
    template <typename States>
    void
        multiple_final_states_builder_from_graph<Targets,Uid>::apply<
            Graph
          , VertexStateMap
          , EdgeInputMap
        >::type::make_final_states(States& states) const
    {
        ::std::insert_iterator<States> inserter(states, begin(states));
        typename range_const_iterator<Targets>::type
            v_end = end(_builder._targets);

        for (
            typename range_const_iterator<Targets>::type
                v_i = begin(_builder._targets);
            v_i != v_end;
            ++v_i
        )
        {
            *inserter = get(_vertex_state_map, *v_i);
            ++inserter;
        }
    }
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_BUILDER_FROM_GRAPH_MULTIPLE_FINAL_STATES_HPP_INCLUDED

