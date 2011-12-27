// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BASE_HPP_INCLUDED
#define BOOST_TREE_NODE_BASE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/detail/base_pointee.hpp>

//[reference__tree_node_base
namespace boost { namespace tree_node {

    template <typename Derived>
    struct tree_node_base
        //<-
      : public ::boost::detail::base_pointee<Derived>
        //->
    {
        typedef // implementation_defined
                //<-
                typename ::boost::detail::base_pointee<Derived>::pointer
                //->
                pointer;
        typedef // implementation_defined
                //<-
                typename ::boost::detail::base_pointee<Derived>::const_pointer
                //->
                const_pointer;

     protected:
        void shallow_update_impl();

        void deep_update_impl();

        template <typename Iterator>
        void set_position_impl(Iterator position, ::boost::mpl::true_);

        template <typename Iterator>
        void set_position_impl(Iterator position, ::boost::mpl::false_);

        void shallow_update_derived();

        void deep_update_derived();

        template <typename Iterator, typename BooleanIntegralConstant>
        void
            set_position_derived(
                Iterator position
              , BooleanIntegralConstant invalidates_sibling_positions
            );
    };

    //<-
    template <typename Derived>
    inline void tree_node_base<Derived>::shallow_update_impl()
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::deep_update_impl()
    {
    }

    template <typename Derived>
    template <typename Iterator>
    inline void
        tree_node_base<Derived>::set_position_impl(
            Iterator position
          , ::boost::mpl::true_
        )
    {
    }

    template <typename Derived>
    template <typename Iterator>
    inline void
        tree_node_base<Derived>::set_position_impl(
            Iterator position
          , ::boost::mpl::false_
        )
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::shallow_update_derived()
    {
        this->get_derived()->shallow_update_impl();
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::deep_update_derived()
    {
        this->get_derived()->deep_update_impl();
    }

    template <typename Derived>
    template <typename Iterator, typename BooleanIntegralConstant>
    inline void
        tree_node_base<Derived>::set_position_derived(
            Iterator position
          , BooleanIntegralConstant invalidates_sibling_positions
        )
    {
        this->get_derived()->set_position_impl(
            position
          , invalidates_sibling_positions
        );
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_BASE_HPP_INCLUDED

