// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_POLICY_SERIAL_FINAL_STATES_HPP_INCLUDED
#define BOOST_AUTOMATA_POLICY_SERIAL_FINAL_STATES_HPP_INCLUDED

#include <iterator>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/range.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/keys/observer.hpp>
#include <boost/automata/observer/full_noop.hpp>

//[reference__has_no_unvisited_states
namespace boost { namespace automata {

    template <
        typename States
      , typename SubjectAutomaton
      , typename TransitionFunctionTag
    >
    bool
        has_no_unvisited_states(
            States const& unvisited_states
          , SubjectAutomaton const& subject_automaton
          , TransitionFunctionTag
        );

    //<-
    template <
        typename States
      , typename SubjectAutomaton
      , typename TransitionFunctionTag
    >
    inline bool
        has_no_unvisited_states(
            States const& unvisited_states
          , SubjectAutomaton const& subject_automaton
          , TransitionFunctionTag
        )
    {
        return unvisited_states.empty();
    }

    template <typename States, typename SubjectAutomaton>
    inline bool
        has_no_unvisited_states(
            States const& unvisited_states
          , SubjectAutomaton const& subject_automaton
          , dpda_transition_function_tag
        )
    {
        return subject_automaton.has_empty_stack() && unvisited_states.empty();
    }
    //->
}}  // namespace boost::automata
//]

//[reference__serial_final_states_policy
namespace boost { namespace automata {

    template <
        unsigned long Uid = 0UL
      , typename AssociativeContainerSelector = ::boost::setS
    >
    struct serial_final_states_policy
    {
        template <typename SubjectAutomaton>
        struct apply
        {
            class type : public full_noop_observer<SubjectAutomaton>
            {
                //<-
                typedef typename ::boost::mpl::apply_wrap1<
                            ::boost::associative_container_gen<
                                AssociativeContainerSelector
                            >
                          , typename SubjectAutomaton::state
                        >::type
                        States;

                States _final_states;
                States _states;
                //->

             public:
                type(
                    serial_final_states_policy const& policy
                  , SubjectAutomaton const& automaton
                );

                type(type const& copy, SubjectAutomaton const& automaton);

                type(type const& copy);

                type& operator=(type const& copy);

                template <typename Builder, typename Tag>
                void on_construction(Builder const& builder, Tag);

                template <typename Builder, typename Tag>
                void on_initialize(Builder const& builder, Tag);

                void on_reset();

                template <typename Input>
                void on_accept_input(Input const& i);

                operator bool() const;
            };
        };
    };

    //<-
    template <unsigned long Uid, typename AssociativeContainerSelector>
    template <typename SubjectAutomaton>
    serial_final_states_policy<Uid,AssociativeContainerSelector>::apply<
        SubjectAutomaton
    >::type::type(
        serial_final_states_policy const& policy
      , SubjectAutomaton const& automaton
    ) : full_noop_observer<SubjectAutomaton>(automaton)
      , _final_states()
      , _states()
    {
    }

    template <unsigned long Uid, typename AssociativeContainerSelector>
    template <typename SubjectAutomaton>
    serial_final_states_policy<Uid,AssociativeContainerSelector>::apply<
        SubjectAutomaton
    >::type::type(type const& copy, SubjectAutomaton const& automaton)
      : full_noop_observer<SubjectAutomaton>(automaton)
      , _final_states(copy._final_states)
      , _states(copy._states)
    {
    }

    template <unsigned long Uid, typename AssociativeContainerSelector>
    template <typename SubjectAutomaton>
    serial_final_states_policy<Uid,AssociativeContainerSelector>::apply<
        SubjectAutomaton
    >::type::type(type const& copy)
      : full_noop_observer<SubjectAutomaton>(copy.get_subject_automaton())
      , _final_states(copy._final_states)
      , _states(copy._states)
    {
    }

    template <unsigned long Uid, typename AssociativeContainerSelector>
    template <typename SubjectAutomaton>
    inline typename serial_final_states_policy<
        Uid
      , AssociativeContainerSelector
    >::BOOST_NESTED_TEMPLATE apply<SubjectAutomaton>::type&
        serial_final_states_policy<Uid,AssociativeContainerSelector>::apply<
            SubjectAutomaton
        >::type::operator=(type const& copy)
    {
        if (this != &copy)
        {
            _final_states = copy._final_states;
            _states = copy._states;
        }

        return *this;
    }

    template <unsigned long Uid, typename AssociativeContainerSelector>
    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    inline void
        serial_final_states_policy<Uid,AssociativeContainerSelector>::apply<
            SubjectAutomaton
        >::type::on_construction(Builder const& builder, Tag)
    {
        _final_states.clear();
        ::boost::fusion::at_key<multiple_final_states_key<Uid> >(
            builder.get_observer_builder_map()
        ).make_final_states(_final_states);
    }

    template <unsigned long Uid, typename AssociativeContainerSelector>
    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    inline void
        serial_final_states_policy<Uid,AssociativeContainerSelector>::apply<
            SubjectAutomaton
        >::type::on_initialize(Builder const& builder, Tag)
    {
        _final_states.clear();
        ::boost::fusion::at_key<multiple_final_states_key<Uid> >(
            builder.get_observer_builder_map()
        ).make_final_states(_final_states);
    }

    template <unsigned long Uid, typename AssociativeContainerSelector>
    template <typename SubjectAutomaton>
    void
        serial_final_states_policy<Uid,AssociativeContainerSelector>::apply<
            SubjectAutomaton
        >::type::on_reset()
    {
        _states.clear();
        ::std::insert_iterator<States> inserter(_states, begin(_states));
        typename range_const_iterator<States>::type s_end = end(
            _final_states
        );

        for (
            typename range_const_iterator<States>::type s_i = begin(
                _final_states
            );
            s_i != s_end;
            ++s_i
        )
        {
            *inserter = *s_i;
            ++inserter;
        }
    }

    template <unsigned long Uid, typename AssociativeContainerSelector>
    template <typename SubjectAutomaton>
    template <typename Input>
    inline void
        serial_final_states_policy<Uid,AssociativeContainerSelector>::apply<
            SubjectAutomaton
        >::type::on_accept_input(Input const& i)
    {
        _states.remove(this->get_subject_automaton().get_current_state());
    }

    template <unsigned long Uid, typename AssociativeContainerSelector>
    template <typename SubjectAutomaton>
    inline serial_final_states_policy<
        Uid
      , AssociativeContainerSelector
    >::apply<SubjectAutomaton>::type::operator bool() const
    {
        return has_no_unvisited_states(
            _states
          , this->get_subject_automaton()
          , typename SubjectAutomaton::transition_function::tag()
        );
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_POLICY_SERIAL_FINAL_STATES_HPP_INCLUDED

