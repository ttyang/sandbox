// Copyright Franz Alt 2009-2011
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MGL_BREADTH_FIRST_SEARCH_HPP
#define BOOST_MGL_BREADTH_FIRST_SEARCH_HPP

#include <boost/mpl/vector.hpp>
#include <boost/mpl/void.hpp>

#include <boost/mgl/begin_end.hpp>
#include <boost/mgl/find.hpp>
#include <boost/mgl/iterator_policies.hpp>
#include <boost/mgl/visitors.hpp>
#include <boost/mgl/aux_/breadth_first_search_impl.hpp>

namespace boost
{

namespace mgl
{

/// \brief Performs a breadth-first-traversal of the vertices in a directed graph
/// \tparam Graph The graph that should be traversed
/// \tparam Visitor The visitor used at the traversal
/// \tparam Vertex The Vertex where the search begins at
/// \tparam EndAtStrategy Strategy what is done when all vertices are visited
template<
    class Graph,
    class Visitor = ::boost::mgl::null_visitor,
    class Vertex = ::boost::mpl::void_,
    class EndAtStrategy = ::boost::mgl::EndAtEndOfGraph
>
struct breadth_first_search
{
    typedef typename ::boost::mpl::eval_if<
        typename ::boost::is_same<Vertex, ::boost::mpl::void_>::type,
        ::boost::mgl::bfs_begin<
            Graph,
            EndAtStrategy,
            Visitor
        >,
        ::boost::mgl::bfs_find<
            Graph,
            Vertex,
            EndAtStrategy,
            Visitor
        >
    >::type iter;

    typedef typename aux::template breadth_first_search_impl<iter>::type type;
};

} // namespace mgl

} // namespace boost

#endif // BOOST_MGL_BREATH_FIRST_SEARCH_HPP
