// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_PARAMETER_MAX_ARITY 11

#include <iostream>
#include <boost/tr1/tuple.hpp>
#include <boost/array.hpp>
#include <boost/gil/utilities.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/vertex_property_map_gen.hpp>
#include <boost/graph/basic_vert_insert_iterator.hpp>
#include <boost/graph/basic_add_edge_function.hpp>
#include <boost/graph/set_orthogonal_grid_layout.hpp>
#include <boost/automata/generator/deterministic.hpp>
#include <boost/automata/transition_function/totalistic_boolean_cell.hpp>
#include <boost/automata/transition_function/input_rule.hpp>
#include <boost/automata/input_rule/cellular_graph.hpp>
#include <boost/automata/policy/moore_output.hpp>
#include <boost/automata/automaton.hpp>

//[example__game_of_life__cell_function
typedef boost::automata::totalistic_boolean_cell_transition_function<>
        CellFunction;

void build_function(CellFunction& function)
{
    function |= 3;
    function &= 2, 3;
}
//]

//[example__game_of_life__more_typedefs
typedef boost::adjacency_list<boost::multisetS,boost::listS,boost::undirectedS>
        Graph;
typedef boost::automata::automaton<
            boost::automata::deterministic_generator
          , CellFunction
        >
        Cell;
typedef boost::vertex_property_map_gen<Graph,Cell>::type
        CellMap;
//]

//[example__game_of_life__program
class life_program
{
    static const std::size_t dim_size = 5;

    Graph graph;
    boost::automata::cellular_graph_input_rule<Graph> rule;

    life_program() : graph(), rule(graph)
    {
        boost::array<bool,2> wraparound_policy = {{true, true}};

        boost::set_orthogonal_grid_layout(
            boost::basic_vertex_inserter(graph)
          , boost::basic_2way_edge_adder(graph)
          , boost::gil::point2<int>(dim_size, dim_size)
          , boost::graph::keywords::_is_zeta = true
          , boost::graph::keywords::_wraparound_policy = wraparound_policy
        );
    }

    life_program(life_program const& copy);
    life_program& operator=(life_program const& copy);
    ~life_program() {}

 public:
    static life_program const& get_instance()
    {
        static life_program instance;
        return instance;
    }
    //]

    //[example__game_of_life__build_cells
    void build_cells(CellMap& cell_map) const
    {
        boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
        int i = 0;

        for (
            std::tr1::tie(vi, vi_end) = boost::vertices(graph);
            vi != vi_end;
            ++vi
        )
        {
            boost::put(
                cell_map
              , *vi
              , Cell(
                    build_function
                  , (
                        (i == 0)
                     || (i == dim_size + 1)
                     || (i == dim_size + 2)
                     || (i == dim_size * 2)
                     || (i == dim_size * 2 + 1)
                    )
                )
            );
            ++i;
        }
    }

    struct cell_builder
    {
        typedef CellMap argument_type;
        typedef void result_type;

        result_type operator()(argument_type& cell_map) const
        {
            life_program::get_instance().build_cells(cell_map);
        }
    };
    //]

    //[example__game_of_life__output
 private:
    void output(CellMap const& cell_map) const
    {
        boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
        std::tr1::tie(vi, vi_end) = boost::vertices(graph);
        std::cout << std::endl;

        for (std::size_t y = 0; y < dim_size; ++y)
        {
            for (std::size_t x = 0; x < dim_size; ++x)
            {
                std::cout << (
                    boost::get(cell_map, *vi).get_current_state() ? '1' : '0'
                );
                ++vi;
            }

            std::cout << std::endl;
        }
    }

    struct output_cells
    {
        template <typename SubjectAutomaton>
        void operator()(SubjectAutomaton const& automaton) const
        {
            life_program::get_instance().output(automaton.get_current_state());
        }
    };
    //]

    //[example__game_of_life__run
 public:
    void run() const
    {
        CellMap start(graph);
        boost::automata::automaton<
            boost::automata::deterministic_generator
          , boost::automata::input_rule_transition_function<CellMap,true>
          , boost::fusion::cons<
                boost::automata::moore_output_policy<output_cells>
            >
        > game_of_life(cell_builder(), start);
        std::size_t iteration_count = dim_size * 4;

        for (std::size_t i = 0; i < iteration_count; ++i)
        {
            game_of_life(rule);
        }
    }
};

int main()
{
    life_program::get_instance().run();
    return 0;
}
//]

