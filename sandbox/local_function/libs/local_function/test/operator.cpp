
#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestOperator
#include <boost/test/unit_test.hpp>

//[operator
struct point {
    int x;
    int y;
};

BOOST_AUTO_TEST_CASE( test_operator ) {
    bool BOOST_LOCAL_FUNCTION(const point& p, const point& q) {
        return p.x == q.x && p.y == q.y;
    } BOOST_LOCAL_FUNCTION_NAME(equal) // OK: not using `operator...`.

    point a; a.x = 1; a.y = 2;
    point b = a;
    BOOST_CHECK( equal(a, b) );
}
//]

