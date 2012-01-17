
//[test_offset_cpp
#include <iostream>
#include <boost/closure.hpp>
#include <boost/function.hpp>
#include <cstdlib>

/** @todo test returning closures with defaults, this binding, and recursion */

boost::function<int (int)> offset(int delta) {
    int BOOST_CLOSURE(bind delta, int x) { // Must not bind by reference.
        std::cout << delta << std::endl;
        return x + delta;
    } BOOST_CLOSURE_END(add)
    return add; // Return the function closure.
}

int main(void) {
    boost::function<int (int)> offset10 = offset(10);
    return (offset10(2) == 12) ? EXIT_SUCCESS : EXIT_FAILURE;
}
//]

