// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_EDGE_KEY_TRAIT_HPP
#define BOOST_GRAPH_EDGE_KEY_TRAIT_HPP

#include <boost/graph/grid_graph.hpp>

//[reference__edge_key_trait
namespace boost {

    template <typename Graph>
    struct edge_key_trait
    {
        typedef void type;
    };

    //<-
    template <
        ::std::size_t Dimensions
      , typename VertexIndex
      , typename EdgeIndex
    >
    struct edge_key_trait<
        grid_graph<Dimensions,VertexIndex,EdgeIndex>
    >
    {
        typedef ::std::size_t type;
    };
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_EDGE_KEY_TRAIT_HPP

