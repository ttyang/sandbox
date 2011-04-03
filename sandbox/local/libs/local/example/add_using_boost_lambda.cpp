
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

//[ add_using_boost_lambda_cpp
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    using boost::lambda::_1;
    using boost::lambda::var;

    double sum = 0.0;
    int factor = 10;

    std::vector<double> v(3);
    v[0] = 1.0; v[1] = 2.0; v[2] = 3.0;

    // Passed as template parameter and also defined at expression level.
    std::for_each(v.begin(), v.end(), (
        // Unfortunately, cannot make `factor` constant.
        // Unfortunately, body cannot use C++ statement syntax.
        sum += factor * _1,
        var(std::cout) << "Summed: " << var(sum) << "\n"
    ));

    std::cout << sum << std::endl;
    return 0;
}
//]

