
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestNesting
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_nesting ) {
    //[test_nesting
    int x = 0;

    void BOOST_LOCAL_FUNCTION(bind& x) {
        void BOOST_LOCAL_FUNCTION_PARAMS(bind& x) { // Nested.
            x++;
        } BOOST_LOCAL_FUNCTION_NAME(g)

        x--;
        g(); // Nested local function call.
    } BOOST_LOCAL_FUNCTION_NAME(f)
    
    f();
    //]
    BOOST_CHECK( x == 0 );
}

