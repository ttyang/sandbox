
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_CONSTRUCTOR_ENTRY_HPP_
#define BOOST_CONTRACT_AUX_CODE_CONSTRUCTOR_ENTRY_HPP_

#include <boost/contract/aux_/macro/code_/typename.hpp>
#include <boost/contract/aux_/macro/code_/precondition.hpp>
#include <boost/contract/aux_/call/constructor_entry.hpp>
#include <boost/contract/aux_/constructor_try_block_guard.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_CONSTRUCTOR_ENTRY_COMMA_PARAM_NAME_( \
        r, tpl, p) \
    , BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)
                
#define BOOST_CONTRACT_AUX_CODE_CONSTRUCTOR_ENTRY_COMMA_PRECONDITION_( \
        id, tpl, k, f) \
    , \
    & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
            BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC(id, tpl, k, f) \
            BOOST_CONTRACT_AUX_CODE_TEMPLATE_INSTANCE( \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
  BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f)))

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_CONSTRUCTOR_ENTRY(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01, \
            BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01), \
        ( /* a pp-list to be used with constructor member initializers */ \
            /* POLICY: constructor preconditions and static class */ \
            /* invariants are checked using an artificial base class and */ \
            /* the 1st initializer so the checks happen before executing */ \
            /* other base and member initializers */ \
            ::contract::aux::call_constructor_entry< \
                BOOST_CONTRACT_AUX_CODE_CLASS_TYPE \
            >( \
                BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __FILE__)\
                BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
                BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __LINE__)\
                BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
                BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
                    BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f)() \
                BOOST_PP_LIST_FOR_EACH( \
  BOOST_CONTRACT_AUX_CODE_CONSTRUCTOR_ENTRY_COMMA_PARAM_NAME_, \
                        tpl, \
                        BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS( \
                                        f))) \
                /* call func to check this object (not all) pre, static inv */ \
                BOOST_PP_COMMA_IF( \
                        BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01) \
                BOOST_PP_EXPR_IIF( \
                        BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01, \
                    & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
                            BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC\
                ) \
                BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01, \
  BOOST_CONTRACT_AUX_CODE_CONSTRUCTOR_ENTRY_COMMA_PRECONDITION_ \
                , \
                    BOOST_PP_TUPLE_EAT(4) \
                )(id, tpl, k, f) \
            ) \
        , \
            BOOST_PP_NIL \
        ) \
    , \
        BOOST_PP_NIL /* no constructor preconditions or invariants */\
    )

#endif // #include guard

