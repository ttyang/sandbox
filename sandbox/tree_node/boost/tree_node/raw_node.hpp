// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_RAW_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_RAW_NODE_HPP_INCLUDED

#include <utility>
#include <boost/mpl/bool.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/utility/container_gen.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/tree_node/factory.hpp>
#include <boost/detail/function/add_const_to_pointee.hpp>

//[reference__raw_node_base
namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Selector>
    class raw_node_base : public tree_node_base<Derived>
    {
     public:
        struct traits
        {
            typedef T data_type;
        };

        typedef typename tree_node_base<Derived>::pointer
                pointer;
        typedef typename tree_node_base<Derived>::const_pointer
                const_pointer;

        //<-
     private:
        typedef typename ::boost::container_gen<Selector,pointer>::type
                children;

     public:
        //->
        typedef // implementation_defined
                //<-
                typename children::iterator
                //->
                child_iterator;
        typedef // implementation_defined
                //<-
#if 0
// TODO:
// Fix crash that occurs on depth-first iteration
// when this code is used.
                ::boost::transform_iterator<
                    ::boost::detail::add_const_to_pointee<Derived>
                  , typename children::const_iterator
                >
#else
                typename children::const_iterator
#endif
                //->
                const_child_iterator;

        //<-
     private:
        children                   _children;
        pointer                    _parent;
        typename traits::data_type _data;

     public:
        //->
        raw_node_base();

        explicit raw_node_base(typename traits::data_type const& data);

        raw_node_base(raw_node_base const& copy);

        raw_node_base& operator=(raw_node_base const& copy);

        virtual ~raw_node_base();

        pointer clone() const;

        typename traits::data_type const& get_data() const;

        typename traits::data_type& get_data();

        const_pointer get_parent() const;

        pointer get_parent();

        pointer add_child(typename traits::data_type const& data);

        pointer add_child();

        pointer add_child_copy(const_pointer const& copy);

        const_child_iterator get_child_begin() const;

        child_iterator get_child_begin();

        const_child_iterator get_child_end() const;

        child_iterator get_child_end();

        void remove_all_children();

        //<-
     private:
        void _remove_all_children();

        void _add_child(pointer const& child);
        //->
    };

    //<-
    template <typename Derived, typename T, typename Selector>
    raw_node_base<Derived,T,Selector>::raw_node_base()
      : _children(), _parent(), _data()
    {
    }

    template <typename Derived, typename T, typename Selector>
    raw_node_base<Derived,T,Selector>::raw_node_base(
        typename traits::data_type const& data
    ) : _children(), _parent(), _data(data)
    {
    }

    template <typename Derived, typename T, typename Selector>
    raw_node_base<Derived,T,Selector>::raw_node_base(raw_node_base const& copy)
      : _children(), _parent(), _data(copy._data)
    {
        pointer p = this->get_derived();

        for (
            depth_first_iterator<const_pointer,::boost::mpl::true_> copy_itr(
                copy.get_derived()
            );
            copy_itr;
            ++copy_itr
        )
        {
            switch (traversal_state(copy_itr))
            {
                case pre_order_traversal:
                {
                    pointer child = ::boost::tree_node::factory<
                        Derived
                    >::create((*copy_itr)->get_data());

                    p->_add_child(child);
                    p = child;
                    break;
                }

                case post_order_traversal:
                {
                    p = p->_parent;
                    break;
                }
            }
        }

        this->deep_update_derived();
    }

    template <typename Derived, typename T, typename Selector>
    raw_node_base<Derived,T,Selector>&
        raw_node_base<Derived,T,Selector>::operator=(raw_node_base const& copy)
    {
        if (this != &copy)
        {
            raw_node_base temp_copy(copy);

            _remove_all_children();
            _children = temp_copy._children;
            _data = temp_copy._data;
            temp_copy._children.clear();

            child_iterator itr_end = get_child_end();

            for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
            {
                (*itr)->_parent = this->get_derived();
            }

            this->shallow_update_derived();
        }

        return *this;
    }

    template <typename Derived, typename T, typename Selector>
    raw_node_base<Derived,T,Selector>::~raw_node_base()
    {
        _remove_all_children();
    }

    template <typename Derived, typename T, typename Selector>
    typename raw_node_base<Derived,T,Selector>::pointer
        raw_node_base<Derived,T,Selector>::clone() const
    {
        pointer result = ::boost::tree_node::factory<Derived>::create(_data);
        pointer p = result;

        for (
            depth_first_iterator<const_pointer,::boost::mpl::true_> copy_itr(
                this->get_derived()
            );
            copy_itr;
            ++copy_itr
        )
        {
            switch (traversal_state(copy_itr))
            {
                case pre_order_traversal:
                {
                    pointer child = ::boost::tree_node::factory<
                        Derived
                    >::create((*copy_itr)->get_data());

                    p->_add_child(child);
                    p = child;
                    break;
                }

                case post_order_traversal:
                {
                    p = p->_parent;
                    break;
                }
            }
        }

        result->deep_update_derived();
        return result;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::traits::data_type const&
        raw_node_base<Derived,T,Selector>::get_data() const
    {
        return _data;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::traits::data_type&
        raw_node_base<Derived,T,Selector>::get_data()
    {
        return _data;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::const_pointer
        raw_node_base<Derived,T,Selector>::get_parent() const
    {
        return _parent;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::pointer
        raw_node_base<Derived,T,Selector>::get_parent()
    {
        return _parent;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::pointer
        raw_node_base<Derived,T,Selector>::add_child(
            typename traits::data_type const& data
        )
    {
        pointer child = ::boost::tree_node::factory<Derived>::create(data);

        _add_child(child);
        this->shallow_update_derived();
        return child;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::pointer
        raw_node_base<Derived,T,Selector>::add_child()
    {
        pointer child = ::boost::tree_node::factory<Derived>::create();

        _add_child(child);
        this->shallow_update_derived();
        return child;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::pointer
        raw_node_base<Derived,T,Selector>::add_child_copy(
            const_pointer const& copy
        )
    {
        pointer child = copy->clone();

        _add_child(child);
        this->shallow_update_derived();
        return child;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::const_child_iterator
        raw_node_base<Derived,T,Selector>::get_child_begin() const
    {
        return const_child_iterator(_children.begin());
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::child_iterator
        raw_node_base<Derived,T,Selector>::get_child_begin()
    {
        return _children.begin();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::const_child_iterator
        raw_node_base<Derived,T,Selector>::get_child_end() const
    {
        return const_child_iterator(_children.end());
    }

    template <typename Derived, typename T, typename Selector>
    inline typename raw_node_base<Derived,T,Selector>::child_iterator
        raw_node_base<Derived,T,Selector>::get_child_end()
    {
        return _children.end();
    }

    template <typename Derived, typename T, typename Selector>
    inline void raw_node_base<Derived,T,Selector>::remove_all_children()
    {
        _remove_all_children();
        this->shallow_update_derived();
    }

    template <typename Derived, typename T, typename Selector>
    void raw_node_base<Derived,T,Selector>::_remove_all_children()
    {
        child_iterator itr_end = get_child_end();

        for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
        {
            delete *itr;
        }

        _children.clear();
    }

    template <typename Derived, typename T, typename Selector>
    inline void
        raw_node_base<Derived,T,Selector>::_add_child(pointer const& child)
    {
        child->_parent = this->get_derived();
        _children.insert(_children.end(), child);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__raw_node
namespace boost { namespace tree_node {

    template <typename T, typename Selector = ::boost::dequeS>
    class raw_node : public raw_node_base<raw_node<T,Selector>,T,Selector>
    {
        typedef raw_node_base<raw_node,T,Selector> super_t;

     public:
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::child_iterator child_iterator;
        typedef typename super_t::const_child_iterator const_child_iterator;

        raw_node();

        explicit raw_node(typename traits::data_type const& data);
    };

    //<-
    template <typename T, typename Selector>
    raw_node<T,Selector>::raw_node() : super_t()
    {
    }

    template <typename T, typename Selector>
    raw_node<T,Selector>::raw_node(typename traits::data_type const& data)
      : super_t(data)
    {
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__raw_node_gen
namespace boost { namespace tree_node {

    template <typename Selector = ::boost::dequeS>
    struct raw_node_gen
    {
        template <typename Derived, typename T>
        struct apply
        {
            typedef raw_node_base<Derived,T,Selector> type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_RAW_NODE_HPP_INCLUDED

