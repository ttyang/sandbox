// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_TRAITS_RED_BLACK_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_TRAITS_RED_BLACK_NODE_HPP_INCLUDED

#include <boost/tree_node/traits/red_black_node_fwd.hpp>

//[reference__red_black_node_traits
namespace boost { namespace tree_node {

    template <typename NodeTraits>
    struct red_black_node_traits : NodeTraits
    {
        typedef bool color;

        static color get_color(typename NodeTraits::const_node_ptr n);
        static void set_color(typename NodeTraits::node_ptr n, color c);
        static color black();
        static color red();
    };

    //<-
    template <typename NodeTraits>
    inline typename red_black_node_traits<NodeTraits>::color
        red_black_node_traits<NodeTraits>::get_color(
            typename NodeTraits::const_node_ptr n
        )
    {
        return get(*n, red_flag_key());
    }

    template <typename NodeTraits>
    inline void
        red_black_node_traits<NodeTraits>::set_color(
            typename NodeTraits::node_ptr n
          , typename red_black_node_traits<NodeTraits>::color c
        )
    {
        put(*n, red_flag_key(), c);
    }

    template <typename NodeTraits>
    inline typename red_black_node_traits<NodeTraits>::color
        red_black_node_traits<NodeTraits>::black()
    {
        return false;
    }

    template <typename NodeTraits>
    inline typename red_black_node_traits<NodeTraits>::color
        red_black_node_traits<NodeTraits>::red()
    {
        return true;
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_TRAITS_RED_BLACK_NODE_HPP_INCLUDED

