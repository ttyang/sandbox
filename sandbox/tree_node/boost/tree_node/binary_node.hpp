// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED

#include <iterator>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#ifndef BOOST_NO_SFINAE
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#endif
#include <boost/move/move.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/depth_first_desc_iterator.hpp>
#include <boost/tree_node/in_order_iterator.hpp>
#include <boost/tree_node/algorithm/equal.hpp>
#include <boost/tree_node/algorithm/lexicographical_compare.hpp>

//[reference__binary_node_base
namespace boost { namespace tree_node {
  //<-
  namespace _detail {

    template <typename Node>
    class binary_child_iterator
    {
#ifndef BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

     public:
        typedef ::std::bidirectional_iterator_tag iterator_category;
        typedef Node value_type;
        typedef ::std::ptrdiff_t difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;

//     private:
        pointer _current;

     public:
        binary_child_iterator();

        binary_child_iterator(pointer const& p, bool p_is_child);

        template <typename N>
        binary_child_iterator(
            binary_child_iterator<N> const& other
#ifndef BOOST_NO_SFINAE
          , typename ::boost::enable_if<
                ::std::tr1::is_convertible<N,Node>
              , enabler
            >::type = enabler()
#endif
        );

        reference operator*() const;

        pointer operator->() const;

        binary_child_iterator& operator++();

        binary_child_iterator operator++(int);

        binary_child_iterator& operator--();

        binary_child_iterator operator--(int);

     private:
        void _iterate(pointer const& sibling);

        template <typename N1, typename N2>
        friend bool
            operator==(
                binary_child_iterator<N1> const& lhs
              , binary_child_iterator<N2> const& rhs
            );
    };

    template <typename Node>
    binary_child_iterator<Node>::binary_child_iterator() : _current(0)
    {
    }

    template <typename Node>
    binary_child_iterator<Node>::binary_child_iterator(
        pointer const& p
      , bool p_is_child
    ) : _current(
        p_is_child
      ? p
      : p->get_left_child_ptr()
      ? p->get_left_child_ptr()
      : p->get_right_child_ptr()
    )
    {
    }

    template <typename Node>
    template <typename N>
    binary_child_iterator<Node>::binary_child_iterator(
        binary_child_iterator<N> const& other
#ifndef BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            ::std::tr1::is_convertible<N,Node>
          , enabler
        >::type
#endif
    ) : _current(other._current)
    {
    }

    template <typename Node>
    inline typename binary_child_iterator<Node>::reference
        binary_child_iterator<Node>::operator*() const
    {
        return *_current;
    }

    template <typename Node>
    inline typename binary_child_iterator<Node>::pointer
        binary_child_iterator<Node>::operator->() const
    {
        return _current;
    }

    template <typename Node>
    inline binary_child_iterator<Node>&
        binary_child_iterator<Node>::operator++()
    {
        _iterate(_current->get_parent_ptr()->get_right_child_ptr());
        return *this;
    }

    template <typename Node>
    binary_child_iterator<Node> binary_child_iterator<Node>::operator++(int)
    {
        binary_child_iterator itr(*this);
        ++(*this);
        return itr;
    }

    template <typename Node>
    inline binary_child_iterator<Node>&
        binary_child_iterator<Node>::operator--()
    {
        _iterate(_current->get_parent_ptr()->get_left_child_ptr());
        return *this;
    }

    template <typename Node>
    binary_child_iterator<Node> binary_child_iterator<Node>::operator--(int)
    {
        binary_child_iterator itr(*this);
        --(*this);
        return itr;
    }

    template <typename Node>
    inline void binary_child_iterator<Node>::_iterate(pointer const& sibling)
    {
        _current = (_current == sibling) ? 0 : sibling;
    }

    template <typename N1, typename N2>
    inline bool
        operator==(
            binary_child_iterator<N1> const& lhs
          , binary_child_iterator<N2> const& rhs
        )
    {
        return lhs._current == rhs._current;
    }

    template <typename N1, typename N2>
    inline bool
        operator!=(
            binary_child_iterator<N1> const& lhs
          , binary_child_iterator<N2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
  }  // namespace _detail
  //->

    template <typename Derived, typename T>
    class binary_node_base : public tree_node_base<Derived>
    {
        //<-
        BOOST_COPYABLE_AND_MOVABLE(binary_node_base);
        //->

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
                _detail::binary_child_iterator<Derived>
                //->
                iterator;
        typedef // implementation_defined
                //<-
                _detail::binary_child_iterator<Derived const>
                //->
                const_iterator;

        //<-
     private:
        pointer                    _left_child;
        pointer                    _right_child;
        pointer                    _parent;
        typename traits::data_type _data;

     public:
        //->
        binary_node_base();

        explicit binary_node_base(typename traits::data_type const& data);

        binary_node_base(binary_node_base const& copy);

//<-
#if 0
//->
        binary_node_base(binary_node_base&& source);

        binary_node_base& operator=(binary_node_base const& copy);

        binary_node_base& operator=(binary_node_base&& source);
//<-
#endif

        binary_node_base(BOOST_RV_REF(binary_node_base) source);

        binary_node_base&
            operator=(BOOST_COPY_ASSIGN_REF(binary_node_base) copy);

        binary_node_base& operator=(BOOST_RV_REF(binary_node_base) source);
//->

        ~binary_node_base();

        typename traits::data_type const& get_data() const;

        typename traits::data_type& get_data();

        const_pointer get_parent_ptr() const;

        pointer get_parent_ptr();

        iterator add_left_child(typename traits::data_type const& data);

        iterator add_left_child();

        iterator add_left_child_copy(Derived const& copy);

        iterator add_right_child(typename traits::data_type const& data);

        iterator add_right_child();

        iterator add_right_child_copy(Derived const& copy);

        const_pointer get_left_child_ptr() const;

        pointer get_left_child_ptr();

        const_pointer get_right_child_ptr() const;

        pointer get_right_child_ptr();

        const_iterator begin() const;

        iterator begin();

        const_iterator end() const;

        iterator end();

        bool empty() const;

        void clear();

        pointer rotate_left();

        pointer rotate_right();

        void remove_left_child();

        void remove_right_child();

        //<-
     private:
        iterator _add_child(pointer const& child);

        void _clone(binary_node_base const& copy);
        //->
    };

    //<-
    template <typename Derived, typename T>
    binary_node_base<Derived,T>::binary_node_base()
      : _left_child(), _right_child(), _parent(), _data()
    {
    }

    template <typename Derived, typename T>
    binary_node_base<Derived,T>::binary_node_base(
        typename traits::data_type const& data
    ) : _left_child(), _right_child(), _parent(), _data(data)
    {
    }

    template <typename Derived, typename T>
    binary_node_base<Derived,T>::binary_node_base(
        binary_node_base const& copy
    ) : _left_child(), _right_child(), _parent(), _data(copy._data)
    {
        _clone(copy);
    }

    template <typename Derived, typename T>
    binary_node_base<Derived,T>::binary_node_base(
        BOOST_RV_REF(binary_node_base) source
    ) : _left_child(source._left_child)
      , _right_child(source._right_child)
      , _parent()
      , _data(::boost::move(source._data))
    {
        this->shallow_update_derived();
        source._left_child = source._right_child = 0;
    }

    template <typename Derived, typename T>
    binary_node_base<Derived,T>&
        binary_node_base<Derived,T>::operator=(
            BOOST_COPY_ASSIGN_REF(binary_node_base) copy
        )
    {
        if (this != &copy)
        {
            binary_node_base twin(copy);

            delete _left_child;
            delete _right_child;
            _left_child = twin._left_child;
            _right_child = twin._right_child;
            _left_child->_parent = _right_child->_parent = this->get_derived();
            _data = ::boost::move(twin._data);
            this->shallow_update_derived();
            twin._left_child = twin._right_child = 0;
        }

        return *this;
    }

    template <typename Derived, typename T>
    inline binary_node_base<Derived,T>&
        binary_node_base<Derived,T>::operator=(
            BOOST_RV_REF(binary_node_base) source
        )
    {
        if (this != &source)
        {
            _left_child = source._left_child;
            _right_child = source._right_child;
            _left_child->_parent = _right_child->_parent = this->get_derived();
            _data = ::boost::move(source._data);
            this->shallow_update_derived();
            source._left_child = source._right_child = 0;
        }

        return *this;
    }

    template <typename Derived, typename T>
    binary_node_base<Derived,T>::~binary_node_base()
    {
        delete _left_child;
        delete _right_child;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::traits::data_type const&
        binary_node_base<Derived,T>::get_data() const
    {
        return _data;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::traits::data_type&
        binary_node_base<Derived,T>::get_data()
    {
        return _data;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::const_pointer
        binary_node_base<Derived,T>::get_parent_ptr() const
    {
        return _parent;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::get_parent_ptr()
    {
        return _parent;
    }

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::add_left_child(
            typename traits::data_type const& data
        )
    {
        if (_left_child)
        {
            return end();
        }
        else
        {
            return _add_child(_left_child = new Derived(data));
        }
    }

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::add_left_child()
    {
        if (_left_child)
        {
            return end();
        }
        else
        {
            return _add_child(_left_child = new Derived());
        }
    }

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::add_left_child_copy(Derived const& copy)
    {
        if (_left_child)
        {
            return end();
        }
        else
        {
            return _add_child(_left_child = new Derived(copy));
        }
    }

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::add_right_child(
            typename traits::data_type const& data
        )
    {
        if (_right_child)
        {
            return end();
        }
        else
        {
            return _add_child(_right_child = new Derived(data));
        }
    }

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::add_right_child()
    {
        if (_right_child)
        {
            return end();
        }
        else
        {
            return _add_child(_right_child = new Derived());
        }
    }

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::add_right_child_copy(Derived const& copy)
    {
        if (_right_child)
        {
            return end();
        }
        else
        {
            return _add_child(_right_child = new Derived(copy));
        }
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::const_pointer
        binary_node_base<Derived,T>::get_left_child_ptr() const
    {
        return _left_child;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::get_left_child_ptr()
    {
        return _left_child;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::const_pointer
        binary_node_base<Derived,T>::get_right_child_ptr() const
    {
        return _right_child;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::get_right_child_ptr()
    {
        return _right_child;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::const_iterator
        binary_node_base<Derived,T>::begin() const
    {
        return const_iterator(this->get_derived(), false);
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::begin()
    {
        return iterator(this->get_derived(), false);
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::const_iterator
        binary_node_base<Derived,T>::end() const
    {
        return const_iterator();
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::end()
    {
        return iterator();
    }

    template <typename Derived, typename T>
    inline bool binary_node_base<Derived,T>::empty() const
    {
        return !_left_child && !_right_child;
    }

    template <typename Derived, typename T>
    void binary_node_base<Derived,T>::clear()
    {
        delete _left_child;
        delete _right_child;
        _left_child = _right_child = 0;
        this->shallow_update_derived();
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::rotate_left()
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
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::rotate_right()
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
    void binary_node_base<Derived,T>::remove_left_child()
    {
        delete _left_child;
        _left_child = 0;
        this->shallow_update_derived();
    }

    template <typename Derived, typename T>
    void binary_node_base<Derived,T>::remove_right_child()
    {
        delete _right_child;
        _right_child = 0;
        this->shallow_update_derived();
    }

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::_add_child(pointer const& child)
    {
        iterator result(child, true);

        result->_parent = this->get_derived();
        result->set_position_derived(result, ::boost::mpl::false_());
        this->shallow_update_derived();
        return result;
    }

    template <typename Derived, typename T>
    void binary_node_base<Derived,T>::_clone(binary_node_base const& copy)
    {
        pointer p = this->get_derived();

        for (
            depth_first_descendant_iterator<Derived const> copy_itr(
                *copy.get_derived()
            );
            copy_itr;
            ++copy_itr
        )
        {
            switch (traversal_state(copy_itr))
            {
                case pre_order_traversal:
                {
                    if (copy_itr->_parent->_left_child == &*copy_itr)
                    {
                        p->_left_child = new Derived(copy_itr->get_data());
                        p->_left_child->_parent = p;
                        p = p->_left_child;
                    }
                    else // if (copy_itr->_parent->_right_child == &*copy_itr)
                    {
                        p->_right_child = new Derived(copy_itr->get_data());
                        p->_right_child->_parent = p;
                        p = p->_right_child;
                    }

                    p->set_position_derived(
                        iterator(p, true)
                      , ::boost::mpl::false_()
                    );
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
    //->
}}  // namespace boost::tree_node
//]

//[reference__binary_node_base__operator_equals
namespace boost { namespace tree_node {

    template <typename Derived, typename T>
    bool
        operator==(
            binary_node_base<Derived,T> const& lhs
          , binary_node_base<Derived,T> const& rhs
        );

    //<-
    template <typename Derived, typename T>
    inline bool
        operator==(
            binary_node_base<Derived,T> const& lhs
          , binary_node_base<Derived,T> const& rhs
        )
    {
        return ::boost::tree_node::equal(
            in_order_iterator<Derived const>(*lhs.get_derived())
          , in_order_iterator<Derived const>(*rhs.get_derived())
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__binary_node_base__operator_less_than
namespace boost { namespace tree_node {

    template <typename Derived, typename T>
    bool
        operator<(
            binary_node_base<Derived,T> const& lhs
          , binary_node_base<Derived,T> const& rhs
        );

    //<-
    template <typename Derived, typename T>
    inline bool
        operator<(
            binary_node_base<Derived,T> const& lhs
          , binary_node_base<Derived,T> const& rhs
        )
    {
        return ::boost::tree_node::lexicographical_compare(
            in_order_iterator<Derived const>(*lhs.get_derived())
          , in_order_iterator<Derived const>(*rhs.get_derived())
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__binary_node
namespace boost { namespace tree_node {

    template <typename T>
    class binary_node : public binary_node_base<binary_node<T>,T>
    {
        //<-
        BOOST_COPYABLE_AND_MOVABLE(binary_node);
        //->
        typedef binary_node_base<binary_node<T>,T> super_t;

     public:
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::iterator iterator;
        typedef typename super_t::const_iterator const_iterator;

        binary_node();

        explicit binary_node(typename traits::data_type const& data);

//<-
#if 0
//->
        binary_node(binary_node const& copy);

        binary_node(binary_node&& source);

        binary_node& operator=(binary_node const& copy);

        binary_node& operator=(binary_node&& source);
//<-
#endif

        binary_node(BOOST_RV_REF(binary_node) source);

        binary_node& operator=(BOOST_COPY_ASSIGN_REF(binary_node) copy);

        binary_node& operator=(BOOST_RV_REF(binary_node) source);
//->
    };

    //<-
    template <typename T>
    binary_node<T>::binary_node() : super_t()
    {
    }

    template <typename T>
    binary_node<T>::binary_node(typename traits::data_type const& data)
      : super_t(data)
    {
    }

    template <typename T>
    binary_node<T>::binary_node(BOOST_RV_REF(binary_node) source)
      : super_t(::boost::move(static_cast<super_t&>(source)))
    {
    }

    template <typename T>
    inline binary_node<T>&
        binary_node<T>::operator=(
            BOOST_COPY_ASSIGN_REF(binary_node) copy
        )
    {
        super_t::operator=(static_cast<super_t const&>(copy));
        return *this;
    }

    template <typename T>
    inline binary_node<T>&
        binary_node<T>::operator=(BOOST_RV_REF(binary_node) source)
    {
        super_t::operator=(::boost::move(static_cast<super_t&>(source)));
        return *this;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__binary_node_gen
namespace boost { namespace tree_node {

    struct binary_node_gen
    {
        template <typename Derived, typename T>
        struct apply
        {
            typedef binary_node_base<Derived,T> type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED

