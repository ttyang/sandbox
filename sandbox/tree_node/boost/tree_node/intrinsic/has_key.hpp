// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_INTRINSIC_HAS_KEY_HPP_INCLUDED
#define BOOST_TREE_NODE_INTRINSIC_HAS_KEY_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/tr1/type_traits.hpp>

namespace boost { namespace tree_node { namespace result_of {

    template <typename Node, typename Key>
    struct has_key : ::std::tr1::is_base_of<Key,Node>
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(2,has_key,(Node,Key))
    };
}}}  // namespace boost::tree_node::result_of
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//[reference__tree_node__result_of__has_key
namespace boost { namespace tree_node { namespace result_of {

    template <typename Node, typename Key>
    struct has_key_impl : has_key_impl<typename Node::super_t,Key>
    {
    };

    template <typename Key>
    struct has_key_impl<void,Key> : ::boost::mpl::false_
    {
    };

    template <typename Node, typename Key>
    struct has_key : has_key_impl<Node,Key>::type
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(2,has_key,(Node,Key))
    };
}}}  // namespace boost::tree_node::result_of
//]
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__tree_node__has_key
namespace boost { namespace tree_node {

    template <typename Key, typename Node>
    typename result_of::has_key<Node,Key>::type has_key(Node const& node);

    template <typename Key, typename Node>
    inline typename result_of::has_key<Node,Key>::type has_key(Node const&)
    {
        return typename result_of::has_key<Node,Key>::type();
    }
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_INTRINSIC_HAS_KEY_HPP_INCLUDED

