
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

//[n2081_min
// File: min.cpp
#include "min.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    BOOST_TEST(min(1, 2) == 1);
    BOOST_TEST(min(-1, -2) == -2);
    return boost::report_errors();
}
//]

