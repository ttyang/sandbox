
//[test_add_seq_cpp
#include <boost/closure.hpp>
#define BOOST_TEST_MODULE TestAddSeq
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_add_seq) {
    int sum = 0, factor = 10;
    
    void BOOST_CLOSURE( (const bind factor) (bind& sum) (int num) ) {
        sum += factor * num;
    } BOOST_CLOSURE_END(add)
    
    add(1); // Call the function closure.

    int nums[] = {2, 3};
    std::for_each(nums, nums + 2, add); // Pass the closure to an algorithm.

    BOOST_CHECK(sum == 60);
}
//]

