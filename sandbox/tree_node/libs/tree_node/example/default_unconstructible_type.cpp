// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "default_unconstructible_type.hpp"

//[example__default_unconstructible_type__definitions
default_unconstructible_example_type::default_unconstructible_example_type()
{
}

default_unconstructible_example_type create_instance(std::size_t n)
{
    default_unconstructible_example_type instance;
    instance.number = n;
    return instance;
}
//]

