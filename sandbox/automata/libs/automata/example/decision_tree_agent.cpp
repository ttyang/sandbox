// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <boost/tr1/random.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/automata/keys/common.hpp>
#include <boost/automata/generator/probabilistic.hpp>
#include <boost/automata/transition_function/decision_tree.hpp>
#include <boost/automata/policy/mealy_output.hpp>
#include <boost/automata/automaton.hpp>

//[example__decision_tree
typedef boost::automata::decision_tree_transition_function<
            std::string
          , std::string
        >
        DecisionTreeFunction;

void initial_build(DecisionTreeFunction& function)
{
    function.set_examples()
        ("Health", "Good")
        ("Position", "Exposed")
        ("Ammunition", "Low")
        ["Run"]
        ("Health", "Good")
        ("Position", "Covered")
        ("Ammunition", "Plentiful")
        ["Attack"]
        ("Health", "Bad")
        ("Position", "Covered")
        ("Ammunition", "Plentiful")
        ["Attack"]
        ("Health", "Good")
        ("Position", "Covered")
        ("Ammunition", "Low")
        ["Defend"]
        ("Health", "Bad")
        ("Position", "Covered")
        ("Ammunition", "Low")
        ["Defend"]
        ;
}

void incremental_build_1(DecisionTreeFunction& function)
{
    function.add_example()
        ("Health", "Bad")
        ("Position", "Exposed")
        ("Ammunition", "Plentiful")
        ["Defend"];
}

void incremental_build_2(DecisionTreeFunction& function)
{
    function.add_example()
        ("Health", "Good")
        ("Position", "Exposed")
        ("Ammunition", "Plentiful")
        ["Run"];
}

typedef std::map<std::string,std::string>
        InputMap;

void write_input(InputMap::value_type const& input_pair)
{
    std::cout << '(' <<  input_pair.first << ": " << input_pair.second << ") ";
}

struct decision_tree_output
{
    template <typename Agent>
    void operator()(Agent const& agent, InputMap const& input_map) const
    {
        std::for_each(input_map.begin(), input_map.end(), write_input);
        std::cout << "=> " << agent.get_current_state() << std::endl;
    }
};

typedef boost::automata::automaton<
            boost::automata::probabilistic_generator<std::tr1::mt19937>
          , DecisionTreeFunction
          , boost::fusion::cons<
                boost::automata::mealy_output_policy<decision_tree_output>
            >
        >
        DecisionTreeAgent;

void run(DecisionTreeAgent& agent)
{
    InputMap input_map;

    input_map["Health"] = "Good";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Bad";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Position"] = "Covered";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Position"] = "Exposed";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Good";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Position"] = "Covered";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map.erase("Health");
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Position"] = "Exposed";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Ammunition"] = "Low";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Ammunition"] = "Plentiful";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Position"] = "Covered";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Ammunition"] = "Low";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map.erase("Position");
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Ammunition"] = "Plentiful";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Good";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Bad";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Ammunition"] = "Low";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Good";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);

    input_map["Health"] = "Bad";
    input_map["Position"] = "Covered";
    input_map["Ammunition"] = "Low";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Bad";
    input_map["Position"] = "Covered";
    input_map["Ammunition"] = "Plentiful";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Bad";
    input_map["Position"] = "Exposed";
    input_map["Ammunition"] = "Low";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Bad";
    input_map["Position"] = "Exposed";
    input_map["Ammunition"] = "Plentiful";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Good";
    input_map["Position"] = "Covered";
    input_map["Ammunition"] = "Low";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Good";
    input_map["Position"] = "Covered";
    input_map["Ammunition"] = "Plentiful";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Good";
    input_map["Position"] = "Exposed";
    input_map["Ammunition"] = "Low";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
    input_map["Health"] = "Good";
    input_map["Position"] = "Exposed";
    input_map["Ammunition"] = "Plentiful";
    for (std::size_t i = 0; i < 10; ++i) agent(input_map);
}

int main()
{
    DecisionTreeAgent agent(initial_build);

    std::cout << "Agent after learning first 5 examples..." << std::endl;
    run(agent);
    std::cout << std::endl << "After learning example 6..." << std::endl;
    agent.initialize(incremental_build_1);
    run(agent);
    std::cout << std::endl << "After learning example 7..." << std::endl;
    agent.initialize(incremental_build_2);
    run(agent);

    return 0;
}
//]

