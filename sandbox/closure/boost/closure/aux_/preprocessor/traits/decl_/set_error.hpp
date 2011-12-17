
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SET_ERROR_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SET_ERROR_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_param.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_bind.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_const_bind.hpp>

// PUBLIC //

// error: `[ERROR_message_text] EMPTY`, no ERROR_message_text if no error.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SET_ERROR(decl_traits, error) \
    ( /* unbind params and defaults */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS(decl_traits) \
    , /* const-bind names */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BINDS(decl_traits) \
    , /* const-bind `this` types */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES(decl_traits) \
    , /* bind names */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    , /* bind `this` types */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    , /* error message (if any) */ \
        error \
    ) 

#endif // #include guard

