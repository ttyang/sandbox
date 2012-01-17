
#include <separate.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

template<typename T, typename A = int>
struct buf {
    int x;

    explicit buf(size_t count = 0) {
        std::cout << "created with size " << count << std::endl;
    }
    void push_back(T const& value) {
        std::cout << "pushed " << value << std::endl;
    }
};

int main() {
    SEPARATE_DECL(buf<int>, i)(3);
    (SEPARATED(i)::push_back)(10);
    SEPARATED(i)::x = 1;

    typedef std::vector<int> vect_t;
    separate_ptr<vect_t> vect = new vect_t(3);
    (vect->*&vect_t::push_back)(123);

    return EXIT_SUCCESS;
}

