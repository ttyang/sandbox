
//[example_add_lambda_cpp
#include <boost/closure.hpp>
#include <algorithm>
#include <cstdlib>

int main(void) {
    int sum = 0, factor = 10;
    
    auto add = [factor, &sum](int num) {
        sum += factor * num;
    };
    
    add(1); // Call the lambda function.

    int nums[] = {2, 3};
    std::for_each(nums, nums + 2, add); // Pass the lambda to an algorithm.

    return (sum == 60) ? EXIT_SUCCESS : EXIT_FAILURE;
}
//]

