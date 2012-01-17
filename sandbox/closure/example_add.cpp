
//[example_add_cpp
#include <boost/closure.hpp>
#include <algorithm>
#include <cstdlib>

int main(void) {
    int sum = 0, factor = 10;
    
    void BOOST_CLOSURE(int num, const bind factor, bind& sum) {
        sum += factor * num;
    } BOOST_CLOSURE_END(add)
    
    add(1); // Call the function closure.

    int nums[] = {2, 3};
    std::for_each(nums, nums + 2, add); // Pass the closure to an algorithm.

    return (sum == 60) ? EXIT_SUCCESS : EXIT_FAILURE;
}
//]

