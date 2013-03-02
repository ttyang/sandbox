// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_BINARY_DESCENDANT_HPP
#define BOOST_TREE_NODE_ALGORITHM_BINARY_DESCENDANT_HPP

//[reference__tree_node__binary_descendant
namespace boost { namespace tree_node {

    template <typename NodePointer, typename Value, typename Compare>
    NodePointer
        binary_descendant(
            NodePointer node_ptr
          , Value const& value
          , Compare const& compare
        );

    //<-
    template <typename NodePointer, typename Value, typename Compare>
    NodePointer
        binary_descendant(
            NodePointer node_ptr
          , Value const& value
          , Compare const& compare
        )
    {
        while (node_ptr)
        {
            if (compare(value, *node_ptr))
            {
                node_ptr = node_ptr->get_left_child_ptr();
            }
            else if (compare(*node_ptr, value))
            {
                node_ptr = node_ptr->get_right_child_ptr();
            }
            else
            {
                return node_ptr;
            }
        }

        return node_ptr;
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ALGORITHM_BINARY_DESCENDANT_HPP

