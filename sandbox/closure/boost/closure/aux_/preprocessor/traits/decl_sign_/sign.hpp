
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_sign_/validate.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_sign_/any_bind_type.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/nil.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/set_error.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/validate.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/append.hpp>
#include <boost/closure/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/closure/detail/preprocessor/keyword/bind.hpp>
#include <boost/closure/detail/preprocessor/keyword/return.hpp>
#include <boost/closure/detail/preprocessor/keyword/default.hpp>
#include <boost/closure/detail/preprocessor/keyword/thisunderscore.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>

// PRIVATE //

// Parse const binds.

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_THIS_( \
        decl_traits, sign) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_APPEND_CONST_BIND_THIS_TYPE(decl_traits, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE(sign))

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_VAR_( \
        decl_traits, sign) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_APPEND_CONST_BIND(decl_traits, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE(sign), \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE(sign))

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_( \
        decl_traits, sign) \
    /* check from back because non `this` bounds might have `&` in front */ \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK( \
            /* remove all leading symbols `[const] bind [(type)] ...` */ \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE(sign)),\
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_THIS_ \
    , \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_VAR_ \
    )(decl_traits, sign)

// Parse binds.

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_THIS_( \
        decl_traits, sign) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_APPEND_BIND_THIS_TYPE(decl_traits, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE(sign))

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_VAR_( \
        decl_traits, sign) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_APPEND_BIND(decl_traits, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE( \
                    sign), \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE(sign))

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_(decl_traits, sign) \
    /* check from back because non `this` bounds might have `&` in front */ \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK( \
            /* remove all leading symbols `[const] bind [(type)] ...` */ \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE( \
                    sign)), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_THIS_ \
    , \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_VAR_ \
    )(decl_traits, sign)

// Parse all elements.

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_(s, decl_traits, sign) \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_RETURN_FRONT(sign), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_APPEND_RETURN \
    , BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_BIND_FRONT(sign), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_ \
    , BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT(sign), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_ \
    , BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT(sign), \
        /* elem is `default ...` where leading default is kept because */ \
        /* default value might not be alphanumeric (so it fails later CAT */ \
        /* for checks), leading default will be removed later when getting */ \
        /* the default value */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_APPEND_PARAM_DEFAULT \
    , /* else, it is a function parameter */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_APPEND_PARAM \
    ))))(decl_traits, sign)

// Parse param seq after following precondition has been validated by caller.
// Precondition: If seq contains a default param value `... (default ...) ...`,
// the default value element is never 1st (it always has a previous elem) and
// its previous element is a unbind param (no const-bind and no bind).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_SEQ_(sign) \
    BOOST_PP_SEQ_FOLD_LEFT(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_NIL, sign)

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_YES_(sign, unused) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_VALIDATE( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_SEQ_(sign))

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

