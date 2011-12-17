
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_HPP_

#include <boost/closure/aux_/preprocessor/traits/bind.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/adt.hpp> // For `IS_CONS`.
#include <boost/preprocessor/list/transform.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_TYPED_(d, macro, elem) \
    macro(elem)

// PUBLIC //

// Expand: pp-list of const-binds.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_CONST_BINDS, decl_traits)

// Expand: 1 iff at least 1 const-bind, 0 otherwise.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_CONST_BIND(decl_traits) \
    BOOST_PP_LIST_IS_CONS(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND( \
            decl_traits))

// Expand: pp-list of const-binds without explicit type.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BINDS_WITHOUT_TYPE( \
        decl_traits) \
    BOOST_PP_LIST_TRANSFORM( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAUTS_CONST_BIND_TYPED_, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ANY_BIND_WITHOUT_TYPE, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND(decl_traits))
        
// Expand: pp-list of const-binds with explicit type.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BINDS_WITH_TYPE(decl_traits) \
    BOOST_PP_LIST_TRANSFORM( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_TYPED_, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ANY_BIND_WITH_TYPE, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND(decl_traits))

// Expand: pp-list of type for const-bind of this (size <= 1 after validation).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_CONST_BIND_THIS_TYPES, \
            decl_traits)

// Expand: 1 iff this is const-bind, 0 otherwise.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_CONST_BIND_THIS(decl_traits) \
    BOOST_PP_LIST_IS_CONS( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES(decl_traits))

#endif // #include guard

