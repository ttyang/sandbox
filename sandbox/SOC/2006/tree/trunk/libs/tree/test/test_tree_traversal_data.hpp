//  Copyright (c) 2006-2008, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_HPP
#define LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_HPP

#include <list>

#include <boost/test/minimal.hpp>

// Test data from http://en.wikipedia.org/wiki/Image:Binary_search_tree.svg
// (With two additional nodes: 11 inserted left of 13; 12 right of 11)
// and in combination with http://en.wikipedia.org/wiki/Tree_traversal#Examples
// (as tree shapes are equal [apart from the extra nodes])
template <class Tree>
void create_test_data_tree(Tree& ret)
{
	typename Tree::cursor cur = ret.insert(ret.root(), 8);
	cur = ret.insert(cur, 3);
	ret.insert(cur, 1);
	cur = ret.insert(++cur, 6);
	ret.insert(cur, 4);
	ret.insert(++cur, 7);	
	cur = ret.insert(ret.root().end(), 10);
	cur = ret.insert(ret.root().end().end(), 14);	
	cur = ret.insert(cur, 13);
	cur = ret.insert(cur, 11);
	cur = ret.insert(++cur, 12);
}

template <class Tree>
void validate_test_data_tree(Tree const& ret)
{
	BOOST_CHECK(*ret.root().begin() == 8);
	BOOST_CHECK(*ret.root().begin().begin() == 3);	
	BOOST_CHECK(*ret.root().begin().begin().begin() == 1);
	BOOST_CHECK(*ret.root().begin().end().begin() == 6);		
	BOOST_CHECK(*ret.root().begin().end().begin().begin() == 4);	
	BOOST_CHECK(*ret.root().begin().end().end().begin() == 7);	

	BOOST_CHECK(*ret.root().end().begin() == 10);
	BOOST_CHECK(*ret.root().end().end().begin() == 14);
	BOOST_CHECK(*ret.root().end().end().begin().begin() == 13);
	BOOST_CHECK(*ret.root().end().end().begin().begin().begin() == 11);
	BOOST_CHECK(*ret.root().end().end().begin().begin().end().begin() == 12);
}

namespace test {

namespace preorder {

//std::list data;


template <class Iterator>
void traversal(Iterator a, Iterator b) 
{
	BOOST_CHECK(*a++ == 8);
	BOOST_CHECK(*a++ == 3);
	BOOST_CHECK(*a++ == 1);
	BOOST_CHECK(*a++ == 6);
	BOOST_CHECK(*a++ == 4);
	BOOST_CHECK(*a++ == 7);
	BOOST_CHECK(*a++ == 10);
	BOOST_CHECK(*a++ == 14);
	BOOST_CHECK(*a++ == 13);
	BOOST_CHECK(*a++ == 11);
	BOOST_CHECK(*a++ == 12);
	BOOST_CHECK(a == b);
}

template <class Iterator>
void reverse_traversal(Iterator a, Iterator b)
{	 
	BOOST_CHECK(*--a == 12);
	BOOST_CHECK(*--a == 11);
	BOOST_CHECK(*--a == 13);
	BOOST_CHECK(*--a == 14);
	BOOST_CHECK(*--a == 10);
	BOOST_CHECK(*--a == 7);
	BOOST_CHECK(*--a == 4);
	BOOST_CHECK(*--a == 6);
	BOOST_CHECK(*--a == 1);
	BOOST_CHECK(*--a == 3);
	BOOST_CHECK(*--a == 8);
	BOOST_CHECK(a == b);
}

template <class Iterator>
void subtree_traversal(Iterator a, Iterator b) 
{
	BOOST_CHECK(*a++ == 3);
	BOOST_CHECK(*a++ == 1);
	BOOST_CHECK(*a++ == 6);
	BOOST_CHECK(*a++ == 4);
	BOOST_CHECK(*a++ == 7);
	BOOST_CHECK(a == b);
}

} // namespace preorder

namespace inorder {



template < class Tp, class Alloc = std::allocator<Tp> >
class flat_binary_tree {
 protected:
	std::list<Tp, Alloc> cont;
 public:
	
};

template <class Iterator>
void traversal(Iterator a, Iterator b)
{		
	BOOST_CHECK(*a++ == 1);
	BOOST_CHECK(*a++ == 3);
	BOOST_CHECK(*a++ == 4);
	BOOST_CHECK(*a++ == 6);
	BOOST_CHECK(*a++ == 7);
	BOOST_CHECK(*a++ == 8);
	BOOST_CHECK(*a++ == 10);
	BOOST_CHECK(*a++ == 11);
	BOOST_CHECK(*a++ == 12);
	BOOST_CHECK(*a++ == 13);
	BOOST_CHECK(*a++ == 14);
	BOOST_CHECK(a == b);
}

template <class Iterator>
void reverse_traversal(Iterator a, Iterator b)
{	
	BOOST_CHECK(*--a == 14);
	BOOST_CHECK(*--a == 13);
	BOOST_CHECK(*--a == 12);
	BOOST_CHECK(*--a == 11);
	BOOST_CHECK(*--a == 10);
	BOOST_CHECK(*--a == 8);
	BOOST_CHECK(*--a == 7);
	BOOST_CHECK(*--a == 6);
	BOOST_CHECK(*--a == 4);
	BOOST_CHECK(*--a == 3);
	BOOST_CHECK(*--a == 1);
	BOOST_CHECK(a == b);
}

} // namespace inorder

namespace postorder {

template <class Iterator>
void traversal(Iterator a, Iterator b)
{	
	BOOST_CHECK(*a++ == 1);	
	BOOST_CHECK(*a++ == 4);
	BOOST_CHECK(*a++ == 7);
	BOOST_CHECK(*a++ == 6);
	BOOST_CHECK(*a++ == 3);
	BOOST_CHECK(*a++ == 12);
	BOOST_CHECK(*a++ == 11);
	BOOST_CHECK(*a++ == 13);
	BOOST_CHECK(*a++ == 14);
	BOOST_CHECK(*a++ == 10);
	BOOST_CHECK(*a++ == 8);
	BOOST_CHECK(a == b);
}

template <class Iterator>
void reverse_traversal(Iterator a, Iterator b)
{	
	BOOST_CHECK(*--a == 8);	
	BOOST_CHECK(*--a == 10);
	BOOST_CHECK(*--a == 14);
	BOOST_CHECK(*--a == 13);
	BOOST_CHECK(*--a == 11);
	BOOST_CHECK(*--a == 12);
	BOOST_CHECK(*--a == 3);
	BOOST_CHECK(*--a == 6);
	BOOST_CHECK(*--a == 7);
	BOOST_CHECK(*--a == 4);
	BOOST_CHECK(*--a == 1);
	BOOST_CHECK(a == b);
}

} // namespace postorder

namespace ascending {

template <class Iterator>
void traversal_from_leaf4(Iterator a, Iterator b)
{	
	BOOST_CHECK(*a == 4);
	BOOST_CHECK(*++a == 6);
	BOOST_CHECK(*++a == 3);
	BOOST_CHECK(*++a == 8);
	BOOST_CHECK(++a == b);
}

} // namespace ascending

} // namespace test


#endif // LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_HPP
