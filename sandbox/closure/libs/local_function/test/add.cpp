
#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestAdd
#include <boost/test/unit_test.hpp>
#include <algorithm>

BOOST_AUTO_TEST_CASE( test_add )
//[test_add
{ // Some local scope.
    int sum = 0, factor = 10; // Variables in scope to bind.
    
    void BOOST_LOCAL_FUNCTION(const bind factor, bind& sum, int num) {
        sum += factor * num;
    } BOOST_LOCAL_FUNCTION_NAME(add)
    
    add(1); // Call the local function (with one parameter `num`).
    int nums[] = {2, 3};
    std::for_each(nums, nums + 2, add); // Pass it to an algorithm.

    BOOST_CHECK( sum == 60 ); // Assert final summation value.
}
//]

