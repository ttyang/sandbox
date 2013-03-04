
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES_HPP_

#include <boost/contract/detail/preprocessor/traits/base.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/list.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/extends.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST(sign, \
            0, /* might not be empty */ \
            0, /* might not have defaults */ \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_EXTENDS_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_EXTENDS_REMOVE_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_BASE_TRAITS)

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES_REMOVE_extends \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES_SIGN_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_EXTENDS_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES_REMOVE_)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_BASES(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES_SIGN_)

// PUBLIC //

// Expand to pp-list of base classes (see `BASE_CLASS_TRAITS` macros).
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES(class_traits) \
    BOOST_PP_ARRAY_ELEM(9, class_traits)

#endif // #include guard

