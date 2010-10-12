// Boost.Geometry (aka GGL, Generic Geometry Library) test file
//
// Copyright Barend Gehrels 2010, Geodan, Amsterdam, the Netherlands
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>


#include <algorithms/test_intersection.hpp>
#include <algorithms/test_overlay.hpp>
#include <multi/algorithms/overlay/multi_overlay_cases.hpp>

#include <boost/geometry/multi/algorithms/correct.hpp>
#include <boost/geometry/multi/algorithms/intersection.hpp>

#include <boost/geometry/multi/geometries/multi_point.hpp>
#include <boost/geometry/multi/geometries/multi_linestring.hpp>
#include <boost/geometry/multi/geometries/multi_polygon.hpp>

#include <boost/geometry/extensions/gis/io/wkt/read_wkt_multi.hpp>

template <typename Ring, typename Polygon, typename MultiPolygon>
void test_areal()
{
    test_one<Polygon, MultiPolygon, MultiPolygon>("simplex_multi",
        case_multi_simplex[0], case_multi_simplex[1],
        2, 12, 6.42);

    test_one<Polygon, MultiPolygon, MultiPolygon>("case_multi_no_ip",
        case_multi_no_ip[0], case_multi_no_ip[1],
        2, 8, 8.5);
    test_one<Polygon, MultiPolygon, MultiPolygon>("case_multi_2",
        case_multi_2[0], case_multi_2[1],
        3, 12, 5.9);

    test_one<Polygon, MultiPolygon, Polygon>("simplex_multi_mp_p",
        case_multi_simplex[0], case_single_simplex,
        2, 12, 6.42);

    test_one<Polygon, Ring, MultiPolygon>("simplex_multi_r_mp",
        case_single_simplex, case_multi_simplex[0],
        2, 12, 6.42);
    test_one<Ring, MultiPolygon, Polygon>("simplex_multi_mp_r",
        case_multi_simplex[0], case_single_simplex,
        2, 12, 6.42);
}


template <typename P>
void test_all()
{
    namespace bg = boost::geometry;


    typedef bg::linear_ring<P> ring;
    typedef bg::polygon<P> polygon;
    typedef bg::multi_polygon<polygon> multi_polygon;
    test_areal<ring, polygon, multi_polygon>();

    typedef bg::linear_ring<P, std::vector, false> ring_ccw;
    typedef bg::polygon<P, std::vector, std::vector, false> polygon_ccw;
    typedef bg::multi_polygon<polygon_ccw> multi_polygon_ccw;
    test_areal<ring_ccw, polygon_ccw, multi_polygon_ccw>();

    typedef bg::linestring<P> linestring;
    typedef bg::multi_linestring<linestring> multi_linestring;


    // linear
    test_one<P, multi_linestring, multi_linestring>("case_multi_linear_1",
        "MULTILINESTRING((0 0,1 1))", "MULTILINESTRING((0 1,1 0))",
        1, 1, 0);
    test_one<P, multi_linestring, multi_linestring>("case_multi_linear_2",
        "MULTILINESTRING((0 0,1 1),(0.5 0,1.5 1))", "MULTILINESTRING((0 1,1 0),(0.5 1,1.5 0))",
        4, 4, 0);

    test_one<P, linestring, multi_linestring>("case_multi_linear_3",
        "LINESTRING(0 0,1 1)", "MULTILINESTRING((0 1,1 0),(0.5 1,1.5 0))",
        2, 2, 0);
    test_one<P, multi_linestring, linestring>("case_multi_linear_4",
        "MULTILINESTRING((0 1,1 0),(0.5 1,1.5 0))", "LINESTRING(0 0,1 1)", 
        2, 2, 0);

}


int test_main(int, char* [])
{
    test_all<boost::geometry::point_xy<double> >();

    return 0;
}
