//  Copyright (c) 2006 Xiaogang Zhang
//
//  This code may be used under either of the following two licences:
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE. OF SUCH DAMAGE.
//
//  Or:
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/math/special_functions/bessel_jv.hpp>
#include <boost/math/tools/testutils.hpp>
#include <boost/array.hpp>

template <typename T>
void test_bessel_jv(T, const char* type_name)
{
   // TODO
}

template <typename T>
void test_spots(T, const char* type_name)
{
    // function values calculated on http://functions.wolfram.com/
    #define SC_(x) static_cast<T>(BOOST_JOIN(x, L))
    static const boost::array<boost::array<T, 3>, 10> data = {
        SC_(-2.4), SC_(0), std::numeric_limits<T>::infinity(),
        SC_(2.4), SC_(1e-02), SC_(1.007239545211832536148340943169134971589e-06),
        SC_(5.5), SC_(3.1416), SC_(2.819324174208752668629781718572610128855e-02),
        SC_(-5.5), SC_(3.1416), SC_(-2.558205897167535567702182324451308320967),
        SC_(-5.5), SC_(1e+04), SC_(2.449843111985605522111159013846599118397e-03),
        SC_(-10.0003), SC_(1e-02), SC_(1.117298136559883282451589188593774445102e+25),
        SC_(-10.0003), SC_(15), SC_(-9.022420634837421001178451581412959947838e-02),
        SC_(1.414e+02), SC_(1e+02), SC_(8.029654028891234369752357191475059941099e-13),
        SC_(1.414e+02), SC_(2e+04), SC_(-1.627949087398007958983153593184616633717e-03),
        SC_(-1.414e+02), SC_(1e+02), SC_(-3.771723772650031678385927069594942797589e+09),
    };
    #undef SC_

    boost::math::tools::test_bivariate
        (data, type_name, "boost::math::bessel_jv", boost::math::bessel_jv);
}

int test_main(int, char* [])
{
    test_spots(0.0F, "float");
    test_spots(0.0, "double");
    test_spots(0.0L, "long double");

    test_bessel_jv(0.0F, "float");
    test_bessel_jv(0.0, "double");
    test_bessel_jv(0.0L, "long double");

    return 0;
}
