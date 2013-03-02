// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_BINARY_LOWER_BOUND_HPP
#define BOOST_TREE_NODE_ALGORITHM_BINARY_LOWER_BOUND_HPP

#include <boost/utility/value_init.hpp>

//[reference__tree_node__binary_lower_bound
namespace boost { namespace tree_node {

    template <typename NodePointer, typename Value, typename Compare>
    NodePointer
        binary_lower_bound(
            NodePointer node_ptr
          , Value const& value
          , Compare const& compare
        );

    //<-
    template <typename NodePointer, typename Value, typename Compare>
    NodePointer
        binary_lower_bound(
            NodePointer node_ptr
          , Value const& value
          , Compare const& compare
        )
    {
        NodePointer result = ::boost::initialized_value;

        while (node_ptr)
        {
            if (compare(*node_ptr, value))
            {
                node_ptr = node_ptr->get_right_child_ptr();
            }
            else
            {
                result = node_ptr;
                node_ptr = node_ptr->get_left_child_ptr();
            }
        }

        return result;
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ALGORITHM_BINARY_LOWER_BOUND_HPP

