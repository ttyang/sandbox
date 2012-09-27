/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_THIS_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_THIS_DETAILS_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/ordered_iif.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/generic/detail/seq_size.hpp>
#include <boost/generic/detail/this/function_dets.hpp>
#include <boost/generic/detail/this/typename_dets.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/replace.hpp>

// A "this" parameter specifies a series of member requirement.
// It is of the form:
//   ( this (type_name)
//   , requirement0
//   , requirement1
//   , etc.
//   )

// a this requirement is specified as:
//   ( this name )
// -or-
//   ( this name, (default_type) )

// Result is of the form:
// (validity_bit)((type))((requirement_seq_dets))
// (is_partial_bit)((error_macro_seq))

// requirement_seq_dets is a sequence of requirement specifications
// Each element of the sequence is of the form:
// ( id_name )( details )((error_msgs_seq))
// id_name is one of:
//   if
//   typename
//   function // ToDo: Add support for auto function declarations
//   type_template
//   function_template
//   unknown
//   fatal_error (i.e. unparenthesized arg, abort processing)
//
// "details" are the details corresponding to that parameter
// requirement_seq_dets may be empty, in which case there are no params
//
// error_msg_seq is either empty or a sequence of c-strings representing errors
#define BOOST_GENERIC_DETAIL_THIS_DETS( ... )                                  \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( __VA_ARGS__ )             \
            , BOOST_GENERIC_DETAIL_THIS_DETS_IMPL                              \
            , BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_INVALID                      \
            )( __VA_ARGS__ )


// expands to:
// macro(validity_bit, (return_type), name, param_list_details
//      , (definition) -or- empty parameter if no defition
//      )
#define BOOST_GENERIC_DETAIL_THIS_DETS_VISIT( dets, typename_macros            \
                                            , function_macros                  \
                                            )                                  \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_THIS_DETS_IS_VALID( dets )                  \
            , BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_IMPL                        \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( dets, typename_macros, function_macros )

#define BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_IMPL( dets, typename_macros       \
                                                 , function_macros             \
                                                 )                             \
BOOST_GENERIC_DETAIL_REMOVE_PAREN                                              \
( BOOST_PP_SEQ_ELEM                                                            \
  ( 1, BOOST_PP_SEQ_FOLD_LEFT                                                  \
       ( BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_VALID_IMPL_MACRO                 \
       , ( ( (BOOST_GENERIC_DETAIL_THIS_DETS_TYPE( dets ))                     \
           , typename_macros, function_macros                                  \
           )                                                                   \
         )(())                                                                 \
       , BOOST_GENERIC_DETAIL_THIS_DETS_REQUIREMENTS( dets )                   \
       )                                                                       \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_VALID_IMPL_MACRO( s, state, dets )\
BOOST_PP_SEQ_REPLACE                                                           \
( state, 1                                                                     \
, ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, state ) )         \
    BOOST_PP_CAT                                                               \
    ( BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_IMPL                                \
    , BOOST_GENERIC_DETAIL_THIS_DETS_REQ_DETS_TAG( dets )                      \
    )( BOOST_GENERIC_DETAIL_THIS_DETS_REQ_DETS_DETS( dets )                    \
     , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, state ) )      \
     )                                                                         \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_IMPLtypename( ... )               \
BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_IMPLtypename_( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_IMPLtypename_( dets               \
                                                          , this_type          \
                                                          , typename_macros    \
                                                          , function_macros    \
                                                          )                    \
BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_VISIT                                  \
( dets, this_type                                                              \
, BOOST_PP_SEQ_ELEM( 0, typename_macros )                                      \
, BOOST_PP_SEQ_ELEM( 1, typename_macros )                                      \
)


#define BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_IMPLfunction( ... )               \
BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_IMPLfunction_( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_THIS_DETS_VISIT_IMPLfunction_( dets               \
                                                          , this_type          \
                                                          , typename_macros    \
                                                          , function_macros    \
                                                          )                    \
BOOST_GENERIC_DETAIL_THIS_FUNCTION_DETS_VISIT                                  \
( dets, this_type                                                              \
, BOOST_PP_SEQ_ELEM( 0, function_macros )                                      \
, BOOST_PP_SEQ_ELEM( 1, function_macros )                                      \
)

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL( ... )                             \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_WITH_THIS                                        \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( __VA_ARGS__ ) )                         \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_IS_THIS                                  \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_INVALID                                  \
)( BOOST_GENERIC_DETAIL_REMOVE_PAREN( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IS_VALID( dets )                        \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_THIS_DETS_REQUIREMENTS( dets )                    \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_THIS_DETS_REQ_DETS_TAG( dets )                    \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_THIS_DETS_REQ_DETS_DETS( dets )                   \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IS_PARTIAL( dets )                      \
BOOST_PP_SEQ_ELEM( 3, dets )

#define BOOST_GENERIC_DETAIL_THIS_DETS_TYPE( dets )                            \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, dets ) )

#define BOOST_GENERIC_DETAIL_THIS_DETS_REQUIREMENTS( dets )                    \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_THIS_DETS_HAS_REQUIREMENTS( dets )                \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_THIS_DETS_REQUIREMENTS( dets ) )                      \
)

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_INVALID( ... )                     \
(0)(())(())(0)((("Not a \"this\" declaration.")))

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_PARTIAL_INVALID( ... )             \
(0)(())(())(1)((("Invalid \"this\" declaration.")))

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_IS_THIS( ... )                     \
BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_EATEN_THIS                                 \
( BOOST_GENERIC_DETAIL_EAT_THIS( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_EATEN_THIS( ... )                  \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_PARENTHESIZED                                        \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_EATEN_THIS_PAREN                         \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_PARTIAL_INVALID                          \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_EATEN_THIS_PAREN( ... )            \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_WRAPPED_EMPTY                                        \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_PARTIAL_INVALID                          \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_FIRST_PART_VALID                         \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_FIRST_PART_VALID( ... )            \
BOOST_PP_IIF( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ ), 1 )\
            , BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_VALID_NO_NESTED              \
            , BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAMS                \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_VALID_NO_NESTED( this_t )          \
(1)(this_t)(())(1)

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_NAME( dets )     \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_DETS( dets )     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, dets ) )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_IS_VALID(dets)   \
BOOST_PP_SEQ_ELEM( 2, dets )

// Note: The while state is
//    (curr_index)(seq)(param_dets_seq)(has_errors_bit)
// Where param_dets_seq is a sequence of elements of the form:
//    (param_name)(param_dets)( (error_msg_seq) )
#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAMS( this_t, ... )       \
BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_WHILE_STATE_TO_DETS                        \
( this_t                                                                       \
, BOOST_PP_WHILE                                                               \
  ( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_PRED                      \
  , BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_OP                        \
  , BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAMS_INITIAL_STATE            \
    ( BOOST_GENERIC_DETAIL_SEQ_TO_SEQ                                          \
      ( BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( __VA_ARGS__ ) )                 \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_WHILE_STATE_TO_DETS( this_t,state )\
(BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_IS_VALID(state))                          \
(this_t)                                                                       \
((BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_DETS(state)))                            \
(1)                                                                            \
((BOOST_PP_IIF                                                                 \
  ( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_IS_VALID(state)                        \
  , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                                        \
  , BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( ("Invalid \"this\" parameter.") )  \
  )()                                                                          \
))

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_CURR_INDEX( state )                \
BOOST_PP_SEQ_ELEM( 0, state )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_SEQ( state )                       \
BOOST_PP_SEQ_ELEM( 1, state )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_DETS( state )                      \
BOOST_PP_SEQ_ELEM( 2, state )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_IS_VALID( state )                  \
BOOST_PP_SEQ_ELEM( 3, state )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_PRED( d, state )      \
BOOST_PP_COMPL                                                                 \
( BOOST_PP_BITOR                                                               \
  ( BOOST_PP_EQUAL                                                             \
    ( BOOST_PP_INC( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_CURR_INDEX( state ) )  \
    , BOOST_GENERIC_DETAIL_SEQ_SIZE                                            \
      ( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_SEQ( state ) )                     \
    )                                                                          \
  , BOOST_PP_COMPL( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_IS_VALID( state ) )    \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_OP( d, state )        \
BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_OP_IMPL                       \
( state                                                                        \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_IMPL                   \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN                                          \
    ( BOOST_PP_SEQ_ELEM                                                        \
      ( BOOST_PP_INC( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_CURR_INDEX( state ) )\
      , BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_SEQ( state )                       \
      )                                                                        \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_OP_IMPL( state, dets )\
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_CURR_INDEX( state ) ) )    \
( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_SEQ( state ) )                           \
( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_DETS(state)(dets) )                      \
( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_IS_VALID( dets ) )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAMS_INITIAL_STATE( seq ) \
BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAMS_INITIAL_STATE_IMPL           \
( seq                                                                          \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_IMPL                   \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, seq ) ) )         \
)

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAMS_INITIAL_STATE_IMPL(  \
                                                                           seq \
                                                                         , dets\
                                                                         )     \
(0)                                                                            \
(seq)                                                                          \
((dets))                                                                       \
( BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_IS_VALID( dets ) )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_TAG_TYPENAME( dets )               \
(typename)(dets)(1)

#define BOOST_GENERIC_DETAIL_THIS_DETS_ANALYZE_TYPENAME_PARTIAL( dets )        \
(typename)(dets)(0)

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_TAG_FUNCTION( dets )               \
(function)(dets)(1)

#define BOOST_GENERIC_DETAIL_THIS_DETS_ANALYZE_FUNCTION_PARTIAL( dets )        \
(function)(dets)(0)

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_IMPL( elem )     \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( elem )                                \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_IMPL_PAREN             \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_IMPL_NOT_PAREN         \
)( elem )

#define BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_NESTED_PARAM_DETS_IMPL_PAREN(elem) \
BOOST_GENERIC_DETAIL_ORDERED_IIF                                               \
( elem                                                                         \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_UNRECOGNIZED_NESTED_PARAM                \
, (BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS)                                    \
  (BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IS_PARTIAL)                         \
  (BOOST_GENERIC_DETAIL_THIS_DETS_ANALYZE_TYPENAME)                            \
, (BOOST_GENERIC_DETAIL_THIS_FUNCTION_DETS)                                    \
  (BOOST_GENERIC_DETAIL_THIS_FUNCTION_DETS_IS_PARTIAL)                         \
  (BOOST_GENERIC_DETAIL_THIS_DETS_ANALYZE_FUNCTION)                            \
)

#define BOOST_GENERIC_DETAIL_THIS_DETS_ANALYZE_TYPENAME( dets )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_THIS_TYPENAME_DETS_IS_VALID( dets )                     \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_TAG_TYPENAME                             \
, BOOST_GENERIC_DETAIL_THIS_DETS_ANALYZE_TYPENAME_PARTIAL                      \
)( dets )

#define BOOST_GENERIC_DETAIL_THIS_DETS_ANALYZE_FUNCTION( dets )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID_WITHOUT_DEFINITION( dets )  \
, BOOST_GENERIC_DETAIL_THIS_DETS_IMPL_TAG_FUNCTION                             \
, BOOST_GENERIC_DETAIL_THIS_DETS_ANALYZE_FUNCTION_PARTIAL                      \
)( dets )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_THIS( ... )                           \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )                     \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPL                                   \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPL( ... )                      \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN                                   \
  ( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                          \
    ( BOOST_GENERIC_DETAIL_STARTS_WITH_THIS                                    \
    , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) foo                    \
    )                                                                          \
  )                                                                            \
, 2                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_THISthis ,

#define BOOST_GENERIC_DETAIL_EAT_THIS( ... )                                   \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_THIS, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_THISthis

#endif // BOOST_GENERIC_DETAIL_THIS_DETAILS_HPP
