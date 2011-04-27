
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

//[ add_function_inline_cpp
#include <boost/local/function.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    double sum = 0.0;
    int factor = 10;

    void BOOST_LOCAL_FUNCTION_PARAMS( (double num) (const bind factor)
            (bind& sum) ) {
        sum += factor * num;
    } BOOST_LOCAL_FUNCTION_NAME(inline add) // inlined local function

    std::vector<double> v(1000000);
    std::fill(v.begin(), v.end(), 1.0);

    // On some compiler (e.g., GCC) inlined local functions are more likely to
    // be optimized for faster run-times. However, inlined local functions
    // cannot be passed at template parameters (i.e., `std::for_each` cannot be
    // used here).
    // On C++03 compilers (e.g., MSVC or GCC 4.5) linining has no effect
    // because the local function can always be optimized even if not
    // explicitly specified inline and inlined local functions can be always be
    // passed as template paramters.
    for (size_t i = 0; i < v.size(); ++i) { // Can't use for_each (portably).
        add(v[i]);
    }

    std::cout << sum << std::endl;
    return 0;
}
//]
