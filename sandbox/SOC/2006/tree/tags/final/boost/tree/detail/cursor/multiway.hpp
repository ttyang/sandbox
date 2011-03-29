//  Copyright (c) 2006, Bernhard Reiter
//
//  This code may be used under either of the following two licences:
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy 
//  of this software and associated documentation files (the "Software"), to deal 
//  in the Software without restriction, including without limitation the rights 
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
//  copies of the Software, and to permit persons to whom the Software is 
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in 
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
//  THE SOFTWARE. OF SUCH DAMAGE.
//
//  Or:
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// TODO: Use TR1 type_traits (integral_constant)

#ifndef BOOST_TREE_DETAIL_CURSOR_MULTIWAY_HPP
#define BOOST_TREE_DETAIL_CURSOR_MULTIWAY_HPP


namespace boost {
namespace tree {

template <class Container>
struct some_nary_node_base
{
	some_nary_node_base* parent;
	std::vector<some_nary_node_base*> children; //how do we get a ValueAlloc ?
};


class multiway_cursor_for_some_node
{
 private:
 	typedef multiway_cursor_for_some_node self_type;
 	
 	typedef some_node node_type;
	typedef node_traits<node_type> traits;
	
	typedef typename traits::value_type container_type;
	
	typedef typename container_type::value_type value_type;
	typedef typename container_type::reference_type reference;
	typedef typename container_type::pointer_type pointer;
	typedef typename container_type::size_type size_type;

	
	typedef typename traits::position_type position_type ;
	

 public:
 	//iterator part
 
 	explicit multiway_cursor_for_some_node(position_type pos)
 	 : m_pos(pos) {}
 	
 	multiway_cursor_for_some_node(self_type const& other)
 	{
 		m_pos = other.m_pos;
 	}
 	
 	//this could probably done more time-efficiently if we stored a size_type 
 	//together with the parent or so...
	reference operator*() 
	{
		typename container_type::iterator it =
			(static_cast<node_type*>(this->parent()))->begin();
		std::advance(it, std::distance((this->parent()).begin(), m_pos);
		return *it;
	}
	
	reference operator++()
	{
		++mpos; //not +sizeof(...)?
		return *this;
	}
	
	reference operator--()
	{
		--mpos;
		return *this;
	}
	
	//Container part
	self_type begin()
	{
		return multiway_cursor_for_some_node(m_pos->children->begin());
	}
	
	self_type end()
	{
		return multiway_cursor_for_some_node(m_pos->children->end());
	}
	
	size_type size()
	{
		return m_pos->children->size();
	}
	
	size_type max_size()
	{
		return m_pos->children->size(); //FIXME: this may be constrained for nary nodes.
	}
	
	//Cursor part
	//cursor with parent:
	self_type parent()
	{
		return multiway_cursor_for_some_node(m_pos->parent());
	}
	
 private:
 	position_type m_pos;
};

//concept check: Node::value_type Sequence?
template <class Node>
class multiway_cursor
{
};



} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_CURSOR_MULTIWAY_HPP