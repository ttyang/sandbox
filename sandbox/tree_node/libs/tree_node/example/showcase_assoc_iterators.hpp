// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_SHOWCASE_ASSOC_ITERATORS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_SHOWCASE_ASSOC_ITERATORS_HPP_INCLUDED

#include <iostream>
#include <boost/typeof/typeof.hpp>
#include <boost/tree_node/typeof/breadth_first_desc_iterator.hpp>
#include <boost/tree_node/typeof/pre_order_desc_iterator.hpp>
#include <boost/tree_node/typeof/post_order_desc_iterator.hpp>
#include <boost/tree_node/typeof/depth_first_desc_iterator.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>

//[example__showcase_associative_iterators
template <
    typename Node
  , typename Function1
  , typename Function2
  , typename Function4
  , typename Function3
>
void
    showcase_associative_iterators(
        Node const& root
      , Function1 show1
      , Function2 show2
      , Function3 show3
      , Function4 show4
    )
{
    std::cout << "  Breadth-first: ";
    boost::tree_node::breadth_first_iterate(root, show1);
    std::cout << std::endl << "    sans root:     ";

    for (
        BOOST_AUTO_TPL(
            itr
          , boost::tree_node::make_breadth_first_descendant_iterator(root)
        );
        itr;
        ++itr
    )
    {
        show3(itr->first, boost::tree_node::dereference_iterator(itr));
    }

    std::cout << std::endl << "  Pre-order:     ";
    boost::tree_node::pre_order_iterate(root, show1);
    std::cout << std::endl << "    sans root:     ";

    for (
        BOOST_AUTO_TPL(
            itr
          , boost::tree_node::make_pre_order_descendant_iterator(root)
        );
        itr;
        ++itr
    )
    {
        show3(itr->first, boost::tree_node::dereference_iterator(itr));
    }

    std::cout << std::endl << "  Post-order:    ";
    boost::tree_node::post_order_iterate(root, show1);
    std::cout << std::endl << "    sans root:   ";

    for (
        BOOST_AUTO_TPL(
            itr
          , boost::tree_node::make_post_order_descendant_iterator(root)
        );
        itr;
        ++itr
    )
    {
        show3(itr->first, boost::tree_node::dereference_iterator(itr));
    }

    std::cout << std::endl << "  Depth-first:" << std::endl;
    boost::tree_node::depth_first_iterate(root, show2);
    std::cout << std::endl << "    sans root:" << std::endl;

    for (
        BOOST_AUTO_TPL(
            itr
          , boost::tree_node::make_depth_first_descendant_iterator(root)
        );
        itr;
        ++itr
    )
    {
        show4(itr, boost::tree_node::traversal_state(itr));
    }

    std::cout << std::endl;
}
//]

#endif  // LIBS_TREE_NODE_EXAMPLE_SHOWCASE_ASSOC_ITERATORS_HPP_INCLUDED

