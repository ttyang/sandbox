//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  conversions from floating point to integral durations disallowed

#include <boost/chrono.hpp>

void test()
{
    boost::chrono::duration<double> d;
    boost::chrono::duration<int> i = d;
}
