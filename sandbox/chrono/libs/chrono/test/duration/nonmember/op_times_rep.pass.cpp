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

// duration

// template <class Rep1, class Period, class Rep2>
//   duration<typename common_type<Rep1, Rep2>::type, Period>
//   operator*(const duration<Rep1, Period>& d, const Rep2& s);

// template <class Rep1, class Period, class Rep2>
//   duration<typename common_type<Rep1, Rep2>::type, Period>
//   operator*(const Rep1& s, const duration<Rep2, Period>& d);

#include <boost/chrono.hpp>
#include <cassert>

int main()
{
    boost::chrono::nanoseconds ns(3);
    ns = ns * 5;
    assert(ns.count() == 15);
    ns = 6 * ns;
    assert(ns.count() == 90);
}
