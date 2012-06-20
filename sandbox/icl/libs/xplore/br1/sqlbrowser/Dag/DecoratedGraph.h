/****************************************************************************
**
**
****************************************************************************/

#pragma once

//boost
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>


namespace dag
{

//! Template DecoratedGraph provides all types for a graph that is decorated
//! with vertex and edge objects.
template<class VertexDeco, class EdgeDeco, class Directed = boost::directedS>
struct DecoratedGraph
{
    typedef VertexDeco tVertexDeco;
    typedef EdgeDeco   tEdgeDeco;

    // The kind of vertex_attr_tag is a vertex_property_tag
    struct vertex_attr_tag  { typedef boost::vertex_property_tag kind; };

    // The kind of edge_attr_tag is a edge_property_tag
    struct edge_attr_tag  { typedef boost::edge_property_tag kind; };

    // Here we associate a real type for content 'VertexAttributes' to the tag type
    // vertex_attr_tag -> VertexAttributes
    typedef boost::property<vertex_attr_tag,  VertexDeco> tVertexAttrTag;
    typedef boost::property<edge_attr_tag,    EdgeDeco>   tEdgeAttrTag;

    typedef boost::adjacency_list
    < boost::vecS  //Edges:    Sequence or AssociativeContainer
    , boost::vecS //Vertexes: Sequence or RandomAccessContainer
    , Directed
    , VertexDeco
    , EdgeDeco
    > tGraph;

    typedef typename tGraph type;
    typedef typename tGraph::vertex_descriptor vertex_descriptor;
    typedef typename tGraph::edge_descriptor   edge_descriptor;

    typedef std::map<vertex_descriptor, int>   tVertex2Depth;

};


} // dag

