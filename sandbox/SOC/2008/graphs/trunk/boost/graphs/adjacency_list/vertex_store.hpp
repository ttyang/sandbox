
#ifndef BOOST_GRAPH_ADJLIST_VERTEX_STORE_TRAITS_HPP
#define BOOST_GRAPH_ADJLIST_VERTEX_STORE_TRAITS_HPP

#include <boost/containers.hpp>
#include <boost/descriptors.hpp>

namespace boost { namespace graphs { namespace adjacency_list {

struct vertex_descriptor_kind { };

/**
 * The vertex store traits defines the basic types associate with a vertex set.
 */
template <typename VertexStore>
struct vertex_store_traits
{ };

/**
 * Add a vertex to the given store, returning a descriptor to the added
 * vertex. The semantics and performance of this function depend on the
 * kind of vertex store.
 */
template <typename Store, typename Vertex>
typename descriptor_traits<Store>::descriptor_type
add_vertex_to_store(Store& store, Vertex v)
{ return make_descriptor(store, insert(store, v)); }

} } } /* namespace boost::graphs::adjacency_list */

#endif
