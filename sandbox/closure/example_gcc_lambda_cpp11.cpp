
//[example_add_cpp
#include <algorithm>
#include <cstdlib>

int main(void) {
    int val = 2;
    int nums[] = {1, 2, 3};
    int* end = nums + 3;

    int* iter = std::find_if(nums, end, 
        [val](int num) -> bool {
            return num == val;
        }
    );

    return (iter != end) ? EXIT_SUCCESS : EXIT_FAILURE;
}
//]

