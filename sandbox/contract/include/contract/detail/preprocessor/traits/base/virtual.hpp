
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_BASE_TRAITS_VIRTUAL_HPP_
#define CONTRACT_DETAIL_PP_BASE_TRAITS_VIRTUAL_HPP_

#include <contract/detail/preprocessor/traits/aux_/apply_1.hpp>
#include <contract/detail/preprocessor/traits/aux_/keyword.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <contract/detail/preprocessor/keyword/virtual.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_BASE_TRAITS_VIRTUAL_TRAIT_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    CONTRACT_DETAIL_PP_TRAITS_AUX_KEYWORD(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL_FRONT, virtual) \

#define CONTRACT_DETAIL_PP_BASE_TRAITS_VIRTUAL_SIGN_(sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_KEYWORD(sign, \
            CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_REMOVE_FRONT)

// PROTECTED //

#define CONTRACT_DETAIL_PP_BASE_TRAITS_AUX_VIRTUAL(traits_sign) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_1(traits_sign, \
            CONTRACT_DETAIL_PP_BASE_TRAITS_VIRTUAL_TRAIT_, \
            CONTRACT_DETAIL_PP_BASE_TRAITS_VIRTUAL_SIGN_)

// PUBLIC //

// Expand to `[virtual]`.
#define CONTRACT_DETAIL_PP_BASE_TRAITS_VIRTUAL(base_traits) \
    BOOST_PP_CAT(CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(1, base_traits))

#endif // #include guard

