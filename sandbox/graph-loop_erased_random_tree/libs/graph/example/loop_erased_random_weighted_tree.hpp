// Copyright (C) 2004-2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_EXAMPLE_LOOP_ERASED_RANDOM_WEIGHTED_TREE_HPP
#define LIBS_GRAPH_EXAMPLE_LOOP_ERASED_RANDOM_WEIGHTED_TREE_HPP

// maximum number of named arguments in a function
//#define BOOST_PARAMETER_MAX_ARITY 11

// std::cout and std::endl
#include <iostream>
// std::ostream_iterator
#include <iterator>
// std::make_pair
#include <utility>
// std::tr1::tie
#include <boost/tr1/tuple.hpp>
// std::tr1::uniform_real and std::tr1::variate_generator
#include <boost/tr1/random.hpp>
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
// boost::loop_erased_random_weighted_tree
#include <boost/graph/loop_erased_random_weighted_tree.hpp>

template <typename Graph, typename WeightGen>
void
    add_edge_with_random_weight(
        Graph& g
      , WeightGen& weight_gen
      , std::size_t source_index
      , std::size_t target_index
    )
{
    typename boost::graph_traits<Graph>::edge_descriptor e;
    bool b;

    std::tr1::tie(e, b) = boost::add_edge(
        boost::vertex(source_index, g)
      , boost::vertex(target_index, g)
      , g
    );

    if (b)
    {
        boost::put(boost::edge_weight, g, e, weight_gen());
    }
}

template <typename Graph, typename WeightGen>
void initialize_graph(Graph& g, WeightGen& weight_gen)
{
    add_edge_with_random_weight(g, weight_gen, 0, 7);
    add_edge_with_random_weight(g, weight_gen, 1, 2);
    add_edge_with_random_weight(g, weight_gen, 2, 10);
    add_edge_with_random_weight(g, weight_gen, 2, 5);
    add_edge_with_random_weight(g, weight_gen, 3, 10);
    add_edge_with_random_weight(g, weight_gen, 3, 0);
    add_edge_with_random_weight(g, weight_gen, 4, 5);
    add_edge_with_random_weight(g, weight_gen, 4, 0);
    add_edge_with_random_weight(g, weight_gen, 5, 14);
    add_edge_with_random_weight(g, weight_gen, 6, 3);
    add_edge_with_random_weight(g, weight_gen, 7, 17);
    add_edge_with_random_weight(g, weight_gen, 7, 11);
    add_edge_with_random_weight(g, weight_gen, 8, 17);
    add_edge_with_random_weight(g, weight_gen, 8, 1);
    add_edge_with_random_weight(g, weight_gen, 9, 11);
    add_edge_with_random_weight(g, weight_gen, 9, 1);
    add_edge_with_random_weight(g, weight_gen, 10, 19);
    add_edge_with_random_weight(g, weight_gen, 10, 15);
    add_edge_with_random_weight(g, weight_gen, 10, 8);
    add_edge_with_random_weight(g, weight_gen, 11, 19);
    add_edge_with_random_weight(g, weight_gen, 11, 15);
    add_edge_with_random_weight(g, weight_gen, 11, 4);
    add_edge_with_random_weight(g, weight_gen, 12, 19);
    add_edge_with_random_weight(g, weight_gen, 12, 8);
    add_edge_with_random_weight(g, weight_gen, 12, 4);
    add_edge_with_random_weight(g, weight_gen, 13, 15);
    add_edge_with_random_weight(g, weight_gen, 13, 8);
    add_edge_with_random_weight(g, weight_gen, 13, 4);
    add_edge_with_random_weight(g, weight_gen, 14, 22);
    add_edge_with_random_weight(g, weight_gen, 14, 12);
    add_edge_with_random_weight(g, weight_gen, 15, 22);
    add_edge_with_random_weight(g, weight_gen, 15, 6);
    add_edge_with_random_weight(g, weight_gen, 16, 12);
    add_edge_with_random_weight(g, weight_gen, 16, 6);
    add_edge_with_random_weight(g, weight_gen, 17, 20);
    add_edge_with_random_weight(g, weight_gen, 18, 9);
    add_edge_with_random_weight(g, weight_gen, 19, 23);
    add_edge_with_random_weight(g, weight_gen, 19, 18);
    add_edge_with_random_weight(g, weight_gen, 20, 23);
    add_edge_with_random_weight(g, weight_gen, 20, 13);
    add_edge_with_random_weight(g, weight_gen, 21, 18);
    add_edge_with_random_weight(g, weight_gen, 21, 13);
    add_edge_with_random_weight(g, weight_gen, 22, 21);
    add_edge_with_random_weight(g, weight_gen, 23, 16);
}

//[loop_erased_random_weighted_tree_example_with_visitor_list
template <typename Graph, typename RNGEngine>
void loop_erased_random_weighted_tree_example_with_visitor_list()
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
    typedef typename boost::property_map<Graph,boost::edge_weight_t>::type
            EdgeWeightMap;

    Graph          g(24);
    VertexIterator vi, vi_end;
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    std::tr1::variate_generator<RNGEngine&,std::tr1::uniform_real<> > rng(
        engine
      , std::tr1::uniform_real<>(0.2, 0.8)
    );
    initialize_graph(g, rng);

    EdgeWeightMap e_map = boost::get(boost::edge_weight, g);
    typename boost::graph_traits<Graph>::edge_descriptor e;
    bool b;
    Vertex u;

    std::cout << "Graph:" << std::endl;
    boost::print_graph(g);
    boost::print_edges2(g, index_map, e_map);

    for (;;)
    {
        std::cout << std::endl << std::endl;

        if (
#ifdef BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_ALL_PARAMS
            boost::loop_erased_random_weighted_tree(
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
#else  // !def BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_ALL_PARAMS
            boost::loop_erased_random_weighted_tree(
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
#endif  // BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_ALL_PARAMS
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
                u = boost::get(pred_map, *vi);
                std::cout << boost::get(index_map, u) << " (";
                boost::tie(e, b) = boost::edge(*vi, u, g);

                if (b)
                {
                    std::cout << boost::get(e_map, e);
                }

                std::cout << ')' << std::endl;
            }

            break;
        }

        std::cout << std::endl << "Trying again...\t";
    }
}
//]

//[loop_erased_random_weighted_tree_example_with_fusion_visitor_list
template <typename Graph, typename RNGEngine>
void
    loop_erased_random_weighted_tree_example_with_fusion_visitor_list(
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
    typedef typename boost::property_map<Graph,boost::edge_weight_t>::type
            EdgeWeightMap;

    Graph          g(24);
    VertexIterator vi, vi_end;
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    std::tr1::variate_generator<RNGEngine&,std::tr1::uniform_real<> > rng(
        engine
      , std::tr1::uniform_real<>(0.2, 0.8)
    );
    initialize_graph(g, rng);

    EdgeWeightMap e_map = boost::get(boost::edge_weight, g);
    typename boost::graph_traits<Graph>::edge_descriptor e;
    bool b;
    Vertex u, root = boost::vertex(root_index, g);

    std::cout << std::endl << "Target = " << boost::get(index_map, root);
    std::cout << ", Graph:" << std::endl;
    boost::print_graph(g);
    boost::print_edges2(g, index_map, e_map);

    for (;;)
    {
        std::cout << std::endl << std::endl;

        if (
#ifdef BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_ALL_PARAMS
            boost::loop_erased_random_weighted_tree(
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
#else  // !def BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_ALL_PARAMS
            boost::loop_erased_random_weighted_tree(
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
#endif  // BOOST_GRAPH_LOOP_ERASED_RANDOM_WEIGHTED_TREE_TAKES_ALL_PARAMS
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
                u = boost::get(pred_map, *vi);
                std::cout << boost::get(index_map, u) << " (";
                boost::tie(e, b) = boost::edge(*vi, u, g);

                if (b)
                {
                    std::cout << boost::get(e_map, e);
                }

                std::cout << ')' << std::endl;
            }

            break;
        }

        std::cout << std::endl << "Trying again...\t";
    }
}
//]

//[loop_erased_random_weighted_tree_example
template <typename Graph, typename RNGEngine>
void loop_erased_random_weighted_tree_example(unsigned int num_runs)
{
    typedef typename boost::graph_traits<Graph>::vertex_iterator
            VertexIterator;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor
            Vertex;
    typedef typename boost::vertex_property_map_gen<Graph,Vertex>::type
            PredecessorMap;
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;
    typedef typename boost::property_map<Graph,boost::edge_weight_t>::type
            EdgeWeightMap;

    Graph          g(24);
    VertexIterator vi, vi_end;
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    std::tr1::variate_generator<RNGEngine&,std::tr1::uniform_real<> > rng(
        engine
      , std::tr1::uniform_real<>(0.2, 0.8)
    );
    initialize_graph(g, rng);

    EdgeWeightMap e_map = boost::get(boost::edge_weight, g);
    typename boost::graph_traits<Graph>::edge_descriptor e;
    bool b;
    Vertex u;

    std::cout << std::endl << "Graph:" << std::endl;
    boost::print_graph(g);
    boost::print_edges2(g, index_map, e_map);

    while (num_runs)
    {
        if (boost::loop_erased_random_weighted_tree(g, engine, pred_map))
        {
            std::cout << std::endl << "Successors:" << std::endl;

            for (
                boost::tie(vi, vi_end) = boost::vertices(g);
                vi != vi_end;
                ++vi
            )
            {
                std::cout << '\t' << boost::get(index_map, *vi) << " --> ";
                u = boost::get(pred_map, *vi);
                std::cout << boost::get(index_map, u) << " (";
                boost::tie(e, b) = boost::edge(*vi, u, g);

                if (b)
                {
                    std::cout << boost::get(e_map, e);
                }

                std::cout << ')' << std::endl;
            }

            --num_runs;
        }
    }
}
//]

//[loop_erased_random_weighted_tree_with_source_example
template <typename Graph, typename RNGEngine>
void
    loop_erased_random_weighted_tree_with_source_example(
        std::size_t const root_index
      , unsigned int num_runs
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
    typedef typename boost::property_map<Graph,boost::edge_weight_t>::type
            EdgeWeightMap;

    Graph          g(24);
    VertexIterator vi, vi_end;
    Vertex         root = boost::vertex(root_index, g);
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    std::tr1::variate_generator<RNGEngine&,std::tr1::uniform_real<> > rng(
        engine
      , std::tr1::uniform_real<>(0.2, 0.8)
    );
    initialize_graph(g, rng);

    EdgeWeightMap e_map = boost::get(boost::edge_weight, g);
    typename boost::graph_traits<Graph>::edge_descriptor e;
    bool b;
    Vertex u;

    std::cout << std::endl << "Source = " << boost::get(index_map, root);
    std::cout << ", Graph:" << std::endl;
    boost::print_graph(g);
    boost::print_edges2(g, index_map, e_map);

    while (num_runs)
    {
        if (
            boost::loop_erased_random_weighted_tree(
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
                u = boost::get(pred_map, *vi);
                std::cout << boost::get(index_map, u) << " (";
                boost::tie(e, b) = boost::edge(u, *vi, g);

                if (b)
                {
                    std::cout << boost::get(e_map, e);
                }

                std::cout << ')' << std::endl;
            }

            --num_runs;
        }
    }
}
//]

//[loop_erased_random_weighted_tree_with_target_example
template <typename Graph, typename RNGEngine>
void
    loop_erased_random_weighted_tree_with_target_example(
        std::size_t const root_index
      , unsigned int num_runs
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
    typedef typename boost::property_map<Graph,boost::edge_weight_t>::type
            EdgeWeightMap;

    Graph          g(24);
    VertexIterator vi, vi_end;
    Vertex         root = boost::vertex(root_index, g);
    PredecessorMap pred_map(g);
    VertexIndexMap index_map = boost::get(boost::vertex_index, g);
    RNGEngine      engine;

    std::tr1::variate_generator<RNGEngine&,std::tr1::uniform_real<> > rng(
        engine
      , std::tr1::uniform_real<>(0.2, 0.8)
    );
    initialize_graph(g, rng);

    EdgeWeightMap e_map = boost::get(boost::edge_weight, g);
    typename boost::graph_traits<Graph>::edge_descriptor e;
    bool b;
    Vertex u;

    std::cout << std::endl << "Target = " << boost::get(index_map, root);
    std::cout << ", Graph:" << std::endl;
    boost::print_graph(g);
    boost::print_edges2(g, index_map, e_map);

    while (num_runs)
    {
        if (boost::loop_erased_random_weighted_tree(g, engine, pred_map, root))
        {
            std::cout << std::endl << "Successors:" << std::endl;

            for (
                boost::tie(vi, vi_end) = boost::vertices(g);
                vi != vi_end;
                ++vi
            )
            {
                std::cout << '\t' << boost::get(index_map, *vi) << " --> ";
                u = boost::get(pred_map, *vi);
                std::cout << boost::get(index_map, u) << " (";
                boost::tie(e, b) = boost::edge(*vi, u, g);

                if (b)
                {
                    std::cout << boost::get(e_map, e);
                }

                std::cout << ')' << std::endl;
            }

            --num_runs;
        }
    }
}
//]

//[loop_erased_random_weighted_path_example
template <typename Graph, typename RNGEngine>
void
    loop_erased_random_weighted_path_example(
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

    std::tr1::variate_generator<RNGEngine&,std::tr1::uniform_real<> > rng(
        engine
      , std::tr1::uniform_real<>(0.2, 0.8)
    );

    initialize_graph(g, rng);
    std::cout << std::endl << "Start = " << boost::get(index_map, start);
    std::cout << ", End = " << boost::get(index_map, end);
    std::cout << ", Graph:" << std::endl;
    boost::print_graph(g);
    boost::print_edges2(g, index_map, boost::get(boost::edge_weight, g));

    while (num_runs)
    {
        if (
            boost::loop_erased_random_weighted_tree(
                g
              , engine
              , pred_map
              , end
              , start
            )
        )
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
              , boost::no_property
              , boost::property<boost::edge_weight_t,double>
            >
            UndirectedGraph;
    typedef boost::adjacency_list<
                EdgeContainerSelector
              , boost::vecS
              , boost::bidirectionalS
              , boost::no_property
              , boost::property<boost::edge_weight_t,double>
            >
            BidirectionalGraph;
    typedef boost::adjacency_list<
                EdgeContainerSelector
              , boost::vecS
              , boost::directedS
              , boost::no_property
              , boost::property<boost::edge_weight_t,double>
            >
            DirectedGraph;

    std::cout << "Running loop_erased_random_weighted_tree function template ";
    std::cout << "on undirected graph." << std::endl;
    loop_erased_random_weighted_tree_example_with_visitor_list<
        UndirectedGraph
      , RNGEngine
    >();
    loop_erased_random_weighted_tree_example_with_fusion_visitor_list<
        UndirectedGraph
      , RNGEngine
    >(end_index);
    loop_erased_random_weighted_tree_example<
        UndirectedGraph
      , RNGEngine
    >(num_runs);
    loop_erased_random_weighted_tree_with_source_example<
        UndirectedGraph
      , RNGEngine
    >(start_index, num_runs);
    loop_erased_random_weighted_tree_with_target_example<
        UndirectedGraph
      , RNGEngine
    >(end_index, num_runs);
    loop_erased_random_weighted_path_example<
        UndirectedGraph
      , RNGEngine
    >(start_index, end_index, num_runs);
    std::cout << std::endl << std::endl;

    std::cout << "Running loop_erased_random_weighted_tree function template ";
    std::cout << "on directed graph." << std::endl;
    loop_erased_random_weighted_tree_example_with_visitor_list<
        DirectedGraph
      , RNGEngine
    >();
    loop_erased_random_weighted_tree_example_with_fusion_visitor_list<
        DirectedGraph
      , RNGEngine
    >(end_index);
    loop_erased_random_weighted_tree_example<
        DirectedGraph
      , RNGEngine
    >(num_runs);
    loop_erased_random_weighted_tree_with_source_example<
        DirectedGraph
      , RNGEngine
    >(start_index, num_runs);
    loop_erased_random_weighted_tree_with_target_example<
        DirectedGraph
      , RNGEngine
    >(end_index, num_runs);
    loop_erased_random_weighted_path_example<
        DirectedGraph
      , RNGEngine
    >(start_index, end_index, num_runs);
    std::cout << std::endl << std::endl;

    std::cout << "Running loop_erased_random_weighted_tree function template ";
    std::cout << "on bidirectional graph." << std::endl;
    loop_erased_random_weighted_tree_example_with_visitor_list<
        BidirectionalGraph
      , RNGEngine
    >();
    loop_erased_random_weighted_tree_example_with_fusion_visitor_list<
        BidirectionalGraph
      , RNGEngine
    >(end_index);
    loop_erased_random_weighted_tree_example<
        BidirectionalGraph
      , RNGEngine
    >(num_runs);
    loop_erased_random_weighted_tree_with_source_example<
        BidirectionalGraph
      , RNGEngine
    >(start_index, num_runs);
    loop_erased_random_weighted_tree_with_target_example<
        BidirectionalGraph
      , RNGEngine
    >(end_index, num_runs);
    loop_erased_random_weighted_path_example<
        BidirectionalGraph
      , RNGEngine
    >(start_index, end_index, num_runs);
}

#endif  // LIBS_GRAPH_EXAMPLE_LOOP_ERASED_RANDOM_WEIGHTED_TREE_HPP

