// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_POLICY_INPUT_VALIDATION_HPP_INCLUDED
#define BOOST_AUTOMATA_POLICY_INPUT_VALIDATION_HPP_INCLUDED

//[reference__input_validation_policy
namespace boost { namespace automata {

    template <typename Exception = void>
    struct input_validation_policy
    {
        template <typename SubjectAutomaton>
        struct apply
        {
            class type
            {
                //<-
                SubjectAutomaton const& _subject_automaton;
                //->

             public:
                type(
                    input_validation_policy<Exception> const& policy
                  , SubjectAutomaton const& automaton
                );

                type(type const& copy, SubjectAutomaton const& automaton);

                type(type const& copy);

                type& operator=(type const& copy);

                void on_construction();

                template <typename Builder, typename Tag>
                void on_construction(Builder const& builder, Tag);

                template <typename Builder, typename Tag>
                void on_initialize(Builder const& builder, Tag);

                template <typename Input>
                bool operator()(Input const& i);
            };
        };
    };

    //<-
    template <typename Exception>
    template <typename SubjectAutomaton>
    input_validation_policy<Exception>::apply<SubjectAutomaton>::type::type(
        input_validation_policy<Exception> const& policy
      , SubjectAutomaton const& automaton
    ) : _subject_automaton(automaton)
    {
    }

    template <typename Exception>
    template <typename SubjectAutomaton>
    input_validation_policy<Exception>::apply<SubjectAutomaton>::type::type(
        type const& copy
      , SubjectAutomaton const& automaton
    ) : _subject_automaton(automaton)
    {
    }

    template <typename Exception>
    template <typename SubjectAutomaton>
    input_validation_policy<Exception>::apply<SubjectAutomaton>::type::type(
        type const& copy
    ) : _subject_automaton(copy._subject_automaton)
    {
    }

    template <typename Exception>
    template <typename SubjectAutomaton>
    inline typename input_validation_policy<
        Exception
    >::BOOST_NESTED_TEMPLATE apply<SubjectAutomaton>::type&
        input_validation_policy<Exception>::apply<
            SubjectAutomaton
        >::type::operator=(type const& copy)
    {
        return *this;
    }

    template <typename Exception>
    template <typename SubjectAutomaton>
    inline void
        input_validation_policy<Exception>::apply<
            SubjectAutomaton
        >::type::on_construction()
    {
    }

    template <typename Exception>
    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    inline void
        input_validation_policy<Exception>::apply<
            SubjectAutomaton
        >::type::on_construction(Builder const& builder, Tag)
    {
    }

    template <typename Exception>
    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    inline void
        input_validation_policy<Exception>::apply<
            SubjectAutomaton
        >::type::on_initialize(Builder const& builder, Tag)
    {
    }

    template <typename Exception>
    template <typename SubjectAutomaton>
    template <typename Input>
    inline bool
        input_validation_policy<Exception>::apply<
            SubjectAutomaton
        >::type::operator()(Input const& i)
    {
        if (!_subject_automaton.get_transition_function().recognizes_input(i))
        {
            throw Exception(i);
        }

        return true;
    }
    //->

    template <>
    struct input_validation_policy<void>
    {
        template <typename SubjectAutomaton>
        struct apply
        {
            class type
            {
                SubjectAutomaton const& _subject_automaton;

             public:
                type(
                    input_validation_policy<void> const& policy
                  , SubjectAutomaton const& automaton
                ) : _subject_automaton(automaton)
                {
                }

                type(type const& copy, SubjectAutomaton const& automaton)
                  : _subject_automaton(automaton)
                {
                }

                type(type const& copy)
                  : _subject_automaton(copy._subject_automaton)
                {
                }

                inline type& operator=(type const& copy)
                {
                    return *this;
                }

                inline void on_construction()
                {
                }

                template <typename Builder, typename Tag>
                inline void on_construction(Builder const& builder, Tag)
                {
                }

                template <typename Builder, typename Tag>
                inline void on_initialize(Builder const& builder, Tag)
                {
                }

                template <typename Input>
                inline bool operator()(Input const& i)
                {
                    return
                        _subject_automaton
                        .get_transition_function()
                        .recognizes_input(i);
                }
            };
        };
    };
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_POLICY_INPUT_VALIDATION_HPP_INCLUDED

