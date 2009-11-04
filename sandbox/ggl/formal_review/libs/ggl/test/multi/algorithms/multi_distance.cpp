// Generic Geometry Library
//
// Copyright Barend Gehrels, Geodan B.V. Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>


#include <ggl_test_common.hpp>

#include <ggl/algorithms/distance.hpp>
#include <ggl/extensions/gis/io/wkt/read_wkt.hpp>

#include <ggl/strategies/strategies.hpp>


#include <ggl/multi/algorithms/distance.hpp>
#include <ggl/multi/geometries/multi_point.hpp>
#include <ggl/multi/geometries/multi_linestring.hpp>
#include <ggl/multi/geometries/multi_polygon.hpp>
#include <ggl/extensions/gis/io/wkt/read_wkt_multi.hpp>

#include <ggl/geometries/geometries.hpp>
#include <ggl/geometries/adapted/c_array_cartesian.hpp>
#include <ggl/geometries/adapted/tuple_cartesian.hpp>
#include <test_common/test_point.hpp>


template <typename Geometry1, typename Geometry2>
void test_distance(const std::string& wkt1, const std::string& wkt2, double expected)
{
    Geometry1 g1;
    Geometry2 g2;
    ggl::read_wkt(wkt1, g1);
    ggl::read_wkt(wkt2, g2);
    double d = ggl::distance(g1, g2);

    BOOST_CHECK_CLOSE(d, expected, 0.0001);
}

template <typename Geometry1, typename Geometry2, typename Strategy>
void test_distance(const Strategy& strategy, const std::string& wkt1,
                   const std::string& wkt2, double expected)
{
    Geometry1 g1;
    Geometry2 g2;
    ggl::read_wkt(wkt1, g1);
    ggl::read_wkt(wkt2, g2);
    double d = ggl::distance(g1, g2, strategy);

    BOOST_CHECK_CLOSE(d, expected, 0.0001);
}


template <typename P>
void test_2d()
{
    typedef ggl::multi_point<P> mp;
    typedef ggl::multi_linestring<ggl::linestring<P> > ml;
    test_distance<P, P>("POINT(0 0)", "POINT(1 1)", sqrt(2.0));
    test_distance<P, mp>("POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);
    test_distance<mp, P>("MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);
    test_distance<mp, mp>("MULTIPOINT((1 1),(1 0),(0 2))", "MULTIPOINT((2 2),(2 3))", sqrt(2.0));
    test_distance<P, ml>("POINT(0 0)", "MULTILINESTRING((1 1,2 2),(1 0,2 0),(0 2,0 3))", 1.0);
    test_distance<ml, P>("MULTILINESTRING((1 1,2 2),(1 0,2 0),(0 2,0 3))", "POINT(0 0)", 1.0);
    test_distance<ml, mp>("MULTILINESTRING((1 1,2 2),(1 0,2 0),(0 2,0 3))", "MULTIPOINT((0 0),(1 1))", 0.0);

    // Test with a strategy
    ggl::strategy::distance::pythagoras<P, P> pyth;
    test_distance<P, P>(pyth, "POINT(0 0)", "POINT(1 1)", sqrt(2.0));
    test_distance<P, mp>(pyth, "POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);
    test_distance<mp, P>(pyth, "MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);
}


template <typename P>
void test_3d()
{
    typedef ggl::multi_point<P> mp;
    test_distance<P, P>("POINT(0 0 0)", "POINT(1 1 1)", sqrt(3.0));
    test_distance<P, mp>("POINT(0 0 0)", "MULTIPOINT((1 1 1),(1 0 0),(0 1 2))", 1.0);
    test_distance<mp, mp>("MULTIPOINT((1 1 1),(1 0 0),(0 0 2))", "MULTIPOINT((2 2 2),(2 3 4))", sqrt(3.0));
}


template <typename P1, typename P2>
void test_mixed()
{
    typedef ggl::multi_point<P1> mp1;
    typedef ggl::multi_point<P2> mp2;

    test_distance<P1, P2>("POINT(0 0)", "POINT(1 1)", sqrt(2.0));

    test_distance<P1, mp1>("POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);
    test_distance<P1, mp2>("POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);
    test_distance<P2, mp1>("POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);
    test_distance<P2, mp2>("POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);

    // Test automatic reversal
    test_distance<mp1, P1>("MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);
    test_distance<mp1, P2>("MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);
    test_distance<mp2, P1>("MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);
    test_distance<mp2, P2>("MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);

    // Test multi-multi using different point types for each
    test_distance<mp1, mp2>("MULTIPOINT((1 1),(1 0),(0 2))", "MULTIPOINT((2 2),(2 3))", sqrt(2.0));

    // Test with a strategy
    using namespace ggl::strategy::distance;

    test_distance<P1, P2>(pythagoras<P1, P2>(), "POINT(0 0)", "POINT(1 1)", sqrt(2.0));

    test_distance<P1, mp1>(pythagoras<P1, P1>(), "POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);
    test_distance<P1, mp2>(pythagoras<P1, P2>(), "POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);
    test_distance<P2, mp1>(pythagoras<P2, P1>(), "POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);
    test_distance<P2, mp2>(pythagoras<P2, P2>(), "POINT(0 0)", "MULTIPOINT((1 1),(1 0),(0 2))", 1.0);

    // Most interesting: reversal AND a strategy (note that the stategy must be reversed automatically
    test_distance<mp1, P1>(pythagoras<P1, P1>(), "MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);
    test_distance<mp1, P2>(pythagoras<P1, P2>(), "MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);
    test_distance<mp2, P1>(pythagoras<P2, P1>(), "MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);
    test_distance<mp2, P2>(pythagoras<P2, P2>(), "MULTIPOINT((1 1),(1 0),(0 2))", "POINT(0 0)", 1.0);
}



int test_main( int , char* [] )
{
    test_2d<boost::tuple<float, float> >();
    test_2d<ggl::point_xy<float> >();
    test_2d<ggl::point_xy<double> >();

    test_3d<boost::tuple<float, float, float> >();
    test_3d<ggl::point<double, 3, ggl::cs::cartesian> >();

    test_mixed<ggl::point_xy<float>, ggl::point_xy<double> >();

    return 0;
}
