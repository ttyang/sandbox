
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BINDS_HPP_

#include <boost/closure/aux_/preprocessor/traits/bind.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/transform.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_APPLY_( \
        d, bind_macro, bind_traits) \
    bind_macro(bind_traits)

// PUBLIC //

// Expand: pp-list of const bind-traits.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_CONST_BINDS, decl_traits)

// Expand: pp-list of const bind-this-traits (size <= 1 after validation).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_INDEX_CONST_BIND_THIS_TYPES, \
            decl_traits)

#endif // #include guard

