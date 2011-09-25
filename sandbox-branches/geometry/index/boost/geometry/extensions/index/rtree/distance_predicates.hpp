// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Boost.SpatialIndex - Spatial index distance predicates, calculators and checkers
//                      used in nearest query - rtree's specializations
//
// Copyright 2011 Adam Wulkiewicz.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_DISTANCE_PREDICATES_HPP
#define BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_DISTANCE_PREDICATES_HPP

#include <boost/geometry/extensions/index/distance_predicates.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail {

namespace rtree
{

struct value_distance_predicate_tag {};
struct node_distance_predicate_tag {};

} // namespace rtree

// distance_calc

template <typename Point, typename Indexable>
struct distance_calc<
    Point,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    typedef typename geometry::default_distance_result<Point, Indexable>::type result_type;

    static inline result_type apply(Point const& p, Indexable const& i)
    {
        return index::comparable_distance_near(p, i);
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_calc<
    detail::distance_unbounded<Point, AlgoTag>,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    typedef typename geometry::default_distance_result<Point, Indexable>::type result_type;

    static inline result_type apply(
        detail::distance_unbounded<Point, AlgoTag> const& dx,
        Indexable const& i)
    {
        return index::comparable_distance_near(dx.point, i);
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_calc<
    detail::distance_half_bounded<Point, AlgoTag, detail::distance_min_tag>,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    typedef typename geometry::default_distance_result<Point, Indexable>::type distance_type;
    typedef std::pair<distance_type, distance_type> result_type;

    static inline result_type apply(
        detail::distance_half_bounded<Point, AlgoTag, detail::distance_min_tag> const& dx,
        Indexable const& i)
    {
        return std::make_pair(
            index::comparable_distance_near(dx.point, i),
            index::comparable_distance_far(dx.point, i)
        );
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_calc<
    detail::distance_half_bounded<Point, AlgoTag, detail::distance_max_tag>,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    typedef typename geometry::default_distance_result<Point, Indexable>::type result_type;

    static inline result_type apply(
        detail::distance_half_bounded<Point, AlgoTag, detail::distance_max_tag> const& dx,
        Indexable const& i)
    {
        return index::comparable_distance_near(dx.point, i);
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_calc<
    detail::distance_bounded<Point, AlgoTag>,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    typedef typename geometry::default_distance_result<Point, Indexable>::type distance_type;
    typedef std::pair<distance_type, distance_type> result_type;

    static inline result_type apply(
        detail::distance_bounded<Point, AlgoTag> const& dx,
        Indexable const& i)
    {
        return std::make_pair(
            index::comparable_distance_near(dx.point, i),
            index::comparable_distance_far(dx.point, i)
        );
    }
};

// distance_predicate_check

template <typename Point, typename Indexable>
struct distance_predicate_check<
    Point,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    template <typename DistanceType>
    static inline bool apply(Point const&, DistanceType const&)
    {
        return true;
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_predicate_check<
    detail::distance_unbounded<Point, AlgoTag>,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    template <typename DistanceType>
    static inline bool apply(
        detail::distance_unbounded<Point, AlgoTag> const&,
        DistanceType const&)
    {
        return true;
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_predicate_check<
    detail::distance_half_bounded<Point, AlgoTag, detail::distance_min_tag>,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    template <typename DistanceType>
    static inline bool apply(
        detail::distance_half_bounded<Point, AlgoTag, detail::distance_min_tag> const& dx,
        DistanceType const& d)
    {
        return dx.comparable_limit <= d.second;
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_predicate_check<
    detail::distance_half_bounded<Point, AlgoTag, detail::distance_max_tag>,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    template <typename DistanceType>
    static inline bool apply(
        detail::distance_half_bounded<Point, AlgoTag, detail::distance_max_tag> const& dx,
        DistanceType const& comparable_d)
    {
        return comparable_d <= dx.comparable_limit;
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_predicate_check<
    detail::distance_bounded<Point, AlgoTag>,
    Indexable,
    rtree::node_distance_predicate_tag>
{
    template <typename DistanceType>
    static inline bool apply(
        detail::distance_bounded<Point, AlgoTag> const& dx,
        DistanceType const& d)
    {
        return dx.comparable_min <= d.second && d.first <= dx.comparable_max;
    }
};

// TODO implement alternative version for Indexable being a Point - don't need to calculate the distance 2x
// TODO explicitly define DistanceType ?

namespace rtree
{

// distance less comparator

template <typename Point, typename Indexable>
struct distance_less
{
    template <typename DistanceType>
    inline bool operator()(DistanceType const& d1, DistanceType const& d2)
    {
        return d1 < d2;
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_less<
    detail::distance_half_bounded<Point, AlgoTag, detail::distance_min_tag>,
    Indexable
>
{
    template <typename DistanceType>
    inline bool operator()(DistanceType const& d1, DistanceType const& d2)
    {
        return d1.first < d2.first;
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_less<
    detail::distance_bounded<Point, AlgoTag>,
    Indexable
>
{
    template <typename DistanceType>
    inline bool operator()(DistanceType const& d1, DistanceType const& d2)
    {
        return d1.first < d2.first;
    }
};

// TODO distance_node_pruning_check

template <typename Point, typename Indexable>
struct distance_node_pruning_check
{
    template <typename SmallestDistanceType, typename NodeDistanceType>
    static inline bool apply(SmallestDistanceType const& sd, NodeDistanceType const& nd)
    {
        return sd < nd;
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_node_pruning_check<
    detail::distance_half_bounded<Point, AlgoTag, detail::distance_min_tag>,
    Indexable
>
{
    template <typename SmallestDistanceType, typename NodeDistanceType>
    static inline bool apply(SmallestDistanceType const& sd, NodeDistanceType const& nd)
    {
        return sd < nd.first;
    }
};

template <typename Point, typename AlgoTag, typename Indexable>
struct distance_node_pruning_check<
    detail::distance_bounded<Point, AlgoTag>,
    Indexable
>
{
    template <typename SmallestDistanceType, typename NodeDistanceType>
    static inline bool apply(SmallestDistanceType const& sd, NodeDistanceType const& nd)
    {
        return sd < nd.first;
    }
};

} // namespace rtree

// move distance_calc and distance_comp into geometry::index ?

// TODO: awulkiew - pruning for nodes! <- inside detail::rtree so NOT HERE
// if 0 < comp_near node is pruned if maxdist(point, node_box) < comp_near
// if comp_far < INF node is pruned if comp_far < min_dist(point, node_box)
// still nodes must be sorted by min_dist(point, node_box)

// for values, proper distance values are calculated min, max or centroid
// and tested with comp_near and/or comp_far

// + something in case of nodes
// additional calculation of maxdist in case of distance_between and
// distance_xxxxx<more> 

} // namespace detail

//template <typename PointData, typename Indexable>
//inline typename detail::distance_calc<PointData, Indexable>::distance_type
//distance_calc(PointData const& p, Indexable const& i)
//{
//    return detail::distance_calc<PointData, Indexable>
//        ::apply(p, i);
//}
//
//template <typename PointData, typename DistanceType>
//inline bool
//distance_comp(PointData const& p, DistanceType const& d)
//{
//    return detail::distance_comp<PointData>
//        ::apply(p, d);
//}

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_DISTANCE_PREDICATES_HPP
