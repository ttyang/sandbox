/*==============================================================================
    Copyright (c) 2010, 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_HPP

#include <boost/generic/detail/args_to_sequence.hpp>
#include <boost/generic/detail/concept_map/typedef_dets.hpp>
#include <boost/generic/detail/function_decl_details.hpp>
#include <boost/generic/detail/no_return_dets.hpp>
#include <boost/generic/detail/is_error.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/ordered_iif.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/generic/detail/seq_size.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

// satisfier_seq_dets is a sequence of requirement specifications
// Each element of the sequence is of the form:
// ( id_name )( simplified_details )
//
// id_name is one of:                    and simplified_details is:
//   typedef                               ( everything )
//
//   function                              ( return_type_in_paren
//                                         , name
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   member_function                       ( return_type_in_paren
//                                         , this_type_in_paren, name
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   static_member_function                ( return_type_in_paren
//                                         , this_type_in_paren, name
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   prefix_unary_operator                 ( return_type_in_paren
//                                         , operator
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   postfix_unary_operator                ( return_type_in_paren
//                                         , operator
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   binary_operator                       ( return_type_in_paren
//                                         , operator
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   call_operator                         ( return_type_in_paren
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   comma_operator                        ( return_type_in_paren
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   arrow_operator                        ( return_type_in_paren
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   assign_operator                       ( return_type_in_paren
//                                         , this_type_in_paren
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   allocation_operator                   ( return_type_in_paren
//                                         , this_type_in_paren
//                                         , operator
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   deallocation_operator                 ( return_type_in_paren
//                                         , this_type_in_paren
//                                         , operator
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   constructor                           ( this_type_in_paren, param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   explicit_constructor                  ( this_type_in_paren, param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   destructor                            ( this_type_in_paren
//                                         , def_or_empty_in_paren
//                                         )
//
//   conversion                            ( target_type_in_paren
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   explicit_conversion                   ( target_type_in_paren
//                                         , param_list_dets
//                                         , def_or_empty_in_paren
//                                         )
//
//   type_template                         ( param_list_dets, name )
//
//   error                                 ( error_message_in_quotes )
//
// "details" are the details corresponding to that parameter
// requirement_seq_dets may be empty, in which case there are no params
#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS( ... )                      \
BOOST_PP_IIF( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ ), 0 )\
            , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_INVALID_EMPTY    \
            , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL                  \
            )( BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_INVALID_EMPTY( ... )   \
(0)(())("Empty Parameter")

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_VISIT( dets, macro_base     \
                                                        , index_base, data     \
                                                        )                      \
BOOST_PP_SEQ_FOR_EACH_I                                                        \
( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_VISIT_IMPL                        \
, (macro_base)(index_base)(data)                                               \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_SATISFIERS( dets )                \
)

// ToDo: Get rid of the add! Rewrite to use inc instead
#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_VISIT_IMPL( r, data, i      \
                                                             , elem            \
                                                             )                 \
BOOST_GENERIC_DETAIL_SELF                                                      \
( BOOST_PP_CAT( BOOST_PP_SEQ_ELEM( 0, data ), BOOST_PP_SEQ_ELEM( 0, elem ) )   \
  BOOST_GENERIC_DETAIL_SELF                                                    \
  ( ( BOOST_PP_ADD( BOOST_PP_SEQ_ELEM( 1, data ), i )                          \
    , BOOST_PP_SEQ_ELEM( 2, data )                                             \
    , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, elem ) )        \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_VALID_EMPTY( ... )     \
(1)(())

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL( args )                \
BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_WHILE_STATE_TO_DETS            \
( BOOST_PP_WHILE                                                               \
  ( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_PRED                 \
  , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_OP                   \
  , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAMS_INITIAL_STATE       \
    ( BOOST_GENERIC_DETAIL_SEQ_TO_SEQ( args ) )                                \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IS_VALID( dets )            \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_SATISFIERS( dets )          \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_WHILE_STATE_TO_DETS(   \
                                                                          state\
                                                                        )      \
( BOOST_PP_COMPL                                                               \
  ( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_HAS_ERRORS( state ) )      \
)                                                                              \
( ( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_DETS( state ) ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_CURR_INDEX( state )    \
BOOST_PP_SEQ_ELEM( 0, state )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_SEQ( state )           \
BOOST_PP_SEQ_ELEM( 1, state )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_DETS( state )          \
BOOST_PP_SEQ_ELEM( 2, state )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_HAS_ERRORS( state )    \
BOOST_PP_SEQ_ELEM( 3, state )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_PRED( d, state ) \
BOOST_PP_COMPL                                                                 \
( BOOST_PP_BITOR                                                               \
  ( BOOST_PP_EQUAL                                                             \
    ( BOOST_PP_INC                                                             \
      ( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_CURR_INDEX( state ) )  \
    , BOOST_GENERIC_DETAIL_SEQ_SIZE                                            \
      ( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_SEQ( state ) )         \
    )                                                                          \
  , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_HAS_ERRORS( state )        \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_OP( d, state )   \
BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_OP_IMPL                  \
( state                                                                        \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_DETS_IMPL              \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN                                          \
    ( BOOST_PP_SEQ_ELEM                                                        \
      ( BOOST_PP_INC                                                           \
        ( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_CURR_INDEX( state ) )\
      , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_SEQ( state )           \
      )                                                                        \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_OP_IMPL( state   \
                                                                     , dets    \
                                                                     )         \
( BOOST_PP_INC                                                                 \
  ( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_CURR_INDEX( state ) )      \
)                                                                              \
( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_SEQ( state ) )               \
( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_DETS(state)(dets) )          \
( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAGGED_DETS_IS_ERROR( dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAMS_INITIAL_STATE(  \
                                                                            seq\
                                                                          )    \
BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAMS_INITIAL_STATE_IMPL      \
( seq                                                                          \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_DETS_IMPL              \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, seq ) ) )         \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAMS_INITIAL_STATE_IMPL(seq, dets)\
(0)                                                                            \
(seq)                                                                          \
((dets))                                                                       \
( BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAGGED_DETS_IS_ERROR( dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAGGED_DETS_TAG( dets )\
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAGGED_DETS_DETS(dets) \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAGGED_DETS_IS_ERROR(  \
                                                                           dets\
                                                                         )     \
BOOST_GENERIC_DETAIL_STARTS_WITH_ERROR( BOOST_PP_SEQ_ELEM( 0, dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_TYPEDEF( dets )    \
(typedef)                                                                      \
( ( ( BOOST_GENERIC_DETAIL_TYPEDEF_DETS_DEFINITION( dets ) ) ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_TYPEDEF_PARTIAL(    \
                                                                           dets\
                                                                         )     \
(error)( BOOST_GENERIC_DETAIL_TYPEDEF_DETS_ERROR( dets ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_FUNCTION( dets )   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_OPERATOR( dets )      \
            , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_OPERATOR     \
            , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONOPERATOR  \
            )( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONOPERATOR( dets )\
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION( dets )           \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_MEMBER_FUNCTION          \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONMEMBER_FUNCTION       \
)( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_MEMBER_FUNCTION(   \
                                                                           dets\
                                                                         )     \
(BOOST_PP_IIF                                                                  \
 ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_STATIC( dets )                   \
 , static_member_function                                                      \
 , member_function                                                             \
 )                                                                             \
)                                                                              \
( ( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_TYPE( dets ) )              \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME( dets )                       \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets ) )             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONMEMBER_FUNCTION(\
                                                                           dets\
                                                                         )     \
(function)                                                                     \
( ( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )            \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME( dets )                       \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets ) )             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_OPERATOR( dets )   \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION( dets )           \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_MEMBER_OPERATOR          \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONMEMBER_OPERATOR       \
)( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_MEMBER_OPERATOR(   \
                                                                           dets\
                                                                         )     \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_ASSIGN                                               \
  ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR_NAME( dets ) )     \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_ASSIGN_OPERATOR          \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONASSIGN_MEMBER_OPERATOR\
)( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONASSIGN_MEMBER_OPERATOR(dets )\
(BOOST_GENERIC_DETAIL_OPERATOR_KIND                                            \
 (BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR_NAME( dets ))        \
)                                                                              \
( ( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_TYPE( dets ) )              \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR( dets )            \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets ) )             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_ASSIGN_OPERATOR(   \
                                                                           dets\
                                                                         )     \
(BOOST_GENERIC_DETAIL_OPERATOR_KIND                                            \
 (BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR_NAME( dets ))        \
)                                                                              \
( ( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_TYPE( dets ) )              \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets ) )             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONMEMBER_OPERATOR(\
                                                                           dets\
                                                                         )     \
(BOOST_GENERIC_DETAIL_OPERATOR_KIND                                            \
 (BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR_NAME( dets ))     \
)                                                                              \
( ( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )            \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR( dets )         \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets ) )             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_FUNCTION_PARTIAL(   \
                                                                           dets\
                                                                         )     \
(error)(BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_ERROR(dets))

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NO_RETURN( dets )  \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONSTRUCTOR( dets )                   \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_CONSTRUCTOR              \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONCONSTRUCTOR           \
)( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NONCONSTRUCTOR(    \
                                                                           dets\
                                                                         )     \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_DESTRUCTOR( dets )        \
            , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_DESTRUCTOR   \
            , BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_CONVERSION   \
            )( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_CONSTRUCTOR( dets )\
(BOOST_PP_IIF                                                                  \
 ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_EXPLICIT( dets )                     \
 , explicit_constructor                                                        \
 , constructor                                                                 \
 )                                                                             \
)                                                                              \
( ( ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_THIS_TYPE( dets ) )                  \
  , BOOST_GENERIC_DETAIL_NO_RETURN_DETS_PARAM_DETS( dets )                     \
  , ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_DEFINITION( dets ) )                 \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_DESTRUCTOR( dets ) \
(destructor)                                                                   \
( ( ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_THIS_TYPE( dets ) )                  \
  , ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_DEFINITION( dets ) )                 \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_CONVERSION( dets ) \
(BOOST_PP_IIF                                                                  \
 ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_EXPLICIT( dets )                     \
 , explicit_conversion                                                         \
 , conversion                                                                  \
 )                                                                             \
)                                                                              \
( ( ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_TARGET_TYPE( dets ) )                \
  , BOOST_GENERIC_DETAIL_NO_RETURN_DETS_PARAM_DETS( dets )                     \
  , ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_DEFINITION( dets ) )                 \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_DETS_IMPL( elem )\
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( elem )                                \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_DETS_IMPL_PAREN        \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_DETS_IMPL_NOT_PAREN    \
)( elem )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_PARAM_DETS_IMPL_PAREN( \
                                                                           elem\
                                                                         )     \
BOOST_GENERIC_DETAIL_ORDERED_IIF_1                                             \
( elem                                                                         \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_UNRECOGNIZED_PARAM           \
, (BOOST_GENERIC_DETAIL_WRAPPED_TYPEDEF_DETS)                                  \
  (BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_PARTIAL)                               \
  (BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_TYPEDEF)                 \
, (BOOST_GENERIC_DETAIL_WRAPPED_NO_RETURN_DETS)                                \
  (BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_PARTIAL)                             \
  (BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_NO_RETURN)               \
, (BOOST_GENERIC_DETAIL_WRAPPED_FUNCTION_DECL_DETS)                            \
  (BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_PARTIAL)                         \
  (BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_FUNCTION)                \
)

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_TYPEDEF( dets )     \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_VALID( dets )                           \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_TYPEDEF                  \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_TYPEDEF_PARTIAL           \
)( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_FUNCTION( dets )    \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( dets )                     \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_FUNCTION                 \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_FUNCTION_PARTIAL          \
)( dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_NO_RETURN( dets )   \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_VALID( dets )                         \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_IMPL_TAG_NO_RETURN                \
, BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_ANALYZE_NO_RETURN_PARTIAL         \
)( dets )

#endif // BOOST_GENERIC_DETAIL_CONCEPT_MAP_BODY_DETS_HPP
