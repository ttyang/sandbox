#ifndef BOOST_GENERIC_DETAIL_ARG_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_ARG_DETAILS_HPP

// ToDo: Remove all auto_function includes
//#include <boost/auto_function/detail/error.hpp>
//#include <boost/auto_function/detail/function_name_details.hpp>
//#include <boost/auto_function/detail/is_conditional_arg.hpp>
//#include <boost/auto_function/detail/is_parenthesized.hpp>
//#include <boost/auto_function/detail/is_recognized_arg.hpp>
//#include <boost/auto_function/detail/is_valid_name_and_params.hpp>
//#include <boost/auto_function/detail/num_args.hpp>
//#include <boost/auto_function/detail/opener_details.hpp>
//#include <boost/auto_function/detail/param.hpp>
//#include <boost/auto_function/detail/param_id.hpp>
//#include <boost/auto_function/detail/param_id_category_value.hpp>
//#include <boost/auto_function/detail/param_id_implies_parentheses.hpp>
//#include <boost/auto_function/detail/param_list_details.hpp>
//#include <boost/auto_function/detail/template_details.hpp>
//#include <boost/auto_function/support.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/array/data.hpp>
#include <boost/preprocessor/array/push_back.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/bool.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/replace.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

// Takes in the parameters passed to BOOST_GENERIC.
// It yields a sequence of the form:
// (error_array)(template_details)(function_name_details)(param_list_details)
// (arguments)
// where arguments is a sequence with elements of the form:
// (param_id_without_spaces)(param_without_id_in_paren)
#define BOOST_GENERIC_DETAIL_ARGUMENT_DETAILS( ... )                           \
BOOST_GENERIC_DETAIL_ARGUMENT_DETAILS_IMPL                                     \
( BOOST_GENERIC_DETAIL_OPENER_DETAILS( __VA_ARGS__ ) )

// Converts a preprocessor array to a sequence
#define BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ( result_as_array )                   \
BOOST_PP_TUPLE_TO_SEQ                                                          \
( BOOST_PP_ARRAY_SIZE( result_as_array )                                       \
, BOOST_PP_ARRAY_DATA( result_as_array )                                       \
)

#define BOOST_GENERIC_DETAIL_ARGUMENT_DETAILS_IMPL( opener_dets )              \
BOOST_PP_IF                                                                    \
( BOOST_PP_ARRAY_SIZE                                                          \
  ( BOOST_GENERIC_DETAIL_OPENER_DETAILS_ERRORS( opener_dets ) )                \
, BOOST_GENERIC_DETAIL_ARGUMENT_DETAILS_OPENER_ERROR                           \
, BOOST_GENERIC_DETAIL_ARGUMENT_DETAILS_CHECK_ARGS                             \
)( BOOST_GENERIC_DETAIL_OPENER_DETAILS_ERRORS( opener_dets )                   \
 , BOOST_GENERIC_DETAIL_OPENER_DETAILS_TEMPLATE_DETAILS( opener_dets )         \
 , BOOST_GENERIC_DETAIL_OPENER_DETAILS_FUNCTION_NAME_DETAILS(opener_dets)      \
 , BOOST_GENERIC_DETAIL_OPENER_DETAILS_PARAM_LIST_DETAILS( opener_dets )       \
 , BOOST_GENERIC_DETAIL_OPENER_DETAILS_CURR_ARG_NUM( opener_dets )             \
 , BOOST_GENERIC_DETAIL_OPENER_DETAILS_REMAINING_ARGS( opener_dets )           \
 )

#define BOOST_GENERIC_DETAIL_PARAM_CATEGORY_BIT_TABLE_EMPTY()                  \
BOOST_PP_REPEAT                                                                \
( BOOST_GENERIC_DETAIL_NUM_PARAM_CATEGORIES                                    \
, BOOST_GENERIC_DETAIL_PARAM_CATEGORY_BIT_TABLE_EMPTY_MACRO                    \
, ~                                                                            \
)

#define BOOST_GENERIC_DETAIL_PARAM_CATEGORY_BIT_TABLE_EMPTY_MACRO(z,n,t) \
((0))

// State is a sequence of:
//   A bit specifying if a fatal error was encountered
//     (in which case we don't try to parse any more arguments)
//
//   The template details
//
//   The function name details
//
//   The param list details
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
//   explicit category argument if present following the form:
//   (exists_bit)(param_id_without_spaces)(param_without_id_in_paren)
//
//   do category argument if present following the form:
//   (exists_bit)(param_id_without_spaces)(param_without_id_in_paren)
//
//   switch category argument if present following the form:
//   (exists_bit)(param_id_without_spaces)(param_without_id_in_paren)
//
//   case category argument if present following the form:
//   (exists_bit)(param_id_without_spaces)(param_without_id_in_paren)
//
//   An array of errors
#define BOOST_GENERIC_DETAIL_ARGUMENT_DETAILS_CHECK_ARGS( opener_errors        \
                                                              , tmpl_dets      \
                                                              , fun_name_dets  \
                                                              , param_list_dets\
                                                              , curr_arg_num   \
                                                              , remaining_args \
                                                              )                \
BOOST_GENERIC_DETAIL_CHECK_FOR_VALID_END                                       \
( BOOST_PP_SEQ_FOLD_LEFT                                                       \
  ( BOOST_GENERIC_DETAIL_ARGUMENT_DETAILS_MACRO                                \
  , ( 0 )                                                                      \
    ( tmpl_dets )                                                              \
    ( fun_name_dets )                                                          \
    ( param_list_dets )                                                        \
    ( curr_arg_num )                                                           \
    ( BOOST_GENERIC_DETAIL_PARAM_CATEGORY_BIT_TABLE_EMPTY() )                  \
    ( ( 0, () ) )                                                              \
    ( ( 0 ) ( ~ ) ( ~ ) )                                                      \
    ( ( 0 ) ( ~ ) ( ~ ) )                                                      \
    ( ( 0 ) ( ~ ) ( ~ ) )                                                      \
    ( ( 0 ) ( ~ ) ( ~ ) )                                                      \
    ( ( 0, () ) )                                                              \
  , remaining_args                                                             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_ARG_DETS_FATAL_ERROR( state )                     \
BOOST_PP_SEQ_ELEM( 0, state )

#define BOOST_GENERIC_DETAIL_ARG_DETS_TMP_DETS( state )                        \
BOOST_PP_SEQ_ELEM( 1, state )

#define BOOST_GENERIC_DETAIL_ARG_DETS_FUN_NAME_DETS( state )                   \
BOOST_PP_SEQ_ELEM( 2, state )

#define BOOST_GENERIC_DETAIL_ARG_DETS_PARAM_LIST_DETS( state )                 \
BOOST_PP_SEQ_ELEM( 3, state )

#define BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state )                         \
BOOST_PP_SEQ_ELEM( 4, state )

#define BOOST_GENERIC_DETAIL_ARG_DETS_CATEGORY_INFO( state )                   \
BOOST_PP_SEQ_ELEM( 5, state )

#define BOOST_GENERIC_DETAIL_ARG_DETS_CONDITIONAL_ARGS( state )                \
BOOST_PP_SEQ_ELEM( 6, state )

#define BOOST_GENERIC_DETAIL_ARG_DETS_CONDITIONAL_ARGS_AS_SEQ( state )         \
BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ                                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CONDITIONAL_ARGS( state ) )

#define BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state )                        \
BOOST_PP_SEQ_ELEM( 7, state )

#define BOOST_GENERIC_DETAIL_ARG_DETS_HAS_EXPLICIT_CATEGORY( state )           \
BOOST_PP_SEQ_HEAD( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )

#define BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT_PARAM_ID( state )               \
BOOST_PP_SEQ_ELEM( 1, BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )

#define BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT_PARAM( state )                  \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_PP_SEQ_ELEM                                                            \
  ( 2, BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                       \
)

#define BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state )                          \
BOOST_PP_SEQ_ELEM( 11, state )

#define BOOST_GENERIC_DETAIL_ARG_DETS_HAS_ERRORS( state )                      \
BOOST_PP_BOOL                                                                  \
( BOOST_PP_ARRAY_SIZE( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state ) ) )

// state is described above
#define BOOST_GENERIC_DETAIL_ARGUMENT_DETAILS_MACRO( s, state, elem )          \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_ARG_DETS_FATAL_ERROR( state )                           \
, BOOST_GENERIC_DETAIL_FORWARD_FATAL_ERROR                                     \
, BOOST_PP_IIF                                                                 \
  ( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( elem )                          \
  , BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_PARENTHESIZED                        \
  , BOOST_GENERIC_DETAIL_NOT_PARENTHESIZED                                     \
  )                                                                            \
)( state, elem )

// Checks starting after it is established that the argument is parenthesized
#define BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_PARENTHESIZED( state,elem )      \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_RECOGNIZED_ARG( elem )                               \
, BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_RECOGNIZED                             \
, BOOST_GENERIC_DETAIL_UNRECOGNIZED_ARG                                       \
)( state, elem )

// Checks starting after we have recognized the parameter kind
#define BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_RECOGNIZED( state, elem )        \
BOOST_PP_IIF                                                                   \
( BOOST_NO_BOOST_GENERIC_PARAM                                                 \
  ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                                    \
, BOOST_GENERIC_DETAIL_ERROR_NO_SUPPORT_INFO                                   \
, BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_SUPPORTED                              \
)( state, elem )

#define BOOST_GENERIC_DETAIL_NO_CHANGE_IN_ERRORS( state )                      \
( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state ) )

// Invoked when no error is found (updates line counter, categories, and args)
#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT( state, elem )             \
( BOOST_GENERIC_DETAIL_ARG_DETS_FATAL_ERROR( state ) )                         \
( BOOST_GENERIC_DETAIL_ARG_DETS_TMP_DETS( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_FUN_NAME_DETS( state ) )                       \
( BOOST_GENERIC_DETAIL_ARG_DETS_PARAM_LIST_DETS( state ) )                     \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ) ) )             \
( BOOST_PP_SEQ_REPLACE                                                         \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_CATEGORY_INFO( state )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , ( 1 )( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ) )                    \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_PUSH_BACK_IF_CONDITIONAL                                \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_CONDITIONAL_ARGS( state ), elem )            \
)                                                                              \
BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA( state, elem )

#define BOOST_GENERIC_DETAIL_PUSH_BACK_IF_CONDITIONAL( array, elem )           \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_CONDITIONAL_ARG( elem )                  \
            , BOOST_GENERIC_DETAIL_PUSH_BACK_IF_CONDITIONAL_IMPL               \
            , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( array )                  \
            )( array, elem )

#define BOOST_GENERIC_DETAIL_PUSH_BACK_IF_CONDITIONAL_IMPL( array, elem )      \
BOOST_PP_ARRAY_PUSH_BACK                                                       \
( array                                                                        \
, ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                                    \
  ( ( BOOST_GENERIC_DETAIL_PARAM( elem ) ) )                                   \
)

#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA(state,elem)       \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( ( explicit ) )               \
  )                                                                            \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_EXPLICIT                \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_EXPL                \
)( state, elem )

#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_EXPLICIT(         \
                                                                       state   \
                                                                     , elem    \
                                                                     )         \
( ( 1 ) ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                              \
        ( ( BOOST_GENERIC_DETAIL_PARAM( elem ) ) )                             \
)                                                                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_DO( state ) )                                  \
( BOOST_GENERIC_DETAIL_ARG_DETS_SWITCH( state ) )                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CASE( state ) )                                \
( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state ) )

#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_EXPL(         \
                                                                          state\
                                                                        , elem \
                                                                        )      \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( ( do ) )                     \
  )                                                                            \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_DO                      \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_DO                  \
)( state, elem )

#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_DO( state         \
                                                                     , elem    \
                                                                     )         \
( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                            \
( ( 1 ) ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                              \
        ( ( BOOST_GENERIC_DETAIL_PARAM( elem ) ) )                             \
)                                                                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_SWITCH( state ) )                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CASE( state ) )                                \
( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state ) )

#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_DO(state      \
                                                                        , elem \
                                                                        )      \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( ( switch ) )                 \
  )                                                                            \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_SWITCH                  \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_SWITCH              \
)( state, elem )

#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_SWITCH(           \
                                                                       state   \
                                                                     , elem    \
                                                                     )         \
( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_DO( state ) )                                  \
( ( 1 ) ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                              \
        ( ( BOOST_GENERIC_DETAIL_PARAM( elem ) ) )                             \
)                                                                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CASE( state ) )                                \
( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state ) )

#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_SWITCH(       \
                                                                          state\
                                                                        , elem \
                                                                        )      \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( ( case ) )                   \
  )                                                                            \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_CASE                    \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_CASE                \
)( state, elem )

#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_CASE( state       \
                                                                       , elem  \
                                                                       )       \
( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_DO( state ) )                                  \
( BOOST_GENERIC_DETAIL_ARG_DETS_SWITCH( state ) )                              \
( ( 1 ) ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                              \
        ( ( BOOST_GENERIC_DETAIL_PARAM( elem ) ) )                             \
)                                                                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state ) )

#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT_END_DATA_NOT_CASE(         \
                                                                         state \
                                                                       , elem  \
                                                                       )       \
( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_DO( state ) )                                  \
( BOOST_GENERIC_DETAIL_ARG_DETS_SWITCH( state ) )                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CASE( state ) )                                \
( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state ) )

// Update the fold state when we hit an argument that should take a sequence but
// it is detected that the argument does not have parentheses
#define BOOST_GENERIC_DETAIL_ARG_ARG_NOT_PAREN_INFO( state, elem )             \
( BOOST_GENERIC_DETAIL_ARG_DETS_FATAL_ERROR( state ) )                         \
( BOOST_GENERIC_DETAIL_ARG_DETS_TMP_DETS( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_FUN_NAME_DETS( state ) )                       \
( BOOST_GENERIC_DETAIL_ARG_DETS_PARAM_LIST_DETS( state ) )                     \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ) ) )             \
( BOOST_PP_SEQ_REPLACE                                                         \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_CATEGORY_INFO( state )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , ( 1 )( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ) )                    \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CONDITIONAL_ARGS( state ) )                    \
( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_DO( state ) )                                  \
( BOOST_GENERIC_DETAIL_ARG_DETS_SWITCH( state ) )                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CASE( state ) )                                \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state )                              \
  , BOOST_GENERIC_DETAIL_ERROR_ARG_ARG_NOT_PAREN                               \
    ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                                  \
  )                                                                            \
)

// Update the fold state when we hit an argument that duplicates a category that
// was already encountered
#define BOOST_GENERIC_DETAIL_DUPLICATE_CATEGORY_INFO( state, elem )            \
( BOOST_GENERIC_DETAIL_ARG_DETS_FATAL_ERROR( state ) )                         \
( BOOST_GENERIC_DETAIL_ARG_DETS_TMP_DETS( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_FUN_NAME_DETS( state ) )                       \
( BOOST_GENERIC_DETAIL_ARG_DETS_PARAM_LIST_DETS( state ) )                     \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ) ) )             \
( BOOST_GENERIC_DETAIL_ARG_DETS_CATEGORY_INFO( state ) )                       \
( BOOST_GENERIC_DETAIL_ARG_DETS_CONDITIONAL_ARGS( state ) )                    \
( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_DO( state ) )                                  \
( BOOST_GENERIC_DETAIL_ARG_DETS_SWITCH( state ) )                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CASE( state ) )                                \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state )                              \
  , BOOST_GENERIC_DETAIL_ERROR_MULTIPLE_OF_CATEGORY                            \
    ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY( elem )                           \
    , BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state )                           \
    , BOOST_PP_SEQ_ELEM                                                        \
      ( 1                                                                      \
      , BOOST_PP_SEQ_ELEM                                                      \
        ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                 \
        , BOOST_GENERIC_DETAIL_ARG_DETS_CATEGORY_INFO( state )                 \
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
#define BOOST_GENERIC_DETAIL_NOT_PARENTHESIZED( state, elem )                  \
( 1 )( ~ )( ~ )( ~ )( ~ )( ~ )( ~ )                                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_DO( state ) )                                  \
( BOOST_GENERIC_DETAIL_ARG_DETS_SWITCH( state ) )                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CASE( state ) )                                \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state )                              \
  , BOOST_GENERIC_DETAIL_ERROR_NOT_PARENTHESIZED                               \
    ( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ), elem )                   \
  )                                                                            \
)

// Update the fold state when we hit an unrecognized param id
#define BOOST_GENERIC_DETAIL_UNRECOGNIZED_ARG( state, elem )                   \
( BOOST_GENERIC_DETAIL_ARG_DETS_FATAL_ERROR( state ) )                         \
( BOOST_GENERIC_DETAIL_ARG_DETS_TMP_DETS( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_FUN_NAME_DETS( state ) )                       \
( BOOST_GENERIC_DETAIL_ARG_DETS_PARAM_LIST_DETS( state ) )                     \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ) ) )             \
( BOOST_GENERIC_DETAIL_ARG_DETS_CATEGORY_INFO( state ) )                       \
( BOOST_GENERIC_DETAIL_ARG_DETS_CONDITIONAL_ARGS( state ) )                    \
( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_DO( state ) )                                  \
( BOOST_GENERIC_DETAIL_ARG_DETS_SWITCH( state ) )                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CASE( state ) )                                \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state )                              \
  , BOOST_GENERIC_DETAIL_ERROR_UNRECOGNIZED_PARAM_ID                           \
    ( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ), elem )                   \
  )                                                                            \
)

// On a fatal error don't bother trying to parse any more arguments
#define BOOST_GENERIC_DETAIL_FORWARD_FATAL_ERROR( state, elem ) state

// Determines if the category of this argument has already appeared
#define BOOST_GENERIC_DETAIL_IS_DUPLICATE_CATEGORY( state, elem )              \
BOOST_PP_SEQ_ELEM                                                              \
( 0                                                                            \
, BOOST_PP_SEQ_ELEM( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )      \
                   , BOOST_GENERIC_DETAIL_ARG_DETS_CATEGORY_INFO( state )      \
                   )                                                           \
)

// Update the fold state when we hit a parameter kind that we can't support
#define BOOST_GENERIC_DETAIL_ERROR_NO_SUPPORT_INFO( state, elem )              \
( BOOST_GENERIC_DETAIL_ARG_DETS_FATAL_ERROR( state ) )                         \
( BOOST_GENERIC_DETAIL_ARG_DETS_TMP_DETS( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_FUN_NAME_DETS( state ) )                       \
( BOOST_GENERIC_DETAIL_ARG_DETS_PARAM_LIST_DETS( state ) )                     \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ) ) )             \
( BOOST_PP_SEQ_REPLACE                                                         \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_CATEGORY_INFO( state )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , ( 1 )( BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state ) )                    \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CONDITIONAL_ARGS( state ) )                    \
( BOOST_GENERIC_DETAIL_ARG_DETS_EXPLICIT( state ) )                            \
( BOOST_GENERIC_DETAIL_ARG_DETS_DO( state ) )                                  \
( BOOST_GENERIC_DETAIL_ARG_DETS_SWITCH( state ) )                              \
( BOOST_GENERIC_DETAIL_ARG_DETS_CASE( state ) )                                \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_ERRORS( state )                              \
  , BOOST_GENERIC_DETAIL_ERROR_NO_PARAM_SUPPORT                                \
    ( BOOST_GENERIC_DETAIL_PARAM_ID( elem )                                    \
    , BOOST_GENERIC_DETAIL_ARG_DETS_ARG_NUM( state )                           \
    )                                                                          \
  )                                                                            \
)

// Checks starting after we have determined that the parameter kind is supported
#define BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_SUPPORTED( state, elem )         \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_DUPLICATE_CATEGORY( state, elem )                    \
, BOOST_GENERIC_DETAIL_DUPLICATE_CATEGORY_INFO                                 \
, BOOST_GENERIC_DETAIL_ERROR_NO_DUPLICATE                                      \
)( state, elem )

#define BOOST_GENERIC_DETAIL_LACKS_PARENT_FOR_ARG( state, elem )               \
BOOST_PP_BITAND                                                                \
( BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PARENTHESES( elem )                    \
, BOOST_PP_COMPL                                                               \
  ( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                  \
    ( BOOST_GENERIC_DETAIL_PARAM( elem ) )                                     \
  )                                                                            \
)

// Checks starting after we have determined that there is not a duplicate
#define BOOST_GENERIC_DETAIL_ERROR_NO_DUPLICATE( state, elem )                 \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_LACKS_PARENT_FOR_ARG( state, elem )                     \
, BOOST_GENERIC_DETAIL_ARG_ARG_NOT_PAREN_INFO                                  \
, BOOST_GENERIC_DETAIL_PROPER_ARGUMENT_FORM                                    \
)( state, elem )

#define BOOST_GENERIC_DETAIL_PROPER_ARGUMENT_FORM( state, elem )               \
BOOST_PP_IIF                                                                   \
( BOOST_PP_EQUAL                                                               \
  ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( ( switch ) )                 \
  )                                                                            \
, BOOST_GENERIC_DETAIL_CHECK_SWITCH_OPENER_REQUIREMENT                         \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT                                  \
)( state, elem )

// ToDo: Check for template parameter
#define BOOST_GENERIC_DETAIL_CHECK_SWITCH_OPENER_REQUIREMENT(state,elem)       \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_NONBASIC                          \
  ( BOOST_GENERIC_DETAIL_ARG_DETS_PARAM_LIST_DETS( state ) )                   \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT                                  \
, BOOST_GENERIC_DETAIL_SWITCH_USED_WITH_BASIC_PARAM_LIST                       \
)( state, elem )

// Yields 1 if there were errors, otherwise it yields 0
#define BOOST_GENERIC_DETAIL_HAS_ERRORS( error_array )                         \
BOOST_PP_BOOL( BOOST_PP_ARRAY_SIZE( error_array ) )

// Yields all errors as statements
#define BOOST_GENERIC_DETAIL_EMIT_ERRORS( error_array )                        \
BOOST_PP_IF( BOOST_PP_ARRAY_SIZE( error_array )                                \
           , BOOST_GENERIC_DETAIL_EMIT_ERRORS_IMPL                             \
           , BOOST_GENERIC_DETAIL_EMIT_NO_ERRORS_IMPL                          \
           )( error_array )

// Do nothing if there are no errors to emit
#define BOOST_GENERIC_DETAIL_EMIT_NO_ERRORS_IMPL( error_array )

// Yields all errors as statements (only valid if array size is greater than 1)
#define BOOST_GENERIC_DETAIL_EMIT_ERRORS_IMPL( error_array )                   \
void BOOST_PP_CAT( failed_auto_function_on_line_, __LINE__ )();                \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_GENERIC_DETAIL_EMIT_ERROR_IMPL, ~                                      \
, BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ( error_array )                             \
)

// Yields an error as a statement
#define BOOST_GENERIC_DETAIL_EMIT_ERROR_IMPL( r, dummy, error ) error;

#endif // BOOST_GENERIC_DETAIL_ARG_DETAILS_HPP
