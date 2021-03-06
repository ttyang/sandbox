//  io_ex2.cpp  ----------------------------------------------------------//

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
#include <cassert>

int main()
{
    using namespace std;
    using namespace boost::chrono;

#ifdef BOOST_CHRONO_IO_INPUT
    istringstream in("5000 milliseconds 4000 ms 3001 ms");
    seconds d(0);
    in >> d;
    assert(in.good());
    assert(d == seconds(5));
    in >> d;
    assert(in.good());
    assert(d == seconds(4));
    in >> d;
    assert(in.fail());
    assert(d == seconds(4));
#endif
    return 0;
}

