// Boost.Polygon library voronoi_benchmark.cpp file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <iomanip>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/timer.hpp>

typedef boost::int32_t int32;

// Include for Boost.Polygon Voronoi library.
#include <boost/polygon/voronoi.hpp>
typedef boost::polygon::default_voronoi_builder VB_BOOST;
typedef boost::polygon::voronoi_diagram<double> VD_BOOST;

// Includes for CGAL library.
# include <CGAL/Quotient.h>
# include <CGAL/MP_Float.h>
typedef CGAL::Quotient<CGAL::MP_Float> ENT;
#include <CGAL/Simple_cartesian.h>
typedef CGAL::Simple_cartesian<double> CK;
typedef CGAL::Simple_cartesian<ENT> EK;
#include <CGAL/Segment_Delaunay_graph_filtered_traits_2.h>
#include <CGAL/Segment_Delaunay_graph_2.h>
typedef CGAL::Segment_Delaunay_graph_filtered_traits_2<
    CK, CGAL::Field_with_sqrt_tag, EK, CGAL::Field_tag> Gt;
typedef CGAL::Segment_Delaunay_graph_2<Gt> SDT_CGAL;
typedef SDT_CGAL::Point_2 Point_CGAL;

const int RANDOM_SEED = 27;
const int NUM_TESTS = 6;
const int NUM_POINTS[] = {10, 100, 1000, 10000, 100000, 1000000};
const int NUM_RUNS[] = {100000, 10000, 1000, 100, 10, 1};
std::ofstream bf("benchmark_points.txt", std::ios_base::out | std::ios_base::app);
boost::timer timer;

void format_line(int num_points, int num_tests, double time_per_test) {
  bf << "| " << std::setw(16) << num_points << " ";
  bf << "| " << std::setw(15) << num_tests << " ";
  bf << "| " << std::setw(17) << time_per_test << " ";
  bf << "|" << std::endl;
}

void run_boost_test() {
  boost::mt19937 gen(RANDOM_SEED);
  bf << "Boost.Polygon Voronoi of Points:\n";
  for (int i = 0; i < NUM_TESTS; ++i) {
    timer.restart();
    for (int j = 0; j < NUM_RUNS[i]; ++j) {
      VB_BOOST vb;
      VD_BOOST vd;
      for (int k = 0; k < NUM_POINTS[i]; ++k)
        vb.insert(static_cast<int32>(gen()), static_cast<int32>(gen()));
      vb.construct(&vd);
    }
    double time_per_test = timer.elapsed() / NUM_RUNS[i];
    format_line(NUM_POINTS[i], NUM_RUNS[i], time_per_test);
  }
  bf << "\n";
}

void run_cgal_test() {
  boost::mt19937 gen(RANDOM_SEED);
  bf << "CGAL Triangulation of Points:\n";
  for (int i = 0; i < NUM_TESTS; ++i) {
    timer.restart();
    for (int j = 0; j < NUM_RUNS[i]; ++j) {
      SDT_CGAL dt;
      for (int k = 0; k < NUM_POINTS[i]; ++k) {
        dt.insert(Point_CGAL(static_cast<int32>(gen()),
                             static_cast<int32>(gen())));
      }
    }
    double time_per_test = timer.elapsed() / NUM_RUNS[i];
    format_line(NUM_POINTS[i], NUM_RUNS[i], time_per_test);
  }
  bf << "\n";
}

int main() {
  bf << std::setiosflags(std::ios::right | std::ios::fixed)
     << std::setprecision(6);
  run_boost_test();
  run_cgal_test();
  bf.close();
  return 0;
}
