// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_ASSOC_ITERATOR_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_ASSOC_ITERATOR_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/iterator/breadth_first_descendant.hpp>
#include <boost/tree_node/iterator/pre_order_descendant.hpp>
#include <boost/tree_node/iterator/post_order_descendant.hpp>
#include <boost/tree_node/iterator/depth_first_descendant.hpp>
#include <boost/tree_node/iterator/dereference.hpp>

template <typename NodeIterator, typename Function>
void associative_iterator_out(NodeIterator itr, Function f, unsigned int n)
{
    for (unsigned int i = 0; itr; ++itr)
    {
        if (!i)
        {
            std::cout << std::endl << "            ";
        }

        f(itr->first, boost::tree_node::dereference_iterator(itr));

        if (++i == n)
        {
            i = 0;
        }
    }
}

template <typename NodeIterator, typename Function>
void associative_iterator_out(NodeIterator itr, Function f, char const* text)
{
    for (std::cout << ';' << std::endl << text; itr; ++itr)
    {
        f(
            itr->first
          , boost::tree_node::dereference_iterator(itr)
          , boost::tree_node::traversal_state(itr)
        );
    }
}

template <typename Node, typename Function>
void associative_out_bf_pre_post(Node const& node, Function f, unsigned int n)
{
    std::cout << ';' << std::endl << "        emplacer[bf_d_vals]";
    associative_iterator_out(
        boost::tree_node::make_breadth_first_descendant_iterator(node)
      , f
      , n
    );
    std::cout << ';' << std::endl << "        emplacer[pre_d_vals]";
    associative_iterator_out(
        boost::tree_node::make_pre_order_descendant_iterator(node)
      , f
      , n
    );
    std::cout << ';' << std::endl << "        emplacer[post_d_vals]";
    associative_iterator_out(
        boost::tree_node::make_post_order_descendant_iterator(node)
      , f
      , n
    );
}

template <typename Node, typename Function>
void associative_out_df(Node const& node, Function f)
{
    associative_iterator_out(
        boost::tree_node::make_depth_first_descendant_iterator(node)
      , f
      , "        emplacer[df_d_vals]"
    );
}

#endif  // LIBS_TREE_NODE_EXAMPLE_ASSOC_ITERATOR_FUNCTIONS_HPP_INCLUDED

