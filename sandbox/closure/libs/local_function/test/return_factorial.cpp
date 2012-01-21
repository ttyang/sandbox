
#include <boost/local_function.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE TestReturnFactorial
#include <boost/test/unit_test.hpp>
#include <vector>
#include <iostream>

boost::function<int (int)> factorial(std::vector<int>& steps) {
    int BOOST_LOCAL_FUNCTION(bind& steps, int n) {
        int result;
        if(n < 2) result = 1;
        else result = n * (*this)(n - 1); // Recursive call.
        steps.push_back(result);
        return result;
    } BOOST_LOCAL_FUNCTION_NAME(fact)
    return fact;
}

BOOST_AUTO_TEST_CASE( test_return_factorial ) {
    std::vector<int> steps;
    boost::function<int (int)> fact = factorial(steps);

    int i = fact(4); BOOST_CHECK( i == 24 );
    i = steps.at(0); BOOST_CHECK( i == 1 );
    i = steps.at(1); BOOST_CHECK( i == 2 );
    i = steps.at(2); BOOST_CHECK( i == 6 );
    i = steps.at(3); BOOST_CHECK( i == 24 );
}

