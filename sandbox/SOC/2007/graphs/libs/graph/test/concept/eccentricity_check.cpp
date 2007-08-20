// (C) Copyright Andrew Sutton 2007
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#include "archetypes.hpp"
#include <boost/graph/eccentricity.hpp>

using namespace std;
using namespace boost;

int
main(int argc, char *argv[])
{
    {
        typedef vertex_list_graph_archetype<
                undirected_tag,
                allow_parallel_edge_tag
            > Graph;
        typedef graph_traits<Graph>::vertex_descriptor Vertex;
        typedef writable_property_map_archetype<Vertex, float> EccentricityMap;
        typedef readable_property_map_archetype<Vertex, size_t> DistanceMap;
        typedef readable_property_map_archetype<Vertex, DistanceMap> DistanceMatrix;

        Graph& g = static_object<Graph>::get();
        EccentricityMap em;
        DistanceMatrix dm;

        all_eccentricities(g, dm, em);
    }

    {
        typedef vertex_list_graph_archetype<
                undirected_tag,
                allow_parallel_edge_tag
            > Graph;
        typedef graph_traits<Graph>::vertex_descriptor Vertex;
        typedef readable_property_map_archetype<Vertex, size_t> DistanceMap;

        Graph& g = static_object<Graph>::get();
        DistanceMap dm;

        eccentricity(g, dm);
    }

    {
        typedef vertex_list_graph_archetype<
                undirected_tag,
                allow_parallel_edge_tag
            > Graph;
        typedef graph_traits<Graph>::vertex_descriptor Vertex;
        typedef readable_property_map_archetype<Vertex, size_t> EccentricityMap;

        Graph& g = static_object<Graph>::get();
        EccentricityMap em;

        radius(g, em);
        diameter(g, em);
        radius_and_diameter(g, em);
    }

    return 0;
}
