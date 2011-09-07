// Boost sweepline library benchmark_test.cpp file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <iomanip>
#include <iostream>
#include <fstream>

#define BOOST_TEST_MODULE benchmark_test
#include <boost/mpl/list.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/timer.hpp>

#include "boost/sweepline/voronoi_diagram.hpp"

typedef boost::mpl::list<int> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(benchmark_test1, T, test_types) {
    typedef T coordinate_type;
    typedef point_data<coordinate_type> point_type;
    boost::mt19937 gen(static_cast<unsigned int>(time(NULL)));
    boost::timer timer;
    typename boost::sweepline::voronoi_output<double> test_output;

    std::ofstream bench_file("benchmark.txt", std::ios_base::out | std::ios_base::app);
    bench_file << "Voronoi Segment Sweepline Benchmark Test (time in seconds):" << std::endl;
    bench_file << "| Number of points | Number of tests | Time per one test |" << std::endl;
    bench_file << std::setiosflags(std::ios::right | std::ios::fixed) << std::setprecision(6);

#ifdef NDEBUG
    int max_points = 1000000;
#else
    int max_points = 100;
#endif

    std::vector<point_type> points;
    for (int num_points = 10; num_points <= max_points; num_points *= 10) {
        points.resize(num_points);
        timer.restart();
        int num_tests = max_points / num_points;
        for (int cur = 0; cur < num_tests; cur++) {
            for (int cur_point = 0; cur_point < num_points; cur_point++) {
                points[cur_point] = point_mutable_traits<point_type>::construct(
                    static_cast<coordinate_type>(gen()),
                    static_cast<coordinate_type>(gen()));
            }
            boost::sweepline::construct_voronoi_points<coordinate_type>(points, test_output);
        }
        double elapsed_time = timer.elapsed();
        double time_per_test = elapsed_time / num_tests;

        bench_file << "| " << std::setw(16) << num_points << " ";
        bench_file << "| " << std::setw(15) << num_tests << " ";
        bench_file << "| " << std::setw(17) << time_per_test << " ";
        bench_file << "| " << std::endl;
    }
    bench_file.close();
}
