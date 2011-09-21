// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_POLICY_DEFAULT_INPUT_VALIDATION_HPP_INCLUDED
#define BOOST_AUTOMATA_POLICY_DEFAULT_INPUT_VALIDATION_HPP_INCLUDED

//[reference__default_input_validation_policy
namespace boost { namespace automata {

    struct default_input_validation_policy
    {
        template <typename SubjectAutomaton>
        struct apply
        {
            struct type
            {
                type(
                    default_input_validation_policy const& policy
                  , SubjectAutomaton const& automaton
                );

                type(type const& copy, SubjectAutomaton const& automaton);

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
    template <typename SubjectAutomaton>
    default_input_validation_policy::apply<SubjectAutomaton>::type::type(
        default_input_validation_policy const& policy
      , SubjectAutomaton const& automaton
    )
    {
    }

    template <typename SubjectAutomaton>
    default_input_validation_policy::apply<SubjectAutomaton>::type::type(
        type const& copy
      , SubjectAutomaton const& automaton
    )
    {
    }

    template <typename SubjectAutomaton>
    inline void
        default_input_validation_policy::apply<
            SubjectAutomaton
        >::type::on_construction()
    {
    }

    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    inline void
        default_input_validation_policy::apply<
            SubjectAutomaton
        >::type::on_construction(Builder const& builder, Tag)
    {
    }

    template <typename SubjectAutomaton>
    template <typename Builder, typename Tag>
    inline void
        default_input_validation_policy::apply<
            SubjectAutomaton
        >::type::on_initialize(Builder const& builder, Tag)
    {
    }

    template <typename SubjectAutomaton>
    template <typename Input>
    inline bool
        default_input_validation_policy::apply<
            SubjectAutomaton
        >::type::operator()(Input const& i)
    {
        return true;
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_POLICY_DEFAULT_INPUT_VALIDATION_HPP_INCLUDED

