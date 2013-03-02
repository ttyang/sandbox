// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_INTRINSIC_VALUE_AT_KEY_HPP_INCLUDED
#define BOOST_TREE_NODE_INTRINSIC_VALUE_AT_KEY_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/utility/get_reference.hpp>

//[reference__tree_node__result_of__value_at_key
namespace boost { namespace tree_node { namespace result_of {

    template <typename Node, typename Key>
    class value_at_key
    {
        typedef typename ::std::tr1::remove_const<Node>::type::super_t
                _base;

     public:
        typedef BOOST_TYPEOF_TPL(
                    get<Key>(
                        ::boost::get_reference<
                            typename ::boost::mpl::if_<
                                ::std::tr1::is_const<Node>
                              , _base const
                              , _base
                            >::type
                        >()
                    )
                )
                type;

        //<-
        BOOST_MPL_AUX_LAMBDA_SUPPORT(2,value_at_key,(Node,Key))
        //->
    };
}}}  // namespace boost::tree_node::result_of
//]

#endif  // BOOST_TREE_NODE_INTRINSIC_VALUE_AT_KEY_HPP_INCLUDED

