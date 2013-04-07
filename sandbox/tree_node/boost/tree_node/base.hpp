// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BASE_HPP_INCLUDED
#define BOOST_TREE_NODE_BASE_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/detail/base_pointee.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/move/move.hpp>
#endif

namespace boost { namespace tree_node {

    template <typename Derived>
    struct tree_node_base
      : public ::boost::detail::base_pointee<Derived>
    {
        typedef typename ::boost::detail::base_pointee<Derived>::pointer
                pointer;
        typedef typename ::boost::detail::base_pointee<Derived>::const_pointer
                const_pointer;
        typedef void
                super_t;

     protected:
        ~tree_node_base();

        //[reference__tree_node_base__clone_metadata_impl
        void clone_metadata_impl(Derived const& copy);
        //]

        //[reference__tree_node_base__clone_metadata
        void clone_metadata(Derived const& copy);
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined BOOST_NO_RVALUE_REFERENCES
        void move_metadata_impl(::boost::rv<Derived>& source);

        void move_metadata(::boost::rv<Derived>& source);
#else  // !defined BOOST_NO_RVALUE_REFERENCES
        //[reference__tree_node_base__move_metadata_impl
        void move_metadata_impl(Derived&& source);
        //]

        //[reference__tree_node_base__move_metadata
        void move_metadata(Derived&& source);
        //]
#endif  // BOOST_NO_RVALUE_REFERENCES
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

        //[reference__tree_node_base__on_post_emplacement_construct
        void on_post_emplacement_construct();
        //]

        //[reference__tree_node_base__on_post_copy_or_move_impl
        void on_post_copy_or_move_impl();
        //]

        //[reference__tree_node_base__on_post_copy_or_move
        void on_post_copy_or_move();
        //]

        //[reference__tree_node_base__on_post_modify_value_impl
        template <typename Key>
        void on_post_modify_value_impl(Key const& key);
        //]

        //[reference__tree_node_base__on_post_modify_value
        template <typename Key>
        void on_post_modify_value(Key const& key);
        //]

        //[reference__tree_node_base__on_post_propagate_value_impl
        template <typename Key>
        void on_post_propagate_value_impl(Key const& key);
        //]

        //[reference__tree_node_base__on_post_propagate_value
        template <typename Key>
        void on_post_propagate_value(Key const& key);
        //]

        //[reference__tree_node_base__on_post_propagate_value_once_impl
        template <typename Key>
        void on_post_propagate_value_once_impl(Key const& key);
        //]

        //[reference__tree_node_base__on_post_propagate_value_once
        template <typename Key>
        void on_post_propagate_value_once(Key const& key);
        //]

        //[reference__tree_node_base__on_post_inserted_impl__true
        template <typename Iterator>
        void on_post_inserted_impl(Iterator position, ::boost::mpl::true_);
        //]

        //[reference__tree_node_base__on_post_inserted_impl__false
        template <typename Iterator>
        void on_post_inserted_impl(Iterator position, ::boost::mpl::false_);
        //]

        //[reference__tree_node_base__on_post_inserted
        template <typename Iterator, typename BooleanIntegralConstant>
        void
            on_post_inserted(
                Iterator position
              , BooleanIntegralConstant invalidates_sibling_positions
            );
        //]

        //[reference__tree_node_base__on_post_insert_impl__true
        template <typename Iterator>
        void
            on_post_insert_impl(
                Iterator itr
              , Iterator itr_end
              , ::boost::mpl::true_
            );
        //]

        //[reference__tree_node_base__on_post_insert_impl__false
        template <typename Iterator>
        void
            on_post_insert_impl(
                Iterator itr
              , Iterator itr_end
              , ::boost::mpl::false_
            );
        //]

        //[reference__tree_node_base__on_post_insert
        template <typename Iterator, typename BooleanIntegralConstant>
        void
            on_post_insert(
                Iterator itr
              , Iterator itr_end
              , BooleanIntegralConstant invalidates_children_positions
            );
        //]

        //[reference__tree_node_base__on_post_erase_impl
        void on_post_erase_impl();
        //]

        //[reference__tree_node_base__on_post_erase
        void on_post_erase();
        //]

        //[reference__tree_node_base__on_post_clear_impl
        void on_post_clear_impl();
        //]

        //[reference__tree_node_base__on_post_clear
        void on_post_clear();
        //]

        //[reference__tree_node_base__on_post_rotate_left_impl
        void on_post_rotate_left_impl();
        //]

        //[reference__tree_node_base__on_post_rotate_left
        void on_post_rotate_left();
        //]

        //[reference__tree_node_base__on_post_rotate_right_impl
        void on_post_rotate_right_impl();
        //]

        //[reference__tree_node_base__on_post_rotate_right
        void on_post_rotate_right();
        //]
    };

    template <typename Derived>
    tree_node_base<Derived>::~tree_node_base()
    {
    }

    template <typename Derived>
    inline void
        tree_node_base<Derived>::clone_metadata_impl(Derived const& copy)
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::clone_metadata(Derived const& copy)
    {
        this->get_derived()->clone_metadata_impl(copy);
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined BOOST_NO_RVALUE_REFERENCES
    template <typename Derived>
    inline void
        tree_node_base<Derived>::move_metadata_impl(
            ::boost::rv<Derived>& source
        )
    {
    }

    template <typename Derived>
    inline void
        tree_node_base<Derived>::move_metadata(::boost::rv<Derived>& source)
    {
        this->get_derived()->move_metadata_impl(source);
    }
#else  // !defined BOOST_NO_RVALUE_REFERENCES
    template <typename Derived>
    inline void tree_node_base<Derived>::move_metadata_impl(Derived&& source)
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::move_metadata(Derived&& source)
    {
        this->get_derived()->move_metadata_impl(
            static_cast<Derived&&>(source)
        );
    }
#endif  // BOOST_NO_RVALUE_REFERENCES
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_emplacement_construct()
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_copy_or_move_impl()
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_copy_or_move()
    {
        this->get_derived()->on_post_copy_or_move_impl();
    }

    template <typename Derived>
    template <typename Key>
    inline void tree_node_base<Derived>::on_post_modify_value_impl(Key const&)
    {
    }

    template <typename Derived>
    template <typename Key>
    inline void tree_node_base<Derived>::on_post_modify_value(Key const& key)
    {
        this->get_derived()->on_post_modify_value_impl(key);
    }

    template <typename Derived>
    template <typename Key>
    inline void
        tree_node_base<Derived>::on_post_propagate_value_impl(Key const&)
    {
    }

    template <typename Derived>
    template <typename Key>
    inline void
        tree_node_base<Derived>::on_post_propagate_value(Key const& key)
    {
        this->get_derived()->on_post_propagate_value_impl(key);
    }

    template <typename Derived>
    template <typename Key>
    inline void
        tree_node_base<Derived>::on_post_propagate_value_once_impl(Key const&)
    {
    }

    template <typename Derived>
    template <typename Key>
    inline void
        tree_node_base<Derived>::on_post_propagate_value_once(Key const& key)
    {
        this->get_derived()->on_post_propagate_value_once_impl(key);
    }

    template <typename Derived>
    template <typename Iterator>
    inline void
        tree_node_base<Derived>::on_post_inserted_impl(
            Iterator position
          , ::boost::mpl::true_
        )
    {
    }

    template <typename Derived>
    template <typename Iterator>
    inline void
        tree_node_base<Derived>::on_post_inserted_impl(
            Iterator position
          , ::boost::mpl::false_
        )
    {
    }

    template <typename Derived>
    template <typename Iterator, typename BooleanIntegralConstant>
    inline void
        tree_node_base<Derived>::on_post_inserted(
            Iterator position
          , BooleanIntegralConstant invalidates_sibling_positions
        )
    {
        this->get_derived()->on_post_inserted_impl(
            position
          , invalidates_sibling_positions
        );
    }

    template <typename Derived>
    template <typename Iterator>
    inline void
        tree_node_base<Derived>::on_post_insert_impl(
            Iterator itr
          , Iterator itr_end
          , ::boost::mpl::true_
        )
    {
    }

    template <typename Derived>
    template <typename Iterator>
    inline void
        tree_node_base<Derived>::on_post_insert_impl(
            Iterator itr
          , Iterator itr_end
          , ::boost::mpl::false_
        )
    {
    }

    template <typename Derived>
    template <typename Iterator, typename BooleanIntegralConstant>
    inline void
        tree_node_base<Derived>::on_post_insert(
            Iterator itr
          , Iterator itr_end
          , BooleanIntegralConstant invalidates_children_positions
        )
    {
        this->get_derived()->on_post_insert_impl(
            itr
          , itr_end
          , invalidates_children_positions
        );
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_erase_impl()
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_erase()
    {
        this->get_derived()->on_post_erase_impl();
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_clear_impl()
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_clear()
    {
        this->get_derived()->on_post_clear_impl();
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_rotate_left_impl()
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_rotate_left()
    {
        this->get_derived()->on_post_rotate_left_impl();
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_rotate_right_impl()
    {
    }

    template <typename Derived>
    inline void tree_node_base<Derived>::on_post_rotate_right()
    {
        this->get_derived()->on_post_rotate_right_impl();
    }
}}  // namespace boost::tree_node

#endif  // BOOST_TREE_NODE_BASE_HPP_INCLUDED

