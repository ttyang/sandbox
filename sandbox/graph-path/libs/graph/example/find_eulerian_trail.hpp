// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_EXAMPLE_FIND_EULERIAN_TRAIL_HPP
#define LIBS_GRAPH_EXAMPLE_FIND_EULERIAN_TRAIL_HPP

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
#include <boost/graph/has_eulerian_trail.hpp>
#include <boost/graph/find_eulerian_trail.hpp>

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/fusion/container/generation/make_list.hpp>
#include <boost/graph/fuse_property_writer.hpp>
#endif

#include "../test/initialize_euler_graphs.hpp"

template <typename Graph>
void initialize_bridges(Graph& g)
{
    boost::add_edge(boost::vertex(0, g), boost::vertex(1, g), g);
    boost::add_edge(boost::vertex(0, g), boost::vertex(1, g), g);
    boost::add_edge(boost::vertex(0, g), boost::vertex(2, g), g);
    boost::add_edge(boost::vertex(0, g), boost::vertex(2, g), g);
    boost::add_edge(boost::vertex(0, g), boost::vertex(3, g), g);
    boost::add_edge(boost::vertex(1, g), boost::vertex(3, g), g);
    boost::add_edge(boost::vertex(2, g), boost::vertex(3, g), g);
}

//[find_eulerian_trail_example_with_visitor_list
template <typename Graph>
void find_eulerian_trail_example_with_visitor_list(Graph const& g)
{
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;
    typedef typename boost::property_traits<VertexIndexMap>::value_type
            VertexIndex;
    typedef std::list<typename boost::graph_traits<Graph>::edge_descriptor>
            EdgeList;

    VertexIndexMap i_map = boost::get(boost::vertex_index, g);

    std::cout << "Graph:" << std::endl;
    boost::print_graph(g);
    std::cout << std::endl;

    if (boost::has_eulerian_trail(g))
    {
        EdgeList path;

        boost::find_eulerian_trail(
            g
          , std::back_inserter(path)
          , std::make_pair(
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
        std::cout << "...has no Eulerian trail." << std::endl;
    }
}
//]

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[find_eulerian_trail_example_with_fusion_visitor_list
template <typename Graph>
void find_eulerian_trail_example_with_fusion_visitor_list(Graph const& g)
{
    typedef typename boost::property_map<Graph,boost::vertex_index_t>::type
            VertexIndexMap;
    typedef typename boost::property_traits<VertexIndexMap>::value_type
            VertexIndex;
    typedef std::list<typename boost::graph_traits<Graph>::edge_descriptor>
            EdgeList;

    VertexIndexMap i_map = boost::get(boost::vertex_index, g);

    std::cout << "Graph:" << std::endl;
    boost::print_graph(g);
    std::cout << std::endl;

    if (boost::has_eulerian_trail(g))
    {
        EdgeList path;

        boost::find_eulerian_trail(
            g
          , std::back_inserter(path)
          , boost::fusion::make_list(
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
        std::cout << "...has no Eulerian trail." << std::endl;
    }
}
//]

#endif

template <typename EdgeContainerSelector>
void vec_adjacency_list_example()
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

    UndirectedGraph konigsberg(4), paper_clip(4);
    BidirectionalGraph bidigraph(5);
    DirectedGraph digraph(5);

    initialize_bridges(konigsberg);
    initialize_two_triangles(paper_clip);
    initialize_almost_complete_graph(bidigraph);
    initialize_almost_complete_graph(digraph);

    std::cout << std::endl << std::endl;
    std::cout << "Running find_eulerian_trail algorithm on Konigsberg.";
    std::cout << std::endl << std::endl;
    find_eulerian_trail_example_with_visitor_list(konigsberg);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    std::cout << std::endl;
    find_eulerian_trail_example_with_fusion_visitor_list(konigsberg);
#endif

    std::cout << std::endl << std::endl;
    std::cout << "Running find_eulerian_trail algorithm on two triangles.";
    std::cout << std::endl << std::endl;
    find_eulerian_trail_example_with_visitor_list(paper_clip);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    std::cout << std::endl;
    find_eulerian_trail_example_with_fusion_visitor_list(paper_clip);
#endif

    std::cout << std::endl << std::endl;
    std::cout << "Running find_eulerian_trail algorithm on bidigraph.";
    std::cout << std::endl << std::endl;
    find_eulerian_trail_example_with_visitor_list(bidigraph);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    std::cout << std::endl;
    find_eulerian_trail_example_with_fusion_visitor_list(bidigraph);
#endif

    std::cout << std::endl << std::endl;
    std::cout << "Running find_eulerian_trail algorithm on digraph.";
    std::cout << std::endl << std::endl;
    find_eulerian_trail_example_with_visitor_list(digraph);
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    std::cout << std::endl;
    find_eulerian_trail_example_with_fusion_visitor_list(digraph);
#endif
}

#endif  // LIBS_GRAPH_EXAMPLE_FIND_EULERIAN_TRAIL_HPP

