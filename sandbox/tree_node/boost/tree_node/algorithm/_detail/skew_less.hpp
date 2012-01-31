// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_DETAIL_SKEW_LESS_HPP_INCLUDED
#define BOOST_TREE_NODE_ALGORITHM_DETAIL_SKEW_LESS_HPP_INCLUDED

#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/assert.hpp>

namespace boost { namespace tree_node { namespace _detail {

    template <typename Node1, typename Node2>
    bool skew_less(Node1 const& node1, Node2 const& node2)
    {
        ::boost::tree_node::depth_first_iterator<Node1 const> itr1(node1);
        ::boost::tree_node::depth_first_iterator<Node2 const> itr2(node2);

        while (itr1)
        {
            BOOST_ASSERT(itr2 && "The nodes are not lexicographically equal!");

            if (
                ::boost::tree_node::traversal_state(itr1)
              < ::boost::tree_node::traversal_state(itr2)
            )
            {
                return true;
            }

            if (
                ::boost::tree_node::traversal_state(itr2)
              < ::boost::tree_node::traversal_state(itr1)
            )
            {
                return false;
            }

            ++itr1;
            ++itr2;
        }

        BOOST_ASSERT(!itr2 && "The nodes are not lexicographically equal!");

        return false;
    }
}}}  // namespace boost::tree_node::_detail

#endif  // BOOST_TREE_NODE_ALGORITHM_DETAIL_SKEW_LESS_HPP_INCLUDED

