// Boost.Geometry (aka GGL, Generic Geometry Library) test file
//
// Copyright Barend Gehrels 2009, Geodan, Amsterdam, the Netherlands
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>

#define BOOST_GEOMETRY_REPORT_OVERLAY_ERROR
#define BOOST_GEOMETRY_NO_BOOST_TEST

#include <boost/timer.hpp>
#include <boost/lexical_cast.hpp>

#include <test_overlay_p_q.hpp>

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/multi/multi.hpp>


template <typename Polygon>
inline void make_pie(Polygon& polygon,
    int count, int offset, int offset_y, double factor1, int total_segment_count = 36)
{
    typedef typename boost::geometry::point_type<Polygon>::type p;
    typedef typename boost::geometry::select_most_precise
        <
            typename boost::geometry::coordinate_type<Polygon>::type,
            long double
        >::type coordinate_type;

    // Create pie
    coordinate_type cx = 2500.0;
    coordinate_type cy = 2500.0 + offset_y;

    boost::geometry::exterior_ring(polygon).push_back(boost::geometry::make<p>(int(cx), int(cy)));

    coordinate_type dx = 5000.0;
    coordinate_type dy = 5000.0;

    coordinate_type half = 0.5;
    coordinate_type two = 2.0;

    coordinate_type a = coordinate_type(factor1) * half * dx;
    coordinate_type b = coordinate_type(factor1) * half * dy;

    coordinate_type pi = boost::math::constants::pi<long double>();
    coordinate_type delta = pi * two / total_segment_count;
    coordinate_type angle = coordinate_type(offset) * delta;
    for (int i = 0; i < count; i++, angle += delta)
    {
        coordinate_type s = sin(angle);
        coordinate_type c = cos(angle);
        coordinate_type x = cx + a * s;
        coordinate_type y = cy + b * c;
        boost::geometry::exterior_ring(polygon).push_back(boost::geometry::make<p>(int(x), int(y)));
    }
    boost::geometry::exterior_ring(polygon).push_back(boost::geometry::make<p>(int(cx), int(cy)));
}


template <typename T>
void test_pie(int total_segment_count, T factor_p, T factor_q, bool svg)
{
    boost::timer t;
    typedef boost::geometry::point_xy<T> point_type;
    typedef boost::geometry::polygon<point_type> polygon;
    typedef boost::geometry::multi_polygon<polygon> multi_polygon;

    int good_count = 0;
    int bad_count = 0;

    for (int a = 2; a < total_segment_count; a++)
    {
        polygon p;
        make_pie(p, a, 0, 0, factor_p, total_segment_count);
        for (int b = 2; b < total_segment_count; b++)
        {
            for (int offset = 1; offset < total_segment_count; offset++)
            {
                //for (int y = 0; y <= 2500; y += 500)
                int y = 0;
                {
                    polygon q;
                    make_pie(q, b, offset, y, factor_q, total_segment_count);

                    // multi-polygon:
                    //for (int c = o
                    int left = total_segment_count - b - 2;
                    //std::cout << a << " " << b << " " << left << std::endl;
                    for (int c = 2; c < left; c++)
                    {
                        polygon q2;
                        make_pie(q2, c, offset + b + 1, y, factor_q, total_segment_count);

                        std::ostringstream out;
                        out << "pie_" << a << "_" << b << "_" << offset << "_" << y
                            << "_" << c
                            ;

                        bool good = false;
                        bool one_with_self_tangency = false;

                        // Represent as either multi-polygon, or as single-self-touching-polygon
                        if (one_with_self_tangency)
                        {
                            polygon q1 = q;
                            for (unsigned int i = 1; i < q2.outer().size(); i++)
                            {
                                q1.outer().push_back(q2.outer()[i]);
                            }
                            good = test_overlay_p_q<polygon, T>(out.str(), p, q1, svg, 0.01);
                        }
                        else 
                        {
                            multi_polygon mq;
                            mq.push_back(q);
                            mq.push_back(q2);
                            good = test_overlay_p_q<polygon, T>(out.str(), p, mq, svg, 0.01);
                        }

                        if (good)
                        {
                            good_count++;
                        }
                        else
                        {
                            bad_count++;
                        }
                    }
                }
            }
        }
    }
    std::cout
        << "Time: " << t.elapsed()  << std::endl
        << "Good: " << good_count << std::endl
        << "Bad: " << bad_count << std::endl;
}


template <typename T>
void test_all(bool svg)
{
    test_pie<T>(24, 0.55, 0.45, svg);
}

int main(int argc, char** argv)
{
    try
    {
        bool svg = argc > 1 && std::string(argv[1]) == std::string("svg");

        //test_all<float>();
        test_all<double>(svg);
        //test_all<long double>();

#if defined(HAVE_CLN)
        //test_all<boost::numeric_adaptor::cln_value_type>();
#endif
#if defined(HAVE_GMP)
        //test_all<boost::numeric_adaptor::gmp_value_type>();
#endif
    }
    catch(std::exception const& e)
    {
        std::cout << "Exception " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "Other exception" << std::endl;
    }
    return 0;
}
