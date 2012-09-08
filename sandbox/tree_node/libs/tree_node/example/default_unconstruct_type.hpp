// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_DEFAULT_UNCONSTRUCT_TYPE_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_DEFAULT_UNCONSTRUCT_TYPE_HPP_INCLUDED

#include <cstddef>
#include <boost/config.hpp>

//[example__default_unconstructible_type
struct default_unconstructible_example_type
{
    std::size_t number;
    explicit default_unconstructible_example_type(std::size_t n);
    bool operator==(std::size_t n) const;
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

#if defined BOOST_TYPEOF_COMPLIANT
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TYPE(default_unconstructible_example_type)
#endif

#endif  // LIBS_TREE_NODE_EXAMPLE_DEFAULT_UNCONSTRUCT_TYPE_HPP_INCLUDED

