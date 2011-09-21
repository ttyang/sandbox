// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TYPEOF_HPP_INCLUDED
#define BOOST_AUTOMATA_TYPEOF_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/automata.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(boost::automata::dpda_generator)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::dpda_transition_function, 4)
BOOST_TYPEOF_REGISTER_TYPE(boost::automata::dfa_generator)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::matrix_transition_function, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::mapped_input_tabular_transition_function
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::mapped_input_transition_function
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::next_state_transition_function
  , 2
)
BOOST_TYPEOF_REGISTER_TYPE(boost::automata::deterministic_generator)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::adaptor_transition_function, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::input_rule_transition_function
  , (typename)(bool)
)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::cellular_graph_input_rule, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::totalistic_boolean_cell_transition_function
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::totalistic_dfa_cell_transition_function
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::wolfram_code_input_rule, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::probabilistic_generator, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::mdp_mapped_input_transition_function
  , 4
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::decision_tree_transition_function
  , 5
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::decision_tree_explicit_transition_function
  , 5
)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::function_builder, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::builder_from_graph, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::output_observer, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::single_final_state_builder_from_graph
  , (typename)(unsigned long)
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::multiple_final_states_builder_from_graph
  , (typename)(unsigned long)
)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::base_observer, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::full_noop_observer, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::output_observer, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::single_final_state_policy
  , (unsigned long)
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::parallel_final_states_policy
  , (unsigned long)(typename)
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    boost::automata::serial_final_states_policy
  , (unsigned long)(typename)
)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::bool_insertion_policy, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::dpda_insertion_policy, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::dfa_insertion_policy, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::mdp_best_input_policy, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::moore_output_policy, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::mealy_output_policy, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::automata::default_input_validation_policy)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::input_validation_policy, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::automaton, 5)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::automata::function_automaton, 4)

#endif  // BOOST_AUTOMATA_TYPEOF_HPP_INCLUDED

