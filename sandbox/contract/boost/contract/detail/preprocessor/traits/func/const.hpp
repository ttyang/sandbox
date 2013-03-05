
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST_HPP_
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/keyword.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/contract/detail/preprocessor/keyword/const.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_FRONT, const)

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST_SIGN_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CONST(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST_SIGN_)

// PUBLIC //

// Expand to `[const]`.
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST(func_traits) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(14, func_traits))

#endif // #include guard

