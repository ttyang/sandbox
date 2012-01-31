// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_TRAVERSAL_STATE_HPP_INCLUDED
#define BOOST_TREE_NODE_TRAVERSAL_STATE_HPP_INCLUDED

//[reference__traversal_state
namespace boost { namespace tree_node {

    enum traversal_state
    {
        no_traversal
      , pre_order_traversal
      , post_order_traversal
      , breadth_first_traversal
      , in_order_traversal
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_TRAVERSAL_STATE_HPP_INCLUDED

