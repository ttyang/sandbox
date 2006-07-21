//  (C) Copyright Xiaogang Zhang 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/math/special_functions/bessel_i1.hpp>
#include <boost/math/tools/testutils.hpp>
#include <boost/array.hpp>

template <typename T>
void test_bessel_i1(T, const char* type_name)
{
   // TODO
}

template <typename T>
void test_spots(T, const char* type_name)
{
    // function values calculated on http://functions.wolfram.com/
    #define SC_(x) static_cast<T>(BOOST_JOIN(x, L))
    static const boost::array<boost::array<T, 2>, 10> data = {
        SC_(0), SC_(0),
        SC_(1), SC_(0.5651591039924850272076960276098633073289),
        SC_(-2), SC_(-1.590636854637329063382254424999666247954),
        SC_(4), SC_(9.759465153704449909475192567312680900056),
        SC_(-8), SC_(-3.998731367825600982190830861458227548896e+02),
        SC_(1e-05), SC_(5.000000000062500000000260416666667209201e-06),
        SC_(1e-10), SC_(5.000000000000000000006250000000000000000e-11),
        SC_(-1e+01), SC_(-2.670988303701254654341031966772152549146e+03),
        SC_(1e+02), SC_(1.068369390338162481206145763224295265446e+42),
        SC_(2e+02), SC_(2.034581549332062703427427977139069503897e+85),
    };
    #undef SC_

    boost::math::tools::test_univariate
        (data, type_name, "boost::math::bessel_i1", boost::math::bessel_i1);
}

int test_main(int, char* [])
{
    test_spots(0.0F, "float");
    test_spots(0.0, "double");
    test_spots(0.0L, "long double");

    test_bessel_i1(0.0F, "float");
    test_bessel_i1(0.0, "double");
    test_bessel_i1(0.0L, "long double");

    return 0;
}
