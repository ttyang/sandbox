// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_GRAPH_TEST_INITIALIZE_COMPLETE_GRAPH_HPP
#define LIBS_GRAPH_TEST_INITIALIZE_COMPLETE_GRAPH_HPP

#include <boost/tr1/type_traits.hpp>
#include <boost/graph/graph_traits.hpp>

template <typename Graph>
void initialize_complete_graph(Graph& g)
{
    typedef typename boost::graph_traits<Graph>::vertices_size_type Index;

    for (Index j = 1; j < boost::num_vertices(g); ++j)
    {
        for (Index i = 0; i < j; ++i)
        {
            boost::add_edge(boost::vertex(i, g), boost::vertex(j, g), g);

            if (
                std::tr1::is_base_of<
                    boost::directed_tag
                  , typename boost::graph_traits<Graph>::directed_category
                >::value
            )
            {
                boost::add_edge(boost::vertex(j, g), boost::vertex(i, g), g);
            }
        }
    }
}

#endif  // LIBS_GRAPH_TEST_INITIALIZE_COMPLETE_GRAPH_HPP

