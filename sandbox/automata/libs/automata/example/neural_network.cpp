// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <utility>
#include <vector>
#include <boost/array.hpp>
#include <boost/foreach.hpp>
#include <boost/fusion/container/list.hpp>
#include <boost/automata/automaton.hpp>
#include "neural_network_generator.hpp"
#include "neural_network_trans_func.hpp"
#include "neural_network_make_samples.hpp"
#include "neural_network_builder.hpp"
#include "neural_network_policy.hpp"

//[example__neural_network__type_definitions
using namespace boost;
using namespace automata;
using namespace example;

int main()
{
    typedef array<char const*,neural_network_transition_function::state_count>
            States;
    typedef array<char const*,neural_network_transition_function::input_count>
            InputNames;
    typedef neural_network_insertion_policy<std::ostream,States,InputNames>
            OutputStreamPolicy;
    typedef fusion::list<OutputStreamPolicy>
            NeuralNetworkPolicies;
    typedef automaton<
                neural_network_generator
              , neural_network_transition_function
              , NeuralNetworkPolicies
            >
            NeuralNetwork;
    typedef std::vector<std::vector<double> >
            Inputs;
    typedef std::vector<NeuralNetwork::traits::output>
            Outputs;
    typedef neural_network_builder<Inputs,Outputs>
            Builder;
    //]

    //[example__neural_network__inputs_outputs
    Inputs inputs;
    Outputs outputs;

    make_samples(inputs, outputs);
    //]

    //[example__neural_network__automaton
    States
        states = {{"Hunt", "Run", "Wander", "Hide"}};
    InputNames
        input_names = {{"Health", "Has Knife", "Has Gun", "Bear Count"}};
    NeuralNetwork
        neural_network(
            Builder(inputs, outputs, 100000, 0.2)
          , NeuralNetworkPolicies(
                OutputStreamPolicy(
                    std::cout
                  , states
                  , input_names
                  , "%1% vote = %2%"
                  , "%1% = %2%"
                  , "%1%.\n  %2%.\n  Current action = %3%."
                  , ", "
                )
            )
        );
    //]

    //[example__neural_network__run
    BOOST_FOREACH(std::vector<double> const& i, inputs)
    {
        neural_network(i);
    }

    return 0;
}
//]

