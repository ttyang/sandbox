// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_CONCEPT_CHECK_PROB_TRANS_FUNC_HPP_INCLUDED
#define BOOST_AUTOMATA_CONCEPT_CHECK_PROB_TRANS_FUNC_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/concept_archetype.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/concept_check/trans_func.hpp>
#include <boost/concept/detail/concept_def.hpp>

//[concept__probabilistic_transition_function
namespace boost { namespace automata {

    BOOST_concept(ProbabilisticTransitionFunction, (Function)(Input))
    //]
    //[concept__probabilistic_transition_function__refinement_of
      : TransitionFunction<Function>
    {
    //]
        //[concept__probabilistic_transition_function__types_and_variables
     public:
        typedef typename Function::tag   tag;
        typedef typename Function::state state;

     private:
        bool                              b;
        generator_archetype<unsigned int> engine;
        state const&                      s;
        Input const&                      i;
        Function&                         function;
        //]

        //[concept__probabilistic_transition_function__expressions
     public:
        BOOST_CONCEPT_USAGE(ProbabilisticTransitionFunction)
        {
            const_constraints(function);
        }

     private:
        void const_constraints(Function const& const_function)
        {
            b = const_function(s, i, engine);
        }
    };
}}  // namespace boost::automata
//]

#include <boost/concept/detail/concept_undef.hpp>

#endif  // BOOST_AUTOMATA_CONCEPT_CHECK_PROB_TRANS_FUNC_HPP_INCLUDED

