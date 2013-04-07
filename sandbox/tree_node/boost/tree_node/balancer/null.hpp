// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BALANCER_NULL_HPP_INCLUDED
#define BOOST_TREE_NODE_BALANCER_NULL_HPP_INCLUDED

//[reference__null_balancer
namespace boost { namespace tree_node {

    struct null_balancer
    {
        template <typename NodePointer>
        static NodePointer post_insert(NodePointer node_ptr);

        template <typename Node>
        static bool choose_predecessor(Node const& node);

        template <typename Node>
        static bool pre_erase(Node const& node);

        template <typename NodePointer>
        static NodePointer post_erase_left(NodePointer node_ptr);

        template <typename NodePointer>
        static NodePointer post_erase_right(NodePointer node_ptr);
    };

    //<-
    template <typename NodePointer>
    inline NodePointer null_balancer::post_insert(NodePointer node_ptr)
    {
        return node_ptr;
    }

    template <typename Node>
    inline bool null_balancer::choose_predecessor(Node const& node)
    {
        return true;
    }

    template <typename Node>
    inline bool null_balancer::pre_erase(Node const& node)
    {
        return true;
    }

    template <typename NodePointer>
    inline NodePointer null_balancer::post_erase_left(NodePointer node_ptr)
    {
        return node_ptr;
    }

    template <typename NodePointer>
    inline NodePointer null_balancer::post_erase_right(NodePointer node_ptr)
    {
        return node_ptr;
    }
    //->

    namespace balancer {

        typedef ::boost::tree_node::null_balancer null;
    }  // namespace balancer
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_BALANCER_NULL_HPP_INCLUDED

