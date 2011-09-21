// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_CONCEPT_CHECK_DFA_TRANS_FUNC_HPP_INCLUDED
#define BOOST_AUTOMATA_CONCEPT_CHECK_DFA_TRANS_FUNC_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/concept_archetype.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/concept_check/cons_input_trans_func.hpp>
#include <boost/automata/concept_check/sr_trans_func.hpp>
#include <boost/concept/detail/concept_def.hpp>

//[concept__dfa_transition_function
namespace boost { namespace automata {

    BOOST_concept(DFATransitionFunction, (Function))
    //]
    //[concept__dfa_transition_function__refinement_of
      : ConstrainedInputTransitionFunction<
            Function
          , typename Function::second_argument_type
        >
      , StateRegisterTransitionFunction<Function>
    {
    //]
        //[concept__dfa_transition_function__types_and_variables
     public:
        typedef typename Function::tag                  tag;
        typedef typename Function::state                state;
        typedef typename Function::result_type          result_type;
        typedef typename Function::first_argument_type  first_argument_type;
        typedef typename Function::second_argument_type second_argument_type;

     private:
        BOOST_STATIC_ASSERT((
            is_base_of<dfa_transition_function_tag,tag>::value
        ));
        BOOST_STATIC_ASSERT((
            is_same<result_type,first_argument_type>::value
        ));
        BOOST_STATIC_ASSERT((
            is_same<result_type,state>::value
        ));

        state const&                                    current_state;
        second_argument_type const&                     i;
        output_iterator_archetype<second_argument_type> out_itr;
        Function&                                       function;
        //]

        //[concept__dfa_transition_function__expressions
     public:
        BOOST_CONCEPT_USAGE(DFATransitionFunction)
        {
            const_constraints(function);
        }

     private:
        void const_constraints(Function const& const_function)
        {
            result_type next_state = const_function(current_state, i);
            next_state = const_function.get_state_count();
            const_function.make_nontrivial_inputs(current_state, out_itr);
        }
    };
}}  // namespace boost::automata
//]

#include <boost/concept/detail/concept_undef.hpp>

#endif  // BOOST_AUTOMATA_CONCEPT_CHECK_DFA_TRANS_FUNC_HPP_INCLUDED

