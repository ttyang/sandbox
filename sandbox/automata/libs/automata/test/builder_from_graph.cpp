// Copyright (C) 2007-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/automata/generator/dpda.hpp>
#include <boost/automata/transition_function/dpda.hpp>
#include <boost/automata/builder/from_graph.hpp>
#include <boost/automata/automaton.hpp>
#include "basics.hpp"

//[test__builder_from_graph__dpda_typedef
using namespace boost;
using namespace automata;

typedef dpda_transition_function<char,char>
        Function;
typedef automaton<dpda_generator,Function>
        DPDA;
//]

//[test__builder_from_graph__graph_typedef
using namespace fusion;

typedef map<
            pair<input_symbol_key,Function::input>
          , pair<pop_from_stack_key,Function::optional_stack_element>
          , pair<push_to_stack_key,Function::optional_stack_element>
        >
        EdgeInput;
typedef adjacency_list<
            vecS
          , vecS  // Let the vertex_index_t property map be built-in.
          , directedS
          , no_property
          , property<edge_input_t,EdgeInput>
        >
        Graph;
//]

//[test__builder_from_graph__builder_typedef
typedef builder_from_graph<
            Graph
          , property_map<Graph,vertex_index_t>::type
          , property_map<Graph,edge_input_t>::type
        >
        Builder;
//]

//[test__builder_from_graph__case0_edge_inputs
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(builder_from_graph_test0)
{
    Function::optional_stack_element
        N;
    Function::optional_stack_element
        S('S');
    EdgeInput
        i0(
            make_pair<input_symbol_key>('a')
          , make_pair<pop_from_stack_key>(N)
          , make_pair<push_to_stack_key>(S)
        );
    EdgeInput
        i1(
            make_pair<input_symbol_key>('b')
          , make_pair<pop_from_stack_key>(S)
          , make_pair<push_to_stack_key>(N)
        );
    //]

    //[test__builder_from_graph__case0_graph
    Graph                                g(2);
    graph_traits<Graph>::edge_descriptor e;
    bool                                 b;

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(0, g), g);
    if (b) put(get(edge_input, g), e, i0);
    boost::tie(e, b) = add_edge(vertex(0, g), vertex(1, g), g);
    if (b) put(get(edge_input, g), e, i1);
    boost::tie(e, b) = add_edge(vertex(1, g), vertex(1, g), g);
    if (b) put(get(edge_input, g), e, i1);
    //]

    //[test__builder_from_graph__case0_dpda
    DPDA dpda(Builder(g, get(vertex_index, g), get(edge_input, g)));
    //]

    //[test__builder_from_graph__case0_run
    BOOST_CHECK(!accept(dpda, "aab"));
    dpda.reset();
    BOOST_CHECK(accept(dpda, "aabb"));
    dpda.reset();
    BOOST_CHECK(!accept(dpda, "aabbb"));
    dpda.reset();
    BOOST_CHECK(accept(dpda, "aaabbb"));
}
//]

//[test__builder_from_graph__case1
BOOST_AUTO_TEST_CASE(builder_from_graph_test1)
{
    Function::optional_stack_element     N;
    Function::optional_stack_element     S('S');
    Function::optional_stack_element     A('A');
    Graph                                g(2);
    graph_traits<Graph>::edge_descriptor e;
    bool                                 b;

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(0, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('(')
              , make_pair<pop_from_stack_key>(N)
              , make_pair<push_to_stack_key>(S)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(0, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('(')
              , make_pair<pop_from_stack_key>(A)
              , make_pair<push_to_stack_key>(S)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(1, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('x')
              , make_pair<pop_from_stack_key>(N)
              , make_pair<push_to_stack_key>(N)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(1, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('x')
              , make_pair<pop_from_stack_key>(A)
              , make_pair<push_to_stack_key>(N)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(1, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('y')
              , make_pair<pop_from_stack_key>(N)
              , make_pair<push_to_stack_key>(N)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(1, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('y')
              , make_pair<pop_from_stack_key>(A)
              , make_pair<push_to_stack_key>(N)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(1, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('z')
              , make_pair<pop_from_stack_key>(N)
              , make_pair<push_to_stack_key>(N)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(1, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('z')
              , make_pair<pop_from_stack_key>(A)
              , make_pair<push_to_stack_key>(N)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(1, g), vertex(1, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>(')')
              , make_pair<pop_from_stack_key>(S)
              , make_pair<push_to_stack_key>(N)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(1, g), vertex(0, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('+')
              , make_pair<pop_from_stack_key>(N)
              , make_pair<push_to_stack_key>(A)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(1, g), vertex(0, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('-')
              , make_pair<pop_from_stack_key>(N)
              , make_pair<push_to_stack_key>(A)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(1, g), vertex(0, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('*')
              , make_pair<pop_from_stack_key>(N)
              , make_pair<push_to_stack_key>(A)
            )
        );
    }

    boost::tie(e, b) = add_edge(vertex(1, g), vertex(0, g), g);

    if (b)
    {
        put(
            get(edge_input, g)
          , e
          , EdgeInput(
                make_pair<input_symbol_key>('/')
              , make_pair<pop_from_stack_key>(N)
              , make_pair<push_to_stack_key>(A)
            )
        );
    }

    DPDA dpda(Builder(get(edge_input, g), g, get(vertex_index, g)));

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
}
//]

//[test__builder_from_graph__case2
BOOST_AUTO_TEST_CASE(builder_from_graph_test2)
{
    Function::optional_stack_element
        N;
    Function::optional_stack_element
        S('S');
    Function::optional_stack_element
        B('B');
    EdgeInput
        iaNS(
            make_pair<input_symbol_key>('a')
          , make_pair<pop_from_stack_key>(N)
          , make_pair<push_to_stack_key>(S)
        );
    EdgeInput
        ibNB(
            make_pair<input_symbol_key>('b')
          , make_pair<pop_from_stack_key>(N)
          , make_pair<push_to_stack_key>(B)
        );
    EdgeInput
        icSN(
            make_pair<input_symbol_key>('c')
          , make_pair<pop_from_stack_key>(S)
          , make_pair<push_to_stack_key>(N)
        );
    EdgeInput
        icBN(
            make_pair<input_symbol_key>('c')
          , make_pair<pop_from_stack_key>(B)
          , make_pair<push_to_stack_key>(N)
        );

    Graph                                g(3);
    graph_traits<Graph>::edge_descriptor e;
    bool                                 b;

    boost::tie(e, b) = add_edge(vertex(0, g), vertex(0, g), g);
    if (b) put(get(edge_input, g), e, iaNS);
    boost::tie(e, b) = add_edge(vertex(0, g), vertex(1, g), g);
    if (b) put(get(edge_input, g), e, ibNB);
    boost::tie(e, b) = add_edge(vertex(0, g), vertex(2, g), g);
    if (b) put(get(edge_input, g), e, icSN);
    boost::tie(e, b) = add_edge(vertex(1, g), vertex(1, g), g);
    if (b) put(get(edge_input, g), e, ibNB);
    boost::tie(e, b) = add_edge(vertex(1, g), vertex(2, g), g);
    if (b) put(get(edge_input, g), e, icBN);
    boost::tie(e, b) = add_edge(vertex(2, g), vertex(2, g), g);
    if (b) put(get(edge_input, g), e, icSN);
    boost::tie(e, b) = add_edge(vertex(2, g), vertex(2, g), g);
    if (b) put(get(edge_input, g), e, icBN);

    DPDA dpda(Builder(get(vertex_index, g), get(edge_input, g), g));

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

