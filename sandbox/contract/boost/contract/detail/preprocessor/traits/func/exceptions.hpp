
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/list.hpp>
#include <boost/contract/detail/preprocessor/keyword/throw.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_TRAIT_COMMA_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(BOOST_PP_TUPLE_REM(1), sign)

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_TRAIT_(sign) \
    ( \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_THROW_FRONT(sign) \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST(sign, \
                /* empty list from both `throw( )` and `throw( void )` */ \
                1, /* might be empty (for non-throw specification) */ \
                0, /* might not have defaults */ \
                BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_THROW_FRONT, \
                BOOST_CONTRACT_DETAIL_PP_KEYWORD_THROW_REMOVE_FRONT, \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_TRAIT_COMMA_) \
    )

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_REMOVE_throw \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_SIGN_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_THROW_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_REMOVE_)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_EXCEPTIONS(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS_SIGN_)

// PUBLIC //

// Expand to 1 iff it has exception specifications (even if no exceptions 
// `throw()` for no-throw)
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_HAS_EXCEPTION_SPEC(func_traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_ARRAY_ELEM(19, func_traits))

// Expand to pp-list of exception specification types
// `(n, (exception_token0, ...))` (array to handle unwrapped commas).
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXCEPTIONS(func_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_ARRAY_ELEM(19, func_traits))

#endif // #include guard

