
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/list.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/requires.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_TRAIT_COMMA_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(BOOST_PP_TUPLE_REM(1), sign)

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST(sign, \
            0, /* might not be empty */ \
            0, /* might not have defaults */ \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_REQUIRES_REMOVE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_TRAIT_COMMA_)

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_REMOVE_requires \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_SIGN_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_REMOVE_)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_CONCEPTS(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS_SIGN_)

// PUBLIC //

// Expand to pp-list of concept types `(n, (concept_token0, ...))` (array for
// unwrapped commas).
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_CONCEPTS(class_traits) \
    BOOST_PP_ARRAY_ELEM(3, class_traits)

#endif // #include guard

