// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_KEY_ACCUMULATION_HPP
#define BOOST_TREE_NODE_KEY_ACCUMULATION_HPP

#include <boost/config.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#error boost::tree_node::with_accumulation uses Boost.Accumulators,
#error which requires working partial template specialization.
#endif

#include <boost/mpl/bool.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/tree_node/key/data.hpp>

//[reference__accumulation_key
namespace boost { namespace tree_node {

    //<-
    struct accumulation_key_base
    {
    };
    //->

    template <
        typename Key = data_key
      , typename Tag = ::boost::accumulators::tag::sum
      , typename IncludesAllDescendants = ::boost::mpl::true_
      , typename IncludesRoot = ::boost::mpl::true_
      , typename Value = void
    >
    struct accumulation_key
    //<-
      : accumulation_key_base
    //->
    {
        typedef Key key;
        typedef Tag tag;
        typedef IncludesAllDescendants includes_all_descendants;
        typedef IncludesRoot includes_root;
        typedef Value value;
    };

    typedef accumulation_key<> default_accumulation_key;
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_KEY_ACCUMULATION_HPP

