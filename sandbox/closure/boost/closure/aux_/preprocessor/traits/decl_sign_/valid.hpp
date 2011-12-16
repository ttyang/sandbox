
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_HPP_

#include <boost/closure/aux_/preprocessor/traits/decl_sign_/any_bind_type.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_/nil.hpp>
#include <boost/closure/aux_/preprocessor/traits/dec_/append_unbind.hpp>
#include <boost/closure/aux_/preprocessor/traits/dec_/append_unbind_default.hpp>
#include <boost/closure/aux_/preprocessor/traits/dec_/append_const_bind.hpp>
#include <boost/closure/aux_/preprocessor/traits/dec_/append_const_bind_this_type.hpp>
#include <boost/closure/aux_/preprocessor/traits/dec_/append_bind.hpp>
#include <boost/closure/aux_/preprocessor/traits/dec_/append_bind_this_type.hpp>
#include <boost/closure/detail/keyword/const_bind.hpp>
#include <boost/closure/detail/keyword/bind.hpp>
#include <boost/detail/preprocessor/keyword/default.hpp>
#include <boost/detail/preprocessor/keyword/this.hpp>
#include <boost/preprocessor/control/iif.hpp>

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
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_THIS_BACK( \
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
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_THIS_BACK( \
            /* remove all leading symbols `[const] bind [(type)] ...` */ \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE( \
                    sign)), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_THIS_ \
    , \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_VAR_ \
    )(decl_traits, sign)

// Parse all elements.

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_(s, decl_traits, sign) \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_BIND_FRONT(sign), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_BIND_ \
    , BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT(sign), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_CONST_BIND_ \
    , BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT(sign), \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_UNBIND_DEFAULT_ \
        /* elem is `default ...` where leading default is kept because */ \
        /* default value might not be alphanumeric (so it fails later CAT */ \
        /* for checks), leading default will be removed later when getting */ \
        /* the default value */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_APPEND_UNBIND_DEFAULT \
    , \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_APPEND_UNBIND \
    )))(decl_traits, sign)

// PUBLIC //

// Parse param seq after following precondition has been validated by caller.
// Precondition: If seq contains a default param value `... (default ...) ...`,
// the default value element is never 1st (it always has a previous elem) and
// its previous element is a unbind param (no const-bind and no bind).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID(sign) \
    BOOST_PP_SEQ_FOLD_LEFT(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_VALID_, \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_NIL, sign)

#endif // #include guard

