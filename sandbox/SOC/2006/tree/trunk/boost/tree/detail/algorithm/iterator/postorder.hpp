//  Copyright (c) 2006-2008, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file postorder.hpp
 * Non-modifying hierarchy postorder range algorithms
 */

// TODO: concept checks.

#ifndef BOOST_TREE_DETAIL_ALGORITHM_ITERATOR_POSTORDER_HPP
#define BOOST_TREE_DETAIL_ALGORITHM_ITERATOR_POSTORDER_HPP

#include <boost/tree/detail/iterator/postorder.hpp>
#include <boost/tree/detail/algorithm/cursor/postorder.hpp>

namespace boost {
namespace tree {
	
namespace postorder {

template <class Cursor>
iterator<Cursor, forward_traversal_tag> 
begin(Cursor c, forward_traversal_tag)
{
	std::stack<Cursor> s;

	s.push(c);
	while (true)
		if (!s.top().empty())
			s.push(s.top().begin());
		else if (!(++s.top()).empty())
			s.push(s.top().begin());
		else {
			--s.top();
			return iterator<Cursor, forward_traversal_tag>(s);
		}		
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

} // namespace postorder

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_ALGORITHM_ITERATOR_POSTORDER_HPP
