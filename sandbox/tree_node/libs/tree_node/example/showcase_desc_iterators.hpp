// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_SHOWCASE_DESC_ITERATORS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_SHOWCASE_DESC_ITERATORS_HPP_INCLUDED

#include <iostream>
#include <boost/tree_node/typeof.hpp>

//[example__showcase_descendant_iterators
template <typename Node, typename Function1, typename Function2>
void
    showcase_descendant_iterators(
        Node const& root
      , Function1 show1
      , Function2 show2
    )
{
    std::cout << "    Breadth-first traversal:";

    for (
        BOOST_AUTO(
            itr
          , boost::tree_node::make_breadth_first_descendant_iterator(root)
        );
        itr;
        ++itr
    )
    {
        show1(itr->first, itr->second);
    }

    std::cout << std::endl << "    Pre-order traversal:";

    for (
        BOOST_AUTO(
            itr
          , boost::tree_node::make_pre_order_descendant_iterator(root)
        );
        itr;
        ++itr
    )
    {
        show1(itr->first, itr->second);
    }

    std::cout << std::endl << "    Post-order traversal:";

    for (
        BOOST_AUTO(
            itr
          , boost::tree_node::make_post_order_descendant_iterator(root)
        );
        itr;
        ++itr
    )
    {
        show1(itr->first, itr->second);
    }

    std::cout << std::endl << "    Depth-first traversal:" << std::endl;

    for (
        BOOST_AUTO(
            itr
          , boost::tree_node::make_depth_first_descendant_iterator(root)
        );
        itr;
        ++itr
    )
    {
        show2(itr, boost::tree_node::traversal_state(itr));
    }

    std::cout << std::endl;
}
//]

#endif  // LIBS_TREE_NODE_EXAMPLE_SHOWCASE_DESC_ITERATORS_HPP_INCLUDED

