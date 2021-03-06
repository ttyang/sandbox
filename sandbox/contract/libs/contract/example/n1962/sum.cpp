
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

//[n1962_sum
// File: sum.cpp
#include "sum.hpp"

int CONTRACT_FREE_BODY(sum) ( int count, int* array ) {
    int total = 0;
    for(int i = 0; i < count; ++i) total += array[i];
    return total;
}
//]

