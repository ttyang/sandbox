// Boost.Geometry Index
//
// R-tree options, algorithms, parameters
//
// Copyright (c) 2011-2012 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_OPTIONS_HPP
#define BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_OPTIONS_HPP

namespace boost { namespace geometry { namespace index {

// InsertTag
struct insert_default_tag {};
struct insert_reinsert_tag {};

// ChooseNextNodeTag
struct choose_by_content_diff_tag {};
struct choose_by_overlap_diff_tag {};

// SplitTag
struct split_default_tag {};
//struct split_kmeans_tag {};

// RedistributeTag
struct linear_tag {};
struct quadratic_tag {};
struct rstar_tag {};

// NodeTag
struct node_default_tag {};
struct node_default_variant_tag {};
struct node_default_static_tag {};
struct node_default_static_variant_tag {};

// TODO: awulkiew - implement those:
//if ( m_min_elems_per_node < 1 )
//    m_min_elems_per_node = 1;
//if ( m_max_elems_per_node < 2 )
//    m_max_elems_per_node = 2;

/*!
Linear r-tree creation algorithm parameters.

\tparam MaxElements     Maximum number of elements in nodes.
\tparam MinElements     Minimum number of elements in nodes.
*/
template <size_t MaxElements, size_t MinElements>
struct linear
{
    static const size_t max_elements = MaxElements;
    static const size_t min_elements = MinElements;
};

/*!
Quadratic r-tree creation algorithm parameters.

\tparam MaxElements     Maximum number of elements in nodes.
\tparam MinElements     Minimum number of elements in nodes.
*/
template <size_t MaxElements, size_t MinElements>
struct quadratic
{
    static const size_t max_elements = MaxElements;
    static const size_t min_elements = MinElements;
};

namespace options { namespace detail { 

template <size_t MaxElements>
struct default_rstar_reinserted_elements
{
    static const size_t value = (MaxElements * 3) / 10;
};

}} // namespace options::detail

/*!
Quadratic r-tree creation algorithm parameters.

\tparam MaxElements             Maximum number of elements in nodes.
\tparam MinElements             Minimum number of elements in nodes.
\tparam OverlapCostThreshold    The number of leaf node children elements above which
                                nearly minimum overlap cost is calculated instead of minimum
                                overlap cost. If 0 minimum overlap cost is always calculated.
\tparam ReinsertedElements      Number of elements reinserted by forced reinsertions algorithm.
*/
template <size_t MaxElements,
          size_t MinElements,
          size_t OverlapCostThreshold = 0,
          size_t ReinsertedElements = options::detail::default_rstar_reinserted_elements<MaxElements>::value
          >
struct rstar
{
    static const size_t max_elements = MaxElements;
    static const size_t min_elements = MinElements;
    static const size_t overlap_cost_threshold = OverlapCostThreshold;
    static const size_t reinserted_elements = ReinsertedElements;
};

namespace options {

template <typename Parameters, typename InsertTag, typename ChooseNextNodeTag, typename SplitTag, typename RedistributeTag, typename NodeTag>
struct rtree
{
    typedef Parameters parameters_type;
    typedef InsertTag insert_tag;
    typedef ChooseNextNodeTag choose_next_node_tag;
    typedef SplitTag split_tag;
    typedef RedistributeTag redistribute_tag;
    typedef NodeTag node_tag;
};

} // namespace options

//template <size_t MaxElements, size_t MinElements>
//struct kmeans
//{
//    static const size_t max_elements = MaxElements;
//    static const size_t min_elements = MinElements;
//};

namespace detail { namespace rtree {

template <typename Parameters>
struct options_type
{
    // TODO: awulkiew - use static assert
};

template <size_t MaxElements, size_t MinElements>
struct options_type< linear<MaxElements, MinElements> >
{
    typedef options::rtree<
        linear<MaxElements, MinElements>,
        insert_default_tag,
        choose_by_content_diff_tag,
        split_default_tag,
        linear_tag,
        node_default_static_tag
    > type;
};

template <size_t MaxElements, size_t MinElements>
struct options_type< quadratic<MaxElements, MinElements> >
{
    typedef options::rtree<
        quadratic<MaxElements, MinElements>,
        insert_default_tag,
        choose_by_content_diff_tag,
        split_default_tag,
        quadratic_tag,
        node_default_static_tag
    > type;
};

template <size_t MaxElements, size_t MinElements, size_t OverlapCostThreshold, size_t ReinsertedElements>
struct options_type< rstar<MaxElements, MinElements, OverlapCostThreshold, ReinsertedElements> >
{
    typedef options::rtree<
        rstar<MaxElements, MinElements, OverlapCostThreshold, ReinsertedElements>,
        insert_reinsert_tag,
        choose_by_overlap_diff_tag,
        split_default_tag,
        rstar_tag,
        node_default_static_tag
    > type;
};

//template <size_t MaxElements, size_t MinElements>
//struct options_type< kmeans<MaxElements, MinElements> >
//{
//    typedef options::rtree<
//        kmeans<MaxElements, MinElements>,
//        insert_default_tag,
//        choose_by_content_diff_tag, // change it?
//        split_kmeans_tag,
//        int, // dummy tag - not used for now
//        node_default_static_tag
//    > type;
//};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_OPTIONS_HPP
