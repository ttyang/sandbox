
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

//[n2081_equal_error
// File: equal_error.cpp
#include "equal.hpp"

struct num
{
    int value;
    explicit num ( int v = 0 ) : value(v) {}
};

int main ( void )
{
    equal(num(1), num(1)); // Compiler error.
    return 0;
}
//]

