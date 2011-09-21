// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/fusion/support/pair.hpp>
#include "dpda_builder.hpp"

//[test__dpda_build1__function
void build1(Function& function)
{
    Function::optional_stack_element
        N;
    Function::optional_stack_element
        S('S');
    Function::result_map
        r0(
            boost::fusion::make_pair<boost::automata::next_state_key>(0)
          , boost::fusion::make_pair<boost::automata::push_to_stack_key>(S)
        );
    Function::result_map
        r1(
            boost::fusion::make_pair<boost::automata::next_state_key>(1)
          , boost::fusion::make_pair<boost::automata::push_to_stack_key>(N)
        );

    function.reset(2);
    function.set_transition(0, 'a', r0);
    function.set_transition(0, 'b', 'S', r1);
    function.set_transition(1, 'b', 'S', r1);
}
//]

//[test__dpda_build2__function
void build2(Function& function)
{
    Function::optional_stack_element
        N;
    Function::optional_stack_element
        S('S');
    Function::optional_stack_element
        A('A');
    Function::result_map
        r0S(
            boost::fusion::make_pair<boost::automata::next_state_key>(0)
          , boost::fusion::make_pair<boost::automata::push_to_stack_key>(S)
        );
    Function::result_map
        r0A(
            boost::fusion::make_pair<boost::automata::next_state_key>(0)
          , boost::fusion::make_pair<boost::automata::push_to_stack_key>(A)
        );
    Function::result_map
        r1N(
            boost::fusion::make_pair<boost::automata::next_state_key>(1)
          , boost::fusion::make_pair<boost::automata::push_to_stack_key>(N)
        );

    function.reset(2);
    function.set_transition(0, '(', r0S);
    function.set_transition(0, '(', 'A', r0S);
    function.set_transition(0, 'x', r1N);
    function.set_transition(0, 'x', 'A', r1N);
    function.set_transition(0, 'y', r1N);
    function.set_transition(0, 'y', 'A', r1N);
    function.set_transition(0, 'z', r1N);
    function.set_transition(0, 'z', 'A', r1N);
    function.set_transition(1, ')', 'S', r1N);
    function.set_transition(1, '+', r0A);
    function.set_transition(1, '-', r0A);
    function.set_transition(1, '*', r0A);
    function.set_transition(1, '/', r0A);
}
//]

//[test__dpda_build3__function
void build3(Function& function)
{
    Function::optional_stack_element
        N;
    Function::optional_stack_element
        S('S');
    Function::optional_stack_element
        B('B');
    Function::result_map
        r0S(
            boost::fusion::make_pair<boost::automata::next_state_key>(0)
          , boost::fusion::make_pair<boost::automata::push_to_stack_key>(S)
        );
    Function::result_map
        r1B(
            boost::fusion::make_pair<boost::automata::next_state_key>(1)
          , boost::fusion::make_pair<boost::automata::push_to_stack_key>(B)
        );
    Function::result_map
        r2N(
            boost::fusion::make_pair<boost::automata::next_state_key>(2)
          , boost::fusion::make_pair<boost::automata::push_to_stack_key>(N)
        );

    function.reset(3);
    function(0, 'a') = r0S;
    function(0, 'b') = r1B;
    function(0, 'c', 'S') = r2N;
    function(1, 'b') = r1B;
    function(1, 'c', 'B') = r2N;
    function(2, 'c', 'S') = r2N;
    function(2, 'c', 'B') = r2N;
}
//]

