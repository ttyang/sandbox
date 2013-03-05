
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/keyword.hpp>
#include <boost/contract/detail/preprocessor/keyword/class.hpp>
#include <boost/contract/detail/preprocessor/keyword/struct.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD2(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT, class, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STRUCT_FRONT, struct)

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_SIGN_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD2(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STRUCT_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_STRUCT_REMOVE_FRONT)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_KIND(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND_SIGN_)

// PUBLIC //

// Expand to `class | struct`.
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_KIND(class_traits) \
    BOOST_PP_ARRAY_ELEM(5, class_traits)

#endif // #include guard

