
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/local/function.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    double sum = 0.0;
    int factor = 10;

    std::vector<double> v(1000000);
    std::fill(v.begin(), v.end(), 10);

    void BOOST_LOCAL_FUNCTION_PARAMS( (double num)
            (const bind factor) (bind& sum) ) {
        sum += factor * num;
    } BOOST_LOCAL_FUNCTION_NAME(add)
    
    for(int i = 0; i < 10000; ++i) {
        std::for_each(v.begin(), v.end(), add);
    }

    std::cout << sum << std::endl;
    return 0;
}
