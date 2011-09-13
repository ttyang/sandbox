// Boost sweepline library sweepline_test.cpp file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <ctime>

#define BOOST_TEST_MODULE sweepline_test
#include <boost/mpl/list.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/test/test_case_template.hpp>

#include "boost/sweepline/voronoi.hpp"
using namespace boost::sweepline;
using namespace boost::sweepline::detail;
#include "output_verification.hpp"

typedef boost::mpl::list<int> test_types;

#define CHECK_EQUAL_POINTS(p1, p2) \
        BOOST_CHECK_EQUAL(p1.x() == static_cast<T>(p2.x()), true); \
        BOOST_CHECK_EQUAL(p1.y() == static_cast<T>(p2.y()), true)

#define CHECK_BRECT(brect, xmin, ymin, xmax, ymax) \
        BOOST_CHECK_EQUAL(brect.x_min() == static_cast<coordinate_type>(xmin), true); \
        BOOST_CHECK_EQUAL(brect.y_min() == static_cast<coordinate_type>(ymin), true); \
        BOOST_CHECK_EQUAL(brect.x_max() == static_cast<coordinate_type>(xmax), true); \
        BOOST_CHECK_EQUAL(brect.y_max() == static_cast<coordinate_type>(ymax), true)

#define CHECK_OUTPUT_SIZE(output, cells, vertices, edges) \
        BOOST_CHECK_EQUAL(output.cell_records().size() == static_cast<unsigned int>(cells), true); \
        BOOST_CHECK_EQUAL(output.num_cell_records() == cells, true); \
        BOOST_CHECK_EQUAL(output.vertex_records().size() == static_cast<unsigned int>(vertices), true); \
        BOOST_CHECK_EQUAL(output.num_vertex_records() == vertices, true); \
        BOOST_CHECK_EQUAL(output.edge_records().size() == static_cast<unsigned int>(edges << 1), true); \
        BOOST_CHECK_EQUAL(output.num_edge_records() == edges, true)

#define VERIFY_OUTPUT(output) \
        BOOST_CHECK_EQUAL(verify_output(output, HALF_EDGE_ORIENTATION), true); \
        BOOST_CHECK_EQUAL(verify_output(output, CELL_CONVEXITY), true); \
        BOOST_CHECK_EQUAL(verify_output(output, INCIDENT_EDGES_CCW_ORDER), true); \
        BOOST_CHECK_EQUAL(verify_output(output, NO_HALF_EDGE_INTERSECTIONS), true)

// Sites: (0, 0).
BOOST_AUTO_TEST_CASE_TEMPLATE(single_site_test, T, test_types) {
    typedef double coordinate_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_cell_const_iterator_type
        voronoi_cell_const_iterator_type;

    std::vector< point_data<T> > points;
    points.push_back(point_data<T>(0, 0));
    voronoi_diagram<coordinate_type> test_output;
    construct_voronoi_points<T>(points, test_output);
    VERIFY_OUTPUT(test_output);

    CHECK_BRECT(test_output.bounding_rectangle(), 0, 0, 0, 0);
    CHECK_OUTPUT_SIZE(test_output, 1, 0, 0);

    voronoi_cell_const_iterator_type it = test_output.cell_records().begin();
    BOOST_CHECK_EQUAL(it->num_incident_edges(), 0);
    BOOST_CHECK_EQUAL(it->incident_edge() == NULL, true);
}

// Sites: (0, 0), (0, 1).
BOOST_AUTO_TEST_CASE_TEMPLATE(collinear_sites_test1, T, test_types) {
    typedef double coordinate_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_edge_type voronoi_edge_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_cell_const_iterator_type
        voronoi_cell_const_iterator_type;

    std::vector< point_data<T> > points;
    points.push_back(point_data<T>(0, 0));
    points.push_back(point_data<T>(0, 1));
    voronoi_diagram<coordinate_type> test_output;
    construct_voronoi_points<T>(points, test_output);
    VERIFY_OUTPUT(test_output);

    CHECK_BRECT(test_output.bounding_rectangle(), 0, 0, 0, 1);
    CHECK_OUTPUT_SIZE(test_output, 2, 0, 1);

    voronoi_cell_const_iterator_type cell_it = test_output.cell_records().begin();
    BOOST_CHECK_EQUAL(cell_it->num_incident_edges(), 1);
    cell_it++;
    BOOST_CHECK_EQUAL(cell_it->num_incident_edges(), 1);

    const voronoi_edge_type *edge1_1 = cell_it->incident_edge();
    const voronoi_edge_type *edge1_2 = edge1_1->twin();

    BOOST_CHECK_EQUAL(edge1_1->twin() == edge1_2, true);
    BOOST_CHECK_EQUAL(edge1_2->twin() == edge1_1, true);

    BOOST_CHECK_EQUAL(edge1_1->next() == edge1_1, true);
    BOOST_CHECK_EQUAL(edge1_1->prev() == edge1_1, true);
    BOOST_CHECK_EQUAL(edge1_1->rot_next() == NULL, true);
    BOOST_CHECK_EQUAL(edge1_1->rot_prev() == NULL, true);

    BOOST_CHECK_EQUAL(edge1_2->next() == edge1_2, true);
    BOOST_CHECK_EQUAL(edge1_2->prev() == edge1_2, true);
    BOOST_CHECK_EQUAL(edge1_2->rot_next() == NULL, true);
    BOOST_CHECK_EQUAL(edge1_2->rot_prev() == NULL, true);
}

// Sites: (0, 0), (1, 1), (2, 2).
BOOST_AUTO_TEST_CASE_TEMPLATE(collinear_sites_test2, T, test_types) {
    typedef double coordinate_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_edge_type voronoi_edge_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_cell_const_iterator_type
        voronoi_cell_const_iterator_type;

    std::vector< point_data<T> > points;
    points.push_back(point_data<T>(0, 0));
    points.push_back(point_data<T>(1, 1));
    points.push_back(point_data<T>(2, 2));
    voronoi_diagram<coordinate_type> test_output;
    construct_voronoi_points<T>(points, test_output);
    VERIFY_OUTPUT(test_output);

    CHECK_BRECT(test_output.bounding_rectangle(), 0, 0, 2, 2);
    CHECK_OUTPUT_SIZE(test_output, 3, 0, 2);

    voronoi_cell_const_iterator_type cell_it = test_output.cell_records().begin();
    BOOST_CHECK_EQUAL(cell_it->num_incident_edges(), 1);
    const voronoi_edge_type *edge1_1 = cell_it->incident_edge();
    const voronoi_edge_type *edge1_2 = edge1_1->twin();
    cell_it++;
    BOOST_CHECK_EQUAL(cell_it->num_incident_edges(), 2);
    cell_it++;
    BOOST_CHECK_EQUAL(cell_it->num_incident_edges(), 1);
    const voronoi_edge_type *edge2_2 = cell_it->incident_edge();
    const voronoi_edge_type *edge2_1 = edge2_2->twin();

    BOOST_CHECK_EQUAL(edge1_1->twin() == edge1_2 && edge1_2->twin() == edge1_1, true);
    BOOST_CHECK_EQUAL(edge2_1->twin() == edge2_2 && edge2_2->twin() == edge2_1, true);

    BOOST_CHECK_EQUAL(edge1_1->next() == edge1_1 && edge1_1->prev() == edge1_1, true);
    BOOST_CHECK_EQUAL(edge1_1->rot_next() == NULL && edge1_1->rot_prev() == NULL, true);
    BOOST_CHECK_EQUAL(edge1_2->rot_next() == NULL && edge1_2->rot_prev() == NULL, true);
    BOOST_CHECK_EQUAL(edge2_1->rot_next() == NULL && edge2_1->rot_prev() == NULL, true);
    BOOST_CHECK_EQUAL(edge2_2->next() == edge2_2 && edge2_2->prev() == edge2_2, true);
    BOOST_CHECK_EQUAL(edge2_2->rot_next() == NULL && edge2_2->rot_prev() == NULL, true);

    BOOST_CHECK_EQUAL(edge1_2->next() == edge2_1 && edge1_2->prev() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge2_1->next() == edge1_2 && edge2_1->prev() == edge1_2, true);
}

// Sites: (0, 0), (0, 4), (2, 1).
BOOST_AUTO_TEST_CASE_TEMPLATE(triangle_test1, T, test_types) {
    typedef double coordinate_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_edge_type voronoi_edge_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_vertex_const_iterator_type
        voronoi_vertex_const_iterator_type;

    point_2d<coordinate_type> point1 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(0), static_cast<coordinate_type>(0));
    point_2d<coordinate_type> point2 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(0), static_cast<coordinate_type>(4));
    point_2d<coordinate_type> point3 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(2), static_cast<coordinate_type>(1));

    std::vector< point_data<T> > points;
    points.push_back(point_data<T>(point1.x(), point1.y()));
    points.push_back(point_data<T>(point2.x(), point2.y()));
    points.push_back(point_data<T>(point3.x(), point3.y()));
    voronoi_diagram<coordinate_type> test_output;
    construct_voronoi_points<T>(points, test_output);
    VERIFY_OUTPUT(test_output);

    CHECK_BRECT(test_output.bounding_rectangle(), 0, 0, 2, 4);
    CHECK_OUTPUT_SIZE(test_output, 3, 1, 3);

    voronoi_vertex_const_iterator_type it = test_output.vertex_records().begin();
    BOOST_CHECK_EQUAL(it->vertex().x() == static_cast<coordinate_type>(0.25) &&
                      it->vertex().y() == static_cast<coordinate_type>(2.0), true);

    const voronoi_edge_type *edge1_1 = it->incident_edge();
    const voronoi_edge_type *edge1_2 = edge1_1->twin();
    CHECK_EQUAL_POINTS(edge1_1->cell()->point0(), point3);
    CHECK_EQUAL_POINTS(edge1_2->cell()->point0(), point1);

    const voronoi_edge_type *edge2_1 = edge1_1->rot_prev();
    const voronoi_edge_type *edge2_2 = edge2_1->twin();
    CHECK_EQUAL_POINTS(edge2_1->cell()->point0(), point1);
    CHECK_EQUAL_POINTS(edge2_2->cell()->point0(), point2);

    const voronoi_edge_type *edge3_1 = edge2_1->rot_prev();
    const voronoi_edge_type *edge3_2 = edge3_1->twin();
    CHECK_EQUAL_POINTS(edge3_1->cell()->point0(), point2);
    CHECK_EQUAL_POINTS(edge3_2->cell()->point0(), point3);

    BOOST_CHECK_EQUAL(edge1_2->twin() == edge1_1, true);
    BOOST_CHECK_EQUAL(edge2_2->twin() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge3_2->twin() == edge3_1, true);

    BOOST_CHECK_EQUAL(edge1_1->prev() == edge3_2 && edge1_1->next() == edge3_2, true);
    BOOST_CHECK_EQUAL(edge2_1->prev() == edge1_2 && edge2_1->next() == edge1_2, true);
    BOOST_CHECK_EQUAL(edge3_1->prev() == edge2_2 && edge3_1->next() == edge2_2, true);

    BOOST_CHECK_EQUAL(edge1_2->next() == edge2_1 && edge1_2->prev() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge2_2->next() == edge3_1 && edge2_2->prev() == edge3_1, true);
    BOOST_CHECK_EQUAL(edge3_2->next() == edge1_1 && edge3_2->prev() == edge1_1, true);

    BOOST_CHECK_EQUAL(edge1_1->rot_next() == edge3_1, true);
    BOOST_CHECK_EQUAL(edge3_1->rot_next() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge2_1->rot_next() == edge1_1, true);
}

// Sites: (0, 1), (2, 0), (2, 4).
BOOST_AUTO_TEST_CASE_TEMPLATE(triangle_test2, T, test_types) {
    typedef double coordinate_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_edge_type voronoi_edge_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_vertex_const_iterator_type
        voronoi_vertex_const_iterator_type;

    point_2d<coordinate_type> point1 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(0), static_cast<coordinate_type>(1));
    point_2d<coordinate_type> point2 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(2), static_cast<coordinate_type>(0));
    point_2d<coordinate_type> point3 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(2), static_cast<coordinate_type>(4));

    std::vector< point_data<T> > points;
    points.push_back(point_data<T>(point1.x(), point1.y()));
    points.push_back(point_data<T>(point2.x(), point2.y()));
    points.push_back(point_data<T>(point3.x(), point3.y()));
    voronoi_diagram<coordinate_type> test_output;
    construct_voronoi_points<T>(points, test_output);
    VERIFY_OUTPUT(test_output);

    CHECK_BRECT(test_output.bounding_rectangle(), 0, 0, 2, 4);
    CHECK_OUTPUT_SIZE(test_output, 3, 1, 3);

    voronoi_vertex_const_iterator_type it = test_output.vertex_records().begin();
    BOOST_CHECK_EQUAL(it->vertex().x() == static_cast<coordinate_type>(1.75) &&
                      it->vertex().y() == static_cast<coordinate_type>(2.0), true);

    const voronoi_edge_type *edge1_1 = it->incident_edge();
    const voronoi_edge_type *edge1_2 = edge1_1->twin();
    CHECK_EQUAL_POINTS(edge1_1->cell()->point0(), point2);
    CHECK_EQUAL_POINTS(edge1_2->cell()->point0(), point1);

    const voronoi_edge_type *edge2_1 = edge1_1->rot_prev();
    const voronoi_edge_type *edge2_2 = edge2_1->twin();
    CHECK_EQUAL_POINTS(edge2_1->cell()->point0(), point1);
    CHECK_EQUAL_POINTS(edge2_2->cell()->point0(), point3);

    const voronoi_edge_type *edge3_1 = edge2_1->rot_prev();
    const voronoi_edge_type *edge3_2 = edge3_1->twin();
    CHECK_EQUAL_POINTS(edge3_1->cell()->point0(), point3);
    CHECK_EQUAL_POINTS(edge3_2->cell()->point0(), point2);

    BOOST_CHECK_EQUAL(edge1_2->twin() == edge1_1, true);
    BOOST_CHECK_EQUAL(edge2_2->twin() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge3_2->twin() == edge3_1, true);

    BOOST_CHECK_EQUAL(edge1_1->prev() == edge3_2 && edge1_1->next() == edge3_2, true);
    BOOST_CHECK_EQUAL(edge2_1->prev() == edge1_2 && edge2_1->next() == edge1_2, true);
    BOOST_CHECK_EQUAL(edge3_1->prev() == edge2_2 && edge3_1->next() == edge2_2, true);

    BOOST_CHECK_EQUAL(edge1_2->next() == edge2_1 && edge1_2->prev() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge2_2->next() == edge3_1 && edge2_2->prev() == edge3_1, true);
    BOOST_CHECK_EQUAL(edge3_2->next() == edge1_1 && edge3_2->prev() == edge1_1, true);

    BOOST_CHECK_EQUAL(edge1_1->rot_next() == edge3_1, true);
    BOOST_CHECK_EQUAL(edge3_1->rot_next() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge2_1->rot_next() == edge1_1, true);
}

// Sites: (0, 0), (0, 1), (1, 0), (1, 1).
BOOST_AUTO_TEST_CASE_TEMPLATE(square_test1, T, test_types) {
    typedef double coordinate_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_edge_type voronoi_edge_type;
    typedef typename voronoi_diagram<coordinate_type>::voronoi_vertex_const_iterator_type
        voronoi_vertex_const_iterator_type;

    point_2d<coordinate_type> point1 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(0), static_cast<coordinate_type>(0));
    point_2d<coordinate_type> point2 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(0), static_cast<coordinate_type>(1));
    point_2d<coordinate_type> point3 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(1), static_cast<coordinate_type>(0));
    point_2d<coordinate_type> point4 = point_2d<coordinate_type>(
        static_cast<coordinate_type>(1), static_cast<coordinate_type>(1));

    std::vector< point_data<T> > points;
    points.push_back(point_data<T>(point1.x(), point1.y()));
    points.push_back(point_data<T>(point2.x(), point2.y()));
    points.push_back(point_data<T>(point3.x(), point3.y()));
    points.push_back(point_data<T>(point4.x(), point4.y()));
    voronoi_diagram<coordinate_type> test_output;
    construct_voronoi_points<T>(points, test_output);
    VERIFY_OUTPUT(test_output);

    CHECK_BRECT(test_output.bounding_rectangle(), 0, 0, 1, 1);
    CHECK_OUTPUT_SIZE(test_output, 4, 1, 4);

    // Check voronoi vertex.
    voronoi_vertex_const_iterator_type it = test_output.vertex_records().begin();
    BOOST_CHECK_EQUAL(it->vertex().x() == static_cast<coordinate_type>(0.5) &&
                      it->vertex().y() == static_cast<coordinate_type>(0.5), true);

    // Check voronoi edges.
    const voronoi_edge_type *edge1_1 = it->incident_edge();
    const voronoi_edge_type *edge1_2 = edge1_1->twin();
    CHECK_EQUAL_POINTS(edge1_1->cell()->point0(), points[1]);
    CHECK_EQUAL_POINTS(edge1_2->cell()->point0(), points[3]);

    const voronoi_edge_type *edge2_1 = edge1_1->rot_prev();
    const voronoi_edge_type *edge2_2 = edge2_1->twin();
    CHECK_EQUAL_POINTS(edge2_1->cell()->point0(), points[3]);
    CHECK_EQUAL_POINTS(edge2_2->cell()->point0(), points[2]);

    const voronoi_edge_type *edge3_1 = edge2_1->rot_prev();
    const voronoi_edge_type *edge3_2 = edge3_1->twin();
    CHECK_EQUAL_POINTS(edge3_1->cell()->point0(), points[2]);
    CHECK_EQUAL_POINTS(edge3_2->cell()->point0(), points[0]);

    const voronoi_edge_type *edge4_1 = edge3_1->rot_prev();
    const voronoi_edge_type *edge4_2 = edge4_1->twin();
    CHECK_EQUAL_POINTS(edge4_1->cell()->point0(), points[0]);
    CHECK_EQUAL_POINTS(edge4_2->cell()->point0(), points[1]);

    BOOST_CHECK_EQUAL(edge1_2->twin() == edge1_1, true);
    BOOST_CHECK_EQUAL(edge2_2->twin() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge3_2->twin() == edge3_1, true);
    BOOST_CHECK_EQUAL(edge4_2->twin() == edge4_1, true);

    BOOST_CHECK_EQUAL(edge1_1->prev() == edge4_2 && edge1_1->next() == edge4_2, true);
    BOOST_CHECK_EQUAL(edge2_1->prev() == edge1_2 && edge2_1->next() == edge1_2, true);
    BOOST_CHECK_EQUAL(edge3_1->prev() == edge2_2 && edge3_1->next() == edge2_2, true);
    BOOST_CHECK_EQUAL(edge4_1->prev() == edge3_2 && edge4_1->next() == edge3_2, true);

    BOOST_CHECK_EQUAL(edge1_2->next() == edge2_1 && edge1_2->prev() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge2_2->next() == edge3_1 && edge2_2->prev() == edge3_1, true);
    BOOST_CHECK_EQUAL(edge3_2->next() == edge4_1 && edge3_2->prev() == edge4_1, true);
    BOOST_CHECK_EQUAL(edge4_2->next() == edge1_1 && edge4_2->prev() == edge1_1, true);

    BOOST_CHECK_EQUAL(edge1_1->rot_next() == edge4_1, true);
    BOOST_CHECK_EQUAL(edge4_1->rot_next() == edge3_1, true);
    BOOST_CHECK_EQUAL(edge3_1->rot_next() == edge2_1, true);
    BOOST_CHECK_EQUAL(edge2_1->rot_next() == edge1_1, true);
}

#ifdef NDEBUG
BOOST_AUTO_TEST_CASE_TEMPLATE(grid_test, T, test_types) {
    voronoi_diagram<double> test_output_small, test_output_large;
    std::vector< point_data<T> > point_vec_small, point_vec_large;
    int grid_size[4] = {10, 33, 101, 163};
    int max_value[4] = {10, 33, 101, 163};
    int array_length = sizeof(grid_size) / sizeof(int);
    for (int k = 0; k < array_length; k++) {
        point_vec_small.clear();
        point_vec_large.clear();
        int koef = std::numeric_limits<int>::max() / max_value[k];
        for (int i = 0; i < grid_size[k]; i++)
            for (int j = 0; j < grid_size[k]; j++) {
                point_vec_small.push_back(point_data<T>(i, j));
                point_vec_large.push_back(point_data<T>(koef * i, koef * j));
            }
        construct_voronoi_points<T>(point_vec_small, test_output_small);
        construct_voronoi_points<T>(point_vec_large, test_output_large);
        VERIFY_OUTPUT(test_output_small);
        VERIFY_OUTPUT(test_output_large);
        int num_cells = grid_size[k] * grid_size[k];
        int num_vertices = num_cells - 2 * grid_size[k] + 1;
        int num_edges = 2 * num_cells - 2 * grid_size[k];
        CHECK_OUTPUT_SIZE(test_output_small, num_cells, num_vertices, num_edges);
        CHECK_OUTPUT_SIZE(test_output_large, num_cells, num_vertices, num_edges);
    }
}
#endif

#ifdef NDEBUG
BOOST_AUTO_TEST_CASE_TEMPLATE(random_test, T, test_types) {
    boost::mt19937 gen(static_cast<unsigned int>(time(NULL)));
    voronoi_diagram<double> test_output_small, test_output_large;
    std::vector< point_data<T> > point_vec_small, point_vec_large;
    int num_points[] = {5, 100, 1000, 10000, 100000};
    int num_runs[] = {10000, 1000, 100, 10, 1};
    int mod_koef[] = {10, 100, 100, 1000, 10000};
    int max_value[] = {5, 50, 50, 5000, 5000};
    int array_length = sizeof(num_points) / sizeof(int);
    for (int k = 0; k < array_length; k++) {
        int koef = std::numeric_limits<int>::max() / max_value[k];
        for (int i = 0; i < num_runs[k]; i++) {
            point_vec_small.clear();
            point_vec_large.clear();
            for (int j = 0; j < num_points[k]; j++) {
                T x = gen() % mod_koef[k] - mod_koef[k] / 2;
                T y = gen() % mod_koef[k] - mod_koef[k] / 2;
                point_vec_small.push_back(point_data<T>(x, y));
                point_vec_large.push_back(point_data<T>(koef * x, koef * y));
            }
            construct_voronoi_points<T>(point_vec_small, test_output_small);
            construct_voronoi_points<T>(point_vec_large, test_output_large);
            VERIFY_OUTPUT(test_output_small);
            VERIFY_OUTPUT(test_output_large);
            BOOST_CHECK_EQUAL(test_output_small.num_cell_records(),
                              test_output_large.num_cell_records());
            BOOST_CHECK_EQUAL(test_output_small.num_vertex_records(),
                              test_output_large.num_vertex_records());
            BOOST_CHECK_EQUAL(test_output_small.num_edge_records(),
                              test_output_large.num_edge_records());
        }
    }
}
#endif

#ifdef NDEBUG
BOOST_AUTO_TEST_CASE_TEMPLATE(enormous_random_test, T, test_types) {
    boost::mt19937 gen(static_cast<unsigned int>(time(NULL)));
    voronoi_diagram<double> test_output;
    std::vector< point_data<T> > point_vec;
    for (int i = 0; i < 1000000; i++)
        point_vec.push_back(point_data<T>(gen() % 10000 - 5000, gen() % 10000 - 5000));
    construct_voronoi_points<T>(point_vec, test_output);
    BOOST_CHECK_EQUAL(verify_output(test_output, FAST_VERIFICATION), true);
}
#endif

BOOST_AUTO_TEST_CASE_TEMPLATE(segment_sites_test1, T, test_types) {
    typedef T coordinate_type;
    voronoi_diagram<double> test_output;
    directed_line_segment_set_data<T> segments;
    point_data<T> point1(0, 0);
    point_data<T> point2(1, 1);
    segments.insert(directed_line_segment_data<T>(point1, point2));
    construct_voronoi_segments<T>(segments, test_output);
    CHECK_OUTPUT_SIZE(test_output, 3, 0, 2);
    BOOST_CHECK_EQUAL(verify_output(test_output, NO_HALF_EDGE_INTERSECTIONS), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(segment_sites_test2, T, test_types) {
    typedef T coordinate_type;
    voronoi_diagram<double> test_output;
    std::vector< point_data<T> > points;
    directed_line_segment_set_data<T> segments;
    point_data<T> point1(0, 0);
    point_data<T> point2(4, 4);
    point_data<T> point3(3, 1);
    point_data<T> point4(1, 3);
    segments.insert(directed_line_segment_data<T>(point1, point2));
    points.push_back(point3);
    points.push_back(point4);
    construct_voronoi<T>(points, segments, test_output);
    CHECK_OUTPUT_SIZE(test_output, 5, 4, 8);
    BOOST_CHECK_EQUAL(verify_output(test_output, NO_HALF_EDGE_INTERSECTIONS), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(segment_sites_test3, T, test_types) {
    typedef T coordinate_type;
    voronoi_diagram<double> test_output;
    std::vector< point_data<T> > points;
    directed_line_segment_set_data<T> segments;
    point_data<T> point1(4, 0);
    point_data<T> point2(0, 4);
    point_data<T> point3(3, 3);
    point_data<T> point4(1, 1);
    segments.insert(directed_line_segment_data<T>(point1, point2));
    points.push_back(point3);
    points.push_back(point4);
    construct_voronoi<T>(points, segments, test_output);
    CHECK_OUTPUT_SIZE(test_output, 5, 4, 8);
    BOOST_CHECK_EQUAL(verify_output(test_output, NO_HALF_EDGE_INTERSECTIONS), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(segment_sites_test4, T, test_types) {
    typedef T coordinate_type;
    voronoi_diagram<double> test_output;
    std::vector< point_data<T> > points;
    directed_line_segment_set_data<T> segments;
    point_data<T> point1(4, 0);
    point_data<T> point2(0, 4);
    point_data<T> point3(3, 2);
    point_data<T> point4(2, 3);
    segments.insert(directed_line_segment_data<T>(point1, point2));
    points.push_back(point3);
    points.push_back(point4);
    construct_voronoi<T>(points, segments, test_output);
    CHECK_OUTPUT_SIZE(test_output, 5, 3, 7);
    BOOST_CHECK_EQUAL(verify_output(test_output, NO_HALF_EDGE_INTERSECTIONS), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(segment_site_test5, T, test_types) {
    typedef T coordinate_type;
    voronoi_diagram<double> test_output;
    std::vector< point_data<T> > points;
    directed_line_segment_set_data<T> segments;
    point_data<T> point1(0, 0);
    point_data<T> point2(0, 8);
    point_data<T> point3(-2, -2);
    point_data<T> point4(-2, 4);
    point_data<T> point5(-2, 10);
    segments.insert(directed_line_segment_data<T>(point1, point2));
    points.push_back(point3);
    points.push_back(point4);
    points.push_back(point5);
    construct_voronoi<T>(points, segments, test_output);
    CHECK_OUTPUT_SIZE(test_output, 6, 4, 9);
    BOOST_CHECK_EQUAL(verify_output(test_output, NO_HALF_EDGE_INTERSECTIONS), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(segment_site_test6, T, test_types) {
    typedef T coordinate_type;
    voronoi_diagram<double> test_output;
    std::vector< point_data<T> > points;
    directed_line_segment_set_data<T> segments;
    point_data<T> point1(-1, 1);
    point_data<T> point2(1, 0);
    point_data<T> point3(1, 2);
    segments.insert(directed_line_segment_data<T>(point2, point3));
    points.push_back(point1);
    construct_voronoi<T>(points, segments, test_output);
    CHECK_OUTPUT_SIZE(test_output, 4, 2, 5);
    BOOST_CHECK_EQUAL(verify_output(test_output, NO_HALF_EDGE_INTERSECTIONS), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(segment_site_test7, T, test_types) {
    typedef T coordinate_type;
    voronoi_diagram<double> test_output;
    directed_line_segment_set_data<T> segments;
    point_data<T> point1(0, 0);
    point_data<T> point2(4, 0);
    point_data<T> point3(0, 4);
    point_data<T> point4(4, 4);
    segments.insert(directed_line_segment_data<T>(point1, point2));
    segments.insert(directed_line_segment_data<T>(point2, point3));
    segments.insert(directed_line_segment_data<T>(point3, point4));
    construct_voronoi_segments<T>(segments, test_output);
    CHECK_OUTPUT_SIZE(test_output, 7, 6, 12);
    BOOST_CHECK_EQUAL(verify_output(test_output, NO_HALF_EDGE_INTERSECTIONS), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(segment_site_test8, T, test_types) {
    typedef T coordinate_type;
    voronoi_diagram<double> test_output;
    directed_line_segment_set_data<T> segments;
    point_data<T> point1(0, 0);
    point_data<T> point2(4, 0);
    point_data<T> point3(4, 4);
    point_data<T> point4(0, 4);
    segments.insert(directed_line_segment_data<T>(point1, point2));
    segments.insert(directed_line_segment_data<T>(point2, point3));
    segments.insert(directed_line_segment_data<T>(point3, point4));
    segments.insert(directed_line_segment_data<T>(point4, point1));
    construct_voronoi_segments<T>(segments, test_output);
    CHECK_OUTPUT_SIZE(test_output, 8, 5, 12);
    BOOST_CHECK_EQUAL(verify_output(test_output, NO_HALF_EDGE_INTERSECTIONS), true);
}

#ifdef NDEBUG
BOOST_AUTO_TEST_CASE_TEMPLATE(segment_grid_test, T, test_types) {
    voronoi_diagram<double> test_output_small, test_output_large;
    directed_line_segment_set_data<T> segments_small, segments_large;
    int grid_size[] = {10, 33, 100};
    int max_value[] = {100, 330, 1000};
    int array_length = sizeof(grid_size) / sizeof(int);
    for (int k = 0; k < array_length; k++) {
        segments_small.clear();
        segments_large.clear();
        int cur_sz = grid_size[k];
        int koef = std::numeric_limits<int>::max() / max_value[k];
        for (int i = 0; i < cur_sz + 1; i++)
            for (int j = 0; j < cur_sz; j++) {
                point_data<T> point1_1(10 * i, 10 * j);
                point_data<T> point1_2(koef * 10 * i, koef * 10 * j);
                point_data<T> point2_1(10 * i, 10 * j + 10);
                point_data<T> point2_2(koef * 10 * i, koef * (10 * j + 10));
                segments_small.insert(directed_line_segment_data<T>(point1_1, point2_1));
                segments_large.insert(directed_line_segment_data<T>(point1_2, point2_2));
                point_data<T> point3_1(10 * j, 10 * i);
                point_data<T> point3_2(koef * 10 * j, koef * 10 * i);
                point_data<T> point4_1(10 * j + 10, 10 * i);
                point_data<T> point4_2(koef * (10 * j + 10), koef * 10 * i);
                segments_small.insert(directed_line_segment_data<T>(point3_1, point4_1));
                segments_large.insert(directed_line_segment_data<T>(point3_2, point4_2));
            }
        construct_voronoi_segments<T>(segments_small, test_output_small);
        construct_voronoi_segments<T>(segments_large, test_output_large);
        BOOST_CHECK_EQUAL(verify_output(test_output_small, NO_HALF_EDGE_INTERSECTIONS), true);
        BOOST_CHECK_EQUAL(verify_output(test_output_large, NO_HALF_EDGE_INTERSECTIONS), true);
        BOOST_CHECK_EQUAL(test_output_small.num_cell_records(), test_output_large.num_cell_records());
        BOOST_CHECK_EQUAL(test_output_small.num_vertex_records(), test_output_large.num_vertex_records());
        BOOST_CHECK_EQUAL(test_output_small.num_edge_records(), test_output_large.num_edge_records());
    }
}
#endif

#ifdef NDEBUG
BOOST_AUTO_TEST_CASE_TEMPLATE(segment_random_test1, T, test_types) {
    boost::mt19937 gen(static_cast<unsigned int>(time(NULL)));
    voronoi_diagram<double> test_output;
    std::vector< point_data<T> > points;
    directed_line_segment_set_data<T> segments;
    int num_runs = 1000;
    int num_segments = 10;
    points.push_back(point_data<T>(-100, -100));
    points.push_back(point_data<T>(-100, 100));
    points.push_back(point_data<T>(100, -100));
    points.push_back(point_data<T>(100, 100));
    for (int i = 0; i < num_runs; i++) {
        segments.clear();
        for (int j = 0; j < num_segments; j++) {
            T x1 = 0, y1 = 0, x2 = 0, y2 = 0;
            while (x1 == x2 && y1 == y2) {
                x1 = (gen() % 100) - 50;
                y1 = (gen() % 100) - 50;
                x2 = (gen() % 100) - 50;
                y2 = (gen() % 100) - 50;
            }
            point_data<T> point1(x1, y1);
            point_data<T> point2(x2, y2);
            segments.insert(directed_line_segment_data<T>(point1, point2));
        }
        segments.clean();
        construct_voronoi<T>(points, segments, test_output);
        BOOST_CHECK_EQUAL(verify_output(test_output, NO_HALF_EDGE_INTERSECTIONS), true);
    }
}
#endif

#ifdef NDEBUG
BOOST_AUTO_TEST_CASE_TEMPLATE(segment_random_test2, T, test_types) {
    boost::mt19937 gen(static_cast<unsigned int>(time(NULL)));
    voronoi_diagram<double> test_output_small, test_output_large;
    directed_line_segment_set_data<T> segments_small, segments_large;
    int num_segments[] = {5, 25, 125, 625};
    int num_runs[] = {1000, 100, 10, 1};
    int mod_koef1[] = {10, 100, 200, 300};
    int mod_koef2[] = {10, 20, 50, 100};
    int max_value[] = {10, 60, 125, 200};
    int array_length = sizeof(num_segments) / sizeof(int);
    for (int k = 0; k < array_length; k++) {
        int koef = std::numeric_limits<int>::max() / max_value[k];
        for (int i = 0; i < num_runs[k]; i++) {
            segments_small.clear();
            segments_large.clear();
            for (int j = 0; j < num_segments[k]; j++) {
                T x1 = (gen() % mod_koef1[k]) - mod_koef1[k] / 2;
                T y1 = (gen() % mod_koef1[k]) - mod_koef1[k] / 2;
                T dx = 0, dy = 0;
                while (dx == 0 && dy == 0) {
                    dx = (gen() % mod_koef2[k]) - mod_koef2[k] / 2;
                    dy = (gen() % mod_koef2[k]) - mod_koef2[k] / 2;
                }
                T x2 = x1 + dx;
                T y2 = y1 + dy;
                point_data<T> point1_small(x1, y1);
                point_data<T> point2_small(x2, y2);
                segments_small.insert(directed_line_segment_data<T>(point1_small, point2_small));
            }
            segments_small.clean();
            for (typename directed_line_segment_set_data<T>::iterator_type it = segments_small.begin();
                 it != segments_small.end(); ++it) {
                T x1 = it->low().x() * koef;
                T y1 = it->low().y() * koef;
                T x2 = it->high().x() * koef;
                T y2 = it->high().y() * koef;
                point_data<T> point1_large(x1, y1);
                point_data<T> point2_large(x2, y2);
                segments_large.insert(directed_line_segment_data<T>(point1_large, point2_large));
            }
            construct_voronoi_segments<T>(segments_small, test_output_small);
            construct_voronoi_segments<T>(segments_large, test_output_large);
            BOOST_CHECK_EQUAL(verify_output(test_output_small, NO_HALF_EDGE_INTERSECTIONS), true);
            BOOST_CHECK_EQUAL(verify_output(test_output_large, NO_HALF_EDGE_INTERSECTIONS), true);
            BOOST_CHECK_EQUAL(test_output_small.num_cell_records(), test_output_large.num_cell_records());
            BOOST_CHECK_EQUAL(test_output_small.num_vertex_records(), test_output_large.num_vertex_records());
            BOOST_CHECK_EQUAL(test_output_small.num_edge_records(), test_output_large.num_edge_records());
        }
    }
}
#endif
