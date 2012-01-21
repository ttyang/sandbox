
#include "gcc_lambda.hpp"
#define BOOST_TEST_MODULE ExampleGccLambda
#include <boost/test/unit_test.hpp>
#include <algorithm>

BOOST_AUTO_TEST_CASE( example_gcc_lambda ) {
    //[example_gcc_lambda
    int val = 2;
    int nums[] = {1, 2, 3};
    int* end = nums + 3;

    int* iter = std::find_if(nums, end,
        GCC_LAMBDA(const bind val, int num, return bool) {
            return num == val;
        } GCC_LAMBDA_END
    );
    //]

    BOOST_CHECK( iter != end );
    BOOST_CHECK( *iter == val );
}

