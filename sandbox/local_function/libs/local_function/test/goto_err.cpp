
#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestGotoErr
#include <boost/test/unit_test.hpp>

//[test_goto_err
int error(int x, int y) {
    bool BOOST_LOCAL_FUNCTION(int x) {
        if(x <= 0) goto failure;    // Error: Cannot jump to enclosing scope.
        else goto success;          // OK: Can jump within local function.

    success:
        return 0;
    } BOOST_LOCAL_FUNCTION_NAME(validate)

    return validate(x + y);
faliure:
    return -1;
}
//]

BOOST_AUTO_TEST_CASE( test_goto_err ) {
    error(1, 2);
}

