
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_TYPE_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_TYPE_HPP_

#include <boost/closure/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/detail/preprocessor/keyword/this.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
// IS_UNARY is part of details because it does not work on BCC compiler.
#include <boost/preprocessor/detail/is_unary.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE_(sign) \
    BOOST_PP_EXPAND( \
        BOOST_PP_TUPLE_REM(1) \
        BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT(sign) \
    ) \
    BOOST_PP_EMPTY /* always trail EMPTY because bind type is optional */

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE_(sign) \
    BOOST_PP_EXPAND( \
        BOOST_PP_TUPLE_EAT(1) \
        BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT(sign) \
    )

#define this_BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_REMOVE_THIS \
    /* must expand to nothing */

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE_(sign) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE( \
        /* can't use `THIS_REMOVE_BACK` because `sign` contains multiple */ \
        /* tokens (and not just one token) so `IS_THIS_BACK` does not work */ \
        /* (but we know `sign` ends with this if we here so we can */ \
        /* manually force the removal using `CAT`) */ \
        BOOST_PP_CAT(sign, _BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_REMOVE_THIS) \
    ) \
    /* do not append PP_EMPTY because ANY_BIND_WITH_TYPE macro above */ \
    /* already appends it */

// PUBLIC //

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE(sign) \
    BOOST_PP_IS_UNARY(BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT( \
            sign))

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE(sign) \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE(sign),\
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITH_TYPE_ \
    , \
        BOOST_PP_EMPTY \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign)

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE(sign) \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE(sign),\
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_WITHOUT_TYPE_ \
    , \
        BOOST_CLOSURE_DETAIL_PP_KEYWORD_CONST_BIND_REMOVE_FRONT \
    )(sign)

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE(sign) \
    BOOST_PP_IIF(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_HAS_TYPE(sign),\
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_ANY_BIND_THIS_TYPE_ \
    , \
        BOOST_PP_EMPTY \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign)

#endif // #include guard

