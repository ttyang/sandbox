
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/*************************************************************/
/* WARNING:  FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "<FILE>-generate.py" */
/*************************************************************/
// Used maximum number of iterations: 1

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_HPP_

#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/array/data.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PRIVATE //

// From BOOST_PP_ARRAY_PUSH_BACK.
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_( \
            array, elem) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_I_( \
                BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
#else
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_( \
            array, elem) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_D_(array, elem)
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_D_( \
            array, elem) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_I_( \
                BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
#endif
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_I_( \
        size, data, elem) \
    ( \
        BOOST_PP_INC(size) \
    , \
        (BOOST_PP_TUPLE_REM(size) data BOOST_PP_COMMA_IF(size) elem) \
    )

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_INIT( \
        traits_sign, trait_macro, sign_macro) \
    ( \
        ( 1 /* create 1-array */, ( trait_macro( \
          BOOST_PP_TUPLE_ELEM(2, 1, traits_sign)) ) ) \
    , \
        sign_macro(BOOST_PP_TUPLE_ELEM(2, 1, traits_sign)) \
    )

// Expand to next `traits_sign` applying `trait_macro(sign)` and
// `sign_macro(macro)`.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY( \
        traits_sign, trait_macro, sign_macro) \
    ( \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ARRAY_PUSH_BACK_( \
                BOOST_PP_TUPLE_ELEM(2, 0, traits_sign), \
                trait_macro(BOOST_PP_TUPLE_ELEM(2, 1, traits_sign))) \
    , \
        sign_macro(BOOST_PP_TUPLE_ELEM(2, 1, traits_sign)) \
    )

#endif // #include guard

