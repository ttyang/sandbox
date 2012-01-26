
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#define BOOST_TEST_MODULE AddGlobalFunctor
#include <boost/test/unit_test.hpp>
#include <algorithm>

//[add_global_functor
// Unfortunately, cannot be defined locally (so not real alternative).
struct global_add { // Unfortunately, boilerplate code to program the class.
    global_add(int& _sum, int _factor): sum(_sum), factor(_factor) {}

    inline void operator()(int num) { // Body uses C++ statement syntax.
        sum += factor * num;
    }
private: // Unfortunately, cannot bind so repeat variable types.
    int& sum; // Access `sum` by reference.
    const int& factor; // Make `factor` constant.
};

BOOST_AUTO_TEST_CASE( add_global_functor ) {
    int sum = 0, factor = 10;

    global_add add(sum, factor);

    add(1);
    int nums[] = {2, 3};
    std::for_each(nums, nums + 2, add); // Passed as template parameter.

    BOOST_CHECK( sum == 60 );
}
//]

