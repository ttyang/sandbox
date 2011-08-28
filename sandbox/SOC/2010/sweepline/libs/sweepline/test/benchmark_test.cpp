// Boost sweepline library benchmark_test.cpp file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <cstdio>
#include <iostream>

#define BOOST_TEST_MODULE benchmark_test
#include <boost/mpl/list.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/timer.hpp>

#include "boost/sweepline/voronoi_diagram.hpp"

typedef boost::mpl::list<int> test_types;

#ifdef WIN32
#pragma warning( disable : 4996 )
#endif

BOOST_AUTO_TEST_CASE_TEMPLATE(benchmark_test1, T, test_types) {
    typedef T coordinate_type;
    boost::mt19937 gen(static_cast<unsigned int>(time(NULL)));
    boost::timer timer;
    typename boost::sweepline::detail::voronoi_traits<coordinate_type>::output_type test_output;

    FILE *bench_file = fopen("benchmark.txt", "a");
    fprintf(bench_file, "Voronoi Segment Sweepline Benchmark Test (time in seconds):\n");
    fprintf(bench_file, "| Number of points | Number of tests | Time per one test |\n"); 

#ifdef NDEBUG
    int max_points = 1000000;
#else
    int max_points = 100;
#endif

    typename boost::sweepline::detail::voronoi_traits<coordinate_type>::input_point_set_type points;
    typedef typename boost::sweepline::detail::voronoi_traits<coordinate_type>::input_point_type
        input_point_type;
    for (int num_points = 10; num_points <= max_points; num_points *= 10) {
        points.resize(num_points);
        timer.restart();
        int num_tests = max_points / num_points;
        for (int cur = 0; cur < num_tests; cur++) {
            for (int cur_point = 0; cur_point < num_points; cur_point++) {
                points[cur_point] = point_mutable_traits<input_point_type>::construct(
                    static_cast<coordinate_type>(gen()),
                    static_cast<coordinate_type>(gen()));
            }
            boost::sweepline::build_voronoi<coordinate_type>(points, test_output);
        }
        double elapsed_time = timer.elapsed();
        double time_per_test = elapsed_time / num_tests;

        fprintf(bench_file, "| %16d ", num_points);
        fprintf(bench_file, "| %15d ", num_tests);
        fprintf(bench_file, "| %17.6f |\n", time_per_test);
    }
    fclose(bench_file);
}
