
#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestOperatorErr
#include <boost/test/unit_test.hpp>

//[operator_err
struct point {
    int x;
    int y;
};

BOOST_AUTO_TEST_CASE( test_operator_err ) {
    bool BOOST_LOCAL_FUNCTION(const point& p, const point& q) {
        return p.x == q.x && p.y == q.y;
    } BOOST_LOCAL_FUNCTION_NAME(operator==) // Error: Cannot use `operator...`.

    point a; a.x = 1; a.y = 2;
    point b = a;
    BOOST_CHECK( a == b );
}
//]

