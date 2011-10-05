// Boost polygon/voronoi_builder.hpp header file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI_BUILDER
#define BOOST_POLYGON_VORONOI_BUILDER

#include <algorithm>
#include <cmath>
#include <cstring>
#include <list>
#include <map>
#include <queue>
#include <vector>

#pragma warning(disable:4800)
#include <gmpxx.h>

#include "polygon.hpp"

#include "detail/mpt_wrapper.hpp"
#include "detail/voronoi_calc_kernel.hpp"
#include "detail/voronoi_fpt_kernel.hpp"
#include "detail/voronoi_formation.hpp"

namespace boost {
namespace polygon {

    ///////////////////////////////////////////////////////////////////////////
    // VORONOI TRAITS /////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    
    template <typename T>
    struct voronoi_builder_traits;

    template <>
    struct voronoi_builder_traits<int> {
        typedef detail::voronoi_calc_kernel<int> calc_kernel_type;
        typedef calc_kernel_type::fpt_type coordinate_type;
    };

    ///////////////////////////////////////////////////////////////////////////
    // VORONOI BUILDER ////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // The sweepline algorithm implementation to compute voronoi diagram of
    // input data sets of points and segments (Fortune's algorithm).
    // Complexity - O(N*logN), memory usage - O(N), where N is the total
    // number of input objects.
    // Sweepline is a vertical line that sweeps from the left to the right
    // along the x-axis positive direction. Each of the input objects is
    // wrapped into the site event. Each event is characterized by its
    // coordinates: the point site is defined by the point itself,
    // the segment site is defined by its startpoint. At any moment we
    // consider only the sites that lie to the left of the sweepline. Beach
    // line is a curve formed by the parabolic arcs and line segments, that
    // consists of the points equidistant from the sweepline and the nearest
    // site to the left of the sweepline. The part of the generated diagram to
    // the left of the beach line remains unchanged until the end of the
    // algorithm. Each node in the beach line corresponds to some voronoi edge.
    // Each node is represented by two sites. Two neighboring nodes has a
    // common site. Circle event appears at the rightmost point of the circle
    // tangent to the three sites that correspond to the two consecutive
    // bisectors. At each step algorithm goes over the leftmost event
    // and processes it appropriately. This is made until there are no events.
    // At the end output data structure holds the voronoi diagram of the
    // initial set of objects.
    // Each point creates one site event. Each segment creates three site
    // events: two for its endpoints and one for the segment itself (this is
    // made to simplify output construction). All the site events are
    // constructed at the algorithm initialization step. After that they
    // are ordered using quicksort algorithm.
    // Priority queue is used to dynamically hold circle events. At each step
    // of the algorithm the leftmost event is retrieved by comparing the
    // current site event and the topmost element from the circle event queue.
    // Standard map container was chosen to hold state of the beach line. The
    // keys of the map correspond to the bisectors and values to the
    // corresponding edges from the output data structure. Specially defined
    // comparison functor is used to make the beach line correctly ordered.
    // Epsilon-based and high-precision approaches are used to guarantee
    // efficiency and robustness of the algorithm implementation.
    // Member data: 1) site_events_ - vector of the site events;
    //              2) site_event_iterator_ - iterator to the next
    //                 site event;
    //              3) circle_events_ - priority queue of circle events,
    //                 allows to retrieve topmost event in O(logN) time;
    //              4) beach_line_ - contains current state of the beach line;
    //              5) end_points_ - maps endpoints of the segment sites with
    //                 temporary nodes from the beach line. While sweepline
    //                 sweeps over the second endpoint of the segments
    //                 temporary nodes are being removed;
    //              6) output_ - contains voronoi diagram itself.
    template <typename T, typename VD>
    class voronoi_builder {
    public:
        typedef typename voronoi_builder_traits<T>::coordinate_type coordinate_type;
        typedef VD output_type;

        voronoi_builder() {}

        template <typename PointIterator>
        void insert_points(PointIterator first_point, PointIterator last_point) {
            // Create a site event from each input point.
            for (PointIterator it = first_point; it != last_point; ++it) {
                site_events_.push_back(detail::site_event<coordinate_type>(
                    static_cast<coordinate_type>(it->x()),
                    static_cast<coordinate_type>(it->y()), 0));
            }
        }

        template <typename SegmentIterator>
        void insert_segments(SegmentIterator first_segment, SegmentIterator last_segment) {
            // Each segment creates three segment sites:
            //   1) the startpoint of the segment;
            //   2) the endpoint of the segment;
            //   3) the segment itself.
            for (SegmentIterator it = first_segment; it != last_segment; ++it) {
                coordinate_type x1 = static_cast<coordinate_type>(it->low().x());
                coordinate_type y1 = static_cast<coordinate_type>(it->low().y());
                coordinate_type x2 = static_cast<coordinate_type>(it->high().x());
                coordinate_type y2 = static_cast<coordinate_type>(it->high().y());
                site_events_.push_back(detail::site_event<coordinate_type>(x1, y1, 0));
                site_events_.push_back(detail::site_event<coordinate_type>(x2, y2, 0));
                site_events_.push_back(detail::site_event<coordinate_type>(x1, y1, x2, y2, 0));
            }
        }

        template <typename PointIterator, typename SegmentIterator>
        void insert_sites(PointIterator first_point, PointIterator last_point,
                          SegmentIterator first_segment, SegmentIterator last_segment) {
            insert_points(first_point, last_point);
            insert_segments(first_segment, last_segment);
        }

        // Run the sweepline algorithm.
        void construct(output_type &output) {
            // Init structures.
            output_ = &output;
            output_->clear();
            output_->reserve(site_events_.size());
            init_sites_queue();
            init_beach_line();

            // The algorithm stops when there are no events to process.
            // The circle events with the same rightmost point as the next
            // site event go first.
            event_comparison_predicate event_comparison;
            while (!circle_events_.empty() ||
                   !(site_event_iterator_ == site_events_.end())) {
                if (circle_events_.empty()) {
                    process_site_event();
                } else if (site_event_iterator_ == site_events_.end()) {
                    process_circle_event();
                } else {
                    if (event_comparison(*site_event_iterator_, circle_events_.top().first)) {
                        process_site_event();
                    } else {
                        process_circle_event();
                    }
                }
                while (!circle_events_.empty() && !circle_events_.top().first.is_active()) {
                    circle_events_.pop();
                }
            }

            beach_line_.clear();

            // Clean the output (remove zero-length edges).
            output_->clean();
        }

        void clear() {
            site_events_.clear();
        }

    private:
        typedef voronoi_builder_traits<int>::calc_kernel_type calc_kernel_type;

        typedef detail::point_2d<coordinate_type> point_type;
        typedef detail::site_event<coordinate_type> site_event_type;
        typedef calc_kernel_type::site_comparison_predicate<site_event_type>
            site_comparison_predicate;
        typedef calc_kernel_type::site_equality_predicate<site_event_type>
            site_equality_predicate;
        typedef typename std::vector<site_event_type>::const_iterator
            site_event_iterator_type;
        typedef detail::circle_event<coordinate_type> circle_event_type;
        typedef calc_kernel_type::circle_comparison_predicate<circle_event_type>
            circle_comparison_predicate;
        typedef calc_kernel_type::event_comparison_predicate<site_event_type, circle_event_type>
            event_comparison_predicate;
        typedef calc_kernel_type::circle_formation_predicate<site_event_type, circle_event_type>
            circle_formation_predicate_type;
        typedef detail::beach_line_node_key<site_event_type> key_type;
        typedef detail::beach_line_node_data<circle_event_type> value_type;
        typedef calc_kernel_type::node_comparison_predicate<key_type> node_comparer_type;
        typedef std::map< key_type, value_type, node_comparer_type > beach_line_type;
        typedef typename beach_line_type::iterator beach_line_iterator;
        typedef std::pair<circle_event_type, beach_line_iterator> event_type; 
        typedef struct {
            bool operator()(const event_type &lhs, const event_type &rhs) const {
                return predicate(rhs.first, lhs.first);
            }
            circle_comparison_predicate predicate;
        } event_comparison_type;
        typedef detail::ordered_queue<event_type, event_comparison_type>
            circle_event_queue_type;
        typedef typename output_type::voronoi_edge_type edge_type;
        typedef std::pair<point_type, beach_line_iterator> end_point_type;

        // Create site events.
        // There will be one site event for each input point and three site
        // events for each input segment (both endpoints of a segment and the
        // segment itself).
        void init_sites_queue() {
            // Sort the site events.
            sort(site_events_.begin(), site_events_.end(), site_comparison_predicate());

            // Remove duplicates.
            site_events_.erase(unique(
                site_events_.begin(), site_events_.end(), site_equality_predicate()), site_events_.end());

            // Number the sites.
            for (size_t cur = 0; cur < site_events_.size(); ++cur)
                site_events_[cur].index(cur);

            // Init the site's iterator.
            site_event_iterator_ = site_events_.begin();
        }

        void init_beach_line() {
            if (site_events_.empty()) return;
            if (site_events_.size() == 1) {
                // Handle one input site case.
                output_->process_single_site(site_events_[0]);
                ++site_event_iterator_;
            } else {
                int skip = 0;

                // Count the number of the sites to init the beach line.
                while(site_event_iterator_ != site_events_.end() &&
                      site_event_iterator_->x() == site_events_.begin()->x() &&
                      site_event_iterator_->is_vertical()) {
                    ++site_event_iterator_;
                    ++skip;
                }

                if (skip == 1) {
                    // Init the beach line with the two first sites.
                    init_beach_line_default();
                } else {
                    // Init the beach line with the sites situated on the same
                    // vertical line. This could be a set of point and vertical
                    // segment sites.
                    init_beach_line_collinear_sites();
                }
            }
        }

        // Init the beach line with the two first sites.
        // The first site is always a point.
        void init_beach_line_default() {
            // Get the first and the second site events.
            site_event_iterator_type it_first = site_events_.begin();
            site_event_iterator_type it_second = site_events_.begin();
            ++it_second;

            // Update the beach line.
            insert_new_arc(*it_first, *it_first, *it_second, beach_line_.begin());

            // The second site has been already processed.
            // Move the site's iterator.
            ++site_event_iterator_;
        }

        // Insert bisectors for all collinear initial sites.
        void init_beach_line_collinear_sites() {
             site_event_iterator_type it_first = site_events_.begin();
             site_event_iterator_type it_second = site_events_.begin();
             ++it_second;
             while (it_second != site_event_iterator_) {
                 // Create a new beach line node.
                 key_type new_node(*it_first, *it_second);

                 // Update the output.
                 edge_type *edge = output_->insert_new_edge(*it_first, *it_second);

                 // Insert a new bisector into the beach line.
                 beach_line_.insert(
                     std::pair<key_type, value_type>(new_node, value_type(edge)));

                 // Update iterators.
                 ++it_first;
                 ++it_second;
             }
        }

        // Process a single site.
        void process_site_event() {
            // Get the site event to process.
            site_event_type site_event = *site_event_iterator_;

            // Move the site's iterator.
            site_event_iterator_type last = site_event_iterator_ + 1;

            // If a new site is an end point of some segment,
            // remove temporary nodes from the beach line data structure.
            if (!site_event.is_segment()) {
                while (!end_points_.empty() &&
                       end_points_.top().first == site_event.point0()) {
                    beach_line_iterator b_it = end_points_.top().second;
                    end_points_.pop();
                    beach_line_.erase(b_it);
                }
            } else {
                while (last != site_events_.end() &&
                       last->is_segment() && last->point0() == site_event.point0())
                    last++;
            }

            for (; site_event_iterator_ != last; ++site_event_iterator_) {
                site_event = *site_event_iterator_;
                // Create degenerate node.
                key_type new_key(site_event);

                // Find the node in the binary search tree with left arc
                // lying above the new site point.
                beach_line_iterator it = beach_line_.lower_bound(new_key);
                int it_dist = site_event.is_segment() ? 2 : 1;

                // Do further processing depending on the above node position.
                // For any two neighbouring nodes the second site of the first node
                // is the same as the first site of the second arc.
                if (it == beach_line_.end()) {
                    // The above arc corresponds to the second arc of the last node.
                    // Move the iterator to the last node.
                    --it;

                    // Get the second site of the last node
                    const site_event_type &site_arc = it->first.right_site();

                    // Insert new nodes into the beach line. Update the output.
                    beach_line_iterator new_node_it =
                        insert_new_arc(site_arc, site_arc, site_event, it);

                    // Add a candidate circle to the circle event queue.
                    // There could be only one new circle event formed by
                    // a new bisector and the one on the left.
                    std::advance(new_node_it, -it_dist);
                    activate_circle_event(it->first.left_site(),
                                          it->first.right_site(),
                                          site_event, new_node_it);
                } else if (it == beach_line_.begin()) {
                    // The above arc corresponds to the first site of the first node.
                    const site_event_type &site_arc = it->first.left_site();

                    // Insert new nodes into the beach line. Update the output.
                    insert_new_arc(site_arc, site_arc, site_event, it);

                    // If the site event is a segment, update its direction.
                    if (site_event.is_segment()) {
                        site_event.inverse();
                    }

                    // Add a candidate circle to the circle event queue.
                    // There could be only one new circle event formed by
                    // a new bisector and the one on the right.
                    activate_circle_event(site_event, it->first.left_site(),
                                          it->first.right_site(), it);
                } else {
                    // The above arc corresponds neither to the first,
                    // nor to the last site in the beach line.
                    const site_event_type &site_arc2 = it->first.left_site();
                    const site_event_type &site3 = it->first.right_site();

                    // Remove the candidate circle from the event queue.
                    it->second.deactivate_circle_event();
                    --it;
                    const site_event_type &site_arc1 = it->first.right_site();
                    const site_event_type &site1 = it->first.left_site();

                    // Insert new nodes into the beach line. Update the output.
                    beach_line_iterator new_node_it =
                        insert_new_arc(site_arc1, site_arc2, site_event, it);

                    // Add candidate circles to the circle event queue.
                    // There could be up to two circle events formed by
                    // a new bisector and the one on the left or right.
                    std::advance(new_node_it, -it_dist);
                    activate_circle_event(site1, site_arc1, site_event,
                                          new_node_it);

                    // If the site event is a segment, update its direction.
                    if (site_event.is_segment()) {
                        site_event.inverse();
                    }
                    std::advance(new_node_it, it_dist + 1);
                    activate_circle_event(site_event, site_arc2, site3,
                                          new_node_it);
                }
            }
        }

        // Process a single circle event.
        // In general case circle event is made of the three consequtive sites
        // that form two bisector nodes in the beach line data structure.
        // Let circle event sites be A, B, C, two bisectors that define
        // circle event be (A, B), (B, C). During circle event processing
        // we remove (A, B), (B, C) and insert (A, C). As beach line comparer
        // works correctly only if one of the nodes is a new one we remove
        // (B, C) bisector and change (A, B) bisector to the (A, C). That's
        // why we use const_cast there and take all the responsibility that
        // map data structure keeps correct ordering.
        void process_circle_event() {
            // Get the topmost circle event.
            const event_type &e = circle_events_.top();
            const circle_event_type &circle_event = e.first;
            beach_line_iterator it_first = e.second;
            beach_line_iterator it_last = it_first;

            // Get the C site.
            site_event_type site3 = it_first->first.right_site();

            // Get the half-edge corresponding to the second bisector - (B, C).
            edge_type *bisector2 = static_cast<edge_type *>(it_first->second.edge());

            // Get the half-edge corresponding to the first bisector - (A, B).
            --it_first;
            edge_type *bisector1 = static_cast<edge_type *>(it_first->second.edge());

            // Get the A site.
            site_event_type site1 = it_first->first.left_site();

            if (!site1.is_segment() && site3.is_segment() &&
                site3.point1(true) == site1.point0()) {
                site3.inverse();
            }

            // Change the (A, B) bisector node to the (A, C) bisector node.
            const_cast<key_type &>(it_first->first).right_site(site3);

            // Insert the new bisector into the beach line.
            it_first->second.edge(output_->insert_new_edge(site1, site3, circle_event,
                                                           bisector1, bisector2));

            // Remove the (B, C) bisector node from the beach line.
            beach_line_.erase(it_last);
            it_last = it_first;

            // Pop the topmost circle event from the event queue.
            circle_events_.pop();

            // Check new triplets formed by the neighboring arcs
            // to the left for potential circle events.
            if (it_first != beach_line_.begin()) {
                it_first->second.deactivate_circle_event();
                --it_first;
                const site_event_type &site_l1 = it_first->first.left_site();
                activate_circle_event(site_l1, site1, site3, it_last);
            }

            // Check the new triplet formed by the neighboring arcs
            // to the right for potential circle events.
            ++it_last;
            if (it_last != beach_line_.end()) {
                it_last->second.deactivate_circle_event();
                const site_event_type &site_r1 = it_last->first.right_site();
                activate_circle_event(site1, site3, site_r1, it_last);
            }
        }

        // Insert new nodes into the beach line. Update the output.
        beach_line_iterator insert_new_arc(const site_event_type &site_arc1,
                                           const site_event_type &site_arc2,
                                           const site_event_type &site_event,
                                           const beach_line_iterator &position) {
            // Create two new bisectors with opposite directions.
            key_type new_left_node(site_arc1, site_event);
            key_type new_right_node(site_event, site_arc2);

            // Set correct orientation for the first site of the second node.
            if (site_event.is_segment()) {
                new_right_node.inverse_left_site();
            }

            // Update the output.
            edge_type *edge = output_->insert_new_edge(site_arc2, site_event);

            // Update the beach line with the (site_arc1, site_event) bisector.
            beach_line_iterator it = beach_line_.insert(position,
                typename beach_line_type::value_type(new_right_node, value_type(edge->twin())));

            if (site_event.is_segment()) {
                // Update the beach line with temporary bisector, that will
                // disappear after processing site event going through the
                // endpoint of the segment site.
                key_type new_node(site_event, site_event);
                new_node.inverse_right_site();
                beach_line_iterator temp_it = beach_line_.insert(position,
                    typename beach_line_type::value_type(new_node, value_type(NULL)));

                // Update the data structure that holds temporary bisectors.
                end_points_.push(std::make_pair(site_event.point1(), temp_it));
            }

            // Update the beach line with the (site_event, site_arc2) bisector.
            beach_line_.insert(position,
                typename beach_line_type::value_type(new_left_node, value_type(edge)));
            return it;
        }

        // Add a new circle event to the event queue.
        // bisector_node corresponds to the (site2, site3) bisector.
        void activate_circle_event(const site_event_type &site1,
                                   const site_event_type &site2,
                                   const site_event_type &site3,
                                   beach_line_iterator bisector_node) {
            circle_event_type c_event;
            // Check if the three input sites create a circle event.
            if (circle_formation_predicate_(site1, site2, site3, c_event)) {
                // Add the new circle event to the circle events queue.
                // Update bisector's circle event iterator to point to the
                // new circle event in the circle event queue.
                event_type &e = circle_events_.push(
                    std::pair<circle_event_type, beach_line_iterator>(c_event, bisector_node));
                bisector_node->second.activate_circle_event(&e.first);
            }
        }

    private:
        struct end_point_comparison {
            bool operator() (const end_point_type &end1, const end_point_type &end2) const {
                return end1.first > end2.first;
            }
        };

        std::vector<site_event_type> site_events_;
        site_event_iterator_type site_event_iterator_;
        std::priority_queue< end_point_type, std::vector<end_point_type>,
                             end_point_comparison > end_points_;
        circle_event_queue_type circle_events_;
        beach_line_type beach_line_;
        output_type *output_;
        circle_formation_predicate_type circle_formation_predicate_;

        //Disallow copy constructor and operator=
        voronoi_builder(const voronoi_builder&);
        void operator=(const voronoi_builder&);
    };

} // polygon
} // boost

#endif
