
/*************************************************************/
/* WARNING:  FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "<FILE>-generate.py" */
/*************************************************************/
// Used BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS: 5

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_1_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_1_HPP_

#include <boost/contract/limits.hpp>
#if BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS != 5
#   error "Code generation used incorrect BOOST_CONTRACT_LIMIT_NESTED_SELECT_ASSERTIONS"
#endif

#include <boost/contract/detail/preprocessor/traits/aux_/assertion.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/select_assertion.hpp>
#if 2 <= 5
#   include <boost/contract/detail/preprocessor/traits/aux_/select_assertion_2.hpp>
#endif
#include <boost/contract/detail/preprocessor/keyword/boost/contract/requires.hpp>
#include <boost/contract/detail/preprocessor/keyword/if.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELEM_1_( \
        d, number_instruction_requirements_traits, assertion) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_IF_FRONT(assertion), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_2 \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_IS_STATEMENT(\
            assertion), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_STATEMENT \
    , BOOST_PP_IIF( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT(assertion), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_REQUIRES \
    , /* else: bool, const, or static assert */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_CONDITION \
    )))(d, assertion \
        , BOOST_PP_TUPLE_ELEM(4, 0, number_instruction_requirements_traits) \
        , BOOST_PP_TUPLE_ELEM(4, 1, number_instruction_requirements_traits) \
        , BOOST_PP_TUPLE_ELEM(4, 2, number_instruction_requirements_traits) \
        , BOOST_PP_TUPLE_ELEM(4, 3, number_instruction_requirements_traits) \
    )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_LIST_1_( \
        d, select_assertions, number_instruction_requirements_traits) \
    BOOST_PP_LIST_FOLD_LEFT_ ## d( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELEM_1_, \
            number_instruction_requirements_traits, select_assertions)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_1_( \
        d, select_traits, prev_number, prev_instruction, prev_requirements, \
        traits) \
    /* 6th, append right-curly to end else block */ \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_RCURLY(d \
    /* 5th, append else-assertions */ \
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_LIST_1_(d, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_ELSES( \
                    select_traits) \
    /* 4th, append else-statement `else` */ \
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_ELSE(d \
    /* 3rd, append right-curly to end if block */ \
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_RCURLY(d \
    /* 2nd, append then-assertions */ \
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_LIST_1_(d \
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_THENS(select_traits) \
    /* 1st, append if-statement `if(...)` */ \
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_PREPEND_IF(d \
  , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_IF(select_traits) \
  , (prev_number, prev_instruction, prev_requirements, traits) \
  ) ) ) ) ) )

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_1( \
        d, assertion, prev_number, prev_instruction, prev_requirements, \
        traits) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_ASSERTION_APPEND_TUPLE(d, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION_1_(d, \
                    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_SELECT_ASSERTION( \
                            assertion),\
                    prev_number, prev_instruction, prev_requirements, traits))

#endif // #include guard

