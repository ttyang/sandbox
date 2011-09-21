// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_TEST_DFA_BUILDER_HPP_INCLUDED
#define LIBS_AUTOMATA_TEST_DFA_BUILDER_HPP_INCLUDED

#include <string>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/automata/transition_function/matrix.hpp>
#include <boost/automata/transition_function/mapped_input_tabular.hpp>
#include <boost/automata/transition_function/mapped_input.hpp>
#include <boost/automata/transition_function/next_state.hpp>

//[test__dfa_trans_func__typedefs
typedef boost::automata::matrix_transition_function<
            boost::numeric::ublas::matrix<std::size_t>
        >
        Function0;
typedef boost::automata::mapped_input_tabular_transition_function<
            std::string
          , Function0
        >
        Function1;
typedef boost::automata::mapped_input_transition_function<std::string>
        Function2;
typedef boost::automata::next_state_transition_function<>
        Function3;
//]

void build1(Function0& function);
void build2(Function1& function);
void build3(Function2& function);
void build4(Function3& function);

#endif  // LIBS_AUTOMATA_TEST_DFA_BUILDER_HPP_INCLUDED

