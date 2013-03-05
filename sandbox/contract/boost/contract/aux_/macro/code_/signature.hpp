
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_SIGNATURE_HPP_
#define BOOST_CONTRACT_AUX_CODE_SIGNATURE_HPP_

#include <boost/contract/aux_/symbol.hpp>
#include <boost/contract/aux_/signature_traits.hpp>
#include <boost/contract/detail/preprocessor/traits/func.hpp> // f
#include <boost/contract/detail/preprocessor/traits/func_param.hpp> // p
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_SIGNATURE_PARAM_TYPE_ENUM_(r, unused, i, p) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_ARRAY_ENUM(BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p))

#define BOOST_CONTRACT_AUX_CODE_SIGNATURE_COMMA_SUBBOOST_CONTRACTED_BASE_TYPE_(\
        z, n, id) \
    , \
    BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE(id, n)

#define BOOST_CONTRACT_AUX_CODE_SIGNATURE_CLASS_(id, tpl, k, f) \
    /* this symbol is unique because of id (it cannot be made unique */ \
    /* without id, for example just using the func and param names, */ \
    /* because overloaded func will have same func name, param name, etc) */ \
    /* NOTE: f's name is still needed because free func in same namespace */ \
    /* and decl on same line will have same id in same namespace */ \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f), \
            (signature_traits)(id))

// PUBLIC //

// In type-dependent context, this must be prefixed by typename.
#define BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_SIGNATURE_CLASS_(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_TEMPLATE_INSTANCE( \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    ::type

#define BOOST_CONTRACT_AUX_CODE_SIGNATURE(id, tpl, k, f) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), \
        private: \
    ) \
    BOOST_CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    struct BOOST_CONTRACT_AUX_CODE_SIGNATURE_CLASS_(id, tpl, k, f) { \
        typedef \
            BOOST_PP_IIF( \
  BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
                            k, f), \
                ::contract::aux::derived_signature_traits \
            , \
                ::contract::aux::signature_traits \
            ) \
            < \
                BOOST_CONTRACT_AUX_CODE_RESULT_TYPE(f, 0 /* no empty result */)\
                /* function (eventually member function) pointer type */ \
                ( \
                    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR( \
  BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(\
                                    k, f) \
                            , BOOST_PP_BITOR( \
    BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k) \
  , BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k) \
                            )), \
                        BOOST_CONTRACT_AUX_CODE_CLASS_TYPE:: \
                    ) \
                    * \
                ) \
                /* function argument types */ \
                ( \
                    BOOST_PP_LIST_FOR_EACH_I( \
                            BOOST_CONTRACT_AUX_CODE_SIGNATURE_PARAM_TYPE_ENUM_,\
                            ~, \
                            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
  BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
                ) \
                /* cv-qualifiers */ \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST(f) \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f) \
                /* base class types (only for subcontracting) */ \
                BOOST_PP_IIF( \
  BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f), \
                    BOOST_PP_REPEAT \
                , \
                    BOOST_PP_TUPLE_EAT(3) \
                )(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
  BOOST_CONTRACT_AUX_CODE_SIGNATURE_COMMA_SUBBOOST_CONTRACTED_BASE_TYPE_,\
                        id) \
            > \
            type \
        ; /* typedef end */ \
    }; /* struct end */

#endif // #include guard

