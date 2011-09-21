// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_OBSERVER_BASE_HPP_INCLUDED
#define BOOST_AUTOMATA_OBSERVER_BASE_HPP_INCLUDED

//[reference__base_observer
namespace boost { namespace automata {

    template <typename SubjectAutomaton>
    class base_observer
    {
        //<-
        SubjectAutomaton const& _subject_automaton;

        base_observer(base_observer const& copy);
        //->

     protected:
        explicit base_observer(SubjectAutomaton const& automaton);

     public:
        void on_reset();

        template <typename Input>
        void on_accept_input(Input const& i);

        template <typename Input>
        void on_reject_input(Input const& i);

        template <typename Input>
        void on_invalid_input(Input const& i);

        void on_accept_undo();

        void on_reject_undo();

     protected:
        SubjectAutomaton const& get_subject_automaton() const;
    };

    //<-
    template <typename SubjectAutomaton>
    base_observer<SubjectAutomaton>::base_observer(base_observer const& copy)
      : _subject_automaton(copy._subject_automaton)
    {
    }

    template <typename SubjectAutomaton>
    base_observer<SubjectAutomaton>::base_observer(
        SubjectAutomaton const& automaton
    ) : _subject_automaton(automaton)
    {
    }

    template <typename SubjectAutomaton>
    inline void base_observer<SubjectAutomaton>::on_reset()
    {
    }

    template <typename SubjectAutomaton>
    template <typename Input>
    inline void
        base_observer<SubjectAutomaton>::on_accept_input(Input const& i)
    {
    }

    template <typename SubjectAutomaton>
    template <typename Input>
    inline void
        base_observer<SubjectAutomaton>::on_reject_input(Input const& i)
    {
    }

    template <typename SubjectAutomaton>
    template <typename Input>
    inline void
        base_observer<SubjectAutomaton>::on_invalid_input(Input const& i)
    {
    }

    template <typename SubjectAutomaton>
    inline void base_observer<SubjectAutomaton>::on_accept_undo()
    {
    }

    template <typename SubjectAutomaton>
    inline void base_observer<SubjectAutomaton>::on_reject_undo()
    {
    }

    template <typename SubjectAutomaton>
    inline SubjectAutomaton const&
        base_observer<SubjectAutomaton>::get_subject_automaton() const
    {
        return _subject_automaton;
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_OBSERVER_BASE_HPP_INCLUDED

