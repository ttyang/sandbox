
#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestTenVoid
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE( test_ten_void ) {
    //[test_ten_void
    int BOOST_LOCAL_FUNCTION(void) { // No parameter.
        return 10;
    } BOOST_LOCAL_FUNCTION_NAME(ten)

    BOOST_CHECK( ten() == 10 );
    //]
}

