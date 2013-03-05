
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_HPP_
#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_HPP_

#include <boost/contract/aux_/macro/code_/named_params_/function.hpp>
#include <boost/contract/aux_/macro/code_/named_params_/constructor.hpp>
#include <boost/contract/aux_/macro/code_/named_params_/contracted.hpp>
#include <boost/preprocessor/punctuation/paren_if.hpp>

// PRIVATE //
 
#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_FREE_( \
        id, tpl, k, f, contracted_f, body_func) \
    BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS( \
            id, tpl, k, contracted_f, body_func) ; /* forward declaration */ \
    BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_CONTRACTED_BODY_DECL( \
            id, tpl, k, f, body_func) \
    /* user's function definition { ... } (and try-blocks) follows here */

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_MEMBER_( \
        id, tpl, k, f, contracted_f, body_func) \
    BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNCTION(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS( \
            id, tpl, k, contracted_f, body_func) \
    /* user's function definition { ... } (and try-blocks) follows here */

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_CONSTRUCTOR_( \
        id, tpl, k, f, contracted_f, body_func) \
    BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BOOST_CONTRACT( \
            id, tpl, k, contracted_f, body_func) \
    BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CONSTRUCTOR( \
            id, tpl, k, f, body_func) \
    BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BODY_DECL_FORCE( \
            id, tpl, k, contracted_f, body_func, 1 /* named force body */) \
    /* user's function definition { ... } (and try-blocks) follows here */

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_( \
        id, tpl, k, f, contracted_f, body_func) \
    /* destructors have no parameters so we'll never get here */ \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
        BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_CONSTRUCTOR_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), \
        BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_MEMBER_ \
    , \
        BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_FREE_ \
    ))(id, tpl, k, f, contracted_f, body_func)
            

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC(id, tpl, k, f, body_func) \
    /* NOTE: even if named params are always impl using templates, tpl */ \
    /* should not be forced to 1 here because tpl indicates if the */ \
    /* enclosing scope and not the impl is type-dependent */ \
    BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC_(id, tpl /* keep tpl */, k, f, \
            BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_CONTRACTED_F(k, f), \
            body_func)

#endif // #include guard

