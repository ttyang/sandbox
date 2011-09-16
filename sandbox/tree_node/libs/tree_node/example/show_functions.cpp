// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "show_functions.hpp"

//[example__show_tabs
void
    show_tabs(
        boost::tree_node::traversal_state state
      , unsigned int& depth_limit
    )
{
    switch (state)
    {
        case boost::tree_node::pre_order_traversal:
        {
            ++depth_limit;

            for (unsigned int depth = 0; depth < depth_limit; ++depth)
            {
                std::cout << "    ";
            }

            std::cout << "Pre-order: ";
            break;
        }

        case boost::tree_node::post_order_traversal:
        {
            for (unsigned int depth = 0; depth < depth_limit; ++depth)
            {
                std::cout << "    ";
            }

            std::cout << "Post-order: ";
            --depth_limit;
            break;
        }
    }
}
//]

show_number_tree::show_number_tree() : depth_limit(1)
{
}

show_key_and_number_tree::show_key_and_number_tree() : depth_limit(1)
{
}

show_data_tree::show_data_tree() : depth_limit(1)
{
}

show_key_and_data_tree::show_key_and_data_tree() : depth_limit(1)
{
}

