/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_HPP

#include <boost/generic/detail/array_to_seq.hpp>
#include <boost/generic/detail/ad_hoc_concept/name_param_details.hpp>
#include <boost/generic/detail/is_conditional_arg.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/is_recognized_arg.hpp>
#include <boost/generic/detail/param.hpp>
#include <boost/generic/detail/param_id.hpp>
#include <boost/generic/detail/param_id_category.hpp>
#include <boost/generic/detail/param_id_category_value.hpp>
#include <boost/generic/detail/param_id_implies_parentheses.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/push_back.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/logical/bool.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/replace.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS( ... )                        \
BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_IMPL                                  \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NAME_PARAM_DETAILS( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_IMPL( name_param_dets )       \
BOOST_PP_IF                                                                    \
( BOOST_PP_ARRAY_SIZE                                                          \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NAME_PARAM_DETAILS_ERRORS( name_param_dets ) )\
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_IMPL_NAME_PARAM_ERRORS              \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_IMPL_NO_NAME_PARAM_ERROR            \
)( name_param_dets )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_IMPL_NO_NAME_PARAM_ERROR(     \
                                                                name_param_dets\
                                                              )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                    \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NAME_PARAM_DETAILS_REMAINING_ARGS             \
    ( name_param_dets )                                                        \
  )                                                                            \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARGUMENT_DETAILS_CHECK_ARGS                     \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_IMPL_EMPTY                          \
)( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NAME_PARAM_DETAILS_ERRORS( name_param_dets )   \
 , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NAME_PARAM_DETAILS_NAME( name_param_dets )     \
 , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NAME_PARAM_DETAILS_PARAM_LIST_DETS             \
   ( name_param_dets )                                                         \
 , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NAME_PARAM_DETAILS_CURR_ARG_NUM                \
   ( name_param_dets )                                                         \
 , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NAME_PARAM_DETAILS_REMAINING_ARGS              \
   ( name_param_dets ) BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                          \
 )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_PARAM_CATEGORY_BIT_TABLE_EMPTY()          \
BOOST_PP_REPEAT                                                                \
( BOOST_GENERIC_DETAIL_NUM_PARAM_CATEGORIES                                    \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_PARAM_CATEGORY_BIT_TABLE_EMPTY_MACRO            \
, ~                                                                            \
)

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_PARAM_CATEGORY_BIT_TABLE_EMPTY_MACRO(     \
                                                                        z, n, t\
                                                                      )        \
((0))

// State is a sequence of:
//   A bit specifying if a fatal error was encountered
//     (in which case we don't try to parse any more arguments)
//
//   The concept name
//
//   The concept param list details
//
//   A value specifying the current argument number
//
//   A sequence of sequences of category info where the first element is a
//     bit that specifies whether or not the category was encountered. If and
//     only if the first element is 1, there is a second element which
//     specifies the line number where the first occurrence of the category
//     appeared
//
//   An array of sequences of analyzed conditional arguments of the form:
//     (param_id_without_spaces)(param_without_id_in_paren)
//
//   public category argument if present following the form:
//   (exists_bit)(param_id_without_spaces)(param_without_id_in_paren)
//
//   for category argument if present following the form:
//   (exists_bit)(param_id_without_spaces)(param_without_id_in_paren)
//
//   for typedef category argument if present following the form:
//   (exists_bit)(param_id_without_spaces)(param_without_id_in_paren)
//
//   An array of errors
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARGUMENT_DETAILS_CHECK_ARGS( errors       \
                                                              , name           \
                                                              , param_dets     \
                                                              , curr_arg_num   \
                                                              , remaining_args \
                                                              )                \
BOOST_PP_SEQ_FOLD_LEFT                                                         \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARGUMENT_DETAILS_MACRO                          \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_IMPL_EMPTY                          \
  ( errors, name, param_dets, curr_arg_num, remaining_args )                   \
, remaining_args()                                                             \
)

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_IMPL_EMPTY( errors            \
                                                           , name              \
                                                           , param_dets        \
                                                           , curr_arg_num      \
                                                           , remaining_args    \
                                                           )                   \
( 0 )                                                                          \
( name )                                                                       \
( param_dets )                                                                 \
( curr_arg_num )                                                               \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_PARAM_CATEGORY_BIT_TABLE_EMPTY() )              \
( ( 0, () ) )                                                                  \
( ( 0 ) ( ~ ) ( ~ ) )                                                          \
( ( 0 ) ( ~ ) ( ~ ) )                                                          \
( ( 0 ) ( ~ ) ( ~ ) )                                                          \
( ( 0, () ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FATAL_ERROR( state )             \
BOOST_PP_SEQ_ELEM( 0, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_NAME( state )                    \
BOOST_PP_SEQ_ELEM( 1, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PARAM_DETS( state )              \
BOOST_PP_SEQ_ELEM( 2, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state )                 \
BOOST_PP_SEQ_ELEM( 3, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CATEGORY_INFO( state )           \
BOOST_PP_SEQ_ELEM( 4, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state )        \
BOOST_PP_SEQ_ELEM( 5, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_CONDITIONAL_ARGS( state )    \
BOOST_PP_BOOL                                                                  \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_NUM_CONDITIONAL_ARGS( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_NUM_CONDITIONAL_ARGS( state )    \
BOOST_PP_ARRAY_SIZE                                                            \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS_AS_SEQ( state ) \
BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ                                              \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARG_N_SPACED_ID(     \
                                                                        state  \
                                                                      , n      \
                                                                      )        \
BOOST_GENERIC_DETAIL_SPACED_ID                                                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARG_N_ID( state, n ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARG_N_ID( state, n ) \
BOOST_PP_SEQ_ELEM                                                              \
( 0, BOOST_PP_ARRAY_ELEM                                                       \
     ( n, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state ) )    \
)

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARG_N_PARAM(state,n) \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_PP_SEQ_ELEM                                                            \
  ( 1, BOOST_PP_ARRAY_ELEM                                                     \
       ( n, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state ) )  \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARG_N_X_PARAM( state \
                                                                       , n, x  \
                                                                       )       \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_PP_SEQ_ELEM                                                            \
  ( x                                                                          \
  , BOOST_GENERIC_DETAIL_SEQ_TO_SEQ                                            \
    ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARG_N_PARAM            \
      ( state, n )                                                             \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state )                  \
BOOST_PP_SEQ_ELEM( 6, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_PUBLIC_CATEGORY( state )     \
BOOST_PP_SEQ_HEAD( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC_PARAM_ID( state )         \
BOOST_PP_SEQ_ELEM( 1, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC_PARAM( state )            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_PP_SEQ_ELEM                                                            \
  ( 2, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )                 \
)

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state )                     \
BOOST_PP_SEQ_ELEM( 7, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_FOR_CATEGORY( state )        \
BOOST_PP_SEQ_HEAD( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_PARAM_ID( state )            \
BOOST_PP_SEQ_ELEM( 1, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_PARAM( state )               \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_PP_SEQ_ELEM( 2, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state )             \
BOOST_PP_SEQ_ELEM( 8, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_FOR_TYPEDEF_CATEGORY( state )\
BOOST_PP_SEQ_HEAD( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF_PARAM_ID( state )    \
BOOST_PP_SEQ_ELEM                                                              \
( 1, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF_PARAM( state )       \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_PP_SEQ_ELEM                                                            \
  ( 2, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )            \
)

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state )                  \
BOOST_PP_SEQ_ELEM( 9, state )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_ERRORS( state )              \
BOOST_PP_BOOL                                                                  \
( BOOST_PP_ARRAY_SIZE( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state ) ) )

// state is described above
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARGUMENT_DETAILS_MACRO( s, state, elem )  \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FATAL_ERROR( state )                   \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_FORWARD_FATAL_ERROR                             \
, BOOST_PP_IIF                                                                 \
  ( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( elem )                          \
  , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_INFO_MACRO_PARENTHESIZED                \
  , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NOT_PARENTHESIZED                             \
  )                                                                            \
)( state, elem )

// Checks starting after it is established that the argument is parenthesized
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_INFO_MACRO_PARENTHESIZED( state     \
                                                                   , elem      \
                                                                   )           \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_RECOGNIZED_ARG( elem )                               \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_INFO_MACRO_RECOGNIZED                     \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_UNRECOGNIZED_ARG                                \
)( state, elem )

// Checks starting after we have recognized the parameter kind
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_INFO_MACRO_RECOGNIZED( state, elem )\
BOOST_PP_IIF                                                                   \
( BOOST_NO_BOOST_GENERIC_CONCEPT_PARAM                                         \
  ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                                    \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_NO_SUPPORT_INFO                           \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_INFO_MACRO_SUPPORTED                      \
)( state, elem )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_CHANGE_IN_ERRORS( state )              \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state ) )

// Invoked when no error is found (updates line counter, categories, and args)
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT( state, elem )     \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FATAL_ERROR( state ) )                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_NAME( state ) )                        \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PARAM_DETS( state ) )                  \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ) ) )     \
( BOOST_PP_SEQ_REPLACE                                                         \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CATEGORY_INFO( state )               \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , ( 1 )( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ) )            \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_PUSH_BACK_IF_CONDITIONAL                        \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state ), elem )    \
)                                                                              \
BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA( state, elem )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_PUSH_BACK_IF_CONDITIONAL( array, elem )   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_CONDITIONAL_ARG( elem )                  \
            , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_PUSH_BACK_IF_CONDITIONAL_IMPL       \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( array )                  \
            )( array, elem )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_PUSH_BACK_IF_CONDITIONAL_IMPL( array      \
                                                                  , elem       \
                                                                  )            \
BOOST_PP_ARRAY_PUSH_BACK                                                       \
( array                                                                        \
, ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                                    \
  ( ( BOOST_GENERIC_DETAIL_PARAM( elem ) ) )                                   \
)

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA( state    \
                                                                    , elem     \
                                                                    )          \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( ( public ) )                 \
  )                                                                            \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_PUBLIC          \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_PUBL        \
)( state, elem )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_PUBLIC(   \
                                                                       state   \
                                                                     , elem    \
                                                                     )         \
( ( 1 ) ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                              \
        ( ( BOOST_GENERIC_DETAIL_PARAM( elem ) ) )                             \
)                                                                              \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )                         \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_PUBL( \
                                                                          state\
                                                                        , elem \
                                                                        )      \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( ( for () ) )                 \
  )                                                                            \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_FOR             \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_FOR         \
)( state, elem )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_FOR( state\
                                                                        , elem \
                                                                        )      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )                      \
( ( 1 ) ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                              \
        ( ( BOOST_GENERIC_DETAIL_PARAM( elem ) ) )                             \
)                                                                              \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_FOR(  \
                                                                          state\
                                                                        , elem \
                                                                        )      \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( ( for typedef ) )            \
  )                                                                            \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_FOR_T           \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_FOR_T       \
)( state, elem )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_FOR_T(    \
                                                                       state   \
                                                                     , elem    \
                                                                     )         \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )                      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )                         \
( ( 1 ) ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                              \
        ( ( BOOST_GENERIC_DETAIL_PARAM( elem ) ) )                             \
)                                                                              \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state ) )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_FOR_T(\
                                                                          state\
                                                                        , elem \
                                                                        )      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )                      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )                         \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state ) )

// Update the fold state when we hit an argument that should take a sequence but
// it is detected that the argument does not have parentheses
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_ARG_NOT_PAREN_INFO( state, elem )     \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FATAL_ERROR( state ) )                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_NAME( state ) )                        \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PARAM_DETS( state ) )                  \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ) ) )     \
( BOOST_PP_SEQ_REPLACE                                                         \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CATEGORY_INFO( state )               \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , ( 1 )( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ) )            \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state ) )            \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )                      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )                         \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )                 \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state )                      \
  , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_ARG_ARG_NOT_PAREN                       \
    ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                                  \
  )                                                                            \
)

// Update the fold state when we hit an argument that duplicates a category that
// was already encountered
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_DUPLICATE_CATEGORY_INFO( state, elem )    \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FATAL_ERROR( state ) )                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_NAME( state ) )                        \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PARAM_DETS( state ) )                  \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ) ) )     \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CATEGORY_INFO( state ) )               \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state ) )            \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )                      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )                         \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )                 \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state )                      \
  , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_MULTIPLE_OF_CATEGORY                    \
    ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY( elem )                           \
    , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state )                   \
    , BOOST_PP_SEQ_ELEM                                                        \
      ( 1                                                                      \
      , BOOST_PP_SEQ_ELEM                                                      \
        ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                 \
        , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CATEGORY_INFO( state )         \
        )                                                                      \
      )                                                                        \
    )                                                                          \
  )                                                                            \
)

// Update the fold state when we hit an argument that wasn't parenthesized
// An argument that isn't parenthesized is a fatal error and we can't parse
// anything after that since we can't know whether or not commas there are
// intended to end that argument or if they are supposed to be a part of that
// argument
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NOT_PARENTHESIZED( state, elem )          \
( 1 )( ~ )( ~ )( ~ )( ~ )( ~ )                                                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )                      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )                         \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )                 \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state )                      \
  , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_NOT_PARENTHESIZED                       \
    ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ), elem )           \
  )                                                                            \
)

// Update the fold state when we hit an unrecognized param id
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_UNRECOGNIZED_ARG( state, elem )           \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FATAL_ERROR( state ) )                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_NAME( state ) )                        \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PARAM_DETS( state ) )                  \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ) ) )     \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CATEGORY_INFO( state ) )               \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state ) )            \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )                      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )                         \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )                 \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state )                      \
  , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_UNRECOGNIZED_PARAM_ID                   \
    ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ), elem )           \
  )                                                                            \
)

// On a fatal error don't bother trying to parse any more arguments
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_FORWARD_FATAL_ERROR( state, elem ) state

// Determines if the category of this argument has already appeared
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_IS_DUPLICATE_CATEGORY( state, elem )      \
BOOST_PP_SEQ_ELEM                                                              \
( 0                                                                            \
, BOOST_PP_SEQ_ELEM                                                            \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CATEGORY_INFO( state )               \
  )                                                                            \
)

// Update the fold state when we hit a parameter kind that we can't support
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_NO_SUPPORT_INFO( state, elem )      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FATAL_ERROR( state ) )                 \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_NAME( state ) )                        \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PARAM_DETS( state ) )                  \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ) ) )     \
( BOOST_PP_SEQ_REPLACE                                                         \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CATEGORY_INFO( state )               \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , ( 1 )( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state ) )            \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_CONDITIONAL_ARGS( state ) )            \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_PUBLIC( state ) )                      \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR( state ) )                         \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FOR_TYPEDEF( state ) )                 \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ERRORS( state )                      \
  , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_NO_PARAM_SUPPORT                        \
    ( BOOST_GENERIC_DETAIL_PARAM_ID( elem )                                    \
    , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_ARG_NUM( state )                   \
    )                                                                          \
  )                                                                            \
)

// Checks starting after we have determined that the parameter kind is supported
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_INFO_MACRO_SUPPORTED( state, elem ) \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_IS_DUPLICATE_CATEGORY( state, elem )            \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_DUPLICATE_CATEGORY_INFO                         \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_NO_DUPLICATE                              \
)( state, elem )

#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_LACKS_PARENT_FOR_ARG( state, elem )       \
BOOST_PP_BITAND                                                                \
( BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PARENTHESES( elem )                    \
, BOOST_PP_COMPL                                                               \
  ( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                  \
    ( BOOST_GENERIC_DETAIL_PARAM( elem ) )                                     \
  )                                                                            \
)

// Checks starting after we have determined that there is not a duplicate
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ERROR_NO_DUPLICATE( state, elem )         \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_LACKS_PARENT_FOR_ARG( state, elem )             \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_ARG_NOT_PAREN_INFO                          \
, BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_NO_ERROR_WITH_ARGUMENT                          \
)( state, elem )

// Yields 1 if there were errors, otherwise it yields 0
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_HAS_ERRORS( error_array )                 \
BOOST_PP_BOOL( BOOST_PP_ARRAY_SIZE( error_array ) )

// Yields all errors as statements
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_EMIT_ERRORS( error_array )                \
BOOST_PP_IF( BOOST_PP_ARRAY_SIZE( error_array )                                \
           , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_EMIT_ERRORS_IMPL                     \
           , BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_EMIT_NO_ERRORS_IMPL                  \
           )( error_array )

// Do nothing if there are no errors to emit
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_EMIT_NO_ERRORS_IMPL( error_array )

// Yields all errors as statements (only valid if array size is greater than 1)
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_EMIT_ERRORS_IMPL( error_array )           \
void BOOST_PP_CAT( failed_auto_function_on_line_, __LINE__ )();                \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_EMIT_ERROR_IMPL, ~                              \
, BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ( error_array )                             \
)

// Yields an error as a statement
#define BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_EMIT_ERROR_IMPL( r, dummy, error ) error;

#endif // BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS_HPP
