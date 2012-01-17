
#include <algorithm>
#include <iostream>

int main() {
    struct s {
        void operator()(int x) {
            std::cout << x << std::endl;
        }
    } l;

    int nums[] = {1, 2, 3};
    std::for_each(nums, nums + 3, l);

    return 0;
}

