
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the
// Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_HPP_
#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_HPP_

#include "../../symbol.hpp"
#include "../../scope_exit/scope_exit.hpp" // Use this lib's ScopeExit impl.
#include "../../type_traits/add_pointed_const.hpp"
#include <boost/detail/preprocessor/keyword/this.hpp>
#include <boost/detail/preprocessor/keyword/auto.hpp>
#include <boost/detail/preprocessor/keyword/register.hpp>
#include <boost/local/aux_/preprocessor/sign/params_unbind.hpp>
#include <boost/type_traits.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/cat.hpp>

// Param named `this`.

#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_THIS_TYPE(id) \
    BOOST_PP_CAT(se_this_type, id) // Using ScopeExit prefix `se_...`.

#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_THIS_NAME \
    se_this // Using ScopeExit prefix `se_...`.

#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_RENAME_THIS_(param_name) \
    /* can't use `PP_KEYWORD_IS_THIS_FRONT()` because some `param_name` */ \
    /* might start with non-alphanumeric symbol `&` (but never for `this`) */ \
    BOOST_PP_IIF(BOOST_DETAIL_PP_KEYWORD_IS_THIS_BACK(param_name), \
        BOOST_LOCAL_AUX_SYMBOL_THIS_PARAM_NAME \
    , \
        param_name \
    )

// Tag param.

// Adapted from `BOOST_SCOPE_EXIT_AUX_TAG_DECL()`.
#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_TAG_DECL(r, id, i, var) \
    typedef void (*BOOST_SCOPE_EXIT_AUX_TAG(id,i))(int \
            BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_RENAME_THIS_(var) );

// Bound param (const and non-const).

#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_MAYBECONST_BIND_TYPE( \
        id_typename_offset, i, var) \
    BOOST_SCOPE_EXIT_AUX_PARAMS_T( \
            BOOST_PP_TUPLE_ELEM(3, 0, id_typename_offset)):: \
    BOOST_SCOPE_EXIT_AUX_PARAM_T( \
            BOOST_PP_TUPLE_ELEM(3, 0, id_typename_offset), \
            BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(3, 2, id_typename_offset)),\
            var)

#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_MAYBECONST_BIND_VALUE( \
        id_offset, i, var) \
    BOOST_LOCAL_AUX_SYMBOL_PARAMS_VARIABLE_NAME-> \
            BOOST_SCOPE_EXIT_AUX_PARAM( \
                    BOOST_PP_TUPLE_ELEM(2, 0, id_offset), \
                    BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(2, 1, id_offset)), \
                    var).value

// Adapted from `BOOST_SCOPE_EXIT_AUX_ARG_DECL()`.
#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_MAYBECONST_BIND_DECL_( \
        r, id_typename_offset, i, var, const01) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_TUPLE_ELEM(3, 1, id_typename_offset) /* eventual typename */ \
    BOOST_PP_EXPR_IF(const01, \
        BOOST_PP_IIF( \
                BOOST_DETAIL_PP_KEYWORD_IS_TRAILING_THIS(var), \
            ::boost::local::aux::add_pointed_const< /* pointed obj const */ \
        , \
            ::boost::add_const< /* outer type const */ \
        ) \
        BOOST_PP_TUPLE_ELEM(3, 1, id_typename_offset) /* eventual typename */ \
    ) \
    BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_MAYBECONST_BIND_TYPE( \
            id_typename_offset, i, var) \
    BOOST_PP_EXPR_IF(const01, >::type) \
    BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_RENAME_THIS_(var)
    
#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_CONST_BIND_DECL( \
        r, id_typename_offset, i, var) \
    BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_MAYBECONST_BIND_DECL_( \
            r, id_typename_offset, i, var, 1 /* force const */)

#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_BIND_DECL( \
        r, id_typename_offset, i, var) \
    BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_MAYBECONST_BIND_DECL_( \
            r, id_typename_offset, i, var, 0 /* do not force const */)

// Adapted from `BOOST_SCOPE_EXIT_AUX_ARG()`.
#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_MAYBECONST_BIND( \
        r, id_offset, i, var) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_MAYBECONST_BIND_VALUE( \
            id_offset, i, var)

// Unbind param.

#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_UNBIND_DECL( \
        z, param, unused) \
    BOOST_LOCAL_AUX_PP_SIGN_PARAMS_UNBIND_PARAM_DECL(param)

#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_UNBIND_DECL_WITH_DEFAULT( \
        z, param, unused) \
    BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_UNBIND_DECL( \
            z, param, unused) \
    BOOST_PP_IIF(BOOST_LOCAL_AUX_PP_SIGN_PARAMS_UNBIND_PARAM_HAS_DEFAULT( \
            param), \
        = BOOST_LOCAL_AUX_PP_SIGN_PARAMS_UNBIND_PARAM_DEFAULT \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(param)

#define BOOST_LOCAL_AUX_FUNCTION_CODE_PARAM_UNBIND_TYPE_AND_NAME( \
        z, param, unused) \
    BOOST_DETAIL_PP_KEYWORD_AUTO_REMOVE( \
        BOOST_DETAIL_PP_KEYWORD_REGISTER_REMOVE( \
            BOOST_LOCAL_AUX_PP_SIGN_PARAMS_UNBIND_PARAM_DECL(param) \
        ) \
    )

#endif // #include guard

