// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_INTRINSIC_AT_KEY_HPP_INCLUDED
#define BOOST_TREE_NODE_INTRINSIC_AT_KEY_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/utility/get_reference.hpp>

//[reference__tree_node__result_of__at_key
namespace boost { namespace tree_node { namespace result_of {

    template <typename Key>
    struct at_key_impl
    {
        template <typename Node>
        struct apply
        {
            typedef BOOST_TYPEOF_TPL(get<Key>(::boost::get_reference<Node>()))
                    type;
        };
    };

    template <typename Node, typename Key>
    struct at_key : ::boost::mpl::apply_wrap1<at_key_impl<Key>,Node>
    {
        BOOST_MPL_AUX_LAMBDA_SUPPORT(2,at_key,(Node,Key))
    };
}}}  // namespace boost::tree_node::result_of
//]

#endif  // BOOST_TREE_NODE_INTRINSIC_AT_KEY_HPP_INCLUDED

