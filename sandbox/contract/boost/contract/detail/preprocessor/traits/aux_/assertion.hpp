
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/requires.hpp>
#include <boost/contract/detail/preprocessor/keyword/using.hpp>
#include <boost/contract/detail/preprocessor/keyword/namespace.hpp>
#include <boost/contract/detail/preprocessor/keyword/typedef.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/append.hpp>

// PROTECTED //

// Expand to 1 iff it is an assertion statement.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_IS_STATEMENT(assertion) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_USING_FRONT(assertion), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_NAMESPACE_FRONT( \
            assertion), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TYPEDEF_FRONT( \
            assertion), \
        1 \
    , \
        0 \
    )))

// Append specified assertion traits to trait list.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND( \
        d, traits, number, instruction, requirements) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT( \
            instruction), \
        traits BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_PP_LIST_APPEND \
    )(traits, ((number, instruction, requirements), BOOST_PP_NIL))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND_TUPLE( \
        d, number_instruction_requirements_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits) \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* instruction */ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* requirements */ \
    , \
        /* append very last trait */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND(d \
            , BOOST_PP_TUPLE_ELEM(4, 3, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 1, number_instruction_requirements_traits)\
            , BOOST_PP_TUPLE_ELEM(4, 2, number_instruction_requirements_traits)\
        ) \
    )

// To be used for assertion statements using, namespace, and typedef.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_STATEMENT(d, statement, \
        prev_number, prev_instruction, prev_requirements, traits) \
    ( \
        prev_number /* statement is not an assertion so don't inc number */ \
    , \
        statement /* statement instruction */ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* stmnt has no requirement */ \
    , \
        /* append prev traits */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND(d, traits,  \
                prev_number, prev_instruction, prev_requirements) \
    )

// To be used for assertion requirements.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_REQUIRES(d, \
        requirements, prev_number, prev_instruction, prev_requirements, traits)\
    ( \
        prev_number \
    , \
        prev_instruction \
    , \
        /* only update requirements for prev assertion */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_REQUIRES_REMOVE_FRONT(requirements) \
    , \
        traits /* don't append, will append at next iteration */ \
    )

// To be used for boolean, const, and static assertions.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_CONDITION(d, assertion, \
        prev_number, prev_instruction, prev_requirements, traits) \
    ( \
        BOOST_PP_INC(prev_number) /* new actual assertion, inc number */ \
    , \
        assertion /* assertion instruction */ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no rqrmnts (maybe next) */ \
    , \
        /* append prev traits */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND(d, traits, \
                prev_number, prev_instruction, prev_requirements) \
    )

#endif // #include guard

