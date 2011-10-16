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
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/detail/function/add_const_to_pointee.hpp>

//[reference__raw_node
namespace boost { namespace tree_node {

    template <typename T, typename Selector = ::boost::dequeS>
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
// when this code is is used.
                ::boost::transform_iterator<
                    ::boost::detail::add_const_to_pointee<raw_node>
                  , typename children::const_iterator
                >
#else
                typename children::const_iterator
#endif
                //->
                const_child_iterator;

        //<-
     private:
        children  _children;
        pointer   _parent;
        data_type _data;

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

        std::pair<const_child_iterator,const_child_iterator>
            get_children() const;

        std::pair<child_iterator,child_iterator>
            get_children();

        void remove_all_children();

        //<-
     private:
        void _add_child(pointer const& child);
        //->
    };

    //<-
    template <typename T, typename Selector>
    raw_node<T,Selector>::raw_node() : _children(), _parent(), _data()
    {
    }

    template <typename T, typename Selector>
    raw_node<T,Selector>::raw_node(data_type const& data)
      : _children(), _parent(), _data(data)
    {
    }

    template <typename T, typename Selector>
    raw_node<T,Selector>::raw_node(raw_node const& copy)
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

    template <typename T, typename Selector>
    raw_node<T,Selector>& raw_node<T,Selector>::operator=(raw_node const& copy)
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

    template <typename T, typename Selector>
    raw_node<T,Selector>::~raw_node()
    {
        remove_all_children();
    }

    template <typename T, typename Selector>
    inline typename raw_node<T,Selector>::data_type const&
        raw_node<T,Selector>::get_data() const
    {
        return _data;
    }

    template <typename T, typename Selector>
    inline typename raw_node<T,Selector>::data_type&
        raw_node<T,Selector>::get_data()
    {
        return _data;
    }

    template <typename T, typename Selector>
    inline typename raw_node<T,Selector>::const_pointer
        raw_node<T,Selector>::get_parent() const
    {
        return _parent;
    }

    template <typename T, typename Selector>
    inline typename raw_node<T,Selector>::pointer
        raw_node<T,Selector>::get_parent()
    {
        return _parent;
    }

    template <typename T, typename Selector>
    typename raw_node<T,Selector>::pointer
        raw_node<T,Selector>::add_child(data_type const& data)
    {
        pointer child = new raw_node(data);

        child->_parent = this;
        _add_child(child);
        return child;
    }

    template <typename T, typename Selector>
    typename raw_node<T,Selector>::pointer raw_node<T,Selector>::add_child()
    {
        pointer child = new raw_node();

        child->_parent = this;
        _add_child(child);
        return child;
    }

    template <typename T, typename Selector>
    typename raw_node<T,Selector>::pointer
        raw_node<T,Selector>::add_child_copy(const_pointer const& copy)
    {
        pointer child = new raw_node(*copy);

        child->_parent = this;
        _add_child(child);
        return child;
    }

    template <typename T, typename Selector>
    inline typename raw_node<T,Selector>::const_child_iterator
        raw_node<T,Selector>::get_child_begin() const
    {
        return const_child_iterator(_children.begin());
    }

    template <typename T, typename Selector>
    inline typename raw_node<T,Selector>::child_iterator
        raw_node<T,Selector>::get_child_begin()
    {
        return _children.begin();
    }

    template <typename T, typename Selector>
    inline typename raw_node<T,Selector>::const_child_iterator
        raw_node<T,Selector>::get_child_end() const
    {
        return const_child_iterator(_children.end());
    }

    template <typename T, typename Selector>
    inline typename raw_node<T,Selector>::child_iterator
        raw_node<T,Selector>::get_child_end()
    {
        return _children.end();
    }

    template <typename T, typename Selector>
    inline ::std::pair<
        typename raw_node<T,Selector>::const_child_iterator
      , typename raw_node<T,Selector>::const_child_iterator
    >
        raw_node<T,Selector>::get_children() const
    {
        return ::std::pair<const_child_iterator,const_child_iterator>(
            get_child_begin()
          , get_child_end()
        );
    }

    template <typename T, typename Selector>
    inline ::std::pair<
        typename raw_node<T,Selector>::child_iterator
      , typename raw_node<T,Selector>::child_iterator
    >
        raw_node<T,Selector>::get_children()
    {
        return ::std::pair<child_iterator,child_iterator>(
            get_child_begin()
          , get_child_end()
        );
    }

    template <typename T, typename Selector>
    void raw_node<T,Selector>::remove_all_children()
    {
        child_iterator itr_end = get_child_end();

        for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
        {
            delete *itr;
        }

        _children.clear();
    }

    template <typename T, typename Selector>
    inline void raw_node<T,Selector>::_add_child(pointer const& child)
    {
        _children.insert(_children.end(), child);
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_RAW_NODE_HPP_INCLUDED

