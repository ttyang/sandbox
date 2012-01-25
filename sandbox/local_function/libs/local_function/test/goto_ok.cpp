
#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestGotoOk
#include <boost/test/unit_test.hpp>

//[test_goto_ok
int error(int x, int y) {
    bool BOOST_LOCAL_FUNCTION(int x) {
        if(x > 0) goto success; // OK: Can jump within local function.
        return -1;
    success:
        return 0;
    } BOOST_LOCAL_FUNCTION_NAME(validate)

    return validate(x + y);
}
//]

BOOST_AUTO_TEST_CASE( test_goto_ok ) {
    error(1, 2);
}

