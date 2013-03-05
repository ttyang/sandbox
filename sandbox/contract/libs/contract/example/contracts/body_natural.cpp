
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/detail/lightweight_test.hpp>
#include "body_natural.hpp"

int main ( void )
{
    natural<int> n, m(123);
    BOOST_TEST(n.equal(natural<int>()));
    BOOST_TEST(less(n, m));
    BOOST_TEST(greater(m, n));
    return boost::report_errors();
}

