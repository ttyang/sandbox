//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

// Adapted from llvm/libcxx/test/utilities/chrono
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <chrono>

// time_point

// template <class Clock, class Duration1, class Rep2, class Period2>
//   time_point<Clock, typename common_type<Duration1, duration<Rep2, Period2>>::type>
//   operator+(const time_point<Clock, Duration1>& lhs, const duration<Rep2, Period2>& rhs);

// template <class Rep1, class Period1, class Clock, class Duration2>
//   time_point<Clock, typename common_type<duration<Rep1, Period1>, Duration2>::type>
//   operator+(const duration<Rep1, Period1>& lhs, const time_point<Clock, Duration2>& rhs);

#include <boost/chrono.hpp>
#include <cassert>

int main()
{
    typedef boost::chrono::system_clock Clock;
    typedef boost::chrono::milliseconds Duration1;
    typedef boost::chrono::microseconds Duration2;
    boost::chrono::time_point<Clock, Duration1> t1(Duration1(3));
    boost::chrono::time_point<Clock, Duration2> t2 = t1 + Duration2(5);
    assert(t2.time_since_epoch() == Duration2(3005));
    t2 = Duration2(6) + t1;
    assert(t2.time_since_epoch() == Duration2(3006));
}
