
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_FINAL_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_FINAL_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/keyword.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/contract/detail/preprocessor/keyword/cxx11/final.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_FINAL_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_FINAL_FRONT, final)

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_FINAL_SIGN_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_FINAL_REMOVE_FRONT)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_FINAL(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_FINAL_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_FINAL_SIGN_)

// PUBLIC //

// Expand to `[final]`.
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_FINAL(class_traits) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(8, class_traits))

#endif // #include guard

