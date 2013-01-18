// Boost.Geometry Index
//
// R-tree spatial query visitor implementation
//
// Copyright (c) 2011-2012 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_VISITORS_SPATIAL_QUERY_HPP
#define BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_VISITORS_SPATIAL_QUERY_HPP

#include <boost/geometry/extensions/index/detail/predicates.hpp>

#include <boost/geometry/extensions/index/detail/rtree/node/node.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename Value, typename Options, typename Translator, typename Box, typename Allocators, typename Predicates, typename OutIter>
struct spatial_query
    : public rtree::visitor<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag, true>::type
    , index::detail::nonassignable
{
    typedef typename rtree::node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type node;
    typedef typename rtree::internal_node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type internal_node;
    typedef typename rtree::leaf<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type leaf;

    inline spatial_query(Translator const& t, Predicates const& p, OutIter out_it)
        : tr(t), pred(p), out_iter(out_it), found_count(0)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // traverse nodes meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            // if node meets predicates
            // 0 - dummy value
            if ( index::detail::predicates_check<index::detail::envelope_tag>(pred, 0, it->first) )
                rtree::apply_visitor(*this, *it->second);
        }
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // get all values meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            // if value meets predicates
            if ( index::detail::predicates_check<index::detail::value_tag>(pred, *it, tr(*it)) )
            {
                out_iter = *it;
                ++out_iter;

                ++found_count;
            }
        }
    }

    Translator const& tr;
    Predicates const& pred;
    OutIter out_iter;
    size_t found_count;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_VISITORS_SPATIAL_QUERY_HPP
