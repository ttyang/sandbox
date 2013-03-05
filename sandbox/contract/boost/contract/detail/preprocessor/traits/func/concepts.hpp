
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/list.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/requires.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_TRAIT_COMMA_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(BOOST_PP_TUPLE_REM(1), sign)

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST(sign, \
            0, /* might not be empty */ \
            0, /* might not have defaults */ \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_REQUIRES_REMOVE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_TRAIT_COMMA_)

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_REMOVE_requires \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_SIGN_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_REMOVE_)
                
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_INDEX_ 3

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CONCEPTS(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_SIGN_)

// PUBLIC //

// Expand to pp-list of concept types.
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS(func_traits) \
    BOOST_PP_ARRAY_ELEM(BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_INDEX_, \
            func_traits)

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_REPLACE( \
        func_traits, concepts_sign) \
    /* can't use ARRAY_REPLACE because it has reentrancy _D */ \
    ( BOOST_PP_ARRAY_SIZE(func_traits), \
    ( \
  BOOST_CONTRACT_DETAIL_PP_ARRAY_REM(BOOST_CONTRACT_DETAIL_PP_ARRAY_FIRST_N( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_INDEX_, \
                func_traits)) \
        , BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_TRAIT_(concepts_sign) \
  , BOOST_CONTRACT_DETAIL_PP_ARRAY_REM(BOOST_CONTRACT_DETAIL_PP_ARRAY_REST_N( \
                BOOST_PP_INC( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS_INDEX_), \
                func_traits)) \
    ) )

#endif // #include guard

