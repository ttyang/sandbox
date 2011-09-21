// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_AUTOMATA_CONCEPT_CHECK_TRANS_FUNC_HPP_INCLUDED
#define BOOST_AUTOMATA_CONCEPT_CHECK_TRANS_FUNC_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/automata/tags/transition_function.hpp>
#include <boost/concept/detail/concept_def.hpp>

//[concept__transition_function
namespace boost { namespace automata {

    BOOST_concept(TransitionFunction, (Function))
    //]
    //[concept__transition_function__refinement_of
      : DefaultConstructible<Function>
    {
    //]
        //[concept__transition_function__types_and_variables
     public:
        typedef typename Function::tag   tag;
        typedef typename Function::state state;

     private:
        BOOST_STATIC_ASSERT((is_base_of<transition_function_tag,tag>::value));

        Function& function;
        //]

        //[concept__transition_function__expressions
     public:
        BOOST_CONCEPT_USAGE(TransitionFunction)
        {
            const_constraints(function);
        }

     private:
        void const_constraints(Function const& const_function)
        {
        }
    };
}}  // namespace boost::automata
//]

#include <boost/concept/detail/concept_undef.hpp>

#endif  // BOOST_AUTOMATA_CONCEPT_CHECK_TRANS_FUNC_HPP_INCLUDED

