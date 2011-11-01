// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_SHARED_BASE_HPP_INCLUDED
#define BOOST_TREE_NODE_SHARED_BASE_HPP_INCLUDED

#include <boost/detail/base_pointee_shared.hpp>

//[reference__shared_tree_node_base
namespace boost { namespace tree_node {

    template <typename Derived>
    struct shared_tree_node_base
        //<-
      : public ::boost::detail::base_pointee_shared<Derived>
        //->
    {
        typedef // implementation_defined
                //<-
                typename ::boost::detail::base_pointee_shared<
                    Derived
                >::pointer
                //->
                pointer;
        typedef // implementation_defined
                //<-
                typename ::boost::detail::base_pointee_shared<
                    Derived
                >::const_pointer
                //->
                const_pointer;

     protected:
        void shallow_update_impl();

        void deep_update_impl();

        void shallow_update_derived();

        void deep_update_derived();
    };

    //<-
    template <typename Derived>
    inline void shared_tree_node_base<Derived>::shallow_update_impl()
    {
    }

    template <typename Derived>
    inline void shared_tree_node_base<Derived>::deep_update_impl()
    {
    }

    template <typename Derived>
    inline void shared_tree_node_base<Derived>::shallow_update_derived()
    {
        this->get_derived()->shallow_update_impl();
    }

    template <typename Derived>
    inline void shared_tree_node_base<Derived>::deep_update_derived()
    {
        this->get_derived()->deep_update_impl();
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_SHARED_BASE_HPP_INCLUDED

