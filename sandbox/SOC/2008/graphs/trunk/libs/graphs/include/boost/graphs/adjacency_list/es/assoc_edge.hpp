
#ifndef BOOST_GRAPHS_ADJLIST_ES_ASSOCIATION_HPP
#define BOOST_GRAPHS_ADJLIST_ES_ASSOCIATION_HPP

namespace boost { namespace graphs {

// NOTE: The code in this module is identical to that in sequence.hpp except
// for the fact that the edge pair is const. Is there a graceful way to get
// around this? Probably, but it might involve pushing more code through traits
// classes.

// Specializations to support labels for undirected edges for edge vectors,
// and lists.

template <typename VertexDesc, typename EdgeLabel>
struct label_traits<std::pair<std::pair<VertexDesc, VertexDesc> const, EdgeLabel>>
{
    typedef EdgeLabel label_type;
};

template <typename VertexDesc, typename EdgeLabel>
inline EdgeLabel&
label(std::pair<std::pair<VertexDesc, VertexDesc> const, EdgeLabel>& edge)
{ return edge.second; }

template <typename VertexDesc, typename EdgeLabel>
inline EdgeLabel const&
label(std::pair<std::pair<VertexDesc, VertexDesc> const, EdgeLabel> const& edge)
{ return edge.second; }

// Specializations of the edge interface for edge sequences (vectors and lists).

// NOTE: I'm un-consting the key type for an associative container. Will this
// cause problems later? Possibly.
template <typename VertexDesc, typename EdgeLabel>
struct edge_traits<std::pair<std::pair<VertexDesc, VertexDesc> const, EdgeLabel>>
{
    typedef VertexDesc vertex_descriptor;
    typedef std::pair<VertexDesc, VertexDesc> edge_ends;
};

template <typename VertexDesc, typename EdgeLabel>
inline std::pair<VertexDesc, VertexDesc>
ends(std::pair<std::pair<VertexDesc, VertexDesc> const, EdgeLabel> const& edge)
{ return edge.first; }

template <typename VertexDesc, typename EdgeLabel>
inline VertexDesc
first(std::pair<std::pair<VertexDesc, VertexDesc> const, EdgeLabel> const& edge)
{ return edge.first.first; }

template <typename VertexDesc, typename EdgeLabel>
inline VertexDesc
second(std::pair<std::pair<VertexDesc, VertexDesc> const, EdgeLabel> const& edge)
{ return edge.first.second; }

template <typename VertexDesc, typename EdgeLabel>
inline VertexDesc
oppposite(std::pair<std::pair<VertexDesc, VertexDesc> const, EdgeLabel> const& edge, VertexDesc which)
{ return which == first(edge) ? second(edge) : first(edge); }


} } /* namespace boost::graphs */

#endif
