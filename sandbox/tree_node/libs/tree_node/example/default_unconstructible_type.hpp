// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_DEFAULT_UNCONSTRUCTIBLE_TYPE_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_DEFAULT_UNCONSTRUCTIBLE_TYPE_HPP_INCLUDED

#include <vector>

//[example__default_unconstructible_type
class default_unconstructible_example_type
{
    default_unconstructible_example_type();

    friend default_unconstructible_example_type
        create_instance(std::size_t n);

 public:
    std::size_t number;
};
//]

default_unconstructible_example_type create_instance(std::size_t n);

#endif  // LIBS_TREE_NODE_EXAMPLE_DEFAULT_UNCONSTRUCTIBLE_TYPE_HPP_INCLUDED

