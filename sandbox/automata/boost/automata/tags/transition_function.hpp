// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_TAGS_TRANSITION_FUNCTION_HPP_INCLUDED
#define BOOST_AUTOMATA_TAGS_TRANSITION_FUNCTION_HPP_INCLUDED

namespace boost { namespace automata {

    struct transition_function_tag
    {
    };

    struct combinatorial_transition_function_tag
      : transition_function_tag
    {
    };

    struct constrained_input_transition_function_tag
      : transition_function_tag
    {
    };

    struct constrained_state_transition_function_tag
      : transition_function_tag
    {
    };

    struct state_register_transition_function_tag
      : constrained_state_transition_function_tag
    {
    };

    struct dpda_transition_function_tag
      : constrained_input_transition_function_tag
      , state_register_transition_function_tag
    {
    };

    struct dfa_transition_function_tag
      : constrained_input_transition_function_tag
      , state_register_transition_function_tag
    {
    };

    struct mdp_transition_function_tag
      : constrained_input_transition_function_tag
      , state_register_transition_function_tag
    {
    };

    struct tabular_transition_function_tag
      : dfa_transition_function_tag
    {
    };

    struct mapped_input_tabular_transition_function_tag
      : dfa_transition_function_tag
    {
    };

    struct mapped_input_transition_function_tag
      : dfa_transition_function_tag
    {
    };

    struct next_state_transition_function_tag
      : dfa_transition_function_tag
    {
    };

    struct mdp_mapped_input_transition_function_tag
      : mdp_transition_function_tag
    {
    };
}}  // namespace boost::automata

#endif  // BOOST_AUTOMATA_TAGS_TRANSITION_FUNCTION_HPP_INCLUDED

