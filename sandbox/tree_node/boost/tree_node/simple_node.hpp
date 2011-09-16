// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_SIMPLE_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_SIMPLE_NODE_HPP_INCLUDED

#include <deque>
#include <boost/mpl/bool.hpp>
#include <boost/noncopyable.hpp>
#include <boost/tr1/memory.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>

//[reference__simple_node
namespace boost { namespace tree_node {

    template <typename T>
    class simple_node
      : public ::std::tr1::enable_shared_from_this<simple_node<T> >
      , private noncopyable
    {
     public:
        typedef T
                data_type;
        typedef ::std::tr1::shared_ptr<simple_node>
                pointer;
        typedef ::std::tr1::shared_ptr<simple_node const>
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
        children                          _children;
        ::std::tr1::weak_ptr<simple_node> _parent;
        data_type                         _data;

        simple_node();

        explicit simple_node(data_type const& data);

     public:
        //->
        ~simple_node();

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

        static pointer create(data_type const& data);

        static pointer create();

        static pointer create_copy(const_pointer const& p);
    };

    //<-
    template <typename T>
    simple_node<T>::simple_node() : _children(), _parent(), _data()
    {
    }

    template <typename T>
    simple_node<T>::simple_node(data_type const& data)
      : _children(), _parent(), _data(data)
    {
    }

    template <typename T>
    simple_node<T>::~simple_node()
    {
        remove_all_children();
        _parent.reset();
    }

    template <typename T>
    inline typename simple_node<T>::data_type const&
        simple_node<T>::get_data() const
    {
        return _data;
    }

    template <typename T>
    inline typename simple_node<T>::data_type& simple_node<T>::get_data()
    {
        return _data;
    }

    template <typename T>
    inline typename simple_node<T>::const_pointer
        simple_node<T>::get_parent() const
    {
        return const_pointer(_parent.lock());
    }

    template <typename T>
    inline typename simple_node<T>::pointer simple_node<T>::get_parent()
    {
        return pointer(_parent.lock());
    }

    template <typename T>
    inline typename simple_node<T>::pointer
        simple_node<T>::add_child(data_type const& data)
    {
        pointer child(new simple_node(data));

        child->_parent = this->shared_from_this();
        _children.push_back(child);
        return child;
    }

    template <typename T>
    inline typename simple_node<T>::pointer simple_node<T>::add_child()
    {
        pointer child(new simple_node<T>());

        child->_parent = this->shared_from_this();
        _children.push_back(child);
        return child;
    }

    template <typename T>
    inline typename simple_node<T>::pointer
        simple_node<T>::add_child_copy(const_pointer const& copy)
    {
        pointer child(create_copy(copy));

        child->_parent = this->shared_from_this();
        _children.push_back(child);
        return child;
    }

    template <typename T>
    inline typename simple_node<T>::const_child_iterator
        simple_node<T>::get_child_begin() const
    {
        return _children.begin();
    }

    template <typename T>
    inline typename simple_node<T>::child_iterator
        simple_node<T>::get_child_begin()
    {
        return _children.begin();
    }

    template <typename T>
    inline typename simple_node<T>::const_child_iterator
        simple_node<T>::get_child_end() const
    {
        return _children.end();
    }

    template <typename T>
    inline typename simple_node<T>::child_iterator
        simple_node<T>::get_child_end()
    {
        return _children.end();
    }

    template <typename T>
    void simple_node<T>::remove_all_children()
    {
        child_iterator itr_end = get_child_end();

        for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
        {
            (*itr)->remove_all_children();
            (*itr)->_parent.reset();
        }

        _children.clear();
    }

    template <typename T>
    inline typename simple_node<T>::pointer
        simple_node<T>::create(data_type const& data)
    {
        return pointer(new simple_node(data));
    }

    template <typename T>
    inline typename simple_node<T>::pointer simple_node<T>::create()
    {
        return pointer(new simple_node());
    }

    template <typename T>
    typename simple_node<T>::pointer
        simple_node<T>::create_copy(const_pointer const& copy)
    {
        pointer result(new simple_node(copy->get_data()));
        pointer p(result);

        for (
            depth_first_iterator<const_pointer,::boost::mpl::true_> copy_itr(
                copy
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
                    p = p->get_parent();
                    break;
                }
            }
        }

        return result;
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_SIMPLE_NODE_HPP_INCLUDED

