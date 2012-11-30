//ChangeLog:
//  2012-10-25.1521 CST
//    Copied code from unrolled_tuple.cpp from:
//      https://github.com/ericniebler/home/tree/master/src/tuple
//
///////////////////////////////////////////////////////////////////////////////
// unrolled_tuple.cpp
//
// Copyright 2012 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "./tree_builder.hpp"
template<unsigned I>
struct leaf
{};

int main()
{
    auto y = tree_builder<1>::make_tree(::make_tuple(leaf<100>(),leaf<101>(),leaf<102>()));
    return 0;
}

