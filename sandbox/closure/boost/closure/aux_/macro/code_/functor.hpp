
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_CODE_FUNCTOR_HPP_
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_HPP_

/** @todo uncomment these includes */
#include <boost/closure/aux_/symbol.hpp>
//#include <boost/closure/aux_/function.hpp>
#include <boost/closure/aux_/add_pointed_const.hpp>
#include <boost/closure/aux_/macro/closure.hpp>
#include <boost/closure/aux_/macro/closure_typeof.hpp>
#include <boost/closure/aux_/macro/code_/result.hpp>
#include <boost/closure/aux_/macro/code_/bind.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_params.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_binds.hpp>
#include <boost/closure/aux_/preprocessor/traits/decl_const_binds.hpp>
#include <boost/closure/detail/preprocessor/keyword/auto.hpp>
#include <boost/closure/detail/preprocessor/keyword/register.hpp>
#include <boost/closure/detail/preprocessor/keyword/this.hpp>
#include <boost/utility/identity.hpp>
//#include <boost/scope_exit.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/list/first_n.hpp>

// PRIVATE //

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_CLASS_TYPE_(id) \
    BOOST_CLOSURE_AUX_SYMBOL( (functor)(id) )

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_F_TYPE_ \
    BOOST_CLOSURE_AUX_SYMBOL( (function_type) )

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_BODY_FUNC_ \
    BOOST_CLOSURE_AUX_SYMBOL( (body) )

// Unbind parameters.

// i: 1 for 1st param, 2 for 2nd, ... (start from 1 not 0).
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_(i) \
    /* this must be a generic parameter name because type and name */ \
    /* are not separate tokens in the macro syntax so name is not available */ \
    /* separately from its type */ \
    BOOST_PP_CAT(arg, i)

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_ENUM_( \
        r, unused, i, param_traits) \
    BOOST_PP_COMMA_IF(i) /* enumeration commas */ \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_(BOOST_PP_INC(i))

// i: 1 for 1st param, 2 for 2nd, ... (start from 1 not 0).
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_TYPE_(typename01, i) \
    /* the parameter type must be accessed using function traits from */ \
    /* function type because it is not available to the macro syntax */ \
    /* separately from the parameter name */ \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    ::boost::function_traits< \
        BOOST_CLOSURE_AUX_CODE_FUNCTOR_F_TYPE_ \
    >::BOOST_PP_CAT(BOOST_PP_CAT(arg, i), _type) \

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_DECL_ENUM_( \
        r, typename01, i, param_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_EXPR_IIF(typename01, typename) \
    ::boost::call_traits< \
        BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_TYPE_(typename01, \
                BOOST_PP_INC(i)) \
    >::param_type \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_(BOOST_PP_INC(i))

// Precondition: !EMPTY(DEFAULT(param_traits))
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_DEFAULT_ASSIGNMENT_(param_traits) \
    = BOOST_CLOSURE_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_FRONT( \
            BOOST_CLOSURE_AUX_PP_PARAM_TRAITS_DEFAULT(param_traits))

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_DECL_ENUM_( \
        r, default01, i, param_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_AUTO_REMOVE_BACK( \
    BOOST_CLOSURE_DETAIL_PP_KEYWORD_REGISTER_REMOVE_BACK( \
        BOOST_CLOSURE_AUX_PP_PARAM_TRAITS_DECL(param_traits) \
    )) \
    BOOST_PP_IIF(BOOST_PP_COMPL(default01), \
        BOOST_PP_TUPLE_EAT(1) /* without default */ \
    , BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            BOOST_CLOSURE_AUX_PP_PARAM_TRAITS_DEFAULT(param_traits)), \
        BOOST_PP_TUPLE_EAT(1) /* has no default */ \
    , /* else, with default and has default */ \
        BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_DEFAULT_ASSIGNMENT_ \
    ))(param_traits)

// Bound parameters.

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAMS_ \
    bind_params /* constructor void* param */

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_VAR_(i) \
    /* named `bind0`, `bind1`, ... */ \
    BOOST_CLOSURE_AUX_SYMBOL( (bind)(i) )

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_ \
    BOOST_CLOSURE_AUX_SYMBOL( (bind_this) )

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_TYPE_( \
        id_typename_offset, i, bind_traits) \
    BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(3, 1, id_typename_offset), typename) \
    BOOST_SCOPE_EXIT_AUX_PARAMS_T( \
            BOOST_PP_TUPLE_ELEM(3, 0, id_typename_offset)):: \
    BOOST_SCOPE_EXIT_AUX_PARAM_T( \
            BOOST_PP_TUPLE_ELEM(3, 0, id_typename_offset), \
            BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(3, 2, id_typename_offset)),\
            BOOST_CLOSURE_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE(bind_traits))

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_MEMBER_BIND_( \
        r, offset, i, bind_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_VAR_( \
            BOOST_PP_ADD(offset, i))

// Adapted from `BOOST_SCOPE_EXIT_AUX_ARG_DECL()`.
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_( \
        r, id_typename_offset, i, bind_traits, is_const) \
    /* IMPORTANT: here can't use `PP_KEYWORD_IS_THIS_FRONT()` because some */ \
    /* `param_name` might start with non-alphanumeric symbol `&` (but that */ \
    /* is never the case for `this`) */ \
    BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(3, 1, id_typename_offset), typename) \
    BOOST_PP_EXPR_IF(is_const, \
        BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_THIS_BACK( \
                BOOST_CLOSURE_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                        bind_traits)), \
            ::boost::local::aux::add_pointed_const< /* pointed obj const */ \
        , \
            ::boost::add_const< /* outer type const */ \
        ) \
    ) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_TYPE_(id_typename_offset, \
            i, bind_traits) \
    BOOST_PP_EXPR_IF(is_const, >::type) \
    BOOST_PP_IIF(BOOST_DETAIL_PP_KEYWORD_IS_THIS_BACK( \
                BOOST_CLOSURE_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE( \
                        bind_traits)), \
        this_ BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CLOSURE_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE \
    )(bind_traits)

// Adapted from `BOOST_SCOPE_EXIT_AUX_ARG_DECL()`.
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_ENUM_( \
        r, id_typename_offset, i, bind_traits, is_const) \
    BOOST_PP_COMMA_IF(i) /* enumeration commas */ \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_( \
            r, id_typename_offset, i, bind_traits, is_const)
    
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_BIND_DECL_ENUM_( \
        r, id_typename_offset, i, bind_traits) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_ENUM_( \
            r, id_typename_offset, i, bind_traits, 0 /* do not force const */)

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_CONST_BIND_DECL_ENUM_( \
        r, id_typename_offset, i, bind_traits) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_ENUM_( \
            r, id_typename_offset, i, bind_traits, 1 /* force const */)

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_DECL_( \
        r, id_typename_offset, i, bind_traits, is_const) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_( \
            r, id_typename_offset, i, \
            & /* all bind member vars are refs to ScopeExit struct members */ \
            BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_VAR_( \
                    BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(3, 2, \
                            id_typename_offset))), \
            is_const) \
    ; /* end member variable declaration */

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_BIND_MEMBER_DECL_( \
        r, id_typename_offset, i, bind_traits) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_DECL_( \
            r, id_typename_offset, i, bind_traits, 0 /* do not force const */)

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_CONST_BIND_MEMBER_DECL_( \
        r, id_typename_offset, i, bind_traits) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_DECL_( \
            r, id_typename_offset, i, bind_traits, 1 /* force const */)

// Adapted from `BOOST_SCOPE_EXIT_AUX_ARG()`.
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_INIT_ENUM_( \
        r, id_offset, i, bind_traits) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_VAR_( \
            BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(2, 1, id_offset))) \
    ( /* member variable initialization */ \
        static_cast< \
            BOOST_SCOPE_EXIT_AUX_PARAMS_T( \
                    BOOST_PP_TUPLE_ELEM(2, 0, id_offset))* \
        >(BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAMS_)-> \
        BOOST_SCOPE_EXIT_AUX_PARAM( \
              BOOST_PP_TUPLE_ELEM(2, 0, id_offset) \
            , BOOST_PP_ADD(i, BOOST_PP_TUPLE_ELEM(2, 1, id_offset)) \
            , BOOST_CLOSURE_AUX_PP_BIND_TRAITS_VAR_WITHOUT_TYPE(bind_traits) \
        ).value \
    )

// Typeof type-definitions.

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_TYPEDEF_( \
        r, id_typename_offset, i, bind_traits, is_const) \
    typedef /* the type with the special typeof name */ \
        BOOST_CLOSURE_AUX_CLOSURE_TYPEOF_TYPE( \
            BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_DECL_( \
                    r, id_typename_offset, i, bind_traits, is_const) \
        ) \
    ; /* end typedef */

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_TYPEDEF_( \
        r, id_typename_offset, i, bind_traits) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_TYPEDEF_( \
            r, id_typename_offset, i, bind_traits, 0 /* do not add const */)

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_CONST_TYPEDEF_( \
        r, id_typename_offset, i, bind_traits) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_TYPEDEF_( \
            r, id_typename_offset, i, bind_traits, 1 /* add const */)

// Expand to the function type `R (A1, ...)`.
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_F_( \
        decl_traits, id, has_type, function_type) \
    BOOST_CLOSURE_AUX_CODE_RESULT_TYPE(id) \
    BOOST_PP_EXPR_IIF(has_type, (function_type) ) \
    ( \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_DECL_ENUM_, \
                0, /* without defaults */ \
                BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS(decl_traits)) \
    )

// Functor call operations.

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_CALL_(z, defaults_n, decl_traits, \
        params, const_binds, has_const_bind_this, binds, has_bind_this, \
        id, typename01) \
    inline BOOST_CLOSURE_AUX_CODE_RESULT_TYPE(id) operator()( \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_DECL_ENUM_, \
                typename01, params) \
    ) const { \
        /* just forward call to member function with local func name */ \
        return BOOST_CLOSURE_AUX_CODE_FUNCTOR_BODY_FUNC_( \
            BOOST_PP_LIST_FOR_EACH_I( \
                    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_MEMBER_BIND_, \
                    0 /* no offset */, const_binds) \
            /* pass plain binds */ \
            BOOST_PP_COMMA_IF( \
                BOOST_PP_BITAND( \
                      BOOST_PP_LIST_IS_CONS(const_binds) \
                    , BOOST_PP_LIST_IS_CONS(binds) \
                ) \
            ) \
            BOOST_PP_LIST_FOR_EACH_I( \
                    BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_MEMBER_BIND_, \
                    /* offset index of # const-binds (could be 0) */ \
                    BOOST_PP_LIST_SIZE(const_binds), binds) \
            /* pass bind `this` */ \
            BOOST_PP_COMMA_IF( \
                BOOST_PP_BITAND( \
                      BOOST_PP_BITOR( \
                          BOOST_PP_LIST_IS_CONS(const_binds) \
                        , BOOST_PP_LIST_IS_CONS(binds) \
                      ) \
                    , BOOST_PP_BITOR(has_const_bind_this, has_bind_this) \
                ) \
            ) \
            BOOST_PP_EXPR_IIF( \
                    BOOST_PP_BITOR(has_const_bind_this, has_bind_this), \
                BOOST_CLOSURE_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_ \
            ) \
            /* pass params */ \
            BOOST_PP_COMMA_IF( \
                BOOST_PP_BITAND( \
                      BOOST_PP_BITOR( \
                          BOOST_PP_BITOR( \
                              BOOST_PP_LIST_IS_CONS(const_binds) \
                            , BOOST_PP_LIST_IS_CONS(binds) \
                          ) \
                        , BOOST_PP_BITOR(has_const_bind_this, has_bind_this) \
                      ) \
                    , BOOST_PP_LIST_IS_CONS(params) \
                ) \
            ) \
            BOOST_PP_LIST_FOR_EACH_I( \
                    BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_ENUM_, ~, \
                    params) \
        ); \
    }

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_STATIC_CALL_FUNC_( \
        z, defaults_n, unused) \
    BOOST_CLOSURE_AUX_SYMBOL( (call)(defaults_n) )

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_STATIC_CALL_FUNC_ADDR_( \
        z, defaults_n, unused) \
    &BOOST_CLOSURE_AUX_CODE_FUNCTOR_STATIC_CALL_FUNC_(z, defaults_n, unused)

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_STATIC_CALL_(z, defaults_n, \
        decl_traits, params, const_binds, has_const_bind_this, binds, \
        has_bind_this, id, typename01) \
    inline static BOOST_CLOSURE_AUX_CODE_RESULT_TYPE(id) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_STATIC_CALL_FUNC_(z, defaults_n, ~)( \
        void* object \
        BOOST_PP_COMMA_IF(BOOST_PP_LIST_IS_CONS(params)) \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_DECL_ENUM_, \
                typename01, params) \
    ) { \
        /* run-time: casting object to this class type and forward call to */ \
        /* `operator()` (this performs better than doing multiple casting */ \
        /* or using a casted object local variable here to call body */ \
        /* directly from here without passing via `operator()`) */ \
        /* compliance: passing local class type to `static_cast` is fully */ \
        /* C++03 compliant because `static_cast` is not a template (even */ \
        /* if its syntax resembles a function template call) in fact even */ \
        /* in C is legal to cast to a local struct (using C-style casting) */ \
        return static_cast< BOOST_CLOSURE_AUX_CODE_FUNCTOR_CLASS_TYPE_(id)* >( \
                object)->operator()( \
            BOOST_PP_LIST_FOR_EACH_I( \
                    BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_ARG_NAME_ENUM_, ~, \
                    params) \
        ); \
    }

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_CALL_FOR_DEFAULTS_(z, n, \
        op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename) \
    BOOST_PP_EXPAND( \
    BOOST_PP_TUPLE_ELEM(9, 0, \
        op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename) \
    ( z, n \
    , BOOST_PP_TUPLE_ELEM(9, 1, \
        op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename) \
    , BOOST_PP_LIST_FIRST_N(BOOST_PP_SUB(BOOST_PP_LIST_SIZE( \
        /* remove last n default params */ \
        BOOST_PP_TUPLE_ELEM(9, 2, \
            op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename)),\
            n), \
        BOOST_PP_TUPLE_ELEM(9, 2, \
            op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename)) \
    , BOOST_PP_TUPLE_ELEM(9, 3, \
        op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename) \
    , BOOST_PP_TUPLE_ELEM(9, 4, \
        op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename) \
    , BOOST_PP_TUPLE_ELEM(9, 5, \
        op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename) \
    , BOOST_PP_TUPLE_ELEM(9, 6, \
        op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename) \
    , BOOST_PP_TUPLE_ELEM(9, 7, \
        op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename) \
    , BOOST_PP_TUPLE_ELEM(9, 8, \
        op_decl_params_constbinds_hasconstthis_binds_hasthis_id_typename) \
    ) /* end `op_macro(...)` */ \
    ) /* end expand */

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_MEMBER_INITS_( \
        const_binds, has_const_bind_this, binds, has_bind_this, id) \
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(BOOST_PP_BITOR(BOOST_PP_BITOR( \
            BOOST_PP_LIST_IS_CONS(const_binds), BOOST_PP_LIST_IS_CONS(binds)), \
            has_bind_this), has_const_bind_this), \
        : \
    ) \
    /* init const binds */ \
    BOOST_PP_LIST_FOR_EACH_I( \
            BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_INIT_ENUM_, \
            ( id, 0 /* no offset */ ), const_binds) \
    /* init plain binds */ \
    BOOST_PP_COMMA_IF( \
        BOOST_PP_BITAND( \
              BOOST_PP_LIST_IS_CONS(const_binds) \
            , BOOST_PP_LIST_IS_CONS(binds) \
        ) \
    ) \
    BOOST_PP_LIST_FOR_EACH_I( \
            BOOST_CLOSURE_AUX_CODE_FUNCTOR_MAYBECONST_BIND_MEMBER_INIT_ENUM_, \
            /* offset index of # of const-binds (could be 0) */ \
            ( id, BOOST_PP_LIST_SIZE(const_binds) ), binds) \
    /* init `this` bind (const or not) */ \
    BOOST_PP_COMMA_IF( \
        BOOST_PP_BITAND( \
              BOOST_PP_BITOR( \
                  BOOST_PP_LIST_IS_CONS(const_binds) \
                , BOOST_PP_LIST_IS_CONS(binds) \
              ) \
            , BOOST_PP_BITOR(has_const_bind_this, has_bind_this) \
        ) \
    ) \
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(has_const_bind_this, has_bind_this), \
        BOOST_CLOSURE_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_( \
            static_cast< BOOST_SCOPE_EXIT_AUX_PARAMS_T(id)* >( \
                    BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAMS_)-> \
                    BOOST_CLOSURE_AUX_CODE_BIND_THIS_VAR \
        ) \
    )

// Functor class.

// Adapted from `BOOST_SCOPE_EXIT_AUX_IMPL()`.
#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_(decl_traits, params, default_count, \
        const_binds, has_const_bind_this, binds, has_bind_this, \
        id, typename01) \
    class BOOST_CLOSURE_AUX_CODE_FUNCTOR_CLASS_TYPE_(id) \
    /* run-time: do not use base class to allow for compiler optimizations */ \
    { \
        /* function type */ \
        typedef BOOST_CLOSURE_AUX_CODE_FUNCTOR_F_(sign_params, id, \
                1 /* has type */, BOOST_CLOSURE_AUX_CODE_FUNCTOR_F_TYPE_); \
        /* functor type -- this type cannot have ID postfix because it is */ \
        /* used the `NAME` macro (this symbol is within functor class so */ \
        /* it does not have to have ID postfix) */ \
        typedef BOOST_PP_EXPR_IIF(typename01, typename) \
            BOOST_IDENTITY_TYPE(( /* IDENTITY for template param comma */ \
                ::boost::local::aux::function< \
                      BOOST_CLOSURE_AUX_CODE_FUNCTOR_F_TYPE_ \
                    , default_count \
                > \
            )) \
            BOOST_CLOSURE_AUX_CODE_FUNCTOR_TYPE \
        ; \
        /* typeof types -- these types are qualified with extra eventual */ \
        /* const and/or & if their variables are bound by const and/or & */ \
        /* (this is because it is not possible to strip the eventual & */ \
        /* given that the var name is always attached to the & symbol plus */ \
        /* programmers can always remove const& using type traits) */ \
        /* const bind typeof types */ \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_CLOSURE_AUX_CODE_FUNCTOR_CONST_TYPEDEF_,\
                (id, typename01, 0 /* no offset */), const_binds) \
        /* bind typeof types */ \
        BOOST_PP_LIST_FOR_EACH_I(BOOST_CLOSURE_AUX_CODE_FUNCTOR_TYPEDEF_, \
                /* offset index with # of preceding const-binds (if any) */ \
                ( id, typename01, BOOST_PP_LIST_SIZE(const_binds) ), binds) \
        /* const this... */ \
        BOOST_PP_EXPR_IIF(has_const_bind_this, \
            typedef BOOST_CLOSURE_AUX_CLOSURE_TYPEOF_TYPE( \
                BOOST_PP_EXPR_IIF(typename01, typename) \
                ::boost::local::aux::add_pointed_const< \
                    BOOST_CLOSURE_AUX_CODE_BIND_THIS_TYPE(id) \
                >::type \
                this_ \
            ) ; /* close typedef */ \
        ) \
        /* ... or, non-const this */ \
        BOOST_PP_EXPR_IIF(has_bind_this, \
            typedef BOOST_CLOSURE_AUX_CLOSURE_TYPEOF_TYPE( \
                BOOST_CLOSURE_AUX_CODE_BIND_THIS_TYPE(id) \
                this_ \
            ) ; /* close typedef */ \
        ) \
    public: \
        /* constructor */ \
        inline explicit BOOST_CLOSURE_AUX_CODE_FUNCTOR_CLASS_TYPE_(id)( \
                void* BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAMS_) \
            /* NOTE: there is no way to wrap member initializer commas */ \
            /* within paren so you must handle these commas manually if */ \
            /* expanding this macro within another macro */ \
            BOOST_CLOSURE_AUX_CODE_FUNCTOR_MEMBER_INITS_(const_binds, \
                    has_const_bind_this, binds, has_bind_this, id) \
        { /* do nothing */ } \
        /* run-time: implement `operator()` (and for all default params) so */ \
        /* this obj can be used directly as a functor for C++03 extensions */ \
        /* and optimized macros */ \
        BOOST_PP_REPEAT( \
            /* PP_INC to handle no dflt (EXPAND for MVSC) */ \
            BOOST_PP_EXPAND(BOOST_PP_INC(default_count)), \
            BOOST_CLOSURE_AUX_CODE_FUNCTOR_CALL_FOR_DEFAULTS_,\
            ( BOOST_CLOSURE_AUX_CODE_FUNCTOR_CALL_, decl_traits, params \
            , const_binds, has_const_bind_this, binds, has_bind_this, id \
            , typename01 ) \
        ) \
        /* compliance: trick to pass this local class as a template param */ \
        /* on pure C++03 without non C++03 extension */ \
        /* performance: this trick introduced _one_ indirect function call */ \
        /* via a function pointer that is usually not inlined by compliers */ \
        /* thus increasing run-time (also another trick using a base */ \
        /* interface class was investigated but virtual calls also cannot */ \
        /* inlined plus they require virtual table lookups to the "virtual */ \
        /* call trick" measured longer run-times than this "static call */ \
        /* trick") */ \
        BOOST_PP_REPEAT( \
            /* PP_INC to handle no dflt (EXPAND for MVSC) */ \
            BOOST_PP_EXPAND(BOOST_PP_INC(default_count)), \
            BOOST_CLOSURE_AUX_CODE_FUNCTOR_CALL_FOR_DEFAULTS_,\
            ( BOOST_CLOSURE_AUX_CODE_FUNCTOR_STATIC_CALL_, decl_traits \
            , params, const_binds, has_const_bind_this, binds, has_bind_this \
            , id, typename01 ) \
        ) \
        inline static void BOOST_CLOSURE_AUX_CODE_FUNCTOR_INIT_CALL_FUNC( \
                void* object, BOOST_CLOSURE_AUX_CODE_FUNCTOR_TYPE& functor) { \
            functor.BOOST_CLOSURE_AUX_CODE_FUNCTOR_INIT_CALL_FUNC(object, \
                BOOST_PP_ENUM( \
                        /* PP_INC to handle no dflt (EXPAND for MVSC) */ \
                        BOOST_PP_EXPAND(BOOST_PP_INC(default_count)), \
                        BOOST_CLOSURE_AUX_CODE_FUNCTOR_STATIC_CALL_FUNC_ADDR_, \
                        ~) \
            ); \
        } \
    private: \
        /* run-time: it is faster if call `operator()` just accesses member */ \
        /* references to the ScopeExit struct instead of accessing the bind */ \
        /* struct at each call (these mem refs are init by the constructor) */ \
        BOOST_PP_LIST_FOR_EACH_I( /* const bind member references */ \
                BOOST_CLOSURE_AUX_CODE_FUNCTOR_CONST_BIND_MEMBER_DECL_,\
                ( id, typename01, 0 /* no offset */ ), const_binds) \
        BOOST_PP_LIST_FOR_EACH_I( /* bind member references */ \
                BOOST_CLOSURE_AUX_CODE_FUNCTOR_BIND_MEMBER_DECL_, \
                /* offset index of # of const-binds (could be 0) */ \
                ( id, typename01, BOOST_PP_LIST_SIZE(const_binds) ), binds) \
        /* bind this const or not (pointed-const is not added here because */ \
        /* this is a reference, it is added to the this_ body param instead */ \
        BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(has_bind_this, has_const_bind_this), \
            BOOST_CLOSURE_AUX_CODE_BIND_THIS_TYPE(id) \
            & /* all bind member vars are refs to ScopeExit struct members */ \
            BOOST_CLOSURE_AUX_CODE_FUNCTOR_BIND_MEMBER_THIS_ \
            ; /* end member variable declaration */ \
        ) \
        /* this decl allows for nesting (local functions, etc) as */ \
        /* it makes the args variable visible within the body code (which */ \
        /* cannot be static); this is for compilation only as the args */ \
        /* variable is actually declared by the 1st enclosing local func */ \
        boost::scope_exit::aux::undeclared BOOST_CLOSURE_AUX_CLOSURE_ARGS_VAR; \
        /* body function (unfortunately, cannot be static to allow access */ \
        /* to member var with local function name for recursion but doing */ \
        /* so also allows the body to misuse `this` instead of `this_`) */ \
        inline BOOST_CLOSURE_AUX_CODE_RESULT_TYPE(id) \
        BOOST_CLOSURE_AUX_CODE_FUNCTOR_BODY_FUNC_( \
                /* const binds */ \
                BOOST_PP_LIST_FOR_EACH_I( \
                        BOOST_CLOSURE_AUX_CODE_FUNCTOR_CONST_BIND_DECL_ENUM_,\
                        ( id, typename01, 0 /* no offset */ ), const_binds) \
                /* plain binds */ \
                BOOST_PP_COMMA_IF( \
                    BOOST_PP_BITAND( \
                          BOOST_PP_LIST_IS_CONS(const_binds) \
                        , BOOST_PP_LIST_IS_CONS(binds) \
                    ) \
                ) \
                BOOST_PP_LIST_FOR_EACH_I( \
                        BOOST_CLOSURE_AUX_CODE_FUNCTOR_BIND_DECL_ENUM_, \
                        /* offset index of # of const-binds (could be 0) */ \
                        ( id, typename01, BOOST_PP_LIST_SIZE(const_binds) ), \
                        binds) \
                /* `this` bind */ \
                BOOST_PP_COMMA_IF( \
                    BOOST_PP_BITAND( \
                          BOOST_PP_BITOR( \
                              BOOST_PP_LIST_IS_CONS(const_binds) \
                            , BOOST_PP_LIST_IS_CONS(binds) \
                          ) \
                        , BOOST_PP_BITOR(has_const_bind_this, has_bind_this) \
                    ) \
                ) \
                /* const pointer to const object */ \
                BOOST_PP_EXPR_IIF(has_const_bind_this, \
                    BOOST_PP_EXPR_IIF(typename01, typename) \
                    ::boost::local::aux::add_pointed_const< \
                        BOOST_CLOSURE_AUX_CODE_BIND_THIS_TYPE(id) \
                    >::type const \
                    this_ /* special name to access object this */ \
                ) \
                /* const pointer to non-const object */ \
                BOOST_PP_EXPR_IIF(has_bind_this, \
                    BOOST_CLOSURE_AUX_CODE_BIND_THIS_TYPE(id) const \
                    this_ /* special name to access object this */ \
                ) \
                /* params (last because they can have defaults) */ \
                BOOST_PP_COMMA_IF( \
                    BOOST_PP_BITAND( \
                          BOOST_PP_BITOR( \
                              BOOST_PP_BITOR( \
                                  BOOST_PP_LIST_IS_CONS(const_binds) \
                                , BOOST_PP_LIST_IS_CONS(binds) \
                              ) \
                            , BOOST_PP_BITOR(has_const_bind_this, \
                                    has_bind_this) \
                          ) \
                        , BOOST_PP_LIST_IS_CONS(params) \
                    ) \
                ) \
                BOOST_PP_LIST_FOR_EACH_I( \
                        BOOST_CLOSURE_AUX_CODE_FUNCTOR_PARAM_DECL_ENUM_, \
                        1 /* with defaults */, params) \
            ) /* end body function params */ \
            /* const member func so it cannot change obj (reassign member */ \
            /* var with local function name, etc) */ \
            const \
            /* user local function definition `{ ... }` will follow here */ \
    /* `END` macro will close function class decl `};` here */ 

// PUBLIC //

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_TYPE \
    BOOST_CLOSURE_AUX_SYMBOL( (functor_type) )

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR_INIT_CALL_FUNC \
    BOOST_CLOSURE_AUX_SYMBOL( (init_call) )

#define BOOST_CLOSURE_AUX_CODE_FUNCTOR(decl_traits, id, typename01) \
    BOOST_CLOSURE_AUX_CODE_FUNCTOR_(decl_traits, \
            /* params (might have defaults) */ \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS(decl_traits), \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_PARAMS_DEFAULT_COUNT(decl_traits),\
            /* const bind vars (`this` excluded) */ \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BINDS_WITHOUT_TYPE( \
                    decl_traits), \
            /* if const bind `this` is present */ \
            BOOST_PP_LIST_IS_CONS( \
                    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_CONST_BIND_THIS_TYPES( \
                    decl_traits)), \
            /* bind (non-const) vars (`this` excluded) */ \
            BOOST_CLOSURE_AUX_PP_DECL_TRAITS_BINDS_WITHOUT_TYPE(decl_traits), \
            /* if (non-const) bind `this` is present */ \
            BOOST_PP_LIST_IS_CONS( \
                    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES( \
                    decl_traits)), \
            /* etc */ \
            id, typename01)

#endif // #include guard

