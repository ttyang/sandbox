// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_RAW_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_RAW_NODE_HPP_INCLUDED

#include <deque>
#include <boost/mpl/bool.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>

//[reference__raw_node
namespace boost { namespace tree_node {

    template <typename T>
    class raw_node
    {
     public:
        typedef T
                data_type;
        typedef raw_node*
                pointer;
        typedef raw_node const*
                const_pointer;

        //<-
     private:
        typedef ::std::deque<pointer>
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
                typename children::const_iterator
                //->
                const_child_iterator;

        //<-
     private:
        children  _children;
        pointer   _parent;
        data_type _data;

        raw_node(data_type const& data, pointer const& parent);

        explicit raw_node(pointer const& parent);

     public:
        //->
        raw_node();

        explicit raw_node(data_type const& data);

        raw_node(raw_node const& copy);

        raw_node& operator=(raw_node const& copy);

        ~raw_node();

        data_type const& get_data() const;

        data_type& get_data();

        const_pointer get_parent() const;

        pointer get_parent();

        pointer add_child(data_type const& data);

        pointer add_child();

        pointer add_child_copy(const_pointer const& copy);

        const_child_iterator get_child_begin() const;

        child_iterator get_child_begin();

        const_child_iterator get_child_end() const;

        child_iterator get_child_end();

        void remove_all_children();
    };

    //<-
    template <typename T>
    raw_node<T>::raw_node(data_type const& data, pointer const& parent)
      : _children(), _parent(parent), _data(data)
    {
        if (parent)
        {
            parent->_children.push_back(this);
        }
    }

    template <typename T>
    raw_node<T>::raw_node(pointer const& parent)
      : _children(), _parent(parent), _data()
    {
        if (parent)
        {
            parent->_children.push_back(this);
        }
    }

    template <typename T>
    raw_node<T>::raw_node() : _children(), _parent(), _data()
    {
    }

    template <typename T>
    raw_node<T>::raw_node(data_type const& data)
      : _children(), _parent(), _data(data)
    {
    }

    template <typename T>
    raw_node<T>::raw_node(raw_node const& copy)
      : _children(), _parent(), _data(copy._data)
    {
        pointer p = this;

        for (
            depth_first_iterator<const_pointer,::boost::mpl::true_> copy_itr(
                &copy
            );
            copy_itr;
            ++copy_itr
        )
        {
            switch (traversal_state(copy_itr))
            {
                case pre_order_traversal:
                {
                    p = p->add_child((*copy_itr)->get_data());
                    break;
                }

                case post_order_traversal:
                {
                    p = p->_parent;
                    break;
                }
            }
        }
    }

    template <typename T>
    raw_node<T>& raw_node<T>::operator=(raw_node const& copy)
    {
        if (this != &copy)
        {
            raw_node temp_copy(copy);

            remove_all_children();
            _children = temp_copy._children;
            _data = temp_copy._data;
            temp_copy._children.clear();

            child_iterator itr_end = get_child_end();

            for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
            {
                (*itr)->_parent = this;
            }
        }

        return *this;
    }

    template <typename T>
    raw_node<T>::~raw_node()
    {
        remove_all_children();
    }

    template <typename T>
    inline typename raw_node<T>::data_type const& raw_node<T>::get_data() const
    {
        return _data;
    }

    template <typename T>
    inline typename raw_node<T>::data_type& raw_node<T>::get_data()
    {
        return _data;
    }

    template <typename T>
    inline typename raw_node<T>::const_pointer raw_node<T>::get_parent() const
    {
        return _parent;
    }

    template <typename T>
    inline typename raw_node<T>::pointer raw_node<T>::get_parent()
    {
        return _parent;
    }

    template <typename T>
    inline typename raw_node<T>::pointer
        raw_node<T>::add_child(data_type const& data)
    {
        return new raw_node(data, this);
    }

    template <typename T>
    inline typename raw_node<T>::pointer raw_node<T>::add_child()
    {
        return new raw_node(this);
    }

    template <typename T>
    inline typename raw_node<T>::pointer
        raw_node<T>::add_child_copy(const_pointer const& copy)
    {
        pointer child = new raw_node(*copy);

        child->_parent = this;
        _children.push_back(child);
        return child;
    }

    template <typename T>
    inline typename raw_node<T>::const_child_iterator
        raw_node<T>::get_child_begin() const
    {
        return _children.begin();
    }

    template <typename T>
    inline typename raw_node<T>::child_iterator
        raw_node<T>::get_child_begin()
    {
        return _children.begin();
    }

    template <typename T>
    inline typename raw_node<T>::const_child_iterator
        raw_node<T>::get_child_end() const
    {
        return _children.end();
    }

    template <typename T>
    inline typename raw_node<T>::child_iterator
        raw_node<T>::get_child_end()
    {
        return _children.end();
    }

    template <typename T>
    void raw_node<T>::remove_all_children()
    {
        child_iterator itr_end = get_child_end();

        for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
        {
            delete *itr;
        }

        _children.clear();
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_RAW_NODE_HPP_INCLUDED

