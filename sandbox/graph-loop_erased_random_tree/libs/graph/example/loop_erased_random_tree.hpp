// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_EXAMPLE_LOOP_ERASED_RANDOM_TREE_HPP
#define LIBS_GRAPH_EXAMPLE_LOOP_ERASED_RANDOM_TREE_HPP

// maximum number of named arguments in a function
//#define BOOST_PARAMETER_MAX_ARITY 8

// std::cout and std::endl
#include <iostream>
// std::ostream_iterator
#include <iterator>
// std::make_pair
#include <utility>
// boost::fusion::make_list
#include <boost/fusion/container/generation/make_list.hpp>
// boost::property_traits, boost::get, and boost::put
#include <boost/property_map/property_map.hpp>
// boost::graph_traits
#include <boost/graph/graph_traits.hpp>
// boost::property_map and vertex and edge property tags
#include <boost/graph/properties.hpp>
// boost::write_property and event visitor filters
#include <boost/graph/visitors.hpp>
// boost::bidirectionalS, boost::directedS, and boost::undirectedS
#include <boost/graph/graph_selectors.hpp>
// boost::adjacency_list and associated functions
#include <boost/graph/adjacency_list.hpp>
// boost::print_graph
#include <boost/graph/graph_utility.hpp>
// boost::vertex_property_map_gen
#include <boost/graph/vertex_property_map_gen.hpp>
// boost::fuse_property_writer
#include <boost/graph/fuse_property_writer.hpp>
// boost::make_simple_edge_writer and boost::fuse_simple_edge_writer
#include <boost/graph/simple_edge_writer.hpp>
// boost::loop_erased_random_tree
#include <boost/graph/loop_erased_random_tree.hpp>

template <typename Graph>
void initialize_graph(Graph& g)
{
    boost::add_edge(boost::vertex(0, g), boost::vertex(7, g), g);
    boost::add_edge(boost::vertex(1, g), boost::vertex(2, g), g);
    boost::add_edge(boost::vertex(2, g), boost::vertex(10, g), g);
    boost::add_edge(boost::vertex(2, g), boost::vertex(5, g), g);
    boost::add_edge(boost::vertex(3, g), boost::vertex(10, g), g);
    boost::add_edge(boost::vertex(3, g), boost::vertex(0, g), g);
    boost::add_edge(boost::vertex(4, g), boost::vertex(5, g), g);
    boost::add_edge(boost::vertex(4, g), boost::vertex(0, g), g);
    boost::add_edge(boost::vertex(5, g), boost::vertex(14, g), g);
    boost::add_edge(boost::vertex(6, g), boost::vertex(3, g), g);
    boost::add_edge(boost::vertex(7, g), boost::vertex(17, g), g);
    boost::add_edge(boost::vertex(7, g), boost::vertex(11, g), g);
    boost::add_edge(boost::vertex(8, g), boost::vertex(17, g), g);
    boost::add_edge(boost::vertex(8, g), boost::vertex(1, g), g);
    boost::add_edge(boost::vertex(9, g), boost::vertex(11, g), g);
    boost::add_edge(boost::vertex(9, g), boost::vertex(1, g), g);
    boost::add_edge(boost::vertex(10, g), boost::vertex(19, g), g);
    boost::add_edge(boost::vertex(10, g), boost::vertex(15, g), g);
    boost::add_edge(boost::vertex(10, g), boost::vertex(8, g), g);
    boost::add_edge(boost::vertex(11, g), boost::vertex(19, g), g);
    boost::add_edge(boost::vertex(11, g), boost::vertex(15, g), g);
    boost::add_edge(boost::vertex(11, g), boost::vertex(4, g), g);
    boost::add_edge(boost::vertex(12, g), boost::vertex(19, g), g);
    boost::add_edge(boost::vertex(12, g), boost::vertex(8, g), g);
    boost::add_edge(boost::vertex(12, g), boost::vertex(4, g), g);
    boost::add_edge(boost::vertex(13, g), boost::vertex(15, g), g);
    boost::add_edge(boost::vertex(13, g), boost::vertex(8, g), g);
    boost::add_edge(boost::vertex(13, g), boost::vertex(4, g), g);
    boost::add_edge(boost::vertex(14, g), boost::vertex(22, g), g);
    boost::add_edge(boost::vertex(14, g), boost::vertex(12, g), g);
    boost::add_edge(boost::vertex(15, g), boost::vertex(22, g), g);
    boost::add_edge(boost::vertex(15, g), boost::vertex(6, g), g);
    boost::add_edge(boost::vertex(16, g), boost::vertex(12, g), g);
    boost::add_edge(boost::vertex(16, g), boost::vertex(6, g), g);
    boost::add_edge(boost::vertex(17, g), boost::vertex(20, g), g);
    boost::add_edge(boost::vertex(18, g), boost::vertex(9, g), g);
    boost::add_edge(boost::vertex(19, g), boost::vertex(23, g), g);
    boost::add_edge(boost::vertex(19, g), boost::vertex(18, g), g);
    boost::add_edge(boost::vertex(20, g), boost::vertex(23, g), g);
    boost::add_edge(boost::vertex(20, g), boost::vertex(13, g), g);
    boost::add_edge(boost::vertex(21, g), boost::vertex(18, g), g);
    boost::add_edge(boost::vertex(21, g), boost::vertex(13, g), g);
    boost::add_edge(boost::vertex(22, g), boost::vertex(21, g), g);
    boost::add_edge(boost::vertex(23, g), boost::vertex(16, g), g);
}

//[loop_erased_random_tree_example_with_visitor_list
template <typename Graph, typename RNGEngine>
void loop_erased_random_tree_example_with_visitor_list()
{
    typedef typename boost::graph_traits<Graph>::vertex_iterator
            VertexIterator;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor
            Vertex;
    typedef typename boost::vertex_property_map_gen<Graph,Vertex>::type
            PredecessorMap;
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;
    typedef typename boost::property_traits<VertexIndexMap>::value_type
            VertexIndex;

    Graph          g(24);
    VertexIterator vi, vi_end;
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    initialize_graph(g);
    std::cout << "Graph:" << std::endl;
    boost::print_graph(g);

    for (;;)
    {
        std::cout << std::endl << std::endl;

        if (
#ifdef BOOST_GRAPH_LOOP_ERASED_RANDOM_TREE_TAKES_ALL_PARAMS
            boost::loop_erased_random_tree(
                g
              , engine
              , pred_map
              , boost::graph::keywords::_visitor = std::make_pair(
                    boost::write_property(
                        index_map
                      , std::ostream_iterator<
                            VertexIndex
                        >(std::cout, " initialized...\t")
                      , boost::on_initialize_vertex()
                    )
                  , std::make_pair(
                        boost::write_property(
                            index_map
                          , std::ostream_iterator<
                                VertexIndex
                            >(std::cout, " started...\t")
                          , boost::on_start_vertex()
                        )
                      , std::make_pair(
                            boost::write_property(
                                index_map
                              , std::ostream_iterator<
                                    VertexIndex
                                >(std::cout, " discovered...\t")
                              , boost::on_discover_vertex()
                            )
                          , std::make_pair(
                                boost::write_property(
                                    index_map
                                  , std::ostream_iterator<
                                        VertexIndex
                                    >(std::cout, " examined...\t")
                                  , boost::on_examine_vertex()
                                )
                              , std::make_pair(
                                    boost::write_property(
                                        index_map
                                      , std::ostream_iterator<
                                            VertexIndex
                                        >(std::cout, " erased from loop.\t")
                                      , boost::on_loop_erased_vertex()
                                    )
                                  , std::make_pair(
                                        boost::write_property(
                                            index_map
                                          , std::ostream_iterator<
                                                VertexIndex
                                            >(std::cout," finished.\t")
                                          , boost::on_finish_vertex()
                                        )
                                      , std::make_pair(
                                            boost::make_simple_edge_writer(
                                                index_map
                                              , std::cout
                                              , " examined...\t"
                                              , boost::on_examine_edge()
                                            )
                                          , std::make_pair(
                                                boost::make_simple_edge_writer(
                                                    index_map
                                                  , std::cout
                                                  , " is a tree edge.\t"
                                                  , boost::on_tree_edge()
                                                )
                                              , boost::make_simple_edge_writer(
                                                    index_map
                                                  , std::cout
                                                  , " leads to a loop.\t"
                                                  , boost::on_back_edge()
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
#else  // !def BOOST_GRAPH_LOOP_ERASED_RANDOM_TREE_TAKES_ALL_PARAMS
            boost::loop_erased_random_tree(
              g
             ,boost::make_loop_erased_random_tree_params().rng_engine(
                engine
              ).predecessor_map(
                pred_map
              ).visitor(
                std::make_pair(
                    boost::write_property(
                        index_map
                      , std::ostream_iterator<
                            VertexIndex
                        >(std::cout, " initialized...\t")
                      , boost::on_initialize_vertex()
                    )
                  , std::make_pair(
                        boost::write_property(
                            index_map
                          , std::ostream_iterator<
                                VertexIndex
                            >(std::cout, " started...\t")
                          , boost::on_start_vertex()
                        )
                      , std::make_pair(
                            boost::write_property(
                                index_map
                              , std::ostream_iterator<
                                    VertexIndex
                                >(std::cout, " discovered...\t")
                              , boost::on_discover_vertex()
                            )
                          , std::make_pair(
                                boost::write_property(
                                    index_map
                                  , std::ostream_iterator<
                                        VertexIndex
                                    >(std::cout, " examined...\t")
                                  , boost::on_examine_vertex()
                                )
                              , std::make_pair(
                                    boost::write_property(
                                        index_map
                                      , std::ostream_iterator<
                                            VertexIndex
                                        >(std::cout, " erased from loop.\t")
                                      , boost::on_loop_erased_vertex()
                                    )
                                  , std::make_pair(
                                        boost::write_property(
                                            index_map
                                          , std::ostream_iterator<
                                                VertexIndex
                                            >(std::cout," finished.\t")
                                          , boost::on_finish_vertex()
                                        )
                                      , std::make_pair(
                                            boost::make_simple_edge_writer(
                                                index_map
                                              , std::cout
                                              , " examined...\t"
                                              , boost::on_examine_edge()
                                            )
                                          , std::make_pair(
                                                boost::make_simple_edge_writer(
                                                    index_map
                                                  , std::cout
                                                  , " is a tree edge.\t"
                                                  , boost::on_tree_edge()
                                                )
                                              , boost::make_simple_edge_writer(
                                                    index_map
                                                  , std::cout
                                                  , " leads to a loop.\t"
                                                  , boost::on_back_edge()
                                                )
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
              )
            )
#endif  // BOOST_GRAPH_LOOP_ERASED_RANDOM_TREE_TAKES_ALL_PARAMS
        )
        {
            std::cout << "  Done!" << std::endl << "Successors:" << std::endl;

            for (
                boost::tie(vi, vi_end) = boost::vertices(g);
                vi != vi_end;
                ++vi
            )
            {
                std::cout << '\t' << boost::get(index_map, *vi) << " --> ";
                std::cout << boost::get(index_map, boost::get(pred_map, *vi));
                std::cout << std::endl;
            }

            break;
        }

        std::cout << std::endl << "Trying again...";
    }
}
//]

//[loop_erased_random_tree_example_with_fusion_visitor_list
template <typename Graph, typename RNGEngine>
void
    loop_erased_random_tree_example_with_fusion_visitor_list(
        std::size_t root_index
    )
{
    typedef typename boost::graph_traits<Graph>::vertex_iterator
            VertexIterator;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor
            Vertex;
    typedef typename boost::vertex_property_map_gen<Graph,Vertex>::type
            PredecessorMap;
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;
    typedef typename boost::property_traits<VertexIndexMap>::value_type
            VertexIndex;

    Graph          g(24);
    VertexIterator vi, vi_end;
    Vertex         root = boost::vertex(root_index, g);
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    initialize_graph(g);
    std::cout << std::endl << "Target = " << boost::get(index_map, root);
    std::cout << ", Graph:" << std::endl;
    boost::print_graph(g);

    for (;;)
    {
        std::cout << std::endl << std::endl;

        if (
#ifdef BOOST_GRAPH_LOOP_ERASED_RANDOM_TREE_TAKES_ALL_PARAMS
            boost::loop_erased_random_tree(
                g
              , engine
              , pred_map
              , root
              , boost::graph::keywords::_visitor = boost::fusion::make_list(
                    boost::fuse_property_writer<boost::on_initialize_vertex>(
                        index_map
                      , std::ostream_iterator<
                            VertexIndex
                        >(std::cout, " initialized...\t")
                    )
                  , boost::fuse_property_writer<boost::on_start_vertex>(
                        index_map
                      , std::ostream_iterator<
                            VertexIndex
                        >(std::cout, " started...\t")
                    )
                  , boost::fuse_property_writer<boost::on_discover_vertex>(
                        index_map
                      , std::ostream_iterator<
                            VertexIndex
                        >(std::cout, " discovered...\t")
                    )
                  , boost::fuse_property_writer<boost::on_examine_vertex>(
                        index_map
                      , std::ostream_iterator<
                            VertexIndex
                        >(std::cout, " examined...\t")
                    )
                  , boost::fuse_property_writer<boost::on_loop_erased_vertex>(
                        index_map
                      , std::ostream_iterator<
                            VertexIndex
                        >(std::cout, " erased from loop.\t")
                    )
                  , boost::fuse_property_writer<boost::on_finish_vertex>(
                        index_map
                      , std::ostream_iterator<
                            VertexIndex
                        >(std::cout, " finished.\t")
                    )
                  , boost::fuse_simple_edge_writer<boost::on_examine_edge>(
                        index_map
                      , std::cout
                      , " examined...\t"
                    )
                  , boost::fuse_simple_edge_writer<boost::on_tree_edge>(
                        index_map
                      , std::cout
                      , " examined...\t"
                    )
                  , boost::fuse_simple_edge_writer<boost::on_back_edge>(
                        index_map
                      , std::cout
                      , " leads to a loop.\t"
                    )
                )
            )
#else  // !def BOOST_GRAPH_LOOP_ERASED_RANDOM_TREE_TAKES_ALL_PARAMS
            boost::loop_erased_random_tree(
                g
              , boost::make_loop_erased_random_tree_params().rng_engine(
                    engine
                ).source_vertex(
                    root
                ).predecessor_map(
                    pred_map
                ).visitor(
                    boost::fusion::make_list(
                        boost::fuse_property_writer<
                            boost::on_initialize_vertex
                        >(
                            index_map
                          , std::ostream_iterator<
                                VertexIndex
                            >(std::cout, " initialized...\t")
                        )
                      , boost::fuse_property_writer<boost::on_start_vertex>(
                            index_map
                          , std::ostream_iterator<
                                VertexIndex
                            >(std::cout, " started...\t")
                        )
                      , boost::fuse_property_writer<boost::on_discover_vertex>(
                            index_map
                          , std::ostream_iterator<
                                VertexIndex
                            >(std::cout, " discovered...\t")
                        )
                      , boost::fuse_property_writer<boost::on_examine_vertex>(
                            index_map
                          , std::ostream_iterator<
                                VertexIndex
                            >(std::cout, " examined...\t")
                        )
                      , boost::fuse_property_writer<
                            boost::on_loop_erased_vertex
                        >(
                            index_map
                          , std::ostream_iterator<
                                VertexIndex
                            >(std::cout, " erased from loop.\t")
                        )
                      , boost::fuse_property_writer<boost::on_finish_vertex>(
                            index_map
                          , std::ostream_iterator<
                                VertexIndex
                            >(std::cout, " finished.\t")
                        )
                      , boost::fuse_simple_edge_writer<boost::on_examine_edge>(
                            index_map
                          , std::cout
                          , " examined...\t"
                        )
                      , boost::fuse_simple_edge_writer<boost::on_tree_edge>(
                            index_map
                          , std::cout
                          , " examined...\t"
                        )
                      , boost::fuse_simple_edge_writer<boost::on_back_edge>(
                            index_map
                          , std::cout
                          , " leads to a loop.\t"
                        )
                    )
                )
            )
#endif  // BOOST_GRAPH_LOOP_ERASED_RANDOM_TREE_TAKES_ALL_PARAMS
        )
        {
            std::cout << "  Done!" << std::endl << "Successors:" << std::endl;

            for (
                boost::tie(vi, vi_end) = boost::vertices(g);
                vi != vi_end;
                ++vi
            )
            {
                std::cout << '\t' << boost::get(index_map, *vi) << " --> ";
                std::cout << boost::get(index_map, boost::get(pred_map, *vi));
                std::cout << std::endl;
            }

            break;
        }

        std::cout << std::endl << "Trying again...";
    }
}
//]

//[loop_erased_random_tree_example
template <typename Graph, typename RNGEngine>
void loop_erased_random_tree_example(unsigned int num_runs)
{
    typedef typename boost::graph_traits<Graph>::vertex_descriptor
            Vertex;
    typedef typename boost::graph_traits<Graph>::vertex_iterator
            VertexIterator;
    typedef typename boost::vertex_property_map_gen<Graph,Vertex>::type
            PredecessorMap;
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;

    Graph          g(24);
    VertexIterator vi, vi_end;
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    initialize_graph(g);
    std::cout << std::endl << "Graph:" << std::endl;
    boost::print_graph(g);

    while (num_runs)
    {
        if (boost::loop_erased_random_tree(g, engine, pred_map))
        {
            std::cout << std::endl << "Successors:" << std::endl;

            for (
                boost::tie(vi, vi_end) = boost::vertices(g);
                vi != vi_end;
                ++vi
            )
            {
                std::cout << '\t' << boost::get(index_map, *vi) << " --> ";
                std::cout << boost::get(index_map, boost::get(pred_map, *vi));
                std::cout << std::endl;
            }

            --num_runs;
        }
    }
}
//]

//[loop_erased_random_tree_with_source_example
template <typename Graph, typename RNGEngine>
void
    loop_erased_random_tree_with_source_example(
        std::size_t const root_index
      , unsigned int num_runs
    )
{
    typedef typename boost::graph_traits<Graph>::vertex_descriptor
            Vertex;
    typedef typename boost::graph_traits<Graph>::vertex_iterator
            VertexIterator;
    typedef typename boost::vertex_property_map_gen<Graph,Vertex>::type
            PredecessorMap;
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;

    Graph          g(24);
    Vertex         root = boost::vertex(root_index, g);
    VertexIterator vi, vi_end;
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    initialize_graph(g);
    std::cout << std::endl << "Source = " << boost::get(index_map, root);
    std::cout << ", Graph:" << std::endl;
    boost::print_graph(g);

    while (num_runs)
    {
        if (
            boost::loop_erased_random_tree(
                g
              , engine
              , pred_map
              , boost::graph::keywords::_source_vertex = root
            )
        )
        {
            std::cout << std::endl << "Predecessors:" << std::endl;

            for (
                boost::tie(vi, vi_end) = boost::vertices(g);
                vi != vi_end;
                ++vi
            )
            {
                std::cout << '\t' << boost::get(index_map, *vi) << " <-- ";
                std::cout << boost::get(index_map, boost::get(pred_map, *vi));
                std::cout << std::endl;
            }

            --num_runs;
        }
    }
}
//]

//[loop_erased_random_tree_with_target_example
template <typename Graph, typename RNGEngine>
void
    loop_erased_random_tree_with_target_example(
        std::size_t const root_index
      , unsigned int num_runs
    )
{
    typedef typename boost::graph_traits<Graph>::vertex_descriptor
            Vertex;
    typedef typename boost::graph_traits<Graph>::vertex_iterator
            VertexIterator;
    typedef typename boost::vertex_property_map_gen<Graph,Vertex>::type
            PredecessorMap;
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;

    Graph          g(24);
    Vertex         root = boost::vertex(root_index, g);
    VertexIterator vi, vi_end;
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    initialize_graph(g);
    std::cout << std::endl << "Target = " << boost::get(index_map, root);
    std::cout << ", Graph:" << std::endl;
    boost::print_graph(g);

    while (num_runs)
    {
        if (boost::loop_erased_random_tree(g, engine, pred_map, root))
        {
            std::cout << std::endl << "Successors:" << std::endl;

            for (
                boost::tie(vi, vi_end) = boost::vertices(g);
                vi != vi_end;
                ++vi
            )
            {
                std::cout << '\t' << boost::get(index_map, *vi) << " --> ";
                std::cout << boost::get(index_map, boost::get(pred_map, *vi));
                std::cout << std::endl;
            }

            --num_runs;
        }
    }
}
//]

//[loop_erased_random_path_example
template <typename Graph, typename RNGEngine>
void
    loop_erased_random_path_example(
        std::size_t const start_index
      , std::size_t const end_index
      , unsigned int num_runs
    )
{
    typedef typename boost::graph_traits<Graph>::vertex_descriptor
            Vertex;
    typedef typename boost::vertex_property_map_gen<Graph,Vertex>::type
            PredecessorMap;
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;

    Graph          g(24);
    Vertex         start = boost::vertex(start_index, g);
    Vertex         end = boost::vertex(end_index, g);
    Vertex         v;
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    initialize_graph(g);
    std::cout << std::endl << "Start = " << boost::get(index_map, start);
    std::cout << ", End = " << boost::get(index_map, end);
    std::cout << ", Graph:" << std::endl;
    boost::print_graph(g);

    while (num_runs)
    {
        if (boost::loop_erased_random_tree(g, engine, pred_map, end, start))
        {
            std::cout << "Path: " << boost::get(index_map, v = start);

            while (v != end)
            {
                v = boost::get(pred_map, v);
                std::cout << " -> " << boost::get(index_map, v);
            }

            std::cout << std::endl;
            --num_runs;
        }
    }
}
//]

template <typename EdgeContainerSelector, typename RNGEngine>
void
    vec_adjacency_list_example(
        unsigned int const start_index
      , unsigned int const end_index
      , unsigned int const num_runs
    )
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

    std::cout << "Running loop_erased_random_tree function template on ";
    std::cout << "undirected graph." << std::endl;
    loop_erased_random_tree_example_with_visitor_list<
        UndirectedGraph
      , RNGEngine
    >();
    loop_erased_random_tree_example_with_fusion_visitor_list<
        UndirectedGraph
      , RNGEngine
    >(end_index);
    loop_erased_random_tree_example<UndirectedGraph,RNGEngine>(num_runs);
    loop_erased_random_tree_with_source_example<
        UndirectedGraph
      , RNGEngine
    >(start_index, num_runs);
    loop_erased_random_tree_with_target_example<
        UndirectedGraph
      , RNGEngine
    >(end_index, num_runs);
    loop_erased_random_path_example<
        UndirectedGraph
      , RNGEngine
    >(start_index, end_index, num_runs);
    std::cout << std::endl << std::endl;

    std::cout << "Running loop_erased_random_tree function template on ";
    std::cout << "directed graph." << std::endl;
    loop_erased_random_tree_example_with_visitor_list<
        DirectedGraph
      , RNGEngine
    >();
    loop_erased_random_tree_example_with_fusion_visitor_list<
        DirectedGraph
      , RNGEngine
    >(end_index);
    loop_erased_random_tree_example<DirectedGraph,RNGEngine>(num_runs);
    loop_erased_random_tree_with_source_example<
        DirectedGraph
      , RNGEngine
    >(start_index, num_runs);
    loop_erased_random_tree_with_target_example<
        DirectedGraph
      , RNGEngine
    >(end_index, num_runs);
    loop_erased_random_path_example<
        DirectedGraph
      , RNGEngine
    >(start_index, end_index, num_runs);
    std::cout << std::endl << std::endl;

    std::cout << "Running loop_erased_random_tree function template on ";
    std::cout << "bidirectional graph." << std::endl;
    loop_erased_random_tree_example_with_visitor_list<
        BidirectionalGraph
      , RNGEngine
    >();
    loop_erased_random_tree_example_with_fusion_visitor_list<
        BidirectionalGraph
      , RNGEngine
    >(end_index);
    loop_erased_random_tree_example<BidirectionalGraph,RNGEngine>(num_runs);
    loop_erased_random_tree_with_source_example<
        BidirectionalGraph
      , RNGEngine
    >(start_index, num_runs);
    loop_erased_random_tree_with_target_example<
        BidirectionalGraph
      , RNGEngine
    >(end_index, num_runs);
    loop_erased_random_path_example<
        BidirectionalGraph
      , RNGEngine
    >(start_index, end_index, num_runs);
}

#endif  // LIBS_GRAPH_EXAMPLE_LOOP_ERASED_RANDOM_TREE_HPP

