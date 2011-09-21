// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <vector>
#include "dfa_builder.hpp"

//[example__dfa_builder__get_final_state
std::size_t
    sample_dfa_builder::single_final_state_builder::get_final_state() const
{
    return 3;
}
//]

//[example__dfa_builder__ctor__get_map
sample_dfa_builder::sample_dfa_builder()
  : _map(
        boost::fusion::make_pair<
            boost::automata::single_final_state_key<>
        >(single_final_state_builder())
      , boost::fusion::make_pair<
            boost::automata::multiple_final_states_key<>
        >(multiple_final_states_builder())
    )
{
}

sample_dfa_builder::observer_builder_map const&
    sample_dfa_builder::get_observer_builder_map() const
{
    return _map;
}
//]

//[example__dfa_builder__call_ops
//<-
void sample_dfa_builder::operator()(Function0& function) const
{
    function.reset(4, 4);
    function.set_transition(0, 0, 1);
    function.set_transition(0, 1, 1);
    function.set_transition(0, 2, 2);
    function(1, 1) = 2;
    function(1, 2) = 0;
    function(2, 3) = 3;
}
//->

void sample_dfa_builder::operator()(Function1& function) const
{
    std::vector<std::string> inputs;
    inputs.push_back("alpha");
    inputs.push_back("beta");
    inputs.push_back("gamma");
    inputs.push_back("delta");

    function.reset(4, inputs.begin(), inputs.end());
    function.set_transition(0, "alpha", 1);
    function.set_transition(0, "beta", 1);
    function.set_transition(0, "gamma", 2);
    function(1, "beta") = 2;
    function(1, "gamma") = 0;
    function(2, "delta") = 3;
}

//<-
void sample_dfa_builder::operator()(Function2& function) const
{
    function.reset(4);
    function.set_transition(0, "alpha", 1);
    function.set_transition(0, "beta", 1);
    function.set_transition(0, "gamma", 2);
    function(1, "beta") = 2;
    function(1, "gamma") = 0;
    function(2, "delta") = 3;
}
//->

void sample_dfa_builder::operator()(Function3& function) const
{
    function.reset(6);
    function.add_transition(0, 1);
    function.add_transition(0, 2);
    function.add_transition(0, 4);
    function.add_transition(1, 0);
    function.add_transition(1, 2);
    function.add_transition(1, 3);
    function.add_transition(2, 3);
    function(2) += 4;
    function(3) += 0;
    function(3) += 1;
    function(3) += 2;
    function(4) += 0;
    function(4) += 3;
    function(4) += 5;
}
//]

