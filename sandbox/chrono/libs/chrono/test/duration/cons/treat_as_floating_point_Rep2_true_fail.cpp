//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

// treat_as_floating_point<Rep2>::value must be false

#include <boost/chrono.hpp>

void test()
{
    boost::chrono::duration<int> d(1.);
}