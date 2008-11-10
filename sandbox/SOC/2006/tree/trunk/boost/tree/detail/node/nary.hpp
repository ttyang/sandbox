//  Copyright (c) 2006-2008, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file nary.hpp
 * Nary node implementation (with N=2, i.e. binary specialization)
 */
 
//TODO: maybe Boost.Optional (for the "empty" stuff?)
//Templatize with arity (so we can use this for multiway trees, too?)

#ifndef BOOST_TREE_DETAIL_NODE_NARY_HPP
#define BOOST_TREE_DETAIL_NODE_NARY_HPP

#include <boost/array.hpp>

#include <iterator>
#include <utility>

namespace boost {
namespace tree {
namespace detail {

using boost::array;

template <class T> struct binary_array : public array<T, 2> { };

//struct node_base;
/*
 * node_with_parent_base
 * node_base<N> leitet v. node_with_parent_base ab
 * node_base<2> auch.
 * 
 * we might want nodes that are based on other types of containers, right?
 */
 
class node_with_parent_base {
    typedef node_with_parent_base self_type;
    typedef self_type* base_pointer;
    typedef self_type const* const_base_pointer;

 public:
    base_pointer m_parent; // TODO: protect?
    
    node_with_parent_base()
    {
        m_parent = this;
    }
    
    base_pointer parent()
    {
        return m_parent;
    }
    
    base_pointer const parent() const
    {
        return m_parent;
    }
};

template <template <typename> class Container>
class node_base;

template <template <typename> class Container>
class node_base : public node_with_parent_base, public Container<node_base<Container>*> {
    typedef node_base<Container> self_type;
    
 public:
 
     typedef Container<node_base<Container>*> base_type;
     typedef typename base_type::size_type size_type;
    typedef self_type* base_pointer;
    typedef self_type const* const_base_pointer;
    
    node_base() : node_with_parent_base()
    { }
    
    static base_pointer nil()
    {
        static self_type m_nil_obj;
        static base_pointer m_nil = &m_nil_obj;
        return m_nil;
    }
    
    void init()
    {
        for (typename base_type::size_type i=0; i<base_type::size(); ++i)
            operator[](i) = nil();
    }

    // This injures Meyers' Item 36. OTOH, iterator adaptors do that, too, right?
    bool const empty() const
    {
        return ((this == nil()) || this->base_type::empty());
    }

    // O(n); n is number of parent's children
    typename base_type::size_type const get_index() const
    {
        typename base_type::size_type i = 0;
        while (static_cast<base_pointer>(this->m_parent)->base_type::operator[](i++) != this);
        return --i;
        //return (static_cast<base_pointer>(this->m_parent)->base_type::operator[](0) == this ? 0 : 1);
    }
};

template <>
class node_base<binary_array>
: public node_with_parent_base, public binary_array<node_base<binary_array>*> {
    typedef node_base<binary_array> self_type;
    
 public:
 
     typedef binary_array<node_base*> base_type;
    typedef self_type* base_pointer;
    typedef self_type const* const_base_pointer;
    
    node_base() : node_with_parent_base()
    { }
    
    static base_pointer nil()
    {
        static self_type m_nil_obj;
        static base_pointer m_nil = &m_nil_obj;
        return m_nil;
    }
    
    void init()
    {
        for (base_type::size_type i=0; i<base_type::max_size(); ++i)
            operator[](i) = nil();
    }

    // This injures Meyers' Item 36. OTOH, iterator adaptors do that, too, right?
    bool const empty() const
    {
        return (this == nil());
    }
    
    // Binary specific
    
    base_type::size_type rotate(base_type::size_type const& c)
    {
        //TODO: Optimise.
        base_pointer q = base_type::operator[](c);
        
        base_pointer B = (base_type::operator[](c))->base_type::operator[](c ? 0 : 1);
        //pre_rotate();
        
        //B swaps places with its m_parent:

        base_type::operator[](c) = B;
        B->m_parent = this;
        q->m_parent = this->m_parent;

        base_type::size_type qp = get_index();
        static_cast<base_pointer>(q->m_parent)->base_type::operator[](qp) = q;
        this->m_parent = q;
        q->base_type::operator[](c ? 0 : 1) = this;
        return qp;
        //return (c ? 0 : 1);
    }
    
    base_pointer detach(base_type::size_type m_pos)
    {
        base_pointer q = base_type::operator[](m_pos);
        base_type::operator[](m_pos) = 
            base_type::operator[](m_pos)
          ->base_type::operator[]((base_type::operator[](m_pos))
          ->base_type::operator[](0) == node_base::nil() ? 1 : 0);
        base_type::operator[](m_pos)->m_parent = this;
        return q;
    }
    
    // TODO: actually implement this.
    base_pointer detach(base_type::size_type index, 
                        base_type::size_type other_index, 
                        base_pointer other)
    {
        //Node::pre_splice(q, r);
        // splice out q
        base_pointer x = detach(index);

        // q has been spliced out, now relink it in place of r.                
        static_cast<base_pointer>(other->m_parent)->base_type::operator[](other_index) = this;
        m_parent = other->m_parent;

        for (base_type::size_type i=0; i<base_type::max_size(); ++i) {
            base_type::operator[](i) = other->base_type::operator[](i);
            base_type::operator[](i)->m_parent = this;
        }
        return x;
    }
    
    // O(1)
    base_type::size_type const get_index() const
    {
        return (static_cast<base_pointer>(this->m_parent)->base_type::operator[](0) == this ? 0 : 1);
    }
    
};

template <typename T, template <typename> class Container>
class node : public node_base<Container> {
 public:
     typedef T value_type;
    
    typedef Container<node_base<Container>*> container_type;

    typedef node<value_type, Container> node_type;
    typedef node_type* node_pointer;
    typedef node_type& node_reference;
    //typedef node_pointer position_type;
    typedef node_base<Container> base_type;
    typedef base_type* base_pointer;
    typedef base_type const* const_base_pointer;
    
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer;

    //enum size_t { first = 0, second = 1 };
    //typedef std::size_t size_type;
        
    // TODO: add observers.

    reference operator*() { return *m_data; } 

    const_reference operator*() const { return *m_data; } 
    
    node(pointer data) : base_type(), m_data(data) {}
    
    pointer data()
    {
        return m_data;
    }
    
 private:
    pointer m_data;
};

} // namespace detail
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_NODE_NARY_HPP
