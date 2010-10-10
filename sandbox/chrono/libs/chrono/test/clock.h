//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef CLOCK_H
#define CLOCK_H

#include <boost/chrono.hpp>

class Clock
{
    typedef boost::chrono::nanoseconds               duration;
    typedef duration::rep                            rep;
    typedef duration::period                         period;
    typedef boost::chrono::time_point<Clock, duration> time_point;
    static const bool is_monotonic =                false;

    static time_point now();
};

#endif  // CLOCK_H
