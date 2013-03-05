
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/keyword.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/contract/detail/preprocessor/keyword/public.hpp>
#include <boost/contract/detail/preprocessor/keyword/protected.hpp>
#include <boost/contract/detail/preprocessor/keyword/private.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD3(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_FRONT, public, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED_FRONT, protected, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_FRONT, private)

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS_SIGN_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD3(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_REMOVE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_REMOVE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_REMOVE_FRONT)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_ACCESS(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_INIT(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS_SIGN_)

// PUBLIC //

// Expand to `[public | protected | private]`.
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS(func_traits) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(0, func_traits))

#endif // #include guard

