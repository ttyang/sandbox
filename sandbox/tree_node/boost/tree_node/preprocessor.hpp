// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_PREPROCESSOR_HPP_INCLUDED
#define BOOST_TREE_NODE_PREPROCESSOR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/container/detail/workaround.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
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
        }                                                                    \
//]
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

//[reference__macro__copy_constructible
#define BOOST_TREE_NODE_COPY_CONSTRUCTIBLE(Derived, Base)                    \
        inline Derived(Derived const& copy) : Base(copy)                     \
        {                                                                    \
            Base::on_post_copy_or_move();                                    \
        }                                                                    \
        inline Derived(Derived& copy)                                        \
          : Base(const_cast<Derived const&>(copy))                           \
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

#endif  // BOOST_TREE_NODE_PREPROCESSOR_HPP_INCLUDED

