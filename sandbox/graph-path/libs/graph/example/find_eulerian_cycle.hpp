// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_EXAMPLE_FIND_EULERIAN_CYCLE_HPP
#define LIBS_GRAPH_EXAMPLE_FIND_EULERIAN_CYCLE_HPP

#include <iostream>
#include <iterator>
#include <list>
#include <utility>
#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/simple_edge_writer.hpp>
#include <boost/graph/has_eulerian_cycle.hpp>
#include <boost/graph/find_eulerian_cycle.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/fusion/container/generation/make_list.hpp>
#include <boost/graph/fuse_property_writer.hpp>
#endif

#include "../test/initialize_complete_graph.hpp"

//[find_eulerian_cycle_example_with_visitor_list
template <typename Graph>
void find_eulerian_cycle_example_with_visitor_list(std::size_t vertex_count)
{
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;
    typedef typename boost::property_traits<VertexIndexMap>::value_type
            VertexIndex;
    typedef std::list<typename boost::graph_traits<Graph>::edge_descriptor>
            EdgeList;

    Graph          g(vertex_count);
    VertexIndexMap i_map = boost::get(boost::vertex_index, g);

    initialize_complete_graph(g);
    std::cout << "Graph:" << std::endl;
    boost::print_graph(g);
    std::cout << std::endl;

    if (boost::has_eulerian_cycle(g))
    {
        EdgeList path;

        boost::find_eulerian_cycle(
            g
          , std::back_inserter(path)
//<-
#if defined BOOST_MSVC
          , boost::graph::keywords::_visitor = std::make_pair(
#else
//->
          , std::make_pair(
//<-
#endif
//->
                boost::write_property(
                    i_map
                  , std::ostream_iterator<
                        VertexIndex
                    >(std::cout, " initialized...\t")
                  , boost::on_initialize_vertex()
                )
              , std::make_pair(
                    boost::write_property(
                        i_map
                      , std::ostream_iterator<
                            VertexIndex
                        >(std::cout, " started...\t")
                      , boost::on_start_vertex()
                    )
                  , std::make_pair(
                        boost::write_property(
                            i_map
                          , std::ostream_iterator<
                                VertexIndex
                            >(std::cout, " finished.\t")
                          , boost::on_finish_vertex()
                        )
                      , boost::make_simple_edge_writer(
                            i_map
                          , std::cout
                          , " examined...\t"
                          , boost::on_examine_edge()
                        )
                    )
                )
            )
        );
        std::cout << std::endl;

        for (
            typename EdgeList::const_iterator itr = path.begin();
            itr != path.end();
            ++itr
        )
        {
            std::cout << '\t' << boost::get(i_map, boost::source(*itr, g));
            std::cout << " --> " << boost::get(i_map, boost::target(*itr, g));
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "...has no Eulerian cycle." << std::endl;
    }
}
//]

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[find_eulerian_cycle_example_with_fusion_visitor_list
template <typename Graph>
void
    find_eulerian_cycle_example_with_fusion_visitor_list(
        std::size_t vertex_count
    )
{
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;
    typedef typename boost::property_traits<VertexIndexMap>::value_type
            VertexIndex;
    typedef std::list<typename boost::graph_traits<Graph>::edge_descriptor>
            EdgeList;

    Graph          g(vertex_count);
    VertexIndexMap i_map = boost::get(boost::vertex_index, g);

    initialize_complete_graph(g);
    std::cout << "Graph:" << std::endl;
    boost::print_graph(g);
    std::cout << std::endl;

    if (boost::has_eulerian_cycle(g))
    {
        EdgeList path;

        boost::find_eulerian_cycle(
            g
          , boost::graph::keywords::_visitor = boost::fusion::make_list(
                boost::fuse_property_writer<boost::on_initialize_vertex>(
                    i_map
                  , std::ostream_iterator<
                        VertexIndex
                    >(std::cout, " initialized...\t")
                )
              , boost::fuse_property_writer<boost::on_start_vertex>(
                    i_map
                  , std::ostream_iterator<
                        VertexIndex
                    >(std::cout, " started...\t")
                )
              , boost::fuse_property_writer<boost::on_finish_vertex>(
                    i_map
                  , std::ostream_iterator<
                        VertexIndex
                    >(std::cout, " finished.\t")
                )
              , boost::fuse_simple_edge_writer<boost::on_examine_edge>(
                    i_map
                  , std::cout
                  , " examined...\t"
                )
            )
          , boost::graph::keywords::_result = std::back_inserter(path)
        );
        std::cout << std::endl;

        for (
            typename EdgeList::const_iterator itr = path.begin();
            itr != path.end();
            ++itr
        )
        {
            std::cout << '\t' << boost::get(i_map, boost::source(*itr, g));
            std::cout << " --> " << boost::get(i_map, boost::target(*itr, g));
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "...has no Eulerian cycle." << std::endl;
    }
}
//]

#endif  // !BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template <typename EdgeContainerSelector>
void vec_adjacency_list_example(std::size_t vertex_count)
{
    typedef boost::adjacency_list<
                EdgeContainerSelector
              , boost::vecS
              , boost::undirectedS
            >
            UndirectedGraph;
    typedef boost::adjacency_list<
                EdgeContainerSelector
              , boost::vecS
              , boost::bidirectionalS
            >
            BidirectionalGraph;
    typedef boost::adjacency_list<
                EdgeContainerSelector
              , boost::vecS
              , boost::directedS
            >
            DirectedGraph;

    std::cout << std::endl << std::endl;
    std::cout << "Running find_eulerian_cycle algorithm on " << vertex_count;
    std::cout << "-vertex complete undirected graph." << std::endl;
    std::cout << std::endl;
    find_eulerian_cycle_example_with_visitor_list<UndirectedGraph>(
        vertex_count
    );
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    std::cout << std::endl;
    find_eulerian_cycle_example_with_fusion_visitor_list<UndirectedGraph>(
        vertex_count
    );
#endif

    std::cout << std::endl << std::endl;
    std::cout << "Running find_eulerian_cycle algorithm on " << vertex_count;
    std::cout << "-vertex complete directed graph." << std::endl << std::endl;
    find_eulerian_cycle_example_with_visitor_list<DirectedGraph>(
        vertex_count
    );
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    std::cout << std::endl;
    find_eulerian_cycle_example_with_fusion_visitor_list<DirectedGraph>(
        vertex_count
    );
#endif

    std::cout << std::endl << std::endl;
    std::cout << "Running find_eulerian_cycle algorithm on " << vertex_count;
    std::cout << "-vertex complete bidirectional graph." << std::endl;
    std::cout << std::endl;
    find_eulerian_cycle_example_with_visitor_list<BidirectionalGraph>(
        vertex_count
    );
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    std::cout << std::endl;
    find_eulerian_cycle_example_with_fusion_visitor_list<BidirectionalGraph>(
        vertex_count
    );
#endif
}

#endif  // LIBS_GRAPH_EXAMPLE_FIND_EULERIAN_CYCLE_HPP

