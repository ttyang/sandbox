// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_OUTPUT_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_OUTPUT_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <boost/mpl/bool.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/data_key.hpp>
#include <boost/tree_node/count_key.hpp>
#include <boost/tree_node/height_key.hpp>
#include <boost/tree_node/position_key.hpp>
#include <boost/tree_node/accumulation_key.hpp>
#include "type_definitions.hpp"
#include "output_tabs.hpp"

template <typename Node>
void output_data_height_and_count(Node const& node, bool b, boost::mpl::false_)
{
    std::cout << get(node, boost::tree_node::data_key());
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << get(node, boost::tree_node::height_key());
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << get(node, boost::tree_node::count_key());
}

template <typename Node>
void output_data_height_and_count(Node const& node, bool b, boost::mpl::true_)
{
    std::cout << boost::tree_node::get<boost::tree_node::data_key>(node);
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << boost::tree_node::get<boost::tree_node::height_key>(node);
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << boost::tree_node::get<boost::tree_node::count_key>(node);
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << boost::tree_node::get<boost::tree_node::accumulation_key<> >(
        node
    );
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << boost::tree_node::get<AccuHeightKey>(node);
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << boost::tree_node::get<AccuCountKey>(node);
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << boost::tree_node::get<AccuAccuKey>(node);
}

template <typename Node>
void output_uint_and_char(Node const& node, bool b)
{
    std::cout << boost::tree_node::get<example_keys::your_uint>(
        node
    ) << (b ? ", \'" : ",\'") << static_cast<char>(
        boost::tree_node::get<example_keys::your_char>(node)
    ) << (b ? "\', " : "\',") << boost::tree_node::get<AccuYourUintKey>(node);
}

template <typename IncludeAccumulations>
struct output_node
{
    template <typename Node>
    void operator()(Node const& node) const
    {
        std::cout << '(';
        output_data_height_and_count(node, true, IncludeAccumulations());
        std::cout << ')';
    }

    template <typename Key, typename Node>
    void operator()(Key const& key, Node const& node) const
    {
        std::cout << "(\"" << key << "\", ";
        output_data_height_and_count(node, true, IncludeAccumulations());
        std::cout << ')';
    }
};

struct output_uint_char_node
{
    template <typename Node>
    void operator()(Node const& node) const
    {
        std::cout << '(';
        output_uint_and_char(node, true);
        std::cout << ')';
    }

    template <typename Key, typename Node>
    void operator()(Key const& key, Node const& node) const
    {
        std::cout << "(\"" << key << "\", ";
        output_uint_and_char(node, true);
        std::cout << ')';
    }
};

template <typename IncludeAccumulations>
class output_tree
{
    unsigned int _ply_limit;
    unsigned int _tab_limit;
    bool _is_4_long;

 public:
    output_tree(unsigned int ply_limit, unsigned int tab_limit, bool is_4_long)
      : _ply_limit(ply_limit), _tab_limit(tab_limit), _is_4_long(is_4_long)
    {
    }

    template <typename Node>
    void
        operator()(
            Node const& node
          , boost::tree_node::traversal_state state
        )
    {
        std::cout << std::endl;
        output_tabs(state, _ply_limit, _tab_limit, _is_4_long);
        output_data_height_and_count(node, true, IncludeAccumulations());
        std::cout << ')';
    }

    template <typename Key, typename Node>
    void
        operator()(
            Key const& key
          , Node const& node
          , boost::tree_node::traversal_state state
        )
    {
        std::cout << std::endl;
        output_tabs(state, _ply_limit, _tab_limit, _is_4_long);
        std::cout << '\"' << key << "\",";
        if (_is_4_long) std::cout << ' ';
        output_data_height_and_count(node, _is_4_long, IncludeAccumulations());
        std::cout << ')';
    }
};

class output_uint_char_tree
{
    unsigned int _ply_limit;
    unsigned int _tab_limit;
    bool _is_4_long;

 public:
    output_uint_char_tree(
        unsigned int ply_limit
      , unsigned int tab_limit
      , bool is_4_long
    ) : _ply_limit(ply_limit), _tab_limit(tab_limit), _is_4_long(is_4_long)
    {
    }

    template <typename Node>
    void
        operator()(
            Node const& node
          , boost::tree_node::traversal_state state
        )
    {
        std::cout << std::endl;
        output_tabs(state, _ply_limit, _tab_limit, _is_4_long);
        output_uint_and_char(node, _is_4_long);
        std::cout << ')';
    }

    template <typename Key, typename Node>
    void
        operator()(
            Key const& key
          , Node const& node
          , boost::tree_node::traversal_state state
        )
    {
        std::cout << std::endl;
        output_tabs(state, _ply_limit, _tab_limit, _is_4_long);
        std::cout << '\"' << key << "\",";
        if (_is_4_long) std::cout << ' ';
        output_uint_and_char(node, _is_4_long);
        std::cout << ')';
    }
};

#if defined BOOST_TYPEOF_COMPLIANT
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(output_node, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(output_tree, 1)
#endif

#endif  // LIBS_TREE_NODE_EXAMPLE_OUTPUT_FUNCTIONS_HPP_INCLUDED

