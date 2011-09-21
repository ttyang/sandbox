// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_CONCEPT_CHECK_CONS_STATE_TRANS_FUNC_HPP_INCLUDED
#define BOOST_AUTOMATA_CONCEPT_CHECK_CONS_STATE_TRANS_FUNC_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/concept_check/trans_func.hpp>
#include <boost/concept/detail/concept_def.hpp>

//[concept__constrained_state_transition_function
namespace boost { namespace automata {

    BOOST_concept(ConstrainedStateTransitionFunction, (Function))
    //]
    //[concept__constrained_state_transition_function__refinement_of
      : TransitionFunction<Function>
    {
    //]
        //[concept__constrained_state_transition_function__types_and_variables
     public:
        typedef typename Function::tag   tag;
        typedef typename Function::state state;

     private:
        BOOST_STATIC_ASSERT((
            is_base_of<constrained_state_transition_function_tag,tag>::value
        ));

        bool         b;
        state const& s;
        Function&    function;
        //]

        //[concept__constrained_state_transition_function__expressions
     public:
        BOOST_CONCEPT_USAGE(ConstrainedStateTransitionFunction)
        {
            const_constraints(function);
        }

     private:
        void const_constraints(Function const& const_function)
        {
            b = const_function.recognizes_state(s);
        }
    };
}}  // namespace boost::automata
//]

#include <boost/concept/detail/concept_undef.hpp>

#endif  // BOOST_AUTOMATA_CONCEPT_CHECK_CONS_STATE_TRANS_FUNC_HPP_INCLUDED

