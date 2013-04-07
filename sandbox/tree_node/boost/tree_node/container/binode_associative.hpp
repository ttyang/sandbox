// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_CONTAINER_BINODE_ASSOCIATIVE_HPP_INCLUDED
#define BOOST_TREE_NODE_CONTAINER_BINODE_ASSOCIATIVE_HPP_INCLUDED

#include <boost/config.hpp>

#if !defined BOOST_NO_CXX11_NULLPTR
#include <cstddef>
#endif

#include <algorithm>
#include <utility>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/utility/value_init.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/move/move.hpp>
#include <boost/container/allocator_traits.hpp>
#endif

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/key/data.hpp>
#include <boost/tree_node/key/count.hpp>
#include <boost/tree_node/iterator/in_order.hpp>
#include <boost/tree_node/intrinsic/has_key.hpp>
#include <boost/tree_node/intrinsic/value_at_key.hpp>
#include <boost/tree_node/algorithm/binary_descendant.hpp>
#include <boost/tree_node/algorithm/binary_lower_bound.hpp>
#include <boost/tree_node/algorithm/binary_upper_bound.hpp>
#include <boost/tree_node/algorithm/binary_descendant_at_index.hpp>
#include <boost/tree_node/container/binode_associative_fwd.hpp>
#include <boost/assert.hpp>

namespace boost { namespace tree_node {

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    class binode_associative_container
    {
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        BOOST_COPYABLE_AND_MOVABLE(binode_associative_container)
#endif

     public:
        //[reference__binode_associative_container__key_type
        typedef T1 key_type;
        //]

        //[reference__binode_associative_container__value_type
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<T2>
                  , T1
                  , ::std::pair<T1 const,T2>
                >::type
                value_type;
        //]

        //[reference__binode_associative_container__reference
        typedef value_type& reference;
        //]

        //[reference__binode_associative_container__const_reference
        typedef value_type const& const_reference;
        //]

        //[reference__binode_associative_container__pointer
        typedef value_type* pointer;
        //]

        //[reference__binode_associative_container__const_pointer
        typedef value_type const* const_pointer;
        //]

        //[reference__binode_associative_container__node
        typedef typename ::boost::mpl::apply_wrap1<
                    NodeGenerator
                  , typename ::boost::mpl::if_<
                        ::std::tr1::is_void<T2>
                      , T1
                      , ::std::pair<T1,T2>
                    >::type
                >::type
                node;
        //]

        //[reference__binode_associative_container__allocator_type
        typedef typename node::traits::allocator allocator_type;
        //]

     private:
        //[reference__binode_associative_container__transition_function
        struct simple_transform_function
        {
            typedef const_reference const_result;
            typedef const_reference mutable_result;
            const_reference operator()(node const& n) const;
        };

        struct pair_associative_transform_function
        {
            typedef ::std::pair<T1 const&,T2 const&> const_result;
            typedef ::std::pair<T1 const&,T2&> mutable_result;
            const_result operator()(node const& n) const;
            mutable_result operator()(node& n) const;
        };

        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_void<T2>
                  , simple_transform_function
                  , pair_associative_transform_function
                >::type
                transform_function;
        //]

     public:
        //[reference__binode_associative_container__iterator
        typedef ::boost::transform_iterator<
                    transform_function
                  , in_order_iterator<
                        typename ::boost::mpl::if_<
                            ::std::tr1::is_void<T2>
                          , node const
                          , node
                        >::type
                    >
                >
                iterator;
        //]

        //[reference__binode_associative_container__const_iterator
        typedef ::boost::transform_iterator<
                    transform_function
                  , in_order_iterator<node const>
                >
                const_iterator;
        //]

        //[reference__binode_associative_container__reverse_iterator
        typedef ::boost::transform_iterator<
                    transform_function
                  , in_order_iterator<
                        typename ::boost::mpl::if_<
                            ::std::tr1::is_void<T2>
                          , node const
                          , node
                        >::type
                      , ::boost::mpl::true_
                    >
                >
                reverse_iterator;
        //]

        //[reference__binode_associative_container__const_reverse_iterator
        typedef ::boost::transform_iterator<
                    transform_function
                  , in_order_iterator<node const,::boost::mpl::true_>
                >
                const_reverse_iterator;
        //]

        //[reference__binode_associative_container__size_type
        typedef typename ::boost::mpl::eval_if<
                    result_of::has_key<node,count_key>
                  , result_of::value_at_key<node,count_key>
                  , typename node::size_type
                >::type
                size_type;
        //]

        //[reference__binode_associative_container__key_compare
        typedef typename ::boost::mpl::apply_wrap1<
                    CompareSelector
                  , key_type
                >::type
                key_compare;
        //]

        //[reference__binode_associative_container__value_compare
        class value_compare
        {
            //<-
            key_compare const& _compare;
            //->

         public:
            typedef bool result_type;

            explicit value_compare(key_compare const& compare);
            result_type operator()(const_reference, const_reference) const;
            result_type operator()(node const& n, key_type const& key) const;
            result_type operator()(key_type const& key, node const& n) const;

            //<-
         private:
            result_type
                _evaluate(
                    const_reference arg1
                  , const_reference arg2
                  , ::std::tr1::true_type
                ) const;
            result_type
                _evaluate(
                    const_reference arg1
                  , const_reference arg2
                  , ::std::tr1::false_type
                ) const;
            result_type
                _evaluate(
                    node const& n
                  , key_type const& key
                  , ::std::tr1::true_type
                ) const;
            result_type
                _evaluate(
                    node const& n
                  , key_type const& key
                  , ::std::tr1::false_type
                ) const;
            result_type
                _evaluate(
                    key_type const& key
                  , node const& n
                  , ::std::tr1::true_type
                ) const;
            result_type
                _evaluate(
                    key_type const& key
                  , node const& n
                  , ::std::tr1::false_type
                ) const;
            //->
        };
        //]

     private:
        class insert_compare
        {
            key_compare const& _compare;

         public:
            typedef bool result_type;

            explicit insert_compare(key_compare const& compare);
            result_type operator()(node const&, const_reference) const;
            result_type operator()(const_reference, node const&) const;

         private:
            result_type
                _evaluate(
                    node const& n
                  , const_reference value
                  , ::std::tr1::true_type
                ) const;
            result_type
                _evaluate(
                    node const& n
                  , const_reference value
                  , ::std::tr1::false_type
                ) const;
            result_type
                _evaluate(
                    const_reference value
                  , node const& n
                  , ::std::tr1::true_type
                ) const;
            result_type
                _evaluate(
                    const_reference value
                  , node const& n
                  , ::std::tr1::false_type
                ) const;
        };

        allocator_type _allocator;
        typename node::pointer _root_ptr;
        key_compare _key_compare;
        value_compare _value_compare;

     public:
        //[reference__binode_associative_container__default_ctor
        binode_associative_container();
        //]

        //[reference__binode_associative_container__ctor_w_alloc
        explicit binode_associative_container(allocator_type const& allocator);
        //]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__binode_associative_container__copy_ctor
        binode_associative_container(
            binode_associative_container const& copy
        );
        //]
#else
        binode_associative_container(
            BOOST_COPY_ASSIGN_REF(binode_associative_container) copy
        );
#endif

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__binode_associative_container__copy_ctor_w_alloc
        binode_associative_container(
            binode_associative_container const& copy
          , allocator_type const& allocator
        );
        //]
#else
        binode_associative_container(
            BOOST_COPY_ASSIGN_REF(binode_associative_container) copy
          , allocator_type const& allocator
        );
#endif

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        binode_associative_container(
            BOOST_RV_REF(binode_associative_container) source
        );

        binode_associative_container(
            BOOST_RV_REF(binode_associative_container) source
          , allocator_type const& allocator
        );

        binode_associative_container&
            operator=(BOOST_RV_REF(binode_associative_container) source);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__binode_associative_container__copy_assign
        binode_associative_container&
            operator=(binode_associative_container const& copy);
        //]
#else
        binode_associative_container&
            operator=(
                BOOST_COPY_ASSIGN_REF(binode_associative_container) copy
            );
#endif

        //[reference__binode_associative_container__dtor
        ~binode_associative_container();
        //]

        //[reference__binode_associative_container__data
        typename node::const_pointer data() const;
        //]

        //[reference__binode_associative_container__cbegin
        const_iterator cbegin() const;
        const_iterator begin() const;
        //]

        //[reference__binode_associative_container__begin
        iterator begin();
        //]

        //[reference__binode_associative_container__cend
        const_iterator cend() const;
        const_iterator end() const;
        //]

        //[reference__binode_associative_container__end
        iterator end();
        //]

        //[reference__binode_associative_container__crbegin
        const_reverse_iterator crbegin() const;
        const_reverse_iterator rbegin() const;
        //]

        //[reference__binode_associative_container__rbegin
        reverse_iterator rbegin();
        //]

        //[reference__binode_associative_container__crend
        const_reverse_iterator crend() const;
        const_reverse_iterator rend() const;
        //]

        //[reference__binode_associative_container__rend
        reverse_iterator rend();
        //]

        //[reference__binode_associative_container__cfind
        const_iterator find(key_type const& key) const;
        //]

        //[reference__binode_associative_container__find
        iterator find(key_type const& key);
        //]

        //[reference__binode_associative_container__lower_bound__const
        const_iterator lower_bound(key_type const& key) const;
        //]

        //[reference__binode_associative_container__lower_bound
        iterator lower_bound(key_type const& key);
        //]

        //[reference__binode_associative_container__upper_bound__const
        const_iterator upper_bound(key_type const& key) const;
        //]

        //[reference__binode_associative_container__upper_bound
        iterator upper_bound(key_type const& key);
        //]

        //[reference__binode_associative_container__equal_range__const
        ::std::pair<const_iterator,const_iterator>
            equal_range(key_type const& key) const;
        //]

        //[reference__binode_associative_container__equal_range
        ::std::pair<iterator,iterator> equal_range(key_type const& key);
        //]

        //[reference__binode_associative_container__insert
        typename ::boost::mpl::if_<
            IsMultipleAssociative
          , iterator
          , ::std::pair<iterator,bool>
        >::type
            insert(value_type const& value);
        //]

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binode_associative_container__emplace
        template <typename ...Args>
        typename ::boost::mpl::if_<
            IsMultipleAssociative
          , iterator
          , ::std::pair<iterator,bool>
        >::type
            emplace(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        typename ::boost::mpl::if_<                                          \
            IsMultipleAssociative                                            \
          , iterator                                                         \
          , ::std::pair<iterator,bool>                                       \
        >::type                                                              \
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
          , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        //[reference__binode_associative_container__erase
        size_type erase(key_type const& key);
        //]

        //[reference__binode_associative_container__empty
        bool empty() const;
        //]

        //[reference__binode_associative_container__clear
        void clear();
        //]

        //[reference__binode_associative_container__size
        size_type size() const;
        //]

        //[reference__binode_associative_container__index_operator__const
        typename transform_function::const_result
            operator[](size_type const& index) const;
        //]

        //[reference__binode_associative_container__index_operator
        typename transform_function::mutable_result
            operator[](size_type const& index);
        //]

     private:
        static typename node::pointer
            _construct_node_from(
                ::std::tr1::true_type
              , allocator_type& allocator
              , value_type const& value
            );

        static typename node::pointer
            _construct_node_from(
                ::std::tr1::false_type
              , allocator_type& allocator
              , value_type const& value
            );

        static typename node::pointer
            _construct_node_from(
                ::std::tr1::true_type
              , allocator_type& allocator
              , typename node::pointer p
            );

        static typename node::pointer
            _construct_node_from(
                ::std::tr1::false_type
              , allocator_type& allocator
              , typename node::pointer p
            );

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename ...Args>
        static typename node::pointer
            _construct_node_from(
                ::std::tr1::true_type
              , allocator_type& allocator
              , Args&& ...args
            );

        template <typename ...Args>
        static typename node::pointer
            _construct_node_from(
                ::std::tr1::false_type
              , allocator_type& allocator
              , Args&& ...args
            );

        template <typename ...Args>
        static value_type
            _construct_value_from(
                ::std::tr1::true_type
              , Args&& ...args
            );

        template <typename ...Args>
        static value_type
            _construct_value_from(
                ::std::tr1::false_type
              , key_type const& key
              , Args&& ...args
            );

        template <typename ...Args>
        iterator _emplace(::boost::mpl::true_, Args&& ...args);

        template <typename ...Args>
        ::std::pair<iterator,bool>
            _emplace(::boost::mpl::false_, Args&& ...args);
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        static typename node::pointer                                        \
            _construct_node_from(                                            \
                ::std::tr1::true_type                                        \
              , allocator_type& allocator                                    \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        static typename node::pointer                                        \
            _construct_node_from(                                            \
                ::std::tr1::false_type                                       \
              , allocator_type& allocator                                    \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        static value_type                                                    \
            _construct_value_from(                                           \
                ::std::tr1::true_type                                        \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        static value_type                                                    \
            _construct_value_from(                                           \
                ::std::tr1::false_type                                       \
              , key_type const& key                                          \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_PP_DEC(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
          , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        iterator                                                             \
            _emplace(                                                        \
                ::boost::mpl::true_                                          \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        ::std::pair<iterator,bool>                                           \
            _emplace(                                                        \
                ::boost::mpl::false_                                         \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        iterator _insert(value_type const& value, ::boost::mpl::true_);

        ::std::pair<iterator,bool>
            _insert(value_type const& value, ::boost::mpl::false_);

        void _erase_one(typename node::pointer p);

        size_type _erase(key_type const& key, ::boost::mpl::true_);

        size_type _erase(key_type const& key, ::boost::mpl::false_);

        size_type _size(::boost::mpl::true_) const;

        size_type _size(::boost::mpl::false_) const;
    };

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_reference
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::simple_transform_function::operator()(node const& n) const
    {
        return get(n, data_key());
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::pair_associative_transform_function::const_result
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::pair_associative_transform_function::operator()(node const& n) const
    {
        ::std::pair<T1,T2> const& p = get(n, data_key());
        ::std::pair<T1 const&,T2 const&> result(p.first, p.second);
        return result;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::pair_associative_transform_function::mutable_result
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::pair_associative_transform_function::operator()(node& n) const
    {
        ::std::pair<T1,T2>& p = get(n, data_key());
        ::std::pair<T1 const&,T2&> result(p.first, p.second);
        return result;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::value_compare(key_compare const& c) : _compare(c)
    {
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::value_compare::_evaluate(
            const_reference arg1
          , const_reference arg2
          , ::std::tr1::true_type
        ) const
    {
        return this->_compare(arg1, arg2);
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::value_compare::_evaluate(
            const_reference arg1
          , const_reference arg2
          , ::std::tr1::false_type
        ) const
    {
        return this->_compare(arg1.first, arg2.first);
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::value_compare::operator()(
            const_reference arg1
          , const_reference arg2
        ) const
    {
        return this->_evaluate(arg1, arg2, ::std::tr1::is_void<T2>());
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::value_compare::_evaluate(
            node const& n
          , key_type const& key
          , ::std::tr1::true_type
        ) const
    {
        return this->_compare(get(n, data_key()), key);
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::value_compare::_evaluate(
            node const& n
          , key_type const& key
          , ::std::tr1::false_type
        ) const
    {
        return this->_compare(get(n, data_key()).first, key);
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::value_compare::operator()(node const& n, key_type const& key) const
    {
        return this->_evaluate(n, key, ::std::tr1::is_void<T2>());
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::value_compare::_evaluate(
            key_type const& key
          , node const& n
          , ::std::tr1::true_type
        ) const
    {
        return this->_compare(key, get(n, data_key()));
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::value_compare::_evaluate(
            key_type const& key
          , node const& n
          , ::std::tr1::false_type
        ) const
    {
        return this->_compare(key, get(n, data_key()).first);
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::value_compare::operator()(key_type const& key, node const& n) const
    {
        return this->_evaluate(key, n, ::std::tr1::is_void<T2>());
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::insert_compare::insert_compare(key_compare const& c) : _compare(c)
    {
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::insert_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::insert_compare::_evaluate(
            const_reference value
          , node const& n
          , ::std::tr1::true_type
        ) const
    {
        return this->_compare(value, get(n, data_key()));
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::insert_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::insert_compare::_evaluate(
            const_reference value
          , node const& n
          , ::std::tr1::false_type
        ) const
    {
        return this->_compare(value.first, get(n, data_key()).first);
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::insert_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::insert_compare::operator()(
            const_reference value
          , node const& n
        ) const
    {
        return this->_evaluate(value, n, ::std::tr1::is_void<T2>());
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::insert_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::insert_compare::_evaluate(
            node const& n
          , const_reference value
          , ::std::tr1::true_type
        ) const
    {
        return this->_compare(get(n, data_key()), value);
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::insert_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::insert_compare::_evaluate(
            node const& n
          , const_reference value
          , ::std::tr1::false_type
        ) const
    {
        return this->_compare(get(n, data_key()).first, value.first);
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::insert_compare::result_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::insert_compare::operator()(
            node const& n
          , const_reference value
        ) const
    {
        return this->_evaluate(n, value, ::std::tr1::is_void<T2>());
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::binode_associative_container()
      : _allocator()
      , _root_ptr(
#if defined BOOST_NO_CXX11_NULLPTR
            0
#else
            nullptr
#endif
        )
      , _key_compare()
      , _value_compare(this->_key_compare)
    {
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::binode_associative_container(allocator_type const& allocator)
      : _allocator(allocator)
      , _root_ptr(
#if defined BOOST_NO_CXX11_NULLPTR
            0
#else
            nullptr
#endif
        )
      , _key_compare()
      , _value_compare(this->_key_compare)
    {
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::node::pointer
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_construct_node_from(
            ::std::tr1::true_type
          , allocator_type& allocator
          , typename node::pointer p
        )
    {
        if (p)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typename node::pointer result(allocator.allocate(1));
            allocator.construct(result, *p);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typename node::pointer result(
                ::boost::container::allocator_traits<
                    allocator_type
                >::allocate(allocator, 1)
            );
            ::boost::container::allocator_traits<
                allocator_type
            >::construct(allocator, result, *p);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            return result;
        }
        else
        {
            return p;
        }
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::node::pointer
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_construct_node_from(
            ::std::tr1::false_type
          , allocator_type& allocator
          , typename node::pointer p
        )
    {
        if (p)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typename node::pointer result(allocator.allocate(1));
            allocator.construct(result, *p, allocator);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            typename node::pointer result(
                ::boost::container::allocator_traits<
                    allocator_type
                >::allocate(allocator, 1)
            );
            ::boost::container::allocator_traits<
                allocator_type
            >::construct(allocator, result, *p, allocator);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            return result;
        }
        else
        {
            return p;
        }
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::binode_associative_container(
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        binode_associative_container const& copy
#else
        BOOST_COPY_ASSIGN_REF(binode_associative_container) copy
#endif
    ) : _allocator(copy._allocator)
      , _root_ptr(
            this->_construct_node_from(
                ::std::tr1::is_const<
                    typename ::std::tr1::remove_reference<
                        typename node::traits::allocator_reference
                    >::type
                >()
              , this->_allocator
              , copy._root_ptr
            )
        )
      , _key_compare(copy._key_compare)
      , _value_compare(this->_key_compare)
    {
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::binode_associative_container(
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        binode_associative_container const& copy
#else
        BOOST_COPY_ASSIGN_REF(binode_associative_container) copy
#endif
      , allocator_type const& allocator
    ) : _allocator(allocator)
      , _root_ptr(
            this->_construct_node_from(
                ::std::tr1::is_const<
                    typename ::std::tr1::remove_reference<
                        typename node::traits::allocator_reference
                    >::type
                >()
              , this->_allocator
              , copy._root_ptr
            )
        )
      , _key_compare(copy._key_compare)
      , _value_compare(this->_key_compare)
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::binode_associative_container(
        BOOST_RV_REF(binode_associative_container) source
    ) : _allocator(::boost::move(source._allocator))
      , _root_ptr(source._root_ptr)
      , _key_compare(::boost::move(source._key_compare))
      , _value_compare(this->_key_compare)
    {
#if defined BOOST_NO_CXX11_NULLPTR
        source._root_ptr = 0;
#else
        source._root_ptr = nullptr;
#endif
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::binode_associative_container(
        BOOST_RV_REF(binode_associative_container) source
      , allocator_type const& allocator
    ) : _allocator(allocator)
      , _root_ptr(source._root_ptr)
      , _key_compare(::boost::move(source._key_compare))
      , _value_compare(this->_key_compare)
    {
#if defined BOOST_NO_CXX11_NULLPTR
        source._root_ptr = 0;
#else
        source._root_ptr = nullptr;
#endif
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >&
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::operator=(BOOST_RV_REF(binode_associative_container) source)
    {
        if (this != &static_cast<binode_associative_container&>(source))
        {
            this->_allocator = ::boost::move(source._allocator);
            this->clear();
            this->_root_ptr = source._root_ptr;
#if defined BOOST_NO_CXX11_NULLPTR
            source._root_ptr = 0;
#else
            source._root_ptr = nullptr;
#endif
            this->_key_compare = ::boost::move(source._key_compare);
        }

        return *this;
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >&
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::operator=(
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            binode_associative_container const& copy
#else
            BOOST_COPY_ASSIGN_REF(binode_associative_container) copy
#endif
        )
    {
        if (this != &static_cast<binode_associative_container const&>(copy))
        {
            if (copy._root_ptr)
            {
                if (this->_root_ptr)
                {
                    *this->_root_ptr = *copy._root_ptr;
                }
                else
                {
                    this->_root_ptr = this->_construct_node_from(
                        ::std::tr1::is_const<
                            typename ::std::tr1::remove_reference<
                                typename node::traits::allocator_reference
                            >::type
                        >()
                      , this->_allocator
                      , copy._root_ptr
                    );
                }
            }
            else
            {
                this->clear();
            }

            this->_key_compare = copy._key_compare;
        }

        return *this;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::~binode_associative_container()
    {
        this->clear();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::node::const_pointer
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::data() const
    {
        return this->_root_ptr;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::cbegin() const
    {
        return this->_root_ptr ? const_iterator(
            make_in_order_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->cend();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::begin() const
    {
        return this->_root_ptr ? const_iterator(
            make_in_order_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->end();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::begin()
    {
        return this->_root_ptr ? iterator(
            make_in_order_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->end();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::cend() const
    {
        return const_iterator(
            make_in_order_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::end() const
    {
        return const_iterator(
            make_in_order_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::end()
    {
        return iterator(
            make_in_order_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_reverse_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::crbegin() const
    {
        return this->_root_ptr ? const_reverse_iterator(
            make_in_order_reverse_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->crend();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_reverse_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::rbegin() const
    {
        return this->_root_ptr ? const_reverse_iterator(
            make_in_order_reverse_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->rend();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::reverse_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::rbegin()
    {
        return this->_root_ptr ? reverse_iterator(
            make_in_order_reverse_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->rend();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_reverse_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::crend() const
    {
        return const_reverse_iterator(
            make_in_order_reverse_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_reverse_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::rend() const
    {
        return const_reverse_iterator(
            make_in_order_reverse_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::reverse_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::rend()
    {
        return reverse_iterator(
            make_in_order_reverse_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::find(key_type const& key) const
    {
        typename node::const_pointer node_ptr = this->_root_ptr;

        node_ptr = binary_descendant(node_ptr, key, this->_value_compare);
        return node_ptr ? const_iterator(
            make_in_order_iterator_position(*node_ptr)
          , transform_function()
        ) : this->cend();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::find(key_type const& key)
    {
        typename node::pointer node_ptr = binary_descendant(
            this->_root_ptr
          , key
          , this->_value_compare
        );

        return node_ptr ? iterator(
            make_in_order_iterator_position(*node_ptr)
          , transform_function()
        ) : this->end();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::lower_bound(key_type const& key) const
    {
        typename node::const_pointer node_ptr = this->_root_ptr;

        node_ptr = binary_lower_bound(node_ptr, key, this->_value_compare);
        return node_ptr ? const_iterator(
            make_in_order_iterator_position(*node_ptr)
          , transform_function()
        ) : this->cend();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::lower_bound(key_type const& key)
    {
        typename node::pointer node_ptr = binary_lower_bound(
            this->_root_ptr
          , key
          , this->_value_compare
        );

        return node_ptr ? iterator(
            make_in_order_iterator_position(*node_ptr)
          , transform_function()
        ) : this->end();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::const_iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::upper_bound(key_type const& key) const
    {
        typename node::const_pointer node_ptr = this->_root_ptr;

        node_ptr = binary_upper_bound(node_ptr, key, this->_value_compare);
        return node_ptr ? const_iterator(
            make_in_order_iterator_position(*node_ptr)
          , transform_function()
        ) : this->cend();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::upper_bound(key_type const& key)
    {
        typename node::pointer node_ptr = binary_upper_bound(
            this->_root_ptr
          , key
          , this->_value_compare
        );

        return node_ptr ? iterator(
            make_in_order_iterator_position(*node_ptr)
          , transform_function()
        ) : this->end();
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline ::std::pair<
        typename binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::const_iterator
      , typename binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::const_iterator
    >
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::equal_range(key_type const& key) const
    {
        return ::std::make_pair(
            this->lower_bound(key)
          , this->upper_bound(key)
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline ::std::pair<
        typename binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::iterator
      , typename binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::iterator
    >
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::equal_range(key_type const& key)
    {
        return ::std::make_pair(
            this->lower_bound(key)
          , this->upper_bound(key)
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::node::pointer
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_construct_node_from(
            ::std::tr1::true_type
          , allocator_type& allocator
          , value_type const& value
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename node::pointer result(allocator.allocate(1));
        allocator.construct(result, value);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename node::pointer result(
            ::boost::container::allocator_traits<
                allocator_type
            >::allocate(allocator, 1)
        );
        ::boost::container::allocator_traits<
            allocator_type
        >::construct(allocator, result, value);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        return result;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::node::pointer
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_construct_node_from(
            ::std::tr1::false_type
          , allocator_type& allocator
          , value_type const& value
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename node::pointer result(allocator.allocate(1));
        allocator.construct(
            result
          , ::boost::container::allocator_arg
          , allocator
          , value
        );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename node::pointer result(
            ::boost::container::allocator_traits<
                allocator_type
            >::allocate(allocator, 1)
        );
        ::boost::container::allocator_traits<allocator_type>::construct(
            allocator
          , result
          , ::boost::container::allocator_arg
          , allocator
          , value
        );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        return result;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_insert(value_type const& value, ::boost::mpl::true_)
    {
        if (!this->_root_ptr)
        {
            return iterator(
                make_in_order_iterator(
                    *(
                        this->_root_ptr = this->_construct_node_from(
                            ::std::tr1::is_const<
                                typename ::std::tr1::remove_reference<
                                    typename node::traits::allocator_reference
                                >::type
                            >()
                          , this->_allocator
                          , value
                        )
                    )
                )
              , transform_function()
            );
        }

        typename node::pointer node_ptr = binary_upper_bound(
            this->_root_ptr
          , value
          , insert_compare(this->_key_compare)
        );

        if (node_ptr)
        {
            if (node_ptr->get_left_child_ptr())
            {
                for (
                    node_ptr = node_ptr->get_left_child_ptr();
                    node_ptr->get_right_child_ptr();
                    node_ptr = node_ptr->get_right_child_ptr()
                )
                {
                }

                node_ptr = &*node_ptr->emplace_right(value);
            }
            else
            {
                node_ptr = &*node_ptr->emplace_left(value);
            }
        }
        else  // if (!node_ptr)
        {
            for (
                node_ptr = this->_root_ptr;
                node_ptr->get_right_child_ptr();
                node_ptr = node_ptr->get_right_child_ptr()
            )
            {
            }

            node_ptr = &*node_ptr->emplace_right(value);
        }

        node_ptr = Balancer::post_insert(node_ptr);

        if (!node_ptr->get_parent_ptr())
        {
            this->_root_ptr = node_ptr;
        }

        return iterator(
            make_in_order_iterator_position(*node_ptr)
          , transform_function()
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    ::std::pair<
        typename binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::iterator
      , bool
    >
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_insert(value_type const& value, ::boost::mpl::false_)
    {
        if (!this->_root_ptr)
        {
            return ::std::make_pair(
                iterator(
                    make_in_order_iterator(
                        *(
                            this->_root_ptr = this->_construct_node_from(
                                ::std::tr1::is_const<
                                  typename ::std::tr1::remove_reference<
                                    typename node::traits::allocator_reference
                                  >::type
                                >()
                              , this->_allocator
                              , value
                            )
                        )
                    )
                  , transform_function()
                )
              , true
            );
        }

        insert_compare compare(this->_key_compare);
        typename node::pointer p = this->_root_ptr;

        for (;;)
        {
            if (compare(value, *p))
            {
                if (p->get_left_child_ptr())
                {
                    p = p->get_left_child_ptr();
                }
                else
                {
                    typename node::pointer n = Balancer::post_insert(
                        p = &*p->emplace_left(value)
                    );

                    if (!n->get_parent_ptr())
                    {
                        this->_root_ptr = n;
                    }

                    return ::std::make_pair(
                        iterator(
                            make_in_order_iterator_position(*p)
                          , transform_function()
                        )
                      , true
                    );
                }
            }
            else if (compare(*p, value))
            {
                if (p->get_right_child_ptr())
                {
                    p = p->get_right_child_ptr();
                }
                else
                {
                    typename node::pointer n = Balancer::post_insert(
                        p = &*p->emplace_right(value)
                    );

                    if (!n->get_parent_ptr())
                    {
                        this->_root_ptr = n;
                    }

                    return ::std::make_pair(
                        iterator(
                            make_in_order_iterator_position(*p)
                          , transform_function()
                        )
                      , true
                    );
                }
            }
            else
            {
                break;
            }
        }

        return ::std::make_pair(
            iterator(
                make_in_order_iterator_position(*p)
              , transform_function()
            )
          , false
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename ::boost::mpl::if_<
        IsMultipleAssociative
      , typename binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::iterator
      , ::std::pair<
            typename binode_associative_container<
                NodeGenerator
              , T1
              , T2
              , IsMultipleAssociative
              , CompareSelector
              , Balancer
            >::iterator
          , bool
        >
    >::type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::insert(value_type const& value)
    {
        return this->_insert(value, IsMultipleAssociative());
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    template <typename ...Args>
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::node::pointer
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_construct_node_from(
            ::std::tr1::true_type
          , allocator_type& allocator
          , Args&& ...args
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename node::pointer result(allocator.allocate(1));
        allocator.construct(result, ::boost::forward<Args>(args)...);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename node::pointer result(
            ::boost::container::allocator_traits<
                allocator_type
            >::allocate(allocator, 1)
        );
        ::boost::container::allocator_traits<
            allocator_type
        >::construct(allocator, result, ::boost::forward<Args>(args)...);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        return result;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    template <typename ...Args>
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::node::pointer
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_construct_node_from(
            ::std::tr1::false_type
          , allocator_type& allocator
          , Args&& ...args
        )
    {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename node::pointer result(allocator.allocate(1));
        allocator.construct(
            result
          , ::boost::container::allocator_arg
          , allocator
          , ::boost::forward<Args>(args)...
        );
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        typename node::pointer result(
            ::boost::container::allocator_traits<
                allocator_type
            >::allocate(allocator, 1)
        );
        ::boost::container::allocator_traits<allocator_type>::construct(
            allocator
          , result
          , ::boost::container::allocator_arg
          , allocator
          , ::boost::forward<Args>(args)...
        );
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        return result;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    template <typename ...Args>
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_construct_value_from(
            ::std::tr1::true_type
          , Args&& ...args
        )
    {
        return value_type(::boost::forward<Args>(args)...);
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    template <typename ...Args>
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::value_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_construct_value_from(
            ::std::tr1::false_type
          , key_type const& key
          , Args&& ...args
        )
    {
        return value_type(key, T2(::boost::forward<Args>(args)...));
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    template <typename ...Args>
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::iterator
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_emplace(::boost::mpl::true_, Args&& ...args)
    {
        if (!this->_root_ptr)
        {
            return iterator(
                make_in_order_iterator(
                    *(
                        this->_root_ptr = this->_construct_node_from(
                            ::std::tr1::is_const<
                                typename ::std::tr1::remove_reference<
                                    typename node::traits::allocator_reference
                                >::type
                            >()
                          , this->_allocator
                          , ::boost::forward<Args>(args)...
                        )
                    )
                )
              , transform_function()
            );
        }

        typename node::pointer node_ptr = binary_upper_bound(
            this->_root_ptr
          , this->_construct_value_from(
                ::std::tr1::is_void<T2>()
              , ::boost::forward<Args>(args)...
            )
          , insert_compare(this->_key_compare)
        );

        if (node_ptr)
        {
            if (node_ptr->get_left_child_ptr())
            {
                for (
                    node_ptr = node_ptr->get_left_child_ptr();
                    node_ptr->get_right_child_ptr();
                    node_ptr = node_ptr->get_right_child_ptr()
                )
                {
                }

                node_ptr = &*node_ptr->emplace_right(
                    ::boost::forward<Args>(args)...
                );
            }
            else
            {
                node_ptr = &*node_ptr->emplace_left(
                    ::boost::forward<Args>(args)...
                );
            }
        }
        else  // if (!node_ptr)
        {
            for (
                node_ptr = this->_root_ptr;
                node_ptr->get_right_child_ptr();
                node_ptr = node_ptr->get_right_child_ptr()
            )
            {
            }

            node_ptr = &*node_ptr->emplace_right(
                ::boost::forward<Args>(args)...
            );
        }

        typename node::pointer anc_ptr = Balancer::post_insert(node_ptr);

        if (!anc_ptr->get_parent_ptr())
        {
            this->_root_ptr = anc_ptr;
        }

        return iterator(
            make_in_order_iterator_position(*node_ptr)
          , transform_function()
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    template <typename ...Args>
    ::std::pair<
        typename binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::iterator
      , bool
    >
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_emplace(::boost::mpl::false_, Args&& ...args)
    {
        if (!this->_root_ptr)
        {
            return ::std::make_pair(
                iterator(
                    make_in_order_iterator(
                        *(
                            this->_root_ptr = this->_construct_node_from(
                                ::std::tr1::is_const<
                                  typename ::std::tr1::remove_reference<
                                    typename node::traits::allocator_reference
                                  >::type
                                >()
                              , this->_allocator
                              , ::boost::forward<Args>(args)...
                            )
                        )
                    )
                  , transform_function()
                )
              , true
            );
        }

        value_type value(
            this->_construct_value_from(
                ::std::tr1::is_void<T2>()
              , ::boost::forward<Args>(args)...
            )
        );
        insert_compare compare(this->_key_compare);
        typename node::pointer p = this->_root_ptr;

        for (;;)
        {
            if (compare(value, *p))
            {
                if (p->get_left_child_ptr())
                {
                    p = p->get_left_child_ptr();
                }
                else
                {
                    typename node::pointer n = Balancer::post_insert(
                        p = &*p->emplace_left(::boost::forward<Args>(args)...)
                    );

                    if (!n->get_parent_ptr())
                    {
                        this->_root_ptr = n;
                    }

                    return ::std::make_pair(
                        iterator(
                            make_in_order_iterator_position(*p)
                          , transform_function()
                        )
                      , true
                    );
                }
            }
            else if (compare(*p, value))
            {
                if (p->get_right_child_ptr())
                {
                    p = p->get_right_child_ptr();
                }
                else
                {
                    typename node::pointer n = Balancer::post_insert(
                        p = &*p->emplace_right(::boost::forward<Args>(args)...)
                    );

                    if (!n->get_parent_ptr())
                    {
                        this->_root_ptr = n;
                    }

                    return ::std::make_pair(
                        iterator(
                            make_in_order_iterator_position(*p)
                          , transform_function()
                        )
                      , true
                    );
                }
            }
            else
            {
                break;
            }
        }

        return ::std::make_pair(
            iterator(
                make_in_order_iterator_position(*p)
              , transform_function()
            )
          , false
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    template <typename ...Args>
    inline typename ::boost::mpl::if_<
        IsMultipleAssociative
      , typename binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::iterator
      , ::std::pair<
            typename binode_associative_container<
                NodeGenerator
              , T1
              , T2
              , IsMultipleAssociative
              , CompareSelector
              , Balancer
            >::iterator
          , bool
        >
    >::type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::emplace(Args&& ...args)
    {
        return this->_emplace(
            IsMultipleAssociative()
          , ::boost::forward<Args>(args)...
        );
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
    template <                                                               \
        typename NodeGenerator                                               \
      , typename T1                                                          \
      , typename T2                                                          \
      , typename IsMultipleAssociative                                       \
      , typename CompareSelector                                             \
      , typename Balancer                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_associative_container<                                   \
        NodeGenerator                                                        \
      , T1                                                                   \
      , T2                                                                   \
      , IsMultipleAssociative                                                \
      , CompareSelector                                                      \
      , Balancer                                                             \
    >::node::pointer                                                         \
        binode_associative_container<                                        \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::_construct_node_from(                                             \
            ::std::tr1::true_type                                            \
          , allocator_type& allocator                                        \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        typename node::pointer result(allocator.allocate(1));                \
        allocator.construct(                                                 \
            result                                                           \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        );                                                                   \
        return result;                                                       \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
    template <                                                               \
        typename NodeGenerator                                               \
      , typename T1                                                          \
      , typename T2                                                          \
      , typename IsMultipleAssociative                                       \
      , typename CompareSelector                                             \
      , typename Balancer                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_associative_container<                                   \
        NodeGenerator                                                        \
      , T1                                                                   \
      , T2                                                                   \
      , IsMultipleAssociative                                                \
      , CompareSelector                                                      \
      , Balancer                                                             \
    >::node::pointer                                                         \
        binode_associative_container<                                        \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::_construct_node_from(                                             \
            ::std::tr1::false_type                                           \
          , allocator_type& allocator                                        \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        typename node::pointer result(allocator.allocate(1));                \
        allocator.construct(                                                 \
            result                                                           \
          , ::boost::container::allocator_arg                                \
          , allocator                                                        \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        );                                                                   \
        return result;                                                       \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
    template <                                                               \
        typename NodeGenerator                                               \
      , typename T1                                                          \
      , typename T2                                                          \
      , typename IsMultipleAssociative                                       \
      , typename CompareSelector                                             \
      , typename Balancer                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_associative_container<                                   \
        NodeGenerator                                                        \
      , T1                                                                   \
      , T2                                                                   \
      , IsMultipleAssociative                                                \
      , CompareSelector                                                      \
      , Balancer                                                             \
    >::node::pointer                                                         \
        binode_associative_container<                                        \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::_construct_node_from(                                             \
            ::std::tr1::true_type                                            \
          , allocator_type& allocator                                        \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        typename node::pointer result(                                       \
            ::boost::container::allocator_traits<                            \
                allocator_type                                               \
            >::allocate(allocator, 1)                                        \
        );                                                                   \
        ::boost::container::allocator_traits<allocator_type>::construct(     \
            allocator                                                        \
          , result                                                           \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        );                                                                   \
        return result;                                                       \
     }                                                                       \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
    template <                                                               \
        typename NodeGenerator                                               \
      , typename T1                                                          \
      , typename T2                                                          \
      , typename IsMultipleAssociative                                       \
      , typename CompareSelector                                             \
      , typename Balancer                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_associative_container<                                   \
        NodeGenerator                                                        \
      , T1                                                                   \
      , T2                                                                   \
      , IsMultipleAssociative                                                \
      , CompareSelector                                                      \
      , Balancer                                                             \
    >::node::pointer                                                         \
        binode_associative_container<                                        \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::_construct_node_from(                                             \
            ::std::tr1::false_type                                           \
          , allocator_type& allocator                                        \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        typename node::pointer result(                                       \
            ::boost::container::allocator_traits<                            \
                allocator_type                                               \
            >::allocate(allocator, 1)                                        \
        );                                                                   \
        ::boost::container::allocator_traits<allocator_type>::construct(     \
            allocator                                                        \
          , result                                                           \
          , ::boost::container::allocator_arg                                \
          , allocator                                                        \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        );                                                                   \
        return result;                                                       \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
    template <                                                               \
        typename NodeGenerator                                               \
      , typename T1                                                          \
      , typename T2                                                          \
      , typename IsMultipleAssociative                                       \
      , typename CompareSelector                                             \
      , typename Balancer                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    inline typename binode_associative_container<                            \
        NodeGenerator                                                        \
      , T1                                                                   \
      , T2                                                                   \
      , IsMultipleAssociative                                                \
      , CompareSelector                                                      \
      , Balancer                                                             \
    >::value_type                                                            \
        binode_associative_container<                                        \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::_construct_value_from(                                            \
            ::std::tr1::true_type                                            \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        return value_type(                                                   \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        );                                                                   \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
    template <                                                               \
        typename NodeGenerator                                               \
      , typename T1                                                          \
      , typename T2                                                          \
      , typename IsMultipleAssociative                                       \
      , typename CompareSelector                                             \
      , typename Balancer                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    inline typename binode_associative_container<                            \
        NodeGenerator                                                        \
      , T1                                                                   \
      , T2                                                                   \
      , IsMultipleAssociative                                                \
      , CompareSelector                                                      \
      , Balancer                                                             \
    >::value_type                                                            \
        binode_associative_container<                                        \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::_construct_value_from(                                            \
            ::std::tr1::false_type                                           \
          , key_type const& key                                              \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        return value_type(                                                   \
            key                                                              \
          , T2(                                                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            )                                                                \
        );                                                                   \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_PP_DEC(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
      , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
    template <                                                               \
        typename NodeGenerator                                               \
      , typename T1                                                          \
      , typename T2                                                          \
      , typename IsMultipleAssociative                                       \
      , typename CompareSelector                                             \
      , typename Balancer                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_associative_container<                                   \
        NodeGenerator                                                        \
      , T1                                                                   \
      , T2                                                                   \
      , IsMultipleAssociative                                                \
      , CompareSelector                                                      \
      , Balancer                                                             \
    >::iterator                                                              \
        binode_associative_container<                                        \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::_emplace(                                                         \
            ::boost::mpl::true_                                              \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (!this->_root_ptr)                                                \
        {                                                                    \
            return iterator(                                                 \
                make_in_order_iterator(                                      \
                    *(                                                       \
                        this->_root_ptr = this->_construct_node_from(        \
                            ::std::tr1::is_const<                            \
                              typename ::std::tr1::remove_reference<         \
                                typename node::traits::allocator_reference   \
                              >::type                                        \
                            >()                                              \
                          , this->_allocator                                 \
                            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(        \
                                n                                            \
                               , BOOST_CONTAINER_PP_PARAM_FORWARD            \
                              , _                                            \
                            )                                                \
                        )                                                    \
                    )                                                        \
                )                                                            \
              , transform_function()                                         \
            );                                                               \
        }                                                                    \
        typename node::pointer node_ptr = binary_upper_bound(                \
            this->_root_ptr                                                  \
          , this->_construct_value_from(                                     \
                ::std::tr1::is_void<T2>()                                    \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            )                                                                \
          , insert_compare(this->_key_compare)                               \
        );                                                                   \
        if (node_ptr)                                                        \
        {                                                                    \
            if (node_ptr->get_left_child_ptr())                              \
            {                                                                \
                for (                                                        \
                    node_ptr = node_ptr->get_left_child_ptr();               \
                    node_ptr->get_right_child_ptr();                         \
                    node_ptr = node_ptr->get_right_child_ptr()               \
                )                                                            \
                {                                                            \
                }                                                            \
                node_ptr = &*node_ptr->emplace_right(                        \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , _                                                    \
                    )                                                        \
                );                                                           \
            }                                                                \
            else                                                             \
            {                                                                \
                node_ptr = &*node_ptr->emplace_left(                         \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , _                                                    \
                    )                                                        \
                );                                                           \
            }                                                                \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            for (                                                            \
                node_ptr = this->_root_ptr;                                  \
                node_ptr->get_right_child_ptr();                             \
                node_ptr = node_ptr->get_right_child_ptr()                   \
            )                                                                \
            {                                                                \
            }                                                                \
            node_ptr = &*node_ptr->emplace_right(                            \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
        node_ptr = Balancer::post_insert(node_ptr);                          \
        if (!node_ptr->get_parent_ptr())                                     \
        {                                                                    \
            this->_root_ptr = node_ptr;                                      \
        }                                                                    \
        return iterator(                                                     \
            make_in_order_iterator_position(*node_ptr)                       \
          , transform_function()                                             \
        );                                                                   \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
    template <                                                               \
        typename NodeGenerator                                               \
      , typename T1                                                          \
      , typename T2                                                          \
      , typename IsMultipleAssociative                                       \
      , typename CompareSelector                                             \
      , typename Balancer                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    ::std::pair<                                                             \
        typename binode_associative_container<                               \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::iterator                                                          \
      , bool                                                                 \
    >                                                                        \
        binode_associative_container<                                        \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::_emplace(                                                         \
            ::boost::mpl::false_                                             \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (!this->_root_ptr)                                                \
        {                                                                    \
            return ::std::make_pair(                                         \
                iterator(                                                    \
                    make_in_order_iterator(                                  \
                        *(                                                   \
                            this->_root_ptr = this->_construct_node_from(    \
                                ::std::tr1::is_const<                        \
                                  typename ::std::tr1::remove_reference<     \
                                typename node::traits::allocator_reference   \
                                  >::type                                    \
                                >()                                          \
                              , this->_allocator                             \
                                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(    \
                                    n                                        \
                                   , BOOST_CONTAINER_PP_PARAM_FORWARD        \
                                  , _                                        \
                                )                                            \
                            )                                                \
                        )                                                    \
                    )                                                        \
                  , transform_function()                                     \
                )                                                            \
              , true                                                         \
            );                                                               \
        }                                                                    \
        value_type value(                                                    \
            this->_construct_value_from(                                     \
                ::std::tr1::is_void<T2>()                                    \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            )                                                                \
        );                                                                   \
        insert_compare compare(this->_key_compare);                          \
        typename node::pointer p = this->_root_ptr;                          \
        for (;;)                                                             \
        {                                                                    \
            if (compare(value, *p))                                          \
            {                                                                \
                if (p->get_left_child_ptr())                                 \
                {                                                            \
                    p = p->get_left_child_ptr();                             \
                }                                                            \
                else                                                         \
                {                                                            \
                    typename node::pointer n = Balancer::post_insert(        \
                        p = &*p->emplace_left(                               \
                            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                 \
                                n                                            \
                              , BOOST_CONTAINER_PP_PARAM_FORWARD             \
                              , _                                            \
                            )                                                \
                        )                                                    \
                    );                                                       \
                    if (!n->get_parent_ptr())                                \
                    {                                                        \
                        this->_root_ptr = n;                                 \
                    }                                                        \
                    return ::std::make_pair(                                 \
                        iterator(                                            \
                            make_in_order_iterator_position(*p)              \
                          , transform_function()                             \
                        )                                                    \
                      , true                                                 \
                    );                                                       \
                }                                                            \
            }                                                                \
            else if (compare(*p, value))                                     \
            {                                                                \
                if (p->get_right_child_ptr())                                \
                {                                                            \
                    p = p->get_right_child_ptr();                            \
                }                                                            \
                else                                                         \
                {                                                            \
                    typename node::pointer n = Balancer::post_insert(        \
                        p = &*p->emplace_right(                              \
                            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                 \
                                n                                            \
                              , BOOST_CONTAINER_PP_PARAM_FORWARD             \
                              , _                                            \
                            )                                                \
                        )                                                    \
                    );                                                       \
                    if (!n->get_parent_ptr())                                \
                    {                                                        \
                        this->_root_ptr = n;                                 \
                    }                                                        \
                    return ::std::make_pair(                                 \
                        iterator(                                            \
                            make_in_order_iterator_position(*p)              \
                          , transform_function()                             \
                        )                                                    \
                      , true                                                 \
                    );                                                       \
                }                                                            \
            }                                                                \
            else                                                             \
            {                                                                \
                break;                                                       \
            }                                                                \
        }                                                                    \
        return ::std::make_pair(                                             \
            iterator(                                                        \
                make_in_order_iterator_position(*p)                          \
              , transform_function()                                         \
            )                                                                \
          , false                                                            \
        );                                                                   \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO(z, n, _)          \
    template <                                                               \
        typename NodeGenerator                                               \
      , typename T1                                                          \
      , typename T2                                                          \
      , typename IsMultipleAssociative                                       \
      , typename CompareSelector                                             \
      , typename Balancer                                                    \
    >                                                                        \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    inline typename ::boost::mpl::if_<                                       \
        IsMultipleAssociative                                                \
      , typename binode_associative_container<                               \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::iterator                                                          \
      , ::std::pair<                                                         \
            typename binode_associative_container<                           \
                NodeGenerator                                                \
              , T1                                                           \
              , T2                                                           \
              , IsMultipleAssociative                                        \
              , CompareSelector                                              \
              , Balancer                                                     \
            >::iterator                                                      \
          , bool                                                             \
        >                                                                    \
    >::type                                                                  \
        binode_associative_container<                                        \
            NodeGenerator                                                    \
          , T1                                                               \
          , T2                                                               \
          , IsMultipleAssociative                                            \
          , CompareSelector                                                  \
          , Balancer                                                         \
        >::emplace(                                                          \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        return this->_emplace(                                               \
            IsMultipleAssociative()                                          \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        );                                                                   \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_ASSOCIATIVE_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    void
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_erase_one(typename node::pointer p)
    {
        for (typename node::pointer s;;)
        {
            if (
                (s = p->get_left_child_ptr()) && (
                    !p->get_right_child_ptr() || Balancer::choose_predecessor(
                        *typename node::const_pointer(p)
                    )
                )
            )
            {
                while (s->get_right_child_ptr())
                {
                    s = s->get_right_child_ptr();
                }

                if (s->get_parent_ptr() == p)
                {
                    if (!p->get_right_child_ptr())
                    {
                        put(*p, data_key(), get(*s, data_key()));

                        bool must_rebalance = Balancer::pre_erase(*s);

                        p->erase_left();

                        if (must_rebalance)
                        {
                            p = Balancer::post_erase_left(p);

                            if (!p->get_parent_ptr())
                            {
                                this->_root_ptr = p;
                            }
                        }

                        break;
                    }
                }
                else  // if (s == s->get_parent_ptr()->get_right_child_ptr())
                {
                    put(*p, data_key(), get(*s, data_key()));

                    if (s->get_left_child_ptr())
                    {
                        p = s;
                    }
                    else  // if (s->empty())
                    {
                        p = s->get_parent_ptr();

                        if (p->get_left_child_ptr())
                        {
                            put(*s, data_key(), get(*p, data_key()));
                        }
                        else  // s is only child of p
                        {
                            bool must_rebalance = Balancer::pre_erase(*s);

                            p->erase_right();

                            if (must_rebalance)
                            {
                                p = Balancer::post_erase_right(p);

                                if (!p->get_parent_ptr())
                                {
                                    this->_root_ptr = p;
                                }
                            }

                            break;
                        }
                    }

                    continue;
                }
            }

            if ((s = p->get_right_child_ptr()))
            {
                while (s->get_left_child_ptr())
                {
                    s = s->get_left_child_ptr();
                }

                put(*p, data_key(), get(*s, data_key()));

                if (s->get_right_child_ptr())
                {
                    p = s;
                }
                else if (s->get_parent_ptr() == p)
                {
                    bool must_rebalance = Balancer::pre_erase(*s);

                    p->erase_right();

                    if (must_rebalance)
                    {
                        p = Balancer::post_erase_right(p);

                        if (!p->get_parent_ptr())
                        {
                            this->_root_ptr = p;
                        }
                    }

                    break;
                }
                else
                {
                    BOOST_ASSERT(s->empty());
                    p = s->get_parent_ptr();
                    BOOST_ASSERT(p->get_left_child_ptr() == s);

                    if (p->get_right_child_ptr())
                    {
                        put(*s, data_key(), get(*p, data_key()));
                    }
                    else  // s is only child of p
                    {
                        bool must_rebalance = Balancer::pre_erase(*s);

                        p->erase_left();

                        if (must_rebalance)
                        {
                            p = Balancer::post_erase_left(p);

                            if (!p->get_parent_ptr())
                            {
                                this->_root_ptr = p;
                            }
                        }

                        break;
                    }
                }
            }
            else  // if (p->empty())
            {
                s = p;
                p = p->get_parent_ptr();

                bool must_rebalance = Balancer::pre_erase(*s);

                if (p->get_left_child_ptr() == s)
                {
                    p->erase_left();

                    if (must_rebalance)
                    {
                        p = Balancer::post_erase_left(p);

                        if (!p->get_parent_ptr())
                        {
                            this->_root_ptr = p;
                        }
                    }
                }
                else  // if (p->get_right_child_ptr() == s)
                {
                    p->erase_right();

                    if (must_rebalance)
                    {
                        p = Balancer::post_erase_right(p);

                        if (!p->get_parent_ptr())
                        {
                            this->_root_ptr = p;
                        }
                    }
                }

                break;
            }
        }
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::size_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_erase(key_type const& key, ::boost::mpl::true_)
    {
        size_type result = ::boost::initialized_value;

        for (
            typename node::pointer p;
            (
                p = binary_descendant(
                    this->_root_ptr
                  , key
                  , this->_value_compare
                )
            );
            ++result
        )
        {
            this->_erase_one(p);
        }

        return result;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::size_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_erase(key_type const& key, ::boost::mpl::false_)
    {
        this->_erase_one(
            binary_descendant(
                this->_root_ptr
              , key
              , this->_value_compare
            )
        );
        return 1;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::size_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::erase(key_type const& key)
    {
        if (this->_root_ptr)
        {
            if (this->_root_ptr->empty())
            {
                this->clear();
                return 1;
            }
            else
            {
                return this->_erase(key, IsMultipleAssociative());
            }
        }
        else
        {
            return 0;
        }
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline bool
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::empty() const
    {
        return !this->_root_ptr;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    void
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::clear()
    {
        if (this->_root_ptr)
        {
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            this->_allocator.destroy(this->_root_ptr);
            this->_allocator.deallocate(this->_root_ptr, 1);
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            ::boost::container::allocator_traits<
                allocator_type
            >::destroy(this->_allocator, this->_root_ptr);
            ::boost::container::allocator_traits<
                allocator_type
            >::deallocate(this->_allocator, this->_root_ptr, 1);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_NO_CXX11_NULLPTR
            this->_root_ptr = 0;
#else
            this->_root_ptr = nullptr;
#endif
        }
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::size_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_size(::boost::mpl::true_) const
    {
        return this->_root_ptr ? get(*this->_root_ptr, count_key()) : 0;
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::size_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::_size(::boost::mpl::false_) const
    {
        return ::std::distance(this->cbegin(), this->cend());
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::size_type
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::size() const
    {
        return this->_size(result_of::has_key<node,count_key>());
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::transform_function::const_result
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::operator[](size_type const& index) const
    {
        BOOST_ASSERT_MSG(
            this->_root_ptr && (index < this->size())
          , "index out of bounds"
        );

        typename node::const_pointer node_ptr = this->_root_ptr;

        return transform_function()(
            *binary_descendant_at_index(node_ptr, index)
        );
    }

    template <
        typename NodeGenerator
      , typename T1
      , typename T2
      , typename IsMultipleAssociative
      , typename CompareSelector
      , typename Balancer
    >
    inline typename binode_associative_container<
        NodeGenerator
      , T1
      , T2
      , IsMultipleAssociative
      , CompareSelector
      , Balancer
    >::transform_function::mutable_result
        binode_associative_container<
            NodeGenerator
          , T1
          , T2
          , IsMultipleAssociative
          , CompareSelector
          , Balancer
        >::operator[](size_type const& index)
    {
        BOOST_ASSERT_MSG(
            this->_root_ptr && (index < this->size())
          , "index out of bounds"
        );

        return transform_function()(
            *binary_descendant_at_index(this->_root_ptr, index)
        );
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <
        typename T
      , typename NodeGenerator
      , typename Balancer
      , typename CompareSelector
    >
    class binode_set
      : public
        //[reference__binode_set__bases
        binode_associative_container<
            NodeGenerator
          , T
          , void
          , ::boost::mpl::false_
          , CompareSelector
          , Balancer
        >
        //]
    {
        typedef binode_associative_container<
                    NodeGenerator
                  , T
                  , void
                  , ::boost::mpl::false_
                  , CompareSelector
                  , Balancer
                >
                super_t;

     public:
        BOOST_TREE_NODE_ASSOCIATIVE_CONTAINER_DERIVED_BODY(binode_set, super_t)
    };
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <
        typename T
      , typename NodeGenerator
      , typename Balancer
      , typename CompareSelector
    >
    class binode_multiset
      : public
        //[reference__binode_multiset__bases
        binode_associative_container<
            NodeGenerator
          , T
          , void
          , ::boost::mpl::true_
          , CompareSelector
          , Balancer
        >
        //]
    {
        typedef binode_associative_container<
                    NodeGenerator
                  , T
                  , void
                  , ::boost::mpl::true_
                  , CompareSelector
                  , Balancer
                >
                super_t;

     public:
        BOOST_TREE_NODE_ASSOCIATIVE_CONTAINER_DERIVED_BODY(
            binode_multiset
          , super_t
        )
    };
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Mapped
      , typename NodeGenerator
      , typename Balancer
      , typename CompareSelector
    >
    class binode_map
      : public
        //[reference__binode_map__bases
        binode_associative_container<
            NodeGenerator
          , Key
          , Mapped
          , ::boost::mpl::false_
          , CompareSelector
          , Balancer
        >
        //]
    {
        typedef binode_associative_container<
                    NodeGenerator
                  , Key
                  , Mapped
                  , ::boost::mpl::false_
                  , CompareSelector
                  , Balancer
                >
                super_t;

     public:
        //[reference__binode_map__mapped_type
        typedef Mapped mapped_type;
        //]

        BOOST_TREE_NODE_ASSOCIATIVE_CONTAINER_DERIVED_BODY(binode_map, super_t)
    };
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Mapped
      , typename NodeGenerator
      , typename Balancer
      , typename CompareSelector
    >
    class binode_multimap
      : public
        //[reference__binode_multimap__bases
        binode_associative_container<
            NodeGenerator
          , Key
          , Mapped
          , ::boost::mpl::true_
          , CompareSelector
          , Balancer
        >
        //]
    {
        typedef binode_associative_container<
                    NodeGenerator
                  , Key
                  , Mapped
                  , ::boost::mpl::true_
                  , CompareSelector
                  , Balancer
                >
                super_t;

     public:
        //[reference__binode_multimap__mapped_type
        typedef Mapped mapped_type;
        //]

        BOOST_TREE_NODE_ASSOCIATIVE_CONTAINER_DERIVED_BODY(
            binode_multimap
          , super_t
        )
    };
}}  // namespace boost::tree_node

#endif  // BOOST_TREE_NODE_CONTAINER_BINODE_ASSOCIATIVE_HPP_INCLUDED

