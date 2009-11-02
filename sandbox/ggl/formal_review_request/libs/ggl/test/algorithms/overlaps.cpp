// Generic Geometry Library
//
// Copyright Barend Gehrels, Geodan B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <algorithms/test_overlaps.hpp>


#include <ggl/geometries/box.hpp>
#include <ggl/geometries/cartesian2d.hpp>
#include <ggl/geometries/linear_ring.hpp>
#include <ggl/geometries/linestring.hpp>
#include <ggl/geometries/point.hpp>
#include <ggl/geometries/point_xy.hpp>
#include <ggl/geometries/polygon.hpp>


template <typename P>
void test_2d()
{
    test_geometry<ggl::box<P>, ggl::box<P> >("BOX(1 1, 3 3)", "BOX(0 0,2 2)", true);

    // touch -> false
    test_geometry<ggl::box<P>, ggl::box<P> >("BOX(1 1, 3 3)", "BOX(3 3,5 5)", false);

    // disjoint -> false
    test_geometry<ggl::box<P>, ggl::box<P> >("BOX(1 1, 3 3)", "BOX(4 4,6 6)", false);

    // within -> false
    test_geometry<ggl::box<P>, ggl::box<P> >("BOX(1 1, 5 5)", "BOX(2 2,3 3)", false);

    // within+touch -> false
    test_geometry<ggl::box<P>, ggl::box<P> >("BOX(1 1, 5 5)", "BOX(2 2,5 5)", false);
}

template <typename P>
void test_3d()
{
    test_geometry<ggl::box<P>, ggl::box<P> >("BOX(1 1 1, 3 3 3)", "BOX(0 0 0,2 2 2)", true);
    test_geometry<ggl::box<P>, ggl::box<P> >("BOX(1 1 1, 3 3 3)", "BOX(3 3 3,5 5 5)", false);
    test_geometry<ggl::box<P>, ggl::box<P> >("BOX(1 1 1, 3 3 3)", "BOX(4 4 4,6 6 6)", false);
}



int test_main( int , char* [] )
{
    test_2d<ggl::point_xy<int> >();
    test_2d<ggl::point_xy<double> >();

#if defined(HAVE_CLN)
    test_2d<ggl::point_xy<boost::numeric_adaptor::cln_value_type> >();
#endif
#if defined(HAVE_GMP)
    test_2d<ggl::point_xy<boost::numeric_adaptor::gmp_value_type> >();
#endif

   //test_3d<ggl::point<double, 3, ggl::cs::cartesian> >();

    return 0;
}
