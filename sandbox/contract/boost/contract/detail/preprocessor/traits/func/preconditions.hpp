
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/list.hpp>
#include <boost/contract/detail/preprocessor/traits/assertion.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/precondition.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

// For reentrancy on GCC with C++0x.
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_REM_(tokens) tokens

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST(sign, \
                    0, /* might not be empty */ \
                    0, /* might not have defaults */ \
                    BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_FRONT, \
                    BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRECONDITION_REMOVE_FRONT,\
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_REM_))

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_REMOVE_precondition \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_SIGN_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRECONDITION_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_REMOVE_)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_PRECONDITIONS(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS_SIGN_)

// PUBLIC //

// Expand to pp-list of precondition assertions.
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS(func_traits) \
    BOOST_PP_ARRAY_ELEM(20, func_traits)

#endif // #include guard

