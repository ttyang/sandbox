// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_SHOWCASE_ITERATORS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_SHOWCASE_ITERATORS_HPP_INCLUDED

#include <iostream>
#include <boost/tree_node/breadth_first_iterator.hpp>
#include <boost/tree_node/pre_order_iterator.hpp>
#include <boost/tree_node/post_order_iterator.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/tree_node/in_order_iterator.hpp>

//[example__showcase_iterators
template <typename Node, typename Function1, typename Function2>
void
    showcase_iterators(
        Node const& root
      , Function1 show1
      , Function2 show2
    )
{
    std::cout << "  Breadth-first: ";
    boost::tree_node::breadth_first_iterate(root, show1);
    std::cout << std::endl << "    sans root:     ";
    boost::tree_node::breadth_first_iterate_descendants(root, show1);
    std::cout << std::endl << "  Pre-order:     ";
    boost::tree_node::pre_order_iterate(root, show1);
    std::cout << std::endl << "    sans root:     ";
    boost::tree_node::pre_order_iterate_descendants(root, show1);
    std::cout << std::endl << "  Post-order:    ";
    boost::tree_node::post_order_iterate(root, show1);
    std::cout << std::endl << "    sans root:   ";
    boost::tree_node::post_order_iterate_descendants(root, show1);
    std::cout << std::endl << "  Depth-first:" << std::endl;
    boost::tree_node::depth_first_iterate(root, show2);
    std::cout << std::endl << "    sans root:" << std::endl;
    boost::tree_node::depth_first_iterate_descendants(root, show2);
    std::cout << std::endl;
}
//]

//[example__showcase_in_order_iterator
template <typename Node, typename Function>
void showcase_in_order_iterator(Node const& node, Function show)
{
    std::cout << "  In-order fwd:  ";
    boost::tree_node::in_order_iterate_forward(node, show);
    std::cout << std::endl << "  In-order bck:  ";
    boost::tree_node::in_order_iterate_reverse(node, show);
    std::cout << std::endl;
}
//]

#endif  // LIBS_TREE_NODE_EXAMPLE_SHOWCASE_ITERATORS_HPP_INCLUDED

