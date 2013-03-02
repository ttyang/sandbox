// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_BINARY_INDEX_OF_HPP
#define BOOST_TREE_NODE_ALGORITHM_BINARY_INDEX_OF_HPP

#include <boost/config.hpp>

#if !defined BOOST_NO_CXX11_NULLPTR
#include <cstddef>
#endif

#include <boost/tree_node/key/count.hpp>

//[reference__tree_node__binary_index_of
namespace boost { namespace tree_node {

    template <typename NodePointer, typename Value>
    Value
        binary_index_of(
            NodePointer node_ptr
          , Value offset
          , NodePointer const& root_ptr
        );

    template <typename NodePointer, typename Value>
    Value binary_index_of(NodePointer node_ptr, Value offset);

    //<-
    template <typename NodePointer, typename Value>
    Value
        binary_index_of(
            NodePointer node_ptr
          , Value offset
          , NodePointer const& root_ptr
        )
    {
        NodePointer child_ptr = node_ptr->get_left_child_ptr();

        if (child_ptr)
        {
            offset += get(*child_ptr, count_key());
        }

        if (root_ptr)
        {
            while (node_ptr != root_ptr)
            {
                child_ptr = node_ptr;
                node_ptr = node_ptr->get_parent_ptr();

                if (child_ptr == node_ptr->get_right_child_ptr())
                {
                    ++offset;

                    if ((child_ptr = node_ptr->get_left_child_ptr()))
                    {
                        offset += get(*child_ptr, count_key());
                    }
                }
            }
        }
        else
        {
            for (
                child_ptr = node_ptr;
                (node_ptr = node_ptr->get_parent_ptr());
                child_ptr = node_ptr
            )
            {
                if (child_ptr == node_ptr->get_right_child_ptr())
                {
                    ++offset;

                    if ((child_ptr = node_ptr->get_left_child_ptr()))
                    {
                        offset += get(*child_ptr, count_key());
                    }
                }
            }
        }

        return offset;
    }

    template <typename NodePointer, typename Value>
    inline Value binary_index_of(NodePointer node_ptr, Value offset)
    {
#if defined BOOST_NO_CXX11_NULLPTR
        return binary_index_of(node_ptr, offset, 0);
#else
        return binary_index_of(node_ptr, offset, nullptr);
#endif
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ALGORITHM_BINARY_INDEX_OF_HPP

