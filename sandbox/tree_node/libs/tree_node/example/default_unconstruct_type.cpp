// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "default_unconstruct_type.hpp"

//[example__default_unconstructible_type__definitions
default_unconstructible_example_type::default_unconstructible_example_type(
    std::size_t n
) : number(n)
{
}

bool default_unconstructible_example_type::operator==(std::size_t n) const
{
    return number == n;
}

bool
    operator==(
        default_unconstructible_example_type const& lhs
      , default_unconstructible_example_type const& rhs
    )
{
    return lhs.number == rhs.number;
}

bool
    operator<(
        default_unconstructible_example_type const& lhs
      , default_unconstructible_example_type const& rhs
    )
{
    return lhs.number < rhs.number;
}
//]

