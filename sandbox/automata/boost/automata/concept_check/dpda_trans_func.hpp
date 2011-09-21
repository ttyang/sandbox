// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_CONCEPT_CHECK_DPDA_TRANS_FUNC_HPP_INCLUDED
#define BOOST_AUTOMATA_CONCEPT_CHECK_DPDA_TRANS_FUNC_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/concept_archetype.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/automata/keys/common.hpp>
#include <boost/automata/keys/dpda.hpp>
#include <boost/automata/concept_check/cons_input_trans_func.hpp>
#include <boost/automata/concept_check/sr_trans_func.hpp>
#include <boost/concept/detail/concept_def.hpp>

//[concept__dpda_transition_function
namespace boost { namespace automata {

    BOOST_concept(DPDATransitionFunction, (Function))
    //]
    //[concept__dpda_transition_function__refinement_of
      : ConstrainedInputTransitionFunction<Function,typename Function::input>
      , StateRegisterTransitionFunction<Function>
    {
    //]
        //[concept__dpda_transition_function__types_and_variables
     public:
        typedef typename Function::tag
                tag;
        typedef typename Function::input
                input;
        typedef typename Function::state
                state;
        typedef typename Function::stack_element
                stack_element;
        typedef typename Function::optional_stack_element
                optional_stack_element;
        typedef typename Function::result_map
                result_map;
        typedef typename Function::result_type
                result_type;

     private:
        BOOST_STATIC_ASSERT((
            is_base_of<tag,dpda_transition_function_tag>::value
        ));

        bool                             b;
        input const&                     i;
        std::size_t const&               state_count;
        state const&                     current_state;
        state                            next_state;
        stack_element                    e;
        stack_element const&             const_e;
        output_iterator_archetype<input> out_itr;
        result_map const&                r_map;
        Function&                        function;
        //]

        //[concept__dpda_transition_function__expressions
     public:
        BOOST_CONCEPT_USAGE(DPDATransitionFunction)
        {
            function.set_transition(current_state, i, r_map);
            function(current_state, i) = r_map;
            function.set_transition(current_state, i, const_e, r_map);
            function(current_state, i, const_e) = r_map;
            function.reset(state_count);
            const_constraints(function);
        }

     private:
        void const_constraints(Function const& const_function)
        {
            b = const_function.recognizes_stack_element(const_e);
            result_type r1 = const_function(current_state, i);
            result_type r2 = const_function(current_state, i, const_e);

            if (r1)
            {
                result_map const& m = *r2;
                next_state = boost::fusion::at_key<next_state_key>(m);
                optional_stack_element const&
                    o_e = boost::fusion::at_key<push_to_stack_key>(m);

                if (o_e)
                {
                    e = *o_e;
                }
            }

            const_function.make_nontrivial_inputs(
                current_state
              , out_itr
            );
            const_function.make_nontrivial_inputs(
                current_state
              , const_e
              , out_itr
            );
        }
    };
}}  // namespace boost::automata
//]

#include <boost/concept/detail/concept_undef.hpp>

#endif  // BOOST_AUTOMATA_CONCEPT_CHECK_DPDA_TRANS_FUNC_HPP_INCLUDED

