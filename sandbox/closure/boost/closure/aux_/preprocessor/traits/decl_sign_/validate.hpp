
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_sign_/validate_/defaults.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_sign_/validate_/this.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_1_(sign, error) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(error(/* expand empty */)), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_THIS \
    , \
        error BOOST_PP_TUPLE_EAT(1) \
    )(sign)

// PUBLIC //

// Validate params seq before starting to parse it.
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE(sign) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_1_(sign, \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS(sign))

#endif // #include guard

