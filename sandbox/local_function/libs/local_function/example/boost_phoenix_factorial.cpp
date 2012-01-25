
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/function.hpp>
#define BOOST_TEST_MODULE ExampleBoostPhoenixFactorial
#include <boost/test/unit_test.hpp>

//[example_boost_phoenix_factorial
struct factorial_impl { // Phoenix function from global functor.
    template<typename Sig>
    struct result;

    template<typename This, typename Arg>
    struct result<This (Arg)> : result<This (Arg const&)> {};

    template<typename This, typename Arg>
    struct result<This (Arg&)> { typedef Arg type; };

    template<typename Arg> // Polymorphic.
    Arg operator()(Arg n) const {
        return (n <= 0) ? 1 : n * (*this)(n - 1);
    }
};

BOOST_AUTO_TEST_CASE( example_boost_phoenix_factorial ) {
    using boost::phoenix::arg_names::arg1;
    
    boost::phoenix::function<factorial_impl> factorial;
    
    int i = 4;
    BOOST_CHECK( factorial(i)() == 24 );        // Call.
    BOOST_CHECK( factorial(arg1)(i) == 24 );    // Lazy call.
}
//]

