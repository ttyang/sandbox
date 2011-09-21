// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_POLICY_HPP_INCLUDED
#define LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_POLICY_HPP_INCLUDED

#include <vector>
#include <iosfwd>
#include <sstream>
#include <boost/format.hpp>
#include <boost/automata/observer/full_noop.hpp>

//[example__neural_network_policy
namespace example {

    template <
        typename InsertionTarget
      , typename States
      , typename InputNames
      , typename CharT = char
    >
    class neural_network_insertion_policy
    {
        InsertionTarget&           _target;
        States                     _states;
        InputNames                 _input_names;
        boost::basic_format<CharT> _states_format_string;
        boost::basic_format<CharT> _inputs_format_string;
        boost::basic_format<CharT> _nn_format_string;
        CharT const*               _element_delimiter;
        //]

     public:
        neural_network_insertion_policy(
            InsertionTarget& target
          , States const& states
          , InputNames const& input_names
          , CharT const* states_format_string
          , CharT const* inputs_format_string
          , CharT const* nn_format_string
          , CharT const* element_delimiter
        ) : _target(target)
          , _states(states)
          , _input_names(input_names)
          , _states_format_string(states_format_string)
          , _inputs_format_string(inputs_format_string)
          , _nn_format_string(nn_format_string)
          , _element_delimiter(element_delimiter)
        {
        }

        neural_network_insertion_policy(
            neural_network_insertion_policy const& copy
        ) : _target(copy._target)
          , _states(copy._states)
          , _input_names(copy._input_names)
          , _states_format_string(copy._states_format_string)
          , _inputs_format_string(copy._inputs_format_string)
          , _nn_format_string(copy._nn_format_string)
          , _element_delimiter(copy._element_delimiter)
        {
        }

        //[example__neural_network_policy__output_helper
     private:
        template <typename SubjectAutomaton, typename Input>
        void
            _output(
                SubjectAutomaton const& subject_automaton
              , Input const& in
            )
        {
            std::basic_ostringstream<CharT> inputs_stream;

            for (std::size_t i = 0; i < in.size(); ++i)
            {
                if (i)
                {
                    inputs_stream << _element_delimiter;
                }

                inputs_stream << (
                    _inputs_format_string
                  % _input_names[i]
                  % in[i]
                );
            }

            std::basic_ostringstream<CharT> state_stream;
            typename SubjectAutomaton::traits::output const&
                output = subject_automaton.get_current_output();

            for (std::size_t i = 0; i < output.size(); ++i)
            {
                if (i)
                {
                    state_stream << _element_delimiter;
                }

                state_stream << _states_format_string % _states[i] % output[i];
            }

            _target << (
                _nn_format_string
              % inputs_stream.str().c_str()
              % state_stream.str().c_str()
              % _states[subject_automaton.get_current_state()]
            ) << std::endl;
        }
        //]

        //[example__neural_network_policy__return_type
     public:
        template <typename SubjectAutomaton>
        struct apply
        {
            class type
              : public boost::automata::full_noop_observer<SubjectAutomaton>
            {
                neural_network_insertion_policy _policy;
                //]

                //[example__neural_network_policy__return_type__subject_ctor
             public:
                type(
                    neural_network_insertion_policy const& policy
                  , SubjectAutomaton const& automaton
                ) : boost::automata::full_noop_observer<SubjectAutomaton>(
                        automaton
                    )
                  , _policy(policy)
                {
                }
                //]

                //[example__neural_network_policy__return_type__subject_copy
                type(type const& copy, SubjectAutomaton const& automaton)
                  : boost::automata::full_noop_observer<SubjectAutomaton>(
                        automaton
                    )
                  , _policy(copy._policy)
                {
                }
                //]

                //[example__neural_network_policy__return_type__copy_ctor
                type(type const& copy)
                  : boost::automata::full_noop_observer<SubjectAutomaton>(
                        copy.get_subject_automaton()
                    )
                  , _policy(copy._policy)
                {
                }
                //]

                //[example__neural_network_policy__return_type__assign_op
                type& operator=(type const& copy)
                {
                    return *this;
                }
                //]

                //[example__neural_network_policy__return_type__on_accept
                template <typename Input>
                void on_accept_input(Input const& in)
                {
                    _policy._output(this->get_subject_automaton(), in);
                }
            };
        };
    };
}  // namespace example
//]

#endif  // LIBS_AUTOMATA_EXAMPLE_NEURAL_NETWORK_POLICY_HPP_INCLUDED

