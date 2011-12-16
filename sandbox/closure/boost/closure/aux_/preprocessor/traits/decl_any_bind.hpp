
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ANY_BIND_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ANY_BIND_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_const_bind.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_bind.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/append.hpp>

// Expand to 1 iff `this` is bound (const or not).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_ANY_BIND_THIS(decl_traits) \
    /* can't use PP_BITOR/PP_OR because don't expand on MSVC */ \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_CONST_BIND_THIS( \
            decl_traits), \
        1 \
    , BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_BIND_THIS( \
            decl_traits), \
        1 \
    , \
        0 \
    ))

// Expand to 1 iff has one or more bound including `this` (const or not).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_ANY_BIND(decl_traits) \
    /* can't use PP_BITOR/PP_OR because don't expand on MSVC */ \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_CONST_BIND( \
            decl_traits), \
        1 \
    , BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_CONST_BIND_THIS( \
            decl_traits), \
        1 \
    , BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_BIND(decl_traits), \
        1 \
    , BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_BIND_THIS( \
            decl_traits), \
        1 \
    , \
        0 \
    ))))

// Expand to list with all binds (const or not) but excluding `this`.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ALL_BIND_WITHOUT_THIS(decl_traits) \
    BOOST_PP_LIST_APPEND(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND( \
            decl_traits), BOOST_CLOSURE_AUX_PP_DECL_TRAITS_BIND(decl_traits))

// Expand to list with all binds (const or not) and including `this` if bound
// (const or not).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ALL_BIND(decl_traits) \
    BOOST_PP_LIST_APPEND(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ALL_BIND( \
            decl_traits), \
        BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_ANY_BIND_THIS( \
                decl_traits), \
            (this, BOOST_PP_NIL) /* `this` never by ref because in C++ */ \
        , \
            BOOST_PP_NIL \
        ) \
    )

// Expand to list of all `this` types (const or not). There is at most 1 bind
// `this` type if no parsing error.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ALL_BIND_THIS_TYPE(decl_traits) \
    BOOST_PP_LIST_APPEND( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_BIND_THIS_TYPE(decl_traits), \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPE(decl_traits))

#endif // #include guard

