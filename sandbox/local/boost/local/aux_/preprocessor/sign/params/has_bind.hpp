
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the
// Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_LOCAL_AUX_PP_SIGN_PARAMS_HAS_BIND_HPP_
#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_HAS_BIND_HPP_

#include "../../keyword/is_bind.hpp"
#include <boost/detail/preprocessor/sign/params/size.hpp>
#include <boost/detail/preprocessor/sign/param.hpp>
#include <boost/detail/preprocessor/sign/param/type.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/control/if.hpp>

// IMPORTANT: Do not delay macro expansion within these `PP_IF()` so avoid
// expansion problems due to reentrancy with nested `PP_IF()` (because these
// `HAS()` macros can be used within a `PP_IF()` as the condition statement).

// Assume param size >= 1.
#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_HAS_BIND_AT_LAST_(params) \
    BOOST_LOCAL_AUX_PP_KEYWORD_IS_BIND( \
            BOOST_DETAIL_PP_SIGN_PARAM_TYPE( \
            BOOST_DETAIL_PP_SIGN_PARAM(BOOST_PP_DEC( \
            BOOST_DETAIL_PP_SIGN_PARAMS_SIZE(params)), params)))

#define BOOST_LOCAL_AUX_PP_SIGN_PARAMS_HAS_BIND(params) \
    BOOST_PP_IF(BOOST_DETAIL_PP_SIGN_PARAMS_SIZE(params), \
        BOOST_LOCAL_AUX_PP_SIGN_PARAMS_HAS_BIND_AT_LAST_ \
    , \
        0 /* no params so no bind params */ \
        BOOST_PP_TUPLE_EAT(1) \
    )(params)

#endif // #include guard

