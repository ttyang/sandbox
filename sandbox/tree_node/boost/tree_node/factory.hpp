// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_FACTORY_HPP_INCLUDED
#define BOOST_TREE_NODE_FACTORY_HPP_INCLUDED

//[reference__factory
namespace boost { namespace tree_node {

    template <typename Node>
    struct factory
    {
        static typename Node::pointer create();

        static typename Node::pointer
            create(typename Node::traits::data_type const& data);
    };

    //<-
    template <typename Node>
    typename Node::pointer factory<Node>::create()
    {
        return typename Node::pointer(new Node());
    }

    template <typename Node>
    typename Node::pointer
        factory<Node>::create(typename Node::traits::data_type const& data)
    {
        return typename Node::pointer(new Node(data));
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_FACTORY_HPP_INCLUDED

