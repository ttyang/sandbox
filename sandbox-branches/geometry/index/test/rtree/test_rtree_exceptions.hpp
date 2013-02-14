// Boost.Geometry Index
//
// R-tree nodes based on runtime-polymorphism, storing static-size containers
// test version throwing exceptions on creation
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_TEST_RTREE_EXCEPTIONS_HPP
#define BOOST_GEOMETRY_INDEX_TEST_RTREE_EXCEPTIONS_HPP

#include <rtree/test_rtree.hpp>

#include <boost/geometry/index/detail/rtree/node/dynamic_visitor.hpp>

#include <rtree/test_throwing.hpp>

namespace boost { namespace geometry { namespace index {

template <size_t MaxElements, size_t MinElements>
struct linear_throwing : public linear<MaxElements, MinElements> {};

template <size_t MaxElements, size_t MinElements>
struct quadratic_throwing : public quadratic<MaxElements, MinElements> {};

template <size_t MaxElements, size_t MinElements, size_t OverlapCostThreshold = 0, size_t ReinsertedElements = detail::default_rstar_reinserted_elements_s<MaxElements>::value>
struct rstar_throwing : public rstar<MaxElements, MinElements, OverlapCostThreshold, ReinsertedElements> {};

namespace detail { namespace rtree {

// options implementation (from options.hpp)

struct node_throwing_d_mem_static_tag {};

template <size_t MaxElements, size_t MinElements>
struct options_type< linear_throwing<MaxElements, MinElements> >
{
    typedef options<
        linear_throwing<MaxElements, MinElements>,
        insert_default_tag, choose_by_content_diff_tag, split_default_tag, linear_tag,
        node_throwing_d_mem_static_tag
    > type;
};

template <size_t MaxElements, size_t MinElements>
struct options_type< quadratic_throwing<MaxElements, MinElements> >
{
    typedef options<
        quadratic_throwing<MaxElements, MinElements>,
        insert_default_tag, choose_by_content_diff_tag, split_default_tag, quadratic_tag,
        node_throwing_d_mem_static_tag
    > type;
};

template <size_t MaxElements, size_t MinElements, size_t OverlapCostThreshold, size_t ReinsertedElements>
struct options_type< rstar_throwing<MaxElements, MinElements, OverlapCostThreshold, ReinsertedElements> >
{
    typedef options<
        rstar_throwing<MaxElements, MinElements, OverlapCostThreshold, ReinsertedElements>,
        insert_reinsert_tag, choose_by_overlap_diff_tag, split_default_tag, rstar_tag,
        node_throwing_d_mem_static_tag
    > type;
};

}} // namespace detail::rtree

// node implementation

namespace detail { namespace rtree {

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct dynamic_internal_node<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
    : public dynamic_node<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
{
    typedef throwing_varray<
        std::pair<
            Box,
            typename Allocators::node_pointer
        >,
        Parameters::max_elements + 1
    > elements_type;

    template <typename Dummy>
    inline dynamic_internal_node(Dummy) {}

    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag, false> & v) { v(*this); }
    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag, true> & v) const { v(*this); }

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct dynamic_leaf<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
    : public dynamic_node<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
{
    typedef throwing_varray<Value, Parameters::max_elements + 1> elements_type;

    template <typename Dummy>
    inline dynamic_leaf(Dummy) {}

    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag, false> & v) { v(*this); }
    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag, true> & v) const { v(*this); }

    elements_type elements;
};

// elements derived type
template <typename OldValue, size_t N, typename NewValue>
struct container_from_elements_type<throwing_varray<OldValue, N>, NewValue>
{
    typedef throwing_varray<NewValue, N> type;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct node<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
{
    typedef dynamic_node<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct internal_node<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
{
    typedef dynamic_internal_node<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct leaf<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
{
    typedef dynamic_leaf<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators, bool IsVisitableConst>
struct visitor<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag, IsVisitableConst>
{
    typedef dynamic_visitor<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag, IsVisitableConst> type;
};

// allocators

template <typename Allocator, typename Value, typename Parameters, typename Box>
class allocators<Allocator, Value, Parameters, Box, node_throwing_d_mem_static_tag>
{
    BOOST_COPYABLE_AND_MOVABLE_ALT(allocators)

public:
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;

    typedef typename allocator_type::template rebind<
        typename node<Value, Parameters, Box, allocators, node_throwing_d_mem_static_tag>::type
    >::other::pointer node_pointer;

    typedef typename allocator_type::template rebind<
        typename internal_node<Value, Parameters, Box, allocators, node_throwing_d_mem_static_tag>::type
    >::other::pointer internal_node_pointer;

    typedef typename allocator_type::template rebind<
        typename internal_node<Value, Parameters, Box, allocators, node_throwing_d_mem_static_tag>::type
    >::other internal_node_allocator_type;

    typedef typename allocator_type::template rebind<
        typename leaf<Value, Parameters, Box, allocators, node_throwing_d_mem_static_tag>::type
    >::other leaf_allocator_type;

    inline allocators()
        : allocator()
        , internal_node_allocator()
        , leaf_allocator()
    {}

    inline explicit allocators(Allocator alloc)
        : allocator(alloc)
        , internal_node_allocator(allocator)
        , leaf_allocator(allocator)
    {}

    inline allocators(allocators const& a)
        : allocator(a.allocator)
        , internal_node_allocator(a.internal_node_allocator)
        , leaf_allocator(a.leaf_allocator)
    {}

    inline allocators(BOOST_RV_REF(allocators) a)
        : allocator(boost::move(a.allocator))
        , internal_node_allocator(boost::move(a.internal_node_allocator))
        , leaf_allocator(boost::move(a.leaf_allocator))
    {}

    void swap(allocators & a)
    {
        boost::swap(allocator, a.allocator);
        boost::swap(internal_node_allocator, a.internal_node_allocator);
        boost::swap(leaf_allocator, a.leaf_allocator);
    }

    allocator_type allocator;
    internal_node_allocator_type internal_node_allocator;
    leaf_allocator_type leaf_allocator;
};

struct node_bad_alloc : public std::exception
{
    const char * what() const throw() { return "internal node creation failed."; }
};

struct throwing_node_settings
{
    static void throw_if_required()
    {
        // throw if counter meets max count
        if ( get_max_calls_ref() <= get_calls_counter_ref() )
            throw node_bad_alloc();
        else
            ++get_calls_counter_ref();
    }

    static void reset_calls_counter() { get_calls_counter_ref() = 0; }
    static void set_max_calls(size_t mc) { get_max_calls_ref() = mc; }

    static size_t & get_calls_counter_ref() { static size_t cc = 0; return cc; }
    static size_t & get_max_calls_ref() { static size_t mc = (std::numeric_limits<size_t>::max)(); return mc; }
};

// create_node

template <typename Allocators, typename Value, typename Parameters, typename Box>
struct create_node<
    Allocators,
    dynamic_internal_node<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        // throw if counter meets max count
        throwing_node_settings::throw_if_required();

        return create_dynamic_node<
            typename Allocators::node_pointer,
            dynamic_internal_node<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
        >::apply(allocators.internal_node_allocator, allocators.internal_node_allocator);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box>
struct create_node<
    Allocators,
    dynamic_leaf<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        // throw if counter meets max count
        throwing_node_settings::throw_if_required();

        return create_dynamic_node<
            typename Allocators::node_pointer,
            dynamic_leaf<Value, Parameters, Box, Allocators, node_throwing_d_mem_static_tag>
        >::apply(allocators.leaf_allocator, allocators.leaf_allocator);
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_TEST_RTREE_EXCEPTIONS_HPP
