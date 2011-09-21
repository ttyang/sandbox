// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iterator>
#include <iostream>
#include <vector>
#include <boost/fusion/container/list.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/automata/generator/dfa.hpp>
#include <boost/automata/policy/single_final_state.hpp>
#include <boost/automata/policy/parallel_final_states.hpp>
#include <boost/automata/policy/bool_insertion.hpp>
#include <boost/automata/policy/dfa_insertion.hpp>
#include <boost/automata/automaton.hpp>
#include "dfa_builder.hpp"

//[example__dfa__policies_1
using namespace boost;
using namespace automata;
using namespace keyword;

int main()
{
    typedef dfa_insertion_policy<std::ostream,std::string>
            OutputStreamPolicy1;
    typedef dfa_insertion_policy<std::ostream,unsigned int>
            OutputStreamPolicy2;

    OutputStreamPolicy1 ostream_policy1(
        std::cout
      , "%1%(%4%): current state = %2%; nontrivial inputs = [%3%]"
      , ','
    );
    OutputStreamPolicy2 ostream_policy2(
        std::cout
      , "%1%(%4%): current state = %2%; nontrivial inputs = [%3%]"
      , ','
    );

    typedef bool_insertion_policy<std::ostream,single_final_state_policy<> >
            SingleTargetPolicy;
    typedef fusion::list<
                single_final_state_policy<>
              , OutputStreamPolicy1
              , SingleTargetPolicy
            >
            Policies1;
    //]
    //[example__dfa__1
    typedef automaton<dfa_generator,Function1,Policies1>
            DFA1;

    sample_dfa_builder
        builder;
    DFA1
        dfa1(
            builder
          , Policies1(
                single_final_state_policy<>()
              , ostream_policy1
              , SingleTargetPolicy(
                    std::cout
                  , "DFA1: %1% is a final state."
                  , "DFA1: %1% is not a final state."
                )
            )
        );
    //]

    //[example__dfa__run_1
    dfa1("alpha");
    dfa1("gamma");
    dfa1("beta");
    dfa1("delta");
    dfa1.reset();

    std::vector<std::string> inputs;

    while (
        !fusion::at_key<single_final_state_policy<> >(dfa1.get_observer_map())
    )
    {
        dfa1.make_nontrivial_inputs(
            std::insert_iterator<std::vector<std::string> >(inputs, inputs.begin())
        );

        if (inputs.empty())
        {
            std::cout << "DFA1 final state unreachable." << std::endl;
            break;
        }

        dfa1(inputs[0]);
        inputs.clear();
    }

    std::cout << std::endl;
    //]

    //[example__dfa__2
    typedef bool_insertion_policy<std::ostream,parallel_final_states_policy<> >
            ParallelTargetPolicy;
    typedef fusion::list<
                parallel_final_states_policy<>
              , OutputStreamPolicy2
              , ParallelTargetPolicy
            >
            Policies2;
    typedef automaton<dfa_generator,Function3,Policies2>
            DFA2;

    DFA2
        dfa2(
            builder
          , Policies2(
                parallel_final_states_policy<>()
              , ostream_policy2
              , ParallelTargetPolicy(
                    std::cout
                  , "DFA2: %1% is a final state."
                  , "DFA2: %1% is not a final state."
                )
            )
        );
    //]

    //[example__dfa__run_2
    dfa2(2);
    dfa2(4);
    dfa2(0);
    dfa2(1);
    dfa2(3);
    dfa2(2);
    dfa2(4);
    dfa2(3);
    dfa2(1);
    dfa2(0);
    dfa2(4);
    dfa2(5);

    return 0;
}
//]

