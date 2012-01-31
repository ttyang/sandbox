// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_DEFAULT_UNCONSTRUCT_TYPE_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_DEFAULT_UNCONSTRUCT_TYPE_HPP_INCLUDED

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

//[example__default_unconstructible_type__operator_equal
bool
    operator==(
        default_unconstructible_example_type const& lhs
      , default_unconstructible_example_type const& rhs
    );
//]

//[example__default_unconstructible_type__operator_less
bool
    operator<(
        default_unconstructible_example_type const& lhs
      , default_unconstructible_example_type const& rhs
    );
//]

default_unconstructible_example_type create_instance(std::size_t n);

#endif  // LIBS_TREE_NODE_EXAMPLE_DEFAULT_UNCONSTRUCT_TYPE_HPP_INCLUDED

