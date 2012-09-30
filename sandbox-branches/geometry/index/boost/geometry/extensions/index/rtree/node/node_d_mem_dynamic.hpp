// Boost.Geometry Index
//
// R-tree nodes based on run-time polymorphism, storing std::vectors
//
// Copyright (c) 2011-2012 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_NODE_NODE_DEFAULT_HPP
#define BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_NODE_NODE_DEFAULT_HPP

#include <vector>

#include <boost/geometry/extensions/index/rtree/node/dynamic_visitor.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct dynamic_internal_node<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag>
    : public dynamic_node<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag>
{
    typedef std::vector<
        std::pair<Box, dynamic_node<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag> *>,
        typename Allocators::internal_node_elements_allocator_type
    > elements_type;

    inline dynamic_internal_node(typename Allocators::internal_node_elements_allocator_type & al)
        : elements(al)
    {}

    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag, false> & v) { v(*this); }
    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag, true> & v) const { v(*this); }

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct dynamic_leaf<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag>
    : public dynamic_node<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag>
{
    typedef std::vector<
        Value,
        typename Allocators::leaf_elements_allocator_type
    > elements_type;

    inline dynamic_leaf(typename Allocators::leaf_elements_allocator_type & al)
        : elements(al)
    {}

    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag, false> & v) { v(*this); }
    void apply_visitor(dynamic_visitor<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag, true> & v) const { v(*this); }

    elements_type elements;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct node<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag>
{
    typedef dynamic_node<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct internal_node<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag>
{
    typedef dynamic_internal_node<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct leaf<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag>
{
    typedef dynamic_leaf<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag> type;
};

// visitor traits

template <typename Value, typename Parameters, typename Box, typename Allocators, bool IsVisitableConst>
struct visitor<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag, IsVisitableConst>
{
    typedef dynamic_visitor<Value, Parameters, Box, Allocators, node_d_mem_dynamic_tag, IsVisitableConst> type;
};

// element's indexable type

template <typename Value, typename Translator>
struct element_indexable_type
{
    typedef typename translator::indexable_type<Translator>::type type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag, typename Translator>
struct element_indexable_type<
    std::pair<Box, dynamic_node<Value, Parameters, Box, Allocators, Tag> *>,
    Translator
>
{
    typedef Box type;
};

// element's indexable getter

template <typename Value, typename Translator>
inline typename Translator::result_type
element_indexable(Value const& el, Translator const& tr)
{
	return tr(el);
}

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag, typename Translator>
inline Box const&
element_indexable(
    std::pair< Box, dynamic_node<Value, Parameters, Box, Allocators, Tag> *> const& el,
    Translator const&)
{
    return el.first;
}

// nodes elements

template <typename Node>
struct elements_type
{
	typedef typename Node::elements_type type;
};

template <typename Node>
inline typename elements_type<Node>::type &
elements(Node & n)
{
	return n.elements;
}

template <typename Node>
inline typename elements_type<Node>::type const&
elements(Node const& n)
{
	return n.elements;
}

// elements derived type
template <typename Elements, typename NewValue>
struct container_from_elements_type
{
    typedef std::vector<NewValue> type;
};

// allocators

template <typename Allocator, typename Value, typename Parameters, typename Box>
struct allocators<Allocator, Value, Parameters, Box, node_d_mem_dynamic_tag>
{
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;

    typedef typename allocator_type::template rebind<
        typename internal_node<Value, Parameters, Box, allocators, node_d_mem_dynamic_tag>::type
    >::other internal_node_allocator_type;

    typedef typename allocator_type::template rebind<
        typename leaf<Value, Parameters, Box, allocators, node_d_mem_dynamic_tag>::type
    >::other leaf_allocator_type;

    typedef typename allocator_type::template rebind<
        std::pair<Box, dynamic_node<Value, Parameters, Box, allocators, node_d_mem_dynamic_tag> *>
    >::other internal_node_elements_allocator_type;

    typedef typename allocator_type::template rebind<
        Value
    >::other leaf_elements_allocator_type;

    inline explicit allocators(Allocator alloc)
        : allocator(alloc)
        , internal_node_allocator(allocator)
        , leaf_allocator(allocator)
        , internal_node_elements_allocator(allocator)
        , leaf_elements_allocator(allocator)
    {}

    allocator_type allocator;
    internal_node_allocator_type internal_node_allocator;
    leaf_allocator_type leaf_allocator;
    internal_node_elements_allocator_type internal_node_elements_allocator;
    leaf_elements_allocator_type leaf_elements_allocator;
};

// create_node_impl

template <typename Node>
struct create_node_poly
{
    template <typename RetNode, typename AllocNode, typename AllocElems>
    static inline RetNode * apply(AllocNode & alloc_node, AllocElems & alloc_elems)
    {
        Node * p = alloc_node.allocate(1);

        if ( 0 == p )
            throw std::bad_alloc();

        try
        {
            alloc_node.construct(p, Node(alloc_elems));
        }
        catch(...)
        {
            alloc_node.deallocate(p, 1);
            throw;
        }

        return p;
    }
};

// destroy_node_impl

template <typename Node>
struct destroy_node_poly
{
    template <typename AllocNode, typename BaseNode>
    static inline void apply(AllocNode & alloc_node, BaseNode * n)
    {
        Node * p = rtree::get<Node>(n);
        alloc_node.destroy(p);
        alloc_node.deallocate(p, 1);
    }
};

// create_node

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    dynamic_internal_node<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline typename node<Value, Parameters, Box, Allocators, Tag>::type *
    apply(Allocators & allocators)
    {
        return create_node_poly<
            dynamic_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::template apply<
            typename node<Value, Parameters, Box, Allocators, Tag>::type
        >(allocators.internal_node_allocator, allocators.internal_node_elements_allocator);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    dynamic_leaf<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline typename node<Value, Parameters, Box, Allocators, Tag>::type *
    apply(Allocators & allocators)
    {
        return create_node_poly<
            dynamic_leaf<Value, Parameters, Box, Allocators, Tag>
        >::template apply<
            typename node<Value, Parameters, Box, Allocators, Tag>::type
        >(allocators.leaf_allocator, allocators.leaf_elements_allocator);
    }
};

// destroy_node

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    dynamic_internal_node<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline void apply(Allocators & allocators, typename node<Value, Parameters, Box, Allocators, Tag>::type * n)
    {
        destroy_node_poly<
            dynamic_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.internal_node_allocator, n);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    dynamic_leaf<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline void apply(Allocators & allocators, typename node<Value, Parameters, Box, Allocators, Tag>::type * n)
    {
        destroy_node_poly<
            dynamic_leaf<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.leaf_allocator, n);
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_NODE_NODE_DEFAULT_HPP
