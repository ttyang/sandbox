/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_HPP

#include <boost/generic/detail/array_to_seq.hpp>
#include <boost/generic/detail/concept/name_param_details.hpp>
#include <boost/generic/detail/is_conditional_arg.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/is_recognized_arg.hpp>
#include <boost/generic/detail/map_name_params_details.hpp>
#include <boost/generic/detail/param.hpp>
#include <boost/generic/detail/param_id.hpp>
#include <boost/generic/detail/param_id_category.hpp>
#include <boost/generic/detail/param_id_category_value.hpp>
#include <boost/generic/detail/param_id_implies_parentheses.hpp>
#include <boost/generic/detail/param_list.hpp>
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

// Takes the parameters to the auto concept macro of the format:
//
//   template decl, ( concept name )( concept_params... ), named macro params...
//
// and puts it into an easy-access datastructure of the format:
//
//   A bit specifying if a fatal error was encountered
//     (in which case we may abort parsing arguments midway through)
//
//   The template parameter details
//
//   The name and param dets
//
//   A value specifying the current argument number
//
//   An array of errors
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS( ... )               \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_IMPL                         \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS                                      \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( __VA_ARGS__ )                           \
) // ToDo: Verify there are at least 2 arguments

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_IMPL(param_dets, ...)\
BOOST_PP_IF                                                                    \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID( param_dets )               \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_IMPL_NO_PARAM_ERROR        \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_IMPL_PARAM_ERRORS          \
)( param_dets, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_IMPL_NO_PARAM_ERROR( \
                                                                param_dets     \
                                                              , ...            \
                                                              )                \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_IMPL_NO_PARAM_ERROR_         \
( param_dets, BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_IMPL_NO_PARAM_ERROR_(\
                                                                param_dets     \
                                                              , name_param_dets\
                                                              )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_MAP_NAME_PARAMS_DETS_IS_VALID( name_param_dets )        \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_NO_ERROR                   \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_NAME_PARAMS_ERROR          \
)( param_dets, name_param_dets )

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

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_NO_ERROR( tpl_dets   \
                                                           , name_param_dets   \
                                                           )                   \
( 0 )                                                                          \
( tpl_dets )                                                                   \
( name_param_dets )                                                            \
( 2 )                                                                          \
( ( 0, () ) )

// ToDo: Provide more detailed error information.
//       Was the arg not parenthesized?
//       Was the sequence not of size 2?
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_IMPL_PARAM_ERRORS(   \
                                                                       tpl_dets\
                                                                     , ...     \
                                                                     )         \
( 1 )                                                                          \
( tpl_dets )                                                                   \
( ~ )                                                                          \
( 1 )                                                                          \
( ( 1                                                                          \
  , ( static_assert                                                            \
      ( false                                                                  \
      , "Improperly formatted template parameters specified for auto concept " \
        "map."                                                                 \
      )                                                                        \
    )                                                                          \
  )                                                                            \
)

// ToDo: Provide more detailed error information.
//       Was the arg not parenthesized?
//       Was the sequence not of size 2?
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_NAME_PARAMS_ERROR(   \
                                                                tpl_dets       \
                                                              , name_param_dets\
                                                              )                \
( 1 )                                                                          \
( tpl_dets )                                                                   \
( name_param_dets )                                                            \
( 2 )                                                                          \
( ( 1                                                                          \
  , ( static_assert                                                            \
      ( false                                                                  \
      , "Improperly formatted concept name and parameters specified for auto " \
        "concept map."                                                         \
      )                                                                        \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_FATAL_ERROR( state )    \
BOOST_PP_SEQ_ELEM( 0, state )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_TPL_DETS( state )       \
BOOST_PP_SEQ_ELEM( 1, state )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_CONCEPT_NAME_PARAM_DETS(\
                                                                        state )\
BOOST_PP_SEQ_ELEM( 2, state )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_ARG_NUM( state )        \
BOOST_PP_SEQ_ELEM( 3, state )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_ERRORS( state )         \
BOOST_PP_SEQ_ELEM( 4, state )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_HAS_ERRORS( state )     \
BOOST_PP_BOOL                                                                  \
( BOOST_PP_ARRAY_SIZE                                                          \
  ( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_ERRORS( state ) )           \
)

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_ERRORS( state )             \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_ERRORS_                             \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_ERRORS( state ) )

// Yields all errors as statements
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_ERRORS_( error_array )      \
BOOST_PP_IF( BOOST_PP_ARRAY_SIZE( error_array )                                \
           , BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_ERRORS_IMPL            \
           , BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_NO_ERRORS_IMPL         \
           )( error_array )

// Do nothing if there are no errors to emit
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_NO_ERRORS_IMPL( error_array )

// Yields all errors as statements (only valid if array size is greater than 1)
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_ERRORS_IMPL( error_array )  \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_ERROR_IMPL, ~                     \
, BOOST_GENERIC_DETAIL_ARRAY_TO_SEQ( error_array )                             \
)

// Yields an error as a statement
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_ERROR_IMPL(r, dummy, error )\
error;

#endif // BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS_HPP
