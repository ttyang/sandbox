// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/fusion/container/list.hpp>
#include <boost/automata/generator/dpda.hpp>
#include <boost/automata/policy/dpda_insertion.hpp>
#include <boost/automata/automaton.hpp>
#include "../test/dpda_builder.hpp"
#include "dpda.hpp"

using namespace boost;
using namespace automata;
using namespace keyword;

int main()
{
    typedef dpda_insertion_policy<std::ostream,char>
            OutputStreamPolicy;
    typedef fusion::list<OutputStreamPolicy>
            Policies;

    automaton<dpda_generator,Function,Policies>
        dpda(
            build1
          , Policies(
                OutputStreamPolicy(
                    std::cout
                  , "%1%(%5%): current state = %2%; stack = [%3%]; nontrivial inputs = [%4%]"
                  , ','
                )
            )
        );

    test(dpda, "aab");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "aabb");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "aabbb");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "aaabbb");
    std::cout << std::endl;

    dpda.initialize(build2);

    test(dpda, "x+y)");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "(x+y");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "xy+z");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "x(y+z)");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "(x+y)*x-z*y/(x+x)");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "x/(y*(z-y)+x)");
    std::cout << std::endl;

    dpda.initialize(build3);

    test(dpda, "aacc");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "abc");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "aabccc");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "abbccc");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "abbcccc");
    std::cout << std::endl;
    dpda.reset();
    test(dpda, "bbbccc");
    std::cout << std::endl;

    return 0;
}

