
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/spirit/include/phoenix.hpp>
#define BOOST_TEST_MODULE AddPhoenix
#include <boost/test/unit_test.hpp>
#include <algorithm>
    
BOOST_AUTO_TEST_CASE( add_phoenix )
//[add_phoenix
{
    int sum = 0, factor = 10;
    int nums[] = {1, 2, 3};

    // Passed to template, `factor` by constant, and defined in expression.
    using namespace boost::phoenix;
    std::for_each(nums, nums + 3, let(_f = cref(factor))[
        // Unfortunately, body cannot use C++ statement syntax.
        ref(sum) += _f * _1 // Access `sum` by reference.
    ]);

    BOOST_CHECK( sum == 60 );
}
//]

