
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestFactorial
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <vector>

//[test_factorial
struct calculator {
    std::vector<int> results;

    void factorials(const std::vector<int>& nums) {
        int BOOST_LOCAL_FUNCTION(bind this_, int num,
                bool recursion, default false) {
            int result = 0;
            
            if (n < 2 ) result = 1;
            else result = n * factorial(n - 1, true); // Recursive call.

            if (!recursion) this_->results.push_back(result);
            return result;
        } BOOST_LOCAL_FUNCTION_NAME(recursive factorial) // Recursive.
    
        std::for_each(nums.begin(), nums.end(), factorial);
    }
};
//]

BOOST_AUTO_TEST_CASE( test_factorial ) {
    std::vector<int> v(3);
    v[0] = 1; v[1] = 4; v[2] = 7;

    calculator calc;
    calc.factorials(v);
    BOOST_CHECK( calc.results[0] == 1 );
    BOOST_CHECK( calc.results[1] == 24 );
    BOOST_CHECK( calc.results[2] == 64 );
}

