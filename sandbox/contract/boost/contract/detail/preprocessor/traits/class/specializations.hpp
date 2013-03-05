
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/list.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

// For reentrancy on GCC with C++0x.
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_REM_(tokens) \
    tokens

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_OPTIONAL_LIST(sign, \
            0, /* might not be empty (when present) */ \
            0, /* might not have defaults */ \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_REM_)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_SPECIALIZATIONS(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_OPTIONAL_LIST)

// PUBLIC //

// Expand to pp-list of template specialization types (empty iff the class is
// not a template specialization).
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_SPECIALIZATIONS(class_traits) \
    BOOST_PP_ARRAY_ELEM(7, class_traits)

#endif // #include guard

