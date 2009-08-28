/**
 * This is a simple example of how to create a function_graph.
 *
 * It isn't so hard. A function graph needs only a binary function. Since a
 * function graph without a range is almost nothing, this example also includes
 * a range.
 *
 * Please read the documentation before pursuing this exercise. Do it.
 */

#include <functional>
#include <utility>
#include "function_graph.hpp"
#include <boost/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility.hpp>

using namespace boost;

const unsigned int arr_size = 10;

int main()
{
    // The iterator range in this case will be a simple integer vector
    typedef std::pair<int*, int*> IterRng;
    int vertices[arr_size] = {  -53456,   0, 12,   1345,     224,
                             -6745732, 777, -1, 996212, -758342};


    // The function we will use is std::less<long>, so we prepare with the type
    // bool(long, long). What is done is done. The function graph is finished.
    typedef function_graph<bool(int, int), IterRng> LessGraph;
    LessGraph less_graph(std::less<int>(),
                         std::make_pair(vertices, vertices + arr_size));


    // These are the all important edges. This is simply a wrapper for the
    // std::less<int> and, therefor, returns a bool.
    bool i_am_a_bool = less_graph.edge(vertices[3], vertices[7]);


    // I mentioned in the documentation that the result_type (return type for
    // the function) is not the same as an edge_descriptor. Uncomment this
    // section for proof.
    /*BOOST_ASSERT(bool(
        is_same<
            LessGraph::result_type,
            LessGraph::edge_descriptor
        >::value
    ));*/


    // The way to get a right and proper edge is to use the BGL concepts. The
    // AdjacencyMatrix concept gives us the edge(u, v, g) function, which does
    // return a value edge of type edge_descriptor.
    LessGraph::edge_descriptor an_edge;
    bool edge_exists;
    tie(an_edge, edge_exists) = edge(vertices[3], vertices[7], less_graph);
    BOOST_ASSERT(an_edge.source == vertices[3]);
    BOOST_ASSERT(an_edge.target == vertices[7]);
    BOOST_ASSERT(an_edge.result == i_am_a_bool);


    // Please continue reading the tutorial. The rest is to show that the
    // function graph actually works and shows some of the functions found in
    // the BGL.
    BOOST_ASSERT(arr_size == num_vertices(less_graph));


    // Those who understand how less_than creates a lattice will see that the
    // number of edges is the sum of integers starting at 1 and ending at the
    // number of vertices - 1. Those who don't see this immediately (sane
    // people), will have to count the edges by hand.
    BOOST_ASSERT(45 == num_edges(less_graph));


    // Recall that the second vertex is zero. So if we check all of the target
    // vertices of the out edges of this vertex, it should give us all of the
    // positive vertices.
    typedef std::pair<
                LessGraph::out_edge_iterator,
                LessGraph::out_edge_iterator
            > OutEdges;
    OutEdges out_edges_to_0 = out_edges(vertices[2], less_graph);
    while(out_edges_to_0.first != out_edges_to_0.second)
    {
        BOOST_ASSERT((*out_edges_to_0.first).target > 0);
        ++out_edges_to_0.first;
    }

    return 0;
}
