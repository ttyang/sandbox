// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED

#include <iterator>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/container/scoped_allocator_fwd.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/binary_node_fwd.hpp>
#include <boost/tree_node/traits/binary_node_fwd.hpp>
#include <boost/tree_node/intrinsic/has_key.hpp>
#include <boost/tree_node/intrinsic/get_keys.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/assert.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/move/move.hpp>
#include <boost/container/allocator_traits.hpp>
#endif

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#include <boost/tree_node/_detail/config_begin.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/type_traits/is_pod.hpp>

namespace boost {

    template <typename Derived, typename T, typename Size, typename Allocator>
    struct is_POD<
        ::boost::tree_node::binary_node_base<Derived,T,Size,Allocator>
    > : ::boost::false_type
    {
    };

    template <typename Derived, typename T, typename Size, typename Allocator>
    struct is_pod<
        ::boost::tree_node::binary_node_base<Derived,T,Size,Allocator>
    > : ::boost::false_type
    {
    };
}  // namespace boost
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace tree_node { namespace result_of {

    template <
        typename Derived
      , typename T
      , typename Size
      , typename Allocator
      , typename FusionKey
    >
    struct has_key_impl<
        binary_node_base<Derived,T,Size,Allocator>
      , FusionKey
    > : ::boost::mpl::eval_if<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , ::boost::fusion::result_of::has_key<T,FusionKey>
          , ::std::tr1::is_same<FusionKey,data_key>
        >::type
    {
    };

    template <
        typename Derived
      , typename T
      , typename Size
      , typename Allocator
    >
    struct get_keys_impl<binary_node_base<Derived,T,Size,Allocator> >
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , ::boost::mpl::transform_view<
                T
              , ::boost::fusion::result_of::key_of< ::boost::mpl::_>
            >
          , ::boost::mpl::vector1<data_key>
        >
    {
    };
}}}  // namespace boost::tree_node::result_of
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

namespace boost { namespace tree_node { namespace _detail {

    template <typename Node, typename IsReverse>
    class binary_child_iterator
    {
#if !defined BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

     public:
        typedef ::std::random_access_iterator_tag iterator_category;
        typedef Node value_type;
        typedef ::std::ptrdiff_t difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;

     private:
        class proxy
        {
            binary_child_iterator _itr;

         public:
            proxy(pointer const& p, difference_type n);

            operator binary_child_iterator&();
        };

     public:  // Should be private, but conversion ctor won't work.
        pointer _current;
        pointer _parent;

     public:
        binary_child_iterator();

        explicit binary_child_iterator(pointer const& p);

        binary_child_iterator(pointer const& p, bool p_is_child);

        template <typename N, typename I>
        binary_child_iterator(
            binary_child_iterator<N,I> const& other
#if !defined BOOST_NO_SFINAE
          , typename ::boost::enable_if<
                typename ::boost::mpl::if_<
                    ::std::tr1::is_convertible<N,Node>
                  , ::boost::mpl::equal_to<I,IsReverse>
                  , ::boost::mpl::false_
                >::type
              , enabler
            >::type = enabler()
#endif
        );

        reference operator*() const;

        pointer operator->() const;

        proxy operator[](difference_type n) const;

        binary_child_iterator& operator++();

        binary_child_iterator operator++(int);

        binary_child_iterator& operator--();

        binary_child_iterator operator--(int);

        binary_child_iterator& operator+=(difference_type n);

        binary_child_iterator operator+(difference_type n) const;

        binary_child_iterator& operator-=(difference_type n);

        binary_child_iterator operator-(difference_type n) const;

     private:
        void _iterate(pointer const& sibling);

        void _advance(difference_type n);

        template <typename N1, typename I1, typename N2, typename I2>
        friend
#if defined BOOST_NO_SFINAE
        bool
#else
        typename ::boost::enable_if< ::boost::mpl::equal_to<I1,I2>,bool>::type
#endif
            operator==(
                binary_child_iterator<N1,I1> const& lhs
              , binary_child_iterator<N2,I2> const& rhs
            );

        template <typename N1, typename I1, typename N2, typename I2>
        friend
#if defined BOOST_NO_SFINAE
        bool
#else
        typename ::boost::enable_if< ::boost::mpl::equal_to<I1,I2>,bool>::type
#endif
            operator<(
                binary_child_iterator<N1,I1> const& lhs
              , binary_child_iterator<N2,I2> const& rhs
            );

        template <typename N1, typename I1, typename N2, typename I2>
        friend ::std::ptrdiff_t
            operator-(
                binary_child_iterator<N1,I1> const& lhs
              , binary_child_iterator<N2,I2> const& rhs
            );
    };

    template <typename Node, typename IsReverse>
    binary_child_iterator<Node,IsReverse>::proxy::proxy(
        pointer const& p
      , difference_type n
    ) : _itr(p, true)
    {
        this->_itr._advance(n);
    }

    template <typename Node, typename IsReverse>
    inline binary_child_iterator<
        Node
      , IsReverse
    >::proxy::operator binary_child_iterator&()
    {
        return this->_itr;
    }

    template <typename Node, typename IsReverse>
    binary_child_iterator<Node,IsReverse>::binary_child_iterator()
      : _current(::boost::initialized_value)
      , _parent(::boost::initialized_value)
    {
    }

    template <typename Node, typename IsReverse>
    binary_child_iterator<Node,IsReverse>::binary_child_iterator(
        pointer const& p
      , bool p_is_child
    ) : _current(
            p_is_child ? p : IsReverse::value ? (
                p->get_right_child_ptr()
              ? p->get_right_child_ptr()
              : p->get_left_child_ptr()
            ) : (
                p->get_left_child_ptr()
              ? p->get_left_child_ptr()
              : p->get_right_child_ptr()
            )
        )
      , _parent(p_is_child ? p->get_parent_ptr() : p)
    {
    }

    template <typename Node, typename IsReverse>
    binary_child_iterator<Node,IsReverse>::binary_child_iterator(
        pointer const& p
    ) : _current(::boost::initialized_value), _parent(p)
    {
    }

    template <typename Node, typename IsReverse>
    template <typename N, typename I>
    binary_child_iterator<Node,IsReverse>::binary_child_iterator(
        binary_child_iterator<N,I> const& other
#if !defined BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            typename ::boost::mpl::if_<
                ::std::tr1::is_convertible<N,Node>
              , ::boost::mpl::equal_to<I,IsReverse>
              , ::boost::mpl::false_
            >::type
          , enabler
        >::type
#endif
    ) : _current(other._current), _parent(other._parent)
    {
    }

    template <typename Node, typename IsReverse>
    inline typename binary_child_iterator<Node,IsReverse>::reference
        binary_child_iterator<Node,IsReverse>::operator*() const
    {
        return *this->_current;
    }

    template <typename Node, typename IsReverse>
    inline typename binary_child_iterator<Node,IsReverse>::pointer
        binary_child_iterator<Node,IsReverse>::operator->() const
    {
        return this->_current;
    }

    template <typename Node, typename IsReverse>
    inline typename binary_child_iterator<Node,IsReverse>::proxy
        binary_child_iterator<Node,IsReverse>::operator[](
            difference_type n
        ) const
    {
        return proxy(this->_current, n);
    }

    template <typename Node, typename IsReverse>
    inline binary_child_iterator<Node,IsReverse>&
        binary_child_iterator<Node,IsReverse>::operator++()
    {
        this->_iterate(
            IsReverse::value
          ? this->_parent->get_left_child_ptr()
          : this->_parent->get_right_child_ptr()
        );
        return *this;
    }

    template <typename Node, typename IsReverse>
    binary_child_iterator<Node,IsReverse>
        binary_child_iterator<Node,IsReverse>::operator++(int)
    {
        binary_child_iterator itr(*this);
        ++(*this);
        return itr;
    }

    template <typename Node, typename IsReverse>
    inline binary_child_iterator<Node,IsReverse>&
        binary_child_iterator<Node,IsReverse>::operator--()
    {
        if (this->_current)
        {
            this->_iterate(
                IsReverse::value
              ? this->_parent->get_right_child_ptr()
              : this->_parent->get_left_child_ptr()
            );
        }
        else if (IsReverse::value)
        {
            this->_current = this->_parent->get_left_child_ptr();

            if (!this->_current)
            {
                this->_current = this->_parent->get_right_child_ptr();
            }
        }
        else
        {
            this->_current = this->_parent->get_right_child_ptr();

            if (!this->_current)
            {
                this->_current = this->_parent->get_left_child_ptr();
            }
        }

        BOOST_ASSERT_MSG(this->_current, "Result not dereferenceable.");
        return *this;
    }

    template <typename Node, typename IsReverse>
    binary_child_iterator<Node,IsReverse>
        binary_child_iterator<Node,IsReverse>::operator--(int)
    {
        binary_child_iterator itr(*this);
        --(*this);
        return itr;
    }

    template <typename Node, typename IsReverse>
    inline binary_child_iterator<Node,IsReverse>&
        binary_child_iterator<Node,IsReverse>::operator+=(difference_type n)
    {
        this->_advance(n);
        return *this;
    }

    template <typename Node, typename IsReverse>
    binary_child_iterator<Node,IsReverse>
        binary_child_iterator<Node,IsReverse>::operator+(
            difference_type n
        ) const
    {
        binary_child_iterator itr(*this);
        itr += n;
        return itr;
    }

    template <typename Node, typename IsReverse>
    inline binary_child_iterator<Node,IsReverse>&
        binary_child_iterator<Node,IsReverse>::operator-=(difference_type n)
    {
        this->_advance(-n);
        return *this;
    }

    template <typename Node, typename IsReverse>
    binary_child_iterator<Node,IsReverse>
        binary_child_iterator<Node,IsReverse>::operator-(
            difference_type n
        ) const
    {
        binary_child_iterator itr(*this);
        itr -= n;
        return itr;
    }

    template <typename Node, typename IsReverse>
    inline void
        binary_child_iterator<Node,IsReverse>::_iterate(pointer const& sibling)
    {
        this->_current = (
            this->_current == sibling
        ) ? ::boost::initialized_value : sibling;
    }

    template <typename Node, typename IsReverse>
    inline void
        binary_child_iterator<Node,IsReverse>::_advance(difference_type n)
    {
        switch (n)
        {
            case -2:
            {
                BOOST_ASSERT_MSG(
                    (
                        IsReverse::value
                      ? (
                            (
                                this->_current == (
                                    this->_parent->get_left_child_ptr()
                                )
                            ) && this->_parent->get_right_child_ptr()
                        )
                      : (
                            (
                                this->_current == (
                                    this->_parent->get_right_child_ptr()
                                )
                            ) && this->_parent->get_left_child_ptr()
                        )
                    )
                  , "n must be greater than -2."
                );

                this->_current = ::boost::initialized_value;
                break;
            }

            case -1:
            {
                --(*this);
                break;
            }

            case 0:
            {
                break;
            }

            case 1:
            {
                ++(*this);
                break;
            }

            case 2:
            {
                BOOST_ASSERT_MSG(
                    (
                        IsReverse::value
                      ? (
                            (
                                this->_current == (
                                    this->_parent->get_right_child_ptr()
                                )
                            ) && this->_parent->get_left_child_ptr()
                        )
                      : (
                            (
                                this->_current == (
                                    this->_parent->get_left_child_ptr()
                                )
                            ) && this->_parent->get_right_child_ptr()
                        )
                    )
                  , "n must be less than 2."
                );

                this->_current = ::boost::initialized_value;
                break;
            }

            default:
            {
                BOOST_ASSERT_MSG(false, "|n| must be less than 3.");
            }
        }
    }

    template <typename Node1, typename IsR1, typename Node2, typename IsR2>
    inline
#if defined BOOST_NO_SFINAE
    bool
#else
    typename ::boost::enable_if< ::boost::mpl::equal_to<IsR1,IsR2>,bool>::type
#endif
        operator==(
            binary_child_iterator<Node1,IsR1> const& lhs
          , binary_child_iterator<Node2,IsR2> const& rhs
        )
    {
        return lhs._current == rhs._current;
    }

    template <typename Node1, typename IsR1, typename Node2, typename IsR2>
    inline
#if defined BOOST_NO_SFINAE
    bool
#else
    typename ::boost::enable_if< ::boost::mpl::equal_to<IsR1,IsR2>,bool>::type
#endif
        operator!=(
            binary_child_iterator<Node1,IsR1> const& lhs
          , binary_child_iterator<Node2,IsR2> const& rhs
        )
    {
        return !(lhs == rhs);
    }

    template <typename Node1, typename IsR1, typename Node2, typename IsR2>
    inline
#if defined BOOST_NO_SFINAE
    bool
#else
    typename ::boost::enable_if< ::boost::mpl::equal_to<IsR1,IsR2>,bool>::type
#endif
        operator<(
            binary_child_iterator<Node1,IsR1> const& lhs
          , binary_child_iterator<Node2,IsR2> const& rhs
        )
    {
        BOOST_ASSERT_MSG(lhs._parent, "lhs is unreachable.");
        BOOST_ASSERT_MSG(rhs._parent, "rhs is unreachable.");
        BOOST_ASSERT_MSG(
            rhs._parent == lhs._parent
          , "Neither iterator is reachable from one other."
        );

        if (lhs._current)
        {
            if (rhs._current)
            {
                return rhs._current == lhs._parent->get_right_child_ptr();
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    template <typename Node1, typename IsR1, typename Node2, typename IsR2>
    inline
#if defined BOOST_NO_SFINAE
    bool
#else
    typename ::boost::enable_if< ::boost::mpl::equal_to<IsR1,IsR2>,bool>::type
#endif
        operator>(
            binary_child_iterator<Node1,IsR1> const& lhs
          , binary_child_iterator<Node2,IsR2> const& rhs
        )
    {
        return rhs < lhs;
    }

    template <typename Node1, typename IsR1, typename Node2, typename IsR2>
    inline
#if defined BOOST_NO_SFINAE
    bool
#else
    typename ::boost::enable_if< ::boost::mpl::equal_to<IsR1,IsR2>,bool>::type
#endif
        operator<=(
            binary_child_iterator<Node1,IsR1> const& lhs
          , binary_child_iterator<Node2,IsR2> const& rhs
        )
    {
        return !(rhs < lhs);
    }

    template <typename Node1, typename IsR1, typename Node2, typename IsR2>
    inline
#if defined BOOST_NO_SFINAE
    bool
#else
    typename ::boost::enable_if< ::boost::mpl::equal_to<IsR1,IsR2>,bool>::type
#endif
        operator>=(
            binary_child_iterator<Node1,IsR1> const& lhs
          , binary_child_iterator<Node2,IsR2> const& rhs
        )
    {
        return !(lhs < rhs);
    }

    template <typename Node, typename IsReverse>
    inline binary_child_iterator<Node,IsReverse>
        operator+(
            typename binary_child_iterator<Node,IsReverse>::difference_type n
          , binary_child_iterator<Node,IsReverse> const& itr
        )
    {
        return itr + n;
    }

    template <typename Node1, typename IsR1, typename Node2, typename IsR2>
    inline ::std::ptrdiff_t
        operator-(
            binary_child_iterator<Node1,IsR1> const& lhs
          , binary_child_iterator<Node2,IsR2> const& rhs
        )
    {
        BOOST_ASSERT_MSG(lhs._parent, "lhs is unreachable.");
        BOOST_ASSERT_MSG(rhs._parent, "rhs is unreachable.");
        BOOST_ASSERT_MSG(
            rhs._parent == lhs._parent
          , "Neither iterator is reachable from one other."
        );

        if (lhs._current == rhs._current)
        {
            return 0;
        }
        else if (lhs._current)
        {
            if (rhs._current)
            {
                return (
                    rhs._current == lhs._parent->get_left_child_ptr()
                ) ? 1 : -1;
            }
            else
            {
                return (
                    lhs._parent->get_left_child_ptr() && (
                        lhs._parent->get_right_child_ptr()
                    )
                ) ? 2 : 1;
            }
        }
        else
        {
            return (
                rhs._parent->get_left_child_ptr() && (
                    rhs._parent->get_right_child_ptr()
                )
            ) ? -2 : -1;
        }
    }
}}}  // namespace boost::tree_node::_detail

namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Size, typename Allocator>
    class binary_node_base
      : public
        //[reference__binary_node_base__bases
        tree_node_base<Derived>
        //]
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      , public data_key
#endif
      , private ::boost::noncopyable
    {
        template <typename D>
        friend struct binary_node_traits;

     public:
        //[reference__binary_node_base__super_t
        typedef tree_node_base<Derived> super_t;
        //]

        //[reference__binary_node_base__traits
        struct traits
        {
            typedef T
                    data_type;
            typedef typename ::std::tr1::remove_reference<Allocator>::type
                    allocator;
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_reference<Allocator>
                      , Allocator
                      , typename ::std::tr1::add_reference<
                            typename ::std::tr1::add_const<Allocator>::type
                        >::type
                    >::type
                    allocator_reference;
        };
        //]

        //[reference__binary_node_base__pointer
        typedef typename super_t::pointer pointer;
        //]

        //[reference__binary_node_base__const_pointer
        typedef typename super_t::const_pointer const_pointer;
        //]

        typedef _detail::binary_child_iterator<Derived,::boost::mpl::false_>
                iterator;
        typedef _detail::binary_child_iterator<
                    Derived const
                  , ::boost::mpl::false_
                >
                const_iterator;
        typedef _detail::binary_child_iterator<Derived,::boost::mpl::true_>
                reverse_iterator;
        typedef _detail::binary_child_iterator<
                    Derived const
                  , ::boost::mpl::true_
                >
                const_reverse_iterator;

#if 0
        //[reference__binary_node_base__iterator
        typedef implementation_defined iterator;
        //]

        //[reference__binary_node_base__const_iterator
        typedef implementation_defined const_iterator;
        //]

        //[reference__binary_node_base__reverse_iterator
        typedef implementation_defined reverse_iterator;
        //]

        //[reference__binary_node_base__const_reverse_iterator
        typedef implementation_defined const_reverse_iterator;
        //]
#endif

        //[reference__binary_node_base__size_type
        typedef Size size_type;
        //]

     private:
        typename traits::data_type _data;
        Allocator                  _allocator;
        pointer                    _left_child;
        pointer                    _right_child;
        pointer                    _parent;

     protected:
        //[reference__binary_node_base__derived_copy_ctor
        binary_node_base(Derived const& copy);
        //]

        //[reference__binary_node_base__derived_copy_ctor_w_allocator
        binary_node_base(
            Derived const& copy
          , typename traits::allocator_reference allocator
        );
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        binary_node_base(BOOST_RV_REF(Derived) source);

        binary_node_base(
            BOOST_RV_REF(Derived) source
          , typename traits::allocator_reference allocator
        );
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binary_node_base__emplacement_ctor
        template <typename ...Args>
        explicit binary_node_base(Args&& ...args);
        //]

        //[reference__binary_node_base__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit binary_node_base(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_FWD_DECL
          , binary_node_base
        )

        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_FWD_DECL
          , binary_node_base
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

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
        //[reference__binary_node_base__key_value_operator__const
        typename traits::data_type const& operator[](data_key const&) const;

//<-
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
//->
        template <typename FusionKey>
        typename ::boost::lazy_enable_if<
            typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                    typename ::boost::fusion::traits::is_sequence<T>::type
                  , ::boost::fusion::traits::is_associative<T>
                  , ::boost::mpl::false_
                >::type
              , result_of::has_key<
                    binary_node_base<Derived,T,Size,Allocator>
                  , FusionKey
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::fusion::result_of::at_key<T const,FusionKey>
        >::type
            operator[](FusionKey const&) const;
//<-
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
//->
        //]

        //[reference__binary_node_base__key_value_operator
        typename traits::data_type& operator[](data_key const&);

//<-
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
//->
        template <typename FusionKey>
        typename ::boost::lazy_enable_if<
            typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                    typename ::boost::fusion::traits::is_sequence<T>::type
                  , ::boost::fusion::traits::is_associative<T>
                  , ::boost::mpl::false_
                >::type
              , result_of::has_key<
                    binary_node_base<Derived,T,Size,Allocator>
                  , FusionKey
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::fusion::result_of::at_key<T,FusionKey>
        >::type
            operator[](FusionKey const&);
//<-
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
//->
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

        //[reference__binary_node_base__cbegin
        const_iterator cbegin() const;
        const_iterator begin() const;
        //]

        //[reference__binary_node_base__begin
        iterator begin();
        //]

        //[reference__binary_node_base__cend
        const_iterator cend() const;
        const_iterator end() const;
        //]

        //[reference__binary_node_base__end
        iterator end();
        //]

        //[reference__binary_node_base__crbegin
        const_reverse_iterator crbegin() const;
        const_reverse_iterator rbegin() const;
        //]

        //[reference__binary_node_base__rbegin
        reverse_iterator rbegin();
        //]

        //[reference__binary_node_base__crend
        const_reverse_iterator crend() const;
        const_reverse_iterator rend() const;
        //]

        //[reference__binary_node_base__rend
        reverse_iterator rend();
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
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        static typename traits::allocator_reference
            _construct_from(
                typename traits::allocator_reference allocator
              , ::std::tr1::true_type
            );

        static Allocator
            _construct_from(
                typename traits::allocator_reference allocator
              , ::std::tr1::false_type
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

        iterator _add_child(pointer const& child);

        void _link_children_to_parent();

        void _on_post_modify_value(data_key const& key);

        void _set_parent_ptr(pointer p);

        void _set_left_child_ptr(pointer p);

        void _set_right_child_ptr(pointer p);

        template <typename D, typename T0, typename S, typename A, typename V>
        friend void
            put(binary_node_base<D,T0,S,A>&, data_key const&, V const&);

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        template <typename FusionKey>
        void _on_post_modify_value(FusionKey const& key);

        template <
            typename D
          , typename T0
          , typename S
          , typename A
          , typename FK
          , typename V
        >
        friend void
          put(
            binary_node_base<D,T0,S,A>& node
          , FK const& key
          , V const& value
          , typename ::boost::enable_if<
              typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                  typename ::boost::fusion::traits::is_sequence<T0>::type
                , ::boost::fusion::traits::is_associative<T0>
                , ::boost::mpl::false_
                >::type
              , result_of::has_key<binary_node_base<D,T0,S,A>,FK>
              , ::boost::mpl::false_
              >::type
            , ::boost::mpl::true_
            >::type
          );
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
    };

    template <typename Derived, typename T, typename Size, typename Allocator>
    binary_node_base<Derived,T,Size,Allocator>::binary_node_base(
        Derived const& copy
    ) : _data(copy._data)
      , _allocator(
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            copy._allocator
#else
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::select_on_container_copy_construction(copy._allocator)
#endif
        )
      , _left_child(
            copy._left_child ? (
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                this->_allocator.allocate(1)
#else
                ::boost::container::allocator_traits<
                    typename traits::allocator
                >::allocate(this->_allocator, 1)
#endif
            ) : ::boost::initialized_value
        )
      , _right_child(
            copy._right_child ? (
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                this->_allocator.allocate(1)
#else
                ::boost::container::allocator_traits<
                    typename traits::allocator
                >::allocate(this->_allocator, 1)
#endif
            ) : ::boost::initialized_value
        )
      , _parent(::boost::initialized_value)
    {
        if (this->_left_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.construct(
                this->_left_child
              , *copy.get_left_child_ptr()
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::construct(
                this->_allocator
              , this->_left_child
              , *copy.get_left_child_ptr()
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }

        if (this->_right_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.construct(
                this->_right_child
              , *copy.get_right_child_ptr()
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::construct(
                this->_allocator
              , this->_right_child
              , *copy.get_right_child_ptr()
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    binary_node_base<Derived,T,Size,Allocator>::binary_node_base(
        Derived const& copy
      , typename traits::allocator_reference allocator
    ) : _data(copy._data)
      , _allocator(
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            allocator
#else
            this->_construct_from(
                allocator
              , typename ::std::tr1::is_reference<Allocator>::type()
            )
#endif
        )
      , _left_child(
            copy._left_child ? (
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                this->_allocator.allocate(1)
#else
                ::boost::container::allocator_traits<
                    typename traits::allocator
                >::allocate(this->_allocator, 1)
#endif
            ) : ::boost::initialized_value
        )
      , _right_child(
            copy._right_child ? (
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                this->_allocator.allocate(1)
#else
                ::boost::container::allocator_traits<
                    typename traits::allocator
                >::allocate(this->_allocator, 1)
#endif
            ) : ::boost::initialized_value
        )
      , _parent(::boost::initialized_value)
    {
        if (this->_left_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.construct(
                this->_left_child
              , *copy.get_left_child_ptr()
              , allocator
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::construct(
                this->_allocator
              , this->_left_child
              , *copy.get_left_child_ptr()
              , allocator
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }

        if (this->_right_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.construct(
                this->_right_child
              , *copy.get_right_child_ptr()
              , allocator
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::construct(
                this->_allocator
              , this->_right_child
              , *copy.get_right_child_ptr()
              , allocator
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Size, typename Allocator>
    binary_node_base<Derived,T,Size,Allocator>::binary_node_base(
        BOOST_RV_REF(Derived) source
    ) : _data(::boost::move(source._data))
      , _allocator(::boost::move(source._allocator))
      , _left_child(source._left_child)
      , _right_child(source._right_child)
      , _parent(::boost::initialized_value)
    {
        source._left_child = source._right_child = ::boost::initialized_value;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    binary_node_base<Derived,T,Size,Allocator>::binary_node_base(
        BOOST_RV_REF(Derived) source
      , typename traits::allocator_reference allocator
    ) : _data(::boost::move(source._data))
      , _allocator(
            this->_construct_from(
                allocator
              , typename ::std::tr1::is_reference<Allocator>::type()
            )
        )
      , _left_child(source._left_child)
      , _right_child(source._right_child)
      , _parent(::boost::initialized_value)
    {
        source._left_child = source._right_child = ::boost::initialized_value;
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T, typename Size, typename Allocator>
    template <typename ...Args>
    binary_node_base<Derived,T,Size,Allocator>::binary_node_base(
        Args&& ...args
    ) : _data(::boost::forward<Args>(args)...)
      , _allocator()
      , _left_child(::boost::initialized_value)
      , _right_child(::boost::initialized_value)
      , _parent(::boost::initialized_value)
    {
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    template <typename ...Args>
    binary_node_base<Derived,T,Size,Allocator>::binary_node_base(
        ::boost::container::allocator_arg_t
      , typename traits::allocator_reference allocator
      , Args&& ...args
    ) : _data(::boost::forward<Args>(args)...)
      , _allocator(
            this->_construct_from(
                allocator
              , typename ::std::tr1::is_reference<Allocator>::type()
            )
        )
      , _left_child(::boost::initialized_value)
      , _right_child(::boost::initialized_value)
      , _parent(::boost::initialized_value)
    {
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
    template <                                                               \
        typename Derived                                                     \
      , typename T                                                           \
      , typename Size                                                        \
      , typename Allocator                                                   \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    binary_node_base<Derived,T,Size,Allocator>::binary_node_base(            \
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
      , _allocator()                                                         \
      , _left_child(::boost::initialized_value)                              \
      , _right_child(::boost::initialized_value)                             \
      , _parent(::boost::initialized_value)                                  \
    {                                                                        \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_BINARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_BINARY_NODE_MACRO

#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
    template <                                                               \
        typename Derived                                                     \
      , typename T                                                           \
      , typename Size                                                        \
      , typename Allocator                                                   \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    binary_node_base<Derived,T,Size,Allocator>::binary_node_base(            \
        ::boost::container::allocator_arg_t                                  \
      , typename traits::allocator_reference allocator                       \
        BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                            \
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
      , _allocator(                                                          \
            this->_construct_from(                                           \
                allocator                                                    \
              , typename ::std::tr1::is_reference<Allocator>::type()         \
            )                                                                \
        )                                                                    \
      , _left_child(::boost::initialized_value)                              \
      , _right_child(::boost::initialized_value)                             \
      , _parent(::boost::initialized_value)                                  \
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

    template <typename Derived, typename T, typename Size, typename Allocator>
    binary_node_base<Derived,T,Size,Allocator>::~binary_node_base()
    {
        if (this->_left_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.destroy(this->_left_child);
            this->_allocator.deallocate(this->_left_child, 1);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_left_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_left_child, 1);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }

        if (this->_right_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.destroy(this->_right_child);
            this->_allocator.deallocate(this->_right_child, 1);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_right_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_right_child, 1);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline void
        binary_node_base<Derived,T,Size,Allocator>::on_post_copy_or_move()
    {
        this->_link_children_to_parent();
        this->on_post_modify_value(data_key());
    }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Size, typename Allocator>
    void
        binary_node_base<Derived,T,Size,Allocator>::copy_assign(
            Derived const& copy
        )
    {
        Derived twin(copy);

        if (this->_left_child)
        {
            this->_allocator.destroy(this->_left_child);
            this->_allocator.deallocate(this->_left_child, 1);
        }

        if (this->_right_child)
        {
            this->_allocator.destroy(this->_right_child);
            this->_allocator.deallocate(this->_right_child, 1);
        }

        this->_data = twin._data;
        this->_left_child = twin._left_child;
        this->_right_child = twin._right_child;
        twin._left_child = twin._right_child = ::boost::initialized_value;
    }
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Size, typename Allocator>
    void
        binary_node_base<Derived,T,Size,Allocator>::copy_assign(
            BOOST_COPY_ASSIGN_REF(Derived) copy
        )
    {
        Derived twin(static_cast<Derived const&>(copy));

        if (this->_left_child)
        {
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_left_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_left_child, 1);
        }

        if (this->_right_child)
        {
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_right_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_right_child, 1);
        }

        this->_data = ::boost::move(twin._data);
        this->_left_child = twin._left_child;
        this->_right_child = twin._right_child;
        twin._left_child = twin._right_child = ::boost::initialized_value;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline void
        binary_node_base<Derived,T,Size,Allocator>::move_assign(
            BOOST_RV_REF(Derived) source
        )
    {
        if (this->_left_child)
        {
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_left_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_left_child, 1);
        }

        if (this->_right_child)
        {
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_right_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_right_child, 1);
        }

        this->_data = ::boost::move(source._data);
        this->_left_child = source._left_child;
        this->_right_child = source._right_child;
        source._left_child = source._right_child = ::boost::initialized_value;
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::traits::data_type const&
        binary_node_base<Derived,T,Size,Allocator>::operator[](
            data_key const&
        ) const
    {
        return this->_data;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::traits::data_type&
        binary_node_base<Derived,T,Size,Allocator>::operator[](data_key const&)
    {
        return this->_data;
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    template <typename Derived, typename T, typename Size, typename Allocator>
    template <typename FusionKey>
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                binary_node_base<Derived,T,Size,Allocator>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T const,FusionKey>
    >::type
        binary_node_base<Derived,T,Size,Allocator>::operator[](
            FusionKey const&
        ) const
    {
        return ::boost::fusion::at_key<FusionKey>(this->_data);
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    template <typename FusionKey>
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                binary_node_base<Derived,T,Size,Allocator>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T,FusionKey>
    >::type
        binary_node_base<Derived,T,Size,Allocator>::operator[](
            FusionKey const&
        )
    {
        return ::boost::fusion::at_key<FusionKey>(this->_data);
    }
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::const_pointer
        binary_node_base<Derived,T,Size,Allocator>::get_parent_ptr() const
    {
        return this->_parent;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::pointer
        binary_node_base<Derived,T,Size,Allocator>::get_parent_ptr()
    {
        return this->_parent;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    typename binary_node_base<Derived,T,Size,Allocator>::iterator
        binary_node_base<Derived,T,Size,Allocator>::insert_left(
            Derived const& child
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        pointer p(this->_allocator.allocate(1));
        this->_allocator.construct(p, child);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        pointer p(
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::allocate(this->_allocator, 1)
        );
        ::boost::container::allocator_traits<
            typename traits::allocator
        >::construct(this->_allocator, p, child);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

        pointer c = p->_left_child;

        if (c)
        {
            while (c->_left_child)
            {
                c = c->_left_child;
            }

            c->_add_child(c->_left_child = this->_left_child);
            this->_left_child = ::boost::initialized_value;
            this->on_post_erase();
        }

        return this->_add_child(this->_left_child = p);
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T, typename Size, typename Allocator>
    template <typename ...Args>
    typename binary_node_base<Derived,T,Size,Allocator>::iterator
        binary_node_base<Derived,T,Size,Allocator>::emplace_left(
            Args&& ...args
        )
    {
        if (this->_left_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            pointer p(this->_allocator.allocate(1));
            this->_allocator.construct(p, ::boost::forward<Args>(args)...);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            pointer p(
                ::boost::container::allocator_traits<
                    typename traits::allocator
                >::allocate(this->_allocator, 1)
            );
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::construct(this->_allocator, p, ::boost::forward<Args>(args)...);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            p->_add_child(p->_left_child = this->_left_child);
            this->_left_child = ::boost::initialized_value;
            this->on_post_erase();
            return this->_add_child(this->_left_child = p);
        }
        else
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.construct(
                this->_left_child = this->_allocator.allocate(1)
              , ::boost::forward<Args>(args)...
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::construct(
                this->_allocator
              , this->_left_child = ::boost::container::allocator_traits<
                    typename traits::allocator
                >::allocate(this->_allocator, 1)
              , ::boost::forward<Args>(args)...
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            return this->_add_child(this->_left_child);
        }
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
    template <                                                               \
        typename Derived                                                     \
      , typename T                                                           \
      , typename Size                                                        \
      , typename Allocator                                                   \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binary_node_base<Derived,T,Size,Allocator>::iterator            \
        binary_node_base<Derived,T,Size,Allocator>::emplace_left(            \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (this->_left_child)                                               \
        {                                                                    \
            pointer p(this->_allocator.allocate(1));                         \
            this->_allocator.construct(                                      \
                p                                                            \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
            p->_add_child(p->_left_child = this->_left_child);               \
            this->_left_child = ::boost::initialized_value;                  \
            this->on_post_erase();                                           \
            return this->_add_child(this->_left_child = p);                  \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            this->_allocator.construct(                                      \
                this->_left_child = this->_allocator.allocate(1)             \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
            return this->_add_child(this->_left_child);                      \
        }                                                                    \
    }                                                                        \
//!
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
    template <                                                               \
        typename Derived                                                     \
      , typename T                                                           \
      , typename Size                                                        \
      , typename Allocator                                                   \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binary_node_base<Derived,T,Size,Allocator>::iterator            \
        binary_node_base<Derived,T,Size,Allocator>::emplace_left(            \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (this->_left_child)                                               \
        {                                                                    \
            pointer p(                                                       \
                ::boost::container::allocator_traits<                        \
                    typename traits::allocator                               \
                >::allocate(this->_allocator, 1)                             \
            );                                                               \
            ::boost::container::allocator_traits<                            \
                typename traits::allocator                                   \
            >::construct(                                                    \
                this->_allocator                                             \
              , p                                                            \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
            p->_add_child(p->_left_child = this->_left_child);               \
            this->_left_child = ::boost::initialized_value;                  \
            this->on_post_erase();                                           \
            return this->_add_child(this->_left_child = p);                  \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            ::boost::container::allocator_traits<                            \
                typename traits::allocator                                   \
            >::construct(                                                    \
                this->_allocator                                             \
              , this->_left_child = ::boost::container::allocator_traits<    \
                    typename traits::allocator                               \
                >::allocate(this->_allocator, 1)                             \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
            return this->_add_child(this->_left_child);                      \
        }                                                                    \
    }                                                                        \
//!
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_BINARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_BINARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename T, typename Size, typename Allocator>
    typename binary_node_base<Derived,T,Size,Allocator>::iterator
        binary_node_base<Derived,T,Size,Allocator>::insert_right(
            Derived const& child
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        pointer p(this->_allocator.allocate(1));
        this->_allocator.construct(p, child);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        pointer p(
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::allocate(this->_allocator, 1)
        );
        ::boost::container::allocator_traits<
            typename traits::allocator
        >::construct(this->_allocator, p, child);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

        pointer c = p->_right_child;

        if (c)
        {
            while (c->_right_child)
            {
                c = c->_right_child;
            }

            c->_add_child(c->_right_child = this->_right_child);
            this->_right_child = ::boost::initialized_value;
            this->on_post_erase();
        }

        return this->_add_child(this->_right_child = p);
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T, typename Size, typename Allocator>
    template <typename ...Args>
    typename binary_node_base<Derived,T,Size,Allocator>::iterator
        binary_node_base<Derived,T,Size,Allocator>::emplace_right(
            Args&& ...args
        )
    {
        if (this->_right_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            pointer p(this->_allocator.allocate(1));
            this->_allocator.construct(p, ::boost::forward<Args>(args)...);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            pointer p(
                ::boost::container::allocator_traits<
                    typename traits::allocator
                >::allocate(this->_allocator, 1)
            );
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::construct(this->_allocator, p, ::boost::forward<Args>(args)...);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            p->_add_child(p->_right_child = this->_right_child);
            this->_right_child = ::boost::initialized_value;
            this->on_post_erase();
            return this->_add_child(this->_right_child = p);
        }
        else
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.construct(
                this->_right_child = this->_allocator.allocate(1)
              , ::boost::forward<Args>(args)...
            );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::construct(
                this->_allocator
              , this->_right_child = ::boost::container::allocator_traits<
                    typename traits::allocator
                >::allocate(this->_allocator, 1)
              , ::boost::forward<Args>(args)...
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            return this->_add_child(this->_right_child);
        }
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
    template <                                                               \
        typename Derived                                                     \
      , typename T                                                           \
      , typename Size                                                        \
      , typename Allocator                                                   \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binary_node_base<Derived,T,Size,Allocator>::iterator            \
        binary_node_base<Derived,T,Size,Allocator>::emplace_right(           \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (this->_right_child)                                              \
        {                                                                    \
            pointer p(this->_allocator.allocate(1));                         \
            this->_allocator.construct(                                      \
                p                                                            \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
            p->_add_child(p->_right_child = this->_right_child);             \
            this->_right_child = ::boost::initialized_value;                 \
            this->on_post_erase();                                           \
            return this->_add_child(this->_right_child = p);                 \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            this->_allocator.construct(                                      \
                this->_right_child = this->_allocator.allocate(1)            \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
            return this->_add_child(this->_right_child);                     \
        }                                                                    \
    }                                                                        \
//!
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_BINARY_NODE_MACRO(z, n, _)                           \
    template <                                                               \
        typename Derived                                                     \
      , typename T                                                           \
      , typename Size                                                        \
      , typename Allocator                                                   \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binary_node_base<Derived,T,Size,Allocator>::iterator            \
        binary_node_base<Derived,T,Size,Allocator>::emplace_right(           \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (this->_right_child)                                              \
        {                                                                    \
            pointer p(                                                       \
                ::boost::container::allocator_traits<                        \
                    typename traits::allocator                               \
                >::allocate(this->_allocator, 1)                             \
            );                                                               \
            ::boost::container::allocator_traits<                            \
                typename traits::allocator                                   \
            >::construct(                                                    \
                this->_allocator                                             \
              , p                                                            \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
            p->_add_child(p->_right_child = this->_right_child);             \
            this->_right_child = ::boost::initialized_value;                 \
            this->on_post_erase();                                           \
            return this->_add_child(this->_right_child = p);                 \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            ::boost::container::allocator_traits<                            \
                typename traits::allocator                                   \
            >::construct(                                                    \
                this->_allocator                                             \
              , this->_right_child = ::boost::container::allocator_traits<   \
                    typename traits::allocator                               \
                >::allocate(this->_allocator, 1)                             \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
            return this->_add_child(this->_right_child);                     \
        }                                                                    \
    }                                                                        \
//!
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_BINARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_BINARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::const_pointer
        binary_node_base<Derived,T,Size,Allocator>::get_left_child_ptr() const
    {
        return this->_left_child;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::pointer
        binary_node_base<Derived,T,Size,Allocator>::get_left_child_ptr()
    {
        return this->_left_child;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::const_pointer
        binary_node_base<Derived,T,Size,Allocator>::get_right_child_ptr() const
    {
        return this->_right_child;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::pointer
        binary_node_base<Derived,T,Size,Allocator>::get_right_child_ptr()
    {
        return this->_right_child;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::const_iterator
        binary_node_base<Derived,T,Size,Allocator>::cbegin() const
    {
        return const_iterator(this->get_derived(), false);
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::const_iterator
        binary_node_base<Derived,T,Size,Allocator>::begin() const
    {
        return const_iterator(this->get_derived(), false);
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::iterator
        binary_node_base<Derived,T,Size,Allocator>::begin()
    {
        return iterator(this->get_derived(), false);
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::const_iterator
        binary_node_base<Derived,T,Size,Allocator>::cend() const
    {
        return const_iterator(this->get_derived());
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::const_iterator
        binary_node_base<Derived,T,Size,Allocator>::end() const
    {
        return const_iterator(this->get_derived());
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::iterator
        binary_node_base<Derived,T,Size,Allocator>::end()
    {
        return iterator(this->get_derived());
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::const_reverse_iterator
        binary_node_base<Derived,T,Size,Allocator>::crbegin() const
    {
        return const_reverse_iterator(this->get_derived(), false);
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::const_reverse_iterator
        binary_node_base<Derived,T,Size,Allocator>::rbegin() const
    {
        return const_reverse_iterator(this->get_derived(), false);
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::reverse_iterator
        binary_node_base<Derived,T,Size,Allocator>::rbegin()
    {
        return reverse_iterator(this->get_derived(), false);
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::const_reverse_iterator
        binary_node_base<Derived,T,Size,Allocator>::crend() const
    {
        return const_reverse_iterator(this->get_derived());
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::const_reverse_iterator
        binary_node_base<Derived,T,Size,Allocator>::rend() const
    {
        return const_reverse_iterator(this->get_derived());
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::reverse_iterator
        binary_node_base<Derived,T,Size,Allocator>::rend()
    {
        return reverse_iterator(this->get_derived());
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::size_type
        binary_node_base<Derived,T,Size,Allocator>::size() const
    {
        return (
            this->_left_child
          ? (this->_right_child ? 2 : 1)
          : (this->_right_child ? 1 : 0)
        );
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline bool binary_node_base<Derived,T,Size,Allocator>::empty() const
    {
        return !this->_left_child && !this->_right_child;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline void binary_node_base<Derived,T,Size,Allocator>::clear()
    {
        if (this->_left_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.destroy(this->_left_child);
            this->_allocator.deallocate(this->_left_child, 1);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_left_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_left_child, 1);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }

        if (this->_right_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.destroy(this->_right_child);
            this->_allocator.deallocate(this->_right_child, 1);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_right_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_right_child, 1);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        }

        this->_left_child = this->_right_child = ::boost::initialized_value;
        this->on_post_clear();
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::pointer
        binary_node_base<Derived,T,Size,Allocator>::rotate_left()
    {
        pointer pivot = this->_right_child;

        pivot->_parent = this->_parent;

        if ((this->_right_child = pivot->_left_child))
        {
            this->_right_child->_parent = this->get_derived();
        }

        pivot->_left_child = this->get_derived();

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

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<Derived,T,Size,Allocator>::pointer
        binary_node_base<Derived,T,Size,Allocator>::rotate_right()
    {
        pointer pivot = this->_left_child;

        pivot->_parent = this->_parent;

        if ((this->_left_child = pivot->_right_child))
        {
            this->_left_child->_parent = this->get_derived();
        }

        pivot->_right_child = this->get_derived();

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

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline bool binary_node_base<Derived,T,Size,Allocator>::erase_left()
    {
        if (this->_left_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.destroy(this->_left_child);
            this->_allocator.deallocate(this->_left_child, 1);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_left_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_left_child, 1);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_left_child = ::boost::initialized_value;
            this->on_post_erase();
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline bool binary_node_base<Derived,T,Size,Allocator>::erase_right()
    {
        if (this->_right_child)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.destroy(this->_right_child);
            this->_allocator.deallocate(this->_right_child, 1);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::destroy(this->_allocator, this->_right_child);
            ::boost::container::allocator_traits<
                typename traits::allocator
            >::deallocate(this->_allocator, this->_right_child, 1);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_right_child = ::boost::initialized_value;
            this->on_post_erase();
            return true;
        }
        else
        {
            return false;
        }
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::traits::allocator_reference
        binary_node_base<Derived,T,Size,Allocator>::_construct_from(
            typename traits::allocator_reference allocator
          , ::std::tr1::true_type
        )
    {
        return allocator;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline Allocator
        binary_node_base<Derived,T,Size,Allocator>::_construct_from(
            typename traits::allocator_reference allocator
          , ::std::tr1::false_type
        )
    {
        return ::boost::container::allocator_traits<
            typename traits::allocator
        >::select_on_container_copy_construction(allocator);
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <typename Derived, typename T, typename Size, typename Allocator>
    typename binary_node_base<Derived,T,Size,Allocator>::iterator
        binary_node_base<Derived,T,Size,Allocator>::_add_child(
            pointer const& child
        )
    {
        child->_parent = this->get_derived();
        iterator result(child, true);
        result->on_post_inserted(result, ::boost::mpl::true_());
        return result;
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline void
        binary_node_base<Derived,T,Size,Allocator>::_link_children_to_parent()
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

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline void
        binary_node_base<Derived,T,Size,Allocator>::_on_post_modify_value(
            data_key const& key
        )
    {
        this->on_post_modify_value(key);
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    template <typename Derived, typename T, typename Size, typename Allocator>
    template <typename FusionKey>
    inline void
        binary_node_base<Derived,T,Size,Allocator>::_on_post_modify_value(
            FusionKey const& key
        )
    {
        this->on_post_modify_value(key);
    }
#endif

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline void
        binary_node_base<Derived,T,Size,Allocator>::_set_parent_ptr(pointer p)
    {
        if (this->_parent)
        {
            if (this->get_derived() == this->_parent->_left_child)
            {
                this->_parent->_left_child = ::boost::initialized_value;
            }
            else  // if (this->get_derived() == this->_parent->_right_child)
            {
                this->_parent->_right_child = ::boost::initialized_value;
            }

            this->_parent->on_post_erase();
        }

        if ((this->_parent = p))
        {
            this->on_post_inserted(
                iterator(this->get_derived(), true)
              , ::boost::mpl::true_()
            );
        }
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline void
        binary_node_base<Derived,T,Size,Allocator>::_set_left_child_ptr(
            pointer p
        )
    {
        if (this->_left_child)
        {
            this->_left_child = ::boost::initialized_value;
            this->on_post_erase();
        }

        if ((this->_left_child = p))
        {
            p->_parent = this->get_derived();
            p->on_post_inserted(iterator(p, true), ::boost::mpl::true_());
        }
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline void
        binary_node_base<Derived,T,Size,Allocator>::_set_right_child_ptr(
            pointer p
        )
    {
        if (this->_right_child)
        {
            this->_right_child = ::boost::initialized_value;
            this->on_post_erase();
        }

        if ((this->_right_child = p))
        {
            p->_parent = this->get_derived();
            p->on_post_inserted(iterator(p, true), ::boost::mpl::true_());
        }
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::traits::data_type const&
        get(
            binary_node_base<Derived,T,Size,Allocator> const& node
          , data_key const& key
        )
    {
        return node[key];
    }

    template <typename Derived, typename T, typename Size, typename Allocator>
    inline typename binary_node_base<
        Derived
      , T
      , Size
      , Allocator
    >::traits::data_type&
        get(
            binary_node_base<Derived,T,Size,Allocator>& node
          , data_key const& key
        )
    {
        return node[key];
    }

#if !defined BOOST_NO_SFINAE
    template <
        typename Key
      , typename Derived
      , typename T
      , typename Size
      , typename Allocator
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,data_key>
      , typename binary_node_base<
            Derived
          , T
          , Size
          , Allocator
        >::traits::data_type const&
    >::type
        get(binary_node_base<Derived,T,Size,Allocator> const& node)
    {
        return node[data_key()];
    }

    template <
        typename Key
      , typename Derived
      , typename T
      , typename Size
      , typename Allocator
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,data_key>
      , typename binary_node_base<Derived,T,Size,Allocator>::traits::data_type&
    >::type
        get(binary_node_base<Derived,T,Size,Allocator>& node)
    {
        return node[data_key()];
    }
#endif  // BOOST_NO_SFINAE

    template <
        typename Derived
      , typename T
      , typename Size
      , typename Allocator
      , typename V
    >
    inline void
        put(
            binary_node_base<Derived,T,Size,Allocator>& node
          , data_key const& key
          , V const& value
        )
    {
        node[key] = value;
        node._on_post_modify_value(key);
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    template <
        typename Derived
      , typename T
      , typename Size
      , typename Allocator
      , typename FusionKey
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                binary_node_base<Derived,T,Size,Allocator>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T const,FusionKey>
    >::type
        get(
            binary_node_base<Derived,T,Size,Allocator> const& node
          , FusionKey const& key
        )
    {
        return node[key];
    }

    template <
        typename Derived
      , typename T
      , typename Size
      , typename Allocator
      , typename FusionKey
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                binary_node_base<Derived,T,Size,Allocator>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T,FusionKey>
    >::type
        get(
            binary_node_base<Derived,T,Size,Allocator>& node
          , FusionKey const& key
        )
    {
        return node[key];
    }

    template <
        typename Derived
      , typename T
      , typename Size
      , typename Allocator
      , typename FusionKey
      , typename V
    >
    inline void
        put(
            binary_node_base<Derived,T,Size,Allocator>& node
          , FusionKey const& key
          , V const& value
          , typename ::boost::enable_if<
              typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                  typename ::boost::fusion::traits::is_sequence<T>::type
                , ::boost::fusion::traits::is_associative<T>
                , ::boost::mpl::false_
                >::type
              , result_of::has_key<
                    binary_node_base<Derived,T,Size,Allocator>
                  , FusionKey
                >
              , ::boost::mpl::false_
              >::type
            , ::boost::mpl::true_
            >::type
        )
    {
        node[key] = value;
        node._on_post_modify_value(key);
    }

    template <
        typename FusionKey
      , typename Derived
      , typename T
      , typename Size
      , typename Allocator
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                binary_node_base<Derived,T,Size,Allocator>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T const,FusionKey>
    >::type
        get(binary_node_base<Derived,T,Size,Allocator> const& node)
    {
        return node[FusionKey()];
    }

    template <
        typename FusionKey
      , typename Derived
      , typename T
      , typename Size
      , typename Allocator
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                binary_node_base<Derived,T,Size,Allocator>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T,FusionKey>
    >::type
        get(binary_node_base<Derived,T,Size,Allocator>& node)
    {
        return node[FusionKey()];
    }
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
}}  // namespace boost::tree_node

//[reference__binary_node_base_gen
namespace boost { namespace tree_node {

    template <
        typename Size = ::boost::uint32_t
      , typename AllocatorSelector = ::boost::std_allocator_selector
    >
    struct binary_node_base_gen
    {
        template <typename Derived, typename T>
        struct apply
        {
            typedef binary_node_base<
                        Derived
                      , T
                      , Size
                      , typename ::boost::mpl::apply_wrap1<
                            AllocatorSelector
                          , Derived
                        >::type
                    >
                    type;
        };
    };

    typedef binary_node_base_gen<> binary_node_base_default_gen;
}}  // namespace boost::tree_node
//]

namespace boost { namespace tree_node {

    template <typename T, typename Size, typename AllocatorSelector>
    struct binary_node
      : public
        //[reference__binary_node__bases
        binary_node_base<
            binary_node<T,Size,AllocatorSelector>
          , T
          , Size
          , typename ::boost::mpl::apply_wrap1<
                AllocatorSelector
              , binary_node<T,Size,AllocatorSelector>
            >::type
        >
        //]
    {
        //[reference__binary_node__super_t
        typedef binary_node_base<
                    binary_node
                  , T
                  , Size
                  , typename ::boost::mpl::apply_wrap1<
                        AllocatorSelector
                      , binary_node
                    >::type
                >
                super_t;
        //]

        //[reference__binary_node__traits
        typedef typename super_t::traits
                traits;
        //]

        //[reference__binary_node__pointer
        typedef typename super_t::pointer
                pointer;
        //]

        //[reference__binary_node__const_pointer
        typedef typename super_t::const_pointer
                const_pointer;
        //]

        //[reference__binary_node__iterator
        typedef typename super_t::iterator
                iterator;
        //]

        //[reference__binary_node__const_iterator
        typedef typename super_t::const_iterator
                const_iterator;
        //]

        //[reference__binary_node__reverse_iterator
        typedef typename super_t::reverse_iterator
                reverse_iterator;
        //]

        //[reference__binary_node__const_reverse_iterator
        typedef typename super_t::const_reverse_iterator
                const_reverse_iterator;
        //]

        //[reference__binary_node__size_type
        typedef typename super_t::size_type
                size_type;
        //]

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(binary_node, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binary_node__emplacement_ctor
        template <typename ...Args>
        explicit binary_node(Args&& ...args);
        //]

        //[reference__binary_node__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit binary_node(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (binary_node, super_t)
        )

        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_DEF
          , (binary_node, super_t)
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename T, typename Size, typename AllocatorSelector>
    template <typename ...Args>
    inline binary_node<T,Size,AllocatorSelector>::binary_node(Args&& ...args)
      : super_t(::boost::forward<Args>(args)...)
    {
    }

    template <typename T, typename Size, typename AllocatorSelector>
    template <typename ...Args>
    inline binary_node<T,Size,AllocatorSelector>::binary_node(
        ::boost::container::allocator_arg_t
      , typename traits::allocator_reference allocator
      , Args&& ...args
    ) : super_t(
            ::boost::container::allocator_arg
          , allocator
          , ::boost::forward<Args>(args)...
        )
    {
    }
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
}}  // namespace boost::tree_node

//[reference__binary_node_gen
namespace boost { namespace tree_node {

    template <
        typename Size = ::boost::uint32_t
      , typename AllocatorSelector = ::boost::std_allocator_selector
    >
    struct binary_node_gen
    {
        template <typename T>
        struct apply
        {
            typedef binary_node<T,Size,AllocatorSelector> type;
        };
    };

    typedef binary_node_gen<> binary_node_default_gen;
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_BINARY_NODE_HPP_INCLUDED

