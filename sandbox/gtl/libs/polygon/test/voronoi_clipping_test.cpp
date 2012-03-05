// Boost.Polygon library voronoi_clipping_test.cpp file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#define BOOST_TEST_MODULE voronoi_clipping_test
#include <boost/test/test_case_template.hpp>

#include "boost/polygon/voronoi_utils.hpp"
using namespace boost::polygon;

typedef voronoi_utils<double> VU;
typedef VU::brect_type rect_type;
typedef VU::point_type point_type;

#define SZ(st) static_cast<int>(st.size())

// Test segment clipping.
BOOST_AUTO_TEST_CASE(segment_clipping_test1) {
    rect_type rect(0, -1, 4, 2);
    point_type origin(-1, 3);
    point_type direction1_1(8, -8);
    point_type direction1_2(2, -2);
    point_type direction1_3(0.5, -0.5);
    point_type direction2(2, -4);
    point_type direction3(2, -1);
    point_type direction4(1, -4);
    point_type direction5(5, -1);
    std::vector<point_type> intersections;

    VU::intersect(origin, direction1_1, VU::SEGMENT, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 2);
    BOOST_CHECK_EQUAL(intersections[0].x() == 0 && intersections[0].y() == 2, true);
    BOOST_CHECK_EQUAL(intersections[1].x() == 3 && intersections[1].y() == -1, true);
    intersections.clear();
    
    VU::intersect(origin, direction1_2, VU::SEGMENT, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 1);
    BOOST_CHECK_EQUAL(intersections[0].x() == 0 && intersections[0].y() == 2, true);
    intersections.clear();

    VU::intersect(origin, direction1_3, VU::SEGMENT, rect, intersections);
    BOOST_CHECK_EQUAL(intersections.empty(), true);
    intersections.clear();

    VU::intersect(origin, direction2, VU::SEGMENT, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 2);
    BOOST_CHECK_EQUAL(intersections[0].x() == 0 && intersections[0].y() == 1, true);
    BOOST_CHECK_EQUAL(intersections[1].x() == 1 && intersections[1].y() == -1, true);
    intersections.clear();

    VU::intersect(origin, direction3, VU::SEGMENT, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 1);
    BOOST_CHECK_EQUAL(intersections[0].x() == 1 && intersections[0].y() == 2, true);
    intersections.clear();

    VU::intersect(origin, direction4, VU::SEGMENT, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 1);
    BOOST_CHECK_EQUAL(intersections[0].x() == 0 && intersections[0].y() == -1, true);
    intersections.clear();

    VU::intersect(origin, direction5, VU::SEGMENT, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 1);
    BOOST_CHECK_EQUAL(intersections[0].x() == 4 && intersections[0].y() == 2, true);
    intersections.clear();
}

BOOST_AUTO_TEST_CASE(segment_clipping_test2) {
    rect_type rect(0, -1, 4, 3);
    std::vector<point_type> intersections;
    point_type origin(2, 1);

    for (int i = -50; i <= 50; i++)
        for (int j = -50; j <= 50; j++) {
            intersections.clear();
            point_type direction(i, j);
            VU::intersect(origin, direction, VU::SEGMENT, rect, intersections);
            if (abs(i) >= 2 || abs(j) >= 2)
                BOOST_CHECK_EQUAL(SZ(intersections), 1);
            else
                BOOST_CHECK_EQUAL(SZ(intersections), 0);
        }
}

BOOST_AUTO_TEST_CASE(segment_clipping_test3) {
    rect_type rect(0, -1, 4, 3);
    std::vector<point_type> intersections;
    point_type origin(2, 1);

    for (int i = -50; i <= 50; i++)
        for (int j = -50; j <= 50; j++) {
            intersections.clear();
            double x = 1.0 * i / 26;
            double y = 1.0 * j / 26;
            point_type direction(x, y);
            VU::intersect(origin, direction, VU::SEGMENT, rect, intersections);
            BOOST_CHECK_EQUAL(SZ(intersections), 0);
        }
}

// Test ray clipping.
BOOST_AUTO_TEST_CASE(ray_clipping_test1) {
    rect_type rect(0, -1, 4, 2);
    point_type origin(-1, 3);
    point_type direction1(2, -2);
    point_type direction2(2, -4);
    point_type direction3(2, -1);
    point_type direction4(1, -4);
    point_type direction5(5, -1);
    std::vector<point_type> intersections;

    VU::intersect(origin, direction1, VU::RAY, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 2);
    BOOST_CHECK_EQUAL(intersections[0].x() == 0 && intersections[0].y() == 2, true);
    BOOST_CHECK_EQUAL(intersections[1].x() == 3 && intersections[1].y() == -1, true);
    intersections.clear();

    VU::intersect(origin, direction2, VU::RAY, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 2);
    BOOST_CHECK_EQUAL(intersections[0].x() == 0 && intersections[0].y() == 1, true);
    BOOST_CHECK_EQUAL(intersections[1].x() == 1 && intersections[1].y() == -1, true);
    intersections.clear();

    VU::intersect(origin, direction3, VU::RAY, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 2);
    BOOST_CHECK_EQUAL(intersections[0].x() == 1 && intersections[0].y() == 2, true);
    BOOST_CHECK_EQUAL(intersections[1].x() == 4 && intersections[1].y() == 0.5, true);
    intersections.clear();

    VU::intersect(origin, direction4, VU::RAY, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 1);
    BOOST_CHECK_EQUAL(intersections[0].x() == 0 && intersections[0].y() == -1, true);
    intersections.clear();

    VU::intersect(origin, direction5, VU::RAY, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 1);
    BOOST_CHECK_EQUAL(intersections[0].x() == 4 && intersections[0].y() == 2, true);
    intersections.clear();
}

BOOST_AUTO_TEST_CASE(ray_clipping_test2) {
    rect_type rect(0, -1, 4, 3);
    std::vector<point_type> intersections;
    point_type origin(2, 1);

    for (int i = -50; i <= 50; i++)
        for (int j = -50; j <= 50; j++) {
            if (!i && !j) continue;
            intersections.clear();
            double x = 1.0 * i / 26;
            double y = 1.0 * j / 26;
            point_type direction(x, y);
            VU::intersect(origin, direction, VU::RAY, rect, intersections);
            BOOST_CHECK_EQUAL(SZ(intersections), 1);
        }
}

// Test line clipping.
BOOST_AUTO_TEST_CASE(line_clipping_test1) {
    rect_type rect(0, -1, 4, 2);
    point_type origin(-1, 3);
    point_type direction1(-1, 1);
    point_type direction2(-1, 2);
    point_type direction3(-2, 1);
    point_type direction4(-1, 4);
    point_type direction5(-5, 1);
    std::vector<point_type> intersections;
    
    VU::intersect(origin, direction1, VU::LINE, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 2);
    BOOST_CHECK_EQUAL(intersections[0].x() == 3 && intersections[0].y() == -1, true);
    BOOST_CHECK_EQUAL(intersections[1].x() == 0 && intersections[1].y() == 2, true);
    intersections.clear();

    VU::intersect(origin, direction2, VU::LINE, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 2);
    BOOST_CHECK_EQUAL(intersections[0].x() == 1 && intersections[0].y() == -1, true);
    BOOST_CHECK_EQUAL(intersections[1].x() == 0 && intersections[1].y() == 1, true);
    intersections.clear();

    VU::intersect(origin, direction3, VU::LINE, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 2);
    BOOST_CHECK_EQUAL(intersections[0].x() == 4 && intersections[0].y() == 0.5, true);
    BOOST_CHECK_EQUAL(intersections[1].x() == 1 && intersections[1].y() == 2, true);
    intersections.clear();

    VU::intersect(origin, direction4, VU::LINE, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 1);
    BOOST_CHECK_EQUAL(intersections[0].x() == 0 && intersections[0].y() == -1, true);
    intersections.clear();

    VU::intersect(origin, direction5, VU::LINE, rect, intersections);
    BOOST_CHECK_EQUAL(SZ(intersections), 1);
    BOOST_CHECK_EQUAL(intersections[0].x() == 4 && intersections[0].y() == 2, true);
    intersections.clear();
}

BOOST_AUTO_TEST_CASE(line_clipping_test2) {
    rect_type rect(0, -1, 4, 3);
    std::vector<point_type> intersections;
    point_type origin(2, 1);

    for (int i = -50; i <= 50; i++)
        for (int j = -50; j <= 50; j++) {
            if (!i && !j) continue;
            intersections.clear();
            double x = 1.0 * i / 26;
            double y = 1.0 * j / 26;
            point_type direction(x, y);
            VU::intersect(origin, direction, VU::LINE, rect, intersections);
            BOOST_CHECK_EQUAL(SZ(intersections), 2);
        }
}
