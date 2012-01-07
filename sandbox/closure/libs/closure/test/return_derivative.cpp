
//[test_return_derivative_cpp
#include <boost/closure.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE ReturnDerivative
#include <boost/test/unit_test.hpp>

boost::function<int (int)> derivative(boost::function<int (int)>& f, int dx) {
    int BOOST_CLOSURE(bind& f, const bind dx, int x) {
        return (f(x + dx) - f(x)) / dx;
    } BOOST_CLOSURE_END(deriv)
    return deriv;
}

BOOST_AUTO_TEST_CASE( return_derivative ) {
    int BOOST_CLOSURE(int x) {
        return x + 4;
    } BOOST_CLOSURE_END(add2)
    boost::function<int (int)> a2 = add2; // Reference valid where closure used.

    boost::function<int (int)> d2 = derivative(a2, 2);
    BOOST_CHECK( d2(6) == 1 );
}
//]

