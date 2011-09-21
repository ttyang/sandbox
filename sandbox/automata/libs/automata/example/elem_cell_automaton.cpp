// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/generate.hpp>
#include <boost/tr1/random.hpp>
#include <boost/automata/generator/deterministic.hpp>
#include <boost/automata/transition_function/input_rule.hpp>
#include <boost/automata/input_rule/wolfram_code.hpp>
#include <boost/automata/automaton.hpp>

//[example__elementary_cellular_automaton__builders
typedef std::deque<unsigned char> State;

void build_one(State& state)
{
    state.clear();
    state.push_back('1');
}

void build_from_rng(State& state)
{
    typedef std::tr1::minstd_rand Engine;
    typedef std::tr1::uniform_int<unsigned char> Distribution;

    Engine engine;
    std::tr1::variate_generator<Engine&,Distribution> cg(
        engine
      , Distribution('0', '1')
    );

    state.resize(64);
    boost::range::generate(state, cg);
}
//]

//[example__elementary_cellular_automaton__typedefs
typedef boost::automata::wolfram_code_input_rule<unsigned char>
        Rule;
typedef boost::automata::automaton<
            boost::automata::deterministic_generator
          , boost::automata::input_rule_transition_function<State>
        >
        CA;
//]

//[example__elementary_cellular_automaton__run
typedef std::ostream_iterator<unsigned char>
        OutIterator;

void
    run(
        CA& ca
      , Rule const& rule
      , OutIterator& out_itr
      , std::size_t const count
      , bool const triangle_format
    )
{
    if (triangle_format)
    {
        std::fill_n(out_itr, count + 1, ' ');
    }

    boost::range::copy(ca.get_current_state(), out_itr);
    std::cout << std::endl;

    for (std::size_t i = 0; i < count; ++i)
    {
        ca(rule);

        if (triangle_format)
        {
            std::fill_n(out_itr, count - i, ' ');
        }

        boost::range::copy(ca.get_current_state(), out_itr);
        std::cout << std::endl;
    }
}
//]

//[example__elementary_cellular_automaton__main
int main()
{
    Rule rule('0');
    CA ca(build_one);
    OutIterator out_itr(std::cout);

    rule.add_association('0', '0', '1', '1');
    rule.add_association('0', '1', '0', '1');
    rule.add_association('0', '1', '1', '1');
    rule.add_association('1', '0', '0', '1');
    std::cout << "Rule 30:" << std::endl;
    run(ca, rule, out_itr, 20, true);

    rule.reset();
    rule('0', '0', '1') = '1';
    rule('0', '1', '1') = '1';
    rule('1', '0', '0') = '1';
    rule('1', '1', '0') = '1';
    ca.reset();
    std::cout << std::endl << "Rule 90:" << std::endl;
    run(ca, rule, out_itr, 31, true);

    rule.reset();
    rule('0', '1', '0') = '1';
    rule('1', '1', '0') = '1';
    rule('0', '0', '1') = '1';
    rule('1', '0', '1') = '1';
    rule('0', '1', '1') = '1';
    ca.reset();
    std::cout << std::endl << "Rule 124:" << std::endl;
    run(ca, rule, out_itr, 45, false);

    rule.reset();
    rule('0', '1', '1') = '1';
    rule('1', '0', '0') = '1';
    rule('1', '0', '1') = '1';
    rule('1', '1', '1') = '1';
    ca.initialize(build_from_rng);
    std::cout << std::endl << "Rule 184:" << std::endl;
    run(ca, rule, out_itr, 28, false);

    return 0;
}
//]

