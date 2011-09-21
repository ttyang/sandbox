// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_HPP_INCLUDED
#define BOOST_AUTOMATA_HPP_INCLUDED

#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/tags/base.hpp>
#include <boost/automata/tags/builder.hpp>
#include <boost/automata/keys/common.hpp>
#include <boost/automata/keys/dpda.hpp>
#include <boost/automata/keys/observer.hpp>
#include <boost/automata/concept_check.hpp>
#include <boost/automata/keyword/template.hpp>
#include <boost/automata/keyword/name.hpp>
#include <boost/automata/generator/dpda.hpp>
#include <boost/automata/transition_function/dpda.hpp>
#include <boost/automata/generator/dfa.hpp>
#include <boost/automata/transition_function/matrix.hpp>
#include <boost/automata/transition_function/mapped_input_tabular.hpp>
#include <boost/automata/transition_function/mapped_input.hpp>
#include <boost/automata/transition_function/next_state.hpp>
#include <boost/automata/generator/deterministic.hpp>
#include <boost/automata/transition_function/adaptor.hpp>
#include <boost/automata/transition_function/input_rule.hpp>
#include <boost/automata/input_rule/cellular_graph.hpp>
#include <boost/automata/transition_function/totalistic_boolean_cell.hpp>
#include <boost/automata/transition_function/totalistic_dfa_cell.hpp>
#include <boost/automata/input_rule/wolfram_code.hpp>
#include <boost/automata/generator/probabilistic.hpp>
#include <boost/automata/transition_function/mdp_mapped_input.hpp>
#include <boost/automata/transition_function/decision_tree.hpp>
#include <boost/automata/builder/function.hpp>
#include <boost/automata/builder/from_graph.hpp>
#include <boost/automata/builder/from_graph/single_final_state.hpp>
#include <boost/automata/builder/from_graph/multiple_final_states.hpp>
#include <boost/automata/observer/base.hpp>
#include <boost/automata/observer/full_noop.hpp>
#include <boost/automata/observer/output.hpp>
#include <boost/automata/policy/single_final_state.hpp>
#include <boost/automata/policy/parallel_final_states.hpp>
#include <boost/automata/policy/serial_final_states.hpp>
#include <boost/automata/policy/bool_insertion.hpp>
#include <boost/automata/policy/dpda_insertion.hpp>
#include <boost/automata/policy/dfa_insertion.hpp>
#include <boost/automata/policy/mdp_best_input.hpp>
#include <boost/automata/policy/moore_output.hpp>
#include <boost/automata/policy/mealy_output.hpp>
#include <boost/automata/policy/default_input_validation.hpp>
#include <boost/automata/policy/input_validation.hpp>
#include <boost/automata/automaton.hpp>
#include <boost/automata/function_automaton.hpp>

#endif  // BOOST_AUTOMATA_HPP_INCLUDED

