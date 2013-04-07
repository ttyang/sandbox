// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_NARY_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_NARY_NODE_HPP_INCLUDED

#include <utility>
#include <deque>
#include <algorithm>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/container_gen/splice_function_gen.hpp>
#include <boost/container_gen/insert_range_result_gen.hpp>
#include <boost/container_gen/is_recursive_selector.hpp>
#include <boost/container_gen/is_reversible_selector.hpp>
#include <boost/container_gen/is_random_access_selector.hpp>
#include <boost/container_gen/is_ptr_selector.hpp>
#include <boost/container_gen/has_stable_iters_selector.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/nary_node_fwd.hpp>
#include <boost/tree_node/intrinsic/has_key.hpp>
#include <boost/tree_node/intrinsic/get_keys.hpp>
#include <boost/tree_node/iterator/depth_first_descendant.hpp>
#include <boost/tree_node/iterator/post_order.hpp>
#include <boost/detail/metafunction/container_reverse_iterator.hpp>
#include <boost/assert.hpp>

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/container_gen/insert_range_function_gen.hpp>
#else
#include <boost/move/move.hpp>
#include <boost/container_gen/selectors.hpp>
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

        typedef nary_node_base<Derived,T,Selector> self;

        //[reference__nary_node_base__children
        typedef typename ::boost::container_gen<Selector,Derived>::type
                children;
        //]

     public:
        //[reference__nary_node_base__super_t
        typedef tree_node_base<Derived> super_t;
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
        typedef typename super_t::pointer pointer;
        //]

        //[reference__nary_node_base__const_pointer
        typedef typename super_t::const_pointer const_pointer;
        //]

        //[reference__nary_node_base__iterator
        typedef typename children::iterator iterator;
        //]

        //[reference__nary_node_base__const_iterator
        typedef typename children::const_iterator const_iterator;
        //]

        typedef typename ::boost::detail::metafunction
                ::container_reverse_iterator<children>::type
                reverse_iterator;
        typedef typename ::boost::detail::metafunction
                ::container_reverse_iterator<children const>::type
                const_reverse_iterator;

        //[reference__nary_node_base__size_type
        typedef typename children::size_type size_type;
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

        //[reference__nary_node_base__clone_descendants
        void clone_descendants(Derived const& copy);
        //]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__nary_node_base__copy_assign
        void copy_assign(Derived const& copy);
        //]
#else
        void move_descendants(BOOST_RV_REF(Derived) source);

        void copy_assign(BOOST_COPY_ASSIGN_REF(Derived) copy);

        void move_assign(BOOST_RV_REF(Derived) source);
#endif

        //[reference__nary_node_base__on_post_assign
        void on_post_assign();
        //]

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

        //[reference__nary_node_base__insert
        iterator insert(Derived const& child);
        //]

#if 0//!defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__nary_node_base__move_insert
        iterator insert(BOOST_RV_REF(Derived) child);
        //]
#endif

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

        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            splice(iterator pos, Derived& node, iterator itr);

        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            splice(
                iterator pos
              , Derived& node
              , iterator itr
              , iterator itr_end
            );
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

        void _clone_descendants(Derived const& copy);

        void _clone_descendants(Derived const& copy, ::boost::mpl::true_);

        void _clone_descendants(Derived const& copy, ::boost::mpl::false_);

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        void _move_descendants(BOOST_RV_REF(Derived) source);

        void _move_descendants(Derived& source, ::boost::mpl::true_);

        void _move_descendants(Derived& source, ::boost::mpl::false_);

        void _move_descendants_non_ptr(Derived& source, ::boost::mpl::true_);

        void _move_descendants_non_ptr(Derived& source, ::boost::mpl::false_);

        template <typename A>
        void
            _on_post_insert(
                iterator to_child
              , ::boost::vector_selector< ::boost::mpl::true_,A>
            );

        template <typename A>
        void _on_post_resize(::boost::vector_selector< ::boost::mpl::true_,A>);

        template <typename A>
        void _on_post_outsourced(::boost::stable_vector_selector<A>);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

        template <typename S>
        void _on_post_insert(iterator to_child, S);

        template <typename S>
        void _on_post_resize(S);

        template <typename S>
        void _on_post_outsourced(S);

        void _on_post_clone_or_move(::boost::mpl::true_);

        void _on_post_clone_or_move(::boost::mpl::false_);

        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            _splice(
                iterator pos
              , Derived& node
              , iterator itr
              , iterator itr_end
              , ::boost::mpl::true_
            );

        typename ::boost::insert_range_result_gen<Selector,Derived>::type
            _splice(
                iterator pos
              , Derived& node
              , iterator itr
              , iterator itr_end
              , ::boost::mpl::false_
            );

        template <typename D, typename T0, typename S, typename V>
        friend void
            put(
                nary_node_base<D,T0,S>& node
              , data_key const& key
              , V const& value
            );

        void _on_post_modify_value(data_key const& key);

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
      : _children(), _data(copy._data), _parent()
    {
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        Derived const& copy
      , typename traits::allocator_reference allocator
    ) : _children(allocator), _data(copy._data), _parent()
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        BOOST_RV_REF(Derived) source
    ) : _children(), _data(::boost::move(source._data)), _parent()
    {
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        BOOST_RV_REF(Derived) source
      , typename traits::allocator_reference allocator
    ) : _children(allocator), _data(::boost::move(source._data)), _parent()
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
    inline void
        nary_node_base<Derived,T,Selector>::clone_descendants(
            Derived const& copy
        )
    {
        this->_clone_descendants(copy);
        this->_on_post_clone_or_move(
            ::boost::is_reversible_selector<Selector>()
        );
    }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::copy_assign(Derived const& copy)
    {
        Derived twin(copy._data);

        twin._clone_descendants(copy);
        this->_children.clear();
        this->_clone_descendants(twin);
        this->clone_metadata(copy);
        this->_data = twin._data;
    }
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::move_descendants(
            BOOST_RV_REF(Derived) source
        )
    {
#if defined BOOST_NO_RVALUE_REFERENCES
        this->_move_descendants(source);
#else
        this->_move_descendants(static_cast<Derived&&>(source));
#endif
        this->_on_post_clone_or_move(
            ::boost::is_reversible_selector<Selector>()
        );
        source._on_post_outsourced(Selector());
    }

    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::copy_assign(
            BOOST_COPY_ASSIGN_REF(Derived) copy
        )
    {
        Derived twin(copy._data);

        twin._clone_descendants(static_cast<Derived const&>(copy));
        this->_children.clear();
        this->_move_descendants(::boost::move(twin));
        this->clone_metadata(copy);
        this->_data = ::boost::move(twin._data);
    }

    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::move_assign(
            BOOST_RV_REF(Derived) source
        )
    {
        this->_children.clear();
#if defined BOOST_NO_RVALUE_REFERENCES
        this->_move_descendants(source);
        this->move_metadata(source);
#else
        this->_move_descendants(static_cast<Derived&&>(source));
        this->move_metadata(static_cast<Derived&&>(source));
#endif
        this->_on_post_clone_or_move(
            ::boost::is_reversible_selector<Selector>()
        );
        this->_data = ::boost::move(source._data);
        source._on_post_outsourced(Selector());
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <typename Derived, typename T, typename Selector>
    inline void nary_node_base<Derived,T,Selector>::on_post_assign()
    {
        if (this->_parent)
        {
            this->_parent->on_post_propagate_value(data_key());
        }
    }

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

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::insert(Derived const& child)
    {
        Derived twin(child._data);

        twin._clone_descendants(child);

        typename ::boost::emplace_function_gen<Selector>::type emplacer;
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        ::std::pair<iterator,bool> p = emplacer(this->_children, twin._data);
#else
        ::std::pair<iterator,bool> p = emplacer(
            this->_children
          , ::boost::move(twin._data)
        );
#endif

        if (p.second)
        {
            this->_on_post_insert(p.first, Selector());
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            (*p.first)._clone_descendants(twin);
#else
            (*p.first)._move_descendants(::boost::move(twin));
#endif
            (*p.first).clone_metadata(child);
            (*p.first).on_post_inserted(
                p.first
              , ::boost::has_stable_iterators_selector<Selector>()
            );
        }
        else
        {
            BOOST_ASSERT_MSG(
                false
              , "This type does not yet handle associative selectors."
            );
        }

        return p.first;
    }

#if 0//!defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::insert(BOOST_RV_REF(Derived) child)
    {
        typename ::boost::emplace_function_gen<Selector>::type emplacer;
        ::std::pair<iterator,bool> p = emplacer(
            this->_children
          , ::boost::move(child._data)
        );

        if (p.second)
        {
            this->_on_post_insert(p.first, Selector());
#if defined BOOST_NO_RVALUE_REFERENCES
            (*p.first)._move_descendants(child);
            (*p.first).move_metadata(child);
#else
            (*p.first)._move_descendants(static_cast<Derived&&>(child));
            (*p.first).move_metadata(static_cast<Derived&&>(child));
#endif
            (*p.first)._on_post_clone_or_move(
                ::boost::is_reversible_selector<Selector>()
            );
            (*p.first).on_post_inserted(
                p.first
              , ::boost::has_stable_iterators_selector<Selector>()
            );
        }
        else
        {
            BOOST_ASSERT_MSG(
                false
              , "This type does not yet handle associative selectors."
            );
        }

        return p.first;
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename T, typename Selector>
    template <typename ...Args>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::emplace(Args&& ...args)
    {
        typename ::boost::emplace_function_gen<Selector>::type emplacer;
        ::std::pair<iterator,bool> p = emplacer(
            this->_children
          , ::boost::forward<Args>(args)...
        );

        if (p.second)
        {
            this->_on_post_insert(p.first, Selector());
            (*p.first).on_post_inserted(
                p.first
              , ::boost::has_stable_iterators_selector<Selector>()
            );
        }
        else
        {
            BOOST_ASSERT_MSG(
                false
              , "This type does not yet handle associative selectors."
            );
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
        nary_node_base<Derived,T,Selector>::emplace(                         \
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
            this->_on_post_insert(p.first, Selector());                      \
            (*p.first).on_post_inserted(                                     \
                p.first                                                      \
              , ::boost::has_stable_iterators_selector<Selector>()           \
            );                                                               \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            BOOST_ASSERT_MSG(                                                \
                false                                                        \
              , "This type does not yet handle associative selectors."       \
            );                                                               \
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
    inline typename ::boost::insert_range_result_gen<Selector,Derived>::type
        nary_node_base<Derived,T,Selector>::splice(iterator pos, Derived& node)
    {
        typename ::boost::insert_range_result_gen<
            Selector
          , Derived
        >::type result = this->_splice(
            pos
          , node
          , ::boost::begin(node._children)
          , ::boost::end(node._children)
          , typename ::boost::mpl::if_<
                ::boost::is_ptr_selector<Selector>
              , ::boost::mpl::false_
              , ::boost::is_random_access_selector<Selector>
            >::type()
        );

        node.on_post_clear();
        this->on_post_insert(
            ::boost::begin(result)
          , ::boost::end(result)
          , ::boost::has_stable_iterators_selector<Selector>()
        );
        return result;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename ::boost::insert_range_result_gen<Selector,Derived>::type
        nary_node_base<Derived,T,Selector>::splice(
            iterator pos
          , Derived& node
          , iterator itr
        )
    {
        iterator itr_end = itr;
        return this->splice(
            pos
          , node
          , itr
          , ++itr_end
        );
    }

    template <typename Derived, typename T, typename Selector>
    inline typename ::boost::insert_range_result_gen<Selector,Derived>::type
        nary_node_base<Derived,T,Selector>::splice(
            iterator pos
          , Derived& node
          , iterator itr
          , iterator itr_end
        )
    {
        typename ::boost::insert_range_result_gen<
            Selector
          , Derived
        >::type result = this->_splice(
            pos
          , node
          , itr
          , itr_end
          , typename ::boost::mpl::if_<
                ::boost::is_ptr_selector<Selector>
              , ::boost::mpl::false_
              , ::boost::is_random_access_selector<Selector>
            >::type()
        );

        node.on_post_erase();
        this->on_post_insert(
            ::boost::begin(result)
          , ::boost::end(result)
          , ::boost::has_stable_iterators_selector<Selector>()
        );
        return result;
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
            (*p.first)._parent = this->get_derived();
        }
        else
        {
            BOOST_ASSERT_MSG(
                false
              , "This type does not yet handle associative selectors."
            );
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
            (*p.first)._parent = this->get_derived();                        \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            BOOST_ASSERT_MSG(                                                \
                false                                                        \
              , "This type does not yet handle associative selectors."       \
            );                                                               \
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
        nary_node_base<Derived,T,Selector>::_clone_descendants(
            Derived const& copy
        )
    {
        this->_clone_descendants(
            copy
          , typename ::boost::mpl::if_<
                ::boost::is_ptr_selector<Selector>
              , ::boost::mpl::false_
              , ::boost::is_random_access_selector<Selector>
            >::type()
        );
        this->get_derived()->on_post_copy_or_move();
    }

    template <typename Derived, typename T, typename Selector>
    void
        nary_node_base<Derived,T,Selector>::_clone_descendants(
            Derived const& copy
          , ::boost::mpl::true_
        )
    {
        pointer p = this->get_derived();
        ::std::deque<size_type> indices;
        size_type current_index = ::boost::initialized_value;

        p->_children.resize(copy._children.size(), Derived(copy._data));
        p->_on_post_resize(Selector());

        for (
            depth_first_descendant_iterator<Derived const> itr(copy);
            itr;
            ++itr
        )
        {
            switch (::boost::tree_node::traversal_state(itr))
            {
                case ::boost::tree_node::pre_order_traversal:
                {
                    p->_children[current_index]._parent = p;
                    p = &p->_children[current_index];
                    indices.push_back(current_index);
                    p->_children.clear();
                    p->_children.resize(
                        (*itr)._children.size()
                      , Derived((*itr)._data)
                    );
                    p->_on_post_resize(Selector());
                    p->_data = (*itr)._data;
                    p->clone_metadata(*itr);
                    current_index = ::boost::initialized_value;
                    break;
                }

                case ::boost::tree_node::post_order_traversal:
                {
                    p->on_post_copy_or_move();
                    p = p->get_parent_ptr();
                    ++(current_index = indices.back());
                    indices.pop_back();
                    break;
                }

                default:
                {
                    BOOST_ASSERT_MSG(
                        false
                      , "traversal_state must be pre- or post-order!"
                    );
                }
            }
        }

        BOOST_ASSERT_MSG(p == this->get_derived(), "itr not at-the-end");
    }

    template <typename Derived, typename T, typename Selector>
    void
        nary_node_base<Derived,T,Selector>::_clone_descendants(
            Derived const& copy
          , ::boost::mpl::false_
        )
    {
        pointer p = this->get_derived();

        for (
            depth_first_descendant_iterator<Derived const> itr(copy);
            itr;
            ++itr
        )
        {
            switch (::boost::tree_node::traversal_state(itr))
            {
                case ::boost::tree_node::pre_order_traversal:
                {
                    p = &*p->_add_child((*itr)._data);
                    p->clone_metadata(*itr);
                    break;
                }

                case ::boost::tree_node::post_order_traversal:
                {
                    p->on_post_copy_or_move();
                    p = p->get_parent_ptr();
                    break;
                }

                default:
                {
                    BOOST_ASSERT_MSG(
                        false
                      , "traversal_state must be pre- or post-order!"
                    );
                }
            }
        }

        BOOST_ASSERT_MSG(p == this->get_derived(), "itr not at-the-end");
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::_move_descendants(
            BOOST_RV_REF(Derived) source
        )
    {
        this->_move_descendants(
            static_cast<Derived&>(source)
          , ::boost::is_ptr_selector<Selector>()
        );
        this->get_derived()->on_post_copy_or_move();
    }

    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::_move_descendants(
            Derived& source
          , ::boost::mpl::true_
        )
    {
        this->_children.transfer(this->_children.begin(), source._children);
        self::_link_children_to_parent(
            this->get_derived()
          , this->_children.begin()
          , this->_children.end()
        );
    }

    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::_move_descendants(
            Derived& source
          , ::boost::mpl::false_
        )
    {
        this->_move_descendants_non_ptr(
            source
          , ::boost::is_random_access_selector<Selector>()
        );
        source._children.clear();
    }

    template <typename Derived, typename T, typename Selector>
    void
        nary_node_base<Derived,T,Selector>::_move_descendants_non_ptr(
            Derived& source
          , ::boost::mpl::true_
        )
    {
        pointer p = this->get_derived();
        ::std::deque<size_type> indices;
        size_type current_index = ::boost::initialized_value;

        p->_children.resize(source._children.size(), Derived(this->_data));
        p->_on_post_resize(Selector());

        for (depth_first_descendant_iterator<Derived> itr(source); itr; ++itr)
        {
            switch (::boost::tree_node::traversal_state(itr))
            {
                case ::boost::tree_node::pre_order_traversal:
                {
                    p->_children[current_index]._parent = p;
                    p = &p->_children[current_index];
                    indices.push_back(current_index);
                    p->_children.clear();
                    p->_children.resize(
                        (*itr)._children.size()
                      , Derived((*itr)._data)
                    );
                    p->_on_post_resize(Selector());
                    p->_data = ::boost::move((*itr)._data);
                    p->move_metadata(::boost::move(*itr));
                    current_index = ::boost::initialized_value;
                    break;
                }

                case ::boost::tree_node::post_order_traversal:
                {
                    (*itr)._children.clear();
                    p->on_post_copy_or_move();
                    p = p->get_parent_ptr();
                    ++(current_index = indices.back());
                    indices.pop_back();
                    break;
                }

                default:
                {
                    BOOST_ASSERT_MSG(
                        false
                      , "traversal_state must be pre- or post-order!"
                    );
                }
            }
        }

        BOOST_ASSERT_MSG(p == this->get_derived(), "itr not at-the-end");
    }

    template <typename Derived, typename T, typename Selector>
    void
        nary_node_base<Derived,T,Selector>::_move_descendants_non_ptr(
            Derived& source
          , ::boost::mpl::false_
        )
    {
        pointer p = this->get_derived();

        for (depth_first_descendant_iterator<Derived> itr(source); itr; ++itr)
        {
            switch (::boost::tree_node::traversal_state(itr))
            {
                case ::boost::tree_node::pre_order_traversal:
                {
                    p = &*p->_add_child(::boost::move((*itr)._data));
                    p->move_metadata(::boost::move(*itr));
                    break;
                }

                case ::boost::tree_node::post_order_traversal:
                {
                    p->on_post_copy_or_move();
                    p = p->get_parent_ptr();
                    break;
                }

                default:
                {
                    BOOST_ASSERT_MSG(
                        false
                      , "traversal_state must be pre- or post-order!"
                    );
                }
            }
        }

        BOOST_ASSERT_MSG(p == this->get_derived(), "itr not at-the-end");
    }

    template <typename Derived, typename T, typename Selector>
    template <typename A>
    inline void
        nary_node_base<Derived,T,Selector>::_on_post_insert(
            iterator to_child
          , ::boost::vector_selector< ::boost::mpl::true_,A>
        )
    {
        self::_link_children_to_parent(
            this->get_derived()
          , this->_children.begin()
          , this->_children.end()
        );
    }

    template <typename Derived, typename T, typename Selector>
    template <typename A>
    inline void
        nary_node_base<Derived,T,Selector>::_on_post_resize(
            ::boost::vector_selector< ::boost::mpl::true_,A>
        )
    {
        self::_link_children_to_parent(
            this->get_derived()
          , this->_children.begin()
          , this->_children.end()
        );
    }

    template <typename Derived, typename T, typename Selector>
    template <typename A>
    inline void
        nary_node_base<Derived,T,Selector>::_on_post_outsourced(
            ::boost::stable_vector_selector<A>
        )
    {
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <typename Derived, typename T, typename Selector>
    template <typename S>
    inline void
        nary_node_base<Derived,T,Selector>::_on_post_insert(
            iterator to_child
          , S
        )
    {
        (*to_child)._parent = this->get_derived();
    }

    template <typename Derived, typename T, typename Selector>
    template <typename S>
    inline void
        nary_node_base<Derived,T,Selector>::_on_post_resize(S)
    {
    }

    template <typename Derived, typename T, typename Selector>
    template <typename S>
    inline void nary_node_base<Derived,T,Selector>::_on_post_outsourced(S)
    {
        this->on_post_clear();
    }

    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::_on_post_clone_or_move(
            ::boost::mpl::true_
        )
    {
    }

    template <typename Derived, typename T, typename Selector>
    void
        nary_node_base<Derived,T,Selector>::_on_post_clone_or_move(
            ::boost::mpl::false_
        )
    {
        for (
            post_order_iterator<Derived> itr(*this->get_derived());
            itr;
            ++itr
        )
        {
            (*itr)._children.reverse();
        }
    }

    template <typename Derived, typename T, typename Selector>
    typename ::boost::insert_range_result_gen<Selector,Derived>::type
        nary_node_base<Derived,T,Selector>::_splice(
            iterator pos
          , Derived& node
          , iterator itr
          , iterator itr_end
          , ::boost::mpl::true_
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        size_type const result_size = ::std::distance(itr, itr_end);
        iterator result_itr = this->_children.insert(pos, itr, itr_end);

        node._children.erase(itr, itr_end);
        self::_link_children_to_parent(
            this->get_derived()
          , this->_children.begin()
          , this->_children.end()
        );
        this->get_derived()->on_post_copy_or_move();
        return ::std::pair<iterator,iterator>(
            result_itr
          , result_itr + result_size
        );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if 1
        size_type const result_size = ::std::distance(itr, itr_end);
        iterator result_itr = this->_children.insert(
            pos
          , ::boost::move_iterator<iterator>(itr)
          , ::boost::move_iterator<iterator>(itr_end)
        );

        node._children.erase(itr, itr_end);
        self::_link_children_to_parent(
            this->get_derived()
          , this->_children.begin()
          , this->_children.end()
        );
        this->get_derived()->on_post_copy_or_move();
        return ::std::pair<iterator,iterator>(
            result_itr
          , result_itr + result_size
        );
#else
        iterator result_itr = this->_children.insert(
            pos
          , ::std::distance(itr, itr_end)
          , Derived(this->_data)
        );

        pos = result_itr;

        for (iterator e_itr = itr; e_itr != itr_end; ++e_itr)
        {
            (*pos)._parent = this->get_derived();
            (*pos)._data = ::boost::move((*e_itr)._data);
            (*pos)._move_descendants_non_ptr(*e_itr, ::boost::mpl::true_());
            (*pos).move_metadata(::boost::move(*e_itr));
            (*pos).on_post_copy_or_move();
            ++pos;
        }

        node._children.erase(itr, itr_end);
        self::_link_children_to_parent(
            this->get_derived()
          , this->_children.begin()
          , this->_children.end()
        );
        this->get_derived()->on_post_copy_or_move();
        return ::std::pair<iterator,iterator>(result_itr, pos);
#endif
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    }

    template <typename Derived, typename T, typename Selector>
    inline typename ::boost::insert_range_result_gen<Selector,Derived>::type
        nary_node_base<Derived,T,Selector>::_splice(
            iterator pos
          , Derived& node
          , iterator itr
          , iterator itr_end
          , ::boost::mpl::false_
        )
    {
        typename ::boost::splice_function_gen<Selector>::type splicer;
        typename ::boost::insert_range_result_gen<
            Selector
          , Derived
        >::type result = splicer(
            this->_children
          , pos
          , node._children
          , itr
          , itr_end
        );

        self::_link_children_to_parent(
            this->get_derived()
          , ::boost::begin(result)
          , ::boost::end(result)
        );
        return result;
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

