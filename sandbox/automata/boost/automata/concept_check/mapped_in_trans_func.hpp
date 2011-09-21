// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_CONCEPT_CHECK_MAPPED_IN_TRANS_FUNC_HPP_INCLUDED
#define BOOST_AUTOMATA_CONCEPT_CHECK_MAPPED_IN_TRANS_FUNC_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/concept_check/dfa_trans_func.hpp>
#include <boost/concept/detail/concept_def.hpp>

//[concept__mapped_input_transition_function
namespace boost { namespace automata {

    BOOST_concept(MappedInputTransitionFunction, (Function))
    //]
    //[concept__mapped_input_transition_function__refinement_of
      : DFATransitionFunction<Function>
    {
    //]
        //[concept__mapped_input_transition_function__types_and_variables
     public:
        typedef typename Function::tag                  tag;
        typedef typename Function::state                state;
        typedef typename Function::result_type          result_type;
        typedef typename Function::first_argument_type  first_argument_type;
        typedef typename Function::second_argument_type second_argument_type;

     private:
        BOOST_STATIC_ASSERT((
            is_base_of<mapped_input_transition_function_tag,tag>::value
        ));

        std::size_t const&          state_count;
        state const&                current_state;
        second_argument_type const& i;
        state const&                next_state;
        Function&                   function;
        //]

        //[concept__mapped_input_transition_function__expressions
     public:
        BOOST_CONCEPT_USAGE(MappedInputTransitionFunction)
        {
            function.set_transition(current_state, i, next_state);
            function(current_state, i) = next_state;
            function.reset(state_count);
        }
    };
}}  // namespace boost::automata
//]

#include <boost/concept/detail/concept_undef.hpp>

#endif  // BOOST_AUTOMATA_CONCEPT_CHECK_MAPPED_IN_TRANS_FUNC_HPP_INCLUDED

