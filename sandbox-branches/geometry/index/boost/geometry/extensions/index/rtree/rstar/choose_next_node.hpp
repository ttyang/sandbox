// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Boost.Index - R*-tree ChooseNextNode algorithm
//
// Copyright 2011 Adam Wulkiewicz.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_RSTAR_CHOOSE_NEXT_NODE_HPP
#define BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_RSTAR_CHOOSE_NEXT_NODE_HPP

#include <algorithm>

#include <boost/geometry/algorithms/expand.hpp>

#include <boost/geometry/extensions/index/algorithms/content.hpp>
#include <boost/geometry/extensions/index/algorithms/overlap.hpp>
#include <boost/geometry/extensions/index/algorithms/union_content.hpp>

#include <boost/geometry/extensions/index/rtree/node/node.hpp>
#include <boost/geometry/extensions/index/rtree/visitors/is_leaf.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

namespace detail {

template <typename Value, typename Options, typename Box>
class choose_next_node<Value, Options, Box, choose_by_overlap_diff_tag>
{
    typedef typename rtree::node<Value, typename Options::parameters_type, Box, typename Options::node_tag>::type node;
    typedef typename rtree::internal_node<Value, typename Options::parameters_type, Box, typename Options::node_tag>::type internal_node;
    typedef typename rtree::leaf<Value, typename Options::parameters_type, Box, typename Options::node_tag>::type leaf;

    typedef typename rtree::elements_type<internal_node>::type children_type;
	typedef typename children_type::value_type child_type;

	typedef typename Options::parameters_type parameters_type;

    typedef typename index::default_content_result<Box>::type content_type;
    typedef typename index::default_overlap_result<Box>::type overlap_type;

public:
    template <typename Indexable>
    static inline size_t apply(internal_node & n, Indexable const& indexable, size_t node_relative_level)
    {
        children_type & children = rtree::elements(n);
        
        // children are leafs
        if ( node_relative_level <= 1 )
		{
			if ( 0 < parameters_type::overlap_cost_threshold &&
				 parameters_type::overlap_cost_threshold < children.size() )
				return choose_by_nearly_minimum_overlap_cost(children, indexable);
			else
				return choose_by_minimum_overlap_cost(children, indexable);
		}
        // children are internal nodes
        else
            return choose_by_minimum_content_cost(children, indexable);
    }

private:
    template <typename Indexable>
    static inline size_t choose_by_minimum_overlap_cost(children_type const& children, Indexable const& indexable)
    {
        size_t children_count = children.size();

        // choose index with smallest overlap change value, or content change or smallest content
        size_t choosen_index = 0;
        overlap_type smallest_overlap_diff = std::numeric_limits<overlap_type>::max();
        content_type smallest_content_diff = std::numeric_limits<content_type>::max();
        content_type smallest_content = std::numeric_limits<content_type>::max();

        // for each child node
        for (size_t i = 0 ; i < children_count ; ++i )
        {
            child_type const& ch_i = children[i];

            Box box_exp(ch_i.first);
            // calculate expanded box of child node ch_i
            geometry::expand(box_exp, indexable);

            // calculate content and content diff
            content_type content = index::content(ch_i.first);
            content_type content_diff = index::content(box_exp) - content;

            overlap_type overlap = 0;
            overlap_type overlap_exp = 0;

            // calculate overlap
            for ( size_t j = 0 ; j < children_count ; ++j )
            {
                if ( i != j )
                {
                    child_type const& ch_j = children[j];

                    overlap += index::overlap(ch_i.first, ch_j.first);
                    overlap_exp += index::overlap(box_exp, ch_j.first);
                }
            }

            overlap_type overlap_diff = overlap_exp - overlap;

            // update result
            if ( overlap_diff < smallest_overlap_diff ||
                 ( overlap_diff == smallest_overlap_diff && content_diff < smallest_content_diff ) ||
                 ( content_diff == smallest_content_diff && content < smallest_content ) )
            {
                smallest_overlap_diff = overlap_diff;
                smallest_content_diff = content_diff;
                smallest_content = content;
                choosen_index = i;
            }
        }

        return choosen_index;
    }

	template <typename Indexable>
	static inline size_t choose_by_nearly_minimum_overlap_cost(children_type const& children, Indexable const& indexable)
	{
		const size_t children_count = children.size();

		// create container of children sorted by content enlargement needed to include the new value
		std::vector< boost::tuple<size_t, content_type, content_type> > sorted_children(children_count);
		for ( size_t i = 0 ; i < children_count ; ++i )
		{
			child_type const& ch_i = children[i];

			// expanded child node's box
			Box box_exp(ch_i.first);
			geometry::expand(box_exp, indexable);

			// areas difference
			content_type content = index::content(box_exp);
			content_type content_diff = content - index::content(ch_i.first);

			sorted_children[i] = boost::make_tuple(i, content_diff, content);
		}

		// sort by content_diff
		std::sort(sorted_children.begin(), sorted_children.end(), content_diff_less);

		BOOST_GEOMETRY_INDEX_ASSERT(parameters_type::overlap_cost_threshold <= children_count, "there are not enough children");

		// for overlap_cost_threshold child nodes find the one with smallest overlap value
		size_t choosen_index = 0;
		overlap_type smallest_overlap_diff = std::numeric_limits<overlap_type>::max();

		// for each node
		for (size_t i = 0 ; i < parameters_type::overlap_cost_threshold ; ++i )
		{
			size_t child_index = boost::get<0>(sorted_children[i]);

			typedef typename children_type::value_type child_type;
			child_type const& ch_i = children[child_index];

			Box box_exp(ch_i.first);
			// calculate expanded box of child node ch_i
			geometry::expand(box_exp, indexable);

			overlap_type overlap = 0;
			overlap_type overlap_exp = 0;

			// calculate overlap
			for ( size_t j = 0 ; j < children_count ; ++j )
			{
				if ( child_index != j )
				{
					child_type const& ch_j = children[j];

					overlap += index::overlap(ch_i.first, ch_j.first);
					overlap_exp += index::overlap(box_exp, ch_j.first);
				}
			}

			overlap_type overlap_diff = overlap_exp - overlap;

			// update result
			if ( overlap_diff < smallest_overlap_diff )
			{
				smallest_overlap_diff = overlap_diff;
				choosen_index = child_index;
			}
		}

		return choosen_index;
	}

	static inline bool content_diff_less(boost::tuple<size_t, content_type, content_type> const& p1, boost::tuple<size_t, content_type, content_type> const& p2)
	{
		return boost::get<1>(p1) < boost::get<1>(p2) ||
			   (boost::get<1>(p1) == boost::get<1>(p2) && boost::get<2>(p1) < boost::get<2>(p2));
	}

	template <typename Indexable>
    static inline size_t choose_by_minimum_content_cost(children_type const& children, Indexable const& indexable)
    {
        size_t children_count = children.size();

        // choose index with smallest content change or smallest content
        size_t choosen_index = 0;
        content_type smallest_content_diff = std::numeric_limits<content_type>::max();
        content_type smallest_content = std::numeric_limits<content_type>::max();

        // choose the child which requires smallest box expansion to store the indexable
        for ( size_t i = 0 ; i < children_count ; ++i )
        {
            child_type const& ch_i = children[i];

            // expanded child node's box
            Box box_exp(ch_i.first);
            geometry::expand(box_exp, indexable);

            // areas difference
            content_type content = index::content(box_exp);
            content_type content_diff = content - index::content(ch_i.first);

            // update the result
            if ( content_diff < smallest_content_diff ||
                ( content_diff == smallest_content_diff && content < smallest_content ) )
            {
                smallest_content_diff = content_diff;
                smallest_content = content;
                choosen_index = i;
            }
        }

        return choosen_index;
    }
};

} // namespace detail

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_RSTAR_CHOOSE_NEXT_NODE_HPP
