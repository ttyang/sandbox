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
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/tree_node/factory.hpp>

//[reference__raw_binary_node_base
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
    ) : _child(*other)
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

    template <typename Derived, typename T>
    class raw_binary_node_base : public tree_node_base<Derived>
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
        pointer                    _left_child;
        pointer                    _right_child;
        pointer                    _parent;
        typename traits::data_type _data;

     public:
        //->
        raw_binary_node_base();

        explicit raw_binary_node_base(typename traits::data_type const& data);

        raw_binary_node_base(raw_binary_node_base const& copy);

        raw_binary_node_base& operator=(raw_binary_node_base const& copy);

        virtual ~raw_binary_node_base();

        pointer clone() const;

        typename traits::data_type const& get_data() const;

        typename traits::data_type& get_data();

        const_pointer get_parent() const;

        pointer get_parent();

        pointer add_left_child(typename traits::data_type const& data);

        pointer add_left_child();

        pointer add_left_child_copy(const_pointer const& copy);

        pointer add_right_child(typename traits::data_type const& data);

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

        pointer rotate_left();

        pointer rotate_right();

        void remove_left_child();

        void remove_right_child();

        void remove_all_children();
    };

    //<-
    template <typename Derived, typename T>
    raw_binary_node_base<Derived,T>::raw_binary_node_base()
      : _left_child(), _right_child(), _parent(), _data()
    {
    }

    template <typename Derived, typename T>
    raw_binary_node_base<Derived,T>::raw_binary_node_base(
        typename traits::data_type const& data
    ) : _left_child(), _right_child(), _parent(), _data(data)
    {
    }

    template <typename Derived, typename T>
    raw_binary_node_base<Derived,T>::raw_binary_node_base(
        raw_binary_node_base const& copy
    ) : _left_child(), _right_child(), _parent(), _data(copy._data)
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
                    const_pointer c_p = *copy_itr;

                    if (c_p->_parent->_left_child == c_p)
                    {
                        p->_left_child = ::boost::tree_node::factory<
                            Derived
                        >::create(c_p->get_data());
                        p->_left_child->_parent = p;
                        p = p->_left_child;
                    }
                    else // if (c_p->_parent->_right_child == c_p)
                    {
                        p->_right_child = ::boost::tree_node::factory<
                            Derived
                        >::create(c_p->get_data());
                        p->_right_child->_parent = p;
                        p = p->_right_child;
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

        this->deep_update_derived();
    }

    template <typename Derived, typename T>
    raw_binary_node_base<Derived,T>&
        raw_binary_node_base<Derived,T>::operator=(
            raw_binary_node_base const& copy
        )
    {
        if (this != &copy)
        {
            raw_binary_node_base temp_copy(copy);

            delete _left_child;
            delete _right_child;
            _left_child = temp_copy._left_child;
            _right_child = temp_copy._right_child;
            _data = temp_copy._data;
            temp_copy._left_child = temp_copy._right_child = 0;
            _left_child->_parent = _right_child->_parent = this->get_derived();
            this->shallow_update_derived();
        }

        return *this;
    }

    template <typename Derived, typename T>
    raw_binary_node_base<Derived,T>::~raw_binary_node_base()
    {
        delete _left_child;
        delete _right_child;
    }

    template <typename Derived, typename T>
    typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::clone() const
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
                    const_pointer c_p = *copy_itr;

                    if (c_p->_parent->_left_child == c_p)
                    {
                        p->_left_child = ::boost::tree_node::factory<
                            Derived
                        >::create(c_p->get_data());
                        p->_left_child->_parent = p;
                        p = p->_left_child;
                    }
                    else // if (c_p->_parent->_right_child == c_p)
                    {
                        p->_right_child = ::boost::tree_node::factory<
                            Derived
                        >::create(c_p->get_data());
                        p->_right_child->_parent = p;
                        p = p->_right_child;
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

        result->deep_update_derived();
        return result;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::traits::data_type const&
        raw_binary_node_base<Derived,T>::get_data() const
    {
        return _data;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::traits::data_type&
        raw_binary_node_base<Derived,T>::get_data()
    {
        return _data;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::const_pointer
        raw_binary_node_base<Derived,T>::get_parent() const
    {
        return _parent;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::get_parent()
    {
        return _parent;
    }

    template <typename Derived, typename T>
    typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::add_left_child(
            typename traits::data_type const& data
        )
    {
        _left_child = ::boost::tree_node::factory<Derived>::create(data);
        _left_child->_parent = this->get_derived();
        this->shallow_update_derived();
        return _left_child;
    }

    template <typename Derived, typename T>
    typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::add_left_child()
    {
        _left_child = ::boost::tree_node::factory<Derived>::create();
        _left_child->_parent = this->get_derived();
        this->shallow_update_derived();
        return _left_child;
    }

    template <typename Derived, typename T>
    typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::add_left_child_copy(
            const_pointer const& copy
        )
    {
        _left_child = copy->clone();
        _left_child->_parent = this->get_derived();
        this->shallow_update_derived();
        return _left_child;
    }

    template <typename Derived, typename T>
    typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::add_right_child(
            typename traits::data_type const& data
        )
    {
        _right_child = ::boost::tree_node::factory<Derived>::create(data);
        _right_child->_parent = this->get_derived();
        this->shallow_update_derived();
        return _right_child;
    }

    template <typename Derived, typename T>
    typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::add_right_child()
    {
        _right_child = ::boost::tree_node::factory<Derived>::create();
        _right_child->_parent = this->get_derived();
        this->shallow_update_derived();
        return _right_child;
    }

    template <typename Derived, typename T>
    typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::add_right_child_copy(
            const_pointer const& copy
        )
    {
        _right_child = copy->clone();
        _right_child->_parent = this->get_derived();
        this->shallow_update_derived();
        return _right_child;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::const_pointer
        raw_binary_node_base<Derived,T>::get_left_child() const
    {
        return _left_child;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::get_left_child()
    {
        return _left_child;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::const_pointer
        raw_binary_node_base<Derived,T>::get_right_child() const
    {
        return _right_child;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::get_right_child()
    {
        return _right_child;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::const_child_iterator
        raw_binary_node_base<Derived,T>::get_child_begin() const
    {
        return const_child_iterator(this->get_derived());
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::child_iterator
        raw_binary_node_base<Derived,T>::get_child_begin()
    {
        return child_iterator(this->get_derived());
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::const_child_iterator
        raw_binary_node_base<Derived,T>::get_child_end() const
    {
        return const_child_iterator();
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::child_iterator
        raw_binary_node_base<Derived,T>::get_child_end()
    {
        return child_iterator();
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::rotate_left()
    {
        pointer pivot = _right_child;

        pivot->_parent = _parent;
        _right_child = pivot->_left_child;
        _right_child->_parent = pivot->_left_child = this->get_derived();

        if (_parent)
        {
            if (_parent->_left_child == this->get_derived())
            {
                _parent->_left_child = pivot;
            }
            else // if (_parent->_right_child == this->get_derived())
            {
                _parent->_right_child = pivot;
            }
        }

        _parent = pivot;
        this->shallow_update_derived();
        return pivot;
    }

    template <typename Derived, typename T>
    inline typename raw_binary_node_base<Derived,T>::pointer
        raw_binary_node_base<Derived,T>::rotate_right()
    {
        pointer pivot = _left_child;

        pivot->_parent = _parent;
        _left_child = pivot->_right_child;
        _left_child->_parent = pivot->_right_child = this->get_derived();

        if (_parent)
        {
            if (_parent->_right_child == this->get_derived())
            {
                _parent->_right_child = pivot;
            }
            else // if (_parent->_left_child == this->get_derived())
            {
                _parent->_left_child = pivot;
            }
        }

        _parent = pivot;
        this->shallow_update_derived();
        return pivot;
    }

    template <typename Derived, typename T>
    void raw_binary_node_base<Derived,T>::remove_left_child()
    {
        delete _left_child;
        _left_child = 0;
        this->shallow_update_derived();
    }

    template <typename Derived, typename T>
    void raw_binary_node_base<Derived,T>::remove_right_child()
    {
        delete _right_child;
        _right_child = 0;
        this->shallow_update_derived();
    }

    template <typename Derived, typename T>
    void raw_binary_node_base<Derived,T>::remove_all_children()
    {
        delete _left_child;
        delete _right_child;
        _left_child = _right_child = 0;
        this->shallow_update_derived();
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__raw_binary_node
namespace boost { namespace tree_node {

    template <typename T>
    class raw_binary_node : public raw_binary_node_base<raw_binary_node<T>,T>
    {
        typedef raw_binary_node_base<raw_binary_node<T>,T> super_t;

     public:
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::child_iterator child_iterator;
        typedef typename super_t::const_child_iterator const_child_iterator;

        raw_binary_node();

        explicit raw_binary_node(typename traits::data_type const& data);
    };

    //<-
    template <typename T>
    raw_binary_node<T>::raw_binary_node() : super_t()
    {
    }

    template <typename T>
    raw_binary_node<T>::raw_binary_node(typename traits::data_type const& data)
      : super_t(data)
    {
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__raw_binary_node_gen
namespace boost { namespace tree_node {

    struct raw_binary_node_gen
    {
        template <typename Derived, typename T>
        struct apply
        {
            typedef raw_binary_node_base<Derived,T> type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_RAW_BINARY_NODE_HPP_INCLUDED

