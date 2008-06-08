//  Copyright (c) 2006-2008, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file inorder.hpp
 * Non-modifying hierarchy inorder range algorithms
 */

// TODO: concept checks.

#ifndef BOOST_TREE_DETAIL_ALGORITHM_INORDER_HPP
#define BOOST_TREE_DETAIL_ALGORITHM_INORDER_HPP

#include <boost/tree/detail/iterator/inorder.hpp>

namespace boost {
namespace tree {

namespace inorder {

template <class MultiwayCursor>
iterator<MultiwayCursor, forward_traversal_tag> 
begin(MultiwayCursor c, forward_traversal_tag)
{
	std::stack<MultiwayCursor> s;

	s.push(c);
	while (!s.top().empty())
		s.push(s.top().begin());
	return iterator<MultiwayCursor, forward_traversal_tag>(s);
}

template <class MultiwayCursor>
iterator<MultiwayCursor, forward_traversal_tag> 
end(MultiwayCursor c, forward_traversal_tag)
{
	std::stack<MultiwayCursor> s;

	s.push(c);
	return iterator<MultiwayCursor, forward_traversal_tag>(s);
}

#include <boost/tree/detail/algorithm/iterator/bidirectional.hpp>

} // namespace inorder

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_ALGORITHM_INORDER_HPP
