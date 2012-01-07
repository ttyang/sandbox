
//[test_return_setget_cpp
#include <boost/closure.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE ReturnSetGet
#include <boost/test/unit_test.hpp>
#include <string>

boost::function<void (std::string const&)> set;
boost::function<std::string const& (void)> get;

void action(void) {
    // State `message` hidden behind access functions from here.
    BOOST_CHECK( get() == "abc" );
    set("xyz");
    BOOST_CHECK( get() == "xyz" );
}

BOOST_AUTO_TEST_CASE( return_setget ) {
    std::string message = "abc"; // Reference valid where closure used.
    
    void BOOST_CLOSURE(bind& message, std::string const& text) {
        message = text;
    } BOOST_CLOSURE_END(s)
    set = s;

    std::string const& BOOST_CLOSURE(const bind& message) {
        return message;
    } BOOST_CLOSURE_END(g)
    get = g;
    
    action();
}
//]

