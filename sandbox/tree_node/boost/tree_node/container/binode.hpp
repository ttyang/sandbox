// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_CONTAINER_BINODE_HPP_INCLUDED
#define BOOST_TREE_NODE_CONTAINER_BINODE_HPP_INCLUDED

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
#include <boost/tree_node/algorithm/binary_descendant_at_index.hpp>
#include <boost/tree_node/container/binode_fwd.hpp>
#include <boost/assert.hpp>

namespace boost { namespace tree_node {

    template <typename T, typename NodeGenerator, typename Balancer>
    class binode_container
    {
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        BOOST_COPYABLE_AND_MOVABLE(binode_container)
#endif

     public:
        //[reference__binode_container__value_type
        typedef T value_type;
        //]

        //[reference__binode_container__reference
        typedef value_type& reference;
        //]

        //[reference__binode_container__const_reference
        typedef value_type const& const_reference;
        //]

        //[reference__binode_container__pointer
        typedef value_type* pointer;
        //]

        //[reference__binode_container__const_pointer
        typedef value_type const* const_pointer;
        //]

        //[reference__binode_container__node
        typedef typename ::boost::mpl::apply_wrap1<
                    NodeGenerator
                  , value_type
                >::type
                node;
        //]

        //[reference__binode_container__allocator_type
        typedef typename node::traits::allocator allocator_type;
        //]

     private:
        //[reference__binode_container__transform_function
        struct transform_function
        {
            const_reference operator()(node const& n) const;
            reference operator()(node& n) const;
        };
        //]

     public:
        //[reference__binode_container__iterator
        typedef ::boost::transform_iterator<
                    transform_function
                  , in_order_iterator<node>
                >
                iterator;
        //]

        //[reference__binode_container__const_iterator
        typedef ::boost::transform_iterator<
                    transform_function
                  , in_order_iterator<node const>
                >
                const_iterator;
        //]

        //[reference__binode_container__reverse_iterator
        typedef ::boost::transform_iterator<
                    transform_function
                  , in_order_iterator<node,::boost::mpl::true_>
                >
                reverse_iterator;
        //]

        //[reference__binode_container__const_reverse_iterator
        typedef ::boost::transform_iterator<
                    transform_function
                  , in_order_iterator<node const,::boost::mpl::true_>
                >
                const_reverse_iterator;
        //]

        //[reference__binode_container__size_type
        typedef typename ::boost::mpl::eval_if<
                    result_of::has_key<node,count_key>
                  , result_of::value_at_key<node,count_key>
                  , typename node::size_type
                >::type
                size_type;
        //]

     private:
        allocator_type _allocator;
        typename node::pointer _root_ptr;

     public:
        //[reference__binode_container__default_ctor
        binode_container();
        //]

        //[reference__binode_container__ctor_w_alloc
        explicit binode_container(allocator_type const& allocator);
        //]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__binode_container__copy_ctor
        binode_container(binode_container const& copy);
        //]
#else
        binode_container(
            BOOST_COPY_ASSIGN_REF(binode_container) copy
        );
#endif

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__binode_container__copy_ctor_w_alloc
        binode_container(
            binode_container const& copy
          , allocator_type const& allocator
        );
        //]
#else
        binode_container(
            BOOST_COPY_ASSIGN_REF(binode_container) copy
          , allocator_type const& allocator
        );
#endif

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        //[reference__binode_container__copy_assign
        binode_container& operator=(binode_container const& copy);
        //]
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        binode_container(
            BOOST_RV_REF(binode_container) source
        );

        binode_container(
            BOOST_RV_REF(binode_container) source
          , allocator_type const& allocator
        );

        binode_container& operator=(BOOST_RV_REF(binode_container) source);

        binode_container&
            operator=(BOOST_COPY_ASSIGN_REF(binode_container) copy);
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

        //[reference__binode_container__dtor
        ~binode_container();
        //]

        //[reference__binode_container__data__const
        typename node::const_pointer data() const;
        //]

        //[reference__binode_container__data
        typename node::pointer data();
        //]

        //[reference__binode_container__cbegin
        const_iterator cbegin() const;
        const_iterator begin() const;
        //]

        //[reference__binode_container__begin
        iterator begin();
        //]

        //[reference__binode_container__cend
        const_iterator cend() const;
        const_iterator end() const;
        //]

        //[reference__binode_container__end
        iterator end();
        //]

        //[reference__binode_container__crbegin
        const_reverse_iterator crbegin() const;
        const_reverse_iterator rbegin() const;
        //]

        //[reference__binode_container__rbegin
        reverse_iterator rbegin();
        //]

        //[reference__binode_container__crend
        const_reverse_iterator crend() const;
        const_reverse_iterator rend() const;
        //]

        //[reference__binode_container__rend
        reverse_iterator rend();
        //]

        //[reference__binode_container__cback
        const_reference back() const;
        //]

        //[reference__binode_container__back
        reference back();
        //]

        //[reference__binode_container__push_back
        void push_back(const_reference t);
        //]

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binode_container__emplace_back
        template <typename ...Args>
        void emplace_back(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        void                                                                 \
            emplace_back(                                                    \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        //[reference__binode_container__pop_back
        void pop_back();
        //]

        //[reference__binode_container__cfront
        const_reference front() const;
        //]

        //[reference__binode_container__front
        reference front();
        //]

        //[reference__binode_container__push_front
        void push_front(const_reference t);
        //]

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binode_container__emplace_front
        template <typename ...Args>
        void emplace_front(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        void                                                                 \
            emplace_front(                                                   \
                BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                             \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        //[reference__binode_container__pop_front
        void pop_front();
        //]

        //[reference__binode_container__insert
        iterator insert(const_iterator itr, const_reference t);
        //]

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__binode_container__emplace
        template <typename ...Args>
        iterator emplace(const_iterator itr, Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        iterator                                                             \
            emplace(                                                         \
                const_iterator itr                                           \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_LIST                            \
                  , _                                                        \
                )                                                            \
            );                                                               \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        //[reference__binode_container__erase
        iterator erase(const_iterator p);
        //]

        //[reference__binode_container__erase_range
        void erase(const_iterator itr, const_iterator itr_end);
        //]

        //[reference__binode_container__empty
        bool empty() const;
        //]

        //[reference__binode_container__clear
        void clear();
        //]

        //[reference__binode_container__size
        size_type size() const;
        //]

        //[reference__binode_container__index_operator__const
        const_reference operator[](size_type index) const;
        //]

        //[reference__binode_container__index_operator
        reference operator[](size_type index);
        //]

     private:
        static typename node::pointer
            _construct_from(
                ::std::tr1::true_type
              , allocator_type& allocator
              , value_type const& value
            );

        static typename node::pointer
            _construct_from(
                ::std::tr1::false_type
              , allocator_type& allocator
              , value_type const& value
            );

        static typename node::pointer
            _construct_from(
                ::std::tr1::true_type
              , allocator_type& allocator
              , typename node::pointer p
            );

        static typename node::pointer
            _construct_from(
                ::std::tr1::false_type
              , allocator_type& allocator
              , typename node::pointer p
            );

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        template <typename ...Args>
        static typename node::pointer
            _construct_from(
                ::std::tr1::true_type
              , allocator_type& allocator
              , Args&& ...args
            );

        template <typename ...Args>
        static typename node::pointer
            _construct_from(
                ::std::tr1::false_type
              , allocator_type& allocator
              , Args&& ...args
            );
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        static typename node::pointer                                        \
            _construct_from(                                                 \
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
          , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        static typename node::pointer                                        \
            _construct_from(                                                 \
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
          , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
          , _
        )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        size_type _size(::boost::mpl::true_) const;

        size_type _size(::boost::mpl::false_) const;

        typename node::const_pointer _back() const;

        typename node::pointer _back();
    };

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::const_reference
        binode_container<
            T
          , NodeGenerator
          , Balancer
        >::transform_function::operator()(node const& n) const
    {
        return get(n, data_key());
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::reference
        binode_container<
            T
          , NodeGenerator
          , Balancer
        >::transform_function::operator()(node& n) const
    {
        return get(n, data_key());
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    binode_container<T,NodeGenerator,Balancer>::binode_container()
      : _allocator()
      , _root_ptr(
#if defined BOOST_NO_CXX11_NULLPTR
            0
#else
            nullptr
#endif
        )
    {
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    binode_container<T,NodeGenerator,Balancer>::binode_container(
        allocator_type const& allocator
    ) : _allocator(allocator)
      , _root_ptr(
#if defined BOOST_NO_CXX11_NULLPTR
            0
#else
            nullptr
#endif
        )
    {
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer
        binode_container<T,NodeGenerator,Balancer>::_construct_from(
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

    template <typename T, typename NodeGenerator, typename Balancer>
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer
        binode_container<T,NodeGenerator,Balancer>::_construct_from(
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

    template <typename T, typename NodeGenerator, typename Balancer>
    binode_container<T,NodeGenerator,Balancer>::binode_container(
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        binode_container const& copy
#else
        BOOST_COPY_ASSIGN_REF(binode_container) copy
#endif
    ) : _allocator(copy._allocator)
      , _root_ptr(
            this->_construct_from(
                ::std::tr1::is_const<
                    typename ::std::tr1::remove_reference<
                        typename node::traits::allocator_reference
                    >::type
                >()
              , this->_allocator
              , copy._root_ptr
            )
        )
    {
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    binode_container<T,NodeGenerator,Balancer>::binode_container(
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        binode_container const& copy
#else
        BOOST_COPY_ASSIGN_REF(binode_container) copy
#endif
      , allocator_type const& allocator
    ) : _allocator(copy._allocator)
      , _root_ptr(
            this->_construct_from(
                ::std::tr1::is_const<
                    typename ::std::tr1::remove_reference<
                        typename node::traits::allocator_reference
                    >::type
                >()
              , this->_allocator
              , copy._root_ptr
            )
        )
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <typename T, typename NodeGenerator, typename Balancer>
    binode_container<T,NodeGenerator,Balancer>::binode_container(
        BOOST_RV_REF(binode_container) source
    ) : _allocator(::boost::move(source._allocator))
      , _root_ptr(source._root_ptr)
    {
#if defined BOOST_NO_CXX11_NULLPTR
        source._root_ptr = 0;
#else
        source._root_ptr = nullptr;
#endif
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    binode_container<T,NodeGenerator,Balancer>::binode_container(
        BOOST_RV_REF(binode_container) source
      , allocator_type const& allocator
    ) : _allocator(allocator), _root_ptr(source._root_ptr)
    {
#if defined BOOST_NO_CXX11_NULLPTR
        source._root_ptr = 0;
#else
        source._root_ptr = nullptr;
#endif
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline binode_container<T,NodeGenerator,Balancer>&
        binode_container<T,NodeGenerator,Balancer>::operator=(
            BOOST_RV_REF(binode_container) source
        )
    {
        if (this != &static_cast<binode_container&>(source))
        {
            this->_allocator = ::boost::move(source._allocator);
            this->clear();
            this->_root_ptr = source._root_ptr;
#if defined BOOST_NO_CXX11_NULLPTR
            source._root_ptr = 0;
#else
            source._root_ptr = nullptr;
#endif
        }

        return *this;
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <typename T, typename NodeGenerator, typename Balancer>
    inline binode_container<T,NodeGenerator,Balancer>&
        binode_container<T,NodeGenerator,Balancer>::operator=(
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
            binode_container const& copy
#else
            BOOST_COPY_ASSIGN_REF(binode_container) copy
#endif
        )
    {
        if (this != &copy)
        {
            if (copy._root_ptr)
            {
                if (this->_root_ptr)
                {
                    *this->_root_ptr = *copy._root_ptr;
                }
                else
                {
                    this->_root_ptr = this->_construct_from(
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
        }

        return *this;
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    binode_container<T,NodeGenerator,Balancer>::~binode_container()
    {
        this->clear();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<
        T
      , NodeGenerator
      , Balancer
    >::node::const_pointer
        binode_container<T,NodeGenerator,Balancer>::data() const
    {
        return this->_root_ptr;
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::node::pointer
        binode_container<T,NodeGenerator,Balancer>::data()
    {
        return this->_root_ptr;
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::const_iterator
        binode_container<T,NodeGenerator,Balancer>::cbegin() const
    {
        return this->_root_ptr ? const_iterator(
            make_in_order_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->cend();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::const_iterator
        binode_container<T,NodeGenerator,Balancer>::begin() const
    {
        return this->_root_ptr ? const_iterator(
            make_in_order_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->end();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::iterator
        binode_container<T,NodeGenerator,Balancer>::begin()
    {
        return this->_root_ptr ? iterator(
            make_in_order_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->end();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::const_iterator
        binode_container<T,NodeGenerator,Balancer>::cend() const
    {
        return const_iterator(
            make_in_order_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::const_iterator
        binode_container<T,NodeGenerator,Balancer>::end() const
    {
        return const_iterator(
            make_in_order_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::iterator
        binode_container<T,NodeGenerator,Balancer>::end()
    {
        return iterator(
            make_in_order_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<
        T
      , NodeGenerator
      , Balancer
    >::const_reverse_iterator
        binode_container<T,NodeGenerator,Balancer>::crbegin() const
    {
        return this->_root_ptr ? const_reverse_iterator(
            make_in_order_reverse_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->crend();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<
        T
      , NodeGenerator
      , Balancer
    >::const_reverse_iterator
        binode_container<T,NodeGenerator,Balancer>::rbegin() const
    {
        return this->_root_ptr ? const_reverse_iterator(
            make_in_order_reverse_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->rend();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<
        T
      , NodeGenerator
      , Balancer
    >::reverse_iterator
        binode_container<T,NodeGenerator,Balancer>::rbegin()
    {
        return this->_root_ptr ? reverse_iterator(
            make_in_order_reverse_iterator(*this->_root_ptr)
          , transform_function()
        ) : this->rend();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<
        T
      , NodeGenerator
      , Balancer
    >::const_reverse_iterator
        binode_container<T,NodeGenerator,Balancer>::crend() const
    {
        return const_reverse_iterator(
            make_in_order_reverse_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<
        T
      , NodeGenerator
      , Balancer
    >::const_reverse_iterator
        binode_container<T,NodeGenerator,Balancer>::rend() const
    {
        return const_reverse_iterator(
            make_in_order_reverse_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<
        T
      , NodeGenerator
      , Balancer
    >::reverse_iterator
        binode_container<T,NodeGenerator,Balancer>::rend()
    {
        return reverse_iterator(
            make_in_order_reverse_iterator_end(this->_root_ptr)
          , transform_function()
        );
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::const_reference
        binode_container<T,NodeGenerator,Balancer>::front() const
    {
        return *this->cbegin();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::reference
        binode_container<T,NodeGenerator,Balancer>::front()
    {
        return *this->begin();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::const_reference
        binode_container<T,NodeGenerator,Balancer>::back() const
    {
        return *this->crbegin();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::reference
        binode_container<T,NodeGenerator,Balancer>::back()
    {
        return *this->rbegin();
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline void binode_container<T,NodeGenerator,Balancer>::pop_front()
    {
        this->erase(this->cbegin());
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    typename binode_container<T,NodeGenerator,Balancer>::node::const_pointer
        binode_container<T,NodeGenerator,Balancer>::_back() const
    {
        typename node::const_pointer result = this->_root_ptr;

        if (result)
        {
            while (result->get_right_child_ptr())
            {
                result = result->get_right_child_ptr();
            }
        }

        return result;
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer
        binode_container<T,NodeGenerator,Balancer>::_back()
    {
        typename node::pointer result = this->_root_ptr;

        if (result)
        {
            while (result->get_right_child_ptr())
            {
                result = result->get_right_child_ptr();
            }
        }

        return result;
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline void binode_container<T,NodeGenerator,Balancer>::pop_back()
    {
        this->erase(
            iterator(
                make_in_order_iterator_position(*this->_back())
              , transform_function()
            )
        );
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer
        binode_container<T,NodeGenerator,Balancer>::_construct_from(
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

    template <typename T, typename NodeGenerator, typename Balancer>
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer
        binode_container<T,NodeGenerator,Balancer>::_construct_from(
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

    template <typename T, typename NodeGenerator, typename Balancer>
    void
        binode_container<T,NodeGenerator,Balancer>::push_front(
            const_reference t
        )
    {
        if (this->_root_ptr)
        {
            typename node::pointer p = this->_root_ptr;

            while (p->get_left_child_ptr())
            {
                p = p->get_left_child_ptr();
            }

            p = Balancer::post_insert(p = &*p->emplace_left(t));

            if (!p->get_parent_ptr())
            {
                this->_root_ptr = p;
            }
        }
        else  // if (!this->_root_ptr)
        {
            this->_root_ptr = this->_construct_from(
                ::std::tr1::is_const<
                    typename ::std::tr1::remove_reference<
                        typename node::traits::allocator_reference
                    >::type
                >()
              , this->_allocator
              , t
            );
        }
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    void
        binode_container<T,NodeGenerator,Balancer>::push_back(
            const_reference t
        )
    {
        if (this->_root_ptr)
        {
            typename node::pointer p = this->_root_ptr;

            while (p->get_right_child_ptr())
            {
                p = p->get_right_child_ptr();
            }

            p = Balancer::post_insert(p = &*p->emplace_right(t));

            if (!p->get_parent_ptr())
            {
                this->_root_ptr = p;
            }
        }
        else  // if (!this->_root_ptr)
        {
            this->_root_ptr = this->_construct_from(
                ::std::tr1::is_const<
                    typename ::std::tr1::remove_reference<
                        typename node::traits::allocator_reference
                    >::type
                >()
              , this->_allocator
              , t
            );
        }
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    typename binode_container<T,NodeGenerator,Balancer>::iterator
        binode_container<T,NodeGenerator,Balancer>::insert(
            const_iterator itr
          , const_reference t
        )
    {
        if (itr.base())
        {
            typename node::pointer anc_ptr = const_cast<
                typename node::pointer
            >(&*itr.base());
            typename node::pointer node_ptr = anc_ptr->get_left_child_ptr();

            if (node_ptr)
            {
                while (node_ptr->get_right_child_ptr())
                {
                    node_ptr = node_ptr->get_right_child_ptr();
                }

                node_ptr = &*node_ptr->emplace_right(t);
            }
            else
            {
                node_ptr = &*anc_ptr->emplace_left(t);
            }

            anc_ptr = Balancer::post_insert(node_ptr);

            if (!anc_ptr->get_parent_ptr())
            {
                this->_root_ptr = anc_ptr;
            }

            return iterator(
                make_in_order_iterator_position(*node_ptr)
              , transform_function()
            );
        }
        else  // if (!itr)
        {
            this->push_back(t);
            return this->end();
        }
    }

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename T, typename NodeGenerator, typename Balancer>
    template <typename ...Args>
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer
        binode_container<T,NodeGenerator,Balancer>::_construct_from(
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

    template <typename T, typename NodeGenerator, typename Balancer>
    template <typename ...Args>
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer
        binode_container<T,NodeGenerator,Balancer>::_construct_from(
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

    template <typename T, typename NodeGenerator, typename Balancer>
    template <typename ...Args>
    void
        binode_container<T,NodeGenerator,Balancer>::emplace_front(
            Args&& ...args
        )
    {
        if (this->_root_ptr)
        {
            typename node::pointer p = this->_root;

            while (p->get_left_child_ptr())
            {
                p = p->get_left_child_ptr();
            }

            p = Balancer::post_insert(
                p = &*p->emplace_left(::boost::forward<Args>(args)...)
            );

            if (!p->get_parent_ptr())
            {
                this->_root_ptr = p;
            }
        }
        else  // if (!this->_root_ptr)
        {
            this->_root_ptr = this->_construct_from(
                ::std::tr1::is_const<
                    typename ::std::tr1::remove_reference<
                        typename node::traits::allocator_reference
                    >::type
                >()
              , this->_allocator
              , ::boost::forward<Args>(args)...
            );
        }
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    template <typename ...Args>
    void
        binode_container<T,NodeGenerator,Balancer>::emplace_back(
            Args&& ...args
        )
    {
        if (this->_root_ptr)
        {
            typename node::pointer p = this->_root;

            while (p->get_right_child_ptr())
            {
                p = p->get_right_child_ptr();
            }

            p = Balancer::post_insert(
                p = &*p->emplace_right(::boost::forward<Args>(args)...)
            );

            if (!p->get_parent_ptr())
            {
                this->_root_ptr = p;
            }
        }
        else  // if (!this->_root_ptr)
        {
            this->_root_ptr = this->_construct_from(
                ::std::tr1::is_const<
                    typename ::std::tr1::remove_reference<
                        typename node::traits::allocator_reference
                    >::type
                >()
              , this->_allocator
              , ::boost::forward<Args>(args)...
            );
        }
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    template <typename ...Args>
    typename binode_container<T,NodeGenerator,Balancer>::iterator
        binode_container<T,NodeGenerator,Balancer>::emplace(
            const_iterator itr
          , Args&& ...args
        )
    {
        if (itr.base())
        {
            typename node::pointer anc_ptr = const_cast<
                typename node::pointer
            >(&*itr.base());
            typename node::pointer node_ptr = anc_ptr->get_left_child_ptr();

            if (node_ptr)
            {
                while (node_ptr->get_right_child_ptr())
                {
                    node_ptr = node_ptr->get_right_child_ptr();
                }

                node_ptr = &*node_ptr->emplace_right(
                    ::boost::forward<Args>(args)...
                );
            }
            else
            {
                node_ptr = &*anc_ptr->emplace_left(
                    ::boost::forward<Args>(args)...
                );
            }

            anc_ptr = Balancer::post_insert(node_ptr);

            if (!anc_ptr->get_parent_ptr())
            {
                this->_root_ptr = anc_ptr;
            }

            return iterator(
                make_in_order_iterator_position(*node_ptr)
              , transform_function()
            );
        }
        else  // if (!itr)
        {
            this->emplace_back(::boost::forward<Args>(args)...);
            return this->end();
        }
    }
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
    template <typename T, typename NodeGenerator, typename Balancer>         \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer       \
        binode_container<T,NodeGenerator,Balancer>::_construct_from(         \
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
      , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
    template <typename T, typename NodeGenerator, typename Balancer>         \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer       \
        binode_container<T,NodeGenerator,Balancer>::_construct_from(         \
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
      , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
    template <typename T, typename NodeGenerator, typename Balancer>         \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer       \
        binode_container<T,NodeGenerator,Balancer>::_construct_from(         \
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
      , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
    template <typename T, typename NodeGenerator, typename Balancer>         \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_container<T,NodeGenerator,Balancer>::node::pointer       \
        binode_container<T,NodeGenerator,Balancer>::_construct_from(         \
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
      , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
    template <typename T, typename NodeGenerator, typename Balancer>         \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    void                                                                     \
        binode_container<T,NodeGenerator,Balancer>::emplace_front(           \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (this->_root_ptr)                                                 \
        {                                                                    \
            typename node::pointer p = this->_root;                          \
            while (p->get_left_child_ptr())                                  \
            {                                                                \
                p = p->get_left_child_ptr();                                 \
            }                                                                \
            p = Balancer::post_insert(                                       \
                p = &*p->emplace_left(                                       \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , _                                                    \
                    )                                                        \
                )                                                            \
            );                                                               \
            if (!p->get_parent_ptr())                                        \
            {                                                                \
                this->_root_ptr = p;                                         \
            }                                                                \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            this->_root_ptr = this->_construct_from(                         \
                ::std::tr1::is_const<                                        \
                    typename ::std::tr1::remove_reference<                   \
                        typename node::traits::allocator_reference           \
                    >::type                                                  \
                >()                                                          \
              , this->_allocator                                             \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
    template <typename T, typename NodeGenerator, typename Balancer>         \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    void                                                                     \
        binode_container<T,NodeGenerator,Balancer>::emplace_back(            \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (this->_root_ptr)                                                 \
        {                                                                    \
            typename node::pointer p = this->_root;                          \
            while (p->get_right_child_ptr())                                 \
            {                                                                \
                p = p->get_right_child_ptr();                                \
            }                                                                \
            p = Balancer::post_insert(                                       \
                p = &*p->emplace_right(                                      \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , _                                                    \
                    )                                                        \
                )                                                            \
            );                                                               \
            if (!p->get_parent_ptr())                                        \
            {                                                                \
                this->_root_ptr = p;                                         \
            }                                                                \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            this->_root_ptr = this->_construct_from(                         \
                ::std::tr1::is_const<                                        \
                    typename ::std::tr1::remove_reference<                   \
                        typename node::traits::allocator_reference           \
                    >::type                                                  \
                >()                                                          \
              , this->_allocator                                             \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
        }                                                                    \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO

#define BOOST_TREE_NODE_CONTAINER_BINARY_MACRO(z, n, _)                      \
    template <typename T, typename NodeGenerator, typename Balancer>         \
    BOOST_PP_EXPR_IF(n, template <)                                          \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                             \
    BOOST_PP_EXPR_IF(n, >)                                                   \
    typename binode_container<T,NodeGenerator,Balancer>::iterator            \
        binode_container<T,NodeGenerator,Balancer>::emplace(                 \
            const_iterator itr                                               \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
    {                                                                        \
        if (itr.base())                                                      \
        {                                                                    \
            typename node::pointer anc_ptr = const_cast<                     \
                typename node::pointer                                       \
            >(&*itr.base());                                                 \
            typename node::pointer node_ptr = (                              \
                anc_ptr->get_left_child_ptr()                                \
            );                                                               \
            if (node_ptr)                                                    \
            {                                                                \
                while (node_ptr->get_right_child_ptr())                      \
                {                                                            \
                    node_ptr = node_ptr->get_right_child_ptr();              \
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
                node_ptr = &*anc_ptr->emplace_left(                          \
                    BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                         \
                        n                                                    \
                      , BOOST_CONTAINER_PP_PARAM_FORWARD                     \
                      , _                                                    \
                    )                                                        \
                );                                                           \
            }                                                                \
            anc_ptr = Balancer::post_insert(node_ptr);                       \
            if (!anc_ptr->get_parent_ptr())                                  \
            {                                                                \
                this->_root_ptr = anc_ptr;                                   \
            }                                                                \
            return iterator(                                                 \
                make_in_order_iterator_position(*node_ptr)                   \
              , transform_function()                                         \
            );                                                               \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            this->emplace_back(                                              \
                BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                    \
                    n                                                        \
                  , BOOST_CONTAINER_PP_PARAM_FORWARD                         \
                  , _                                                        \
                )                                                            \
            );                                                               \
            return this->end();                                              \
        }                                                                    \
    }                                                                        \
//!
    BOOST_PP_REPEAT(
        BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
      , BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
      , _
    )
#undef BOOST_TREE_NODE_CONTAINER_BINARY_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <typename T, typename NodeGenerator, typename Balancer>
    typename binode_container<T,NodeGenerator,Balancer>::iterator
        binode_container<T,NodeGenerator,Balancer>::erase(
            const_iterator itr
        )
    {
        if (itr.base()->empty() && (this->_root_ptr == &*itr.base()))
        {
            this->clear();
            return this->end();
        }

        typename node::pointer anc_ptr = const_cast<typename node::pointer>(
            &*itr.base()
        );
        iterator result(
            make_in_order_iterator_position(*anc_ptr)
          , transform_function()
        );
        bool must_erase_begin = (result == this->begin());

        if (!must_erase_begin)
        {
            --result;
        }

        for (typename node::pointer desc_ptr;;)
        {
            if (
                (desc_ptr = anc_ptr->get_left_child_ptr()) && (
                    !anc_ptr->get_right_child_ptr()
                )
            )
            {
                while (desc_ptr->get_right_child_ptr())
                {
                    desc_ptr = desc_ptr->get_right_child_ptr();
                }

                if (desc_ptr->get_parent_ptr() == anc_ptr)
                {
                    if (!anc_ptr->get_right_child_ptr())
                    {
                        put(*anc_ptr, data_key(), get(*desc_ptr, data_key()));

                        bool must_rebalance = Balancer::pre_erase(*desc_ptr);

                        anc_ptr->erase_left();

                        if (must_rebalance)
                        {
                            anc_ptr = Balancer::post_erase_left(anc_ptr);

                            if (!anc_ptr->get_parent_ptr())
                            {
                                this->_root_ptr = anc_ptr;
                            }
                        }

                        break;
                    }
                }
                else  // if (desc_ptr == anc_ptr->get_right_child_ptr())
                {
                    put(*anc_ptr, data_key(), get(*desc_ptr, data_key()));

                    if (desc_ptr->get_left_child_ptr())
                    {
                        anc_ptr = desc_ptr;
                    }
                    else  // if (desc_ptr->empty())
                    {
                        anc_ptr = desc_ptr->get_parent_ptr();

                        if (anc_ptr->get_left_child_ptr())
                        {
                            put(*desc_ptr, data_key(), get(*anc_ptr, data_key()));
                        }
                        else  // desc_ptr is only child of anc_ptr
                        {
                            bool must_rebalance = Balancer::pre_erase(*desc_ptr);

                            anc_ptr->erase_right();

                            if (must_rebalance)
                            {
                                anc_ptr = Balancer::post_erase_right(anc_ptr);

                                if (!anc_ptr->get_parent_ptr())
                                {
                                    this->_root_ptr = anc_ptr;
                                }
                            }

                            break;
                        }
                    }

                    continue;
                }
            }

            if ((desc_ptr = anc_ptr->get_right_child_ptr()))
            {
                while (desc_ptr->get_left_child_ptr())
                {
                    desc_ptr = desc_ptr->get_left_child_ptr();
                }

                put(*anc_ptr, data_key(), get(*desc_ptr, data_key()));

                if (desc_ptr->get_right_child_ptr())
                {
                    if (desc_ptr->get_right_child_ptr()->empty())
                    {
                        bool must_rebalance = Balancer::pre_erase(*desc_ptr);

                        anc_ptr->erase_right();

                        if (must_rebalance)
                        {
                            anc_ptr = Balancer::post_erase_right(anc_ptr);

                            if (!anc_ptr->get_parent_ptr())
                            {
                                this->_root_ptr = anc_ptr;
                            }
                        }
                    }
                    else
                    {
                        anc_ptr = desc_ptr;
                    }
                }
                else if (desc_ptr->get_parent_ptr() == anc_ptr)
                {
                    bool must_rebalance = Balancer::pre_erase(*desc_ptr);

                    anc_ptr->erase_right();

                    if (must_rebalance)
                    {
                        anc_ptr = Balancer::post_erase_right(anc_ptr);

                        if (!anc_ptr->get_parent_ptr())
                        {
                            this->_root_ptr = anc_ptr;
                        }
                    }

                    break;
                }
                else
                {
                    BOOST_ASSERT(desc_ptr->empty());
                    anc_ptr = desc_ptr->get_parent_ptr();
                    BOOST_ASSERT(anc_ptr->get_left_child_ptr() == desc_ptr);

                    if (anc_ptr->get_right_child_ptr())
                    {
                        put(*desc_ptr, data_key(), get(*anc_ptr, data_key()));
                    }
                    else  // desc_ptr is only child of anc_ptr
                    {
                        bool must_rebalance = Balancer::pre_erase(*desc_ptr);

                        anc_ptr->erase_left();

                        if (must_rebalance)
                        {
                            anc_ptr = Balancer::post_erase_left(anc_ptr);

                            if (!anc_ptr->get_parent_ptr())
                            {
                                this->_root_ptr = anc_ptr;
                            }
                        }

                        break;
                    }
                }
            }
            else  // if (anc_ptr->empty())
            {
                desc_ptr = anc_ptr;
                anc_ptr = anc_ptr->get_parent_ptr();

                bool must_rebalance = Balancer::pre_erase(*desc_ptr);

                if (anc_ptr->get_left_child_ptr() == desc_ptr)
                {
                    anc_ptr->erase_left();

                    if (must_rebalance)
                    {
                        anc_ptr = Balancer::post_erase_left(anc_ptr);

                        if (!anc_ptr->get_parent_ptr())
                        {
                            this->_root_ptr = anc_ptr;
                        }
                    }
                }
                else  // if (anc_ptr->get_right_child_ptr() == desc_ptr)
                {
                    anc_ptr->erase_right();

                    if (must_rebalance)
                    {
                        anc_ptr = Balancer::post_erase_right(anc_ptr);

                        if (!anc_ptr->get_parent_ptr())
                        {
                            this->_root_ptr = anc_ptr;
                        }
                    }
                }

                break;
            }
        }

        return must_erase_begin ? this->begin() : ++result;
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    void
        binode_container<T,NodeGenerator,Balancer>::erase(
            const_iterator itr
          , const_iterator itr_end
        )
    {
        while (itr != itr_end)
        {
            itr = this->erase(itr);
        }
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline bool binode_container<T,NodeGenerator,Balancer>::empty() const
    {
        return !this->_root_ptr;
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    void binode_container<T,NodeGenerator,Balancer>::clear()
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

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::size_type
        binode_container<T,NodeGenerator,Balancer>::_size(
            ::boost::mpl::true_
        ) const
    {
        return this->_root_ptr ? get(*this->_root_ptr, count_key()) : 0;
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::size_type
        binode_container<T,NodeGenerator,Balancer>::_size(
            ::boost::mpl::false_
        ) const
    {
        return ::std::distance(this->cbegin(), this->cend());
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::size_type
        binode_container<T,NodeGenerator,Balancer>::size() const
    {
        return this->_size(result_of::has_key<node,count_key>());
    }

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::const_reference
        binode_container<T,NodeGenerator,Balancer>::operator[](
            size_type index
        ) const
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

    template <typename T, typename NodeGenerator, typename Balancer>
    inline typename binode_container<T,NodeGenerator,Balancer>::reference
        binode_container<T,NodeGenerator,Balancer>::operator[](size_type index)
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

#endif  // BOOST_TREE_NODE_CONTAINER_BINODE_HPP_INCLUDED

