// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_CONCEPT_CHECK_NEXT_STATE_TRANS_FUNC_HPP_INCLUDED
#define BOOST_AUTOMATA_CONCEPT_CHECK_NEXT_STATE_TRANS_FUNC_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/concept_check/dfa_trans_func.hpp>
#include <boost/concept/detail/concept_def.hpp>

//[concept__next_state_transition_function
namespace boost { namespace automata {

    BOOST_concept(NextStateTransitionFunction, (Function))
    //]
    //[concept__next_state_transition_function__refinement_of
      : DFATransitionFunction<Function>
    {
    //]
        //[concept__next_state_transition_function__types_and_variables
     public:
        typedef typename Function::tag                  tag;
        typedef typename Function::state                state;
        typedef typename Function::result_type          result_type;
        typedef typename Function::first_argument_type  first_argument_type;
        typedef typename Function::second_argument_type second_argument_type;

     private:
        BOOST_STATIC_ASSERT((
            is_base_of<next_state_transition_function_tag,tag>::value
        ));
        BOOST_STATIC_ASSERT((
            is_same<state,second_argument_type>::value
        ));
        BOOST_STATIC_ASSERT((
            is_same<second_argument_type,first_argument_type>::value
        ));

        std::size_t const& state_count;
        state const&       current_state;
        state const&       next_state;
        Function&          function;
        //]

        //[concept__next_state_transition_function__expressions
     public:
        BOOST_CONCEPT_USAGE(NextStateTransitionFunction)
        {
            function.add_transition(current_state, next_state);
            function(current_state) += next_state;
            function.reset(state_count);
        }
    };
}}  // namespace boost::automata
//]

#include <boost/concept/detail/concept_undef.hpp>

#endif  // BOOST_AUTOMATA_CONCEPT_CHECK_NEXT_STATE_TRANS_FUNC_HPP_INCLUDED

