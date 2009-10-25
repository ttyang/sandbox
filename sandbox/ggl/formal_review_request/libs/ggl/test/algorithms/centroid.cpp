// Generic Geometry Library test file
//
// Copyright Barend Gehrels, 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <ggl_test_common.hpp>


#include <ggl/algorithms/centroid.hpp>

#include <ggl/algorithms/distance.hpp>

#include <ggl/extensions/gis/io/wkt/read_wkt.hpp>

#include <ggl/geometries/geometries.hpp>
#include <ggl/geometries/adapted/c_array_cartesian.hpp>
#include <ggl/geometries/adapted/tuple_cartesian.hpp>

#include <algorithms/test_centroid.hpp>


template <typename P>
void test_2d()
{
    test_centroid<ggl::linear_ring<P> >(
        "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2"
        ",3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3))",
        4.06923363095238, 1.65055803571429);
    test_centroid<ggl::polygon<P> >(
        "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2"
        ",3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3))",
        4.06923363095238, 1.65055803571429);

    // with holes
    test_centroid<ggl::polygon<P> >(
        "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2"
        ",3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3)"
        ",(4 2,4.2 1.4,4.8 1.9,4.4 2.2,4 2))"
        ,
        4.0466264962959677, 1.6348996057331333);


    // ccw
    test_centroid<ggl::linear_ring<P, std::vector, false> >(
        "POLYGON((2 1.3,2.9 0.7,4.9 0.8,5.4 1.2,5.3 2.6,4.1 3,3.4 2"
            ",3.7 1.6,3.4 1.2,2.8 1.8,2.4 1.7,2 1.3))",
        4.06923363095238, 1.65055803571429);


    test_centroid<ggl::box<P> >("POLYGON((1 2,3 4))", 2, 3);
    test_centroid<P>("POINT(3 3)", 3, 3);
}

template <typename P>
void test_3d()
{
    test_centroid<ggl::box<P> >("POLYGON((1 2 3,5 6 7))", 3, 4, 5);
    test_centroid<P>("POINT(1 2 3)", 1, 2, 3);
}



int test_main(int, char* [])
{
    test_2d<ggl::point_xy<double> >();
    test_2d<boost::tuple<float, float> >();
    test_2d<ggl::point_xy<float> >();

    test_3d<boost::tuple<double, double, double> >();


#if defined(HAVE_CLN)
    test_2d<ggl::point_xy<boost::numeric_adaptor::cln_value_type> >();
#endif
#if defined(HAVE_GMP)
    test_2d<ggl::point_xy<boost::numeric_adaptor::gmp_value_type> >();
#endif

    return 0;
}
