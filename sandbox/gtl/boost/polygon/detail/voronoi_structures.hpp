// Boost.Polygon library detail/voronoi_structures.hpp header file

//          Copyright Andrii Sydorchuk 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI_STRUCTURES
#define BOOST_POLYGON_VORONOI_STRUCTURES

#include <list>
#include <queue>
#include <vector>

namespace boost {
namespace polygon {
namespace detail {
    // Cartesian 2D point data structure.
    template <typename T>
    class point_2d {
    public:
        typedef T coordinate_type;

        point_2d() {}

        point_2d(coordinate_type x, coordinate_type y) :
            x_(x),
            y_(y) {}

        bool operator==(const point_2d &that) const {
            return (this->x_ == that.x()) && (this->y_ == that.y());
        }

        bool operator!=(const point_2d &that) const {
            return (this->x_ != that.x()) || (this->y_ != that.y());
        }

        coordinate_type x() const {
            return x_;
        }

        coordinate_type y() const {
            return y_;
        }

        void x(coordinate_type x) {
            x_ = x;
        }

        void y(coordinate_type y) {
            y_ = y;
        }
    private:
        coordinate_type x_;
        coordinate_type y_;
    };

    // Site event type.
    // Occurs when the sweepline sweeps over one of the initial sites:
    //     1) point site;
    //     2) startpoint of the segment site;
    //     3) endpoint of the segment site.
    // Implicit segment direction is defined: the startpoint of
    // the segment compares less than its endpoint.
    // Each input segment is divided onto two site events:
    //     1) One going from the startpoint to the endpoint
    //        (is_inverse_ = false);
    //     2) Another going from the endpoint to the startpoint
    //        (is_inverse_ = true).
    // In beach line data structure segment sites of the first
    // type preceed sites of the second type for the same segment.
    // Variables: point0_ - point site or segment's startpoint;
    //            point1_ - segment's endpoint if site is a segment;
    //            index_ - site event index among other sites;
    //            is_inverse_ - defines type of the segment site.
    // Note: for all the sites is_inverse_ flag is equal to false by default.
    template <typename T>
    class site_event {
    public:
        typedef T coordinate_type;
        typedef point_2d<T> point_type;

        site_event() :
            point0_(0, 0),
            point1_(0, 0),
            is_inverse_(false) {}

        site_event(coordinate_type x, coordinate_type y, int index) :
            point0_(x, y),
            point1_(x, y),
            site_index_(index),
            is_inverse_(false) {}

        site_event(const point_type &point, int index) :
            point0_(point),
            point1_(point),
            site_index_(index),
            is_inverse_(false) {}

        site_event(coordinate_type x1, coordinate_type y1,
                   coordinate_type x2, coordinate_type y2, int index):
            point0_(x1, y1),
            point1_(x2, y2),
            site_index_(index),
            is_inverse_(false) {}

        site_event(const point_type &point1,
                   const point_type &point2, int index) :
            point0_(point1),
            point1_(point2),
            site_index_(index),
            is_inverse_(false) {}

        bool operator==(const site_event &that) const {
            return (this->point0_ == that.point0_) &&
                   (this->point1_ == that.point1_) &&
                   (this->site_index_ == that.site_index_) &&
                   (this->is_inverse_ == that.is_inverse_);
        }

        bool operator!=(const site_event &that) const {
            return (this->point0_ != that.point0_) ||
                   (this->point1_ != that.point1_) ||
                   (this->site_index_ != that.site_index_) ||
                   (this->is_inverse_ != that.is_inverse_);
        }

        coordinate_type x(bool oriented = false) const {
            return x0(oriented);
        }

        coordinate_type y(bool oriented = false) const {
            return y0(oriented);
        }

        coordinate_type x0(bool oriented = false) const {
            if (!oriented)
                return point0_.x();
            return is_inverse_ ? point1_.x() : point0_.x();
        }

        coordinate_type y0(bool oriented = false) const {
            if (!oriented)
                return point0_.y();
            return is_inverse_ ? point1_.y() : point0_.y();
        }

        coordinate_type x1(bool oriented = false) const {
            if (!oriented)
                return point1_.x();
            return is_inverse_ ? point0_.x() : point1_.x();
        }

        coordinate_type y1(bool oriented = false) const {
            if (!oriented)
                return point1_.y();
            return is_inverse_ ? point0_.y() : point1_.y();
        }

        const point_type &point0(bool oriented = false) const {
            if (!oriented)
                return point0_;
            return is_inverse_ ? point1_ : point0_;
        }

        const point_type &point1(bool oriented = false) const {
            if (!oriented)
                return point1_;
            return is_inverse_ ? point0_ : point1_;
        }

        void index(int index) {
            site_index_ = index;
        }

        void inverse() {
            is_inverse_ ^= true;
        }

        int index() const {
            return site_index_;
        }

        bool is_point() const {
            return point0_.x() == point1_.x() && point0_.y() == point1_.y();
        }

        bool is_segment() const {
            return point0_.x() != point1_.x() || point0_.y() != point1_.y();
        }

        bool is_inverse() const {
            return is_inverse_;
        }
    private:
        point_type point0_;
        point_type point1_;
        int site_index_;
        bool is_inverse_;
    };

    // Circle event type.
    // Occrus when the sweepline sweeps over the rightmost point of the voronoi
    // circle (with the center at the intersection point of the bisectors).
    // Circle event is made by the two consequtive nodes in the beach line data
    // structure. In case another node was inserted during algorithm execution
    // between the given two nodes circle event becomes inactive.
    // Variables: center_x_ - numerator of the center's x-coordinate.
    //            center_y_ - numerator of the center's y-coordinate.
    //            lower_x_ - numerator of the bottom point's x-coordinate.
    //            is_active_ - flag whether circle event is still active.
    // NOTE: lower_y coordinate is always equal to center_y.
    template <typename T>
    class circle_event {
    public:
        typedef T coordinate_type;

        circle_event() : is_active_(true) {}

        circle_event(coordinate_type c_x,
                     coordinate_type c_y,
                     coordinate_type lower_x) :
            center_x_(c_x),
            center_y_(c_y),
            lower_x_(lower_x),
            is_active_(true) {}

        coordinate_type x() const {
            return center_x_;
        }

        void x(coordinate_type center_x) {
            center_x_ = center_x;
        }

        coordinate_type y() const {
            return center_y_;
        }

        void y(coordinate_type center_y) {
            center_y_ = center_y;
        }

        coordinate_type lower_x() const {
            return lower_x_;
        }

        void lower_x(coordinate_type lower_x) {
            lower_x_ = lower_x;
        }

        coordinate_type lower_y() const {
            return center_y_;
        }

        bool is_active() const {
            return is_active_;
        }

        void deactivate() {
            is_active_ = false;
        }
    private:
        coordinate_type center_x_;
        coordinate_type center_y_;
        coordinate_type lower_x_;
        bool is_active_;
    };

    // Event queue data structure, holds circle events.
    // During algorithm run, some of the circle events disappear (become
    // inactive). Priority queue data structure doesn't support
    // iterators (there is no direct ability to modify its elements).
    // Instead list is used to store all the circle events and priority queue
    // of the iterators to the list elements is used to keep the correct circle
    // events ordering.
    template <typename T, typename Predicate>
    class ordered_queue {
    public:
        ordered_queue() {}

        bool empty() {
            return c_.empty();
        }

        const T &top() {
            return *c_.top();
        }

        void pop() {
            list_iterator_type it = c_.top();
            c_.pop();
            c_list_.erase(it);
        }

        T &push(const T &e) {
            c_list_.push_front(e);
            c_.push(c_list_.begin());
            return c_list_.front();
        }
    private:
        typedef typename std::list<T>::iterator list_iterator_type;

        struct comparison {
            Predicate cmp_;
            bool operator() (const list_iterator_type &it1,
                             const list_iterator_type &it2) const {
                return cmp_(*it1, *it2);
            }
        };

        std::priority_queue< list_iterator_type,
                             std::vector<list_iterator_type>,
                             comparison > c_;
        std::list<T> c_list_;

        //Disallow copy constructor and operator=
        ordered_queue(const ordered_queue&);
        void operator=(const ordered_queue&);
    };

    // Represents a bisector node made by two arcs that correspond to the left
    // and right sites. Arc is defined as a curve with points equidistant from
    // the site and from the sweepline. If the site is a point then arc is
    // a parabola, otherwise it's a line segment. A segment site event will
    // produce different bisectors based on its direction.
    // In the general case two sites will create two opposite bisectors. That's
    // why the order of the sites is important to define the unique bisector.
    // The one site is considered to be newer than the other one if it was
    // processed by the algorithm later (e.g. has greater index).
    template <typename Site>
    class beach_line_node_key {
    public:
        typedef Site site_type;

        // Constructs degenerate bisector, used to search an arc that is above
        // the given site. The input to the constructor is the new site point.
        explicit beach_line_node_key(const site_type &new_site) :
              left_site_(new_site),
              right_site_(new_site) {}

        // Constructs a new bisector. The input to the constructor is the two
        // sites that create the bisector. The order of sites is important.
        beach_line_node_key(const site_type &left_site,
                            const site_type &right_site) :
            left_site_(left_site),
            right_site_(right_site) {}

        const site_type &left_site() const {
            return left_site_;
        }

        site_type &left_site() {
            return left_site_;
        }

        void left_site(const site_type &site) {
            left_site_ = site;
        }

        const site_type &right_site() const {
            return right_site_;
        }

        site_type &right_site() {
            return right_site_;
        }

        void right_site(const site_type &site) {
            right_site_ = site;
        }
    private:
        site_type left_site_;
        site_type right_site_;
    };

    // Represents edge data sturcture from the voronoi output, that is
    // associated as a value with beach line bisector in the beach
    // line. Contains pointer to the circle event in the circle event
    // queue if the edge corresponds to the right bisector of the circle event.
    template <typename Edge, typename Circle>
    class beach_line_node_data {
    public:
        explicit beach_line_node_data(Edge *new_edge) :
            circle_event_(NULL),
            edge_(new_edge) {}

        Circle *circle_event() {
            return circle_event_;
        }

        void circle_event(Circle *circle_event) {
            circle_event_ = circle_event;
        }

        Edge *edge() {
            return edge_;
        }

        void edge(Edge *new_edge) {
            edge_ = new_edge;
        }
    private:
        Circle *circle_event_;
        Edge *edge_;
    };
} // detail
} // polygon
} // boost

#endif
