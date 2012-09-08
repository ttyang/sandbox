// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/assert.hpp>
#include "show_functions.hpp"

//[example__show_tabs
void
    show_tabs(
        boost::tree_node::traversal_state state
      , unsigned int& ply_limit
    )
{
    switch (state)
    {
        case boost::tree_node::pre_order_traversal:
        {
            ++ply_limit;
            std::cout << "    ";

            for (unsigned int ply = 0; ply < ply_limit; ++ply)
            {
                std::cout << "    ";
            }

            std::cout << "(boost::tree_node::pre_order_traversal, ";
            break;
        }

        case boost::tree_node::post_order_traversal:
        {
            std::cout << "    ";

            for (unsigned int ply = 0; ply < ply_limit; ++ply)
            {
                std::cout << "    ";
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
//]

show_number_tree::show_number_tree() : ply_limit(1)
{
}

show_key_and_number_tree::show_key_and_number_tree() : ply_limit(1)
{
}

show_data_tree::show_data_tree() : ply_limit(1)
{
}

show_key_and_data_tree::show_key_and_data_tree() : ply_limit(1)
{
}

