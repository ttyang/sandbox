
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_TYPENAME_HPP_
#define BOOST_CONTRACT_AUX_CODE_TYPENAME_HPP_

#include <boost/contract/detail/preprocessor/traits/class.hpp> // c
#include <boost/contract/detail/preprocessor/traits/func.hpp> // f
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/bitor.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_TYPENAME01_(tpl, params) \
    /* the typename keyword should be used to resolve nested type */ \
    /* expressions if the enclosing scope is a template (tpl is 1) or */ \
    /* the declared class or function has non-empty template parameters */ \
    /* (template specializations with empty template parameters will still */ \
    /* be templates (...TRAITS_IS_TEMPLATE is 1) but they do not make for */ \
    /* a type-dependent scope so the actual template parameters are used) */ \
    BOOST_PP_BITOR( \
          tpl \
        , BOOST_PP_BITOR( \
              BOOST_PP_LIST_IS_CONS( \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL(params)) \
            , BOOST_PP_BITOR( \
                  BOOST_PP_LIST_IS_CONS( \
                        BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED(params)) \
                , BOOST_PP_LIST_IS_CONS( \
                        BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED(params)) \
            ) \
        ) \
    )

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME01(tpl, c) \
    BOOST_CONTRACT_AUX_CODE_TYPENAME01_(tpl, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_TEMPLATE_PARAMS(c))

#define BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME(tpl, c) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CODE_CLASS_TYPENAME01(tpl, c), \
            typename)

#define BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME01(tpl, f) \
    BOOST_CONTRACT_AUX_CODE_TYPENAME01_(tpl, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))

#define BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME01(tpl, f), \
            typename)

#endif // #include guard

