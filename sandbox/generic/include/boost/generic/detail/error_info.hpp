/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_ERROR_INFO_HPP
#define BOOST_GENERIC_DETAIL_ERROR_INFO_HPP

#include <boost/generic/detail/args_to_sequence.hpp>
#include <boost/generic/detail/array_to_seq.hpp>
#include <boost/generic/detail/error.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/is_recognized_arg.hpp>
#include <boost/generic/detail/is_valid_name_and_params.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/param.hpp>
#include <boost/generic/detail/param_id.hpp>
#include <boost/generic/detail/param_id_category_value.hpp>
#include <boost/generic/detail/param_id_implies_parentheses.hpp>
#include <boost/generic/support.hpp>
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
#include <boost/preprocessor/seq/size.hpp>

// Takes in the parameters passed to BOOST_GENERIC as a sequence. The
// sequence should not include the initial argument of concept name.
// It yields a sequence of 3 element tuples of an argument number of the error
// message as a string, and an identifier-format error message
// ToDo: Handle no errors
#define BOOST_GENERIC_DETAIL_CONCEPT_ERROR_INFO( ... )                         \
BOOST_GENERIC_DETAIL_ERROR_INFO_IMPL                                           \
( BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( __VA_ARGS__ ) )

// Check the first argument (the parameters) for errors
#define BOOST_GENERIC_DETAIL_CHECK_FIRST_ARG( first_arg )                      \
BOOST_GENERIC_DETAIL_CHECK_FIRST_ARG_IMPL                                      \
( BOOST_PP_IIF                                                                 \
  ( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( first_arg )                     \
  , (0)((0,()))                                                                \
  , (1)((1,(BOOST_GENERIC_DETAIL_INVALID_CONCEPT_PARAMS_ERROR())))             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_PARAM_CATEGORY_BIT_TABLE_EMPTY()                  \
BOOST_PP_REPEAT                                                                \
( BOOST_GENERIC_DETAIL_NUM_PARAM_CATEGORIES                                    \
, BOOST_GENERIC_DETAIL_PARAM_CATEGORY_BIT_TABLE_EMPTY_MACRO                    \
, ~                                                                            \
)

#define BOOST_GENERIC_DETAIL_PARAM_CATEGORY_BIT_TABLE_EMPTY_MACRO( z, n, t )   \
((0))

#define BOOST_GENERIC_DETAIL_CHECK_FIRST_ARG_IMPL( first_arg_errors )          \
( BOOST_PP_SEQ_ELEM( 0, first_arg_errors ) )( 2 )                              \
  ( BOOST_GENERIC_DETAIL_PARAM_CATEGORY_BIT_TABLE_EMPTY() )                    \
( BOOST_PP_SEQ_ELEM( 1, first_arg_errors ) )

// Same as above only it yields an array instead of a sequence
// State is a sequence of:
//   A bit specifying if a fatal error was encountered
//     (in which case we don't try to parse any more arguments)
//
//   A value specifying the current argument number
//     (starts at 2 since error handling for the first arg is handled elsewhere)
//
//   A sequence of sequences of category info where the first element is a
//     bit that specifies whether or not the category was encountered. If and
//     only if the first element is 1, there is a second element which
//     specifies the line number where the first occurrence of the category
//     appeared
//
//   An array of errors
#define BOOST_GENERIC_DETAIL_ERROR_INFO_IMPL( args_as_seq )                    \
BOOST_PP_IIF( BOOST_PP_EQUAL( BOOST_PP_SEQ_SIZE( args_as_seq ), 1 )            \
            , BOOST_GENERIC_DETAIL_ERROR_INFO_IMPL_SIZE_1                      \
            , BOOST_GENERIC_DETAIL_ERROR_INFO_IMPL_NOT_SIZE_1                  \
            )( args_as_seq )

#define BOOST_GENERIC_DETAIL_ERROR_INFO_IMPL_SIZE_1( args_as_seq )             \
BOOST_PP_SEQ_ELEM                                                              \
( 3, BOOST_GENERIC_DETAIL_CHECK_FIRST_ARG                                      \
     ( BOOST_PP_SEQ_HEAD( args_as_seq ) )                                      \
)

#define BOOST_GENERIC_DETAIL_ERROR_INFO_IMPL_NOT_SIZE_1( args_as_seq )         \
BOOST_PP_SEQ_ELEM                                                              \
( 3, BOOST_PP_SEQ_FOLD_LEFT                                                    \
     ( BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO                                   \
     , BOOST_GENERIC_DETAIL_CHECK_FIRST_ARG                                    \
       ( BOOST_PP_SEQ_HEAD( args_as_seq ) )                                    \
     , BOOST_PP_SEQ_TAIL( args_as_seq )                                        \
     )                                                                         \
)

// Invoked when no error is found (updates line counter and categories)
#define BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT( data, elem )              \
( BOOST_PP_SEQ_ELEM( 0, data ) )                                               \
( BOOST_PP_INC( BOOST_PP_SEQ_ELEM( 1, data ) ) )                               \
( BOOST_PP_SEQ_REPLACE                                                         \
  ( BOOST_PP_SEQ_ELEM( 2, data )                                               \
  , BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                       \
  , ( 1 )( BOOST_PP_SEQ_ELEM( 1, data ) )                                      \
  )                                                                            \
)                                                                              \
( BOOST_PP_SEQ_ELEM( 3, data ) )

// Update the "fold" state when we hit an argument that should take a sequence
// but it is detected that the argument does not have parentheses
#define BOOST_GENERIC_DETAIL_ARG_ARG_NOT_PAREN_INFO( data, elem )              \
( BOOST_PP_SEQ_ELEM( 0, data ) )                                               \
( BOOST_PP_INC( BOOST_PP_SEQ_ELEM( 1, data ) ) )                               \
( BOOST_PP_SEQ_ELEM( 2, data ) )                                               \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_PP_SEQ_ELEM( 3, data )                                               \
  , BOOST_GENERIC_DETAIL_ERROR_ARG_ARG_NOT_PAREN                               \
    ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                                  \
  )                                                                            \
)

// Update the "fold" state when we hit an argument that duplicates a
// category that was already encountered
#define BOOST_GENERIC_DETAIL_DUPLICATE_CATEGORY_INFO( data, elem )             \
( BOOST_PP_SEQ_ELEM( 0, data ) )                                               \
( BOOST_PP_INC( BOOST_PP_SEQ_ELEM( 1, data ) ) )                               \
( BOOST_PP_SEQ_ELEM( 2, data ) )                                               \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_PP_SEQ_ELEM( 3, data )                                               \
  , BOOST_GENERIC_DETAIL_ERROR_MULTIPLE_OF_CATEGORY                            \
    ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY( elem )                           \
    , BOOST_PP_SEQ_ELEM( 1, data )                                             \
    , BOOST_PP_SEQ_ELEM                                                        \
      ( 1                                                                      \
      , BOOST_PP_SEQ_ELEM                                                      \
        ( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )                 \
        , BOOST_PP_SEQ_ELEM( 2, data )                                         \
        )                                                                      \
      )                                                                        \
    )                                                                          \
  )                                                                            \
)

// Update the "fold" state when we hit an argument that wasn't parenthesized
// An argument that isn't parenthesized is a fatal error and we can't parse
// anything after that since we can't know whether or not commas there are
// intended to end that argument or if they are supposed to be a part of that
// argument
#define BOOST_GENERIC_DETAIL_NOT_PARENTHESIZED( data, elem )                   \
( 1 )                                                                          \
( ~ )                                                                          \
( ~ )                                                                          \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_PP_SEQ_ELEM( 3, data )                                               \
  , BOOST_GENERIC_DETAIL_ERROR_NOT_PARENTHESIZED                               \
    ( BOOST_PP_SEQ_ELEM( 1, data ), elem )                                     \
  )                                                                            \
)

// Update the "fold" state when we hit an unrecognized param id
#define BOOST_GENERIC_DETAIL_UNRECOGNIZED_ARG( data, elem )                    \
( BOOST_PP_SEQ_ELEM( 0, data ) )                                               \
( BOOST_PP_INC( BOOST_PP_SEQ_ELEM( 1, data ) ) )                               \
( BOOST_PP_SEQ_ELEM( 2, data ) )                                               \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_PP_SEQ_ELEM( 3, data )                                               \
  , BOOST_GENERIC_DETAIL_ERROR_UNRECOGNIZED_PARAM_ID                           \
    ( BOOST_PP_SEQ_ELEM( 1, data ), elem )                                     \
  )                                                                            \
)

// On a fatal error don't bother trying to parse any more arguments
#define BOOST_GENERIC_DETAIL_FORWARD_FATAL_ERROR( data, elem ) data

// Determines if the category of this argument has already appeared
#define BOOST_GENERIC_DETAIL_IS_DUPLICATE_CATEGORY( data, elem )               \
BOOST_PP_SEQ_ELEM                                                              \
( 0                                                                            \
, BOOST_PP_SEQ_ELEM( BOOST_GENERIC_DETAIL_PARAM_ID_CATEGORY_VALUE( elem )\
                   , BOOST_PP_SEQ_ELEM( 2, data )                              \
                   )                                                           \
)

// Update the "fold" state when we hit a parameter kind that we can't support
#define BOOST_GENERIC_DETAIL_ERROR_NO_SUPPORT_INFO( data, elem )               \
( BOOST_PP_SEQ_ELEM( 0, data ) )                                               \
( BOOST_PP_INC( BOOST_PP_SEQ_ELEM( 1, data ) ) )                               \
( BOOST_PP_SEQ_ELEM( 2, data ) )                                               \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_PP_SEQ_ELEM( 3, data )                                               \
  , BOOST_GENERIC_DETAIL_ERROR_NO_PARAM_SUPPORT                                \
    ( BOOST_GENERIC_DETAIL_PARAM_ID( elem )                                    \
    , BOOST_PP_SEQ_ELEM( 1, data )                                             \
    )                                                                          \
  )                                                                            \
)

// Checks starting after we have recognized the parameter kind
#define BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_RECOGNIZED( data, elem )         \
BOOST_PP_IIF                                                                   \
( BOOST_NO_BOOST_GENERIC_CONCEPT_PARAM                                         \
  ( BOOST_GENERIC_DETAIL_PARAM_ID( elem ) )                                    \
, BOOST_GENERIC_DETAIL_ERROR_NO_SUPPORT_INFO                                   \
, BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_SUPPORTED                              \
)( data, elem )

// Checks starting after we have determined that the parameter kind is supported
#define BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_SUPPORTED( data, elem )          \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_DUPLICATE_CATEGORY( data, elem )                     \
, BOOST_GENERIC_DETAIL_DUPLICATE_CATEGORY_INFO                                 \
, BOOST_GENERIC_DETAIL_ERROR_NO_DUPLICATE                                      \
)( data, elem )

#define BOOST_GENERIC_DETAIL_LACKS_PARENT_FOR_ARG( data, elem )                \
BOOST_PP_BITAND                                                                \
( BOOST_GENERIC_DETAIL_PARAM_ID_IMPLIES_PARENTHESES( elem )                    \
, BOOST_PP_COMPL                                                               \
  ( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                  \
    ( BOOST_GENERIC_DETAIL_PARAM( elem ) )                                     \
  )                                                                            \
)

// Checks starting after we have determined that there is not a duplicate
#define BOOST_GENERIC_DETAIL_ERROR_NO_DUPLICATE( data, elem )                  \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_LACKS_PARENT_FOR_ARG( data, elem )                      \
, BOOST_GENERIC_DETAIL_ARG_ARG_NOT_PAREN_INFO                                  \
, BOOST_GENERIC_DETAIL_NO_ERROR_WITH_ARGUMENT                                  \
)( data, elem )

// Checks starting after it is established that the argument is parenthesized
#define BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_PARENTHESIZED( data, elem )      \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_RECOGNIZED_ARG( elem )                               \
, BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_RECOGNIZED                             \
, BOOST_GENERIC_DETAIL_UNRECOGNIZED_ARG                                        \
)( data, elem )

// data is a 2 element tuple of the current argument number and an array of
// tuples of argument numbers and the associated unrecognized argument
// ToDo: Push off some of the checks to other macros to prevent errors when not
// parenthesized properly or when there are too many commas
#define BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO( s, data, elem )                 \
BOOST_PP_IIF                                                                   \
( BOOST_PP_SEQ_ELEM( 0, data )                                                 \
, BOOST_GENERIC_DETAIL_FORWARD_FATAL_ERROR                                     \
, BOOST_PP_IIF                                                                 \
  ( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( elem )                          \
  , BOOST_GENERIC_DETAIL_ERROR_INFO_MACRO_PARENTHESIZED                        \
  , BOOST_GENERIC_DETAIL_NOT_PARENTHESIZED                                     \
  )                                                                            \
)( data, elem )

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
void BOOST_PP_CAT( failed_concept_on_line_, __LINE__ )();                      \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_GENERIC_DETAIL_EMIT_ERROR_IMPL, ~                                      \
, BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ( error_array )                             \
)

// Yields an error as a statement
#define BOOST_GENERIC_DETAIL_EMIT_ERROR_IMPL( r, dummy, error ) error;

#endif // BOOST_GENERIC_DETAIL_ERROR_INFO_HPP
