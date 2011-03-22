
//[scope_guards_except_va_cpp
#include <boost/local/exit.hpp>
#include <iostream>
#include <stdexcept>

void f() {
    bool error = false; // No error to start with.

    BOOST_LOCAL_EXIT(void) { // Same as D's `scope(exit)`.
        std::cout << "exit" << std::endl;
    } BOOST_LOCAL_EXIT_END

    BOOST_LOCAL_EXIT(const bind& error) { // Same as D's `scope(success)`.
        if (!error) std::cout << "success" << std::endl;
    } BOOST_LOCAL_EXIT_END
    
    BOOST_LOCAL_EXIT(const bind& error) { // Same as D's `scope(failure)`.
        if (error) std::cout << "failure" << std::endl;
    } BOOST_LOCAL_EXIT_END
    
    error = true; throw std::runtime_error("some error"); // Must set error.
}

int main() {
    // Program cannot terminate with uncaught exception (otherwise local exit
    // code is not guaranteed to be executed).
    try {
        f();
        return 0;
    } catch(...) {
        return -1;
    }
}
//]
