
//[test_return_inc_cpp
#include <boost/closure.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE ReturnInc
#include <boost/test/unit_test.hpp>

boost::function<int (void)> inc(int& value) {
    int BOOST_CLOSURE(bind& value) {
        return ++value;
    } BOOST_CLOSURE_END(i)
    return i;
}

BOOST_AUTO_TEST_CASE( return_inc ) {
    int value1 = 0; // Reference valid in scope where closure is used.
    boost::function<int (void)> inc1 = inc(value1);
    int value2 = 0;
    boost::function<int (void)> inc2 = inc(value2);

    BOOST_CHECK( inc1() == 1 );
    BOOST_CHECK( inc1() == 2 );
    BOOST_CHECK( inc2() == 1 );
    BOOST_CHECK( inc1() == 3 );
}
//]

