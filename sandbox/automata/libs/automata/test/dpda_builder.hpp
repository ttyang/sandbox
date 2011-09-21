// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_AUTOMATA_TEST_DPDA_BUILDER_HPP_INCLUDED
#define LIBS_AUTOMATA_TEST_DPDA_BUILDER_HPP_INCLUDED

#include <boost/automata/transition_function/dpda.hpp>

//[test__dpda_trans_func__typedef
typedef boost::automata::dpda_transition_function<char,char>
        Function;
//]

void build1(Function& function);
void build2(Function& function);
void build3(Function& function);

#endif  // LIBS_AUTOMATA_TEST_DPDA_BUILDER_HPP_INCLUDED

