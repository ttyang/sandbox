// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_TRAITS_BINARY_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_TRAITS_BINARY_NODE_HPP_INCLUDED

#include <boost/tree_node/traits/binary_node_fwd.hpp>

//[reference__binary_node_traits
namespace boost { namespace tree_node {

    template <typename Node>
    struct binary_node_traits
    {
        typedef Node node;
        typedef typename Node::pointer node_ptr;
        typedef typename Node::const_pointer const_node_ptr;

        static const_node_ptr get_parent(const_node_ptr n);
        static node_ptr get_parent(node_ptr n);
        static void set_parent(node_ptr n, node_ptr p);
        static const_node_ptr get_left(const_node_ptr n);
        static node_ptr get_left(node_ptr n);
        static void set_left(node_ptr n, node_ptr l);
        static const_node_ptr get_right(const_node_ptr n);
        static node_ptr get_right(node_ptr n);
        static void set_right(node_ptr n, node_ptr r);
    };

    //<-
    template <typename Node>
    inline typename binary_node_traits<Node>::const_node_ptr
        binary_node_traits<Node>::get_parent(const_node_ptr n)
    {
        return n->get_parent_ptr();
    }

    template <typename Node>
    inline typename binary_node_traits<Node>::node_ptr
        binary_node_traits<Node>::get_parent(node_ptr n)
    {
        return n->get_parent_ptr();
    }

    template <typename Node>
    inline void binary_node_traits<Node>::set_parent(node_ptr n, node_ptr p)
    {
        n->_set_parent_ptr(p);
    }

    template <typename Node>
    inline typename binary_node_traits<Node>::const_node_ptr
        binary_node_traits<Node>::get_left(const_node_ptr n)
    {
        return n->get_left_child_ptr();
    }

    template <typename Node>
    inline typename binary_node_traits<Node>::node_ptr
        binary_node_traits<Node>::get_left(node_ptr n)
    {
        return n->get_left_child_ptr();
    }

    template <typename Node>
    inline void binary_node_traits<Node>::set_left(node_ptr n, node_ptr l)
    {
        n->_set_left_child_ptr(l);
    }

    template <typename Node>
    inline typename binary_node_traits<Node>::const_node_ptr
        binary_node_traits<Node>::get_right(const_node_ptr n)
    {
        return n->get_right_child_ptr();
    }

    template <typename Node>
    inline typename binary_node_traits<Node>::node_ptr
        binary_node_traits<Node>::get_right(node_ptr n)
    {
        return n->get_right_child_ptr();
    }

    template <typename Node>
    inline void binary_node_traits<Node>::set_right(node_ptr n, node_ptr r)
    {
        n->_set_right_child_ptr(r);
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED

