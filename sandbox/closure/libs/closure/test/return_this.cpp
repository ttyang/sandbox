
//[test_return_this_cpp
#include <boost/closure.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE ReturnThis
#include <boost/test/unit_test.hpp>

struct number {
    number(int value) : value_(value) {}

    boost::function<int (void)> inc(void) {
        int BOOST_CLOSURE(bind this_) {
            return ++this_->value_;
        } BOOST_CLOSURE_END(i)
        return i;
    }

private:
    int value_;
};

BOOST_AUTO_TEST_CASE( return_this ) {
    number n1 = 0; // Object valid in scope where closure is used.
    boost::function<int (void)> inc1 = n1.inc();
    number n2 = 0;
    boost::function<int (void)> inc2 = n2.inc();

    BOOST_CHECK( inc1() == 1 );
    BOOST_CHECK( inc1() == 2 );
    BOOST_CHECK( inc2() == 1 );
    BOOST_CHECK( inc1() == 3 );
}
//]

