// Copyright Franz Alt 2009-2011
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MGL_DEPTH_FIRST_SEARCH_IMPL_HPP
#define BOOST_MGL_DEPTH_FIRST_SEARCH_IMPL_HPP

#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/void.hpp>

#include <boost/mgl/begin_end.hpp>
#include <boost/mgl/next_prior.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost
{

namespace mgl
{

namespace aux
{

template<class Iterator, class AtEnd = void>
struct depth_first_search_impl
{
	typedef typename depth_first_search_impl<
		typename ::boost::mgl::next<Iterator>::type
	>::type type;
};

template<class Iterator>
struct depth_first_search_impl<
    Iterator,
    typename ::boost::enable_if<
	    ::boost::is_same<Iterator, ::boost::mpl::void_>
    >::type>
{
	typedef dfs_iterator<
        ::boost::mpl::void_,
	    ::boost::mpl::void_,
		::boost::mpl::set0<>,
		::boost::mpl::vector0<>
	> type;

	typedef typename ::boost::mpl::void_ visitor_type;
	typedef typename ::boost::mpl::void_ visitor_result;
};

template<class Iterator>
struct depth_first_search_impl<
    Iterator,
    typename ::boost::enable_if<
	    ::boost::is_same<
	        typename ::boost::mgl::dfs_end<typename Iterator::graph>::type,
		    typename Iterator::vertex>
	    >::type
    >
{
	typedef dfs_iterator<
		typename Iterator::graph,
		typename Iterator::graph::end,
		typename Iterator::color_map,
		typename Iterator::traversal_stack,
		typename Iterator::end_at_strategy,
		typename Iterator::visitor_type,
		typename Iterator::visitor_result
	> type;
};

} // namespace aux

} // namespace mgl

} // namespace boost

#endif // BOOST_MGL_DEPTH_FIRST_SEARCH_IMPL_HPP
