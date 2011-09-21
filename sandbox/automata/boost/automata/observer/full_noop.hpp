// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_OBSERVER_FULL_NOOP_HPP_INCLUDED
#define BOOST_AUTOMATA_OBSERVER_FULL_NOOP_HPP_INCLUDED

#include <boost/automata/observer/base.hpp>

//[reference__full_noop_observer
namespace boost { namespace automata {

    template <typename SubjectAutomaton>
    class full_noop_observer : public base_observer<SubjectAutomaton>
    {
     protected:
        explicit full_noop_observer(SubjectAutomaton const& automaton);

     public:
        void on_construction();

        template <typename Builder, typename Tag>
        void on_construction(Builder const& builder, Tag);

        template <typename Builder, typename Tag>
        void on_initialize(Builder const& builder, Tag);
    };

    //<-
    template <typename SubjectAutomaton>
    full_noop_observer<SubjectAutomaton>::full_noop_observer(
        SubjectAutomaton const& automaton
    ) : base_observer<SubjectAutomaton>(automaton)
    {
    }

    template <typename SubjectAutomaton>
    inline void full_noop_observer<SubjectAutomaton>::on_construction()
    {
    }

    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    inline void
        full_noop_observer<SubjectAutomaton>::on_construction(
            Builder const& builder
          , Tag
        )
    {
    }

    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    inline void
        full_noop_observer<SubjectAutomaton>::on_initialize(
            Builder const& builder
          , Tag
        )
    {
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_OBSERVER_FULL_NOOP_HPP_INCLUDED

