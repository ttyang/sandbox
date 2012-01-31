// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_SHOW_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_SHOW_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <boost/tree_node/traversal_state.hpp>

void
    show_tabs(
        boost::tree_node::traversal_state state
      , unsigned int& ply_limit
    );

//[example__show_number
template <typename Node>
void show_number(Node const& node)
{
    std::cout << ' ' << node.get_data().number;
}
//]

//[example__show_number_tree
class show_number_tree
{
    unsigned int ply_limit;

 public:
    show_number_tree();

    template <typename Node>
    void
        operator()(
            Node const& node
          , boost::tree_node::traversal_state state
        )
    {
        show_tabs(state, ply_limit);
        std::cout << node.get_data().number << std::endl;
    }
};
//]

//[example__show_key_and_number
template <typename Key, typename Node>
void show_key_and_number(Key const& key, Node const& node)
{
    std::cout << " [" << key << ", " << node.get_data().number << ']';
}
//]

//[example__show_key_and_number_tree
class show_key_and_number_tree
{
    unsigned int ply_limit;

 public:
    show_key_and_number_tree();

    template <typename Iterator>
    void
        operator()(
            Iterator const& itr
          , boost::tree_node::traversal_state state
        )
    {
        show_tabs(state, ply_limit);
        show_key_and_number(itr->first, itr->second);
        std::cout << std::endl;
    }
};
//]

//[example__show_data
template <typename Node>
void show_data(Node const& node)
{
    std::cout << ' ' << node.get_data();
}
//]

//[example__show_data_tree
class show_data_tree
{
    unsigned int ply_limit;

 public:
    show_data_tree();

    template <typename Node>
    void
        operator()(
            Node const& node
          , boost::tree_node::traversal_state state
        )
    {
        show_tabs(state, ply_limit);
        std::cout << node.get_data();
        std::cout << "  (Depth = " << node.get_depth() << ')';
        std::cout << std::endl;
    }
};
//]

//[example__show_key_and_data
template <typename Key, typename Node>
void show_key_and_data(Key const& key, Node const& node)
{
    std::cout << " [" << key << ", " << node.get_data() << ']';
}
//]

//[example__show_key_and_data_tree
class show_key_and_data_tree
{
    unsigned int ply_limit;

 public:
    show_key_and_data_tree();

    template <typename Iterator>
    void
        operator()(
            Iterator const& itr
          , boost::tree_node::traversal_state state
        )
    {
        show_tabs(state, ply_limit);
        show_key_and_data(itr->first, itr->second);
        std::cout << "  (Depth = " << itr->second.get_depth() << ')';
        std::cout << std::endl;
    }
};
//]

#endif  // LIBS_TREE_NODE_EXAMPLE_SHOW_FUNCTIONS_HPP_INCLUDED

