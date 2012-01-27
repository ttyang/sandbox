
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestAddExcept
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_except ) {
    //[add_except
    double sum = 0.0;
    int factor = 10;

    void BOOST_LOCAL_FUNCTION(const bind factor, bind& sum,
            double num) throw() { // Throw nothing.
        sum += factor * num;
    } BOOST_LOCAL_FUNCTION_NAME(add)

    add(100);
    //]

    BOOST_CHECK( sum == 1000 );
}

