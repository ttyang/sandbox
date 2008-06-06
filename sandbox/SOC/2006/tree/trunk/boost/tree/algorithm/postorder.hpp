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

#ifndef BOOST_TREE_ALGORITHM_POSTORDER_HPP
#define BOOST_TREE_ALGORITHM_POSTORDER_HPP

#include <boost/tree/postorder_iterator.hpp>

namespace boost {
namespace tree {
	
namespace postorder {

/**
 * @if maint
 * Helper function for for_each, using a reference parameter in order to
 * require fewer copy and assignment operations.
 * @endif
 */
template <class Cursor, class Op>
void for_each_recursive(Cursor s, Op& f)
{
	if (!s.empty())
		for_each_recursive(s.begin(), f);
	Cursor subtree = s;
	if (!(++s).empty())
		for_each_recursive(s.begin(), f);
	f(*subtree);
}

/**
 * @brief	Apply a function to every element of a subtree, in postorder.
 * @param s	A cursor.
 * @param f	A unary function object.
 * @return	@p f
 *
 * Applies the function object @p f to each element in the subtree @p s, using 
 * postorder. @p f must not modify the order of the sequence.
 * If @p f has a return value it is ignored.
 */
//[postorder_for_each
template <class Cursor, class Op>
Op for_each(Cursor s, Op f)
{
	if (!s.empty())
		for_each_recursive(s.begin(), f);
	Cursor subtree = s;
	if (!(++s).empty())
		for_each_recursive(s.begin(), f);
	f(*subtree);
	return f;
}
//]

/**
 * @brief	Copies the subtree s into t, by traversing s in postorder.
 * @param s	An input cursor.
 * @param t An output cursor.
 * @result	A cursor past t's postorder end, after the copying operation.
 */
template <class InCursor, class OutCursor>
OutCursor copy (InCursor s, OutCursor t)
{
	InCursor insubtree = s;
	OutCursor outsubtree = t;
	if (!s.empty())
		copy(s.begin(), t.begin());
	if (!(++s).empty()) {
		copy(s.begin(), (++t).begin());
	}
	*outsubtree = *insubtree;
	return outsubtree;
}

/**
 * @brief	 Performs an operation on a subtree, by traversing it in postorder.
 * @param s  An input cursor.
 * @param t  An output cursor.
 * @param op A unary operation.
 * @result	 A cursor past t's postorder end, after the transforming has
 * 			 finished.
 * 
 * By traversing the input subtree s in postorder, apply the operation op 
 * to each element and write the result to the output subtree t.
 * 
 * op must not change its argument.
 */
template <class InCursor, class OutCursor, class Op>
OutCursor transform (InCursor s, OutCursor t, Op op)
{
	InCursor insubtree = s;
	OutCursor outsubtree = t;
	if (!s.empty())
		transform(s.begin(), t.begin(), op);
	if (!(++s).empty()) {
		transform(s.begin(), (++t).begin(), op);
	}
	*outsubtree = op(*insubtree);
	return outsubtree;
}

///Iterators

template <class Cursor>
iterator<Cursor, forward_traversal_tag> 
begin(Cursor c, forward_traversal_tag)
{
	// TODO: Only a (bidirectional) dummy!
	return iterator<Cursor, forward_traversal_tag>(first(c));
}

template <class Cursor>
iterator<Cursor, forward_traversal_tag> 
end(Cursor c, forward_traversal_tag)
{
	// TODO: Only a (bidirectional) dummy!
	return iterator<Cursor, forward_traversal_tag>(last(c));
}

} // namespace postorder

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_ALGORITHM_POSTORDER_HPP
