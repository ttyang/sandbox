
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/local_function.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE TestReturnAssign
#include <boost/test/unit_test.hpp>

//[test_return_assign
void call1(boost::function<int (int)> f) { BOOST_CHECK( f(1) == 5 ); }

void call0(boost::function<int (void)> f) { BOOST_CHECK( f() == 5 ); }

boost::function<int (int, int)> linear(int slope) {
    boost::function< int (int, int) > l2;

    int BOOST_LOCAL_FUNCTION(bind slope, int x, default 1, int y, default 2) {
        return x + slope * y;
    } BOOST_LOCAL_FUNCTION_NAME(lin)

    boost::function<int (int, int)> f = lin; // Assign to local variable.
    BOOST_CHECK( f(1, 2) == 5 );

    call1(lin); // Pass to other functions.
    call0(lin);

    return lin; // Return.
}

void call(void) {
    boost::function<int (int, int)> f = linear(2);
    BOOST_CHECK( f(1, 2) == 5 );
}
//]

BOOST_AUTO_TEST_CASE( test_return_assign ) {
    call();
}

