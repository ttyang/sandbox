// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_OUTPUT_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_OUTPUT_FUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <boost/mpl/bool.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/key/data.hpp>
#include <boost/tree_node/key/count.hpp>
#include <boost/tree_node/key/height.hpp>
#include <boost/tree_node/key/position.hpp>

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
#include <boost/tree_node/key/accumulation.hpp>
#endif

#include "type_definitions.hpp"
#include "output_tabs.hpp"
#include <boost/assert.hpp>

template <typename Node>
void output_data_height_and_count(Node const& node, bool b)
{
    std::cout << get(node, boost::tree_node::data_key()).numerator();
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << get(node, boost::tree_node::height_key());
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << get(node, boost::tree_node::count_key());
}

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
template <typename Node>
void output_accumulations(Node const& node, bool b)
{
    std::cout << boost::tree_node::get<boost::tree_node::accumulation_key<> >(
        node
    ).numerator();
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << get(node, AccuHeightKey());
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << get(node, AccuCountKey()) << (
        b ? ", boost::rational<long>(" : ",boost::rational<long>("
    ) << get(node, AccuAccuKey()).numerator();
    if (b) std::cout << ", "; else std::cout << ',';
    std::cout << get(node, AccuAccuKey()).denominator() << ')';
}
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

template <typename Node>
void output_node_contents(Node const& node, bool b, boost::mpl::false_)
{
    output_data_height_and_count(node, b);
}

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
template <typename Node>
void output_node_contents(Node const& node, bool b, boost::mpl::true_)
{
    output_data_height_and_count(node, b);
    if (b) std::cout << ", "; else std::cout << ',';
    output_accumulations(node, b);
}
#endif

template <typename IncludeAccumulations>
struct output_node
{
    template <typename Node>
    void operator()(Node const& node) const
    {
        std::cout << '(';
        output_node_contents(node, true, IncludeAccumulations());
        std::cout << ')';
    }

    template <typename Key, typename Node>
    void operator()(Key const& key, Node const& node) const
    {
        std::cout << "(\"" << key << "\", ";
        output_node_contents(node, true, IncludeAccumulations());
        std::cout << ')';
    }
};

template <typename IncludeAccumulations>
class output_tree
{
    unsigned int _ply_limit;
    unsigned int _tab_limit;
    bool _b;

 public:
    output_tree(unsigned int ply_limit, unsigned int tab_limit, bool b)
      : _ply_limit(ply_limit), _tab_limit(tab_limit), _b(b)
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

        switch (state)
        {
            case boost::tree_node::pre_order_traversal:
            {
                output_tabs(++_ply_limit, _tab_limit, _b);
                std::cout << "(boost::tree_node::pre_order_traversal,";
                if (_b) std::cout << ' ';
                this->_output_contents(node, IncludeAccumulations());
                break;
            }

            case boost::tree_node::post_order_traversal:
            {
                output_tabs(_ply_limit, _tab_limit, _b);
                std::cout << "(boost::tree_node::post_order_traversal,";
                if (_b) std::cout << ' ';
                this->_output_contents(node, IncludeAccumulations());
                --_ply_limit;
                break;
            }

            default:
            {
                BOOST_ASSERT(false);
            }
        }

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

        switch (state)
        {
            case boost::tree_node::pre_order_traversal:
            {
                output_tabs(++_ply_limit, _tab_limit, _b);
                std::cout << "(boost::tree_node::pre_order_traversal,";
                if (_b) std::cout << ' ';
                std::cout << '\"' << key << (_b ? "\", " : "\",");
                this->_output_contents(node, IncludeAccumulations());
                break;
            }

            case boost::tree_node::post_order_traversal:
            {
                output_tabs(_ply_limit, _tab_limit, _b);
                std::cout << "(boost::tree_node::post_order_traversal,";
                if (_b) std::cout << ' ';
                std::cout << '\"' << key << (_b ? "\", " : "\",");
                this->_output_contents(node, IncludeAccumulations());
                --_ply_limit;
                break;
            }

            default:
            {
                BOOST_ASSERT(false);
            }
        }

        std::cout << ')';
    }

 private:
    template <typename Node>
    void _output_contents(Node const& node, boost::mpl::false_)
    {
        output_data_height_and_count(node, _b);
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    template <typename Node>
    void _output_contents(Node const& node, boost::mpl::true_)
    {
        output_data_height_and_count(node, _b);
        std::cout << ',' << std::endl;
        output_tabs(_ply_limit, _tab_limit, _b);
        output_accumulations(node, _b);
    }
#endif
};

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
template <typename Node>
void output_uint_and_char(Node const& node, bool b)
{
    std::cout << get(node, example_keys::your_uint());
    std::cout << (b ? ", \'" : ",\'");
    std::cout << static_cast<char>(get(node, example_keys::your_char()));
    std::cout << (b ? "\', " : "\',");
    std::cout << get(node, AccuYourUintKey());
}

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

class output_uint_char_tree
{
    unsigned int _ply_limit;
    unsigned int _tab_limit;
    bool _b;

 public:
    output_uint_char_tree(unsigned int p, unsigned int t, bool b)
      : _ply_limit(p), _tab_limit(t), _b(b)
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
        output_tabs_and_state(state, _ply_limit, _tab_limit, _b);
        output_uint_and_char(node, _b);
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
        output_tabs_and_state(state, _ply_limit, _tab_limit, _b);
        std::cout << '\"' << key << "\",";
        if (_b) std::cout << ' ';
        output_uint_and_char(node, _b);
        std::cout << ')';
    }
};

template <typename Node>
void output_gui(Node const& node, bool b)
{
    std::cout << get(node, example_keys::row_location());
    std::cout << (b ? ", " : ",");
    std::cout << get(node, example_keys::row_height());
    std::cout << (b ? ", " : ",");
    std::cout << get(node, example_keys::row_priority());
    std::cout << (b ? ", " : ",");
    std::cout << get(node, HeightSumKey());
    std::cout << (b ? ", " : ",");
    std::cout << get(node, MinPriorityKey());
}

struct output_gui_node
{
    template <typename Node>
    void operator()(Node const& node) const
    {
        std::cout << '(';
        output_gui(node, true);
        std::cout << ')';
    }

    template <typename Key, typename Node>
    void operator()(Key const& key, Node const& node) const
    {
        std::cout << "(\"" << key << "\", ";
        output_gui(node, true);
        std::cout << ')';
    }
};

class output_gui_tree
{
    unsigned int _ply_limit;
    unsigned int _tab_limit;
    bool _b;

 public:
    output_gui_tree(unsigned int p, unsigned int t, bool b)
      : _ply_limit(p), _tab_limit(t), _b(b)
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
        output_tabs_and_state(state, _ply_limit, _tab_limit, _b);
        output_gui(node, _b);
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
        output_tabs_and_state(state, _ply_limit, _tab_limit, _b);
        std::cout << '\"' << key << "\",";
        if (_b) std::cout << ' ';
        output_gui(node, _b);
        std::cout << ')';
    }
};
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

#if defined BOOST_TYPEOF_COMPLIANT

#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(output_node, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(output_tree, 1)

#if defined BOOST_TREE_NODE_CAN_USE_FUSION_WITH_TYPEOF
BOOST_TYPEOF_REGISTER_TYPE(output_uint_char_node)
BOOST_TYPEOF_REGISTER_TYPE(output_uint_char_tree)
BOOST_TYPEOF_REGISTER_TYPE(output_gui_node)
BOOST_TYPEOF_REGISTER_TYPE(output_gui_tree)
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION_WITH_TYPEOF

#endif  // BOOST_TYPEOF_COMPLIANT

#endif  // LIBS_TREE_NODE_EXAMPLE_OUTPUT_FUNCTIONS_HPP_INCLUDED

