// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_OUTPUT_TABS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_OUTPUT_TABS_HPP_INCLUDED

#include <boost/tree_node/traversal_state.hpp>

void
    output_tabs(
        boost::tree_node::traversal_state state
      , unsigned int& ply_limit
      , unsigned int tab_limit
      , bool is_4_long
    );

#endif  // LIBS_TREE_NODE_EXAMPLE_OUTPUT_TABS_HPP_INCLUDED

