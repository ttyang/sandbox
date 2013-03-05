
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_VIRTUAL_HPP_
#define BOOST_CONTRACT_AUX_CODE_VIRTAUL_HPP_

#include <boost/contract/aux_/mpl_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_(f) \
    BOOST_CONTRACT_AUX_SYMBOL( (BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f)) \
            (virtual_function_tag) )

#define BOOST_CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_PARAM_TYPE_ENUM_( \
        r, default01, i, p) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
    BOOST_PP_ARRAY_ENUM(BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p))

#define BOOST_CONTRACT_AUX_CODE_VIRTUAL_FUNC_SIGNATURE_(f, name) \
    /* NOTE: virtual functions decl this member func tag which existence */ \
    /* can be checked using the introspection metafunction also def here */ \
    BOOST_CONTRACT_AUX_CODE_RESULT_TYPE(f, \
            0 /* don't allow empty result type */) \
    name \
    ( \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_PARAM_TYPE_ENUM_, ~, \
                BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST(f) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f)

#define BOOST_CONTRACT_AUX_CODE_VIRTUAL_TAG_DECL_(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    BOOST_CONTRACT_AUX_CODE_VIRTUAL_FUNC_SIGNATURE_(f, \
            BOOST_CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_(f)) \
    ; /* no tag func definition needed for SFINAE so `;` */

#define BOOST_CONTRACT_AUX_CODE_VIRTUAL_CHECK_METAFUNC_(id) \
    BOOST_CONTRACT_AUX_SYMBOL( (has_virtual_function_tag)(id) )

#define BOOST_CONTRACT_AUX_CODE_VIRTUAL_CHECK_DEF_(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_HAS_XXX_MEMBER_FUNCTION( \
            BOOST_CONTRACT_AUX_CODE_VIRTUAL_CHECK_METAFUNC_(id), \
            BOOST_CONTRACT_AUX_CODE_VIRTUAL_TAG_FUNC_(f)) \

// PUBLIC //

// Return MPL type true_ or false_.
#define BOOST_CONTRACT_AUX_CODE_HAS_VIRTUAL(id, f, class_type) \
    BOOST_CONTRACT_AUX_CODE_VIRTUAL_CHECK_METAFUNC_(id)< \
        BOOST_CONTRACT_AUX_CODE_VIRTUAL_FUNC_SIGNATURE_(f, (class_type::*)) \
    >

#define BOOST_CONTRACT_AUX_CODE_VIRTUAL_TAG(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VIRTUAL(f)), \
        BOOST_PP_TUPLE_EAT(4) \
    , \
        public: /* must be public to be accessed from intro metafunc */ \
        BOOST_CONTRACT_AUX_CODE_VIRTUAL_TAG_DECL_ \
    )(id, tpl, k, f) \
    private: /* check introspection metafunc can be private */ \
    BOOST_CONTRACT_AUX_CODE_VIRTUAL_CHECK_DEF_(id, tpl, k, f)

#endif // #include guard

