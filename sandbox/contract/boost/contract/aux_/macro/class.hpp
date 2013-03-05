
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CLASS_HPP_
#define BOOST_CONTRACT_AUX_CLASS_HPP_

#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/aux_/config.hpp>
#include <boost/contract/aux_/symbol.hpp>
#include <boost/contract/aux_/constructor_inits_eval.hpp>
#include <boost/contract/aux_/constructor_try_block_guard.hpp>
#include <boost/contract/aux_/call/constructor_entry.hpp>
#include <boost/contract/aux_/macro/code_/typename.hpp>
#include <boost/contract/aux_/macro/code_/template.hpp>
#include <boost/contract/aux_/macro/code_/named_params_class_template.hpp>
#include <boost/contract/aux_/macro/code_/class_concept.hpp>
#include <boost/contract/aux_/macro/code_/base.hpp>
#include <boost/contract/aux_/macro/code_/class.hpp>
#include <boost/contract/aux_/macro/code_/class_final.hpp>
#include <boost/contract/aux_/macro/code_/class_invariant_const.hpp>
#include <boost/contract/aux_/macro/code_/class_invariant_const_volatile.hpp>
#include <boost/contract/aux_/macro/code_/class_invariant_static.hpp>
#include <boost/contract/detail/preprocessor/traits/class.hpp> // c
#include <boost/contract/detail/preprocessor/traits/base.hpp> // b
#include <boost/contract/detail/preprocessor/keyword/class.hpp>
#include <boost/utility/identity_type.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp> // For SEQ_TAIL.
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/at.hpp>
#include <boost/preprocessor/list/enum.hpp>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>

// PRIVATE //

// Bases.

// Precondition: size(nilseq) > 1.
#define BOOST_CONTRACT_AUX_CLASS_BASES_FROM_NILSEQ_ENUM_(nilseq) \
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TAIL(nilseq)) // TAIL ignores leading NIL.

#define BOOST_CONTRACT_AUX_CLASS_BASES_FROM_NILSEQ_(nilseq) \
    BOOST_PP_IIF(BOOST_PP_GREATER(BOOST_PP_SEQ_SIZE(nilseq), 1), \
        : /* inherit symbol */ \
        BOOST_CONTRACT_AUX_CLASS_BASES_FROM_NILSEQ_ENUM_ \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(nilseq)

#define BOOST_CONTRACT_AUX_CLASS_TEMPALTE_SPECIALIZATION_(c) \
    /* template specialization params */ \
    BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS(c)), \
        < \
    ) \
    BOOST_PP_LIST_ENUM( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS(c)) \
    BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS(c)), \
        > \
    )

#define BOOST_CONTRACT_AUX_CLASS_TYPE_(tpl, c) \
    BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME(tpl, c) \
    /* remove and then add reference to handle abstract types */ \
    ::boost::remove_reference< \
        BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME(tpl, c) \
        /* use IDENTITY_TYPE because eventual tparams separated by commas */ \
        BOOST_IDENTITY_TYPE(( \
            BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME(tpl, c) \
            ::boost::add_reference< \
                /* the actual class type (with eventual tparams) */ \
                BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME(c) \
                /* either template specialization types... */ \
                BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
                        BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS( \
                                c)), \
                    BOOST_CONTRACT_AUX_CLASS_TEMPALTE_SPECIALIZATION_ \
                , \
                    BOOST_PP_TUPLE_EAT(1) \
                )(c) \
                /* ... or, template parameter types */ \
                BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
                        BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS( \
                                c)), \
                    BOOST_PP_TUPLE_EAT(1) \
                , \
                    BOOST_CONTRACT_AUX_CODE_TEMPLATE_INSTANCE \
                )(BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS( \
                                c))) \
            >::type \
        )) \
    >::type

#define BOOST_CONTRACT_AUX_CLASS_INVARIANTS_(id, tpl, c) \
    /* subcontract only from base classes that have been also contracted */ \
    public: \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_CLASS_INVARIANT_FROM_BASES( \
            id, tpl, c) \
    /* class invariant (const, volatile, and static) functions must be */ \
    /* def here because they need to be public for subcontracting and for */ \
    /* class INVARIANT macro will always expand in private context (because */ \
    /* INVARIANT macro does not know enclosing scope access level) */ \
    public: \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_STATIC(id, tpl) \
    public: \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_VOLATILE( \
            id, tpl) \
    public: \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST(id, tpl)

#define BOOST_CONTRACT_AUX_CODE_CLASS_TEMPLATE_POSITIONAL_DECL_( \
        template01, tparams) \
    BOOST_CONTRACT_AUX_CODE_TEMPLATE_DECL(template01, \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL(tparams))

// Precondition: c must only contain positional template params.
#define BOOST_CONTRACT_AUX_CLASS_(id, tpl, c, maybe_named_c) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS(c))), \
        /* if nested class (has access) then nested concepts, etc private */ \
        private: \
    ) \
    /* base class to check concepts */ \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS(c)), \
        BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT \
    , \
        BOOST_PP_TUPLE_EAT(3) \
    )(id, tpl, c) \
    /* access level (for nested classes only) */ \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS(c) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_ACCESS(c))), \
        : \
    ) \
    /* template params (either positional or named) */ \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS(BOOST_PP_LIST_APPEND( \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS( \
                    maybe_named_c)), \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS( \
                    maybe_named_c)))), \
        BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_DECL \
    , \
        BOOST_CONTRACT_AUX_CODE_CLASS_TEMPLATE_POSITIONAL_DECL_ \
    )(BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_IS_TEMPLATE(c), \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS( \
                    maybe_named_c)) \
    /* class or struct plus name */ \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND(c) \
    BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME(c) \
    BOOST_CONTRACT_AUX_CLASS_TEMPALTE_SPECIALIZATION_(c) \
    /* base classes */ \
    BOOST_CONTRACT_AUX_CLASS_BASES_FROM_NILSEQ_( \
        (BOOST_PP_NIL) /* nil-seq (handle empty seq)*/ \
        /* named params initialization for constructors, must be 1st base */ \
        /* because params can be used in constructor-try-block (always */ \
        /* present because named params used independently from contracts) */ \
        ( /* seq elem */ \
            /* private inheritance because impl detail and virtual to */ \
            /* avoid that user virtual bases be init before this one */ \
            /* (no typename here, bases always types) */ \
            private virtual BOOST_IDENTITY_TYPE(( \
                    ::contract::aux::constructor_inits_eval< \
                  BOOST_CONTRACT_AUX_CLASS_TYPE_(tpl, c) \
                , ::contract::aux::constructor_inits_eval_named_params_args_set\
            >)) \
        ) \
        /* enable/disable constructor-try-blocks, must be 2nd base because */ \
        /* used when base initializers fail) */ \
        BOOST_PP_EXPR_IIF( \
                BOOST_PP_BITOR( \
                      BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , BOOST_PP_BITOR( \
                          BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                        , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
                      ) \
                ), \
            ( /* seq elem */ \
                /* private inheritance because impl detail and virtual to */ \
                /* avoid that user virtual bases be init before this one */ \
                private virtual ::contract::aux::constructor_try_block_guard< \
                        BOOST_CONTRACT_AUX_CLASS_TYPE_(tpl, c) > \
            ) \
        ) \
        /* check concepts (after constructor-try-block just in case of some */ \
        /* run-time error even if there should not be any because this */ \
        /* class only performs compile-time static checks for concepts) */ \
        BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
                BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS(c)), \
            BOOST_CONTRACT_AUX_CODE_CLASS_CONCEPT_BASE_SEQ \
        , \
            BOOST_PP_TUPLE_EAT(3) \
        )(id, tpl, c) \
        /* constr inv/pre must be 1st base so to check constr inv/pre 1st */ \
        /* (but after concepts because they are static checks) */ \
        BOOST_PP_EXPR_IIF( \
                BOOST_PP_BITOR( \
                      BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
                ), \
            /* this also takes the class type so to be a unique base type */ \
            /* when also base classes have contracts (virtual bases cannot */ \
            /* be used here because they are constructed only one time for */ \
            /* the entire inheritance tree so preventing bases from */ \
            /* they constructor contract entry (preconditions, etc) */ \
            ( /* seq elem */ \
                /* private inheritance because impl detail and virtual to */ \
                /* avoid that user virtual bases be init before this one */ \
                private virtual ::contract::aux::call_constructor_entry< \
                        BOOST_CONTRACT_AUX_CLASS_TYPE_(tpl, c) > \
            ) \
        ) \
        /* must be before user-defined bases (so if they throw, constructor */ \
        /* try-block will catch) */ \
        BOOST_PP_EXPR_IIF( \
                BOOST_PP_BITOR( \
                      BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , BOOST_PP_BITOR( \
                          BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                        , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
                      ) \
                ), \
            ( /* seq elem */ \
                /* private inheritance because impl detail and virtual to */ \
                /* avoid that user virtual bases be init before this one */ \
                /* (no typename here, bases always types) */ \
                private virtual BOOST_IDENTITY_TYPE(( \
                        ::contract::aux::constructor_inits_eval< \
                      BOOST_CONTRACT_AUX_CLASS_TYPE_(tpl, c) \
                    , ::contract::aux::constructor_inits_eval_try_block_set \
                >)) \
            ) \
        ) \
        /* user specified base classes (if any) */ \
        BOOST_PP_LIST_FOR_EACH(BOOST_CONTRACT_AUX_CODE_BASE_SEQ_R, \
                BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME(tpl, c), \
                BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES(c)) \
    ) \
    { /* class definition */ \
        /* this class typedef (needed by named params even if no contracts) */ \
        private: typedef BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME(c) \
                BOOST_CONTRACT_AUX_CODE_CLASS_TYPE; \
        /* base typedefs for other contract macros (only if contracts) */ \
        BOOST_PP_IIF( \
                BOOST_PP_BITOR( \
                      BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , BOOST_PP_BITOR( \
                          BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                        , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
                      ) \
                ), \
            BOOST_PP_REPEAT \
        , \
            BOOST_PP_TUPLE_EAT(3) \
        )(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
                BOOST_CONTRACT_AUX_CODE_BASE_TYPEDEF_Z, c)\
        BOOST_PP_IIF(BOOST_PP_GREATER(BOOST_PP_LIST_SIZE( \
                BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES(c)), \
                BOOST_CONTRACT_CONFIG_INHERITANCE_MAX),\
            BOOST_CONTRACT_AUX_MPL_ASSERT_MSG \
        , \
            BOOST_PP_TUPLE_EAT(3) \
        )( \
              false \
            , \
  ERROR_too_many_base_classes_see_BOOST_CONTRACT_CONFIG_INHERITANCE_MAX \
            , () \
        ); /* need trailing `;` */ \
        /* class invariants */ \
        BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01, \
            BOOST_CONTRACT_AUX_CLASS_INVARIANTS_ \
        , \
            BOOST_PP_TUPLE_EAT(3) \
        )(id, tpl, c) \
        /* handle final classes */ \
        BOOST_CONTRACT_AUX_CODE_CLASS_FINAL(id, tpl, c) \
        /* restore class/struct private/public access level */ \
        BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT( \
                BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND(c)), \
            private: /* class ... */\
        , \
            public : /* struct ... */ \
        ) \
        /* terminate with struct to allow user to follow macro with { */ \
        /* (enum could be used too but struct gives better errors if */ \
        /* INVARIANT macro is not used, unnamed struct so it cannot be */ \
        /* used by mistake) */ \
        struct /* BOOST_CONTRACT_CLASS_INVARIANT macro must follow */

// PUBLIC //

#define BOOST_CONTRACT_AUX_CLASS(id, tpl, c) \
    BOOST_CONTRACT_AUX_CLASS_( \
          id \
        , tpl \
        , BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS(BOOST_PP_LIST_APPEND( \
                BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                        BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS( \
                                c)), \
                BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                        BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS( \
                                c)))), \
            BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_CLASS_TEMPLATE_POSITIONAL_C \
          , \
            BOOST_PP_TUPLE_REM(1) \
          )(c) \
        , c \
    )

#endif // #include guard

