
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/*************************************************************/
/* WARNING:  FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "<FILE>-generate.py" */
/*************************************************************/
// Used: #define BOOST_CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES 10

#ifndef BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_HPP_
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_HPP_

#include <boost/contract/limits.hpp>
#if BOOST_CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES != 10
#   error "Code generation used incorrect BOOST_CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES"
#endif

#include <boost/contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <boost/contract/detail/preprocessor/keyword/catch.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_STATEMENTS_(statements) \
    /* beginning of seq elem of 3-tuple from DECL_catch here */ \
    statements)), /* this comma splits */

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_catch( \
        exception_decl) \
    ( ( \
        exception_decl \
    , \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_STATEMENTS_ \
    /* end of seq elem of 3-tuple from STATEMENTS_ here */

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_9_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        ERROR_support_maximum_of_10_catch_statements \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_9_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_9_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_8_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_9_ \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_8_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_8_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_7_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_8_ \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_7_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_7_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_6_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_7_ \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_6_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_6_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_5_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_6_ \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_5_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_5_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_4_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_5_ \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_4_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_4_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_3_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_4_ \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_3_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_3_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_2_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_3_ \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_2_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_2_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_1_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_2_ \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_1_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_1_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_( \
        seq_sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_1_ \
    , \
        seq_sign BOOST_PP_TUPLE_EAT(2) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_( \
        seq, sign) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT_( ( \
        seq BOOST_PP_CAT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, \
                sign) \
    ) ) 

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_LIST_(sign) \
    BOOST_CONTRACT_DETAIL_PP_SEQ_TO_LIST_NEVER_EMPTY( \
            BOOST_PP_TUPLE_ELEM(2, 0, \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_( \
                            BOOST_PP_EMPTY(), sign)))

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_(sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT(sign), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_LIST_ \
    , \
        BOOST_PP_NIL BOOST_PP_TUPLE_EAT(1) /* empty catch list */ \
    )(sign)
        
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_REMOVE_(sign) \
    BOOST_PP_TUPLE_ELEM(2, 1, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_( \
                    BOOST_PP_EMPTY(), sign))

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_SIGN_(sign) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT(sign), \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_REMOVE_ \
    , \
        sign BOOST_PP_TUPLE_EAT(1) \
    )(sign)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CATCHES(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_SIGN_)

// PUBLIC //

// Expand to pp-list of catch traits `(exception_decl, statements)`.
#define BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES(func_traits) \
    BOOST_PP_ARRAY_ELEM(23, func_traits)

// Expand to either `exception_type exception_var` or `...`.
#define BOOST_CONTRACT_DETAIL_PP_CATCH_TRAITS_EXCEPTION_DECL(catch_traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, catch_traits)

// Expand to `instruction; instruction; ...` (all instructions optional).
#define BOOST_CONTRACT_DETAIL_PP_CATCH_TRAITS_STATEMENTS(catch_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, catch_traits)

#endif // #include guard

