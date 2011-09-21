// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_POLICY_SINGLE_FINAL_STATE_HPP_INCLUDED
#define BOOST_AUTOMATA_POLICY_SINGLE_FINAL_STATE_HPP_INCLUDED

#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/keys/observer.hpp>
#include <boost/automata/observer/full_noop.hpp>

//[reference__is_at_final_state
namespace boost { namespace automata {

    template <typename SubjectAutomaton, typename TransitionFunctionTag>
    bool
        is_at_final_state(
            typename SubjectAutomaton::state const& final_state
          , SubjectAutomaton const& subject_automaton
          , TransitionFunctionTag
        );

    //<-
    template <typename SubjectAutomaton, typename TransitionFunctionTag>
    inline bool
        is_at_final_state(
            typename SubjectAutomaton::state const& final_state
          , SubjectAutomaton const& subject_automaton
          , TransitionFunctionTag
        )
    {
        return final_state == subject_automaton.get_current_state();
    }

    template <typename SubjectAutomaton>
    inline bool
        is_at_final_state(
            typename SubjectAutomaton::state const& final_state
          , SubjectAutomaton const& subject_automaton
          , dpda_transition_function_tag
        )
    {
        return subject_automaton.has_empty_stack() && (
            final_state == subject_automaton.get_current_state()
        );
    }
    //->
}}  // namespace boost::automata
//]

//[reference__single_final_state_policy
namespace boost { namespace automata {

    template <unsigned long Uid = 0UL>
    struct single_final_state_policy
    {
        template <typename SubjectAutomaton>
        struct apply
        {
            class type : public full_noop_observer<SubjectAutomaton>
            {
                // <-
                typename SubjectAutomaton::state _final_state;
                // ->

             public:
                type(
                    single_final_state_policy const& policy
                  , SubjectAutomaton const& automaton
                );

                type(type const& copy, SubjectAutomaton const& automaton);

                type(type const& copy);

                type& operator=(type const& copy);

                template <typename Builder, typename Tag>
                void on_construction(Builder const& builder, Tag);

                template <typename Builder, typename Tag>
                void on_initialize(Builder const& builder, Tag);

                operator bool() const;
            };
        };
    };

    //<-
    template <unsigned long Uid>
    template <typename SubjectAutomaton>
    single_final_state_policy<Uid>::apply<SubjectAutomaton>::type::type(
        single_final_state_policy const& policy
      , SubjectAutomaton const& automaton
    ) : full_noop_observer<SubjectAutomaton>(automaton)
      , _final_state()
    {
    }

    template <unsigned long Uid>
    template <typename SubjectAutomaton>
    single_final_state_policy<Uid>::apply<SubjectAutomaton>::type::type(
        type const& copy
      , SubjectAutomaton const& automaton
    ) : full_noop_observer<SubjectAutomaton>(automaton)
      , _final_state(copy._final_state)
    {
    }

    template <unsigned long Uid>
    template <typename SubjectAutomaton>
    single_final_state_policy<Uid>::apply<SubjectAutomaton>::type::type(
        type const& copy
    ) : full_noop_observer<SubjectAutomaton>(copy.get_subject_automaton())
      , _final_state(copy._final_state)
    {
    }

    template <unsigned long Uid>
    template <typename SubjectAutomaton>
    inline typename single_final_state_policy<
        Uid
    >::BOOST_NESTED_TEMPLATE apply<SubjectAutomaton>::type&
        single_final_state_policy<Uid>::apply<
            SubjectAutomaton
        >::type::operator=(type const& copy)
    {
        if (this != &copy)
        {
            _final_state = copy._final_state;
        }

        return *this;
    }

    template <unsigned long Uid>
    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    void
        single_final_state_policy<Uid>::apply<
            SubjectAutomaton
        >::type::on_construction(Builder const& builder, Tag)
    {
        _final_state = ::boost::fusion::at_key<single_final_state_key<Uid> >(
            builder.get_observer_builder_map()
        ).get_final_state();
    }

    template <unsigned long Uid>
    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    void
        single_final_state_policy<Uid>::apply<
            SubjectAutomaton
        >::type::on_initialize(Builder const& builder, Tag)
    {
        _final_state = ::boost::fusion::at_key<single_final_state_key<Uid> >(
            builder.get_observer_builder_map()
        ).get_final_state();
    }

    template <unsigned long Uid>
    template <typename SubjectAutomaton>
    inline single_final_state_policy<Uid>::apply<
        SubjectAutomaton
    >::type::operator bool() const
    {
        return is_at_final_state(
            _final_state
          , this->get_subject_automaton()
          , typename SubjectAutomaton::transition_function::tag()
        );
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_POLICY_SINGLE_FINAL_STATE_HPP_INCLUDED

