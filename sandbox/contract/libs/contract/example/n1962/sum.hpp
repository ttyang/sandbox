
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

//[n1962_sum_header
// File: sum.hpp
#ifndef SUM_HPP_
#define SUM_HPP_

#include <contract.hpp>

CONTRACT_FUNCTION(
    int (sum)( int count, (int*) array )
        precondition( count % 4 == 0 )
) ; // Separate body definition from function declaration (see ".cpp" file).

#endif // #include guard
//]

