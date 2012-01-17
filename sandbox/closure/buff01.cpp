
#include <vector>
#include <cstdlib>
#include <iostream>

template<typename T, typename A = int>
struct buf {
    explicit buf(size_t count = 0) {
        std::cout << "created with size " << count << std::endl;
    }
    void push_back(T const& value) {
        std::cout << "pushed " << value << std::endl;
    }
};

template<class C>
struct separate_ptr {
    typedef C class_type;
    
    separate_ptr(C* ptr) : ptr_(ptr) {}

private:
    C* ptr_;
};

int main() {
    typedef buf<int> b_t;
    b_t* b = new b_t(2);
    b->push_back(1);
    
//    void (std::vector<int>::*f)(int const&) = &std::vector<int>::push_back;
//    (v->*f)(2);
    
    (b->*&b_t::push_back)(3);

    typedef std::vector<int> v_t;
    v_t* v = new v_t(2);


    return EXIT_SUCCESS;
}

