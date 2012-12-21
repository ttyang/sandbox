// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_ITERATOR_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_ITERATOR_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <boost/tree_node/breadth_first_iterator.hpp>
#include <boost/tree_node/breadth_first_desc_iterator.hpp>
#include <boost/tree_node/pre_order_iterator.hpp>
#include <boost/tree_node/pre_order_desc_iterator.hpp>
#include <boost/tree_node/post_order_iterator.hpp>
#include <boost/tree_node/post_order_desc_iterator.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/tree_node/depth_first_desc_iterator.hpp>
#include <boost/tree_node/in_order_iterator.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>

template <typename NodeIterator, typename Function>
void iterator_out(NodeIterator itr, Function f, unsigned int n)
{
    for (unsigned int i = 0; itr; ++itr)
    {
        if (!i)
        {
            std::cout << std::endl << "            ";
        }

        f(*itr);

        if (++i == n)
        {
            i = 0;
        }
    }
}

template <typename Node, typename Function>
void iterator_out_bf_pre_post(Node const& node, Function f, unsigned int n)
{
    std::cout << std::endl << "        emplacer[bf_vals]";
    iterator_out(boost::tree_node::make_breadth_first_iterator(node), f, n);
    std::cout << ';' << std::endl << "        emplacer[pre_vals]";
    iterator_out(boost::tree_node::make_pre_order_iterator(node), f, n);
    std::cout << ';' << std::endl << "        emplacer[post_vals]";
    iterator_out(boost::tree_node::make_post_order_iterator(node), f, n);
}

template <typename Node, typename Function>
void iterator_out_in_order(Node const& node, Function f, unsigned int n)
{
    std::cout << ';' << std::endl << "        emplacer[in_vals]";
    iterator_out(boost::tree_node::in_order_iterator<Node const>(node), f, n);
}

template <typename Node, typename Function>
void iterator_out_df(Node const& node, Function f)
{
    std::cout << ';' << std::endl << "        emplacer[df_vals]";

    for (
        boost::tree_node::depth_first_iterator<Node const> itr(node);
        itr;
        ++itr
    )
    {
        f(
            boost::tree_node::dereference_iterator(itr)
          , boost::tree_node::traversal_state(itr)
        );
    }

    std::cout << ';' << std::endl;
}

#endif  // LIBS_TREE_NODE_EXAMPLE_ITERATOR_FUNCTIONS_HPP_INCLUDED

