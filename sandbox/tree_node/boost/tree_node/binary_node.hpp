// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED

#include <iterator>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/noncopyable.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/depth_first_desc_iterator.hpp>
#include <boost/assert.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#if !defined BOOST_NO_SFINAE
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#endif

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/move/move.hpp>
#endif

#include <boost/tree_node/_detail/config_begin.hpp>

namespace boost { namespace tree_node { namespace _detail {

    template <typename Node>
    class binary_child_iterator
    {
#if !defined BOOST_NO_SFINAE
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
#if !defined BOOST_NO_SFINAE
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
#if !defined BOOST_NO_SFINAE
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
        return *this->_current;
    }

    template <typename Node>
    inline typename binary_child_iterator<Node>::pointer
        binary_child_iterator<Node>::operator->() const
    {
        return this->_current;
    }

    template <typename Node>
    inline binary_child_iterator<Node>&
        binary_child_iterator<Node>::operator++()
    {
        this->_iterate(
            this->_current->get_parent_ptr()->get_right_child_ptr()
        );
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
        this->_iterate(this->_current->get_parent_ptr()->get_left_child_ptr());
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
        this->_current = (this->_current == sibling) ? 0 : sibling;
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
}}}  // namespace boost::tree_node::_detail

namespace boost { namespace tree_node {

    template <typename Derived, typename T>
    class binary_node_base
      : public
        //[reference__binary_node_base__bases
        tree_node_base<Derived>
        //]
      , private ::boost::noncopyable
    {
     public:
        //[reference__binary_node_base__traits
        struct traits
        {
            typedef T data_type;
        };
        //]

        //[reference__binary_node_base__pointer
        typedef typename tree_node_base<Derived>::pointer
                pointer;
        //]

        //[reference__binary_node_base__const_pointer
        typedef typename tree_node_base<Derived>::const_pointer
                const_pointer;
        //]

        //[reference__binary_node_base__iterator
        typedef // implementation_defined
                //<-
                _detail::binary_child_iterator<Derived>
                //->
                iterator;
        //]

        //[reference__binary_node_base__const_iterator
        typedef // implementation_defined
                //<-
                _detail::binary_child_iterator<Derived const>
                //->
                const_iterator;
        //]

        //[reference__binary_node_base__size_type
        typedef ::boost::uint8_t
                size_type;
        //]

     private:
        typename traits::data_type _data;
        pointer                    _left_child;
        pointer                    _right_child;
        pointer                    _parent;

     protected:
        //[reference__binary_node_base__derived_copy_ctor
        binary_node_base(Derived const& copy);
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        binary_node_base(BOOST_RV_REF(Derived) source);
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binary_node_base__emplacement_ctor
        template <typename ...Args>
        explicit binary_node_base(Args&& ...args);
        //]
#else
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_FWD_DECL
          , binary_node_base
        )
#endif

        ~binary_node_base();

        //[reference__binary_node_base__on_post_copy_or_move
        void on_post_copy_or_move();
        //]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__binary_node_base__copy_assign
        void copy_assign(Derived const& copy);
        //]
#else
        void copy_assign(BOOST_COPY_ASSIGN_REF(Derived) copy);

        void move_assign(BOOST_RV_REF(Derived) source);
#endif

     public:
        //[reference__binary_node_base__get_data__const
        typename traits::data_type const& get_data() const;
        //]

        //[reference__binary_node_base__get_data
        typename traits::data_type& get_data();
        //]

        //[reference__binary_node_base__get_parent_ptr__const
        const_pointer get_parent_ptr() const;
        //]

        //[reference__binary_node_base__get_parent_ptr
        pointer get_parent_ptr();
        //]

        //[reference__binary_node_base__insert_left
        iterator insert_left(Derived const& child);
        //]

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binary_node_base__emplace_left
        template <typename ...Args>
        iterator emplace_left(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        iterator                                                             \
            emplace_left(                                                    \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_BINARY_NODE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_BINARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        //[reference__binary_node_base__insert_right
        iterator insert_right(Derived const& child);
        //]

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binary_node_base__emplace_right
        template <typename ...Args>
        iterator emplace_right(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        iterator                                                             \
            emplace_right(                                                   \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_BINARY_NODE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_BINARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        //[reference__binary_node_base__get_left_child_ptr__const
        const_pointer get_left_child_ptr() const;
        //]

        //[reference__binary_node_base__get_left_child_ptr
        pointer get_left_child_ptr();
        //]

        //[reference__binary_node_base__get_right_child_ptr__const
        const_pointer get_right_child_ptr() const;
        //]

        //[reference__binary_node_base__get_right_child_ptr
        pointer get_right_child_ptr();
        //]

        //[reference__binary_node_base__begin__const
        const_iterator begin() const;
        //]

        //[reference__binary_node_base__begin
        iterator begin();
        //]

        //[reference__binary_node_base__end__const
        const_iterator end() const;
        //]

        //[reference__binary_node_base__end
        iterator end();
        //]

        //[reference__binary_node_base__size
        size_type size() const;
        //]

        //[reference__binary_node_base__empty
        bool empty() const;
        //]

        //[reference__binary_node_base__clear
        void clear();
        //]

        //[reference__binary_node_base__rotate_left
        pointer rotate_left();
        //]

        //[reference__binary_node_base__rotate_right
        pointer rotate_right();
        //]

        //[reference__binary_node_base__erase_left
        bool erase_left();
        //]

        //[reference__binary_node_base__erase_right
        bool erase_right();
        //]

     private:
        iterator _add_child(pointer const& child);

        void _link_children_to_parent();
    };

    template <typename Derived, typename T>
    binary_node_base<Derived,T>::binary_node_base(Derived const& copy)
      : _data(copy._data)
      , _left_child(copy._left_child ? new Derived(*copy._left_child) : 0)
      , _right_child(copy._right_child ? new Derived(*copy._right_child) : 0)
      , _parent()
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T>
    binary_node_base<Derived,T>::binary_node_base(BOOST_RV_REF(Derived) source)
      : _data(::boost::move(source._data))
      , _left_child(source._left_child)
      , _right_child(source._right_child)
      , _parent()
    {
        source._left_child = source._right_child = 0;
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T>
    template <typename ...Args>
    binary_node_base<Derived,T>::binary_node_base(Args&& ...args)
      : _data(::boost::forward<Args>(args)...)
      , _left_child()
      , _right_child()
      , _parent()
    {
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
    template <typename Derived, typename T>                                  \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    binary_node_base<Derived,T>::binary_node_base(                           \
        BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                     \
            n                                                                \
          , BOOST_CONTAINER_PP_PARAM_LIST                                    \
          , _                                                                \
        )                                                                    \
    ) : _data(                                                               \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        )                                                                    \
      , _left_child()                                                        \
      , _right_child()                                                       \
      , _parent()                                                            \
    {                                                                        \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_BINARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_BINARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename T>
    binary_node_base<Derived,T>::~binary_node_base()
    {
        delete this->_left_child;
        delete this->_right_child;
    }

    template <typename Derived, typename T>
    inline void binary_node_base<Derived,T>::on_post_copy_or_move()
    {
        this->_link_children_to_parent();
    }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T>
    void binary_node_base<Derived,T>::copy_assign(Derived const& copy)
    {
        Derived twin(copy);

        delete this->_left_child;
        delete this->_right_child;

        this->_data = twin._data;
        this->_left_child = twin._left_child;
        this->_right_child = twin._right_child;
        twin._left_child = twin._right_child = 0;
    }
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T>
    void
        binary_node_base<Derived,T>::copy_assign(
            BOOST_COPY_ASSIGN_REF(Derived) copy
        )
    {
        Derived twin(static_cast<Derived const&>(copy));

        delete this->_left_child;
        delete this->_right_child;

        this->_data = ::boost::move(twin._data);
        this->_left_child = twin._left_child;
        this->_right_child = twin._right_child;
        twin._left_child = twin._right_child = 0;
    }

    template <typename Derived, typename T>
    void binary_node_base<Derived,T>::move_assign(BOOST_RV_REF(Derived) source)
    {
        delete this->_left_child;
        delete this->_right_child;

        this->_data = ::boost::move(source._data);
        this->_left_child = source._left_child;
        this->_right_child = source._right_child;
        source._left_child = source._right_child = 0;
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::traits::data_type const&
        binary_node_base<Derived,T>::get_data() const
    {
        return this->_data;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::traits::data_type&
        binary_node_base<Derived,T>::get_data()
    {
        return this->_data;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::const_pointer
        binary_node_base<Derived,T>::get_parent_ptr() const
    {
        return this->_parent;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::get_parent_ptr()
    {
        return this->_parent;
    }

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::insert_left(Derived const& child)
    {
        if (this->_left_child)
        {
            return iterator(this->_left_child, true);
        }
        else
        {
            return this->_add_child(this->_left_child = new Derived(child));
        }
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T>
    template <typename ...Args>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::emplace_left(Args&& ...args)
    {
        if (this->_left_child)
        {
            return iterator(this->_left_child, true);
        }
        else
        {
            return this->_add_child(
                this->_left_child = new Derived(
                    ::boost::forward<Args>(args)...
                )
            );
        }
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
    template <typename Derived, typename T>                                  \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binary_node_base<Derived,T>::iterator                           \
        binary_node_base<Derived,T>::emplace_left(                           \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (this->_left_child)                                               \
        {                                                                    \
            return iterator(this->_left_child, true);                        \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            return this->_add_child(                                         \
                this->_left_child = new Derived(                             \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , _                                                    \
                    )                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_BINARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_BINARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::insert_right(Derived const& child)
    {
        if (this->_right_child)
        {
            return iterator(this->_right_child, true);
        }
        else
        {
            return this->_add_child(this->_right_child = new Derived(child));
        }
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T>
    template <typename ...Args>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::emplace_right(Args&& ...args)
    {
        if (this->_right_child)
        {
            return iterator(this->_right_child, true);
        }
        else
        {
            return this->_add_child(
                this->_right_child = new Derived(
                    ::boost::forward<Args>(args)...
                )
            );
        }
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
    template <typename Derived, typename T>                                  \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binary_node_base<Derived,T>::iterator                           \
        binary_node_base<Derived,T>::emplace_right(                          \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (this->_right_child)                                              \
        {                                                                    \
            return iterator(this->_right_child, true);                       \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            return this->_add_child(                                         \
                this->_right_child = new Derived(                            \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , _                                                    \
                    )                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_BINARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_BINARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::const_pointer
        binary_node_base<Derived,T>::get_left_child_ptr() const
    {
        return this->_left_child;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::get_left_child_ptr()
    {
        return this->_left_child;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::const_pointer
        binary_node_base<Derived,T>::get_right_child_ptr() const
    {
        return this->_right_child;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::get_right_child_ptr()
    {
        return this->_right_child;
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
    inline typename binary_node_base<Derived,T>::size_type
        binary_node_base<Derived,T>::size() const
    {
        return (
            this->_left_child
          ? (this->_right_child ? 2 : 1)
          : (this->_right_child ? 1 : 0)
        );
    }

    template <typename Derived, typename T>
    inline bool binary_node_base<Derived,T>::empty() const
    {
        return !this->_left_child && !this->_right_child;
    }

    template <typename Derived, typename T>
    void binary_node_base<Derived,T>::clear()
    {
        delete this->_left_child;
        delete this->_right_child;
        this->_left_child = this->_right_child = 0;
        this->on_post_clear();
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::rotate_left()
    {
        pointer pivot = this->_right_child;

        pivot->_parent = this->_parent;
        this->_right_child = pivot->_left_child;
        this->_right_child->_parent = pivot->_left_child = this->get_derived();

        if (this->_parent)
        {
            if (this->_parent->_left_child == this->get_derived())
            {
                this->_parent->_left_child = pivot;
            }
            else // if (this->_parent->_right_child == this->get_derived())
            {
                this->_parent->_right_child = pivot;
            }
        }

        this->_parent = pivot;
        this->on_post_rotate_left();
        return pivot;
    }

    template <typename Derived, typename T>
    inline typename binary_node_base<Derived,T>::pointer
        binary_node_base<Derived,T>::rotate_right()
    {
        pointer pivot = this->_left_child;

        pivot->_parent = this->_parent;
        this->_left_child = pivot->_right_child;
        this->_left_child->_parent = pivot->_right_child = this->get_derived();

        if (this->_parent)
        {
            if (this->_parent->_right_child == this->get_derived())
            {
                this->_parent->_right_child = pivot;
            }
            else // if (this->_parent->_left_child == this->get_derived())
            {
                this->_parent->_left_child = pivot;
            }
        }

        this->_parent = pivot;
        this->on_post_rotate_right();
        return pivot;
    }

    template <typename Derived, typename T>
    bool binary_node_base<Derived,T>::erase_left()
    {
        if (this->_left_child)
        {
            delete this->_left_child;
            this->_left_child = 0;
            this->on_post_erase();
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Derived, typename T>
    bool binary_node_base<Derived,T>::erase_right()
    {
        if (this->_right_child)
        {
            delete this->_right_child;
            this->_right_child = 0;
            this->on_post_erase();
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Derived, typename T>
    typename binary_node_base<Derived,T>::iterator
        binary_node_base<Derived,T>::_add_child(pointer const& child)
    {
        iterator result(child, true);

        result->_parent = this->get_derived();
        result->on_post_inserted(result, ::boost::mpl::true_());
        return result;
    }

    template <typename Derived, typename T>
    inline void binary_node_base<Derived,T>::_link_children_to_parent()
    {
        if (this->_left_child)
        {
            this->_left_child->_parent = this->get_derived();
        }

        if (this->_right_child)
        {
            this->_right_child->_parent = this->get_derived();
        }
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <typename T>
    class binary_node
      : public
        //[reference__binary_node__bases
        binary_node_base<binary_node<T>,T>
        //]
    {
        //[reference__binary_node__super_t
        typedef binary_node_base<binary_node<T>,T> super_t;
        //]

     public:
        //[reference__binary_node__traits
        typedef typename super_t::traits traits;
        //]

        //[reference__binary_node__pointer
        typedef typename super_t::pointer pointer;
        //]

        //[reference__binary_node__const_pointer
        typedef typename super_t::const_pointer const_pointer;
        //]

        //[reference__binary_node__iterator
        typedef typename super_t::iterator iterator;
        //]

        //[reference__binary_node__const_iterator
        typedef typename super_t::const_iterator const_iterator;
        //]

        //[reference__binary_node__size_type
        typedef typename super_t::size_type size_type;
        //]

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(binary_node, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binary_node__emplacement_ctor
        template <typename ...Args>
        explicit binary_node(Args&& ...args);
        //]
#else
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (binary_node, super_t)
        )
#endif
    };

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename T>
    template <typename ...Args>
    inline binary_node<T>::binary_node(Args&& ...args)
      : super_t(::boost::forward<Args>(args)...)
    {
    }
#endif
}}  // namespace boost::tree_node

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

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED

