// Boost.Geometry Index
//
// R-tree nodes based on Boost.Variant, storing static-size containers
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_DEFAULT_STATIC_VARIANT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_DEFAULT_STATIC_VARIANT_HPP

#include <boost/geometry/index/detail/varray.hpp>

#include <boost/geometry/index/detail/rtree/node/static_visitor.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// nodes default types

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct static_internal_node<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
{
    typedef detail::varray<
        std::pair<
            Box,
            typename Allocators::node_pointer
        >,
        Parameters::max_elements + 1,
        typename Allocators::internal_node_elements_allocator_type
    > elements_type;

    template <typename Dummy>
    inline static_internal_node(Dummy) {}

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct static_leaf<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
{
    typedef detail::varray<
        Value,
        Parameters::max_elements + 1,
        typename Allocators::leaf_elements_allocator_type
    > elements_type;

    template <typename Dummy>
    inline static_leaf(Dummy) {}

    elements_type elements;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct node<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
{
    typedef boost::variant<
        static_leaf<Value, Parameters, Box, Allocators, node_s_mem_static_tag>,
        static_internal_node<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
    > type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct internal_node<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
{
    typedef static_internal_node<Value, Parameters, Box, Allocators, node_s_mem_static_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct leaf<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
{
    typedef static_leaf<Value, Parameters, Box, Allocators, node_s_mem_static_tag> type;
};

// visitor traits

template <typename Value, typename Parameters, typename Box, typename Allocators, bool IsVisitableConst>
struct visitor<Value, Parameters, Box, Allocators, node_s_mem_static_tag, IsVisitableConst>
{
    typedef static_visitor<> type;
};

// allocators

template <typename Allocator, typename Value, typename Parameters, typename Box>
struct allocators<Allocator, Value, Parameters, Box, node_s_mem_static_tag>
    : nonassignable
{
    BOOST_COPYABLE_AND_MOVABLE_ALT(allocators)

public:
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;

    typedef typename allocator_type::template rebind<
        typename node<Value, Parameters, Box, allocators, node_s_mem_static_tag>::type
    >::other::pointer node_pointer;

    typedef typename allocator_type::template rebind<
        typename internal_node<Value, Parameters, Box, allocators, node_s_mem_static_tag>::type
    >::other::pointer internal_node_pointer;

    typedef typename allocator_type::template rebind<
        typename node<Value, Parameters, Box, allocators, node_s_mem_static_tag>::type
    >::other node_allocator_type;

    typedef typename allocator_type::template rebind<
        std::pair<Box, node_pointer>
    >::other internal_node_elements_allocator_type;

    typedef typename allocator_type::template rebind<
        Value
    >::other leaf_elements_allocator_type;

    inline allocators()
        : allocator()
        , node_allocator()
    {}

    inline explicit allocators(Allocator alloc)
        : allocator(alloc)
        , node_allocator(allocator)
    {}

    inline allocators(allocators const& a)
        : allocator(a.allocator)
        , node_allocator(a.node_allocator)
    {}

    inline allocators(BOOST_RV_REF(allocators) a)
        : allocator(boost::move(a.allocator))
        , node_allocator(boost::move(a.node_allocator))
    {}

    void swap(allocators & a)
    {
        boost::swap(allocator, a.allocator);
        boost::swap(node_allocator, a.node_allocator);
    }

    allocator_type allocator;
    node_allocator_type node_allocator;
};

// create_node

template <typename Allocators, typename Value, typename Parameters, typename Box>
struct create_node<
    Allocators,
    static_internal_node<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_static_node<
            typename Allocators::node_pointer,
            static_internal_node<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
        >::template apply(allocators.node_allocator, allocators.node_allocator);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box>
struct create_node<
    Allocators,
    static_leaf<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_static_node<
            typename Allocators::node_pointer,
            static_leaf<Value, Parameters, Box, Allocators, node_s_mem_static_tag>
        >::template apply(allocators.node_allocator, allocators.node_allocator);
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_DEFAULT_STATIC_VARIANT_HPP
