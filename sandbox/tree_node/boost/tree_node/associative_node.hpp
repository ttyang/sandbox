// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ASSOCIATIVE_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_ASSOCIATIVE_NODE_HPP_INCLUDED

#include <utility>
#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_assoc_function_gen.hpp>
#include <boost/container_gen/is_associative_selector.hpp>
#include <boost/container_gen/is_recursive_selector.hpp>
#include <boost/container_gen/is_ptr_selector.hpp>
#include <boost/container_gen/has_stable_iters_selector.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>
#include <boost/tree_node/data_key.hpp>
#include <boost/assert.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#if !defined BOOST_NO_SFINAE
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#endif

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/move/move.hpp>
#endif

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
#include <boost/mpl/eval_if.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/category_of.hpp>
#endif

#include <boost/tree_node/_detail/config_begin.hpp>

//[reference__associative_node_base__put
namespace boost { namespace tree_node {

    //<-
    template <typename Derived, typename Key, typename Data, typename Selector>
    class associative_node_base;
    //->

    template <
        typename Derived
      , typename Key
      , typename Data
      , typename Selector
      , typename V
    >
    void
        put(
            associative_node_base<Derived,Key,Data,Selector>& node
          , data_key const& key
          , V const& value
        );
}}  // namespace boost::tree_node
//]

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename Key
      , typename Data
      , typename Selector
      , typename FusionKey
    >
    struct has_key_impl<
        associative_node_base<Derived,Key,Data,Selector>
      , FusionKey
    > : ::boost::fusion::result_of::has_key<Data,FusionKey>
    {
    };
}}  // namespace boost::tree_node

//[reference__associative_node_base__put__fusion
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename Key
      , typename Data
      , typename Selector
      , typename FusionKey
      , typename V
    >
    void
        put(
            associative_node_base<Derived,Key,Data,Selector>& node
          , FusionKey const& key
          , V const& value
          , typename ::boost::enable_if<
              typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                  typename ::boost::fusion::traits::is_sequence<Data>::type
                , ::boost::fusion::traits::is_associative<Data>
                , ::boost::mpl::false_
                >::type
              , ::boost::tree_node::has_key<
                  associative_node_base<Derived,Key,Data,Selector>
                , FusionKey
                >
              , ::boost::mpl::false_
              >::type
            , ::boost::mpl::true_
            >::type = ::boost::mpl::true_()
        );
}}  // namespace boost::tree_node
//]
#endif

namespace boost { namespace tree_node {

    template <typename Derived, typename Key, typename Data, typename Selector>
    class associative_node_base
      : public
        //[reference__associative_node_base__bases
        tree_node_base<Derived>
        //]
      , private ::boost::noncopyable
    {
        BOOST_MPL_ASSERT((::boost::is_associative_selector<Selector>));
        BOOST_MPL_ASSERT((::boost::is_recursive_selector<Selector>));

        typedef typename ::boost::container_gen<Selector,Key,Derived>::type
                children;

     public:
        //[reference__associative_node_base__super_t
        typedef tree_node_base<Derived>
                super_t;
        //]

        //[reference__associative_node_base__pointer
        typedef typename super_t::pointer
                pointer;
        //]

        //[reference__associative_node_base__const_pointer
        typedef typename super_t::const_pointer
                const_pointer;
        //]

        //[reference__associative_node_base__iterator
        typedef // implementation_defined
                //<-
                typename children::iterator
                //->
                iterator;
        //]

        //[reference__associative_node_base__const_iterator
        typedef // implementation_defined
                //<-
                typename children::const_iterator
                //->
                const_iterator;
        //]

        //[reference__associative_node_base__size_type
        typedef // implementation_defined
                //<-
                typename children::size_type
                //->
                size_type;
        //]

        //[reference__associative_node_base__traits
        struct traits
        {
            typedef Key key_type;
            typedef Data data_type;
            typedef typename ::boost::mpl::if_<
                        ::boost::is_ptr_selector<Selector>
                      , ::boost::iterator_range<iterator>
                      , ::std::pair<iterator,iterator>
                    >::type
                    iterator_range;
            typedef typename ::boost::mpl::if_<
                        ::boost::is_ptr_selector<Selector>
                      , ::boost::iterator_range<const_iterator>
                      , ::std::pair<const_iterator,const_iterator>
                    >::type
                    const_iterator_range;
        };
        //]

     private:
        children                   _children;
        typename traits::data_type _data;
        pointer                    _parent;

     protected:
        //[reference__associative_node_base__derived_copy_ctor
        associative_node_base(Derived const& copy);
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        associative_node_base(BOOST_RV_REF(Derived) source);
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__associative_node_base__emplacement_ctor
        template <typename ...Args>
        explicit associative_node_base(Args&& ...args);
        //]
#else
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_FWD_DECL
          , associative_node_base
        )
#endif

        ~associative_node_base();

        //[reference__associative_node_base__on_post_copy_or_move
        void on_post_copy_or_move();
        //]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__associative_node_base__copy_assign
        void copy_assign(Derived const& copy);
        //]
#else
        void copy_assign(BOOST_COPY_ASSIGN_REF(Derived) copy);

        void move_assign(BOOST_RV_REF(Derived) source);
#endif

     public:
        //[reference__associative_node_base__key_value_operator__const
        typename traits::data_type const& operator[](data_key const&) const;
        //]

        //[reference__associative_node_base__key_value_operator
        typename traits::data_type& operator[](data_key const&);
        //]

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        //[reference__associative_node_base__fusion_key_value_operator__const
        template <typename FusionKey>
        typename ::boost::lazy_enable_if<
            typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                    typename ::boost::fusion::traits::is_sequence<Data>::type
                  , ::boost::fusion::traits::is_associative<Data>
                  , ::boost::mpl::false_
                >::type
              , ::boost::tree_node::has_key<
                    associative_node_base<Derived,Key,Data,Selector>
                  , FusionKey
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::fusion::result_of::at_key<Data const,FusionKey>
        >::type
            operator[](FusionKey const&) const;
        //]

        //[reference__associative_node_base__fusion_key_value_operator
        template <typename FusionKey>
        typename ::boost::lazy_enable_if<
            typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                    typename ::boost::fusion::traits::is_sequence<Data>::type
                  , ::boost::fusion::traits::is_associative<Data>
                  , ::boost::mpl::false_
                >::type
              , ::boost::tree_node::has_key<
                    associative_node_base<Derived,Key,Data,Selector>
                  , FusionKey
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::fusion::result_of::at_key<Data,FusionKey>
        >::type
            operator[](FusionKey const&);
        //]
#endif

        //[reference__associative_node_base__get_parent_ptr__const
        const_pointer get_parent_ptr() const;
        //]

        //[reference__associative_node_base__get_parent_ptr
        pointer get_parent_ptr();
        //]

        //[reference__associative_node_base__insert
        iterator
            insert(
                typename traits::key_type const& key
              , Derived const& child
            );
        //]

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__associative_node_base__emplace
        template <typename ...Args>
        iterator emplace(typename traits::key_type const& key, Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO(z, n, _)                      \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        iterator                                                             \
            emplace(                                                         \
                typename traits::key_type const& key                         \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        //[reference__associative_node_base__begin__const
        const_iterator begin() const;
        //]

        //[reference__associative_node_base__begin
        iterator begin();
        //]

        //[reference__associative_node_base__end__const
        const_iterator end() const;
        //]

        //[reference__associative_node_base__end
        iterator end();
        //]

        //[reference__associative_node_base__size
        size_type size() const;
        //]

        //[reference__associative_node_base__empty
        bool empty() const;
        //]

        //[reference__associative_node_base__clear
        void clear();
        //]

        //[reference__associative_node_base__find__const
        const_iterator find(typename traits::key_type const& key) const;
        //]

        //[reference__associative_node_base__find
        iterator find(typename traits::key_type const& key);
        //]

        //[reference__associative_node_base__equal_range__const
        typename traits::const_iterator_range
            equal_range(typename traits::key_type const& key) const;
        //]

        //[reference__associative_node_base__equal_range
        typename traits::iterator_range
            equal_range(typename traits::key_type const& key);
        //]

        //[reference__associative_node_base__erase
        size_type erase(typename traits::key_type const& key);
        //]

     private:
#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename ...Args>
        iterator
            _add_child(typename traits::key_type const& key, Args&& ...args);
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO(z, n, _)                      \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        iterator                                                             \
            _add_child(                                                      \
                typename traits::key_type const& key                         \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        void _initialize(iterator& itr);

        void _link_children_to_parent();

        void _on_post_modify_value(data_key const& key);

        template <typename D, typename K, typename T, typename S, typename V>
        friend void
            put(
                associative_node_base<D,K,T,S>& node
              , data_key const& key
              , V const& value
            );

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        template <typename FusionKey>
        void _on_post_modify_value(FusionKey const& key);

        template <
            typename D
          , typename K
          , typename T
          , typename S
          , typename FusionKey
          , typename V
        >
        friend void
          put(
            associative_node_base<D,K,T,S>& node
          , FusionKey const& key
          , V const& value
          , typename ::boost::enable_if<
              typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                  typename ::boost::fusion::traits::is_sequence<T>::type
                , ::boost::fusion::traits::is_associative<T>
                , ::boost::mpl::false_
                >::type
              , ::boost::tree_node::has_key<
                  associative_node_base<D,K,T,S>
                , FusionKey
                >
              , ::boost::mpl::false_
              >::type
            , ::boost::mpl::true_
            >::type
          );
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
    };

    template <typename Derived, typename Key, typename Data, typename Selector>
    associative_node_base<Derived,Key,Data,Selector>::associative_node_base(
        Derived const& copy
    ) : _children(copy._children)
      , _data(copy._data)
      , _parent(copy._parent)
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename Key, typename Data, typename Selector>
    associative_node_base<Derived,Key,Data,Selector>::associative_node_base(
        BOOST_RV_REF(Derived) source
    ) : _children(::boost::move(source._children))
      , _data(::boost::move(source._data))
      , _parent(source._parent)
    {
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename Key, typename Data, typename Selector>
    template <typename ...Args>
    associative_node_base<Derived,Key,Data,Selector>::associative_node_base(
        Args&& ...args
    ) : _children(), _data(::boost::forward<Args>(args)...), _parent()
    {
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO(z, n, _)                      \
    template <                                                               \
        typename Derived                                                     \
      , typename Key                                                         \
      , typename Data                                                        \
      , typename Selector                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    associative_node_base<Derived,Key,Data,Selector>::associative_node_base( \
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
      , BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename Key, typename Data, typename Selector>
    associative_node_base<Derived,Key,Data,Selector>::~associative_node_base()
    {
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline void
        associative_node_base<
            Derived
          , Key
          , Data
          , Selector
        >::on_post_copy_or_move()
    {
        this->_link_children_to_parent();
        this->on_post_propagate_value(data_key());
    }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename Key, typename Data, typename Selector>
    void
        associative_node_base<Derived,Key,Data,Selector>::copy_assign(
            Derived const& copy
        )
    {
        Derived twin(copy);

        this->_children = twin._children;
        this->_data = twin._data;
    }
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename Derived, typename Key, typename Data, typename Selector>
    void
        associative_node_base<Derived,Key,Data,Selector>::copy_assign(
            BOOST_COPY_ASSIGN_REF(Derived) copy
        )
    {
        Derived twin(static_cast<Derived const&>(copy));

        this->_children = ::boost::move(twin._children);
        this->_data = ::boost::move(twin._data);
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline void
        associative_node_base<Derived,Key,Data,Selector>::move_assign(
            BOOST_RV_REF(Derived) source
        )
    {
        this->_children = ::boost::move(source._children);
        this->_data = ::boost::move(source._data);
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::traits::data_type const&
        associative_node_base<Derived,Key,Data,Selector>::operator[](
            data_key const&
        ) const
    {
        return this->_data;
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::traits::data_type&
        associative_node_base<Derived,Key,Data,Selector>::operator[](
            data_key const&
        )
    {
        return this->_data;
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    template <typename Derived, typename Key, typename Data, typename Selector>
    template <typename FusionKey>
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<Data>::type
              , ::boost::fusion::traits::is_associative<Data>
              , ::boost::mpl::false_
            >::type
          , ::boost::tree_node::has_key<
                associative_node_base<Derived,Key,Data,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<Data const,FusionKey>
    >::type
        associative_node_base<Derived,Key,Data,Selector>::operator[](
            FusionKey const&
        ) const
    {
        return ::boost::fusion::at_key<FusionKey>(this->_data);
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    template <typename FusionKey>
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<Data>::type
              , ::boost::fusion::traits::is_associative<Data>
              , ::boost::mpl::false_
            >::type
          , ::boost::tree_node::has_key<
                associative_node_base<Derived,Key,Data,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<Data,FusionKey>
    >::type
        associative_node_base<Derived,Key,Data,Selector>::operator[](
            FusionKey const&
        )
    {
        return ::boost::fusion::at_key<FusionKey>(this->_data);
    }
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::const_pointer
        associative_node_base<Derived,Key,Data,Selector>::get_parent_ptr() const
    {
        return this->_parent;
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<Derived,Key,Data,Selector>::pointer
        associative_node_base<Derived,Key,Data,Selector>::get_parent_ptr()
    {
        return this->_parent;
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<Derived,Key,Data,Selector>::iterator
        associative_node_base<Derived,Key,Data,Selector>::insert(
            typename traits::key_type const& key
          , Derived const& child
        )
    {
#if defined BOOST_MSVC
        Derived twin(child);
        iterator result(this->_add_child(key, twin));
#else
        iterator result(this->_add_child(key, Derived(child)));
#endif
        BOOST_ASSERT(
            ::boost::tree_node::dereference_iterator(
                result
            )._parent == this->get_derived()
        );
        return result;
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename Key, typename Data, typename Selector>
    template <typename ...Args>
    typename associative_node_base<Derived,Key,Data,Selector>::iterator
        associative_node_base<Derived,Key,Data,Selector>::emplace(
            typename traits::key_type const& key
          , Args&& ...args
        )
    {
        iterator result(
            this->_add_child(key, ::boost::forward<Args>(args)...)
        );
        BOOST_ASSERT(
            ::boost::tree_node::dereference_iterator(
                result
            )._parent == this->get_derived()
        );
        return result;
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO(z, n, _)                      \
    template <                                                               \
        typename Derived                                                     \
      , typename Key                                                         \
      , typename Data                                                        \
      , typename Selector                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename associative_node_base<Derived,Key,Data,Selector>::iterator      \
        associative_node_base<Derived,Key,Data,Selector>::emplace(           \
            typename traits::key_type const& key                             \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        iterator result = this->_add_child(                                  \
            key                                                              \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        );                                                                   \
        BOOST_ASSERT(                                                        \
            ::boost::tree_node::dereference_iterator(                        \
                result                                                       \
            )._parent == this->get_derived()                                 \
        );                                                                   \
        return result;                                                       \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::const_iterator
        associative_node_base<Derived,Key,Data,Selector>::begin() const
    {
        return this->_children.begin();
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<Derived,Key,Data,Selector>::iterator
        associative_node_base<Derived,Key,Data,Selector>::begin()
    {
        return this->_children.begin();
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::const_iterator
        associative_node_base<Derived,Key,Data,Selector>::end() const
    {
        return this->_children.end();
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<Derived,Key,Data,Selector>::iterator
        associative_node_base<Derived,Key,Data,Selector>::end()
    {
        return this->_children.end();
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<Derived,Key,Data,Selector>::size_type
        associative_node_base<Derived,Key,Data,Selector>::size() const
    {
        return this->_children.size();
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline bool associative_node_base<Derived,Key,Data,Selector>::empty() const
    {
        return this->_children.empty();
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline void associative_node_base<Derived,Key,Data,Selector>::clear()
    {
        this->_children.clear();
        this->on_post_clear();
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::const_iterator
        associative_node_base<Derived,Key,Data,Selector>::find(
            typename traits::key_type const& key
        ) const
    {
        return this->_children.find(key);
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<Derived,Key,Data,Selector>::iterator
        associative_node_base<Derived,Key,Data,Selector>::find(
            typename traits::key_type const& key
        )
    {
        return this->_children.find(key);
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::traits::const_iterator_range
        associative_node_base<Derived,Key,Data,Selector>::equal_range(
            typename traits::key_type const& key
        ) const
    {
        return this->_children.equal_range(key);
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::traits::iterator_range
        associative_node_base<Derived,Key,Data,Selector>::equal_range(
            typename traits::key_type const& key
        )
    {
        return this->_children.equal_range(key);
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    typename associative_node_base<Derived,Key,Data,Selector>::size_type
        associative_node_base<Derived,Key,Data,Selector>::erase(
            typename traits::key_type const& key
        )
    {
        size_type result = this->_children.erase(key);
        this->on_post_erase();
        return result;
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Derived, typename Key, typename Data, typename Selector>
    template <typename ...Args>
    typename associative_node_base<Derived,Key,Data,Selector>::iterator
        associative_node_base<Derived,Key,Data,Selector>::_add_child(
            typename traits::key_type const& key
          , Args&& ...args
        )
    {
        typename ::boost::emplace_associative_function_gen<Selector>::type
            emplacer;
        ::std::pair<iterator,bool> p = emplacer(
            this->_children
          , key
          , ::boost::forward<Args>(args)...
        );

        if (p.second)
        {
            this->_initialize(p.first);
        }

        return p.first;
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO(z, n, _)                      \
    template <                                                               \
        typename Derived                                                     \
      , typename Key                                                         \
      , typename Data                                                        \
      , typename Selector                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename associative_node_base<Derived,Key,Data,Selector>::iterator      \
        associative_node_base<Derived,Key,Data,Selector>::_add_child(        \
            typename traits::key_type const& key                             \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        typename ::boost::emplace_associative_function_gen<Selector>::type   \
            emplacer;                                                        \
        ::std::pair<iterator,bool> p = emplacer(                             \
            this->_children                                                  \
          , key                                                              \
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
      , BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_ASSOCIATIVE_NODE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline void
        associative_node_base<Derived,Key,Data,Selector>::_initialize(
            iterator& itr
        )
    {
        Derived& child = ::boost::tree_node::dereference_iterator(itr);

        child._parent = this->get_derived();
        child.on_post_inserted(
            itr
          , ::boost::has_stable_iterators_selector<Selector>()
        );
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    void
        associative_node_base<
            Derived
          , Key
          , Data
          , Selector
        >::_link_children_to_parent()
    {
        iterator itr_end = this->end();

        for (iterator itr = this->begin(); itr != itr_end; ++itr)
        {
            ::boost::tree_node::dereference_iterator(
                itr
            )._parent = this->get_derived();
        }
    }

    template <typename Derived, typename Key, typename Data, typename Selector>
    inline void
        associative_node_base<
            Derived
          , Key
          , Data
          , Selector
        >::_on_post_modify_value(data_key const& key)
    {
        this->on_post_modify_value(key);
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    template <typename Derived, typename Key, typename Data, typename Selector>
    template <typename FusionKey>
    inline void
        associative_node_base<
            Derived
          , Key
          , Data
          , Selector
        >::_on_post_modify_value(FusionKey const& key)
    {
        this->on_post_modify_value(key);
    }
#endif
}}  // namespace boost::tree_node

//[reference__associative_node_base__get__const
namespace boost { namespace tree_node {

    template <typename Derived, typename Key, typename Data, typename Selector>
    typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::traits::data_type const&
        get(
            associative_node_base<Derived,Key,Data,Selector> const& node
          , data_key const& key
        );

    //<-
    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::traits::data_type const&
        get(
            associative_node_base<Derived,Key,Data,Selector> const& node
          , data_key const& key
        )
    {
        return node[key];
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__associative_node_base__get
namespace boost { namespace tree_node {

    template <typename Derived, typename Key, typename Data, typename Selector>
    typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::traits::data_type&
        get(
            associative_node_base<Derived,Key,Data,Selector>& node
          , data_key const& key
        );

    //<-
    template <typename Derived, typename Key, typename Data, typename Selector>
    inline typename associative_node_base<
        Derived
      , Key
      , Data
      , Selector
    >::traits::data_type&
        get(
            associative_node_base<Derived,Key,Data,Selector>& node
          , data_key const& key
        )
    {
        return node[key];
    }

    template <
        typename Derived
      , typename Key
      , typename Data
      , typename Selector
      , typename V
    >
    inline void
        put(
            associative_node_base<Derived,Key,Data,Selector>& node
          , data_key const& key
          , V const& value
        )
    {
        node[key] = value;
        node._on_post_modify_value(key);
    }
    //->
}}  // namespace boost::tree_node
//]

#if !defined BOOST_NO_SFINAE
//[reference__associative_node_base__get__key__const
namespace boost { namespace tree_node {

    template <
        typename DataKey
      , typename Derived
      , typename Key
      , typename Data
      , typename Selector
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<DataKey,data_key>
      , typename associative_node_base<
            Derived
          , Key
          , Data
          , Selector
        >::traits::data_type const&
    >::type
        get(associative_node_base<Derived,Key,Data,Selector> const& node);

    //<-
    template <
        typename DataKey
      , typename Derived
      , typename Key
      , typename Data
      , typename Selector
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<DataKey,data_key>
      , typename associative_node_base<
            Derived
          , Key
          , Data
          , Selector
        >::traits::data_type const&
    >::type
        get(associative_node_base<Derived,Key,Data,Selector> const& node)
    {
        return node[data_key()];
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__associative_node_base__get__key
namespace boost { namespace tree_node {

    template <
        typename DataKey
      , typename Derived
      , typename Key
      , typename Data
      , typename Selector
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<DataKey,data_key>
      , typename associative_node_base<
            Derived
          , Key
          , Data
          , Selector
        >::traits::data_type&
    >::type
        get(associative_node_base<Derived,Key,Data,Selector>& node);

    //<-
    template <
        typename DataKey
      , typename Derived
      , typename Key
      , typename Data
      , typename Selector
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<DataKey,data_key>
      , typename associative_node_base<
            Derived
          , Key
          , Data
          , Selector
        >::traits::data_type&
    >::type
        get(associative_node_base<Derived,Key,Data,Selector>& node)
    {
        return node[data_key()];
    }
    //->
}}  // namespace boost::tree_node
//]
#endif  // BOOST_NO_SFINAE

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
//[reference__associative_node_base__get__fusion__const
namespace boost { namespace tree_node {

    template <
        typename FusionKey
      , typename Derived
      , typename Key
      , typename Data
      , typename Selector
    >
    typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<Data>::type
              , ::boost::fusion::traits::is_associative<Data>
              , ::boost::mpl::false_
            >::type
          , ::boost::tree_node::has_key<
                associative_node_base<Derived,Key,Data,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<Data const,FusionKey>
    >::type
        get(associative_node_base<Derived,Key,Data,Selector> const& node);

    //<-
    template <
        typename FusionKey
      , typename Derived
      , typename Key
      , typename Data
      , typename Selector
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<Data>::type
              , ::boost::fusion::traits::is_associative<Data>
              , ::boost::mpl::false_
            >::type
          , ::boost::tree_node::has_key<
                associative_node_base<Derived,Key,Data,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<Data const,FusionKey>
    >::type
        get(associative_node_base<Derived,Key,Data,Selector> const& node)
    {
        return node[FusionKey()];
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__associative_node_base__get__fusion
namespace boost { namespace tree_node {

    template <
        typename FusionKey
      , typename Derived
      , typename Key
      , typename Data
      , typename Selector
    >
    typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<Data>::type
              , ::boost::fusion::traits::is_associative<Data>
              , ::boost::mpl::false_
            >::type
          , ::boost::tree_node::has_key<
                associative_node_base<Derived,Key,Data,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<Data,FusionKey>
    >::type
        get(associative_node_base<Derived,Key,Data,Selector>& node);

    //<-
    template <
        typename FusionKey
      , typename Derived
      , typename Key
      , typename Data
      , typename Selector
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::if_<
            typename ::boost::mpl::eval_if<
                typename ::boost::fusion::traits::is_sequence<Data>::type
              , ::boost::fusion::traits::is_associative<Data>
              , ::boost::mpl::false_
            >::type
          , ::boost::tree_node::has_key<
                associative_node_base<Derived,Key,Data,Selector>
              , FusionKey
            >
          , ::boost::mpl::false_
        >::type
      , ::boost::fusion::result_of::at_key<Data,FusionKey>
    >::type
        get(associative_node_base<Derived,Key,Data,Selector>& node)
    {
        return node[FusionKey()];
    }

    template <
        typename Derived
      , typename Key
      , typename Data
      , typename Selector
      , typename FusionKey
      , typename V
    >
    inline void
        put(
            associative_node_base<Derived,Key,Data,Selector>& node
          , FusionKey const& key
          , V const& value
          , typename ::boost::enable_if<
              typename ::boost::mpl::if_<
                typename ::boost::mpl::eval_if<
                  typename ::boost::fusion::traits::is_sequence<Data>::type
                , ::boost::fusion::traits::is_associative<Data>
                , ::boost::mpl::false_
                >::type
              , ::boost::tree_node::has_key<
                  associative_node_base<Derived,Key,Data,Selector>
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
    //->
}}  // namespace boost::tree_node
//]
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Data
      , typename Selector = ::boost::ptr_mapS
    >
    struct associative_node
      : public
        //[reference__associative_node__bases
        associative_node_base<
            associative_node<Key,Data,Selector>
          , Key
          , Data
          , Selector
        >
        //]
    {
        //[reference__associative_node__super_t
        typedef associative_node_base<
                    associative_node
                  , Key
                  , Data
                  , Selector
                >
                super_t;
        //]

        //[reference__associative_node__traits
        typedef typename super_t::traits
                traits;
        //]

        //[reference__associative_node__pointer
        typedef typename super_t::pointer
                pointer;
        //]

        //[reference__associative_node__const_pointer
        typedef typename super_t::const_pointer
                const_pointer;
        //]

        //[reference__associative_node__iterator
        typedef typename super_t::iterator
                iterator;
        //]

        //[reference__associative_node__const_iterator
        typedef typename super_t::const_iterator
                const_iterator;
        //]

        //[reference__associative_node__size_type
        typedef typename super_t::size_type
                size_type;
        //]

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(associative_node, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__associative_node__emplacement_ctor
        template <typename ...Args>
        explicit associative_node(Args&& ...args);
        //]
#else
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (associative_node, super_t)
        )
#endif
    };

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename Key, typename Data, typename Selector>
    template <typename ...Args>
    inline associative_node<Key,Data,Selector>::associative_node(
        Args&& ...args
    ) : super_t(::boost::forward<Args>(args)...)
    {
    }
#endif
}}  // namespace boost::tree_node

//[reference__associative_node_gen
namespace boost { namespace tree_node {

    template <typename Selector = ::boost::ptr_mapS>
    struct associative_node_gen
    {
        template <typename Derived, typename Key, typename Data>
        struct apply
        {
            typedef associative_node_base<Derived,Key,Data,Selector> type;
        };
    };

    typedef associative_node_gen<> associative_node_default_gen;
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_ASSOCIATIVE_NODE_HPP_INCLUDED

