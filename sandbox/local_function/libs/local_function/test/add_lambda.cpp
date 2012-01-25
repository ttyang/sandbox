
#include <boost/config.hpp>

#ifndef BOOST_NO_LAMBDAS

#define BOOST_TEST_MODULE TestAddLambda
#include <boost/test/unit_test.hpp>
#include <algorithm>

BOOST_AUTO_TEST_CASE( test_add_lambda )
//[test_add_lambda
{                                           // Some local scope.
    int sum = 0, factor = 10;               // Variables in scope to bind.
    
    auto add = [factor, &sum](int num) {    // C++11 only.
        sum += factor * num;
    };
    
    add(1);                                 // Call the lambda.
    int nums[] = {2, 3};
    std::for_each(nums, nums + 2, add);     // Pass it to an algorithm.
    
    BOOST_CHECK( sum == 60 );               // Assert final summation value.
}
//]

#else // LAMBDAS

int main(void) { return 0; } // Trivial test.

#endif // LAMBDAS

