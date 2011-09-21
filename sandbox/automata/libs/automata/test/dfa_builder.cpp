// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <vector>
#include "dfa_builder.hpp"

//[test__dfa_build1__function
void build1(Function0& function)
{
    function.reset(4, 4);
    function.set_transition(0, 0, 1);
    function.set_transition(0, 1, 1);
    function.set_transition(0, 2, 2);
    function(1, 1) = 2;
    function(1, 2) = 0;
    function(2, 3) = 3;
}
//]

//[test__dfa_build2__function
void build2(Function1& function)
{
    std::vector<std::string> inputs;
    inputs.push_back("alpha");
    inputs.push_back("beta");
    inputs.push_back("gamma");
    inputs.push_back("delta");

    function.reset(4, inputs.begin(), inputs.end());
    function.set_transition(0, "alpha", 1);
    function.set_transition(0, "beta", 1);
    function.set_transition(0, "gamma", 2);
    function(1, "beta") = 2;
    function(1, "gamma") = 0;
    function(2, "delta") = 3;
}
//]

//[test__dfa_build3__function
void build3(Function2& function)
{
    function.reset(4);
    function.set_transition(0, "alpha", 1);
    function.set_transition(0, "beta", 1);
    function.set_transition(0, "gamma", 2);
    function(1, "beta") = 2;
    function(1, "gamma") = 0;
    function(2, "delta") = 3;
}
//]

//[test__dfa_build4__function
void build4(Function3& function)
{
    function.reset(6);
    function.add_transition(0, 1);
    function.add_transition(0, 2);
    function.add_transition(0, 4);
    function.add_transition(1, 0);
    function.add_transition(1, 2);
    function.add_transition(1, 3);
    function.add_transition(2, 3);
    function(2) += 4;
    function(3) += 0;
    function(3) += 1;
    function(3) += 2;
    function(4) += 0;
    function(4) += 3;
    function(4) += 5;
}
//]

