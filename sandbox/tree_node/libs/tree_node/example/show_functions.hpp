// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_SHOW_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_SHOW_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>

void
    show_tabs(
        boost::tree_node::traversal_state state
      , unsigned int& ply_limit
    );

//[example__show_number
template <typename Node>
void show_number(Node const& node)
{
    std::cout << ", " << node.get_data().number;
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
        std::cout << node.get_data().number << ')' << std::endl;
    }
};
//]

//[example__show_key_and_number
template <typename Key, typename Node>
void show_key_and_number(Key const& key, Node const& node)
{
    std::cout << "(\"" << key << "\", " << node.get_data().number << ')';
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
        std::cout << '\"' << itr->first << "\", ";
        std::cout << boost::tree_node::dereference_iterator(
            itr
        ).get_data().number;
        std::cout << ')' << std::endl;
    }
};
//]

//[example__show_data
template <typename Node>
void show_data(Node const& node)
{
#if 0
    std::cout << ", \"" << node.get_data() << '\"';
#else
    std::cout << "(\"" << node.get_data() << "\", " << node.get_height();
    std::cout << ", " << node.get_count() << ')';
#endif
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
        std::cout << '\"' << node.get_data() << "\", " << node.get_height();
        std::cout << ", " << node.get_count() << ')' << std::endl;
    }
};
//]

//[example__show_key_and_data
template <typename Key, typename Node>
void show_key_and_data(Key const& key, Node const& node)
{
    std::cout << "(\"" << key << "\", \"" << node.get_data() << "\", ";
    std::cout << node.get_height() << ", " << node.get_count() << ')';
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
        std::cout << '\"' << itr->first << "\", \"";
        std::cout << boost::tree_node::dereference_iterator(itr).get_data();
        std::cout << "\", ";
        std::cout << boost::tree_node::dereference_iterator(itr).get_height();
        std::cout << ", ";
        std::cout << boost::tree_node::dereference_iterator(itr).get_count();
        std::cout << ')' << std::endl;
    }
};
//]

#if defined BOOST_TYPEOF_COMPLIANT
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(show_data_tree)
BOOST_TYPEOF_REGISTER_TYPE(show_key_and_data_tree)
#endif

#endif  // LIBS_TREE_NODE_EXAMPLE_SHOW_FUNCTIONS_HPP_INCLUDED

