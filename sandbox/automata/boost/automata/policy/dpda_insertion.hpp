// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_POLICY_DPDA_INSERTION_HPP_INCLUDED
#define BOOST_AUTOMATA_POLICY_DPDA_INSERTION_HPP_INCLUDED

#include <vector>
#include <iterator>
#include <iosfwd>
#include <sstream>
#include <boost/format.hpp>
#include <boost/automata/observer/output.hpp>

//[reference__dpda_insertion_policy
namespace boost { namespace automata {

    template <
        typename InsertionTarget
      , typename NontrivialInput
      , typename CharT = char
    >
    class dpda_insertion_policy
    {
        //<-
        InsertionTarget&    _target;
        basic_format<CharT> _format_string;
        CharT               _element_delimiter;
        //->

     public:
        dpda_insertion_policy(
            InsertionTarget& target
          , CharT const* format_string
          , CharT element_delimiter
        );

        dpda_insertion_policy(dpda_insertion_policy const& copy);

        template <typename String>
        void process_string(String const& string);

        template <typename SubjectAutomaton>
        void process(SubjectAutomaton const& subject_automaton);

        template <typename SubjectAutomaton, typename Input>
        void
            process(SubjectAutomaton const& subject_automaton, Input const& i);

        void output();

        template <typename SubjectAutomaton>
        struct apply
        {
            typedef output_observer<dpda_insertion_policy,SubjectAutomaton>
                    type;
        };
    };

    //<-
    template <
        typename InsertionTarget
      , typename NontrivialInput
      , typename CharT
    >
    dpda_insertion_policy<
        InsertionTarget
      , NontrivialInput
      , CharT
    >::dpda_insertion_policy(
        InsertionTarget& target
      , CharT const* format_string
      , CharT element_delimiter
    ) : _target(target)
      , _format_string(format_string)
      , _element_delimiter(element_delimiter)
    {
        _format_string.exceptions(
            ::boost::io::all_error_bits ^ ::boost::io::too_few_args_bit
        );
    }

    template <
        typename InsertionTarget
      , typename NontrivialInput
      , typename CharT
    >
    dpda_insertion_policy<
        InsertionTarget
      , NontrivialInput
      , CharT
    >::dpda_insertion_policy(dpda_insertion_policy const& copy)
      : _target(copy._target)
      , _format_string(copy._format_string)
      , _element_delimiter(copy._element_delimiter)
    {
    }

    template <
        typename InsertionTarget
      , typename NontrivialInput
      , typename CharT
    >
    template <typename String>
    inline void
        dpda_insertion_policy<
            InsertionTarget
          , NontrivialInput
          , CharT
        >::process_string(String const& string)
    {
        _format_string % string;
    }

    template <
        typename InsertionTarget
      , typename NontrivialInput
      , typename CharT
    >
    template <typename SubjectAutomaton>
    void
        dpda_insertion_policy<
            InsertionTarget
          , NontrivialInput
          , CharT
        >::process(SubjectAutomaton const& subject_automaton)
    {
        _format_string % subject_automaton.get_current_state();

        ::std::basic_ostringstream<CharT> stack_stream;
        typename SubjectAutomaton::traits::stack_iterator
            s_i = subject_automaton.get_stack_begin()
          , s_end = subject_automaton.get_stack_end();

        if (s_i != s_end)
        {
            for (;;)
            {
                stack_stream << *s_i;

                if (++s_i == s_end)
                {
                    break;
                }
                else
                {
                    stack_stream << _element_delimiter;
                }
            }
        }

        _format_string % stack_stream.str().c_str();

        typedef ::std::vector<NontrivialInput> Inputs;

        ::std::basic_ostringstream<CharT> inputs_stream;
        Inputs inputs;
        subject_automaton.make_nontrivial_inputs(::std::back_inserter(inputs));

        typename Inputs::const_iterator i_i = inputs.begin();
        typename Inputs::const_iterator i_end = inputs.end();

        if (i_i != i_end)
        {
            for (;;)
            {
                inputs_stream << *i_i;

                if (++i_i == i_end)
                {
                    break;
                }
                else
                {
                    inputs_stream << _element_delimiter;
                }
            }
        }

        _format_string % inputs_stream.str().c_str();
    }

    template <
        typename InsertionTarget
      , typename NontrivialInput
      , typename CharT
    >
    template <typename SubjectAutomaton, typename Input>
    inline void
        dpda_insertion_policy<
            InsertionTarget
          , NontrivialInput
          , CharT
        >::process(SubjectAutomaton const& subject_automaton, Input const& i)
    {
        this->process(subject_automaton);
        _format_string % i;
    }

    template <
        typename InsertionTarget
      , typename NontrivialInput
      , typename CharT
    >
    inline void
        dpda_insertion_policy<InsertionTarget,NontrivialInput,CharT>::output()
    {
        _target << _format_string << ::std::endl;
        _format_string.clear_binds();
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_POLICY_DPDA_INSERTION_HPP_INCLUDED

