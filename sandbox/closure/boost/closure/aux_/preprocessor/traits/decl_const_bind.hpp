
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

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_CONST_BIND, decl_traits)

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_CONST_BIND(decl_traits) \
    BOOST_PP_LIST_IS_CONS(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND( \
            decl_traits))

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_WITHOUT_TYPE( \
        decl_traits) \
    BOOST_PP_LIST_TRANSFORM( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAUTS_CONST_BIND_TYPED_, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ANY_BIND_WITHOUT_TYPE, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND(decl_traits))
        
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_WITH_TYPE(decl_traits) \
    BOOST_PP_LIST_TRANSFORM( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_TYPED_, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ANY_BIND_WITH_TYPE, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND(decl_traits))

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPE(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRIATS_INDEX_CONST_BIND_THIS_TYPE, \
            decl_traits)

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_HAVE_CONST_BIND_THIS(params) \
    BOOST_PP_LIST_IS_CONS( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPE(decl_traits))

#endif // #include guard

