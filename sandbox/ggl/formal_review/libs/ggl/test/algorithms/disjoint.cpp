// Generic Geometry Library test file
//
// Copyright Barend Gehrels, 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>


#include <ggl_test_common.hpp>

#include <ggl/algorithms/disjoint.hpp>
#include <ggl/geometries/geometries.hpp>
#include <ggl/extensions/gis/io/wkt/read_wkt.hpp>
#include <ggl/strategies/strategies.hpp>

#include <test_common/test_point.hpp>



template <typename G1, typename G2>
void test_disjoint(std::string const& wkt1, std::string const& wkt2, bool expected)
{
    G1 g1;
    ggl::read_wkt(wkt1, g1);

    G2 g2;
    ggl::read_wkt(wkt2, g2);

    bool detected = ggl::disjoint(g1, g2);
    BOOST_CHECK_MESSAGE(detected == expected,
        "disjoint: " << wkt1
        << " and " << wkt2
        << " -> Expected: " << expected
        << " detected: " << detected);
}



template <typename P>
void test_all()
{
    typedef ggl::box<P> box;

    test_disjoint<P, P>("point(1 1)", "point(1 1)", false);
    test_disjoint<P, P>("point(1 1)", "point(1.001 1)", true);

    // left-right
    test_disjoint<box, box>("box(1 1, 2 2)", "box(3 1, 4 2)", true);
    test_disjoint<box, box>("box(1 1, 2 2)", "box(2 1, 3 2)", false);
    test_disjoint<box, box>("box(1 1, 2 2)", "box(2 2, 3 3)", false);
    test_disjoint<box, box>("box(1 1, 2 2)", "box(2.001 2, 3 3)", true);

    // up-down
    test_disjoint<box, box>("box(1 1, 2 2)", "box(1 3, 2 4)", true);
    test_disjoint<box, box>("box(1 1, 2 2)", "box(1 2, 2 3)", false);
    // right-left
    test_disjoint<box, box>("box(1 1, 2 2)", "box(0 1, 1 2)", false);
    test_disjoint<box, box>("box(1 1, 2 2)", "box(0 1, 1 2)", false);

    // point-box
    test_disjoint<P, box>("point(1 1)", "box(0 0, 2 2)", false);
    test_disjoint<P, box>("point(2 2)", "box(0 0, 2 2)", false);
    test_disjoint<P, box>("point(2.0001 2)", "box(1 1, 2 2)", true);
    test_disjoint<P, box>("point(0.9999 2)", "box(1 1, 2 2)", true);

    // box-point (to test reverse compiling)
    test_disjoint<box, P>("box(1 1, 2 2)", "point(2 2)", false);

    // Test triangles for polygons/rings, boxes
    // Note that intersections are tested elsewhere, they don't need
    // thorough test at this place
    typedef ggl::polygon<P> polygon;
    typedef ggl::linear_ring<P> ring;

    // Four times same test with other types
    test_disjoint<polygon, polygon>("POLYGON((0 0,0 2,2 2,0 0))", "POLYGON((1 0,3 2,3 0,1 0))", true);
    test_disjoint<ring, polygon>("POLYGON((0 0,0 2,2 2,0 0))", "POLYGON((1 0,3 2,3 0,1 0))", true);
    test_disjoint<ring, ring>("POLYGON((0 0,0 2,2 2,0 0))", "POLYGON((1 0,3 2,3 0,1 0))", true);
    test_disjoint<polygon, ring>("POLYGON((0 0,0 2,2 2,0 0))", "POLYGON((1 0,3 2,3 0,1 0))", true);

    // Testing touch
    test_disjoint<polygon, polygon>("POLYGON((0 0,0 2,2 2,0 0))", "POLYGON((2 2,3 2,3 0,2 2))", false);

    // Testing overlap (and test compiling with box)
    test_disjoint<polygon, polygon>("POLYGON((0 0,0 2,2 2,2 0,0 0))", "POLYGON((1 1,3 2,3 0,1 1))", false);
    test_disjoint<box, polygon>("POLYGON((0 0,0 2,2 2,2 0,0 0))", "POLYGON((1 1,3 2,3 0,1 1))", false);
    test_disjoint<box, ring>("POLYGON((0 0,0 2,2 2,2 0,0 0))", "POLYGON((1 1,3 2,3 0,1 1))", false);
    test_disjoint<polygon, box>("POLYGON((1 1,3 2,3 0,1 1))", "POLYGON((0 0,0 2,2 2,2 0,0 0))", false);
    test_disjoint<ring, box>("POLYGON((1 1,3 2,3 0,1 1))", "POLYGON((0 0,0 2,2 2,2 0,0 0))", false);

    // Test if within(a,b) returns false for disjoint
    test_disjoint<ring, ring>("POLYGON((0 0,0 3,3 3,3 0,0 0))", "POLYGON((1 1,1 2,2 2,2 1,1 1))", false);
    test_disjoint<ring, ring>("POLYGON((1 1,1 2,2 2,2 1,1 1))", "POLYGON((0 0,0 3,3 3,3 0,0 0))", false);
}

int test_main(int, char* [])
{
    test_all<ggl::point_xy<float> >();
    test_all<ggl::point_xy<double> >();

    return 0;
}
