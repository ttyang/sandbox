// Boost.Geometry Index
//
// R-tree nodes based on Boost.Variant, storing std::vectors
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_DEFAULT_VARIANT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_DEFAULT_VARIANT_HPP

#include <boost/container/vector.hpp>

#include <boost/geometry/index/detail/rtree/node/static_visitor.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// nodes default types

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct static_internal_node
{
    typedef boost::container::vector<
        std::pair<
            Box,
            typename Allocators::node_pointer
        >,
        typename Allocators::internal_node_elements_allocator_type
    > elements_type;

    inline static_internal_node(typename Allocators::internal_node_elements_allocator_type & al)
        : elements(al)
    {}

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct static_leaf
{
    typedef boost::container::vector<
        Value,
        typename Allocators::leaf_elements_allocator_type
    > elements_type;

    inline static_leaf(typename Allocators::leaf_elements_allocator_type & al)
        : elements(al)
    {}

    elements_type elements;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct node<Value, Parameters, Box, Allocators, node_s_mem_dynamic_tag>
{
    typedef boost::variant<
        static_leaf<Value, Parameters, Box, Allocators, node_s_mem_dynamic_tag>,
        static_internal_node<Value, Parameters, Box, Allocators, node_s_mem_dynamic_tag>
    > type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct internal_node<Value, Parameters, Box, Allocators, node_s_mem_dynamic_tag>
{
    typedef static_internal_node<Value, Parameters, Box, Allocators, node_s_mem_dynamic_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct leaf<Value, Parameters, Box, Allocators, node_s_mem_dynamic_tag>
{
    typedef static_leaf<Value, Parameters, Box, Allocators, node_s_mem_dynamic_tag> type;
};

// visitor traits

template <typename Value, typename Parameters, typename Box, typename Allocators, bool IsVisitableConst>
struct visitor<Value, Parameters, Box, Allocators, node_s_mem_dynamic_tag, IsVisitableConst>
{
    typedef static_visitor<> type;
};

// allocators

template <typename Allocator, typename Value, typename Parameters, typename Box>
class allocators<Allocator, Value, Parameters, Box, node_s_mem_dynamic_tag>
    : nonassignable
{
    BOOST_COPYABLE_AND_MOVABLE_ALT(allocators)

public:
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;

    typedef typename allocator_type::template rebind<
        typename node<Value, Parameters, Box, allocators, node_s_mem_dynamic_tag>::type
    >::other::pointer node_pointer;

    typedef typename allocator_type::template rebind<
        typename internal_node<Value, Parameters, Box, allocators, node_s_mem_dynamic_tag>::type
    >::other::pointer internal_node_pointer;

    typedef typename allocator_type::template rebind<
        typename node<Value, Parameters, Box, allocators, node_s_mem_dynamic_tag>::type
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
        , internal_node_elements_allocator()
        , leaf_elements_allocator()
    {}

    inline explicit allocators(Allocator alloc)
        : allocator(alloc)
        , node_allocator(allocator)
        , internal_node_elements_allocator(allocator)
        , leaf_elements_allocator(allocator)
    {}

    inline allocators(allocators const& a)
        : allocator(a.allocator)
        , node_allocator(a.node_allocator)
        , internal_node_elements_allocator(a.internal_node_elements_allocator)
        , leaf_elements_allocator(a.leaf_elements_allocator)
    {}

    inline allocators(BOOST_RV_REF(allocators) a)
        : allocator(boost::move(a.allocator))
        , node_allocator(boost::move(a.node_allocator))
        , internal_node_elements_allocator(boost::move(a.internal_node_elements_allocator))
        , leaf_elements_allocator(boost::move(a.leaf_elements_allocator))
    {}

    void swap(allocators & a)
    {
        boost::swap(allocator, a.allocator);
        boost::swap(node_allocator, a.node_allocator);
        boost::swap(internal_node_elements_allocator, a.internal_node_elements_allocator);
        boost::swap(leaf_elements_allocator, a.leaf_elements_allocator);
    }

    allocator_type allocator;
    node_allocator_type node_allocator;
    internal_node_elements_allocator_type internal_node_elements_allocator;
    leaf_elements_allocator_type leaf_elements_allocator;
};

// create_node_variant

template <typename VariantPtr, typename Node>
struct create_static_node
{
    template <typename AllocNode, typename AllocElems>
    static inline VariantPtr apply(AllocNode & alloc_node, AllocElems & alloc_elems)
    {
        VariantPtr p = alloc_node.allocate(1);

        if ( 0 == p )
            throw std::bad_alloc();

        try
        {
            // NOTE/TODO
            // Here the whole node may be copied
            alloc_node.construct(p, Node(alloc_elems)); // implicit cast to Variant
        }
        catch(...)
        {
            alloc_node.deallocate(p, 1);
            throw;
        }

        return p;
    }
};

// destroy_node_variant

template <typename Node>
struct destroy_static_node
{
    template <typename AllocNode, typename VariantPtr>
    static inline void apply(AllocNode & alloc_node, VariantPtr n)
    {
        alloc_node.destroy(n);
        alloc_node.deallocate(n, 1);
    }
};

// create_node

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    static_internal_node<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_static_node<
            typename Allocators::node_pointer,
            static_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator, allocators.internal_node_elements_allocator);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    static_leaf<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_static_node<
            typename Allocators::node_pointer,
            static_leaf<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator, allocators.leaf_elements_allocator);
    }
};

// destroy_node

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    static_internal_node<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline void apply(Allocators & allocators, typename Allocators::node_pointer n)
    {
        destroy_static_node<
            static_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator, n);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    static_leaf<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline void apply(Allocators & allocators, typename Allocators::node_pointer n)
    {
        destroy_static_node<
            static_leaf<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator, n);
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_DEFAULT_VARIANT_HPP
