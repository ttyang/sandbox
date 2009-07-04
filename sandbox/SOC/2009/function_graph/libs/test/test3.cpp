/**
 * Testing a function that has a range
 *
 * Functions used in test:
 *   vertices(g)
 */

#include <iostream>
#include <boost/function.hpp>
#include <functional>
#include <vector>
#include "function_graph.hpp"
#include <boost/range.hpp>
#include <cassert>

// print an edge
template<typename Result, typename Vertex>
void print_edge(boost::detail::func_graph_edge<Result, Vertex> const& e)
{
    std::cout << "\nEdge:\n" << "  Source: " << e.source_ << "\n";
    std::cout << "  Target: " << e.target_ << "\n";
}

int main()
{
    ////////
    // Data for graph
    long arr[8] = {56233, 572, -7851, 956242, -2, 893437, 63, 4474443};
    std::vector<long> numbers(arr, arr + 8);

    ////////
    // Typedefs
    typedef std::pair<
                std::vector<long>::iterator,
                std::vector<long>::iterator
            > iterator_range;
    typedef boost::function<bool(long, long)> boolean_func;
    typedef boost::function<long(long, long)> weighted_func;
    typedef boost::function_graph<boolean_func, iterator_range> boolean_graph;
    typedef boost::function_graph<weighted_func, iterator_range> weighted_graph;

    ////////
    // Create function graphs
    boolean_graph booleanGraph(std::less<long>(),
                               std::make_pair(numbers.begin(), numbers.end()));
    weighted_graph weightedGraph(std::minus<long>(),
                                std::make_pair(numbers.begin(), numbers.end()));

    ////////
    // Check vertices(g)
    iterator_range correctRange = std::make_pair(numbers.begin(),
                                                    numbers.end());
    assert(vertices(booleanGraph) == correctRange);
    assert(vertices(weightedGraph) == correctRange);

    ////////
    // Check num_vertices
    std::vector<long>::size_type numVertices = numbers.size();
    assert(num_vertices(booleanGraph) == numVertices);
    assert(num_vertices(weightedGraph) == numVertices);

    ////////
    // Check in edges

    return 0;
}
