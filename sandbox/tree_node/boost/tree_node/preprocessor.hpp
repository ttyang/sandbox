// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_PREPROCESSOR_HPP_INCLUDED
#define BOOST_TREE_NODE_PREPROCESSOR_HPP_INCLUDED

#include <boost/config.hpp>

#if !defined BOOST_NO_SFINAE \
 && !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION \
 && !defined BOOST_TREE_NODE_CAN_USE_FUSION
#define BOOST_TREE_NODE_CAN_USE_FUSION
#endif

#if defined BOOST_TREE_NODE_CAN_USE_FUSION \
 && defined BOOST_TYPEOF_NATIVE \
 && !defined BOOST_TREE_NODE_CAN_USE_FUSION_WITH_TYPEOF
#define BOOST_TREE_NODE_CAN_USE_FUSION_WITH_TYPEOF
#endif

#include <boost/container/scoped_allocator_fwd.hpp>
#include <boost/container/detail/workaround.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/container/detail/preprocessor.hpp>

//[reference__macro__emplacement_ctor_header
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_HEADER(z, n, Type)                  \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        BOOST_PP_EXPR_IIF(BOOST_PP_EQUAL(n, 1), explicit)                    \
        Type(                                                                \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
//]

//[reference__macro__emplacement_ctor_fwd_decl
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_FWD_DECL(z, n, Type)                \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_HEADER(z, n, Type);                 \
//]

//[reference__macro__emplacement_ctor_base_fwd
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_BASE_FWD(z, n, Base)                \
      : Base(                                                                \
            BOOST_PP_CAT(BOOST_PP_ENUM_, z)(                                 \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        )                                                                    \
//]

//[reference__macro__emplacement_ctor_inline_header
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_HEADER(z, n, Tuple)          \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_HEADER(                             \
            z                                                                \
          , n                                                                \
          , BOOST_PP_TUPLE_ELEM(2, 0, Tuple)                                 \
        )                                                                    \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_BASE_FWD(                           \
            z                                                                \
          , n                                                                \
          , BOOST_PP_TUPLE_ELEM(2, 1, Tuple)                                 \
        )                                                                    \
//]

//[reference__macro__emplacement_ctor_inline_def
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF(z, n, Tuple)             \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_HEADER(z, n, Tuple)          \
        {                                                                    \
            Base::on_post_emplacement_construct();                           \
        }                                                                    \
//]

//[reference__macro__emplacement_ctor_w_alloc_header
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_HEADER(z, n, Type)          \
        BOOST_PP_EXPR_IF(n, template <)                                      \
            BOOST_PP_ENUM_PARAMS_Z(z, n, typename P)                         \
        BOOST_PP_EXPR_IF(n, >)                                               \
        BOOST_PP_EXPR_IIF(BOOST_PP_EQUAL(n, 1), explicit)                    \
        Type(                                                                \
            ::boost::container::allocator_arg_t                              \
          , typename traits::allocator_reference allocator                   \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_LIST                                \
              , _                                                            \
            )                                                                \
        )                                                                    \
//]

//[reference__macro__emplacement_ctor_w_alloc_fwd_decl
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_FWD_DECL(z, n, Type)        \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_HEADER(z, n, Type);         \
//]

//[reference__macro__emplacement_ctor_w_alloc_base_fwd
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_BASE_FWD(z, n, Base)        \
      : Base(                                                                \
            ::boost::container::allocator_arg                                \
          , allocator                                                        \
            BOOST_PP_CAT(BOOST_PP_ENUM_TRAILING_, z)(                        \
                n                                                            \
              , BOOST_CONTAINER_PP_PARAM_FORWARD                             \
              , _                                                            \
            )                                                                \
        )                                                                    \
//]

//[reference__macro__emplacement_ctor_w_alloc_inline_header
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_HEADER(z, n, Tuple)  \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_HEADER(                     \
            z                                                                \
          , n                                                                \
          , BOOST_PP_TUPLE_ELEM(2, 0, Tuple)                                 \
        )                                                                    \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_BASE_FWD(                   \
            z                                                                \
          , n                                                                \
          , BOOST_PP_TUPLE_ELEM(2, 1, Tuple)                                 \
        )                                                                    \
//]

//[reference__macro__emplacement_ctor_w_alloc_inline_def
#define BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_DEF(z, n, Tuple)     \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_HEADER(z, n, Tuple)  \
        {                                                                    \
            Base::on_post_emplacement_construct();                           \
        }                                                                    \
//]
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

//[reference__macro__copy_constructible
#define BOOST_TREE_NODE_COPY_CONSTRUCTIBLE(Derived, Base)                    \
        inline Derived(Derived const& copy) : Base(copy)                     \
        {                                                                    \
            Base::on_post_copy_or_move();                                    \
        }                                                                    \
        inline Derived(                                                      \
            Derived const& copy                                              \
          , typename traits::allocator_reference a                           \
        ) : Base(copy, a)                                                    \
        {                                                                    \
            Base::on_post_copy_or_move();                                    \
        }                                                                    \
        inline Derived(Derived& copy)                                        \
          : Base(const_cast<Derived const&>(copy))                           \
        {                                                                    \
            Base::on_post_copy_or_move();                                    \
        }                                                                    \
        inline Derived(                                                      \
            Derived& copy                                                    \
          , typename traits::allocator_reference a                           \
        ) : Base(const_cast<Derived const&>(copy), a)                        \
        {                                                                    \
            Base::on_post_copy_or_move();                                    \
        }                                                                    \
//]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(Derived, Base)                  \
        BOOST_TREE_NODE_COPY_CONSTRUCTIBLE(Derived, Base)                    \
        inline Derived& operator=(Derived const& copy)                       \
        {                                                                    \
            if (this != &copy)                                               \
            {                                                                \
                Base::copy_assign(copy);                                     \
                Base::on_post_copy_or_move();                                \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
        inline Derived& operator=(Derived& copy)                             \
        {                                                                    \
            if (this != &copy)                                               \
            {                                                                \
                Base::copy_assign(const_cast<Derived const&>(copy));         \
                Base::on_post_copy_or_move();                                \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
//!
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined BOOST_NO_RVALUE_REFERENCES
#include <boost/move/move.hpp>
#define BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(Derived, Base)                  \
        BOOST_TREE_NODE_COPY_CONSTRUCTIBLE(Derived, Base)                    \
        inline Derived(::boost::rv<Derived>& source) : Base(source)          \
        {                                                                    \
            Base::on_post_copy_or_move();                                    \
        }                                                                    \
        inline Derived(                                                      \
            ::boost::rv<Derived>& source                                     \
          , typename traits::allocator_reference a                           \
        ) : Base(source, a)                                                  \
        {                                                                    \
            Base::on_post_copy_or_move();                                    \
        }                                                                    \
        inline operator ::boost::rv<Derived> const&() const                  \
        {                                                                    \
            return *static_cast< ::boost::rv<Derived> const*>(this);         \
        }                                                                    \
        inline operator ::boost::rv<Derived>&()                              \
        {                                                                    \
            return *static_cast< ::boost::rv<Derived>*>(this);               \
        }                                                                    \
        inline Derived& operator=(::boost::rv<Derived> const& ca_ref)        \
        {                                                                    \
            Derived const& copy = static_cast<Derived const&>(ca_ref);       \
            if (this != &copy)                                               \
            {                                                                \
                Base::copy_assign(copy);                                     \
                Base::on_post_copy_or_move();                                \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
        inline Derived& operator=(::boost::rv<Derived>& rv_ref)              \
        {                                                                    \
            if (this != &static_cast<Derived&>(rv_ref))                      \
            {                                                                \
                Base::move_assign(rv_ref);                                   \
                Base::on_post_copy_or_move();                                \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
        inline Derived& operator=(Derived& copy)                             \
        {                                                                    \
            if (this != &copy)                                               \
            {                                                                \
                Base::copy_assign(const_cast<Derived const&>(copy));         \
                Base::on_post_copy_or_move();                                \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
//!
#else  // !defined BOOST_NO_RVALUE_REFERENCES
//[reference__macro__copyable_and_movable
#define BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(Derived, Base)                  \
        BOOST_TREE_NODE_COPY_CONSTRUCTIBLE(Derived, Base)                    \
        inline Derived(Derived&& source)                                     \
          : Base(static_cast<Derived&&>(source))                             \
        {                                                                    \
            Base::on_post_copy_or_move();                                    \
        }                                                                    \
        inline Derived(                                                      \
            Derived&& source                                                 \
          , typename traits::allocator_reference a                           \
        ) : Base(static_cast<Derived&&>(source), a)                          \
        {                                                                    \
            Base::on_post_copy_or_move();                                    \
        }                                                                    \
        inline Derived& operator=(Derived const& copy)                       \
        {                                                                    \
            if (this != &copy)                                               \
            {                                                                \
                Base::copy_assign(copy);                                     \
                Base::on_post_copy_or_move();                                \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
        inline Derived& operator=(Derived&& source)                          \
        {                                                                    \
            if (this != &static_cast<Derived&>(source))                      \
            {                                                                \
                Base::move_assign(static_cast<Derived&&>(source));           \
                Base::on_post_copy_or_move();                                \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
//]
#endif  // BOOST_NO_RVALUE_REFERENCES
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__macro__container_derived_impl
#define BOOST_TREE_NODE_CONTAINER_DERIVED_IMPL(Derived, Base)                \
        typedef typename Base::reference       reference;                    \
        typedef typename Base::const_reference const_reference;              \
        typedef typename Base::pointer         pointer;                      \
        typedef typename Base::const_pointer   const_pointer;                \
        typedef typename Base::iterator        iterator;                     \
        typedef typename Base::const_iterator  const_iterator;               \
        typedef typename Base::size_type       size_type;                    \
        typedef typename Base::allocator_type  allocator_type;               \
        inline Derived() : Base()                                            \
        {                                                                    \
        }                                                                    \
        inline explicit Derived(allocator_type const& a) : Base(a)           \
        {                                                                    \
        }                                                                    \
        inline Derived(Derived const& copy)                                  \
          : Base(static_cast<Base const&>(copy))                             \
        {                                                                    \
        }                                                                    \
        inline Derived(Derived const& copy, allocator_type const& a)         \
          : Base(static_cast<Base const&>(copy), a)                          \
        {                                                                    \
        }                                                                    \
        inline Derived(Derived& copy)                                        \
          : Base(                                                            \
                static_cast<Base const&>(const_cast<Derived const&>(copy))   \
            )                                                                \
        {                                                                    \
        }                                                                    \
        inline Derived(Derived& copy, allocator_type const& a)               \
          : Base(                                                            \
                static_cast<Base const&>(const_cast<Derived const&>(copy))   \
              , a                                                            \
            )                                                                \
        {                                                                    \
        }                                                                    \
//]

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#define BOOST_TREE_NODE_CONTAINER_DERIVED_BODY(Derived, Base)                \
        BOOST_TREE_NODE_CONTAINER_DERIVED_IMPL(Derived, Base)                \
        inline Derived& operator=(Derived const& copy)                       \
        {                                                                    \
            if (this != &copy)                                               \
            {                                                                \
                Base::operator=(const_cast<Base const&>(copy));              \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
        inline Derived& operator=(Derived& copy)                             \
        {                                                                    \
            if (this != &copy)                                               \
            {                                                                \
                Base::operator=(const_cast<Base const&>(copy));              \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
//!
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#if defined BOOST_NO_RVALUE_REFERENCES
#include <boost/move/move.hpp>
#define BOOST_TREE_NODE_CONTAINER_DERIVED_BODY(Derived, Base)                \
        BOOST_TREE_NODE_CONTAINER_DERIVED_IMPL(Derived, Base)                \
        inline Derived(::boost::rv<Derived>& source)                         \
          : Base(::boost::move(static_cast<Base&>(source)))                  \
        {                                                                    \
        }                                                                    \
        inline Derived(                                                      \
            ::boost::rv<Derived>& source                                     \
          , allocator_type const& a                                          \
        ) : Base(::boost::move(static_cast<Base&>(source)), a)               \
        {                                                                    \
        }                                                                    \
        inline operator ::boost::rv<Derived> const&() const                  \
        {                                                                    \
            return *static_cast< ::boost::rv<Derived> const*>(this);         \
        }                                                                    \
        inline operator ::boost::rv<Derived>&()                              \
        {                                                                    \
            return *static_cast< ::boost::rv<Derived>*>(this);               \
        }                                                                    \
        inline Derived& operator=(::boost::rv<Derived> const& ca_ref)        \
        {                                                                    \
            Base const& copy = static_cast<Base const&>(                     \
                static_cast<Derived const&>(ca_ref)                          \
            );                                                               \
            if (this != &copy)                                               \
            {                                                                \
                Base::operator=(copy);                                       \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
        inline Derived& operator=(::boost::rv<Derived>& rv_ref)              \
        {                                                                    \
            if (this != &static_cast<Derived&>(rv_ref))                      \
            {                                                                \
                Base::operator=(::boost::move(static_cast<Base&>(rv_ref)));  \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
        inline Derived& operator=(Derived& copy)                             \
        {                                                                    \
            if (this != &copy)                                               \
            {                                                                \
                Base::operator=(                                             \
                    static_cast<Base const&>(                                \
                        const_cast<Derived const&>(copy)                     \
                    )                                                        \
                );                                                           \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
//!
#else  // !defined BOOST_NO_RVALUE_REFERENCES
//[reference__macro__container_derived_body
#define BOOST_TREE_NODE_CONTAINER_DERIVED_BODY(Derived, Base)                \
        BOOST_TREE_NODE_CONTAINER_DERIVED_IMPL(Derived, Base)                \
        inline Derived(Derived&& source)                                     \
          : Base(static_cast<Base&&>(source))                                \
        {                                                                    \
        }                                                                    \
        inline Derived(Derived&& source, allocator_type const& a)            \
          : Base(static_cast<Base&&>(source), a)                             \
        {                                                                    \
        }                                                                    \
        inline Derived& operator=(Derived const& copy)                       \
        {                                                                    \
            if (this != &copy)                                               \
            {                                                                \
                Base::operator=(static_cast<Base const&>(copy));             \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
        inline Derived& operator=(Derived&& source)                          \
        {                                                                    \
            if (this != &static_cast<Derived&>(source))                      \
            {                                                                \
                Base::operator=(static_cast<Derived&&>(source));             \
            }                                                                \
            return *this;                                                    \
        }                                                                    \
//]
#endif  // BOOST_NO_RVALUE_REFERENCES
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__macro__associative_container_derived_body
#define BOOST_TREE_NODE_ASSOCIATIVE_CONTAINER_DERIVED_BODY(Derived, Base)    \
        typedef typename Base::key_type key_type;                            \
        typedef typename Base::value_type value_type;                        \
        typedef typename Base::key_compare key_compare;                      \
        typedef typename Base::value_compare value_compare;                  \
        BOOST_TREE_NODE_CONTAINER_DERIVED_BODY(Derived, Base)                \
//]

#endif  // BOOST_TREE_NODE_PREPROCESSOR_HPP_INCLUDED

