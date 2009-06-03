/**
 * Testing a function that returns a boolean
 */

#include <iostream>
#include <boost/function.hpp>
#include <functional>
#include <algorithm>
#include <vector>
#include <utility>
#include "function_graph.hpp"

template <typename T>
struct less_than {
    bool operator()(T a, T b) { return a < b; }
};

int main()
{
    ////////
    // Create a boost function and function graph.
    typedef boost::function<bool(int,int)> function_type;
    typedef boost::function_graph<function_type> graph;
    typedef graph::edge_descriptor edge_descriptor;
    function_type f = less_than<int>();
    function_type g = less_than<int>();
    graph funcGraph(f);
    
    ////////
    // Set a new function to the graph.
    funcGraph.set_function(g);
    
    ////////
    // Check the edge output.
    std::cout << "2 < 1 check ";
    if(funcGraph.edge(2,1)) std::cout << "fails." << "\n";
    else std::cout << "passes." << "\n";

    ////////
    // Check the adjacency matrix edge
    std::pair<edge_descriptor, bool> edge_pair = boost::edge(1, 2, funcGraph);
    std::cout << edge_pair.first << "\n";

    
    
    return 0;
}
