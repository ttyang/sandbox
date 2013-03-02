// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_BINARY_DESCENDANT_AT_INDEX_HPP
#define BOOST_TREE_NODE_ALGORITHM_BINARY_DESCENDANT_AT_INDEX_HPP

#include <boost/tree_node/key/count.hpp>
#include <boost/assert.hpp>

//[reference__tree_node__binary_descendant_at_index
namespace boost { namespace tree_node {

    template <typename NodePointer, typename Index>
    NodePointer binary_descendant_at_index(NodePointer node_ptr, Index index);

    //<-
    template <typename NodePointer, typename Index>
    NodePointer binary_descendant_at_index(NodePointer node_ptr, Index index)
    {
        for (NodePointer child_ptr;;)
        {
            if ((child_ptr = node_ptr->get_left_child_ptr()))
            {
                Index const count = get(*child_ptr, count_key());

                if (index < count)
                {
                    node_ptr = child_ptr;
                }
                else if (count < index)
                {
                    BOOST_ASSERT_MSG(
                        node_ptr->get_right_child_ptr()
                      , "Check modifier methods or with_count adaptor."
                    );
                    index -= count + 1;
                    node_ptr = node_ptr->get_right_child_ptr();
                }
                else
                {
                    break;
                }
            }
            else if ((child_ptr = node_ptr->get_right_child_ptr()))
            {
                if (index)
                {
                    --index;
                    node_ptr = child_ptr;
                }
                else
                {
                    break;
                }
            }
            else
            {
                BOOST_ASSERT_MSG(
                    !index
                  , "Check modifier methods or with_count adaptor."
                );
                break;
            }
        }

        return node_ptr;
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ALGORITHM_BINARY_DESCENDANT_AT_INDEX_HPP

