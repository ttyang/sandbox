// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_OBSERVER_OUTPUT_HPP_INCLUDED
#define BOOST_AUTOMATA_OBSERVER_OUTPUT_HPP_INCLUDED

//[reference__output_observer
namespace boost { namespace automata {

    template <typename Policy, typename SubjectAutomaton>
    class output_observer
    {
        //<-
        Policy                  _policy;
        SubjectAutomaton const& _subject_automaton;
        //->

     public:
        output_observer(
            Policy const& policy
          , SubjectAutomaton const& automaton
        );

        output_observer(
            output_observer const& copy
          , SubjectAutomaton const& automaton
        );

        output_observer(output_observer const& copy);

        output_observer& operator=(output_observer const& copy);

        void on_construction();

        template <typename Builder, typename Tag>
        void on_construction(Builder const& builder, Tag);

        template <typename Builder, typename Tag>
        void on_initialize(Builder const& builder, Tag);

        void on_reset();

        template <typename Input>
        void on_accept_input(Input const& i);

        template <typename Input>
        void on_reject_input(Input const& i);

        template <typename Input>
        void on_invalid_input(Input const& i);

        void on_accept_undo();

        void on_reject_undo();
    };

    //<-
    template <typename Policy, typename SubjectAutomaton>
    output_observer<Policy,SubjectAutomaton>::output_observer(
        Policy const& policy
      , SubjectAutomaton const& automaton
    ) : _policy(policy), _subject_automaton(automaton)
    {
    }

    template <typename Policy, typename SubjectAutomaton>
    output_observer<Policy,SubjectAutomaton>::output_observer(
        output_observer const& copy
      , SubjectAutomaton const& automaton
    ) : _policy(copy._policy), _subject_automaton(automaton)
    {
    }

    template <typename Policy, typename SubjectAutomaton>
    output_observer<Policy,SubjectAutomaton>::output_observer(
        output_observer const& copy
    ) : _policy(copy._policy), _subject_automaton(copy._subject_automaton)
    {
    }

    template <typename Policy, typename SubjectAutomaton>
    inline output_observer<Policy,SubjectAutomaton>&
        output_observer<Policy,SubjectAutomaton>::operator=(
            output_observer const& copy
        )
    {
        return *this;
    }

    template <typename Policy, typename SubjectAutomaton>
    void output_observer<Policy,SubjectAutomaton>::on_construction()
    {
        _policy.process_string(__FUNCTION__);
        _policy.process(_subject_automaton);
        _policy.output();
    }

    template <typename Policy, typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    void
        output_observer<Policy,SubjectAutomaton>::on_construction(
            Builder const& builder
          , Tag
        )
    {
        _policy.process_string(__FUNCTION__);
        _policy.process(_subject_automaton);
        _policy.output();
    }

    template <typename Policy, typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    void
        output_observer<Policy,SubjectAutomaton>::on_initialize(
            Builder const& builder
          , Tag
        )
    {
        _policy.process_string(__FUNCTION__);
        _policy.process(_subject_automaton);
        _policy.output();
    }

    template <typename Policy, typename SubjectAutomaton>
    void output_observer<Policy,SubjectAutomaton>::on_reset()
    {
        _policy.process_string(__FUNCTION__);
        _policy.process(_subject_automaton);
        _policy.output();
    }

    template <typename Policy, typename SubjectAutomaton>
    template <typename Input>
    void
        output_observer<Policy,SubjectAutomaton>::on_accept_input(
            Input const& i
        )
    {
        _policy.process_string(__FUNCTION__);
        _policy.process(_subject_automaton, i);
        _policy.output();
    }

    template <typename Policy, typename SubjectAutomaton>
    template <typename Input>
    void
        output_observer<Policy,SubjectAutomaton>::on_reject_input(
            Input const& i
        )
    {
        _policy.process_string(__FUNCTION__);
        _policy.process(_subject_automaton, i);
        _policy.output();
    }

    template <typename Policy, typename SubjectAutomaton>
    template <typename Input>
    void
        output_observer<Policy,SubjectAutomaton>::on_invalid_input(
            Input const& i
        )
    {
        _policy.process_string(__FUNCTION__);
        _policy.process(_subject_automaton, i);
        _policy.output();
    }

    template <typename Policy, typename SubjectAutomaton>
    void output_observer<Policy,SubjectAutomaton>::on_accept_undo()
    {
        _policy.process_string(__FUNCTION__);
        _policy.process(_subject_automaton);
        _policy.output();
    }

    template <typename Policy, typename SubjectAutomaton>
    void output_observer<Policy,SubjectAutomaton>::on_reject_undo()
    {
        _policy.process_string(__FUNCTION__);
        _policy.process(_subject_automaton);
        _policy.output();
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_OBSERVER_OUTPUT_HPP_INCLUDED

