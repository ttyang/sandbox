
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

//[ add_using_boost_phoenix_cpp
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    using boost::phoenix::let;
    using boost::phoenix::local_names::_f;
    using boost::phoenix::cref;
    using boost::phoenix::ref;
    using boost::phoenix::arg_names::_1;
    using boost::phoenix::val;

    double sum = 0.0;
    int factor = 10;

    std::vector<double> v(3);
    v[0] = 1.0; v[1] = 2.0; v[2] = 3.0;

    // Passed as template parameter and also defined at expression level.
    // Bind `factor` by constant.
    std::for_each(v.begin(), v.end(), let(_f = cref(factor))[
        // Unfortunately, body cannot use C++ statement syntax.
        ref(sum) += _f * _1, // Access `sum` by reference.
        std::cout << val("Summed: ") << ref(sum) << "\n"
    ]);

    std::cout << sum << std::endl;
    return 0;
}
//]

