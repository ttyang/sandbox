// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_VERTEX_DIMENSION_TRAIT_HPP
#define BOOST_GRAPH_VERTEX_DIMENSION_TRAIT_HPP

#include <boost/array.hpp>
#include <boost/graph/grid_graph.hpp>

//[reference__vertex_dimension_trait
namespace boost {

    template <typename Graph>
    struct vertex_dimension_trait
    {
        typedef void type;
    };

    //<-
    template <
        ::std::size_t Dimensions
      , typename VertexIndex
      , typename EdgeIndex
    >
    struct vertex_dimension_trait<
        grid_graph<Dimensions,VertexIndex,EdgeIndex>
    >
    {
        typedef typename ::boost::array<VertexIndex,Dimensions>::size_type
                type;
    };
    //->
}  // namespace boost
//]

#endif  // BOOST_GRAPH_VERTEX_DIMENSION_TRAIT_HPP

