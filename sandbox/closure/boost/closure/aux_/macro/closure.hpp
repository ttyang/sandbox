
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_CLOSURE_HPP_
#define BOOST_CLOSURE_AUX_CLOSURE_HPP_

#include <boost/closure/aux_/macro/code_/result.hpp>
#include <boost/closure/aux_/macro/code_/bind.hpp>
#include <boost/closure/aux_/macro/code_/functor.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_error.hpp>
#include <boost/scope_exit.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_CLOSURE_OK_(decl_traits, id, typename01) \
    BOOST_CLOSURE_AUX_CODE_RESULT(decl_traits, id, typename01) \
    BOOST_CLOSURE_AUX_CODE_BIND(decl_traits, id, typename01) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR(decl_traits, id, typename01) 

#define BOOST_CLOSURE_AUX_CLOSURE_ERROR_(decl_traits, id, typename01) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_RETURNS(decl_traits)), \
        /* return specified, so no result type before this macro expansion */ \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        /* even if error, must declare result type to prevent additional */ \
        /* error due to result type appearing before this macro expansion */ \
        BOOST_CLOSURE_AUX_CODE_RESULT_DECL \
    )(id) \
    ; /* close eventual previous statements, otherwise it has no effect */ \
    BOOST_MPL_ASSERT_MSG(false, /* always fails (there's an error) */ \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ERROR_MSG(decl_traits), ()) \
    ; /* must close ASSERT macro for eventual use within class scope */

// sign_params: parsed parenthesized params.
#define BOOST_CLOSURE_AUX_CLOSURE_(decl_traits, id, typename01) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(BOOST_CLOSURE_AUX_PP_DECL_TRAITS_ERROR_MSG( \
            decl_traits)), \
        BOOST_CLOSURE_AUX_CLOSURE_OK_ \
    , \
        BOOST_CLOSURE_AUX_CLOSURE_ERROR_ \
    )(decl_traits, id, typename01)

// PUBLIC //

#define BOOST_CLOSURE_AUX_CLOSURE_ARGS_VAR \
    BOOST_CLOSURE_AUX_SYMBOL( (args) )

// Undefine local function bound args global variable. Actual declaration of
// this variable is made using SFINAE mechanisms by each local function macro.
extern boost::scope_exit::detail::undeclared BOOST_CLOSURE_AUX_CLOSURE_ARGS_VAR;

#define BOOST_CLOSURE_AUX_CLOSURE(decl_seq, id, typename01) \
    BOOST_CLOSURE_AUX_CLOSURE_(BOOST_CLOSURE_AUX_PP_DECL_TRAITS(decl_seq), \
            id, typename01)

#endif // #include guard

