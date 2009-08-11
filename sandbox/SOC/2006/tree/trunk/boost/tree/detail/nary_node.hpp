//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file nary_node.hpp
 * Nary node implementation (with N=2, i.e. binary specialization)
 */
 
//Templatize with arity (so we can use this for multiway trees, too?)

#ifndef BOOST_TREE_DETAIL_NARY_NODE_HPP
#define BOOST_TREE_DETAIL_NARY_NODE_HPP

#include <boost/array.hpp>

#include <iterator>
#include <utility>

namespace boost {
namespace tree {
namespace detail {

using boost::array;
 
class node_with_parent_base {
public:
    node_with_parent_base* m_parent; // TODO: protect?
    
    node_with_parent_base()
    {
        m_parent = this;
    }
    
    node_with_parent_base(node_with_parent_base* p) : m_parent(p) {}
    
    node_with_parent_base* parent()
    {
        return m_parent;
    }
    
    node_with_parent_base* const parent() const
    {
        return m_parent;
    }
};

void attach(node_with_parent_base* child, node_with_parent_base* parent)
{
    child->m_parent = parent;
}

class node_with_children_base;

class node_with_children_base {
public:
    typedef array<node_with_children_base*, 2> children_type;
    
    node_with_children_base()
    {
        init();
    }

    inline void init()
    {
        for (children_type::size_type i=0; i<children_type::size(); ++i)
            m_children[i] = 0;
    }

//protected:
    children_type m_children;
};

void attach(node_with_children_base*& to, node_with_children_base* p_node, node_with_children_base*& parent)
{
    // Only relevant for non-leaf insertion:
    parent = to;

    to = p_node;
}

static void splice(node_with_children_base*& to, node_with_children_base*& from)
{
    to = from;
    from = 0; 
}

class node_base
: public node_with_parent_base, public node_with_children_base {
public:
    node_base() : node_with_parent_base(), node_with_children_base() {}

    node_base(node_with_parent_base* p)
    : node_with_parent_base(p), node_with_children_base() {}
    
    node_base* detach(children_type::size_type m_pos)
    {
        node_with_children_base::children_type::size_type parent_idx = get_index();

        if (m_children[m_pos] != 0) // Set child's parent only if there _is_ a child
            static_cast<node_base*>(m_children[m_pos])->m_parent = m_parent;

        static_cast<node_base*>(m_parent)->m_children[parent_idx]
            = m_children[m_pos];
        
        return &*this;
    }

    // O(1)
    children_type::size_type const get_index() const
    {
        return (static_cast<node_base*>(this->m_parent)->m_children[0] == this ? 0 : 1);
    }
};

//node_with_children_base::children_type::size_type
void
rotate(node_with_children_base*& child, node_base* parent
     , node_with_children_base::children_type::size_type const& c)
{
    //TODO: Optimise.
    node_base* q = static_cast<node_base*>(child);
    
    node_base* B = static_cast<node_base*>(child->m_children[(c ? 0 : 1)]);
    //pre_rotate();
    
    //B swaps places with its m_parent:

    child = B;
    B->m_parent = parent;
    q->m_parent = parent->m_parent;

    node_with_children_base::children_type::size_type qp = parent->get_index();
    static_cast<node_base*>(q->m_parent)->m_children[qp] = q;
    parent->m_parent = q;
    q->m_children[(c ? 0 : 1)] = parent;
    //return qp;
    //return (c ? 0 : 1);
}

void attach(node_base* parent, node_with_children_base*& parent_child, node_base* child, node_with_children_base*& child_child)
{
    attach(static_cast<node_with_parent_base*>(child), static_cast<node_with_parent_base*>(parent));
    
    // Only relevant for non-leaf insertion:
    if (parent_child != 0)
        static_cast<node_base*>(parent_child)->m_parent = child;

    attach(parent_child, static_cast<node_with_children_base*>(child), child_child);
}

void splice(node_base* to_parent, node_with_children_base*& to, node_with_children_base*& from)
{
    static_cast<node_base*>(from)->m_parent = to_parent;

    splice(to, from);
}

class descending_node_base
: public node_with_children_base {
};

template <typename T>
class ascending_node : public node_base {
public:
    typedef T value_type;

    typedef ascending_node<value_type> node_type;
    typedef node_type* node_pointer;
    typedef node_type& node_reference;
    
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer;

    //enum size_t { first = 0, second = 1 };
    //typedef std::size_t size_type;

    reference operator*() { return m_data; } 

    const_reference operator*() const { return m_data; } 
    
    ascending_node(value_type data) : node_base(), m_data(data) {}
 
    ascending_node(value_type data, node_base* p) : node_base(p), m_data(data) {}
    
private:
    value_type m_data;
};

} // namespace detail
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_NARY_NODE_HPP
