
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_CODE_RESULT_HPP_
#define BOOST_CLOSURE_AUX_CODE_RESULT_HPP_

/** @todo uncomment these includes */
#include <boost/closure/aux_/symbol.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_returns.hpp>
//#include <boost/scope_exit.hpp>
//#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_CODE_RESULT_TAG_(id) \
    BOOST_CLOSURE_AUX_SYMBOL( (deduce_result_tag)(id) )

#define BOOST_CLOSURE_AUX_CODE_RESULT_FUNC_(id) \
    /* symbol (not internal) also gives error if missing result type */ \
    BOOST_PP_CAT( \
  ERROR_missing_result_type_before_the_local_function_parameter_macro_id, \
            id)

#define BOOST_CLOSURE_AUX_CODE_RESULT_WRAP_(id) \
    BOOST_CLOSURE_AUX_SYMBOL( (deduce_result_wrap)(id) )

#define BOOST_CLOSURE_AUX_CODE_RESULT_CAPTURE_(id) \
    BOOST_CLOSURE_AUX_SYMBOL( (deduce_result_capture)(id) )

#define BOOST_CLOSURE_AUX_CODE_RESULT_PARAMS_(id) \
    BOOST_CLOSURE_AUX_SYMBOL( (deduce_result_params)(id) )

#define BOOST_CLOSURE_AUX_CODE_RESULT_FUNC_TYPE_(id) \
    BOOST_CLOSURE_AUX_SYMBOL( (deduce_result_function_type)(id) )

// User did not explicitly specified result type, deduce it (using Typeof).
#define BOOST_CLOSURE_AUX_CODE_RESULT_DEDUCE_(decl_traits, id, typename01) \
    BOOST_CLOSURE_AUX_CODE_RESULT_DECL(decl_traits, id, \
            typename01) \
    /* the many tagging, wrapping, etc that follow are taken from ScopeExit */ \
    /* type deduction mechanism and they are necessary within templates */ \
    /* (at least on GCC) to work around an compiler internal error */ \
    typedef \
        void (*BOOST_CLOSURE_AUX_CODE_RESULT_TAG_(id))( \
            int BOOST_CLOSURE_AUX_CODE_RESULT_FUNC_(id) \
        ) \
    ; \
    typedef \
        BOOST_PP_IIF(typename01, BOOST_TYPEOF_TPL, BOOST_TYPEOF)( \
            ::boost::scope_exit::aux::wrap( \
                ::boost::scope_exit::aux::deref( \
                    BOOST_CLOSURE_AUX_CODE_RESULT_FUNC_(id), \
                    (BOOST_CLOSURE_AUX_CODE_RESULT_TAG_(id))0 \
                ) \
            ) \
        ) \
        BOOST_CLOSURE_AUX_CODE_RESULT_WRAP_(id) \
    ; \
    typedef BOOST_PP_EXPR_IIF(typename01, typename) \
        BOOST_CLOSURE_AUX_CODE_RESULT_WRAP_(id)::type \
        BOOST_CLOSURE_AUX_CODE_RESULT_CAPTURE_(id) \
    ; \
    struct BOOST_CLOSURE_AUX_CODE_RESULT_PARAMS_(id) { \
        /* this typedef is internal to struct so its name will not clash */ \
        typedef BOOST_CLOSURE_AUX_CODE_RESULT_CAPTURE_(id) function_ptr; \
    }; \
    typedef BOOST_PP_EXPR_IIF(typename01, typename) \
        ::boost::remove_pointer< BOOST_PP_EXPR_IIF(typename01, typename) \
            BOOST_CLOSURE_AUX_CODE_RESULT_PARAMS_(id)::function_ptr \
        >::type \
        BOOST_CLOSURE_AUX_CODE_RESULT_FUNC_TYPE_(id) \
    ; \
    typedef BOOST_PP_EXPR_IIF(typename01, typename) \
        ::boost::function_traits< \
            BOOST_CLOSURE_AUX_CODE_RESULT_FUNC_TYPE_(id) \
        >::result_type \
        BOOST_CLOSURE_AUX_CODE_RESULT_TYPE(id) \
    ;

// Use result type as explicitly specified by user (no type deduction needed).
#define BOOST_CLOSURE_AUX_CODE_RESULT_RETURN_( \
        decl_traits, id, typename01) \
    typedef \
        BOOST_PP_LIST_FIRST(BOOST_CLOSURE_AUX_DECL_TRAITS_RETURNS( \
                decl_traits)) \
        BOOST_CLOSURE_AUX_CODE_RESULT_TYPE(id) \
    ;

// PUBLIC //

#define BOOST_CLOSURE_AUX_CODE_RESULT_TYPE(id) \
    BOOST_CLOSURE_AUX_SYMBOL( (result_type)(id) )

#define BOOST_CLOSURE_AUX_CODE_RESULT_DECL( \
        decl_traits, id, typename01) \
    /* result type here */ (*BOOST_CLOSURE_AUX_CODE_RESULT_FUNC_(id))();

#define BOOST_CLOSURE_AUX_CODE_RESULT(decl_traits, id, typename01) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS(BOOST_CLOSURE_AUX_DECL_TRAITS_RETURNS( \
            decl_traits)), \
        BOOST_CLOSURE_AUX_CODE_RESULT_RETURN_ \
    , \
        BOOST_CLOSURE_AUX_CODE_RESULT_DEDUCE_ \
    )(decl_traits, id, typename01)

#endif // #include guard

