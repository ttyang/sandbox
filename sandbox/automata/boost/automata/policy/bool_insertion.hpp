// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_POLICY_BOOL_INSERTION_HPP_INCLUDED
#define BOOST_AUTOMATA_POLICY_BOOL_INSERTION_HPP_INCLUDED

#include <iosfwd>
#include <boost/format.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/automata/observer/output.hpp>

//[reference__bool_insertion_policy
namespace boost { namespace automata {

    template <typename InsertionTarget, typename Policy, typename CharT = char>
    class bool_insertion_policy
    {
        //<-
        InsertionTarget&    _target;
        basic_format<CharT> _true_format_string;
        basic_format<CharT> _false_format_string;
        //->

     public:
        bool_insertion_policy(
            InsertionTarget& target
          , CharT const* true_format_string
          , CharT const* false_format_string
        );

        bool_insertion_policy(bool_insertion_policy const& copy);

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
            typedef output_observer<bool_insertion_policy,SubjectAutomaton>
                    type;
        };
    };

    //<-
    template <typename InsertionTarget, typename Policy, typename CharT>
    bool_insertion_policy<InsertionTarget,Policy,CharT>::bool_insertion_policy(
        InsertionTarget& target
      , CharT const* true_format_string
      , CharT const* false_format_string
    ) : _target(target)
      , _true_format_string(true_format_string)
      , _false_format_string(false_format_string)
    {
    }

    template <typename InsertionTarget, typename Policy, typename CharT>
    bool_insertion_policy<InsertionTarget,Policy,CharT>::bool_insertion_policy(
        bool_insertion_policy const& copy
    ) : _target(copy._target)
      , _true_format_string(copy._true_format_string)
      , _false_format_string(copy._false_format_string)
    {
    }

    template <typename InsertionTarget, typename Policy, typename CharT>
    template <typename String>
    inline void
        bool_insertion_policy<InsertionTarget,Policy,CharT>::process_string(
            String const& string
        )
    {
    }

    template <typename InsertionTarget, typename Policy, typename CharT>
    template <typename SubjectAutomaton>
    void
        bool_insertion_policy<InsertionTarget,Policy,CharT>::process(
            SubjectAutomaton const& subject_automaton
        )
    {
        if (
            ::boost::fusion::at_key<Policy>(
                subject_automaton.get_observer_map()
            )
        )
        {
            _target << (
                _true_format_string
              % subject_automaton.get_current_state()
            ) << ::std::endl;
            _true_format_string.clear_binds();
        }
        else
        {
            _target << (
                _false_format_string
              % subject_automaton.get_current_state()
            ) << ::std::endl;
            _false_format_string.clear_binds();
        }
    }

    template <typename InsertionTarget, typename Policy, typename CharT>
    template <typename SubjectAutomaton, typename Input>
    inline void
        bool_insertion_policy<InsertionTarget,Policy,CharT>::process(
            SubjectAutomaton const& subject_automaton
          , Input const& i
        )
    {
        this->process(subject_automaton);
    }

    template <typename InsertionTarget, typename Policy, typename CharT>
    inline void bool_insertion_policy<InsertionTarget,Policy,CharT>::output()
    {
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_POLICY_BOOL_INSERTION_HPP_INCLUDED

