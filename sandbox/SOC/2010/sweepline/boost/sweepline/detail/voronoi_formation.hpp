// Boost sweepline/voronoi_formation.hpp header file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_SWEEPLINE_VORONOI_FORMATION
#define BOOST_SWEEPLINE_VORONOI_FORMATION

#include "mpt_wrapper.hpp"
#include "voronoi_fpt_kernel.hpp"

namespace boost {
namespace sweepline {

    template <typename T>
    class voronoi_edge;

namespace detail {

    ///////////////////////////////////////////////////////////////////////////
    // VORONOI EVENT TYPES ////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // Forward declarations.
    template <typename T>
    class beach_line_node;

    template <typename T>
    class beach_line_node_data;

    template <typename T>
    struct node_comparer;

    template <typename T>
    class epsilon_robust_comparator;

    // Represents the result of the orientation test.
    enum kOrientation {
        RIGHT_ORIENTATION = -1,
        COLLINEAR = 0,
        LEFT_ORIENTATION = 1,
    };

    // Cartesian 2D point data structure.
    template <typename T>
    class point_2d {
    public:
        typedef T coordinate_type;

        point_2d() {}

        point_2d(coordinate_type x, coordinate_type y) {
            x_ = x;
            y_ = y;
        }

        bool operator==(const point_2d &that) const {
            return (this->x_ == that.x()) && (this->y_ == that.y());
        }

        bool operator!=(const point_2d &that) const {
            return (this->x_ != that.x()) || (this->y_ != that.y());
        }

        // Comparison function.
        // Defines ordering of the points on the 2D plane.
        bool operator<(const point_2d &that) const {
            if (this->x_ != that.x_)
                return this->x_ < that.x_;
            return this->y_ < that.y_;
        }

        bool operator<=(const point_2d &that) const {
            return !(that < (*this));
        }

        bool operator>(const point_2d &that) const {
            return that < (*this);
        }

        bool operator>=(const point_2d &that) const {
            return !((*this) < that);
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
    //            is_segment_ - flag whether site is a segment;
    //            is_vertical_ - flag whether site is vertical;
    //            is_inverse_ - defines type of the segment site.
    // Note: for all the point sites is_vertical_ flag is true,
    //       is_inverse_ flag is false.
    template <typename T>
    class site_event {
    public:
        typedef T coordinate_type;
        typedef point_2d<T> point_type;

        // Point site contructors.
        site_event() :
            is_segment_(false),
            is_vertical_(true),
            is_inverse_(false) {}

        site_event(coordinate_type x, coordinate_type y, int index) :
            point0_(x, y),
            site_index_(index),
            is_segment_(false),
            is_vertical_(true),
            is_inverse_(false) {}

        site_event(const point_type &point, int index) :
            point0_(point),
            site_index_(index),
            is_segment_(false),
            is_vertical_(true),
            is_inverse_(false) {}

        // Segment site constructors.
        site_event(coordinate_type x1, coordinate_type y1,
                   coordinate_type x2, coordinate_type y2, int index):
            point0_(x1, y1),
            point1_(x2, y2),
            site_index_(index),
            is_segment_(true),
            is_inverse_(false) {
            if (point0_ > point1_)
                (std::swap)(point0_, point1_);
            is_vertical_ = (point0_.x() == point1_.x());
        }

        site_event(const point_type &point1,
                   const point_type &point2, int index) :
            point0_(point1),
            point1_(point2),
            site_index_(index),
            is_segment_(true),
            is_inverse_(false) {
            if (point0_ > point1_)
                (std::swap)(point0_, point1_);
            is_vertical_ = (point0_.x() == point1_.x());
        }

        bool operator==(const site_event &that) const {
            return (point0_ == that.point0_) &&
                   ((!is_segment_ && !that.is_segment_) ||
                   (is_segment_ && that.is_segment_ &&
                    point1_ == that.point1_));
        }

        bool operator!=(const site_event &that) const {
            return !((*this) == that);
        }

        // All the sites are sorted by the coordinates of the first point.
        // Point sites preceed vertical segment sites with equal first points.
        // Point sites and vertical segments preceed non-vertical segments
        // with the same x-coordinate of the first point (for any y).
        // Non-vertical segments with equal first points are ordered using
        // counterclockwise direction starting from the positive direction of
        // the x-axis. Such ordering simplifies the initialization step of the
        // algorithm.
        bool operator<(const site_event &that) const {
            // Compare x-coordinates of the first points.
            if (this->point0_.x() != that.point0_.x())
                return this->point0_.x() < that.point0_.x();

            // X-coordinates of the first points are the same.
            if (!(this->is_segment_)) {
                // The first site is a point.
                if (!that.is_segment_) {
                    // The second site is a point.
                    return this->point0_.y() < that.point0_.y();
                }
                if (that.is_vertical_) {
                    // The second site is a vertical segment.
                    return this->point0_.y() <= that.point0_.y();
                }
                // The second site is a non-vertical segment.
                return true;
            } else {
                // The first site is a segment.
                if (that.is_vertical_) {
                    // The second site is a point or a vertical segment.
                    if (this->is_vertical_) {
                        // The first site is a vertical segment.
                        return this->point0_.y() < that.point0_.y();
                    }
                    // The first site is a non-vertical segment.
                    return false;
                }

                // The second site is a non-vertical segment.
                if (this->is_vertical_) {
                    // The first site is a vertical segment.
                    return true;
                }

                // Compare y-coordinates of the first points.
                if (this->point0_.y() != that.point0_.y())
                    return this->point0_.y() < that.point0_.y();

                // Y-coordinates of the first points are the same.
                // Both sites are segment. Sort by angle using CCW ordering
                // starting at the positive direction of the x axis.
                return orientation_test(this->point1_, this->point0_,
                                        that.point1_) == LEFT_ORIENTATION;
            }
        }

        bool operator<=(const site_event &that) const {
            return !(that < (*this));
        }

        bool operator>(const site_event &that) const {
            return that < (*this);
        }

        bool operator>=(const site_event &that) const {
            return !((*this) < that);
        }

        coordinate_type x(bool oriented = false) const {
            return x0(oriented);
        }

        coordinate_type y(bool oriented = false) const {
            return y0(oriented);
        }

        // Return x-coordinate of the point for the point sites.
        // Return x-coordinate of the startpoint for the segment sites.
        coordinate_type x0(bool oriented = false) const {
            if (!oriented)
                return point0_.x();
            return is_inverse_ ? point1_.x() : point0_.x();
        }

        // Return y-coordinate of the point for the point sites.
        // Return y-coordinate of the startpoint for the segment sites.
        coordinate_type y0(bool oriented = false) const {
            if (!oriented)
                return point0_.y();
            return is_inverse_ ? point1_.y() : point0_.y();
        }

        // Return x-coordinate of the endpoint of the segment sites.
        // Doesn't make sense for the point sites.
        coordinate_type x1(bool oriented = false) const {
            if (!oriented)
                return point1_.x();
            return is_inverse_ ? point0_.x() : point1_.x();
        }

        // Return y-coordinate of the endpoint of the segment sites.
        // Doesn't make sense for the point sites.
        coordinate_type y1(bool oriented = false) const {
            if (!oriented)
                return point1_.y();
            return is_inverse_ ? point0_.y() : point1_.y();
        }

        // Return point for the point sites.
        // Return startpoint for the segment sites.
        const point_type &point0(bool oriented = false) const {
            if (!oriented)
                return point0_;
            return is_inverse_ ? point1_ : point0_;
        }

        // Return endpoint of the segment sites.
        // Doesn't make sense for the point sites.
        const point_type &point1(bool oriented = false) const {
            if (!oriented)
                return point1_;
            return is_inverse_ ? point0_ : point1_;
        }

        // Return index of the site among all the other sites.
        void index(int index) {
            site_index_ = index;
        }

        // Change segment site orientation to the opposite one.
        void inverse() {
            is_inverse_ ^= true;
        }

        int index() const {
            return site_index_;
        }

        bool is_segment() const {
            return is_segment_;
        }

        bool is_vertical() const {
            return is_vertical_;
        }

        bool is_inverse() const {
            return is_inverse_;
        }

    private:
        point_type point0_;
        point_type point1_;
        int site_index_;
        bool is_segment_;
        bool is_vertical_;
        bool is_inverse_;
    };

    template <typename T>
    static inline site_event<T> make_site_event(T x, T y, int index) {
        return site_event<T>(x, y, index);
    }

    template <typename T>
    static inline site_event<T> make_site_event(const point_2d<T> &point,
                                                int index) {
        return site_event<T>(point, index);
    }

    template <typename T>
    static inline site_event<T> make_site_event(T x1, T y1, T x2, T y2,
                                                int index) {
        return site_event<T>(x1, y1, x2, y2, index);
    }

    template <typename T>
    static inline site_event<T> make_site_event(const point_2d<T> &point1,
                                                const point_2d<T> &point2,
                                                int index) {
        return site_event<T>(point1, point2, index);
    }

    // Circle event type.
    // Occrus when the sweepline sweeps over the rightmost point of the voronoi
    // circle (with the center at the intersection point of the bisectors).
    // Circle event is made by the two consequtive nodes in the beach line data
    // structure. In case another node was inserted during algorithm execution
    // between the given two nodes circle event becomes inactive.
    // Circle events order is based on the comparison of the rightmost points
    // of the circles. The order is the same like for the point_2d class.
    // However as coordinates of the circle events might be not integers extra
    // comparison checks are required to make the comparison robust.
    // Next representation is used to store parameters of the circle:
    //     each of the parameters is represented as fraction
    //     numerator / denominator. Denominator is common for each of the
    //     three parameters. Epsilon robust comparator class is used
    //     to represent parameters of the circle events.
    // Variables: center_x_ - numerator of the center's x-coordinate.
    //            center_y_ - numerator of the center's y-coordinate.
    //            lower_x_ - numerator of the bottom point's x-coordinate.
    //            denom_ - positive denominator for the previous three values.
    //            bisector_node_ - iterator to the second bisector's node.
    //            is_active_ - flag whether circle event is still active.
    // lower_y coordinate is always equal to center_y.
    template <typename T>
    class circle_event {
    public:
        typedef T coordinate_type;
        typedef point_2d<T> point_type;
        typedef site_event<T> site_event_type;
        typedef epsilon_robust_comparator<T> erc_type;
        typedef beach_line_node<coordinate_type> Key;
        typedef beach_line_node_data<coordinate_type> Value;
        typedef node_comparer<Key> NodeComparer;
        typedef typename std::map< Key, Value, NodeComparer >::iterator
            beach_line_iterator;

        circle_event() : is_active_(true) {}

        circle_event(coordinate_type c_x,
                     coordinate_type c_y,
                     coordinate_type lower_x) :
            center_x_(c_x),
            center_y_(c_y),
            lower_x_(lower_x),
            is_active_(true) {}

        circle_event(const erc_type &c_x,
                     const erc_type &c_y,
                     const erc_type &lower_x) :
            center_x_(c_x),
            center_y_(c_y),
            lower_x_(lower_x),
            is_active_(true) {}

        bool operator==(const circle_event &that) const {
            return (this->lower_x_.compare(that.lower_x_, 128) == UNDEFINED &&
                    this->center_y_.compare(that.center_y_, 128) == UNDEFINED);
        }

        bool operator!=(const circle_event &that) const {
            return !((*this) == that);
        }

        // Compare rightmost points of the circle events.
        // Each rightmost point has next representation:
        // (lower_x / denom, center_y / denom), denom is always positive.
        bool operator<(const circle_event &that) const {
            // Compare x-coordinates of the rightmost points. If the result
            // is undefined we assume that x-coordinates are equal.
            kPredicateResult pres = this->lower_x_.compare(that.lower_x_, 128);
            if (pres != UNDEFINED)
                return (pres == LESS);

            // Compare y-coordinates of the rightmost points.
            return this->center_y_.compare(that.center_y_, 128) == LESS;
        }

        bool operator<=(const circle_event &that) const {
            return !(that < (*this));
        }

        bool operator>(const circle_event &that) const {
            return that < (*this);
        }

        bool operator>=(const circle_event &that) const {
            return !((*this) < that);
        }

        // Compare the rightmost point of the circle event with
        // the point that represents the site event.
        // If circle point is less than site point return -1.
        // If circle point is equal to site point return 0.
        // If circle point is greater than site point return 1.
        kPredicateResult compare(const site_event_type &s_event) const {
            // Compare x-coordinates.
            kPredicateResult pres = lower_x_.compare(s_event.x(), 64);
            // If the comparison result is undefined
            // x-coordinates are considered to be equal.
            if (pres != UNDEFINED)
                return pres;
            // Compare y-coordinates in case of equal x-coordinates.
            return center_y_.compare(s_event.y(), 64);
        }

        // Evaluate x-coordinate of the center of the circle.
        coordinate_type x() const {
            return center_x_.dif();
        }

        void x(coordinate_type center_x) {
            center_x_ = center_x;
        }

        // Evaluate y-coordinate of the center of the circle.
        coordinate_type y() const {
            return center_y_.dif();
        }

        void y(coordinate_type center_y) {
            center_y_ = center_y;
        }

        // Evaluate x-coordinate of the rightmost point of the circle.
        coordinate_type lower_x() const {
            return lower_x_.dif();
        }

        void lower_x(coordinate_type lower_x) {
            lower_x_ = lower_x;
        }

        point_type center() const {
            return point_type(x(), y());
        }

        const erc_type &erc_x() const {
            return center_x_;
        }

        const erc_type &erc_y() const {
            return center_y_;
        }

        // Return iterator to the second bisector from the beach line
        // data structure that forms current circle event.
        const beach_line_iterator &bisector() const {
            return bisector_node_;
        }

        void bisector(beach_line_iterator iterator) {
            bisector_node_ = iterator;
        }

        bool is_active() const {
            return is_active_;
        }

        void deactivate() {
            is_active_ = false;
        }

    private:
        erc_type center_x_;
        erc_type center_y_;
        erc_type lower_x_;
        beach_line_iterator bisector_node_;
        bool is_active_;
    };

    template <typename T>
    static inline circle_event<T> make_circle_event(T c_x, T c_y, T lower_x) {
        return circle_event<T>(c_x, c_y, lower_x);
    }

    ///////////////////////////////////////////////////////////////////////////
    // VORONOI CIRCLE EVENTS QUEUE ////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // Event queue data structure, holds circle events.
    // During algorithm run, some of the circle events disappear(become
    // inactive). Priority queue data structure by itself doesn't support
    // iterators (there is no direct ability to modify its elements).
    // Instead list is used to store all the circle events and priority queue
    // of the iterators to the list elements is used to keep the correct circle
    // events ordering.
    template <typename T>
    class circle_events_queue {
    public:
        typedef T coordinate_type;
        typedef circle_event<T> circle_event_type;
        typedef typename std::list<circle_event_type>::iterator
            circle_event_type_it;

        circle_events_queue() {}

        void clear() {
            while (!circle_events_.empty())
                circle_events_.pop();
            circle_events_list_.clear();
        }

        bool empty() {
            remove_not_active_events();
            return circle_events_.empty();
        }

        const circle_event_type &top() {
            remove_not_active_events();
            return (*circle_events_.top());
        }

        void pop() {
            circle_event_type_it temp_it = circle_events_.top();
            circle_events_.pop();
            circle_events_list_.erase(temp_it);
        }

        circle_event_type_it push(const circle_event_type &c_event) {
            circle_events_list_.push_front(c_event);
            circle_events_.push(circle_events_list_.begin());
            return circle_events_list_.begin();
        }

    private:
        struct comparison {
            bool operator() (const circle_event_type_it &node1,
                             const circle_event_type_it &node2) const {
                return (*node1) > (*node2);
            }
        };

        // Remove all the inactive events from the top of the priority
        // queue until the first active event is found.
        void remove_not_active_events() {
            while (!circle_events_.empty() &&
                   !circle_events_.top()->is_active())
                pop();
        }

        std::priority_queue< circle_event_type_it,
                             std::vector<circle_event_type_it>,
                             comparison > circle_events_;
        std::list<circle_event_type> circle_events_list_;

        //Disallow copy constructor and operator=
        circle_events_queue(const circle_events_queue&);
        void operator=(const circle_events_queue&);
    };

    ///////////////////////////////////////////////////////////////////////////
    // GEOMETRY PREDICATES ////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // Geometry predicates with floating-point variables usually require
    // high-precision predicates to retrieve the correct result.
    // Epsilon robust predicates give the result within some epsilon relative
    // error, but are a lot faster than high-precision predicates.
    // To make algorithm robust and efficient epsilon robust predicates are
    // used at the first step. In case of the undefined result high-precision
    // arithmetic is used to produce required robustness. This approach
    // requires exact computation of epsilon intervals within which epsilon
    // robust predicates have undefined value.
    // There are two ways to measure an error of floating-point calculations:
    // relative error and ULPs(units in the last place).
    // Let EPS be machine epsilon, then next inequalities have place:
    // 1 EPS <= 1 ULP <= 2 EPS (1), 0.5 ULP <= 1 EPS <= 1 ULP (2).
    // ULPs are good for measuring rounding errors and comparing values.
    // Relative erros are good for computation of general relative
    // errors of formulas or expressions. So to calculate epsilon
    // intervals within which epsilon robust predicates have undefined result
    // next schema is used:
    //     1) Compute rounding errors of initial variables using ULPs;
    //     2) Transform ULPs to epsilons using upper bound of the (1);
    //     3) Compute relative error of the formula using epsilon arithmetic;
    //     4) Transform epsilon to ULPs using upper bound of the (2);
    // In case two values are inside undefined ULP range use high-precision
    // arithmetic to produce the correct result, else output the result.
    // Look at almost_equal function to see how two floating-point variables
    // are checked to fit in the ULP range.
    // If A has relative error of r(A) and B has relative error of r(B) then:
    //     1) r(A + B) <= max(r(A), r(B)), for A * B >= 0;
    //     2) r(A - B) <= B*r(A)+A*r(B)/(A-B), for A * B >= 0;
    //     2) r(A * B) <= r(A) + r(B);
    //     3) r(A / B) <= r(A) + r(B);
    // In addition rounding error should be added, that is always equal to
    // 0.5 ULP or atmost 1 epsilon. As you might see from the above formulas
    // substraction relative error may be extremely large, that's why
    // epsilon robust comparator class is used to store floating point values
    // and avoid substraction.
    // For further information about relative errors and ULPs try this link:
    // http://docs.sun.com/source/806-3568/ncg_goldberg.html

    // Convert value to 64-bit unsigned integer.
    // Return true if the value is positive, else false.
    template <typename T>
    static inline bool convert_to_65_bit(
        T value, polygon_ulong_long_type &res) {
        if (value >= 0) {
            res = static_cast<polygon_ulong_long_type>(value);
            return true;
        } else {
            res = static_cast<polygon_ulong_long_type>(-value);
            return false;
        }
    }

    // Value is a determinant of two vectors.
    // Return orientation based on the sign of the determinant.
    template <typename T>
    static inline kOrientation orientation_test(T value) {
        if (value == static_cast<T>(0.0))
            return COLLINEAR;
        return (value < static_cast<T>(0.0)) ?
               RIGHT_ORIENTATION : LEFT_ORIENTATION;
    }

    // Compute robust cross_product: a1 * b2 - b1 * a2.
    // The result is correct with epsilon relative error equal to 2EPS.
    template <typename T>
    static double robust_cross_product(T a1_, T b1_, T a2_, T b2_) {
        polygon_ulong_long_type a1, b1, a2, b2;
        bool a1_plus, a2_plus, b1_plus, b2_plus;
        a1_plus = convert_to_65_bit(a1_, a1);
        b1_plus = convert_to_65_bit(b1_, b1);
        a2_plus = convert_to_65_bit(a2_, a2);
        b2_plus = convert_to_65_bit(b2_, b2);

        polygon_ulong_long_type expr_l = a1 * b2;
        bool expr_l_plus = (a1_plus == b2_plus) ? true : false;
        polygon_ulong_long_type expr_r = b1 * a2;
        bool expr_r_plus = (a2_plus == b1_plus) ? true : false;

        if (expr_l == 0)
            expr_l_plus = true;
        if (expr_r == 0)
            expr_r_plus = true;

        if ((expr_l_plus == expr_r_plus) && (expr_l == expr_r))
            return static_cast<T>(0.0);

        // Produce the result with epsilon relative error.
        if (!expr_l_plus) {
            if (expr_r_plus)
                return -static_cast<double>(expr_l) -
                        static_cast<double>(expr_r);
            else return (expr_l > expr_r) ?
                        -static_cast<double>(expr_l - expr_r) :
                        static_cast<double>(expr_r - expr_l);
        } else {
            if (!expr_r_plus)
                return static_cast<double>(expr_l) +
                       static_cast<double>(expr_r);
            else
                return (expr_l < expr_r) ?
                       -static_cast<double>(expr_r - expr_l) :
                       static_cast<double>(expr_l - expr_r);
        }
    }

    // Robust orientation test. Works correctly for any input type that
    // can be casted without lose of data to the integer type within a range
    // [-2^32, 2^32-1].
    // Arguments: dif_x1_, dif_y1 - coordinates of the first vector.
    //            dif_x2_, dif_y2 - coordinates of the second vector.
    // Returns orientation test result for input vectors.
    template <typename T>
    static kOrientation orientation_test(T dif_x1_, T dif_y1_,
                                         T dif_x2_, T dif_y2_) {
        return orientation_test(
            robust_cross_product(dif_x1_, dif_y1_, dif_x2_, dif_y2_));
    }

    // Robust orientation test. Works correctly for any input coordinate type
    // that can be casted without lose of data to integer type within a range
    // [-2^31, 2^31 - 1] - signed integer type.
    // Arguments: point1, point2 - represent the first vector;
    //            point2, point3 - represent the second vector;
    // Returns orientation test result for input vectors.
    template <typename T>
    static inline kOrientation orientation_test(const point_2d<T> &point1,
                                                const point_2d<T> &point2,
                                                const point_2d<T> &point3) {
        return orientation_test(
            robust_cross_product(point1.x() - point2.x(),
                                 point1.y() - point2.y(),
                                 point2.x() - point3.x(),
                                 point2.y() - point3.y()));
    }

    // Find the x-coordinate (relative to the sweepline position) of the point
    // of the intersection of the horizontal line going through the new site
    // with the arc corresponding to the point site.
    // The relative error is atmost 3EPS.
    template <typename T>
    static double find_distance_to_point_arc(const point_2d<T> &point_site,
                                             const point_2d<T> &new_point) {
        double dx = point_site.x() - new_point.x();
        double dy = point_site.y() - new_point.y();
        return (dx * dx + dy * dy) / (2 * dx);
    }

    // Find the x-coordinate (relative to the sweepline position) of the point
    // of the intersection of the horizontal line going through the new site
    // with the arc corresponding to the segment site.
    // The relative error is atmost 8EPS.
    template <typename T>
    static double find_distance_to_segment_arc(const site_event<T> &segment,
                                               const point_2d<T> &new_point) {
        if (segment.is_vertical()) {
            return (segment.point0().x() - new_point.x()) * 0.5;
        } else {
            const point_2d<T> &segment_start = segment.point1();
            const point_2d<T> &segment_end = segment.point0();
            double a1 = segment_end.x() - segment_start.x();
            double b1 = segment_end.y() - segment_start.y();
            double a3 = new_point.x() - segment_start.x();
            double b3 = new_point.y() - segment_start.y();
            double k = std::sqrt(a1 * a1 + b1 * b1);
            // Avoid substraction while computing k.
            if (segment.is_inverse()) {
                if (b1 >= 0.0) {
                    k = 1.0 / (b1 + k);
                } else {
                    k = (-b1 + k) / (a1 * a1);
                }
            } else {
                if (b1 >= 0.0) {
                    k = (-b1 - k) / (a1 * a1);
                } else {
                    k = 1.0 / (b1 - k);
                }
            }
            // Relative error of the robust cross product is 2EPS.
            // Relative error of the k is atmost 5EPS.
            // The resulting relative error is atmost 8EPS.
            return robust_cross_product(a1, b1, a3, b3) * k;
        }
    }

    //// Robust 65-bit predicate, avoids using high-precision libraries.
    //// Works correctly for any input coordinate type that can be casted without
    //// lose of data to the integer type within a range [-2^31, 2^31 - 1].
    //template <typename T>
    //static bool robust_65bit_less_predicate(const point_2d<T> &left_point,
    //                                        const point_2d<T> &right_point,
    //                                        const point_2d<T> &new_point) {
    //    polygon_ulong_long_type a1, a2, b1, b2;
    //    polygon_ulong_long_type b1_sqr, b2_sqr, l_expr, r_expr;
    //    bool l_expr_plus, r_expr_plus;

    //    // Compute a1 = (x0-x1), a2 = (x0-x2), b1 = (y0 - y1), b2 = (y0 - y2).
    //    convert_to_65_bit(new_point.x() - left_point.x(), a1);
    //    convert_to_65_bit(new_point.x() - right_point.x(), a2);
    //    convert_to_65_bit(new_point.y() - left_point.y(), b1);
    //    convert_to_65_bit(new_point.y() - right_point.y(), b2);

    //    // Compute b1_sqr = (y0-y1)^2 and b2_sqr = (y0-y2)^2.
    //    b1_sqr = b1 * b1;
    //    b2_sqr = b2 * b2;
    //    polygon_ulong_long_type b1_sqr_mod = b1_sqr % a1;
    //    polygon_ulong_long_type b2_sqr_mod = b2_sqr % a2;

    //    // Compute l_expr = (x1 - x2).
    //    l_expr_plus = convert_to_65_bit(left_point.x() - right_point.x(), l_expr);

    //    // In case (b2_sqr / a2) < (b1_sqr / a1), decrease left_expr by 1.
    //    if (b2_sqr_mod * a1 < b1_sqr_mod * a2) {
    //        if (!l_expr_plus)
    //            ++l_expr;
    //        else if (l_expr != 0)
    //            --l_expr;
    //        else {
    //            ++l_expr;
    //            l_expr_plus = false;
    //        }
    //    }

    //    // Compute right expression.
    //    polygon_ulong_long_type value1 = b1_sqr / a1;
    //    polygon_ulong_long_type value2 = b2_sqr / a2;
    //    if (value1 >= value2) {
    //        r_expr = value1 - value2;
    //        r_expr_plus = true;
    //    } else {
    //        r_expr = value2 - value1;
    //        r_expr_plus = false;
    //    }

    //    // Compare left and right expressions.
    //    if (!l_expr_plus && r_expr_plus)
    //        return true;
    //    if (l_expr_plus && !r_expr_plus)
    //        return false;
    //    if (l_expr_plus && r_expr_plus)
    //        return l_expr < r_expr;
    //    return l_expr > r_expr;
    //}

    // Robust predicate, avoids using high-precision libraries.
    // Returns true if a horizontal line going through the new point site
    // intersects right arc at first, else returns false. If horizontal line
    // goes through intersection point of the given two arcs returns false.
    // Works correctly for any input coordinate type that can be casted without
    // lose of data to the integer type within a range [-2^31, 2^31-1].
    template <typename T>
    static bool less_predicate(const point_2d<T> &left_point,
                               const point_2d<T> &right_point,
                               const point_2d<T> &new_point) {
        // Any two point sites with different x-coordinates create two
        // bisectors. Each bisector is defined by the order the sites
        // appear in its representation. Predicates used in this function
        // won't produce the correct result for the any arrangment of the
        // input sites. That's why some preprocessing is required to handle
        // such cases.
        if (left_point.x() > right_point.x()) {
            if (new_point.y() <= left_point.y())
                return false;
        } else if (left_point.x() < right_point.x()) {
            if (new_point.y() >= right_point.y())
                return true;
        } else {
            // If x-coordinates of the sites are equal, we may produce the
            // result without any further computations.
            return left_point.y() + right_point.y() < 2.0 * new_point.y();
        }

        double dist1 = find_distance_to_point_arc(left_point, new_point);
        double dist2 = find_distance_to_point_arc(right_point, new_point);

        // The undefined ulp range is equal to 3EPS + 3EPS <= 6ULP.
        return dist1 < dist2;
    }

    template <typename T>
    static kPredicateResult fast_less_predicate(point_2d<T> site_point, site_event<T> segment_site,
                                                point_2d<T> new_point, bool reverse_order) {
        if (orientation_test(segment_site.point0(true), segment_site.point1(true),
            new_point) != RIGHT_ORIENTATION) {
            return (!segment_site.is_inverse()) ? LESS : MORE;
        }

        const point_2d<T> &segment_start = segment_site.point0(true);
        const point_2d<T> &segment_end = segment_site.point1(true);
        double dif_x = new_point.x() - site_point.x();
        double dif_y = new_point.y() - site_point.y();
        double a = segment_end.x() - segment_start.x();
        double b = segment_end.y() - segment_start.y();

        if (segment_site.is_vertical()) {
            if (new_point.y() < site_point.y() && !reverse_order)
                return MORE;
            else if (new_point.y() > site_point.y() && reverse_order)
                return LESS;
            return UNDEFINED;
        } else {
            kOrientation orientation = orientation_test(a, b, dif_x, dif_y);
            if (orientation == LEFT_ORIENTATION) {
                if (!segment_site.is_inverse())
                    return reverse_order ? LESS : UNDEFINED;
                return reverse_order ? UNDEFINED : MORE;
            }
        }

        double fast_left_expr = a * (dif_y + dif_x) * (dif_y - dif_x);
        double fast_right_expr = (2.0 * b) * dif_x * dif_y;
        if (!(almost_equal(fast_left_expr, fast_right_expr, 4))) {
            if ((fast_left_expr > fast_right_expr) ^ reverse_order)
                return reverse_order ? LESS : MORE;
            return UNDEFINED;
        }
        return UNDEFINED;
    }

    // Returns true if a horizontal line going through a new site intersects
    // right arc at first, else returns false. If horizontal line goes
    // through intersection point of the given two arcs returns false also.
    // reverse_order flag defines arrangement of the sites. If it's false
    // the order is (point, segment), else - (segment, point).
    template <typename T>
    static bool less_predicate(point_2d<T> site_point, site_event<T> segment_site,
                               point_2d<T> new_point, bool reverse_order) {
        kPredicateResult fast_res = fast_less_predicate(
            site_point, segment_site, new_point, reverse_order);
        if (fast_res != UNDEFINED) {
            return (fast_res == LESS);
        }

        double dist1 = find_distance_to_point_arc(site_point, new_point);
        double dist2 = find_distance_to_segment_arc(segment_site, new_point);

        // The undefined ulp range is equal to 3EPS + 8EPS <= 11ULP.
        return reverse_order ^ (dist1 < dist2);
    }

    // Returns true if a horizontal line going through a new site intersects
    // right arc at first, else returns false. If horizontal line goes
    // through intersection point of the given two arcs returns false also.
    template <typename T>
    static bool less_predicate(site_event<T> left_segment,
                               site_event<T> right_segment,
                               point_2d<T> new_point) {
        // Handle temporary segment sites.
        if (left_segment.index() == right_segment.index()) {
            return orientation_test(left_segment.point0(),
                                    left_segment.point1(),
                                    new_point) == LEFT_ORIENTATION;
        }

        // Distances between the x-coordinate of the sweepline and
        // the x-coordinates of the points of the intersections of the
        // horizontal line going through the new site with arcs corresponding
        // to the first and to the second segment sites respectively.
        double dist1 = find_distance_to_segment_arc(left_segment, new_point);
        double dist2 = find_distance_to_segment_arc(right_segment, new_point);

        // The undefined ulp range is equal to 8EPS + 8EPS <= 16ULP.
        return dist1 < dist2;
    }

    ///////////////////////////////////////////////////////////////////////////
    // CIRCLE EVENTS CREATION /////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // At the moment all the circle event creation functions use the
    // epsilon_robust_comparator class to output the parameters of the
    // inscribed circle. Such approach may produce incorrect results while
    // comparing two circle events. In such cases high-precision functions
    // are required to recalculate circle's parameters.

    template <typename T>
    static inline T sqr_distance(T dif_x, T dif_y) {
        return dif_x * dif_x + dif_y * dif_y;
    }

    // Recompute parameters of the circle event using high-precision library.
    template <typename T>
    static bool create_circle_event_ppp_gmpxx(const site_event<T> &site1,
                                              const site_event<T> &site2,
                                              const site_event<T> &site3,
                                              circle_event<T> &c_event,
                                              bool recompute_c_x = true,
                                              bool recompute_c_y = true,
                                              bool recompute_lower_x = true) {
        typedef mpt_wrapper<mpz_class, 8> mpt_type;
        static mpt_type mpz_dif_x[3], mpz_dif_y[3], mpz_sum_x[2], mpz_sum_y[2],
                        mpz_numerator[3], mpz_c_x, mpz_c_y, mpz_sqr_r, denom,
                        cA[2], cB[2];
        mpz_dif_x[0] = site1.x() - site2.x();
        mpz_dif_x[1] = site2.x() - site3.x();
        mpz_dif_x[2] = site1.x() - site3.x();
        mpz_dif_y[0] = site1.y() - site2.y();
        mpz_dif_y[1] = site2.y() - site3.y();
        mpz_dif_y[2] = site1.y() - site3.y();
        denom = (mpz_dif_x[0] * mpz_dif_y[1] - mpz_dif_x[1] * mpz_dif_y[0]) * 2.0;
        mpz_sum_x[0] = site1.x() + site2.x();
        mpz_sum_x[1] = site2.x() + site3.x();
        mpz_sum_y[0] = site1.y() + site2.y();
        mpz_sum_y[1] = site2.y() + site3.y();
    
        mpz_numerator[1] = mpz_dif_x[0] * mpz_sum_x[0] + mpz_dif_y[0] * mpz_sum_y[0];
        mpz_numerator[2] = mpz_dif_x[1] * mpz_sum_x[1] + mpz_dif_y[1] * mpz_sum_y[1];

        if (recompute_c_x || recompute_lower_x) {
            mpz_c_x = mpz_numerator[1] * mpz_dif_y[1] - mpz_numerator[2] * mpz_dif_y[0];
            c_event.x(mpz_c_x.get_d() / denom.get_d());

            if (recompute_lower_x) {
                // Evaluate radius of the circle.
                mpz_sqr_r = 1.0;
                for (int i = 0; i < 3; ++i)
                    mpz_sqr_r *= mpz_dif_x[i] * mpz_dif_x[i] + mpz_dif_y[i] * mpz_dif_y[i];
                double r = std::sqrt(mpz_sqr_r.get_d());

                // If c_x >= 0 then lower_x = c_x + r,
                // else lower_x = (c_x * c_x - r * r) / (c_x - r).
                // To guarantee epsilon relative error.
                if (c_event.x() >= 0) {
                    c_event.lower_x(c_event.x() + r / fabs(denom.get_d()));
                } else {
                    mpz_numerator[0] = mpz_c_x * mpz_c_x - mpz_sqr_r;
                    double lower_x = mpz_numerator[0].get_d() /
                                     (denom.get_d() * (mpz_c_x.get_d() + r));
                    c_event.lower_x(lower_x);
                }
            }
        }

        if (recompute_c_y) {
            mpz_c_y = mpz_numerator[2] * mpz_dif_x[0] - mpz_numerator[1] * mpz_dif_x[1];
            c_event.y(mpz_c_y.get_d() / denom.get_d());
        }

        return true;
    }

    // Recompute parameters of the circle event using high-precision library.
    template <typename T>
    static bool create_circle_event_pps_gmpxx(const site_event<T> &site1,
                                              const site_event<T> &site2,
                                              const site_event<T> &site3,
                                              int segment_index,
                                              circle_event<T> &c_event,
                                              bool recompute_c_x = true,
                                              bool recompute_c_y = true,
                                              bool recompute_lower_x = true) {
        typedef mpt_wrapper<mpz_class, 8> mpt_type;
        typedef mpt_wrapper<mpf_class, 2> mpf_type;
        static mpt_type line_a, line_b, segm_len, vec_x, vec_y, sum_x, sum_y, teta,
                        denom, A, B, sum_AB, dif[2], numer, cA[4], cB[4], det;

        line_a = site3.point1(true).y() - site3.point0(true).y();
        line_b = site3.point0(true).x() - site3.point1(true).x();
        segm_len = line_a * line_a + line_b * line_b;
        vec_x = site2.y() - site1.y();
        vec_y = site1.x() - site2.x();
        sum_x = site1.x() + site2.x();
        sum_y = site1.y() + site2.y();
        teta = line_a * vec_x + line_b * vec_y;
        denom = vec_x * line_b - vec_y * line_a;
        
        dif[0] = site3.point1().y() - site1.y();
        dif[1] = site1.x() - site3.point1().x();
        A = line_a * dif[1] - line_b * dif[0];
        dif[0] = site3.point1().y() - site2.y();
        dif[1] = site2.x() - site3.point1().x();
        B = line_a * dif[1] - line_b * dif[0];
        sum_AB = A + B;

        if (denom == 0) {
            numer = teta * teta - sum_AB * sum_AB;
            denom = teta * sum_AB;
            cA[0] = denom * sum_x * 2 + numer * vec_x;
            cB[0] = segm_len;
            cA[1] = denom * sum_AB * 2 + numer * teta;
            cB[1] = 1;
            cA[2] = denom * sum_y * 2 + numer * vec_y;
            if (recompute_c_x) {
                c_event.x(0.25 * cA[0].get_d() / denom.get_d());
            }
            if (recompute_c_y) {
                c_event.y(0.25 * cA[2].get_d() / denom.get_d());
            }
            if (recompute_lower_x) {
                c_event.lower_x(0.25 * sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(cA, cB).get_d() /
                                (denom.get_d() * std::sqrt(segm_len.get_d())));
            }
            return true;
        }

        det = (teta * teta + denom * denom) * A * B * 4;
        double denom_sqr = denom.get_d() * denom.get_d();

        if (recompute_c_x || recompute_lower_x) {
            cA[0] = sum_x * denom * denom + teta * sum_AB * vec_x;
            cB[0] = 1;
            cA[1] = (segment_index == 2) ? -vec_x : vec_x;
            cB[1] = det;
            if (recompute_c_x) {
                c_event.x(0.5 * sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(cA, cB).get_d() /
                          denom_sqr);
            }
        }
        
        if (recompute_c_y || recompute_lower_x) {
            cA[2] = sum_y * denom * denom + teta * sum_AB * vec_y;
            cB[2] = 1;
            cA[3] = (segment_index == 2) ? -vec_y : vec_y;
            cB[3] = det;
            if (recompute_c_y) {
                c_event.y(0.5 * sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(&cA[2], &cB[2]).get_d() /
                          denom_sqr);
            }
        }
        
        if (recompute_lower_x) {
            cB[0] *= segm_len;
            cB[1] *= segm_len;
            cA[2] = sum_AB * (denom * denom + teta * teta);
            cB[2] = 1;
            cA[3] = (segment_index == 2) ? -teta : teta;
            cB[3] = det;
            c_event.lower_x(0.5 * sqrt_expr_evaluator<4>::eval<mpt_type, mpf_type>(cA, cB).get_d() /
                            (denom_sqr * std::sqrt(segm_len.get_d())));
        }
        
        return true;
    }

    // Evaluates A[3] + A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) +
    //           A[2] * sqrt(B[3] * (sqrt(B[0] * B[1]) + B[2]));
    template <typename mpt, typename mpf>
    static mpf sqrt_expr_evaluator_pss(mpt *A, mpt *B) {
        static mpt cA[4], cB[4];
        static mpf lh, rh, numer;
        if (A[3] == 0) {
            lh = sqrt_expr_evaluator<2>::eval<mpt, mpf>(A, B);
            cA[0] = 1;
            cB[0] = B[0] * B[1];
            cA[1] = B[2];
            cB[1] = 1;
            rh = A[2].get_d() * std::sqrt(B[3].get_d() *
                sqrt_expr_evaluator<2>::eval<mpt, mpf>(cA, cB).get_d());
            if (((lh >= 0) && (rh >= 0)) || ((lh <= 0) && (rh <= 0))) {
                return lh + rh;
            }
            cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1];
            cA[0] -= A[2] * A[2] * B[3] * B[2];
            cB[0] = 1;
            cA[1] = A[0] * A[1] * 2 - A[2] * A[2] * B[3];
            cB[1] = B[0] * B[1];
            numer = sqrt_expr_evaluator<2>::eval<mpt, mpf>(cA, cB);
            return numer / (lh - rh);
        }
        cA[0] = A[3];
        cB[0] = 1;
        cA[1] = A[0];
        cB[1] = B[0];
        cA[2] = A[1];
        cB[2] = B[1];
        lh = sqrt_expr_evaluator<3>::eval<mpt, mpf>(cA, cB);
        cA[0] = 1;
        cB[0] = B[0] * B[1];
        cA[1] = B[2];
        cB[1] = 1;
        rh = A[2].get_d() * std::sqrt(B[3].get_d() *
            sqrt_expr_evaluator<2>::eval<mpt, mpf>(cA, cB).get_d());
        if (((lh >= 0) && (rh >= 0)) || ((lh <= 0) && (rh <= 0))) {
            return lh + rh;
        }
        cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1];
        cA[0] += A[3] * A[3] - A[2] * A[2] * B[2] * B[3];
        cB[0] = 1;
        cA[1] = A[3] * A[0] * 2;
        cB[1] = B[0];
        cA[2] = A[3] * A[1] * 2;
        cB[2] = B[1];
        cA[3] = A[0] * A[1] * 2 - A[2] * A[2] * B[3];
        cB[3] = B[0] * B[1];
        numer = sqrt_expr_evaluator<4>::eval<mpt, mpf>(cA, cB);
        return numer / (lh - rh);
    }

    // Recompute parameters of the circle event using high-precision library.
    template <typename T>
    static bool create_circle_event_pss_gmpxx(const site_event<T> &site1,
                                              const site_event<T> &site2,
                                              const site_event<T> &site3,
                                              int point_index,
                                              circle_event<T> &c_event,
                                              bool recompute_c_x = true,
                                              bool recompute_c_y = true,
                                              bool recompute_lower_x = true) {
        typedef mpt_wrapper<mpz_class, 8> mpt_type;
        typedef mpt_wrapper<mpf_class, 2> mpf_type;
        static mpt_type a[2], b[2], c[2], cA[4], cB[4], orientation, dx, dy, ix, iy;

        const point_2d<T> &segm_start1 = site2.point1(true);
        const point_2d<T> &segm_end1 = site2.point0(true);
        const point_2d<T> &segm_start2 = site3.point0(true);
        const point_2d<T> &segm_end2 = site3.point1(true);

        a[0] = segm_end1.x() - segm_start1.x();
        b[0] = segm_end1.y() - segm_start1.y();
        a[1] = segm_end2.x() - segm_start2.x();
        b[1] = segm_end2.y() - segm_start2.y();
        orientation = a[1] * b[0] - a[0] * b[1];
        if (orientation == 0) {
            double denom = (a[0] * a[0] + b[0] * b[0]).get_d() * 2.0;
            c[0] = b[0] * (segm_start2.x() - segm_start1.x()) -
                   a[0] * (segm_start2.y() - segm_start1.y());
            dx = a[0] * (site1.y() - segm_start1.y()) -
                 b[0] * (site1.x() - segm_start1.x());
            dy = b[0] * (site1.x() - segm_start2.x()) -
                 a[0] * (site1.y() - segm_start2.y());
            cB[0] = dx * dy;
            cB[1] = 1;

            if (recompute_c_y) {
                cA[0] = b[0] * ((point_index == 2) ? 2 : -2);
                cA[1] = a[0] * a[0] * (segm_start1.y() + segm_start2.y()) -
                        a[0] * b[0] * (segm_start1.x() + segm_start2.x() - 2.0 * site1.x()) +
                        b[0] * b[0] * (2.0 * site1.y());
                double c_y = sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(cA, cB).get_d();
                c_event.y(c_y / denom);
            }

            if (recompute_c_x || recompute_lower_x) {
                cA[0] = a[0] * ((point_index == 2) ? 2 : -2);
                cA[1] = b[0] * b[0] * (segm_start1.x() + segm_start2.x()) -
                        a[0] * b[0] * (segm_start1.y() + segm_start2.y() - 2.0 * site1.y()) +
                        a[0] * a[0] * (2.0 * site1.x());

                if (recompute_c_x) {
                    double c_x = sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(cA, cB).get_d();
                    c_event.x(c_x / denom);
                }

                if (recompute_lower_x) {
                    cA[2] = (c[0] < 0) ? -c[0] : c[0];
                    cB[2] = a[0] * a[0] + b[0] * b[0];
                    double lower_x = sqrt_expr_evaluator<3>::eval<mpt_type, mpf_type>(cA, cB).get_d();
                    c_event.lower_x(lower_x / denom);
                }
            }
            return true;
        }
        c[0] = b[0] * segm_end1.x() - a[0] * segm_end1.y();
        c[1] = a[1] * segm_end2.y() - b[1] * segm_end2.x();
        ix = a[0] * c[1] + a[1] * c[0];
        iy = b[0] * c[1] + b[1] * c[0];
        dx = ix - orientation * site1.x();
        dy = iy - orientation * site1.y();
        if ((dx == 0) && (dy == 0)) {
            double denom = orientation.get_d();
            double c_x = ix.get_d() / denom;
            double c_y = iy.get_d() / denom;
            c_event = circle_event<T>(c_x, c_y, c_x);
            return true;
        }

        double sign = ((point_index == 2) ? 1 : -1) * ((orientation < 0) ? 1 : -1);
        cA[0] = a[1] * -dx + b[1] * -dy;
        cA[1] = a[0] * -dx + b[0] * -dy;
        cA[2] = sign;
        cA[3] = 0;
        cB[0] = a[0] * a[0] + b[0] * b[0];
        cB[1] = a[1] * a[1] + b[1] * b[1];
        cB[2] = a[0] * a[1] + b[0] * b[1];
        cB[3] = (a[0] * dy - b[0] * dx) * (a[1] * dy - b[1] * dx) * -2;
        double temp = sqrt_expr_evaluator_pss<mpt_type, mpf_type>(cA, cB).get_d();
        double denom = temp * orientation.get_d();

        if (recompute_c_y) {
            cA[0] = b[1] * (dx * dx + dy * dy) - iy * (dx * a[1] + dy * b[1]);
            cA[1] = b[0] * (dx * dx + dy * dy) - iy * (dx * a[0] + dy * b[0]);
            cA[2] = iy * sign;
            double cy = sqrt_expr_evaluator_pss<mpt_type, mpf_type>(cA, cB).get_d();
            c_event.y(cy / denom);
        }

        if (recompute_c_x || recompute_lower_x) {
            cA[0] = a[1] * (dx * dx + dy * dy) - ix * (dx * a[1] + dy * b[1]);
            cA[1] = a[0] * (dx * dx + dy * dy) - ix * (dx * a[0] + dy * b[0]);
            cA[2] = ix * sign;

            if (recompute_c_x) {
                double cx = sqrt_expr_evaluator_pss<mpt_type, mpf_type>(cA, cB).get_d();
                c_event.x(cx / denom);
            }

            if (recompute_lower_x) {
                cA[3] = orientation * (dx * dx + dy * dy) * (temp < 0 ? -1 : 1);
                double lower_x = sqrt_expr_evaluator_pss<mpt_type, mpf_type>(cA, cB).get_d();
                c_event.lower_x(lower_x / denom);
            }
        }

        return true;
    }

    template <typename T>
    static mpt_wrapper<mpz_class, 8> &mpt_cross(T a0, T b0, T a1, T b1) {
        static mpt_wrapper<mpz_class, 8> temp[2];
        temp[0] = a0;
        temp[1] = b0;
        temp[0] = temp[0] * b1;
        temp[1] = temp[1] * a1;
        temp[0] -= temp[1];
        return temp[0];
    }

    // Recompute parameters of the circle event using high-precision library.
    template <typename T>
    static bool create_circle_event_sss_gmpxx(const site_event<T> &site1,
                                              const site_event<T> &site2,
                                              const site_event<T> &site3,
                                              circle_event<T> &c_event,
                                              bool recompute_c_x = true,
                                              bool recompute_c_y = true,
                                              bool recompute_lower_x = true) {
        typedef mpt_wrapper<mpz_class, 8> mpt_type;
        typedef mpt_wrapper<mpf_class, 2> mpf_type;
        static mpt_type a[3], b[3], c[3], sqr_len[4], cross[4];

        a[0] = site1.x1(true) - site1.x0(true);
        a[1] = site2.x1(true) - site2.x0(true);
        a[2] = site3.x1(true) - site3.x0(true);
    
        b[0] = site1.y1(true) - site1.y0(true);
        b[1] = site2.y1(true) - site2.y0(true);
        b[2] = site3.y1(true) - site3.y0(true);

        c[0] = mpt_cross(site1.x0(true), site1.y0(true), site1.x1(true), site1.y1(true));										
        c[1] = mpt_cross(site2.x0(true), site2.y0(true), site2.x1(true), site2.y1(true));
        c[2] = mpt_cross(site3.x0(true), site3.y0(true), site3.x1(true), site3.y1(true));

        for (int i = 0; i < 3; ++i) {
            sqr_len[i] = a[i] * a[i] + b[i] * b[i];
        }

        for (int i = 0; i < 3; ++i) {
            int j = (i+1) % 3;
            int k = (i+2) % 3;
            cross[i] = a[j] * b[k] - a[k] * b[j];
        }
        double denom = sqrt_expr_evaluator<3>::eval<mpt_type, mpf_type>(cross, sqr_len).get_d();

        if (recompute_c_y) {
            for (int i = 0; i < 3; ++i) {
                int j = (i+1) % 3;
                int k = (i+2) % 3;
                cross[i] = b[j] * c[k] - b[k] * c[j];
            }
            double c_y = sqrt_expr_evaluator<3>::eval<mpt_type, mpf_type>(cross, sqr_len).get_d();
            c_event.y(c_y / denom);
        }

        if (recompute_c_x || recompute_lower_x) {
            cross[3] = 0;
            for (int i = 0; i < 3; ++i) {
                int j = (i+1) % 3;
                int k = (i+2) % 3;
                cross[i] = a[j] * c[k] - a[k] * c[j];
                if (recompute_lower_x) {
                    cross[3] += cross[i] * b[i];
                }
            }

            if (recompute_c_x) {
                double c_x = sqrt_expr_evaluator<3>::eval<mpt_type, mpf_type>(cross, sqr_len).get_d();
                c_event.x(c_x / denom);
            }
            
            if (recompute_lower_x) {
                sqr_len[3] = 1;
                double lower_x = sqrt_expr_evaluator<4>::eval<mpt_type, mpf_type>(cross, sqr_len).get_d();
                c_event.lower_x(lower_x / denom);
            }
        }
        
        return true;
    }

    // Find parameters of the inscribed circle that is tangent to three
    // point sites.
    template <typename T>
    static bool create_circle_event_ppp(const site_event<T> &site1,
                                        const site_event<T> &site2,
                                        const site_event<T> &site3,
                                        circle_event<T> &c_event) {
        double dif_x1 = site1.x() - site2.x();
        double dif_x2 = site2.x() - site3.x();
        double dif_y1 = site1.y() - site2.y();
        double dif_y2 = site2.y() - site3.y();
        double orientation = robust_cross_product(dif_x1, dif_y1, dif_x2, dif_y2);
        if (orientation_test(orientation) != RIGHT_ORIENTATION)
            return false;
        //return create_circle_event_ppp_gmpxx(site1, site2, site3, c_event, 1, 1, 1);
        
        robust_fpt<T> inv_orientation(0.5 / orientation, 3.0);
        double sum_x1 = site1.x() + site2.x();
        double sum_x2 = site2.x() + site3.x();
        double sum_y1 = site1.y() + site2.y();
        double sum_y2 = site2.y() + site3.y();
        double dif_x3 = site1.x() - site3.x();
        double dif_y3 = site1.y() - site3.y();
        epsilon_robust_comparator< robust_fpt<T> > c_x, c_y;
        c_x += robust_fpt<T>(dif_x1 * sum_x1 * dif_y2, 2.0);
        c_x += robust_fpt<T>(dif_y1 * sum_y1 * dif_y2, 2.0);
        c_x -= robust_fpt<T>(dif_x2 * sum_x2 * dif_y1, 2.0);
        c_x -= robust_fpt<T>(dif_y2 * sum_y2 * dif_y1, 2.0);
        c_y += robust_fpt<T>(dif_x2 * sum_x2 * dif_x1, 2.0);
        c_y += robust_fpt<T>(dif_y2 * sum_y2 * dif_x1, 2.0);
        c_y -= robust_fpt<T>(dif_x1 * sum_x1 * dif_x2, 2.0);
        c_y -= robust_fpt<T>(dif_y1 * sum_y1 * dif_x2, 2.0);
        epsilon_robust_comparator< robust_fpt<T> > lower_x(c_x);
        lower_x -= robust_fpt<T>(std::sqrt(sqr_distance(dif_x1, dif_y1) *
                                           sqr_distance(dif_x2, dif_y2) *
                                           sqr_distance(dif_x3, dif_y3)), 5.0);
        c_event = circle_event<double>(c_x.dif().fpv() * inv_orientation.fpv(),
                                       c_y.dif().fpv() * inv_orientation.fpv(),
                                       lower_x.dif().fpv() * inv_orientation.fpv());
        bool recompute_c_x = c_x.dif().ulp() >= 128;
        bool recompute_c_y = c_y.dif().ulp() >= 128;
        bool recompute_lower_x = lower_x.dif().ulp() >= 128;
        if (recompute_c_x || recompute_c_y || recompute_lower_x) {
            return create_circle_event_ppp_gmpxx(
                site1, site2, site3, c_event, recompute_c_x, recompute_c_y, recompute_lower_x);
        }
        return true;
    }

    // Find parameters of the inscribed circle that is tangent to two
    // point sites and on segment site.
    template <typename T>
    static bool create_circle_event_pps(const site_event<T> &site1,
                                        const site_event<T> &site2,
                                        const site_event<T> &site3,
                                        int segment_index,
                                        circle_event<T> &c_event) {
        if (segment_index != 2) {
            kOrientation orient1 = orientation_test(site1.point0(),
                site2.point0(), site3.point0(true));
            kOrientation orient2 = orientation_test(site1.point0(),
                site2.point0(), site3.point1(true));
            if (segment_index == 1 && site1.x0() >= site2.x0()) {
                if (orient1 != RIGHT_ORIENTATION)
                    return false;
            } else if (segment_index == 3 && site2.x0() >= site1.x0()) {
                if (orient2 != RIGHT_ORIENTATION)
                    return false;
            } else if (orient1 != RIGHT_ORIENTATION && orient2 != RIGHT_ORIENTATION) {
                return false;
            }
        } else {
            if (site3.point0(true) == site1.point0() &&
                site3.point1(true) == site2.point0())
                return false;
        }
        //return create_circle_event_pps_gmpxx(site1, site2, site3, segment_index, c_event, 1, 1, 1);

        double line_a = site3.point1(true).y() - site3.point0(true).y();
        double line_b = site3.point0(true).x() - site3.point1(true).x();
        double vec_x = site2.y() - site1.y();
        double vec_y = site1.x() - site2.x();
        robust_fpt<T> teta(robust_cross_product(line_a, line_b, -vec_y, vec_x), 2.0);
        robust_fpt<T> A(robust_cross_product(line_a, line_b,
                                             site3.point1().y() - site1.y(),
                                             site1.x() - site3.point1().x()), 2.0);
        robust_fpt<T> B(robust_cross_product(line_a, line_b,
                                             site3.point1().y() - site2.y(),
                                             site2.x() - site3.point1().x()), 2.0);
        robust_fpt<T> denom(robust_cross_product(vec_x, vec_y, line_a, line_b), 2.0);
        robust_fpt<T> inv_segm_len(1.0 / std::sqrt(sqr_distance(line_a, line_b)), 3.0);
        epsilon_robust_comparator< robust_fpt<T> > t;
        if (orientation_test(denom) == COLLINEAR) {
            t += teta / (robust_fpt<T>(8.0) * A);
            t -= A / (robust_fpt<T>(2.0) * teta);
        } else {
            robust_fpt<T> det = ((teta * teta + denom * denom) * A * B).get_sqrt();
            if (segment_index == 2) {
                t -= det / (denom * denom);
            } else {
                t += det / (denom * denom);
            }
            t += teta * (A + B) / (robust_fpt<T>(2.0) * denom * denom);
        }
        epsilon_robust_comparator< robust_fpt<T> > c_x, c_y;
        c_x += robust_fpt<T>(0.5 * (site1.x() + site2.x()));
        c_x += robust_fpt<T>(vec_x) * t;
        c_y += robust_fpt<T>(0.5 * (site1.y() + site2.y()));
        c_y += robust_fpt<T>(vec_y) * t;
        epsilon_robust_comparator< robust_fpt<T> > r, lower_x(c_x);
        r -= robust_fpt<T>(line_a) * robust_fpt<T>(site3.x0());
        r -= robust_fpt<T>(line_b) * robust_fpt<T>(site3.y0());
        r += robust_fpt<T>(line_a) * c_x;
        r += robust_fpt<T>(line_b) * c_y;
        r.abs();
        lower_x += r * inv_segm_len;
        c_event = circle_event<double>(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
        bool recompute_c_x = c_x.dif().ulp() >= 128;
        bool recompute_c_y = c_y.dif().ulp() >= 128;
        bool recompute_lower_x = lower_x.dif().ulp() >= 128;
        if (recompute_c_x || recompute_c_y || recompute_lower_x) {
            return create_circle_event_pps_gmpxx(
                site1, site2, site3, segment_index, c_event,
                recompute_c_x, recompute_c_y, recompute_lower_x);
        }
        return true;
    }

    // Find parameters of the inscribed circle that is tangent to one
    // point site and two segment sites.
    template <typename T>
    static bool create_circle_event_pss(const site_event<T> &site1,
                                        const site_event<T> &site2,
                                        const site_event<T> &site3,
                                        int point_index,
                                        circle_event<T> &c_event) {
        if (site2.index() == site3.index()) {
            return false;
        }

        const point_2d<T> &segm_start1 = site2.point1(true);
        const point_2d<T> &segm_end1 = site2.point0(true);
        const point_2d<T> &segm_start2 = site3.point0(true);
        const point_2d<T> &segm_end2 = site3.point1(true);

        if (point_index == 2) {
            if (!site2.is_inverse() && site3.is_inverse())
                return false;
            if (site2.is_inverse() == site3.is_inverse() &&
                orientation_test(segm_end1, site1.point0(), segm_end2) != RIGHT_ORIENTATION)
                return false;
        }
        //create_circle_event_pss_gmpxx(site1, site2, site3, point_index, c_event, true, true, true);

        double a1 = segm_end1.x() - segm_start1.x();
        double b1 = segm_end1.y() - segm_start1.y();
        double a2 = segm_end2.x() - segm_start2.x();
        double b2 = segm_end2.y() - segm_start2.y();
        bool recompute_c_x, recompute_c_y, recompute_lower_x;
        robust_fpt<T> orientation(robust_cross_product(b1, a1, b2, a2), 2.0);
        if (orientation_test(orientation) == COLLINEAR) {
            robust_fpt<T> a(a1 * a1 + b1 * b1, 2.0);
            robust_fpt<T> c(robust_cross_product(b1, a1, segm_start2.y() - segm_start1.y(),
                                                 segm_start2.x() - segm_start1.x()), 2.0);
            robust_fpt<T> det(robust_cross_product(a1, b1, site1.x() - segm_start1.x(),
                                                   site1.y() - segm_start1.y()) *
                              robust_cross_product(b1, a1, site1.y() - segm_start2.y(),
                                                   site1.x() - segm_start2.x()), 5.0);
            epsilon_robust_comparator< robust_fpt<T> > t;
            t -= robust_fpt<T>(a1) * robust_fpt<T>((segm_start1.x() + segm_start2.x()) * 0.5 - site1.x());
            t -= robust_fpt<T>(b1) * robust_fpt<T>((segm_start1.y() + segm_start2.y()) * 0.5 - site1.y());
            if (point_index == 2) {
                t += det.get_sqrt();
            } else {
                t -= det.get_sqrt();
            }
            t /= a;
            epsilon_robust_comparator< robust_fpt<T> > c_x, c_y;
            c_x += robust_fpt<T>(0.5 * (segm_start1.x() + segm_start2.x()));
            c_x += robust_fpt<T>(a1) * t;
            c_y += robust_fpt<T>(0.5 * (segm_start1.y() + segm_start2.y()));
            c_y += robust_fpt<T>(b1) * t;
            epsilon_robust_comparator< robust_fpt<T> > lower_x(c_x);
            lower_x += robust_fpt<T>(0.5) * c.fabs() / a.get_sqrt();
            recompute_c_x = c_x.dif().ulp() > 128;
            recompute_c_y = c_y.dif().ulp() > 128;
            recompute_lower_x = lower_x.dif().ulp() > 128;
            c_event = circle_event<double>(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
        } else {
            robust_fpt<T> sqr_sum1(std::sqrt(a1 * a1 + b1 * b1), 2.0);
            robust_fpt<T> sqr_sum2(std::sqrt(a2 * a2 + b2 * b2), 2.0);
            robust_fpt<T> a(robust_cross_product(a1, b1, -b2, a2), 2.0);
            if (a >= 0) {
                a += sqr_sum1 * sqr_sum2;
            } else {
                a = (orientation * orientation) / (sqr_sum1 * sqr_sum2 - a);
            }
            robust_fpt<T> or1(robust_cross_product(b1, a1, segm_end1.y() - site1.y(),
                                                   segm_end1.x() - site1.x()), 2.0);
            robust_fpt<T> or2(robust_cross_product(a2, b2, segm_end2.x() - site1.x(),
                                                   segm_end2.y() - site1.y()), 2.0);
            robust_fpt<T> det = robust_fpt<T>(2.0) * a * or1 * or2;
            robust_fpt<T> c1(robust_cross_product(b1, a1, segm_end1.y(), segm_end1.x()), 2.0);
            robust_fpt<T> c2(robust_cross_product(a2, b2, segm_end2.x(), segm_end2.y()), 2.0);
            robust_fpt<T> inv_orientation = robust_fpt<T>(1.0) / orientation;
            epsilon_robust_comparator< robust_fpt<T> > t, b, ix, iy;
            ix += robust_fpt<T>(a2) * c1 * inv_orientation;
            ix += robust_fpt<T>(a1) * c2 * inv_orientation;
            iy += robust_fpt<T>(b1) * c2 * inv_orientation;
            iy += robust_fpt<T>(b2) * c1 * inv_orientation;

            b += ix * (robust_fpt<T>(a1) * sqr_sum2);
            b += ix * (robust_fpt<T>(a2) * sqr_sum1);
            b += iy * (robust_fpt<T>(b1) * sqr_sum2);
            b += iy * (robust_fpt<T>(b2) * sqr_sum1);
            b -= sqr_sum1 * robust_fpt<T>(robust_cross_product(a2, b2, -site1.y(), site1.x()), 2.0);
            b -= sqr_sum2 * robust_fpt<T>(robust_cross_product(a1, b1, -site1.y(), site1.x()), 2.0);
            t -= b;
            if (point_index == 2) {
                t += det.get_sqrt();
            } else {
                t -= det.get_sqrt();
            }
            t /= (a * a);
            epsilon_robust_comparator< robust_fpt<T> > c_x(ix), c_y(iy);
            c_x += t * (robust_fpt<T>(a1) * sqr_sum2);
            c_x += t * (robust_fpt<T>(a2) * sqr_sum1);
            c_y += t * (robust_fpt<T>(b1) * sqr_sum2);
            c_y += t * (robust_fpt<T>(b2) * sqr_sum1);
            t.abs();
            epsilon_robust_comparator< robust_fpt<T> > lower_x(c_x);
            lower_x += t * orientation.fabs();
            recompute_c_x = c_x.dif().ulp() > 128;
            recompute_c_y = c_y.dif().ulp() > 128;
            recompute_lower_x = lower_x.dif().ulp() > 128;
            c_event = circle_event<double>(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
        }
        if (recompute_c_x || recompute_c_y || recompute_lower_x) {
            return create_circle_event_pss_gmpxx(
                site1, site2, site3, point_index, c_event,
                recompute_c_x, recompute_c_y, recompute_lower_x);
        }
        return true;
    }

    // Find parameters of the inscribed circle that is tangent to three
    // segment sites.
    template <typename T>
    static bool create_circle_event_sss(const site_event<T> &site1,
                                        const site_event<T> &site2,
                                        const site_event<T> &site3,
                                        circle_event<T> &c_event) {
        if (site1.index() == site2.index() ||
            site2.index() == site3.index())
            return false;
        //return create_circle_event_sss_gmpxx(site1, site2, site3, c_event, 1, 1, 1);
        
        robust_fpt<T> a1(site1.x1(true) - site1.x0(true), 0.0);
        robust_fpt<T> b1(site1.y1(true) - site1.y0(true), 0.0);
        robust_fpt<T> c1(robust_cross_product(site1.x0(true), site1.y0(true), site1.x1(true), site1.y1(true)), 2.0);
        
        robust_fpt<T> a2(site2.x1(true) - site2.x0(true), 0.0);
        robust_fpt<T> b2(site2.y1(true) - site2.y0(true), 0.0);
        robust_fpt<T> c2(robust_cross_product(site2.x0(true), site2.y0(true), site2.x1(true), site2.y1(true)), 2.0);
        
        robust_fpt<T> a3(site3.x1(true) - site3.x0(true), 0.0);
        robust_fpt<T> b3(site3.y1(true) - site3.y0(true), 0.0);
        robust_fpt<T> c3(robust_cross_product(site3.x0(true), site3.y0(true), site3.x1(true), site3.y1(true)), 2.0);
        
        robust_fpt<T> len1 = (a1 * a1 + b1 * b1).get_sqrt();
        robust_fpt<T> len2 = (a2 * a2 + b2 * b2).get_sqrt();
        robust_fpt<T> len3 = (a3 * a3 + b3 * b3).get_sqrt();
        robust_fpt<T> cross_12(robust_cross_product(a1.fpv(), b1.fpv(), a2.fpv(), b2.fpv()), 2.0);
        robust_fpt<T> cross_23(robust_cross_product(a2.fpv(), b2.fpv(), a3.fpv(), b3.fpv()), 2.0);
        robust_fpt<T> cross_31(robust_cross_product(a3.fpv(), b3.fpv(), a1.fpv(), b1.fpv()), 2.0);
        epsilon_robust_comparator< robust_fpt<T> > denom, c_x, c_y, r;

        // denom = cross_12 * len3 + cross_23 * len1 + cross_31 * len2.
        denom += cross_12 * len3;
        denom += cross_23 * len1;
        denom += cross_31 * len2;

        // denom * r = (b2 * c_x - a2 * c_y - c2 * denom) / len2.
        r -= cross_12 * c3;
        r -= cross_23 * c1;
        r -= cross_31 * c2;

        c_x += a1 * c2 * len3;
        c_x -= a2 * c1 * len3;
        c_x += a2 * c3 * len1;
        c_x -= a3 * c2 * len1;
        c_x += a3 * c1 * len2;
        c_x -= a1 * c3 * len2;
        c_y += b1 * c2 * len3;
        c_y -= b2 * c1 * len3;
        c_y += b2 * c3 * len1;
        c_y -= b3 * c2 * len1;
        c_y += b3 * c1 * len2;
        c_y -= b1 * c3 * len2;
        epsilon_robust_comparator< robust_fpt<T> > lower_x(c_x + r);
        bool recompute_c_x = c_x.dif().ulp() > 128;
        bool recompute_c_y = c_y.dif().ulp() > 128;
        bool recompute_lower_x = lower_x.dif().ulp() > 128;
        bool recompute_denom = denom.dif().ulp() > 128;
        c_event = circle_event<double>(c_x.dif().fpv() / denom.dif().fpv(),
                                       c_y.dif().fpv() / denom.dif().fpv(),
                                       lower_x.dif().fpv() / denom.dif().fpv());
        if (recompute_c_x || recompute_c_y || recompute_lower_x || recompute_denom) {
            return create_circle_event_sss_gmpxx(
                site1, site2, site3, c_event,
                recompute_c_x, recompute_c_y, recompute_lower_x);
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////
    // VORONOI BEACH LINE DATA TYPES //////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // Represents a bisector node made by two arcs that correspond to the left
    // and right sites. Arc is defined as a curve with points equidistant from
    // the site and from the sweepline. If the site is a point then the arc is
    // a parabola, otherwise it's a line segment. A segment site event will
    // produce different bisectors depending on its direction.
    // In the general case two sites will create two opposite bisectors. That's
    // why the order of the sites is important to define the unique bisector.
    // The one site is considered to be newer than the other in case it was
    // processed by the algorithm later.
    template <typename T>
    class beach_line_node {
    public:
        typedef T coordinate_type;
        typedef point_2d<T> point_type;
        typedef site_event<T> site_event_type;

        beach_line_node() {}

        // Constructs degenerate bisector, used to search an arc that is above
        // the given site. The input to the constructor is the new site point.
        explicit beach_line_node(const site_event_type &new_site) {
            left_site_ = new_site;
            right_site_ = new_site;
        }

        // Constructs a new bisector. The input to the constructor is the two
        // sites that create the bisector. The order of sites is important.
        beach_line_node(const site_event_type &left_site,
                        const site_event_type &right_site) {
            left_site_ = left_site;
            right_site_ = right_site;
        }

        const site_event_type &left_site() const {
            return left_site_;
        }

        const site_event_type &right_site() const {
            return right_site_;
        }

        void left_site(const site_event_type &site) {
            left_site_ = site;
        }

        void right_site(const site_event_type &site) {
            right_site_ = site;
        }

        void inverse_left_site() {
            left_site_.inverse();
        }

        void inverse_right_site() {
            right_site_.inverse();
        }

        // Get the x coordinate of the newer site.
        coordinate_type comparison_x() const {
            return (left_site_.index() >= right_site_.index()) ?
                   left_site_.x() : right_site_.x();
        }

        // Get comparison pair: y coordinate and direction of the newer site.
        std::pair<coordinate_type, int> comparison_y(bool is_new_node = true) const {
            if (left_site_.index() == right_site_.index()) {
                return std::make_pair(left_site_.y(), 0);
            }
            if (left_site_.index() > right_site_.index()) {
                if (!is_new_node && left_site_.is_segment() && left_site_.is_vertical()) {
                    return std::make_pair(left_site_.y1(), 1);
                }
                return std::make_pair(left_site_.y(), 1);
            }
            return std::make_pair(right_site_.y(), -1);
        }

        // Get the index of the newer site.
        int comparison_index() const {
            return (left_site_.index() > right_site_.index()) ?
                    left_site_.index() : right_site_.index();
        }

        // Get the newer site.
        const site_event_type &comparison_site() const {
            return (left_site_.index() >= right_site_.index()) ?
                   left_site_ : right_site_;
        }

        // Return true if the horizontal line going through the new site
        // intersects the arc corresponding to the right_site before the
        // arc corresponding to the left_site.
        bool less(const point_type &new_site) const {
            if (!left_site_.is_segment()) {
                return (!right_site_.is_segment()) ? less_pp(new_site) : less_ps(new_site);
            } else {
                return (!right_site_.is_segment()) ? less_sp(new_site) : less_ss(new_site);
            }
        }

    private:
        bool less_pp(const point_type &new_site) const {
            return less_predicate(left_site_.point0(), right_site_.point0(), new_site);
        }

        bool less_ps(const point_type &new_site) const {
            return less_predicate(left_site_.point0(), right_site_, new_site, false);
        }

        bool less_sp(const point_type &new_site) const {
            return less_predicate(right_site_.point0(), left_site_, new_site, true);
        }

        bool less_ss(const point_type &new_site) const {
            return less_predicate(left_site_, right_site_, new_site);
        }

        site_event_type left_site_;
        site_event_type right_site_;
    };

    // Represents edge data sturcture from the voronoi output, that is
    // associated as a value with beach line bisector as a key in the beach
    // line. Contains iterator to the circle event in the circle event
    // queue in case it's the second bisector that forms a circle event.
    template <typename T>
    class beach_line_node_data {
    public:
        explicit beach_line_node_data(voronoi_edge<T> *new_edge) :
            edge_(new_edge),
            contains_circle_event_(false) {}

        void activate_circle_event(typename circle_events_queue<T>::circle_event_type_it it) {
            circle_event_it_ = it;
            contains_circle_event_ = true;
        }

        void deactivate_circle_event() {
            if (contains_circle_event_)
                circle_event_it_->deactivate();
            contains_circle_event_ = false;
        }

        voronoi_edge<T> *edge() const {
            return edge_;
        }

        void edge(voronoi_edge<T> *new_edge) {
            edge_ = new_edge;
        }

    private:
        typename circle_events_queue<T>::circle_event_type_it circle_event_it_;
        voronoi_edge<T> *edge_;
        bool contains_circle_event_;
    };

    // Beach line comparison functor.
    template <typename BeachLineNode>
    struct node_comparer {
    public:
        typedef typename BeachLineNode::coordinate_type coordinate_type;

        // Compares nodes in the balanced binary search tree. Nodes are
        // compared based on the y coordinates of the arcs intersection points.
        // Nodes with less y coordinate of the intersection point go first.
        // Comparison is only called during the new site events processing.
        // That's why one of the nodes will always lie on the sweepline and may
        // be represented as a straight horizontal line.
        bool operator() (const BeachLineNode &node1,
                         const BeachLineNode &node2) const {
            // Get x coordinate of the righmost site from both nodes.
            coordinate_type node1_x = node1.comparison_x();
            coordinate_type node2_x = node2.comparison_x();

            if (node1_x < node2_x) {
                // The second node contains a new site.
                return node1.less(node2.comparison_site().point0());
            } else if (node1_x > node2_x) {
                // The first node contains a new site.
                return !node2.less(node1.comparison_site().point0());
            } else {
                // This checks were evaluated experimentally.
                if (node1.comparison_index() == node2.comparison_index()) {
                    // Both nodes are new (inserted during the same site event
                    // processing).
                    return node1.comparison_y() < node2.comparison_y();
                } else if (node1.comparison_index() < node2.comparison_index()) {
                    std::pair<coordinate_type, int> y1 = node1.comparison_y(false);
                    std::pair<coordinate_type, int> y2 = node2.comparison_y();
                    if (y1.first != y2.first) {
                        return y1.first < y2.first;
                    }
                    return (!node1.comparison_site().is_segment()) ? (y1.second < 0) : false;
                } else {
                    std::pair<coordinate_type, int> y1 = node1.comparison_y();
                    std::pair<coordinate_type, int> y2 = node2.comparison_y(false);
                    if (y1.first != y2.first) {
                        return y1.first < y2.first;
                    }
                    return (!node2.comparison_site().is_segment()) ? (y2.second > 0) : true;
                }
            }
        }
    };

} // detail
} // sweepline
} // boost

#endif
