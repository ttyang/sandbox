
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_OLDOF_HPP_
#define BOOST_CONTRACT_AUX_CODE_OLDOF_HPP_

#include <boost/contract/aux_/bind_old.hpp>
#include <boost/contract/aux_/subboost/contract/oldof.hpp>
#include <boost/contract/aux_/macro/code_/oldof_type.hpp>
#include <boost/contract/aux_/macro/code_/postcondition.hpp>
#include <boost/contract/detail/preprocessor/traits/func.hpp> // f
#include <boost/contract/detail/preprocessor/traits/func_param.hpp> // p
#include <boost/contract/detail/preprocessor/traits/oldof.hpp> // o
#include <boost/function.hpp>
#include <list>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_OLDOF_COMMA_PARAM_DECL_(r, tpl_f, p) \
    , \
    BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(BOOST_PP_TUPLE_ELEM(2, 0, tpl_f), \
            BOOST_PP_TUPLE_ELEM(2, 1, tpl_f)) \
    ::contract::aux::arg_const< \
        BOOST_PP_ARRAY_ENUM(BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p))\
    >::type \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define BOOST_CONTRACT_AUX_CODE_OLDOF_COMMA_PARAM_NAME_(r, unused, p) \
    , \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define BOOST_CONTRACT_AUX_CODE_OLDOF_COMMA_TYPE_(r, tpl_f, i, o) \
    , \
    BOOST_CONTRACT_AUX_CODE_OLDOF_TYPE( \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME01 tpl_f, o, i)

#define BOOST_CONTRACT_AUX_CODE_NOOLD_COMMA_TYPE_(z, n, unused) \
    , \
    ::contract::aux::void_old

#define BOOST_CONTRACT_AUX_CODE_OLDOF_COMMA_EXPR_(r, unused, o) \
    , \
    BOOST_CONTRACT_DETAIL_PP_OLDOF_TRAITS_EXPR(o)

#define BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_TYPEDEFS_YES_(r, tpl_f, i, o)\
    typedef \
        BOOST_CONTRACT_AUX_CODE_OLDOF_DEDUCE_AUTO_TYPE( \
                BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME01 tpl_f, o, i) \
        BOOST_CONTRACT_AUX_CODE_OLDOF_TYPE( \
                BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME01 tpl_f, o, i) \
    ;

#define BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_TYPEDEFS_(r, tpl_f, i, o) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            BOOST_CONTRACT_DETAIL_PP_OLDOF_TRAITS_TYPE(o)), \
        BOOST_PP_TUPLE_EAT(4) /* explicit old-of type (no `auto`) */ \
    , \
        BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_TYPEDEFS_YES_ \
    )(r, tpl_f, i, o)

// Expand to nothing if old-of type is not `auto`, otherwise deduce types.
#define BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_(id, tpl, k, f) \
    BOOST_PP_LIST_FOR_EACH_I( \
            BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_TYPEDEFS_, \
            (tpl, f), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(f))

#define BOOST_CONTRACT_AUX_CODE_OLDOF_PARAM_OBJ_ \
    BOOST_CONTRACT_AUX_SYMBOL( (obj) )

#define BOOST_CONTRACT_AUX_CODE_OLDOF_PARAMS_DECL_( \
        id, tpl, k, f, oldof_auto_types) \
    ( \
        /* function_type for a dummy param used to resolve overloading */ \
        /* (because pre add const to args and obj so it might have same */ \
        /* signature as of overloaded func with const arg and obj) */ \
        /* not named so it cannot be used by mistake */ \
        BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
        BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f)::body_type \
        /* constructor have static old-of but non-static post so this is */ \
        /* not accessible from static old-of but obj needs to be passed */ \
        /* as a func param so it can be bound to post func */ \
        BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k)) \
        BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            BOOST_CONTRACT_AUX_CODE_CLASS_TYPE const* const \
            BOOST_CONTRACT_AUX_CODE_OLDOF_PARAM_OBJ_ \
        ) \
        /* params and objects are provided because some of the old-of */ \
        /* expr can depend on them (but they must be used as const) */ \
        /* all params are const (and ref) for const-correctness */ \
        BOOST_PP_LIST_FOR_EACH( \
                BOOST_CONTRACT_AUX_CODE_OLDOF_COMMA_PARAM_DECL_, (tpl, f), \
                BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
    ) \
    BOOST_PP_EXPR_IIF( \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f),\
        const /* const obj for const-correctness (unless static) */ \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f)

#define BOOST_CONTRACT_AUX_CODE_OLDOF_(id, tpl, k, f, oldof_auto_types) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), \
        private: \
    ) \
    BOOST_CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL( \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
                    k, f)), \
        /* POLICY: static also for constructor because no obj yet exists */ \
        /* when evaluating old-of expr becore ctor body execution */ \
        static \
    ) \
    BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) :: \
            bound_postcondition_type \
    BOOST_CONTRACT_AUX_CODE_OLDOF_FUNC(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_OLDOF_PARAMS_DECL_( \
            id, tpl, k, f, oldof_auto_types) \
    { \
        BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPEOF_(id, tpl, k, f) \
        return ::contract::aux::bind_old< \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
                    BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) :: \
                    body_type \
            BOOST_PP_LIST_FOR_EACH_I(BOOST_CONTRACT_AUX_CODE_OLDOF_COMMA_TYPE_,\
                    (tpl, f), \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS( \
                            f)) \
            BOOST_PP_REPEAT(BOOST_PP_SUB(BOOST_CONTRACT_CONFIG_OLDOF_MAX, \
                    BOOST_PP_LIST_SIZE( \
  BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS( \
                        f))), \
                    BOOST_CONTRACT_AUX_CODE_NOOLD_COMMA_TYPE_, ~) \
        >( \
            /* post function to bind */ \
            & /* func ptr */ \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), \
                BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
            ) \
            BOOST_PP_EXPR_IIF( \
                    /* post is a func tpl ptr iif oldof_auto_types != nil */ \
                    /* or func template then use template prefix only */ \
                    /* for members in type-dependent context */ \
                    BOOST_PP_BITAND( \
                          tpl \
                        , BOOST_PP_BITAND( \
                              BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f) \
                            , BOOST_PP_BITOR( \
                                  BOOST_PP_LIST_IS_CONS(oldof_auto_types) \
  , BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f)\
                            ) \
                        ) \
                    ), \
                template \
            ) \
            BOOST_CONTRACT_AUX_CODE_POSTCONDITION_FUNC(id, tpl, k, f) \
            BOOST_PP_EXPR_IIF(BOOST_PP_BITOR( \
                    BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                    BOOST_PP_LIST_IS_CONS( \
                            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
  BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                                    f)))), \
                < \
            ) \
                BOOST_PP_LIST_ENUM(oldof_auto_types) \
                BOOST_PP_COMMA_IF(BOOST_PP_BITAND( \
                        BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                        BOOST_PP_LIST_IS_CONS( \
  BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
  BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(\
                                f))))) \
                BOOST_CONTRACT_AUX_CODE_TEMPLATE_PARAM_NAME_ENUM( \
                        BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                                f))) \
            BOOST_PP_EXPR_IIF(BOOST_PP_BITOR( \
                    BOOST_PP_LIST_IS_CONS(oldof_auto_types), \
                    BOOST_PP_LIST_IS_CONS( \
                            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
  BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                                    f)))), \
                > \
            ) \
            /* object (only for non-static member and ctor) */ \
            BOOST_PP_COMMA_IF( \
  BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f)) \
            BOOST_PP_EXPR_IIF( \
  BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f), \
                this \
            ) \
            BOOST_PP_COMMA_IF( \
                    BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k)) \
            BOOST_PP_EXPR_IIF( \
                    BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
                /* constructor old-of are static (because no obj exist yet) */ \
                /* but constructor post are not static (because obj exist) */ \
                /* so special param (not this) is used to bind obj to post */ \
                BOOST_CONTRACT_AUX_CODE_OLDOF_PARAM_OBJ_ \
            ) \
            /* old values */ \
            BOOST_PP_LIST_FOR_EACH(BOOST_CONTRACT_AUX_CODE_OLDOF_COMMA_EXPR_, \
                    ~, \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS( \
                            f)) \
        ); \
    }

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_COMMA_BASE_( \
        z, n, id_tpl_k_f) \
    , dynamic_cast< \
        BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE( \
                BOOST_PP_TUPLE_ELEM(4, 0, id_tpl_k_f), n) \
        const \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE( \
                BOOST_PP_TUPLE_ELEM(4, 3, id_tpl_k_f)) \
        * const \
      >(this) \
    /* call function to bind all (base, base's base, etc) oldofs */ \
    , BOOST_CONTRACT_AUX_CODE_FUNC_PTR( \
          BOOST_PP_TUPLE_ELEM(4, 0, id_tpl_k_f) \
        , BOOST_PP_TUPLE_ELEM(4, 1, id_tpl_k_f) \
        , BOOST_PP_TUPLE_ELEM(4, 2, id_tpl_k_f) \
        , BOOST_PP_TUPLE_ELEM(4, 3, id_tpl_k_f) \
        , BOOST_PP_EXPAND( \
                BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_FUNC \
                id_tpl_k_f) \
        , BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE( \
                BOOST_PP_TUPLE_ELEM(4, 0, id_tpl_k_f), n) \
    )

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_RESULT_TYPE_( \
        id, tpl, k, f) \
    ::std::list< \
        BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
        BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) :: \
                bound_postcondition_type \
    >

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_(id, tpl, k, f) \
    public: /* must be public for subcontracting */ \
    BOOST_CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_RESULT_TYPE_( \
            id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_FUNC(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_OLDOF_PARAMS_DECL_(id, tpl, k, f, oldof_auto_types)\
    { \
        return ::contract::aux::subcontract_oldof< \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) \
        >( \
              this \
            , BOOST_CONTRACT_AUX_CODE_FUNC_PTR(id, tpl, k, f, \
                    BOOST_CONTRACT_AUX_CODE_OLDOF_FUNC(id, tpl, k, f), \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
            BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_COMMA_BASE_, \
                    (id, tpl, k, f)) \
            BOOST_PP_LIST_FOR_EACH( \
                    BOOST_CONTRACT_AUX_CODE_OLDOF_COMMA_PARAM_NAME_, ~, \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
        ); \
    }

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_OLDOF_FUNC(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f), \
            (oldof_))

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_FUNC(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f), \
            (subcontracted_oldof))

#define BOOST_CONTRACT_AUX_CODE_OLDOF(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
        BOOST_PP_TUPLE_EAT(5) \
    , \
        BOOST_CONTRACT_AUX_CODE_OLDOF_ \
    )(id, tpl, k, f, BOOST_CONTRACT_AUX_CODE_OLDOF_AUTO_TYPES( \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME01(tpl, f), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(f))) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
            k, f), \
        BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_ \
    , \
        /* ctor and dtor subcontract via base-class creation rules */ \
        BOOST_PP_TUPLE_EAT(4) \
    )(id, tpl, k, f)

#endif // #include guard

