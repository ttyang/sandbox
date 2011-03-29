
#ifndef BOOST_GRAPHS_ADJLIST_ES_VECTOR_HPP
#define BOOST_GRAPHS_ADJLIST_ES_VECTOR_HPP

#include <vector>

namespace boost { namespace graphs { namespace adjacency_list {

/**
 * @param Alloc A unary template class that will allocate stored vertices.
 */
template <template <typename> class Alloc = std::allocator>
struct edge_vector
{
    typedef typename descriptor_traits<
        std::vector<int, Alloc<int>>,
        edge_descriptor_kind
    >::descriptor_type edge_descriptor;

    // Ends must be a pair of vertices.
    template <typename Vertex, typename Label>
    struct store
    {
    private:
        typedef std::pair<Vertex, Vertex> ends;
        typedef std::pair<ends, Label> edge;
        typedef Alloc<edge> allocator;
    public:
        typedef std::vector<edge, allocator> type;
    };
};

} } } /* namespace boost::graphs::adjacency_list */

#endif