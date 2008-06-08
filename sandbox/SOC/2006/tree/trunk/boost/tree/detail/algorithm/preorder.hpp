//  Copyright (c) 2006-2008, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file preorder.hpp
 * Non-modifying hierarchy preorder range algorithms
 */

// TODO: concept checks.

#ifndef BOOST_TREE_DETAIL_ALGORITHM_PREORDER_HPP
#define BOOST_TREE_DETAIL_ALGORITHM_PREORDER_HPP

#include <boost/tree/detail/iterator/preorder.hpp>

namespace boost {
namespace tree {
	
namespace preorder {

template <class Cursor>
iterator<Cursor, forward_traversal_tag> 
begin(Cursor c, forward_traversal_tag)
{
	std::stack<Cursor> s;

	s.push(c);
	s.push(c.begin());
	return iterator<Cursor, forward_traversal_tag>(s);	
}

template <class Cursor>
iterator<Cursor, forward_traversal_tag> 
end(Cursor c, forward_traversal_tag)
{
	std::stack<Cursor> s;

	s.push(c);
	return iterator<Cursor, forward_traversal_tag>(s);
}

#include <boost/tree/detail/algorithm/iterator/bidirectional.hpp>

} // namespace preorder

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_ALGORITHM_PREORDER_HPP
