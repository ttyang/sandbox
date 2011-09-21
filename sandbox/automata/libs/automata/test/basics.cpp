// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/automata/generator/dpda.hpp>
#include <boost/automata/automaton.hpp>
#include "basics.hpp"
#include "dpda_builder.hpp"

//[test__basics__case
using namespace boost;
using namespace automata;

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(basics_test)
{
    automaton<dpda_generator,Function> dpda(build1);

    BOOST_CHECK(!accept(dpda, "aab"));
    dpda.reset();
    BOOST_CHECK(accept(dpda, "aabb"));
    dpda.reset();
    BOOST_CHECK(!accept(dpda, "aabbb"));
    dpda.reset();
    BOOST_CHECK(accept(dpda, "aaabbb"));

    dpda.initialize(build2);

    BOOST_CHECK(!accept(dpda, "x+y)"));
    dpda.reset();
    BOOST_CHECK(!accept(dpda, "(x+y"));
    dpda.reset();
    BOOST_CHECK(!accept(dpda, "xy+z"));
    dpda.reset();
    BOOST_CHECK(!accept(dpda, "x(y+z)"));
    dpda.reset();
    BOOST_CHECK(accept(dpda, "(x+y)*x-z*y/(x+x)"));
    dpda.reset();
    BOOST_CHECK(accept(dpda, "x/(y*(z-y)+x)"));

    dpda.initialize(build3);

    BOOST_CHECK(accept(dpda, "aacc"));
    dpda.reset();
    BOOST_CHECK(!accept(dpda, "abc"));
    dpda.reset();
    BOOST_CHECK(accept(dpda, "aabccc"));
    dpda.reset();
    BOOST_CHECK(accept(dpda, "abbccc"));
    dpda.reset();
    BOOST_CHECK(!accept(dpda, "abbcccc"));
    dpda.reset();
    BOOST_CHECK(accept(dpda, "bbbccc"));
}
//]

