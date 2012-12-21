// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <algorithm>
#include <boost/assert.hpp>
#include "output_tabs.hpp"

void
    output_tabs(
        boost::tree_node::traversal_state state
      , unsigned int& ply_limit
      , unsigned int tab_limit
      , bool is_4_long
    )
{
    switch (state)
    {
        case boost::tree_node::pre_order_traversal:
        {
            ++ply_limit;

            for (
                unsigned int ply = 0;
                ply < (std::min)(ply_limit, tab_limit);
                ++ply
            )
            {
                std::cout << (is_4_long ? "    " : "  ");
            }

            std::cout << "(boost::tree_node::pre_order_traversal, ";
            break;
        }

        case boost::tree_node::post_order_traversal:
        {
            for (
                unsigned int ply = 0;
                ply < (std::min)(ply_limit, tab_limit);
                ++ply
            )
            {
                std::cout << (is_4_long ? "    " : "  ");
            }

            std::cout << "(boost::tree_node::post_order_traversal, ";
            --ply_limit;
            break;
        }

        default:
        {
            BOOST_ASSERT(false);
        }
    }
}

