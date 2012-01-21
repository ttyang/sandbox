
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestAddClassifiers
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_add_classifiers ) {
    //[test_add_classifiers
    int BOOST_LOCAL_FUNCTION(auto int x, register int y) { // Classifers.
        return x + y;
    } BOOST_LOCAL_FUNCTION_NAME(add)
    //]

    BOOST_CHECK( add(1, 2) == 3 );
}

