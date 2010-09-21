//  io_ex1.cpp  ----------------------------------------------------------//

//  Copyright 2010 Howard Hinnant
//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

/*
This code was adapted by Vicente J. Botet Escriba from Hinnant's html documentation.
Many thanks to Howard for making his code available under the Boost license.

*/

#include <boost/chrono/chrono_io.hpp>
#include <sstream>
#include <iostream>
#include <cassert>

int main() 
{
    using namespace std;
    using namespace boost::chrono;

    high_resolution_clock::time_point t0 = high_resolution_clock::now();
    stringstream io;
    io << t0;
    high_resolution_clock::time_point t1;
    io >> t1;
    assert(!io.fail());
    cout << io.str() << '\n';
    cout << t0 << '\n';
    cout << t1 << '\n';
    high_resolution_clock::time_point t = high_resolution_clock::now();
    cout << t << '\n';
    
    cout << "That took " << t - t0 << '\n';
    cout << "That took " << t - t1 << '\n';
    
    return 0;
}

//~ 50908679121461 nanoseconds since boot
//~ That took 649630 nanoseconds

//~ 2793 nanoseconds since boot
//~ That took 5410464 nanoseconds
//~ That took 5454045 nanoseconds

//~ 1285042579381375000 nanoseconds since Jan 1, 1970
//~ That took 15000000 nanoseconds
