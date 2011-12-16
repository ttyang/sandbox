
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_sign_/validate.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_sign_/valid.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/nil.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/validate.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_YES_(sign, unused) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID(sign))

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_NO_(unused, error) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SET_ERROR( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_NIL, error)

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_(sign, defaults_error) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(defaults_error (/* expand EMPTY */)), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_YES_ \
    , \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_NO_ \
    )(sign, defaults_error)

// PUBLIC //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN(sign) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_(sign, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE(sign))

#endif // #include guard

