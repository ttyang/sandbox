// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <boost/tr1/random.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/fusion/container/list.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/automata/generator/probabilistic.hpp>
#include <boost/automata/transition_function/mdp_mapped_input.hpp>
#include <boost/automata/policy/mdp_best_input.hpp>
#include <boost/automata/policy/moore_output.hpp>
#include <boost/automata/automaton.hpp>

//[example__markov_decision_process__transition_function
typedef boost::automata::mdp_mapped_input_transition_function<int>
        MDPFunction;

void build(MDPFunction& f)
{
    using boost::assign::pair_list_of;

    f.reset(3);
    f(0, 0) = pair_list_of(0, 0.5)(2, 0.5);
    f(0, 1) = 2;
    f(1, 0) = pair_list_of(0, 0.7)(1, 0.1)(2, 0.2);
    f(1, 1) = pair_list_of(1, 0.95)(2, 0.05);
    f(2, 0) = pair_list_of(0, 0.4)(2, 0.6);
    f(2, 1) = pair_list_of(0, 0.3)(1, 0.3)(2, 0.4);
}
//]

//[example__markov_decision_process__reward_function
double reward(std::size_t current_state, int i, std::size_t next_state)
{
    if (next_state == 0)
    {
        if ((current_state == 1) && (i == 0))
        {
            return 5.0;
        }

        if ((current_state == 2) && (i == 1))
        {
            return -1.0;
        }
    }

    return 0.0;
}
//]

//[example__markov_decision_process__output_function
typedef boost::automata::mdp_best_input_policy<int> BestInputPolicy;

struct mdp_output
{
    template <typename SubjectAutomaton>
    void operator()(SubjectAutomaton const& automaton) const
    {
        std::cout << "best_input[" << automaton.get_current_state() << "] = ";
        std::cout << boost::fusion::at_key<BestInputPolicy>(
            automaton.get_observer_map()
        ).get_current_best() << std::endl;
    }
};
//]

//[example__markov_decision_process__main_program
int main()
{
    typedef boost::fusion::list<
                BestInputPolicy
              , boost::automata::moore_output_policy<mdp_output>
            >
            Policies;

    boost::automata::automaton<
        boost::automata::probabilistic_generator<std::tr1::mt19937>
      , MDPFunction
      , Policies
    > mdp(build, Policies(BestInputPolicy(reward, 0.8)));

    for (std::size_t i = 0; i < 30; ++i)
    {
        mdp(
            boost::fusion::at_key<BestInputPolicy>(
                mdp.get_observer_map()
            ).get_current_best()
        );
    }

    return 0;
}
//]

