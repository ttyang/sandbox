// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/automata/generator/dpda.hpp>
#include <boost/automata/automaton.hpp>
#include "dpda_builder.hpp"

using namespace boost;
using namespace automata;

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(dpda_test)
{
    automaton<dpda_generator,Function> dpda(build1);

    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(!dpda.has_empty_stack());
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda.has_empty_stack());
    BOOST_CHECK(!dpda('b'));

    dpda.reset();

    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda.has_empty_stack());

    dpda.initialize(build2);

    BOOST_CHECK(dpda('x'));
    BOOST_CHECK(!dpda('y'));
    BOOST_CHECK(!dpda('('));
    BOOST_CHECK(dpda('+'));
    BOOST_CHECK(dpda('y'));
    BOOST_CHECK(dpda.has_empty_stack());
    BOOST_CHECK(!dpda(')'));

    dpda.reset();

    BOOST_CHECK(dpda('('));
    BOOST_CHECK(dpda('x'));
    BOOST_CHECK(dpda('+'));
    BOOST_CHECK(dpda('y'));
    BOOST_CHECK(!dpda.has_empty_stack());
    BOOST_CHECK(dpda(')'));
    BOOST_CHECK(dpda('*'));
    BOOST_CHECK(dpda('x'));
    BOOST_CHECK(dpda('-'));
    BOOST_CHECK(dpda('z'));
    BOOST_CHECK(dpda('*'));
    BOOST_CHECK(dpda('y'));
    BOOST_CHECK(dpda('/'));
    BOOST_CHECK(dpda('('));
    BOOST_CHECK(dpda('x'));
    BOOST_CHECK(dpda('+'));
    BOOST_CHECK(dpda('x'));
    BOOST_CHECK(dpda(')'));
    BOOST_CHECK(dpda.has_empty_stack());

    dpda.reset();

    BOOST_CHECK(dpda('x'));
    BOOST_CHECK(dpda('/'));
    BOOST_CHECK(dpda('('));
    BOOST_CHECK(dpda('y'));
    BOOST_CHECK(dpda('*'));
    BOOST_CHECK(dpda('('));
    BOOST_CHECK(dpda('z'));
    BOOST_CHECK(dpda('-'));
    BOOST_CHECK(dpda('y'));
    BOOST_CHECK(dpda(')'));
    BOOST_CHECK(dpda('+'));
    BOOST_CHECK(dpda('x'));
    BOOST_CHECK(dpda(')'));
    BOOST_CHECK(dpda.has_empty_stack());

    dpda.initialize(build3);

    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda.has_empty_stack());

    dpda.reset();

    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(!dpda.has_empty_stack());
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda.has_empty_stack());

    dpda.reset();

    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda.has_empty_stack());

    dpda.reset();

    BOOST_CHECK(dpda('a'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda.has_empty_stack());
    BOOST_CHECK(!dpda('c'));

    dpda.reset();

    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda('b'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda('c'));
    BOOST_CHECK(dpda.has_empty_stack());
}

