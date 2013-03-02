// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_OUTPUT_TABS_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_OUTPUT_TABS_HPP_INCLUDED

#include <boost/tree_node/traversal_state.hpp>

void output_tabs(unsigned int ply_limit, unsigned int tab_limit, bool b);

void
    output_tabs_and_state(
        boost::tree_node::traversal_state state
      , unsigned int& ply_limit
      , unsigned int tab_limit
      , bool b
    );

#endif  // LIBS_TREE_NODE_EXAMPLE_OUTPUT_TABS_HPP_INCLUDED

