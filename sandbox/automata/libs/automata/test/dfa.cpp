// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iterator>
#include <set>
#include <boost/automata/generator/dfa.hpp>
#include <boost/automata/automaton.hpp>
#include "dfa_builder.hpp"

//[test__matrix_dfa__case
using namespace boost;
using namespace automata;

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(matrix_transition_function_test)
{
    typedef automaton<dfa_generator,Function0> DFA0;

    DFA0 dfa0(build1);

    BOOST_CHECK(dfa0.get_current_state() == 0);
    BOOST_CHECK(dfa0(0));
    BOOST_CHECK(dfa0.get_current_state() == 1);
    BOOST_CHECK(dfa0(2));
    BOOST_CHECK(dfa0.get_current_state() == 0);
    BOOST_CHECK(dfa0(1));
    BOOST_CHECK(dfa0.get_current_state() == 1);
    BOOST_CHECK(!dfa0(3));
    BOOST_CHECK(dfa0.get_current_state() == 1);
    dfa0.reset();
    BOOST_CHECK(dfa0.get_current_state() == 0);

    std::set<unsigned int> inputs_0;
    DFA0::transition_function const& f0 = dfa0.get_transition_function();
    std::insert_iterator<std::set<unsigned int> > itr(
        inputs_0
      , inputs_0.begin()
    );

    dfa0.make_nontrivial_inputs(itr);
    BOOST_CHECK(inputs_0.size() == 3);
    BOOST_CHECK(inputs_0.find(0) != inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 0) == 1);
    BOOST_CHECK(inputs_0.find(1) != inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 1) == 1);
    BOOST_CHECK(inputs_0.find(2) != inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 2) == 2);
    BOOST_CHECK(inputs_0.find(3) == inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 3) == 0);
    inputs_0.clear();
    BOOST_CHECK(dfa0(0));
    BOOST_CHECK(dfa0.get_current_state() == 1);

    // . . .
    //<-
    dfa0.make_nontrivial_inputs(itr);
    BOOST_CHECK(inputs_0.size() == 2);
    BOOST_CHECK(inputs_0.find(0) == inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 0) == 1);
    BOOST_CHECK(inputs_0.find(1) != inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 1) == 2);
    BOOST_CHECK(inputs_0.find(2) != inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 2) == 0);
    BOOST_CHECK(inputs_0.find(3) == inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 3) == 1);
    inputs_0.clear();
    BOOST_CHECK(dfa0(1));
    BOOST_CHECK(dfa0.get_current_state() == 2);

    dfa0.make_nontrivial_inputs(itr);
    BOOST_CHECK(inputs_0.size() == 1);
    BOOST_CHECK(inputs_0.find(0) == inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 0) == 2);
    BOOST_CHECK(inputs_0.find(1) == inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 1) == 2);
    BOOST_CHECK(inputs_0.find(2) == inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 2) == 2);
    BOOST_CHECK(inputs_0.find(3) != inputs_0.end());
    BOOST_CHECK(f0(dfa0.get_current_state(), 3) == 3);
    inputs_0.clear();
    BOOST_CHECK(dfa0(3));
    BOOST_CHECK(dfa0.get_current_state() == 3);
    //->
}
//]

//[test__mapped_input_tabular_dfa__case
BOOST_AUTO_TEST_CASE(mapped_input_tabular_transition_function_test)
{
    typedef automaton<dfa_generator,Function1> DFA1;

    DFA1 dfa1(build2);

    BOOST_CHECK(dfa1.get_current_state() == 0);
    BOOST_CHECK(dfa1("alpha"));
    BOOST_CHECK(dfa1.get_current_state() == 1);
    BOOST_CHECK(dfa1("gamma"));
    BOOST_CHECK(dfa1.get_current_state() == 0);
    BOOST_CHECK(dfa1("beta"));
    BOOST_CHECK(dfa1.get_current_state() == 1);
    BOOST_CHECK(!dfa1("delta"));
    BOOST_CHECK(dfa1.get_current_state() == 1);
    dfa1.reset();
    BOOST_CHECK(dfa1.get_current_state() == 0);

    std::set<std::string> inputs_1;
    DFA1::transition_function const& f1 = dfa1.get_transition_function();
    std::insert_iterator<std::set<std::string> > itr(
        inputs_1
      , inputs_1.begin()
    );

    dfa1.make_nontrivial_inputs(itr);
    BOOST_CHECK(inputs_1.size() == 3);
    BOOST_CHECK(inputs_1.find("alpha") != inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "alpha") == 1);
    BOOST_CHECK(inputs_1.find("beta") != inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "beta") == 1);
    BOOST_CHECK(inputs_1.find("gamma") != inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "gamma") == 2);
    BOOST_CHECK(inputs_1.find("delta") == inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "delta") == 0);
    inputs_1.clear();
    BOOST_CHECK(dfa1("alpha"));
    BOOST_CHECK(dfa1.get_current_state() == 1);

    // . . .
    //<-
    dfa1.make_nontrivial_inputs(itr);
    BOOST_CHECK(inputs_1.size() == 2);
    BOOST_CHECK(inputs_1.find("alpha") == inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "alpha") == 1);
    BOOST_CHECK(inputs_1.find("beta") != inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "beta") == 2);
    BOOST_CHECK(inputs_1.find("gamma") != inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "gamma") == 0);
    BOOST_CHECK(inputs_1.find("delta") == inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "delta") == 1);
    inputs_1.clear();
    BOOST_CHECK(dfa1("beta"));
    BOOST_CHECK(dfa1.get_current_state() == 2);

    dfa1.make_nontrivial_inputs(itr);
    BOOST_CHECK(inputs_1.size() == 1);
    BOOST_CHECK(inputs_1.find("alpha") == inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "alpha") == 2);
    BOOST_CHECK(inputs_1.find("beta") == inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "beta") == 2);
    BOOST_CHECK(inputs_1.find("gamma") == inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "gamma") == 2);
    BOOST_CHECK(inputs_1.find("delta") != inputs_1.end());
    BOOST_CHECK(f1(dfa1.get_current_state(), "delta") == 3);
    inputs_1.clear();
    BOOST_CHECK(dfa1("delta"));
    BOOST_CHECK(dfa1.get_current_state() == 3);
    //->
}
//]

//[test__mapped_input_dfa__case
BOOST_AUTO_TEST_CASE(mapped_input_transition_function_test)
{
    typedef automaton<dfa_generator,Function2> DFA2;

    DFA2 dfa2(build3);

    BOOST_CHECK(dfa2.get_current_state() == 0);
    BOOST_CHECK(dfa2("alpha"));
    BOOST_CHECK(dfa2.get_current_state() == 1);
    BOOST_CHECK(dfa2("gamma"));
    BOOST_CHECK(dfa2.get_current_state() == 0);
    BOOST_CHECK(dfa2("beta"));
    BOOST_CHECK(dfa2.get_current_state() == 1);
    BOOST_CHECK(!dfa2("delta"));
    BOOST_CHECK(dfa2.get_current_state() == 1);
    dfa2.reset();
    BOOST_CHECK(dfa2.get_current_state() == 0);

    std::set<std::string> inputs_2;
    DFA2::transition_function const& f2 = dfa2.get_transition_function();
    std::insert_iterator<std::set<std::string> > itr(
        inputs_2
      , inputs_2.begin()
    );

    dfa2.make_nontrivial_inputs(itr);
    BOOST_CHECK(inputs_2.size() == 3);
    BOOST_CHECK(inputs_2.find("alpha") != inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "alpha") == 1);
    BOOST_CHECK(inputs_2.find("beta") != inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "beta") == 1);
    BOOST_CHECK(inputs_2.find("gamma") != inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "gamma") == 2);
    BOOST_CHECK(inputs_2.find("delta") == inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "delta") == 0);
    inputs_2.clear();
    BOOST_CHECK(dfa2("alpha"));
    BOOST_CHECK(dfa2.get_current_state() == 1);

    // . . .
    //<-
    dfa2.make_nontrivial_inputs(itr);
    BOOST_CHECK(inputs_2.size() == 2);
    BOOST_CHECK(inputs_2.find("alpha") == inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "alpha") == 1);
    BOOST_CHECK(inputs_2.find("beta") != inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "beta") == 2);
    BOOST_CHECK(inputs_2.find("gamma") != inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "gamma") == 0);
    BOOST_CHECK(inputs_2.find("delta") == inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "delta") == 1);
    inputs_2.clear();
    BOOST_CHECK(dfa2("beta"));
    BOOST_CHECK(dfa2.get_current_state() == 2);

    dfa2.make_nontrivial_inputs(itr);
    BOOST_CHECK(inputs_2.size() == 1);
    BOOST_CHECK(inputs_2.find("alpha") == inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "alpha") == 2);
    BOOST_CHECK(inputs_2.find("beta") == inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "beta") == 2);
    BOOST_CHECK(inputs_2.find("gamma") == inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "gamma") == 2);
    BOOST_CHECK(inputs_2.find("delta") != inputs_2.end());
    BOOST_CHECK(f2(dfa2.get_current_state(), "delta") == 3);
    inputs_2.clear();
    BOOST_CHECK(dfa2("delta"));
    BOOST_CHECK(dfa2.get_current_state() == 3);
    //->
}
//]

//[test__next_state_dfa__case
BOOST_AUTO_TEST_CASE(next_state_transition_function_test)
{
    typedef automaton<dfa_generator,Function3> DFA3;

    DFA3 dfa3(build4);

    BOOST_CHECK(dfa3.get_current_state() == 0);
    BOOST_CHECK(dfa3(2));
    BOOST_CHECK(dfa3.get_current_state() == 2);
    BOOST_CHECK(dfa3(4));
    BOOST_CHECK(dfa3.get_current_state() == 4);
    BOOST_CHECK(dfa3(0));
    BOOST_CHECK(dfa3.get_current_state() == 0);
    BOOST_CHECK(dfa3(1));
    BOOST_CHECK(dfa3.get_current_state() == 1);
    BOOST_CHECK(dfa3(3));
    BOOST_CHECK(dfa3.get_current_state() == 3);
    BOOST_CHECK(dfa3(2));
    BOOST_CHECK(dfa3.get_current_state() == 2);
    BOOST_CHECK(dfa3(4));
    BOOST_CHECK(dfa3.get_current_state() == 4);
    BOOST_CHECK(dfa3(3));
    BOOST_CHECK(dfa3.get_current_state() == 3);
    BOOST_CHECK(dfa3(1));
    BOOST_CHECK(dfa3.get_current_state() == 1);
    BOOST_CHECK(dfa3(0));
    BOOST_CHECK(dfa3.get_current_state() == 0);
    BOOST_CHECK(dfa3(4));
    BOOST_CHECK(dfa3.get_current_state() == 4);
    BOOST_CHECK(dfa3(5));
    BOOST_CHECK(dfa3.get_current_state() == 5);
}
//]

