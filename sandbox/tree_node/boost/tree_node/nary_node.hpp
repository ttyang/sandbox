// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_NARY_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_NARY_NODE_HPP_INCLUDED

#include <utility>
#include <boost/mpl/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/container_gen/insert_range_result_gen.hpp>
#include <boost/container_gen/is_recursive_selector.hpp>
#include <boost/container_gen/has_stable_iters_selector.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/nary_node_fwd.hpp>
#include <boost/tree_node/intrinsic/has_key.hpp>
#include <boost/tree_node/intrinsic/get_keys.hpp>
#include <boost/detail/metafunction/container_reverse_iterator.hpp>
#include <boost/assert.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/container_gen/insert_range_function_gen.hpp>
#else
#include <boost/move/move.hpp>
#include <boost/container_gen/splice_function_gen.hpp>
#endif

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#include <boost/tree_node/_detail/config_begin.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/type_traits/is_pod.hpp>

namespace boost {

    template <typename Derived, typename T, typename Selector>
    struct is_POD<
        ::boost::tree_node::nary_node_base<Derived,T,Selector>
    > : ::boost::false_type
    {
    };

    template <typename Derived, typename T, typename Selector>
    struct is_pod<
        ::boost::tree_node::nary_node_base<Derived,T,Selector>
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
      , typename Selector
      , typename FusionKey
    >
    struct has_key_impl<nary_node_base<Derived,T,Selector>,FusionKey>
      : ::boost::mpl::eval_if<
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

    template <typename Derived, typename T, typename Selector>
    struct get_keys_impl<nary_node_base<Derived,T,Selector> >
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

namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Selector>
    class nary_node_base
      : public
        //[reference__nary_node_base__bases
        tree_node_base<Derived>
        //]
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      , public data_key
#endif
      , private ::boost::noncopyable
    {
        BOOST_MPL_ASSERT((::boost::is_recursive_selector<Selector>));

        //[reference__nary_node_base__children
        typedef typename ::boost::container_gen<Selector,Derived>::type
                children;
        //]

     public:
        //[reference__nary_node_base__super_t
        typedef tree_node_base<Derived>
                super_t;
        //]

        //[reference__nary_node_base__traits
        struct traits
        {
            typedef T data_type;
            typedef typename children::allocator_type allocator;
            typedef allocator const& allocator_reference;
        };
        //]

        //[reference__nary_node_base__pointer
        typedef typename super_t::pointer
                pointer;
        //]

        //[reference__nary_node_base__const_pointer
        typedef typename super_t::const_pointer
                const_pointer;
        //]

        //[reference__nary_node_base__iterator
        typedef typename children::iterator
                iterator;
        //]

        //[reference__nary_node_base__const_iterator
        typedef typename children::const_iterator
                const_iterator;
        //]

        //[reference__nary_node_base__reverse_iterator
        typedef // typename children::reverse_iterator
                //<-
                typename ::boost::detail::metafunction
                ::container_reverse_iterator<children>::type
                //->
                reverse_iterator;
        //]

        //[reference__nary_node_base__const_reverse_iterator
        typedef // typename children::const_reverse_iterator
                //<-
                typename ::boost::detail::metafunction
                ::container_reverse_iterator<children const>::type
                //->
                const_reverse_iterator;
        //]

        //[reference__nary_node_base__size_type
        typedef typename children::size_type
                size_type;
        //]

     private:
        children                   _children;
        typename traits::data_type _data;
        pointer                    _parent;

     protected:
        //[reference__nary_node_base__derived_copy_ctor
        nary_node_base(Derived const& copy);
        //]

        //[reference__nary_node_base__derived_copy_ctor_w_allocator
        nary_node_base(
            Derived const& copy
          , typename traits::allocator_reference allocator
        );
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        nary_node_base(BOOST_RV_REF(Derived) source);

        nary_node_base(
            BOOST_RV_REF(Derived) source
          , typename traits::allocator_reference allocator
        );
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__nary_node_base__emplacement_ctor
        template <typename ...Args>
        explicit nary_node_base(Args&& ...args);
        //]

        //[reference__nary_node_base__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit nary_node_base(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_FWD_DECL
          , nary_node_base
        )

        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_FWD_DECL
          , nary_node_base
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        ~nary_node_base();

        //[reference__nary_node_base__on_post_copy_or_move
        void on_post_copy_or_move();
        //]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__nary_node_base__copy_assign
        void copy_assign(Derived const& copy);
        //]
#else
        void copy_assign(BOOST_COPY_ASSIGN_REF(Derived) copy);

        void move_assign(BOOST_RV_REF(Derived) source);
#endif

     public:
        //[reference__nary_node_base__data_key_value_operator__const
        typename traits::data_type const& operator[](data_key const&) const;
        //]

        //[reference__nary_node_base__data_key_value_operator
        typename traits::data_type& operator[](data_key const&);
        //]

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        //[reference__nary_node_base__key_value_operator__const
        template <typename FusionKey>
        typename ::boost::lazy_enable_if<
            typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                    typename ::boost::fusion::traits::is_sequence<T>::type
                  , ::boost::fusion::traits::is_associative<T>
                  , ::boost::mpl::false_
                >::type
              , result_of::has_key<
                    nary_node_base<Derived,T,Selector>
                  , FusionKey
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::fusion::result_of::at_key<T const,FusionKey>
        >::type
            operator[](FusionKey const&) const;
        //]

        //[reference__nary_node_base__key_value_operator
        template <typename FusionKey>
        typename ::boost::lazy_enable_if<
            typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                    typename ::boost::fusion::traits::is_sequence<T>::type
                  , ::boost::fusion::traits::is_associative<T>
                  , ::boost::mpl::false_
                >::type
              , result_of::has_key<
                    nary_node_base<Derived,T,Selector>
                  , FusionKey
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::fusion::result_of::at_key<T,FusionKey>
        >::type
            operator[](FusionKey const&);
        //]
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

        //[reference__nary_node_base__get_parent_ptr__const
        const_pointer get_parent_ptr() const;
        //]

        //[reference__nary_node_base__get_parent_ptr
        pointer get_parent_ptr();
        //]

        //[reference__nary_node_base__insert
        iterator insert(Derived const& child);
        //]

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__nary_node_base__emplace
        template <typename ...Args>
        iterator emplace(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_NARY_NODE_MACRO(z, n, _)                             \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        iterator                                                             \
            emplace(                                                         \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_NARY_NODE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_NARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        //[reference__nary_node_base__splice
        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            splice(iterator pos, Derived& node);

        iterator splice(iterator pos, Derived& node, iterator itr);

        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            splice(
                iterator pos
              , Derived& node
              , iterator itr
              , iterator itr_end
            );
        //]

        //[reference__nary_node_base__cbegin
        const_iterator cbegin() const;
        const_iterator begin() const;
        //]

        //[reference__nary_node_base__begin
        iterator begin();
        //]

        //[reference__nary_node_base__cend
        const_iterator cend() const;
        const_iterator end() const;
        //]

        //[reference__nary_node_base__end
        iterator end();
        //]

        //[reference__nary_node_base__crbegin
        const_reverse_iterator crbegin() const;
        const_reverse_iterator rbegin() const;
        //]

        //[reference__nary_node_base__rbegin
        reverse_iterator rbegin();
        //]

        //[reference__nary_node_base__crend
        const_reverse_iterator crend() const;
        const_reverse_iterator rend() const;
        //]

        //[reference__nary_node_base__rend
        reverse_iterator rend();
        //]

        //[reference__nary_node_base__size
        size_type size() const;
        //]

        //[reference__nary_node_base__empty
        bool empty() const;
        //]

        //[reference__nary_node_base__clear
        void clear();
        //]

     private:
        static void
            _link_children_to_parent(
                pointer const& p
              , iterator itr
              , iterator itr_end
            );

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename ...Args>
        iterator _add_child(Args&& ...args);
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_NARY_NODE_MACRO(z, n, _)                             \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        iterator                                                             \
            _add_child(                                                      \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_NARY_NODE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_NARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        void _initialize(iterator& to_child);

        void _on_post_modify_value(data_key const& key);

        template <typename D, typename T0, typename S, typename V>
        friend void
            put(
                nary_node_base<D,T0,S>& node
              , data_key const& key
              , V const& value
            );

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        template <typename FusionKey>
        void _on_post_modify_value(FusionKey const& key);

        template <
            typename D
          , typename T0
          , typename S
          , typename FusionKey
          , typename V
        >
        friend void
          put(
            nary_node_base<D,T0,S>& node
          , FusionKey const& key
          , V const& value
          , typename ::boost::enable_if<
              typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                  typename ::boost::fusion::traits::is_sequence<T0>::type
                , ::boost::fusion::traits::is_associative<T0>
                , ::boost::mpl::false_
                >::type
              , result_of::has_key<nary_node_base<D,T0,S>,FusionKey>
              , ::boost::mpl::false_
              >::type
            , ::boost::mpl::true_
            >::type
          );
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
    };

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(Derived const& copy)
      : _children(copy._children)
      , _data(copy._data)
      , _parent(copy._parent)
    {
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        Derived const& copy
      , typename traits::allocator_reference allocator
    ) : _children(copy._children, allocator)
      , _data(copy._data)
      , _parent(copy._parent)
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        BOOST_RV_REF(Derived) source
    ) : _children(::boost::move(source._children))
      , _data(::boost::move(source._data))
      , _parent(source._parent)
    {
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        BOOST_RV_REF(Derived) source
      , typename traits::allocator_reference allocator
    ) : _children(::boost::move(source._children), allocator)
      , _data(::boost::move(source._data))
      , _parent(source._parent)
    {
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T, typename Selector>
    template <typename ...Args>
    nary_node_base<Derived,T,Selector>::nary_node_base(Args&& ...args)
      : _children(), _data(::boost::forward<Args>(args)...), _parent()
    {
    }

    template <typename Derived, typename T, typename Selector>
    template <typename ...Args>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        ::boost::container::allocator_arg_t
      , typename traits::allocator_reference allocator
      , Args&& ...args
    ) : _children(allocator), _data(::boost::forward<Args>(args)...), _parent()
    {
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_NARY_NODE_MACRO(z, n, _)                             \
    template <typename Derived, typename T, typename Selector>               \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    nary_node_base<Derived,T,Selector>::nary_node_base(                      \
        BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                     \
            n                                                                \
          , BOOST_CONTAINER_PP_PARAM_LIST                                    \
          , _                                                                \
        )                                                                    \
    ) : _children()                                                          \
      , _data(                                                               \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        )                                                                    \
      , _parent()                                                            \
    {                                                                        \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_NARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_NARY_NODE_MACRO

#define BOOST_TREE_NODE_NARY_NODE_MACRO(z, n, _)                             \
    template <typename Derived, typename T, typename Selector>               \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    nary_node_base<Derived,T,Selector>::nary_node_base(                      \
        ::boost::container::allocator_arg_t                                  \
      , typename traits::allocator_reference allocator                       \
        BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                            \
            n                                                                \
          , BOOST_CONTAINER_PP_PARAM_LIST                                    \
          , _                                                                \
        )                                                                    \
    ) : _children(allocator)                                                 \
      , _data(                                                               \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        )                                                                    \
      , _parent()                                                            \
    {                                                                        \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_NARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_NARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::~nary_node_base()
    {
    }

    template <typename Derived, typename T, typename Selector>
    inline void nary_node_base<Derived,T,Selector>::on_post_copy_or_move()
    {
        nary_node_base<Derived,T,Selector>::_link_children_to_parent(
            this->get_derived()
          , this->_children.begin()
          , this->_children.end()
        );
        this->on_post_propagate_value(data_key());
    }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Selector>
    void nary_node_base<Derived,T,Selector>::copy_assign(Derived const& copy)
    {
        Derived twin(copy);

        this->_children = twin._children;
        this->_data = twin._data;
    }
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Selector>
    void
        nary_node_base<Derived,T,Selector>::copy_assign(
            BOOST_COPY_ASSIGN_REF(Derived) copy
        )
    {
        Derived twin(static_cast<Derived const&>(copy));

        this->_children = ::boost::move(twin._children);
        this->_data = ::boost::move(twin._data);
    }

    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::move_assign(
            BOOST_RV_REF(Derived) source
        )
    {
        this->_children = ::boost::move(source._children);
        this->_data = ::boost::move(source._data);
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<
        Derived
      , T
      , Selector
    >::traits::data_type const&
        nary_node_base<Derived,T,Selector>::operator[](data_key const&) const
    {
        return this->_data;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::traits::data_type&
        nary_node_base<Derived,T,Selector>::operator[](data_key const&)
    {
        return this->_data;
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    template <typename Derived, typename T, typename Selector>
    template <typename FusionKey>
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T const,FusionKey>
    >::type
        nary_node_base<Derived,T,Selector>::operator[](FusionKey const&) const
    {
        return ::boost::fusion::at_key<FusionKey>(this->_data);
    }

    template <typename Derived, typename T, typename Selector>
    template <typename FusionKey>
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T,FusionKey>
    >::type
        nary_node_base<Derived,T,Selector>::operator[](FusionKey const&)
    {
        return ::boost::fusion::at_key<FusionKey>(this->_data);
    }
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_pointer
        nary_node_base<Derived,T,Selector>::get_parent_ptr() const
    {
        return this->_parent;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::pointer
        nary_node_base<Derived,T,Selector>::get_parent_ptr()
    {
        return this->_parent;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::insert(Derived const& child)
    {
#if defined BOOST_MSVC
        Derived twin(child);
        iterator result(this->_add_child(twin));
#else
        iterator result(this->_add_child(Derived(child)));
#endif
        BOOST_ASSERT((*result)._parent == this->get_derived());
        return result;
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T, typename Selector>
    template <typename ...Args>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::emplace(Args&& ...args)
    {
        iterator result(this->_add_child(::boost::forward<Args>(args)...));
        BOOST_ASSERT((*result)._parent == this->get_derived());
        return result;
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_NARY_NODE_MACRO(z, n, _)                             \
    template <typename Derived, typename T, typename Selector>               \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    inline typename nary_node_base<Derived,T,Selector>::iterator             \
        nary_node_base<Derived,T,Selector>::emplace(                         \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        iterator result = this->_add_child(                                  \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        );                                                                   \
        BOOST_ASSERT((*result)._parent == this->get_derived());              \
        return result;                                                       \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_NARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_NARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename T, typename Selector>
    typename ::boost::insert_range_result_gen<Selector,Derived>::type
        nary_node_base<Derived,T,Selector>::splice(iterator pos, Derived& node)
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename ::boost::insert_range_function_gen<Selector>::type
            range_pusher;
        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            result = range_pusher(
                this->_children
              , pos
              , node.begin()
              , node.end()
            );

        node.clear();
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename ::boost::splice_function_gen<Selector>::type
            splicer;
        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            result = splicer(
                this->_children
              , pos
              , node._children
              , node.begin()
              , node.end()
            );

        node.on_post_clear();
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

        nary_node_base<Derived,T,Selector>::_link_children_to_parent(
            this->get_derived()
          , ::boost::begin(result)
          , ::boost::end(result)
        );
        this->on_post_insert(
            ::boost::begin(result)
          , ::boost::end(result)
          , ::boost::has_stable_iterators_selector<Selector>()
        );
        return result;
    }

    template <typename Derived, typename T, typename Selector>
    typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::splice(
            iterator pos
          , Derived& node
          , iterator itr
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        iterator result = node._children.insert(pos, *itr);

        node._children.erase(itr);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename ::boost::splice_function_gen<Selector>::type
            splicer;
        iterator result = splicer(
            this->_children
          , pos
          , node._children
          , itr
        );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

        node.on_post_erase();
        (*result)._parent = this->get_derived();
        (*result).on_post_inserted(
            result
          , ::boost::has_stable_iterators_selector<Selector>()
        );
        return result;
    }

    template <typename Derived, typename T, typename Selector>
    typename ::boost::insert_range_result_gen<Selector,Derived>::type
        nary_node_base<Derived,T,Selector>::splice(
            iterator pos
          , Derived& node
          , iterator itr
          , iterator itr_end
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename ::boost::insert_range_function_gen<Selector>::type
            range_pusher;
        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            result = range_pusher(
                this->_children
              , pos
              , itr
              , itr_end
            );

        node._children.erase(itr, itr_end);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename ::boost::splice_function_gen<Selector>::type
            splicer;
        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            result = splicer(
                this->_children
              , pos
              , node._children
              , itr
              , itr_end
            );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

        node.on_post_erase();
        nary_node_base<Derived,T,Selector>::_link_children_to_parent(
            this->get_derived()
          , ::boost::begin(result)
          , ::boost::end(result)
        );
        this->on_post_insert(
            ::boost::begin(result)
          , ::boost::end(result)
          , ::boost::has_stable_iterators_selector<Selector>()
        );
        return result;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_iterator
        nary_node_base<Derived,T,Selector>::cbegin() const
    {
        return this->_children.cbegin();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_iterator
        nary_node_base<Derived,T,Selector>::begin() const
    {
        return this->_children.begin();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::begin()
    {
        return this->_children.begin();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_iterator
        nary_node_base<Derived,T,Selector>::cend() const
    {
        return this->_children.cend();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_iterator
        nary_node_base<Derived,T,Selector>::end() const
    {
        return this->_children.end();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::end()
    {
        return this->_children.end();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_reverse_iterator
        nary_node_base<Derived,T,Selector>::crbegin() const
    {
        return this->_children.crbegin();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_reverse_iterator
        nary_node_base<Derived,T,Selector>::rbegin() const
    {
        return this->_children.rbegin();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::reverse_iterator
        nary_node_base<Derived,T,Selector>::rbegin()
    {
        return this->_children.rbegin();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_reverse_iterator
        nary_node_base<Derived,T,Selector>::crend() const
    {
        return this->_children.crend();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_reverse_iterator
        nary_node_base<Derived,T,Selector>::rend() const
    {
        return this->_children.rend();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::reverse_iterator
        nary_node_base<Derived,T,Selector>::rend()
    {
        return this->_children.rend();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::size_type
        nary_node_base<Derived,T,Selector>::size() const
    {
        return this->_children.size();
    }

    template <typename Derived, typename T, typename Selector>
    inline bool nary_node_base<Derived,T,Selector>::empty() const
    {
        return this->_children.empty();
    }

    template <typename Derived, typename T, typename Selector>
    inline void nary_node_base<Derived,T,Selector>::clear()
    {
        this->_children.clear();
        this->on_post_clear();
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T, typename Selector>
    template <typename ...Args>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child(Args&& ...args)
    {
        typename ::boost::emplace_function_gen<Selector>::type emplacer;
        ::std::pair<iterator,bool> p = emplacer(
            this->_children
          , ::boost::forward<Args>(args)...
        );

        if (p.second)
        {
            this->_initialize(p.first);
        }

        return p.first;
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_NARY_NODE_MACRO(z, n, _)                             \
    template <typename Derived, typename T, typename Selector>               \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    inline typename nary_node_base<Derived,T,Selector>::iterator             \
        nary_node_base<Derived,T,Selector>::_add_child(                      \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        typename ::boost::emplace_function_gen<Selector>::type emplacer;     \
        ::std::pair<iterator,bool> p = emplacer(                             \
            this->_children                                                  \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        );                                                                   \
        if (p.second)                                                        \
        {                                                                    \
            this->_initialize(p.first);                                      \
        }                                                                    \
        return p.first;                                                      \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_NARY_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_NARY_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::_initialize(iterator& to_child)
    {
        (*to_child)._parent = this->get_derived();
        (*to_child).on_post_inserted(
            to_child
          , ::boost::has_stable_iterators_selector<Selector>()
        );
    }

    template <typename Derived, typename T, typename Selector>
    void
        nary_node_base<Derived,T,Selector>::_link_children_to_parent(
            pointer const& p
          , iterator itr
          , iterator itr_end
        )
    {
        for (; itr != itr_end; ++itr)
        {
            (*itr)._parent = p;
        }
    }

    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::_on_post_modify_value(
            data_key const& key
        )
    {
        this->on_post_propagate_value(key);
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    template <typename Derived, typename T, typename Selector>
    template <typename FusionKey>
    inline void
        nary_node_base<Derived,T,Selector>::_on_post_modify_value(
            FusionKey const& key
        )
    {
        this->on_post_propagate_value(key);
    }
#endif
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<
        Derived
      , T
      , Selector
    >::traits::data_type const&
        get(
            nary_node_base<Derived,T,Selector> const& node
          , data_key const& key
        )
    {
        return node[key];
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::traits::data_type&
        get(nary_node_base<Derived,T,Selector>& node, data_key const& key)
    {
        return node[key];
    }

#if !defined BOOST_NO_SFINAE
    template <typename Key, typename Derived, typename T, typename Selector>
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,data_key>
      , typename nary_node_base<
            Derived
          , T
          , Selector
        >::traits::data_type const&
    >::type
        get(nary_node_base<Derived,T,Selector> const& node)
    {
        return node[data_key()];
    }

    template <typename Key, typename Derived, typename T, typename Selector>
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,data_key>
      , typename nary_node_base<
            Derived
          , T
          , Selector
        >::traits::data_type&
    >::type
        get(nary_node_base<Derived,T,Selector>& node)
    {
        return node[data_key()];
    }
#endif  // BOOST_NO_SFINAE

    template <typename Derived, typename T, typename Selector, typename V>
    inline void
        put(
            nary_node_base<Derived,T,Selector>& node
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
      , typename Selector
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
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T const,FusionKey>
    >::type
        get(
            nary_node_base<Derived,T,Selector> const& node
          , FusionKey const& key
        )
    {
        return node[key];
    }

    template <
        typename Derived
      , typename T
      , typename Selector
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
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T,FusionKey>
    >::type
        get(nary_node_base<Derived,T,Selector>& node, FusionKey const& key)
    {
        return node[key];
    }

    template <
        typename FusionKey
      , typename Derived
      , typename T
      , typename Selector
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T const,FusionKey>
    >::type
        get(nary_node_base<Derived,T,Selector> const& node)
    {
        return node[FusionKey()];
    }

    template <
        typename FusionKey
      , typename Derived
      , typename T
      , typename Selector
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<T>::type
              , ::boost::fusion::traits::is_associative<T>
              , ::boost::mpl::false_
            >::type
          , result_of::has_key<
                nary_node_base<Derived,T,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<T,FusionKey>
    >::type
        get(nary_node_base<Derived,T,Selector>& node)
    {
        return node[FusionKey()];
    }

    template <
        typename Derived
      , typename T
      , typename Selector
      , typename FusionKey
      , typename V
    >
    inline void
        put(
            nary_node_base<Derived,T,Selector>& node
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
                  nary_node_base<Derived,T,Selector>
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
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
}}  // namespace boost::tree_node

//[reference__nary_node_base_gen
namespace boost { namespace tree_node {

    template <typename Selector = ::boost::ptr_dequeS>
    struct nary_node_base_gen
    {
        template <typename Derived, typename T>
        struct apply
        {
            typedef nary_node_base<Derived,T,Selector> type;
        };
    };

    typedef nary_node_base_gen<> nary_node_base_default_gen;
}}  // namespace boost::tree_node
//]

namespace boost { namespace tree_node {

    template <typename T, typename Selector>
    struct nary_node
      : public
        //[reference__nary_node__bases
        nary_node_base<nary_node<T,Selector>,T,Selector>
        //]
    {
        //[reference__nary_node__super_t
        typedef nary_node_base<nary_node,T,Selector>
                super_t;
        //]

        //[reference__nary_node__traits
        typedef typename super_t::traits
                traits;
        //]

        //[reference__nary_node__pointer
        typedef typename super_t::pointer
                pointer;
        //]

        //[reference__nary_node__const_pointer
        typedef typename super_t::const_pointer
                const_pointer;
        //]

        //[reference__nary_node__iterator
        typedef typename super_t::iterator
                iterator;
        //]

        //[reference__nary_node__const_iterator
        typedef typename super_t::const_iterator
                const_iterator;
        //]

        //[reference__nary_node__reverse_iterator
        typedef typename super_t::reverse_iterator
                reverse_iterator;
        //]

        //[reference__nary_node__const_reverse_iterator
        typedef typename super_t::const_reverse_iterator
                const_reverse_iterator;
        //]

        //[reference__nary_node__size_type
        typedef typename super_t::size_type
                size_type;
        //]

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(nary_node, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__nary_node__emplacement_ctor
        template <typename ...Args>
        explicit nary_node(Args&& ...args);
        //]

        //[reference__nary_node__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit nary_node(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (nary_node, super_t)
        )

        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_DEF
          , (nary_node, super_t)
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename T, typename Selector>
    template <typename ...Args>
    inline nary_node<T,Selector>::nary_node(Args&& ...args)
      : super_t(::boost::forward<Args>(args)...)
    {
    }

    template <typename T, typename Selector>
    template <typename ...Args>
    inline nary_node<T,Selector>::nary_node(
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

//[reference__nary_node_gen
namespace boost { namespace tree_node {

    template <typename Selector = ::boost::ptr_dequeS>
    struct nary_node_gen
    {
        template <typename T>
        struct apply
        {
            typedef nary_node<T,Selector> type;
        };
    };

    typedef nary_node_gen<> nary_node_default_gen;
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_NARY_NODE_HPP_INCLUDED

