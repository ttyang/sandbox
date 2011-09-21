// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/fusion/container/list.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/automata/generator/dfa.hpp>
#include <boost/automata/transition_function/next_state.hpp>
#include <boost/automata/builder/from_graph/single_final_state.hpp>
#include <boost/automata/builder/from_graph.hpp>
#include <boost/automata/policy/single_final_state.hpp>
#include <boost/automata/policy/bool_insertion.hpp>
#include <boost/automata/policy/dfa_insertion.hpp>
#include <boost/automata/policy/input_validation.hpp>
#include <boost/automata/automaton.hpp>
#include "maze.hpp"

//[example__maze__make
using namespace boost;
using namespace automata;
using namespace keyword;

int main()
{
    typedef adjacency_list<vecS,vecS,undirectedS> Graph;

    Graph g;

    make_maze(g);
    //]

    //[example__maze__builder_type
    typedef single_final_state_builder_from_graph<
                graph_traits<Graph>::vertex_descriptor
            >
            SingleFinalStateBuilder;
    typedef fusion::list<SingleFinalStateBuilder>
            BuilderPolicies;
    typedef builder_from_graph<
                Graph
              , property_map<Graph,vertex_index_t>::type
              , _Policies<BuilderPolicies>
            >
            Builder;
    //]

    //[example__maze__builder
    Builder
        builder(
            g
          , get(vertex_index, g)
          , BuilderPolicies(SingleFinalStateBuilder(vertex(29, g)))
        );
    //]

    //[example__maze__policies
    typedef dfa_insertion_policy<std::ostream,int>
            OutputStreamPolicy;
    typedef bool_insertion_policy<std::ostream,single_final_state_policy<> >
            SingleTargetPolicy;
    typedef fusion::list<
                single_final_state_policy<>
              , OutputStreamPolicy
              , SingleTargetPolicy
            >
            MazePolicies;

    MazePolicies
        maze_policies(
            single_final_state_policy<>()
          , OutputStreamPolicy(
                std::cout
              , "%1%(%4%): current room = %2%; possible room changes are [%3%]"
              , ','
            )
          , SingleTargetPolicy(
                std::cout
              , "    Maze room %1% is the goal."
              , "    Maze room %1% is not yet the goal."
            )
        );
    //]

    //[example__maze__type
    typedef automaton<
                dfa_generator
              , next_state_transition_function<>
              , MazePolicies
              , input_validation_policy<>
              , mpl::true_  // Enable undo
            >
            Maze;
    //]

    //[example__maze__object
    Maze
        maze(
            builder
          , maze_policies
          , _source_state = 0
          , _undo_limit = num_vertices(g)
        );
    //]

    //[example__maze__run
    int input;

    while (
        !fusion::at_key<single_final_state_policy<> >(maze.get_observer_map())
    )
    {
        print_graph(g);
        std::cout << std::endl;
        std::cout << "Enter next room (or negative integer to undo):";
        std::cout << std::endl;

        if (!(std::cin >> input))
        {
            std::cout << "Go bye-bye." << std::endl;
            return 0;
        }

        if (input < 0)
        {
            maze.undo();
        }
        else
        {
            maze(input);
        }
    }

    std::cout << "You have solved the maze.  JOB WELL DONE!" << std::endl;
    return 0;
}
//]

