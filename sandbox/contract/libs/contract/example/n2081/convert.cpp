
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

//[n2081_convert
// File: convert.cpp
#include "convert.hpp"
#include <boost/detail/lightweight_test.hpp>

int main ( void )
{
    BOOST_TEST(convert<int>('\0') == 0);
    return boost::report_errors();
}
//]

