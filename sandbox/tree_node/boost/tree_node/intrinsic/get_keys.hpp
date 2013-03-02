// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_INTRINSIC_GET_KEYS_HPP_INCLUDED
#define BOOST_TREE_NODE_INTRINSIC_GET_KEYS_HPP_INCLUDED

#include <boost/config.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/vector/vector0.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

//[reference__tree_node__result_of__get_keys
namespace boost { namespace tree_node { namespace result_of {

    template <typename Node>
    struct get_keys_impl
    {
        typedef ::boost::mpl::vector0<> type;
    };

    template <typename Node>
    class get_keys
    {
        typedef typename Node::super_t _base;

     public:
        typedef typename ::boost::mpl::joint_view<
                    typename get_keys_impl<Node>::type
                  , typename ::boost::mpl::eval_if<
                        ::std::tr1::is_void<_base>
                      , ::boost::mpl::vector0<>
                      , get_keys<_base>
                    >::type
                >::type
                type;

        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,get_keys,(Node))
    };
}}}  // namespace boost::tree_node::result_of
//]
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // BOOST_TREE_NODE_INTRINSIC_GET_KEYS_HPP_INCLUDED

