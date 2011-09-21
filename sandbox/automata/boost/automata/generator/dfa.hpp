// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_GENERATOR_DFA_HPP_INCLUDED
#define BOOST_AUTOMATA_GENERATOR_DFA_HPP_INCLUDED

#include <boost/automata/tags/base.hpp>
#include <boost/automata/concept_check.hpp>

//[reference__dfa_generator
namespace boost { namespace automata {

    struct dfa_generator
    {
        template <typename Function>
        struct apply
        {
            BOOST_CONCEPT_ASSERT((DFATransitionFunction<Function>));

            struct type
            {
             protected:
                typedef input_enumerable_automaton_base_tag tag;
                typedef void                                traits;

                static void reset_impl();

                template <typename Input>
                static bool
                    is_nontrivial_input_impl(
                        Function const& function
                      , typename Function::state const& current_state
                      , Input const& i
                    );

                template <typename Iterator>
                static void
                    make_nontrivial_inputs_impl(
                        Function const& function
                      , typename Function::state const& current_state
                      , Iterator itr
                    );

                template <typename Input>
                static bool
                    process_input_impl(
                        Function const& function
                      , typename Function::state& current_state
                      , Input const& i
                    );
            };
        };
    };

    //<-
    template <typename Function>
    inline void dfa_generator::apply<Function>::type::reset_impl()
    {
    }

    template <typename Function>
    template <typename Input>
    inline bool
        dfa_generator::apply<Function>::type::is_nontrivial_input_impl(
            Function const& function
          , typename Function::state const& current_state
          , Input const& i
        )
    {
        return current_state != function(current_state, i);
    }

    template <typename Function>
    template <typename Iterator>
    inline void
        dfa_generator::apply<Function>::type::make_nontrivial_inputs_impl(
            Function const& function
          , typename Function::state const& current_state
          , Iterator itr
        )
    {
        function.make_nontrivial_inputs(current_state, itr);
    }

    template <typename Function>
    template <typename Input>
    inline bool
        dfa_generator::apply<Function>::type::process_input_impl(
            Function const& function
          , typename Function::state& current_state
          , Input const& i
        )
    {
        if (type::is_nontrivial_input_impl(function, current_state, i))
        {
            current_state = function(current_state, i);
            return true;
        }
        else
        {
            return false;
        }
    }
    //->
}}  // namespace boost::automata
//]

#endif  // BOOST_AUTOMATA_GENERATOR_DFA_HPP_INCLUDED

