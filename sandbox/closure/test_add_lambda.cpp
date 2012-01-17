
//[test_add_lambda_cpp
#include <boost/closure.hpp>
#define BOOST_TEST_MODULE TestAddLambda
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_add_lambda) {
    int sum = 0, factor = 10;
    
    auto add = [factor, &sum](int num) {
        sum += factor * num;
    };
    
    add(1); // Call the lambda.

    int nums[] = {2, 3};
    std::for_each(nums, nums + 2, add); // Pass the lambda to an algorithm.

    BOOST_CHECK(sum == 60);
}
//]

