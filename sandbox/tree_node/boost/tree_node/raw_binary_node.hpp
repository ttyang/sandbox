// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_RAW_BINARY_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_RAW_BINARY_NODE_HPP_INCLUDED

#include <iterator>
#include <utility>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#ifndef BOOST_NO_SFINAE
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>
#endif
#include <boost/array.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/detail/function/add_const_to_pointee.hpp>

//[reference__raw_binary_node
namespace boost { namespace tree_node {
  //<-
  namespace _detail {

    template <typename NodePointer>
    class raw_binary_child_iterator
    {
#ifndef BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

        NodePointer _child;

     public:
        typedef NodePointer value_type;
        typedef value_type const& reference;
        typedef value_type const* pointer;
        typedef ::std::ptrdiff_t difference_type;
        typedef ::std::forward_iterator_tag iterator_category;

        explicit raw_binary_child_iterator(NodePointer const& p);

        raw_binary_child_iterator();

        template <typename NP>
        raw_binary_child_iterator(
            raw_binary_child_iterator<NP> const& other
#ifndef BOOST_NO_SFINAE
          , typename ::boost::enable_if<
                ::std::tr1::is_convertible<NP,NodePointer>
              , enabler
            >::type = enabler()
#endif
        );

        reference operator*() const;

        pointer operator->() const;

        raw_binary_child_iterator& operator++();

        raw_binary_child_iterator operator++(int);

        template <typename NP1, typename NP2>
        friend bool
            operator==(
                raw_binary_child_iterator<NP1> const& lhs
              , raw_binary_child_iterator<NP2> const& rhs
            );
    };

    template <typename NodePointer>
    raw_binary_child_iterator<NodePointer>::raw_binary_child_iterator(
        NodePointer const& p
    ) : _child(
        p->get_left_child() ? p->get_left_child() : p->get_right_child()
    )
    {
    }

    template <typename NodePointer>
    raw_binary_child_iterator<NodePointer>::raw_binary_child_iterator()
      : _child(0)
    {
    }

    template <typename NodePointer>
    template <typename NP>
    raw_binary_child_iterator<NodePointer>::raw_binary_child_iterator(
        raw_binary_child_iterator<NP> const& other
#ifndef BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            ::std::tr1::is_convertible<NP,NodePointer>
          , enabler
        >::type
#endif
    ) : _child(other._child)
    {
    }

    template <typename NodePointer>
    inline typename raw_binary_child_iterator<NodePointer>::reference
        raw_binary_child_iterator<NodePointer>::operator*() const
    {
        return _child;
    }

    template <typename NodePointer>
    inline typename raw_binary_child_iterator<NodePointer>::pointer
        raw_binary_child_iterator<NodePointer>::operator->() const
    {
        return &_child;
    }

    template <typename NodePointer>
    inline raw_binary_child_iterator<NodePointer>&
        raw_binary_child_iterator<NodePointer>::operator++()
    {
        NodePointer sibling = _child->get_parent()->get_right_child();
        _child = (_child == sibling) ? 0 : sibling;
        return *this;
    }

    template <typename NodePointer>
    raw_binary_child_iterator<NodePointer>
        raw_binary_child_iterator<NodePointer>::operator++(int)
    {
        raw_binary_child_iterator<NodePointer> itr(*this);
        ++(*this);
        return itr;
    }

    template <typename NP1, typename NP2>
    inline bool
        operator==(
            raw_binary_child_iterator<NP1> const& lhs
          , raw_binary_child_iterator<NP2> const& rhs
        )
    {
        return lhs._child == rhs._child;
    }

    template <typename NP1, typename NP2>
    inline bool
        operator!=(
            raw_binary_child_iterator<NP1> const& lhs
          , raw_binary_child_iterator<NP2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
  }  // namespace _detail
  //->

    template <typename T>
    class raw_binary_node
    {
     public:
        typedef T
                data_type;
        typedef raw_binary_node*
                pointer;
        typedef raw_binary_node const*
                const_pointer;
        typedef // implementation_defined
                //<-
                _detail::raw_binary_child_iterator<pointer>
                //->
                child_iterator;
        typedef // implementation_defined
                //<-
                _detail::raw_binary_child_iterator<const_pointer>
                //->
                const_child_iterator;

        //<-
     private:
        pointer   _left_child;
        pointer   _right_child;
        pointer   _parent;
        data_type _data;

     public:
        //->
        raw_binary_node();

        explicit raw_binary_node(data_type const& data);

        raw_binary_node(raw_binary_node const& copy);

        raw_binary_node& operator=(raw_binary_node const& copy);

        ~raw_binary_node();

        data_type const& get_data() const;

        data_type& get_data();

        const_pointer get_parent() const;

        pointer get_parent();

        pointer add_left_child(data_type const& data);

        pointer add_left_child();

        pointer add_left_child_copy(const_pointer const& copy);

        pointer add_right_child(data_type const& data);

        pointer add_right_child();

        pointer add_right_child_copy(const_pointer const& copy);

        const_pointer get_left_child() const;

        pointer get_left_child();

        const_pointer get_right_child() const;

        pointer get_right_child();

        const_child_iterator get_child_begin() const;

        child_iterator get_child_begin();

        const_child_iterator get_child_end() const;

        child_iterator get_child_end();

        std::pair<const_child_iterator,const_child_iterator>
            get_children() const;

        std::pair<child_iterator,child_iterator>
            get_children();

        pointer rotate_left();

        pointer rotate_right();

        void remove_left_child();

        void remove_right_child();

        void remove_all_children();
    };

    //<-
    template <typename T>
    raw_binary_node<T>::raw_binary_node()
      : _left_child(), _right_child(), _parent(), _data()
    {
    }

    template <typename T>
    raw_binary_node<T>::raw_binary_node(data_type const& data)
      : _left_child(), _right_child(), _parent(), _data(data)
    {
    }

    template <typename T>
    raw_binary_node<T>::raw_binary_node(raw_binary_node const& copy)
      : _left_child(), _right_child(), _parent(), _data(copy._data)
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
                    const_pointer c_p = *copy_itr;

                    if (c_p->_parent->_left_child == c_p)
                    {
                        p = p->add_left_child(c_p->get_data());
                    }
                    else // if (c_p->_parent->_right_child == c_p)
                    {
                        p = p->add_right_child(c_p->get_data());
                    }

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
    raw_binary_node<T>&
        raw_binary_node<T>::operator=(raw_binary_node const& copy)
    {
        if (this != &copy)
        {
            raw_binary_node temp_copy(copy);

            delete _left_child;
            delete _right_child;
            _left_child = temp_copy._left_child;
            _right_child = temp_copy._right_child;
            _data = temp_copy._data;
            temp_copy._left_child = temp_copy._right_child = 0;
            _left_child->_parent = _right_child->_parent = this;
        }

        return *this;
    }

    template <typename T>
    raw_binary_node<T>::~raw_binary_node()
    {
        remove_all_children();
    }

    template <typename T>
    inline typename raw_binary_node<T>::data_type const&
        raw_binary_node<T>::get_data() const
    {
        return _data;
    }

    template <typename T>
    inline typename raw_binary_node<T>::data_type&
        raw_binary_node<T>::get_data()
    {
        return _data;
    }

    template <typename T>
    inline typename raw_binary_node<T>::const_pointer
        raw_binary_node<T>::get_parent() const
    {
        return _parent;
    }

    template <typename T>
    inline typename raw_binary_node<T>::pointer
        raw_binary_node<T>::get_parent()
    {
        return _parent;
    }

    template <typename T>
    typename raw_binary_node<T>::pointer
        raw_binary_node<T>::add_left_child(data_type const& data)
    {
        _left_child = new raw_binary_node(data);
        _left_child->_parent = this;
        return _left_child;
    }

    template <typename T>
    typename raw_binary_node<T>::pointer raw_binary_node<T>::add_left_child()
    {
        _left_child = new raw_binary_node();
        _left_child->_parent = this;
        return _left_child;
    }

    template <typename T>
    typename raw_binary_node<T>::pointer
        raw_binary_node<T>::add_left_child_copy(const_pointer const& copy)
    {
        _left_child = new raw_binary_node(*copy);
        _left_child->_parent = this;
        return _left_child;
    }

    template <typename T>
    typename raw_binary_node<T>::pointer
        raw_binary_node<T>::add_right_child(data_type const& data)
    {
        _right_child = new raw_binary_node(data);
        _right_child->_parent = this;
        return _right_child;
    }

    template <typename T>
    typename raw_binary_node<T>::pointer raw_binary_node<T>::add_right_child()
    {
        _right_child = new raw_binary_node();
        _right_child->_parent = this;
        return _right_child;
    }

    template <typename T>
    typename raw_binary_node<T>::pointer
        raw_binary_node<T>::add_right_child_copy(const_pointer const& copy)
    {
        _right_child = new raw_binary_node(*copy);
        _right_child->_parent = this;
        return _right_child;
    }

    template <typename T>
    inline typename raw_binary_node<T>::const_pointer
        raw_binary_node<T>::get_left_child() const
    {
        return _left_child;
    }

    template <typename T>
    inline typename raw_binary_node<T>::pointer
        raw_binary_node<T>::get_left_child()
    {
        return _left_child;
    }

    template <typename T>
    inline typename raw_binary_node<T>::const_pointer
        raw_binary_node<T>::get_right_child() const
    {
        return _right_child;
    }

    template <typename T>
    inline typename raw_binary_node<T>::pointer
        raw_binary_node<T>::get_right_child()
    {
        return _right_child;
    }

    template <typename T>
    inline typename raw_binary_node<T>::const_child_iterator
        raw_binary_node<T>::get_child_begin() const
    {
        return const_child_iterator(this);
    }

    template <typename T>
    inline typename raw_binary_node<T>::child_iterator
        raw_binary_node<T>::get_child_begin()
    {
        return child_iterator(this);
    }

    template <typename T>
    inline typename raw_binary_node<T>::const_child_iterator
        raw_binary_node<T>::get_child_end() const
    {
        return const_child_iterator();
    }

    template <typename T>
    inline typename raw_binary_node<T>::child_iterator
        raw_binary_node<T>::get_child_end()
    {
        return child_iterator();
    }

    template <typename T>
    inline ::std::pair<
        typename raw_binary_node<T>::const_child_iterator
      , typename raw_binary_node<T>::const_child_iterator
    >
        raw_binary_node<T>::get_children() const
    {
        return ::std::pair<const_child_iterator,const_child_iterator>(
            get_child_begin()
          , get_child_end()
        );
    }

    template <typename T>
    inline ::std::pair<
        typename raw_binary_node<T>::child_iterator
      , typename raw_binary_node<T>::child_iterator
    >
        raw_binary_node<T>::get_children()
    {
        return ::std::pair<child_iterator,child_iterator>(
            get_child_begin()
          , get_child_end()
        );
    }

    template <typename T>
    inline typename raw_binary_node<T>::pointer
        raw_binary_node<T>::rotate_left()
    {
        pointer pivot = _right_child;

        pivot->_parent = _parent;
        _right_child = pivot->_left_child;
        _right_child->_parent = pivot->_left_child = this;

        if (_parent)
        {
            if (_parent->_left_child == this)
            {
                _parent->_left_child = pivot;
            }
            else // if (_parent->_right_child == this)
            {
                _parent->_right_child = pivot;
            }
        }

        return _parent = pivot;
    }

    template <typename T>
    inline typename raw_binary_node<T>::pointer
        raw_binary_node<T>::rotate_right()
    {
        pointer pivot = _left_child;

        pivot->_parent = _parent;
        _left_child = pivot->_right_child;
        _left_child->_parent = pivot->_right_child = this;

        if (_parent)
        {
            if (_parent->_right_child == this)
            {
                _parent->_right_child = pivot;
            }
            else // if (_parent->_left_child == this)
            {
                _parent->_left_child = pivot;
            }
        }

        return _parent = pivot;
    }

    template <typename T>
    void raw_binary_node<T>::remove_left_child()
    {
        delete _left_child;
        _left_child = 0;
    }

    template <typename T>
    void raw_binary_node<T>::remove_right_child()
    {
        delete _right_child;
        _right_child = 0;
    }

    template <typename T>
    inline void raw_binary_node<T>::remove_all_children()
    {
        remove_left_child();
        remove_right_child();
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_RAW_BINARY_NODE_HPP_INCLUDED

