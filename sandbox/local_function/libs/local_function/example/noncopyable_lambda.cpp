
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/noncopyable.hpp>
#include <cassert>

//[noncopyable_lambda
struct n: boost::noncopyable {
    int i;
    n(int _i): i(_i) {}
};

int main(void) {
    n x(-1);

    auto f = [x](void) {        // Error: x is non-copyable, but if
        assert( x.i == -1 );    // bind `&x` then `x` is not constant.
    };
    f();

    return 0;
}
//]

