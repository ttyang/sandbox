// Copyright Franz Alt 2009-2011
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MGL_FIND_HPP
#define BOOST_MGL_FIND_HPP

#include <boost/mpl/has_xxx.hpp>

#include <boost/utility/enable_if.hpp>

#include <boost/mgl/iterator_policies.hpp>
#include <boost/mgl/visitors.hpp>

namespace boost
{

namespace mgl
{

BOOST_MPL_HAS_XXX_TRAIT_DEF(dfs_find_supported)
BOOST_MPL_HAS_XXX_TRAIT_DEF(bfs_find_supported)

/// \brief Find a specified vertex inside a graph and return a DFS iterator.
/// \tparam Graph Graph where the iteration should be performed
/// \tparam Vertex Vertex that should be found inside the graph
/// \tparam EndAtStrategy The strategy used to abort the iteration
/// \tparam Visitor The visitor class used during the iteration
template<
    class Graph,
    class Vertex,
    class EndAtStrategy = ::boost::mgl::EndAtEndOfGraph,
    class Visitor = ::boost::mgl::null_visitor,
    class Enable = void
>
struct dfs_find
{
    typedef ::boost::mpl::void_ type;
};

template<
    class Graph,
    class Vertex,
    class EndAtStrategy,
    class Visitor
>
struct dfs_find<
    Graph,
    Vertex,
    EndAtStrategy,
    Visitor,
    typename ::boost::enable_if<
	    has_dfs_find_supported<Graph>
	>::type
>
{
    typedef typename Graph::template dfs_find<Vertex, EndAtStrategy, Visitor>::type type;
};

/// \brief Find a specified vertex inside a graph and return a BFS iterator.
/// \tparam Graph Graph where the iteration should be performed
/// \tparam Vertex Vertex that should be found inside the graph
/// \tparam EndAtStrategy The strategy used to abort the iteration
/// \tparam Visitor The visitor class used during the iteration
template<
    class Graph,
    class Vertex,
    class EndAtStrategy = ::boost::mgl::EndAtEndOfGraph,
    class Visitor = ::boost::mgl::null_visitor,
    class Enable = void
>
struct bfs_find
{
    typedef ::boost::mpl::void_ type;
};

template<
    class Graph,
    class Vertex,
    class EndAtStrategy,
    class Visitor
>
struct bfs_find<
    Graph,
    Vertex, 
    EndAtStrategy,
    Visitor,
    typename ::boost::enable_if<
	    has_bfs_find_supported<Graph>
    >::type
>
{
	typedef typename Graph::template bfs_find<Vertex, EndAtStrategy, Visitor>::type type;
};

} // namespace mgl

} // namespace boost

#endif // BOOST_MGL_FIND_HPP
