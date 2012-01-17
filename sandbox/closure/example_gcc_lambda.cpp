
//[example_add_cpp
#include <gcc_lambda.hpp>
#include <algorithm>
#include <cstdlib>

int main(void) {
    int val = 2;
    int nums[] = {1, 2, 3};
    int* end = nums + 3;

    int* iter = std::find_if(nums, end,
        GCC_LAMBDA(const bind val, int num, return bool) {
            return num == val;
        } GCC_LAMDA_END
    );

    return (iter != end) ? EXIT_SUCCESS : EXIT_FAILURE;
}
//]

