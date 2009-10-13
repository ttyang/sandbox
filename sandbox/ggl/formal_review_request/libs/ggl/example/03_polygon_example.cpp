// Generic Geometry Library
//
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Polygon Example

#include <algorithm> // for reverse, unique
#include <iostream>
#include <string>

#include <ggl/ggl.hpp>
#include <ggl/geometries/cartesian2d.hpp>
#include <ggl/geometries/adapted/c_array_cartesian.hpp>
#include <ggl/geometries/adapted/std_as_linestring.hpp>

std::string boolstr(bool v)
{
    return v ? "true" : "false";
}

int main(void)
{
    using namespace ggl;

    // Define a polygon and fill the outer ring.
    // In most cases you will read it from a file or database
    polygon_2d poly;
    {
        const double coor[][2] = {
            {2.0, 1.3}, {2.4, 1.7}, {2.8, 1.8}, {3.4, 1.2}, {3.7, 1.6},
            {3.4, 2.0}, {4.1, 3.0}, {5.3, 2.6}, {5.4, 1.2}, {4.9, 0.8}, {2.9, 0.7},
            {2.0, 1.3} // closing point is opening point
            };
        assign(poly, coor);
    }

    // Polygons should be closed, and directed clockwise. If you're not sure if that is the case,
    // call the correct algorithm
    correct(poly);

    // Polygons can be streamed as text
    // (or more precisely: as DSV (delimiter separated values))
    std::cout << ggl::dsv(poly) << std::endl;

    // As with lines, bounding box of polygons can be calculated
    box_2d b;
    envelope(poly, b);
    std::cout << ggl::dsv(b) << std::endl;

    // The area of the polygon can be calulated
    std::cout << "area: " << area(poly) << std::endl;

    // And the centroid, which is the center of gravity
    point_2d cent;
    centroid(poly, cent);
    std::cout << "centroid: " << ggl::dsv(cent) << std::endl;

    // Actually in most cases you don't want the centroid, which is only defined for polygons.
    // You want a nice labelpoint instead. Call labelpoint in those cases, which is defined
    // for all geometries
    /* not yet in preview, syntax might change
    std::cout << "labelpoints: ";
    label_info<0>(poly, , std::ostream_iterator<point_2d>(std::cout, " "));
    std::cout << std::endl;
    */

    // The number of points have to called per ring separately
    std::cout << "number of points in outer ring: " << poly.outer().size() << std::endl;

    // Polygons can have one or more inner rings, also called holes, donuts, islands, interior rings.
    // Let's add one
    {
        poly.inners().resize(1);
        linear_ring<point_2d>& inner = poly.inners().back();

        const double coor[][2] = { {4.0, 2.0}, {4.2, 1.4}, {4.8, 1.9}, {4.4, 2.2}, {4.0, 2.0} };
        assign(inner, coor);
    }

    correct(poly);

    std::cout << "with inner ring:" << ggl::dsv(poly) << std::endl;
    // The area of the polygon is changed of course
    std::cout << "new area of polygon: " << area(poly) << std::endl;
    centroid(poly, cent);
    std::cout << "new centroid: " << ggl::dsv(cent) << std::endl;

    // You can test whether points are within a polygon
    std::cout << "point in polygon:"
        << " p1: "  << boolstr(within(make<point_2d>(3.0, 2.0), poly))
        << " p2: "  << boolstr(within(make<point_2d>(3.7, 2.0), poly))
        << " p3: "  << boolstr(within(make<point_2d>(4.4, 2.0), poly))
        << std::endl;

    // You can call for_each or for_each_segment on polygons to, this will visit all points / segments
    // in outer ring and inner rings
    //for_each(poly, f);

    // As with linestrings and points, you can derive from polygon to add, for example,
    // fill color and stroke color. Or SRID (spatial reference ID). Or Z-value. Or a property map.
    // We don't show this here.

    // Clip the polygon using a bounding box
    box_2d cb(make<point_2d>(1.5, 1.5), make<point_2d>(4.5, 2.5));
    typedef std::vector<polygon_2d > polygon_list;
    polygon_list v;

    intersection<polygon_2d>(cb, poly, std::back_inserter(v));
    std::cout << "Clipped output polygons" << std::endl;
    for (polygon_list::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        std::cout << ggl::dsv(*it) << std::endl;
    }

    polygon_2d hull;
    convex_hull(poly, std::back_inserter(hull.outer()));
    std::cout << "Convex hull:" << ggl::dsv(hull) << std::endl;

    // If you really want:
    //   You don't have to use a vector, you can define a polygon with a deque
    //   You can specify the container for the points and for the inner rings independantly

    typedef polygon<point_2d, std::vector, std::deque> polygon_type;
    polygon_type poly2;
    ring_type<polygon_type>::type& ring = exterior_ring(poly2);
    append(ring, make<point_2d>(2.8, 1.9));
    append(ring, make<point_2d>(2.9, 2.4));
    append(ring, make<point_2d>(3.3, 2.2));
    append(ring, make<point_2d>(3.2, 1.8));
    append(ring, make<point_2d>(2.8, 1.9));
    std::cout << ggl::dsv(poly2) << std::endl;

    return 0;
}
