
#include <boost/local_function.hpp>
#include <boost/function.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/function.hpp>
#define BOOST_TEST_MODULE ExampleBoostPhoenixFactorialLocal
#include <boost/test/unit_test.hpp>

//[example_boost_phoenix_local_factorial
BOOST_AUTO_TEST_CASE( example_boost_phoenix_factorial_local ) {
    using boost::phoenix::arg_names::arg1;
    
    int BOOST_LOCAL_FUNCTION(int n) { // Monomorphic.
        return (n <= 0) ? 1 : n * factorial_impl(n - 1);
    } BOOST_LOCAL_FUNCTION_NAME(recursive factorial_impl)

    boost::phoenix::function< boost::function<int (int)> >
            factorial(factorial_impl); // Phoenix function from local function.
    
    int i = 4;
    BOOST_CHECK( factorial(i)() == 24 );        // Call.
    BOOST_CHECK( factorial(arg1)(i) == 24 );    // Lazy call.
}
//]

