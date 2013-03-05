
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/name.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_AUX_NAME(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME)

// PUBLIC //

// Expand to `class_name`.
#define BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS_NAME(class_traits) \
    BOOST_PP_ARRAY_ELEM(6, class_traits)

#endif // #include guard

