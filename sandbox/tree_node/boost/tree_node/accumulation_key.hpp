// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ACCUMULATION_KEY_HPP_INCLUDED
#define BOOST_TREE_NODE_ACCUMULATION_KEY_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/tree_node/data_key.hpp>

//[reference__accumulation_key
namespace boost { namespace tree_node {

    template <
        typename Key = data_key
      , typename Tag = ::boost::accumulators::tag::sum
      , typename IncludesAllDescendants = ::boost::mpl::true_
      , typename IncludesRoot = ::boost::mpl::true_
      , typename Value = void
    >
    struct accumulation_key
    {
        typedef Key key;
        typedef Tag tag;
        typedef IncludesAllDescendants includes_all_descendants;
        typedef IncludesRoot includes_root;
        typedef Value value;
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ACCUMULATION_KEY_HPP_INCLUDED

