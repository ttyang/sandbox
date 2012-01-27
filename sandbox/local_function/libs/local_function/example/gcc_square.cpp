
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestGccSquare
#include <boost/test/unit_test.hpp>

double add_square(double a, double b) {
    double BOOST_LOCAL_FUNCTION(double z) {
        return z * z;
    } BOOST_LOCAL_FUNCTION_NAME(square)

    return square(a) + square(b);
}

BOOST_AUTO_TEST_CASE( test_gcc_square ) {
    BOOST_CHECK( add_square(2.0, 4.0) == 20.0 );
}

