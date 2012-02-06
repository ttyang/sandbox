// Boost.Polygon library voronoi_diagram.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI_DIAGRAM
#define BOOST_POLYGON_VORONOI_DIAGRAM

#include <list>
#include <vector>

#include "detail/voronoi_ctypes.hpp"
#include "detail/voronoi_structures.hpp"

namespace boost {
namespace polygon {

    // Forward declarations.
    template <typename T>
    class voronoi_cell;

    template <typename T>
    class voronoi_edge;

    // Bounding rectangle data structure. Contains coordinates
    // of the bottom left and the upper right points of the rectangle.
    template <typename T>
    class bounding_rectangle {
    public:
        typedef T coordinate_type;

        bounding_rectangle() {}

        bounding_rectangle(T x, T y) {
            x_min_ = x_max_ = x;
            y_min_ = y_max_ = y;
        }

        template <typename P>
        bounding_rectangle(const P &p) {
            x_min_ = x_max_ = p.x();
            y_min_ = y_max_ = p.y();
        }

        bounding_rectangle(T x1, T y1, T x2, T y2) {
            x_min_ = (std::min)(x1, x2);
            y_min_ = (std::min)(y1, y2);
            x_max_ = (std::max)(x1, x2);
            y_max_ = (std::max)(y1, y2);
        }

        template <typename P>
        bounding_rectangle(const P &p1, const P &p2) {
            x_min_ = (std::min)(p1.x(), p2.x());
            y_min_ = (std::min)(p1.y(), p2.y());
            x_max_ = (std::max)(p1.x(), p2.x());
            y_max_ = (std::max)(p1.y(), p2.y());
        }

        void update(T x, T y) {
            x_min_ = (std::min)(x_min_, x);
            y_min_ = (std::min)(y_min_, y);
            x_max_ = (std::max)(x_max_, x);
            y_max_ = (std::max)(y_max_, y);
        }

        // Extend the rectangle with a new point.
        template <typename P>
        void update(const P &p) {
            x_min_ = (std::min)(x_min_, p.x());
            y_min_ = (std::min)(y_min_, p.y());
            x_max_ = (std::max)(x_max_, p.x());
            y_max_ = (std::max)(y_max_, p.y());
        }

        bool contains(T x, T y) const {
            return x >= x_min_ && x <= x_max_ &&
                   y >= y_min_ && y <= y_max_;
        }

        // Check whether a point is situated inside the bounding rectangle.
        template <typename P>
        bool contains(const P &p) const {
            return p.x() >= x_min_ && p.x() <= x_max_ &&
                   p.y() >= y_min_ && p.y() <= y_max_;
        }

        // Return the x-coordinate of the bottom left point of the rectangle.
        coordinate_type x_min() const {
            return x_min_;
        }

        // Return the y-coordinate of the bottom left point of the rectangle.
        coordinate_type y_min() const {
            return y_min_;
        }

        // Return the x-coordinate of the upper right point of the rectangle.
        coordinate_type x_max() const {
            return x_max_;
        }

        // Return the y-coordinate of the upper right point of the rectangle.
        coordinate_type y_max() const {
            return y_max_;
        }

        coordinate_type min_len() const {
            return (std::min)(x_max_ - x_min_, y_max_ - y_min_);
        }

        coordinate_type max_len() const {
            return (std::max)(x_max_ - x_min_, y_max_ - y_min_);
        }

    private:
        coordinate_type x_min_;
        coordinate_type y_min_;
        coordinate_type x_max_;
        coordinate_type y_max_;
    };

    // Represents voronoi cell.
    // Data members: 1) pointer to the incident edge;
    //               2) site inside the cell;
    //               3) number of incident edges.
    // The cell may contain point or segment site.
    template <typename T>
    class voronoi_cell {
    public:
        typedef T coordinate_type;
        typedef detail::point_2d<coordinate_type> point_type;
        typedef voronoi_edge<coordinate_type> voronoi_edge_type;

        voronoi_cell(const point_type &p1, voronoi_edge_type *edge) :
            point0_(p1),
            point1_(p1),
            incident_edge_(edge),
            num_incident_edges_(0) {}

        voronoi_cell(const point_type &p1,
                     const point_type &p2,
                     voronoi_edge_type *edge) :
            point0_(p1),
            point1_(p2),
            incident_edge_(edge),
            num_incident_edges_(0) {}

        // Returns true if the cell contains segment site, false else.
        bool contains_segment() const { return point0_ != point1_; }

        // Returns site point in case cell contains point site,
        // the first point of the segment site else.
        const point_type &point0() const { return point0_; }

        // Returns site point in case cell contains point site,
        // the second point of the segment site else.
        const point_type &point1() const { return point1_; }

        voronoi_edge_type *incident_edge() { return incident_edge_; }
        const voronoi_edge_type *incident_edge() const {
            return incident_edge_;
        }
        void incident_edge(voronoi_edge_type *e) { incident_edge_ = e; }

        int num_incident_edges() const { return num_incident_edges_; }
        void inc_num_incident_edges() { ++num_incident_edges_; }
        void dec_num_incident_edges() { --num_incident_edges_; }

    private:
        point_type point0_;
        point_type point1_;
        voronoi_edge_type *incident_edge_;
        int num_incident_edges_;
    };

    // Represents voronoi vertex.
    // Data members: 1) vertex point itself;
    //               2) pointer to the incident edge;
    //               3) number of incident edges.
    template <typename T>
    class voronoi_vertex {
    public:
        typedef T coordinate_type;
        typedef detail::point_2d<T> point_type;
        typedef voronoi_edge<coordinate_type> voronoi_edge_type;

        voronoi_vertex(const point_type &vertex,
                       voronoi_edge_type *edge) :
            vertex_(vertex),
            incident_edge_(edge),
            num_incident_edges_(3) {}

        const point_type &vertex() const { return vertex_; }

        voronoi_edge_type *incident_edge() { return incident_edge_; }
        const voronoi_edge_type *incident_edge() const {
            return incident_edge_;
        }
        void incident_edge(voronoi_edge_type *e) { incident_edge_ = e; }

        int num_incident_edges() const { return num_incident_edges_; }
        void num_incident_edges(int n) { num_incident_edges_ = n; }

    private:
        point_type vertex_;
        voronoi_edge_type *incident_edge_;
        int num_incident_edges_;
    };

    // Half-edge data structure. Represents voronoi edge.
    // Variables: 1) pointer to the corresponding cell;
    //            2) pointer to the vertex that is the starting
    //               point of the half-edge;
    //            3) pointer to the twin edge;
    //            4) pointer to the CCW/CW next edge.
    //            5) pointer to the CCW/CW prev edge.
    template <typename T>
    class voronoi_edge {
    public:
        typedef T coordinate_type;
        typedef voronoi_cell<coordinate_type> voronoi_cell_type;
        typedef voronoi_vertex<coordinate_type> voronoi_vertex_type;
        typedef voronoi_edge<coordinate_type> voronoi_edge_type;

        voronoi_edge() :
            cell_(NULL),
            vertex_(NULL),
            twin_(NULL),
            next_(NULL),
            prev_(NULL) {}

        voronoi_cell_type *cell() { return cell_; }
        const voronoi_cell_type *cell() const { return cell_; }
        void cell(voronoi_cell_type *c) { cell_ = c; }

        voronoi_vertex_type *vertex0() { return vertex_; }
        const voronoi_vertex_type *vertex0() const { return vertex_; }
        void vertex0(voronoi_vertex_type *v) { vertex_ = v; }

        voronoi_vertex_type *vertex1() { return twin_->vertex0(); }
        const voronoi_vertex_type *vertex1() const { return twin_->vertex0(); }
        void vertex1(voronoi_vertex_type *v) { twin_->vertex0(v); }

        voronoi_edge_type *twin() { return twin_; }
        const voronoi_edge_type *twin() const { return twin_; }
        void twin(voronoi_edge_type *e) { twin_ = e; }

        voronoi_edge_type *next() { return next_; }
        const voronoi_edge_type *next() const { return next_; }
        void next(voronoi_edge_type *e) { next_ = e; }

        voronoi_edge_type *prev() { return prev_; }
        const voronoi_edge_type *prev() const { return prev_; }
        void prev(voronoi_edge_type *e) { prev_ = e; }

        // Return a pointer to the rotation next edge
        // over the starting point of the half-edge.
        voronoi_edge_type *rot_next() {
            return (vertex_) ? prev_->twin() : NULL;
        }
        const voronoi_edge_type *rot_next() const {
            return (vertex_) ? prev_->twin() : NULL;
        }

        // Return a pointer to the rotation prev edge
        // over the starting point of the half-edge.
        voronoi_edge_type *rot_prev() {
            return (vertex_) ? twin_->next() : NULL;
        }
        const voronoi_edge_type *rot_prev() const {
            return (vertex_) ? twin_->next() : NULL;
        }

        // Return true if the edge is finite (segment, parabolic arc).
        // Return false if the edge is infinite (ray, line).
        bool is_bounded() const { return vertex0() && vertex1(); }

        // Return true if the edge is linear.
        // Return false if the edge is curved (parabolic arc).
        bool is_linear() const {
            return !(cell()->contains_segment() ^
                     twin()->cell()->contains_segment());
        }

        // Returns true if the edge is curved (parabolic arc).
        // Returns false if the edge is linear.
        bool is_curved() const {
            return (cell()->contains_segment() ^
                    twin()->cell()->contains_segment());
        }

        // Return false if edge goes through the endpoint of the segment.
        // Return true else.
        bool is_primary() const {
            voronoi_cell_type *cell1 = cell_;
            voronoi_cell_type *cell2 = twin_->cell();
            if (cell1->contains_segment() && !cell2->contains_segment()) {
                if (cell1->point0() == cell2->point0() ||
                    cell1->point1() == cell2->point0())
                    return false;
            }
            if (cell2->contains_segment() && !cell1->contains_segment()) {
                if (cell2->point0() == cell1->point0() ||
                    cell2->point1() == cell1->point0())
                    return false;
            }
            return true;
        }

    private:
        voronoi_cell_type *cell_;
        voronoi_vertex_type *vertex_;
        voronoi_edge_type *twin_;
        voronoi_edge_type *next_;
        voronoi_edge_type *prev_;
    };

    template <typename T>
    struct voronoi_diagram_traits {
        typedef T coordinate_type;
        typedef struct {
            template <typename CT>
            coordinate_type operator()(const CT& value) {
                return static_cast<coordinate_type>(value);
            }
        } ctype_converter_type;
        typedef detail::point_2d<coordinate_type> point_type;
        typedef bounding_rectangle<coordinate_type> bounding_rectangle_type;
        typedef voronoi_cell<coordinate_type> voronoi_cell_type;
        typedef voronoi_vertex<coordinate_type> voronoi_vertex_type;
        typedef voronoi_edge<coordinate_type> voronoi_edge_type;
        typedef class {
        public:
            enum { ULPS = 128 };
            bool operator()(const point_type &v1,
                            const point_type &v2) const {
                return (ulp_cmp(v1.x(), v2.x(), ULPS) ==
                        detail::ulp_comparison<T>::EQUAL) &&
                       (ulp_cmp(v1.y(), v2.y(), ULPS) ==
                        detail::ulp_comparison<T>::EQUAL);
            }
        private:
            typename detail::ulp_comparison<T> ulp_cmp;
        } vertex_equality_predicate_type;
    };

    // Voronoi output data structure.
    // Data members:
    //   1) cell_records_ - vector of the voronoi cells;
    //   2) vertex_records_ - list of the voronoi vertices;
    //   3) edge_records_ - list of the voronoi edges;
    //   4) voronoi_rect_ - bounding rectangle;
    //   5) num_cell_records_ - number of the voronoi cells;
    //   6) num_vertex_records_ - number of the voronoi vertices;
    //   7) num_edge_records_ - number of the voronoi edges.
    // CCW ordering is used on the faces perimeter and around the vertices.
    // Robust vertices are used to make the simplification stage epsilon
    // robust. Vector data structure is used to store voronoi cells as the
    // number of the cells may be precomputed at the initialization step.
    // As size() method takes O(n) time on the list data structure three
    // additional counters are used to count the number of the voronoi cells,
    // vertices and edges. As we use list data structure to represent voronoi
    // vertices and edges there is no copy method available, because it will
    // invalidate all the pointers. Another approach could be used to make
    // copying available:
    //     1) use vectors to store voronoi vertices and cells;
    //     2) store vector indices instead of the pointers;
    //     3) store additional pointer to the voronoi output data structure
    //        in the voronoi cell, vertex, edge data structure.
    //     4) implement simplification via copying not degenerate elements
    //        to the new vector as removing elements from a vector takes O(n)
    //        time.
    template <typename T, typename TRAITS = voronoi_diagram_traits<T> >
    class voronoi_diagram {
    public:
        typedef typename TRAITS::coordinate_type coordinate_type;
        typedef typename TRAITS::ctype_converter_type ctype_converter_type;
        typedef typename TRAITS::point_type point_type;
        typedef typename TRAITS::bounding_rectangle_type
            bounding_rectangle_type;
        typedef typename TRAITS::voronoi_cell_type voronoi_cell_type;
        typedef typename TRAITS::voronoi_vertex_type voronoi_vertex_type;
        typedef typename TRAITS::voronoi_edge_type voronoi_edge_type;
        typedef typename TRAITS::vertex_equality_predicate_type
            vertex_equality_predicate_type;

        typedef std::vector<voronoi_cell_type> voronoi_cells_type;
        typedef typename voronoi_cells_type::iterator
            voronoi_cell_iterator_type;
        typedef typename voronoi_cells_type::const_iterator
            voronoi_cell_const_iterator_type;

        typedef std::list<voronoi_vertex_type> voronoi_vertices_type;
        typedef typename voronoi_vertices_type::iterator
            voronoi_vertex_iterator_type;
        typedef typename voronoi_vertices_type::const_iterator
            voronoi_vertex_const_iterator_type;

        typedef std::list<voronoi_edge_type> voronoi_edges_type;
        typedef typename voronoi_edges_type::iterator
            voronoi_edge_iterator_type;
        typedef typename voronoi_edges_type::const_iterator
            voronoi_edge_const_iterator_type;

        voronoi_diagram() :
            num_cell_records_(0),
            num_edge_records_(0),
            num_vertex_records_(0) {}

        void clear() {
            voronoi_cells_type().swap(cell_records_);
            vertex_records_.clear();
            edge_records_.clear();

            num_cell_records_ = 0;
            num_edge_records_ = 0;
            num_vertex_records_ = 0;
        }

        const bounding_rectangle_type &bounding_rectangle() const {
            return voronoi_rect_;
        }

        const voronoi_cells_type &cell_records() const {
            return cell_records_;
        }

        const voronoi_vertices_type &vertex_records() const {
            return vertex_records_;
        }

        const voronoi_edges_type &edge_records() const {
            return edge_records_;
        }

        int num_cell_records() const {
            return num_cell_records_;
        }

        int num_edge_records() const {
            return num_edge_records_;
        }

        int num_vertex_records() const {
            return num_vertex_records_;
        }

        void reserve(int num_sites) {
            // Resize cell vector to avoid reallocations.
            cell_records_.reserve(num_sites);

            // Init counters.
            num_cell_records_ = 0;
            num_edge_records_ = 0;
            num_vertex_records_ = 0;
        }

        // Update the voronoi output in case of a single point input.
        template <typename SEvent>
        void process_single_site(const SEvent &site) {
            // Update bounding rectangle.
            point_type p = prepare_point(site.point0());
            voronoi_rect_ = bounding_rectangle_type(p);

            // Update cell records.
            cell_records_.push_back(voronoi_cell_type(p, NULL));
        }

        // Insert a new half-edge into the output data structure.
        // Takes as input left and right sites that form a new bisector.
        // Returns a pointer to a new half-edge.
        template <typename SEvent>
        std::pair<void*, void*> insert_new_edge(const SEvent &site1,
                                                const SEvent &site2) {
            // Get sites' indices.
            int site_index1 = site1.index();
            int site_index2 = site2.index();

            // Create a new half-edge that belongs to the first site.
            edge_records_.push_back(voronoi_edge_type());
            voronoi_edge_type &edge1 = edge_records_.back();

            // Create a new half-edge that belongs to the second site.
            edge_records_.push_back(voronoi_edge_type());
            voronoi_edge_type &edge2 = edge_records_.back();

            // Add the initial cell during the first edge insertion.
            if (cell_records_.empty()) {
                process_single_site(site1);
                cell_records_.back().incident_edge(&edge1);
            }
            cell_records_[site_index1].inc_num_incident_edges();

            // Update the bounding rectangle.
            voronoi_rect_.update(prepare_point(site2.point0()));

            // The second site represents a new site during site event
            // processing. Add a new cell to the cell records.
            cell_records_.push_back(voronoi_cell_type(
                prepare_point(site2.point0()),
                prepare_point(site2.point1()),
                &edge2));
            cell_records_.back().inc_num_incident_edges();

            // Set up pointers to cells.
            edge1.cell(&cell_records_[site_index1]);
            edge2.cell(&cell_records_[site_index2]);

            // Set up twin pointers.
            edge1.twin(&edge2);
            edge2.twin(&edge1);

            // Return a pointer to the new half-edge.
            return std::make_pair(&edge1, &edge2);
        }

        // Insert a new half-edge into the output data structure with the
        // start at the point where two previously added half-edges intersect.
        // Takes as input two sites that create a new bisector, circle event
        // that correponds to the intersection point of the two old half-edges,
        // pointers to those half-edges. Half-edges' direction goes out of the
        // new voronoi vertex point. Returns a pointer to the new half-edge.
        template <typename SEvent, typename CEvent>
        void *insert_new_edge(const SEvent &site1,
                              const SEvent &site3,
                              const CEvent &circle,
                              void *data12,
                              void *data23) {
            voronoi_edge_type *edge12 =
                static_cast<voronoi_edge_type*>(data12);
            voronoi_edge_type *edge23 =
                static_cast<voronoi_edge_type*>(data23);

            // Add a new voronoi vertex.
            coordinate_type x = convert_(circle.x());
            coordinate_type y = convert_(circle.y());
            vertex_records_.push_back(
                voronoi_vertex_type(point_type(x, y), edge12));
            voronoi_vertex_type &new_vertex = vertex_records_.back();

            // Update vertex pointers of the old edges.
            edge12->vertex0(&new_vertex);
            edge23->vertex0(&new_vertex);

            // Add a new half-edge.
            edge_records_.push_back(voronoi_edge_type());
            voronoi_edge_type &new_edge1 = edge_records_.back();
            new_edge1.cell(&cell_records_[site1.index()]);
            new_edge1.cell()->inc_num_incident_edges();

            // Add a new half-edge.
            edge_records_.push_back(voronoi_edge_type());
            voronoi_edge_type &new_edge2 = edge_records_.back();
            new_edge2.cell(&cell_records_[site3.index()]);
            new_edge2.cell()->inc_num_incident_edges();

            // Update twin pointers.
            new_edge1.twin(&new_edge2);
            new_edge2.twin(&new_edge1);

            // Update vertex pointer.
            new_edge2.vertex0(&new_vertex);

            // Update voronoi prev/next pointers.
            edge12->prev(&new_edge1);
            new_edge1.next(edge12);
            edge12->twin()->next(edge23);
            edge23->prev(edge12->twin());
            edge23->twin()->next(&new_edge2);
            new_edge2.prev(edge23->twin());

            // Return a pointer to the new half-edge.
            return &new_edge1;
        }

        // Remove zero-length edges from the voronoi output.
        void clean() {
            voronoi_edge_iterator_type edge_it1;
            voronoi_edge_iterator_type edge_it = edge_records_.begin();
            num_cell_records_ = cell_records_.size();

            // All the initial sites are colinear.
            if (vertex_records_.empty()) {
                // Update edges counter.
                num_edge_records_ = num_cell_records_ - 1;

                // Return if there are no edges.
                if (edge_it == edge_records_.end())
                    return;

                // Update prev/next pointers of the edges. Those edges won't
                // have any common endpoints, cause they are infinite.
                // But still they follow each other using CCW ordering.
                voronoi_edge_type *edge1 = &(*edge_it);
                edge1->next(edge1);
                edge1->prev(edge1);
                ++edge_it;
                edge1 = &(*edge_it);
                ++edge_it;

                while (edge_it != edge_records_.end()) {
                    voronoi_edge_type *edge2 = &(*edge_it);
                    ++edge_it;

                    edge1->next(edge2);
                    edge1->prev(edge2);
                    edge2->next(edge1);
                    edge2->prev(edge1);

                    edge1 = &(*edge_it);
                    ++edge_it;
                }

                edge1->next(edge1);
                edge1->prev(edge1);
                return;
            }

            // Iterate over all the edges and remove degeneracies
            // (zero-length edges). Edge is considered to be zero-length
            // if both its endpoints lie within some epsilon-rectangle.
            while (edge_it != edge_records_.end()) {
                edge_it1 = edge_it;
                std::advance(edge_it, 2);

                // Degenerate edges exist only among finite edges.
                if (!edge_it1->vertex0() || !edge_it1->vertex1()) {
                    ++num_edge_records_;
                    continue;
                }

                const voronoi_vertex_type *v1 = edge_it1->vertex0();
                const voronoi_vertex_type *v2 = edge_it1->vertex1();

                // Make epsilon robust check.
                if (vertex_equality_predicate_(v1->vertex(), v2->vertex())) {
                    // Decrease number of cell's incident edges.
                    edge_it1->cell()->dec_num_incident_edges();
                    edge_it1->twin()->cell()->dec_num_incident_edges();

                    // Corresponding cell incident edge pointer
                    // points to the degenerate edge.
                    if (edge_it1->cell()->incident_edge() == &(*edge_it1)) {
                        // Update incident edge pointer.
                        if (edge_it1->cell()->incident_edge() ==
                            edge_it1->next()) {
                            edge_it1->cell()->incident_edge(NULL);
                        } else {
                            edge_it1->cell()->incident_edge(edge_it1->next());
                        }
                    }

                    // Cell corresponding to the twin edge
                    // points to the degenerate edge.
                    if (edge_it1->twin()->cell()->incident_edge() ==
                        edge_it1->twin()) {
                        // Update incident edge pointer.
                        if (edge_it1->twin()->cell()->incident_edge() ==
                            edge_it1->twin()->next()) {
                            edge_it1->twin()->cell()->incident_edge(NULL);
                        } else {
                            edge_it1->twin()->cell()->incident_edge(
                                edge_it1->twin()->next());
                        }
                    }

                    // To guarantee O(N) time for all removal operations we
                    // merge vertex with less incident edges to the one with
                    // more.
                    if (v1->num_incident_edges() >= v2->num_incident_edges()) {
                        remove_edge(&(*edge_it1));
                    } else {
                        remove_edge(edge_it1->twin());
                    }

                    // Remove zero-length edge.
                    edge_records_.erase(edge_it1, edge_it);
                } else {
                    // Count not degenerate edge.
                    ++num_edge_records_;
                }
            }

            // Remove degenerate voronoi vertices with zero incident edges.
            for (voronoi_vertex_iterator_type vertex_it =
                 vertex_records_.begin();
                 vertex_it != vertex_records_.end();) {
                if (vertex_it->incident_edge() == NULL) {
                    vertex_it = vertex_records_.erase(vertex_it);
                } else {
                    ++vertex_it;
                    ++num_vertex_records_;
                }
            }

            // Update prev/next pointers for the ray-edges.
            for (voronoi_cell_iterator_type cell_it = cell_records_.begin();
                 cell_it != cell_records_.end(); ++cell_it) {
                // Move to the previous edge while
                // it is possible in the CW direction.
                voronoi_edge_type *cur_edge = cell_it->incident_edge();
                if (cur_edge) {
                    while (cur_edge->prev() != NULL) {
                        cur_edge = cur_edge->prev();

                        // Terminate if this is not a boundary cell.
                        if (cur_edge == cell_it->incident_edge())
                            break;
                    }

                    // Rewind incident edge pointer to the
                    // CW leftmost edge for the boundary cells.
                    cell_it->incident_edge(cur_edge);

                    // Set up prev/next half-edge pointers for the ray-edges.
                    if (cur_edge->prev() == NULL) {
                        voronoi_edge_type *last_edge =
                            cell_it->incident_edge();
                        while (last_edge->next() != NULL)
                            last_edge = last_edge->next();
                        last_edge->next(cur_edge);
                        cur_edge->prev(last_edge);
                    }
                }
            }
        }

    private:
        template <typename T>
        point_type prepare_point(const T& x, const T& y) {
            coordinate_type xc = convert_(x);
            coordinate_type yc = convert_(y);
            return point_type(xc, yc);
        }

        template <typename P>
        point_type prepare_point(const P& p) {
            return prepare_point(p.x(), p.y());
        }

        // Remove degenerate edge.
        void remove_edge(voronoi_edge_type *edge) {
            voronoi_vertex_type *vertex1 = edge->vertex0();
            voronoi_vertex_type *vertex2 = edge->vertex1();

            // Update number of incident edges.
            vertex1->num_incident_edges(vertex1->num_incident_edges() +
                                        vertex2->num_incident_edges() - 2);

            // Update the endpoints of the incident edges to the second vertex.
            voronoi_edge_type *updated_edge = edge->twin()->rot_next();
            while (updated_edge != edge->twin()) {
                updated_edge->vertex0(vertex1);
                updated_edge = updated_edge->rot_next();
            }

            voronoi_edge_type *edge1 = edge;
            voronoi_edge_type *edge2 = edge->twin();

            voronoi_edge_type *edge1_rot_prev = edge1->rot_prev();
            voronoi_edge_type *edge1_rot_next = edge1->rot_next();

            voronoi_edge_type *edge2_rot_prev = edge2->rot_prev();
            voronoi_edge_type *edge2_rot_next = edge2->rot_next();

            // Update prev/next pointers for the incident edges.
            edge1_rot_next->twin()->next(edge2_rot_prev);
            edge2_rot_prev->prev(edge1_rot_next->twin());
            edge1_rot_prev->prev(edge2_rot_next->twin());
            edge2_rot_next->twin()->next(edge1_rot_prev);

            // Change the pointer to the incident edge if it points to the
            // degenerate edge.
            if (vertex1->incident_edge() == edge) {
                vertex1->incident_edge(edge->rot_prev());
            }

            // Set the incident edge point of the second vertex to NULL value.
            if (vertex1 != vertex2) {
                vertex2->incident_edge(NULL);
            }
        }

        voronoi_cells_type cell_records_;
        voronoi_vertices_type vertex_records_;
        voronoi_edges_type edge_records_;

        int num_cell_records_;
        int num_edge_records_;
        int num_vertex_records_;

        bounding_rectangle_type voronoi_rect_;
        ctype_converter_type convert_;
        vertex_equality_predicate_type vertex_equality_predicate_;

        // Disallow copy constructor and operator=
        voronoi_diagram(const voronoi_diagram&);
        void operator=(const voronoi_diagram&);
    };
} // polygon
} // boost

#endif
