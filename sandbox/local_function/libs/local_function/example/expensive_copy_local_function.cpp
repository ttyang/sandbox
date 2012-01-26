
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/local/function.hpp>
#include <iostream>
#include <cassert>

//[expensive_copy_local_function
struct n {
    int i;
    n(int _i): i(_i) {}
    n(n const& x): i(x.i) { // Some time consuming copy.
        for (unsigned i = 0; i < 10000; ++i) std::cout << '.';
    }
};

int main(void) {
    n x(-1);

    void BOOST_LOCAL_FUNCTION(const bind& x) {  // OK: No copy
        assert( x.i == -1 );                    // and constant.
    } BOOST_LOCAL_FUNCTION_NAME(f)
    f();

    return 0;
}
//]

