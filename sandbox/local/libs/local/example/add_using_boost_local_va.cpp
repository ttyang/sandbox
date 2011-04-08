
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#include <boost/config.hpp>
#if defined(BOOST_NO_VARIADIC_MACROS) || defined(BOOST_LOCAL_CONFIG_COMPLIANT)
#include <iostream>
int main() {
    std::cerr << "Error: This program requires variadic macros" << std::endl;
    return 0;
}
#else

//[ add_using_boost_local_va_cpp
#include <boost/local/function.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    double sum = 0.0;
    int factor = 10;

    std::vector<double> v(3);
    v[0] = 1.0; v[1] = 2.0; v[2] = 3.0;

    // Unfortunately, cannot be defined at expression level.
    void BOOST_LOCAL_FUNCTION_PARAMS(double num,
            // Bind `sum` as reference and `factor` as constant reference.
            bind& sum, const bind& factor) {
        // Body uses C++ statement syntax.
        sum += factor * num;
        std::cout << "Summed: " << sum << std::endl;
    } BOOST_LOCAL_FUNCTION_NAME(add)

    std::for_each(v.begin(), v.end(), add); // Passed as template parameter.

    std::cout << sum << std::endl;
    return 0;
}
//]

#endif
