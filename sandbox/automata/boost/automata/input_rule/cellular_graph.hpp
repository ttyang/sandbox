// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_INPUT_RULE_CELLULAR_GRAPH_HPP_INCLUDED
#define BOOST_AUTOMATA_INPUT_RULE_CELLULAR_GRAPH_HPP_INCLUDED

#include <deque>
#include <utility>
#include <boost/tr1/tuple.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/vertex_property_map_gen.hpp>

//[reference__cellular_graph_input_rule
namespace boost { namespace automata {
  //<-
  namespace _detail {

    template <typename Map>
    class get_map_value
    {
        Map& _map;

     public:
        typedef typename property_traits<Map>::key_type argument_type;
        typedef typename property_traits<Map>::value_type& result_type;

        explicit get_map_value(Map& map);

        result_type operator()(argument_type const& arg) const;
    };

    template <typename Map>
    inline get_map_value<Map>::get_map_value(Map& map) : _map(map)
    {
    }

    template <typename Map>
    inline typename get_map_value<Map>::result_type
        get_map_value<Map>::operator()(argument_type const& arg) const
    {
        return get(_map, arg);
    }
  }  // namespace _detail
  //->

    template <typename Graph>
    class cellular_graph_input_rule
    {
        Graph const& _graph;

     public:
        typedef bool result_type;

        explicit cellular_graph_input_rule(Graph const& graph);

        template <typename CellMap>
        result_type operator()(CellMap& cell_map) const;
    };

    //<-
    template <typename Graph>
    cellular_graph_input_rule<Graph>::cellular_graph_input_rule(
        Graph const& graph
    ) : _graph(graph)
    {
    }

    template <typename Graph>
    template <typename CellMap>
    typename cellular_graph_input_rule<Graph>::result_type
        cellular_graph_input_rule<Graph>::operator()(CellMap& cell_map) const
    {
        typedef typename property_traits<CellMap>::value_type
                Cell;
        typedef typename ::boost::vertex_property_map_gen<
                    Graph
                  , typename Cell::state
                >::type
                StateMap;

        StateMap state_map(_graph);
        typename ::boost::graph_traits<Graph>::vertex_iterator v_itr, v_end;

        for (
            ::std::tr1::tie(v_itr, v_end) = boost::vertices(_graph);
            v_itr != v_end;
            ++v_itr
        )
        {
            put(state_map, *v_itr, get(cell_map, *v_itr).get_current_state());
        }

        _detail::get_map_value<StateMap> getter(state_map);
        typename ::boost::graph_traits<Graph>::adjacency_iterator a_itr, a_end;
        bool result = false;

        for (
            ::std::tr1::tie(v_itr, v_end) = ::boost::vertices(_graph);
            v_itr != v_end;
            ++v_itr
        )
        {
            ::std::tr1::tie(a_itr, a_end) = ::boost::adjacent_vertices(
                *v_itr
              , _graph
            );
            Cell& cell = get(cell_map, *v_itr);

            cell(
                ::std::make_pair(
                    make_transform_iterator(a_itr, getter)
                  , make_transform_iterator(a_end, getter)
                )
            );

            if (cell.get_current_state() != getter(*v_itr))
            {
                result = true;
            }
        }

        return result;
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_INPUT_RULE_CELLULAR_GRAPH_HPP_INCLUDED

