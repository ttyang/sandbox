
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/assertion.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/select_assertion_1.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/requires.hpp>
#include <boost/contract/detail/preprocessor/keyword/if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/fold_left.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_ELEM_( \
        d, number_instruction_requirements_traits, assertion) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_IF_FRONT(assertion), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_1 \
    , BOOST_PP_IIF(BOOST_PP_EXPAND( /* EXPAND needed for MSVC */ \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_IS_STATEMENT( \
                    assertion)), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_STATEMENT \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT( \
            assertion), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_REQUIRES \
    , /* else: bool, const, or static assertion */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_CONDITION \
    )))(d, assertion \
        , BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits) \
        , BOOST_PP_TUPLE_ELEM(4, 1, number_instruction_requirements_traits) \
        , BOOST_PP_TUPLE_ELEM(4, 2, number_instruction_requirements_traits) \
        , BOOST_PP_TUPLE_ELEM(4, 3, number_instruction_requirements_traits) \
    )

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_D(d, assertions) \
    BOOST_PP_TUPLE_ELEM(4, 3 /* select traits */ \
        , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND_TUPLE(d \
            , BOOST_PP_LIST_FOLD_LEFT_ ## d( \
                  BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_ELEM_ \
                , ( \
                    0 /* number */ \
                  , \
                    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* instruction */ \
                  , \
                    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* requirements */ \
                  , \
                    BOOST_PP_NIL /* traits of all assertions */ \
                  ) \
                , assertions \
            ) \
        ) \
    )

// PUBLIC //

// Expand to a pp-list of assertion traits.
#define BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS(assertions) \
    BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_D(1, assertions)

// Expand to assertion number 1, 2, ... (for assertion statement, it is the
// number previous assertion or 0 if no previous assertion).
#define BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(assertion_traits) \
    BOOST_PP_TUPLE_ELEM(3, 0, assertion_traits)

// Expand to assertion instruction: bool_expr, const( vars ) const_bool_expr,
// static_assert(static_bool_expr, string), 
// if(bool_expr | const( vars ) const_bool_expr), else, PP_RCURLY,
// using directive, namespace directive, typedef type new_type.
#define BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION( \
        assertion_traits) \
    BOOST_PP_TUPLE_ELEM(3, 1, assertion_traits)

// Expand to 1 iff assertion is a statement (using, namespeace, typedef, etc
// but no if, else, or } of select assertions).
#define BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_IS_STATEMENT( \
        assertion_traits) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_IS_STATEMENT( \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION( \
                    assertion_traits))

// Expand to [boolean_integral_expr] (always EMPTY for statement). Not using
// plural REQUIREMENTS because not a list (or sequence).
#define BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_REQUIREMENT( \
        assertion_traits) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_TUPLE_ELEM(3, 2, assertion_traits))

#endif // #include guard

