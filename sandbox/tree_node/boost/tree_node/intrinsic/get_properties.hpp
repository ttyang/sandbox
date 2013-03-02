// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_INTRINSIC_GET_PROPERTIES_HPP_INCLUDED
#define BOOST_TREE_NODE_INTRINSIC_GET_PROPERTIES_HPP_INCLUDED

#include <boost/tree_node/preprocessor.hpp>

#if !defined BOOST_TREE_NODE_CAN_USE_FUSION
#error This component requires working Boost.Fusion.
#endif

#include <boost/fusion/support/pair.hpp>
#include <boost/tree_node/intrinsic/at_key.hpp>

namespace boost { namespace tree_node { namespace _detail {

    template <typename Node>
    class fused_val_function
    {
        Node& _node;

     public:
        template <typename T>
        struct result;

        template <typename Key>
        struct result<fused_val_function(Key)>
        {
            typedef typename ::boost::fusion::result_of::make_pair<
                        Key
                      , typename ::boost::tree_node::result_of::at_key<
                            Node
                          , Key
                        >::type
                    >::type
                    type;
        };

        explicit fused_val_function(Node& node);

        template <typename Key>
        typename result<fused_val_function(Key)>::type operator()(Key) const;
    };

    template <typename Node>
    fused_val_function<Node>::fused_val_function(Node& node) : _node(node)
    {
    }

    template <typename Node>
    template <typename Key>
    inline typename fused_val_function<
        Node
    >::BOOST_NESTED_TEMPLATE result<fused_val_function<Node>(Key)>::type
        fused_val_function<Node>::operator()(Key) const
    {
        return ::boost::fusion::make_pair<Key>(get<Key>(_node));
    }
}}}  // namespace boost::tree_node::_detail

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/tree_node/intrinsic/get_keys.hpp>

//[reference__result_of__get_properties
namespace boost { namespace tree_node { namespace result_of {

    template <typename Node>
    struct get_properties
    {
//<-
#if 0
//->
        typedef unspecified type;
//<-
#endif
        typedef ::boost::fusion::transform_view<
                    typename get_keys<
                        typename ::std::tr1::remove_const<Node>::type
                    >::type const
                  , ::boost::tree_node::_detail::fused_val_function<Node>
                >
                type;

        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,get_properties,(Node))
//->
    };
}}}  // namespace boost::tree_node::result_of
//]

//[reference__get_properties
namespace boost { namespace tree_node {

    template <typename Node>
    typename result_of::get_properties<Node const>::type
        get_properties(Node const& node);

    //<-
    template <typename Node>
    inline typename result_of::get_properties<Node const>::type
        get_properties(Node const& node)
    {
        typedef ::boost::tree_node::_detail::fused_val_function<Node const> F;
        typedef typename result_of::get_keys<Node>::type Keys;

        return ::boost::fusion::transform_view<Keys const,F>(Keys(), F(node));
    }
    //->

    template <typename Node>
    typename result_of::get_properties<Node>::type
        get_properties(Node& node);

    //<-
    template <typename Node>
    inline typename result_of::get_properties<Node>::type
        get_properties(Node& node)
    {
        typedef ::boost::tree_node::_detail::fused_val_function<Node> F;
        typedef typename result_of::get_keys<Node>::type Keys;

        return ::boost::fusion::transform_view<Keys const,F>(Keys(), F(node));
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_INTRINSIC_GET_PROPERTIES_HPP_INCLUDED

