/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_CONCEPT_REQ_DETS_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_REQ_DETS_HPP

#include <boost/generic/detail/args_to_sequence.hpp>
#include <boost/generic/detail/axiom_dets.hpp>
#include <boost/generic/detail/function_decl_details.hpp>
#include <boost/generic/detail/no_return_dets.hpp>
#include <boost/generic/detail/requires_dets.hpp>
#include <boost/generic/detail/rescan.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_error.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/ordered_iif.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/generic/detail/seq_size.hpp>
#include <boost/generic/detail/typename_details.hpp>
#include <boost/generic/detail/wrap.hpp>
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
#include <boost/preprocessor/seq/fold_left.hpp>

// requirement_seq_dets is a sequence of requirement specifications
// Each element of the sequence is of the form:
// ( id_name )( simplified_details )
//
// id_name is one of:                    and simplified_details is:
//   axiom                                 ( everything )
//
//   requires                              ( requirement )
//
//   typename                              ( name
//                                         , def_or_empty_in_paren
//                                         )
//
//   constrainted_typename                 ( constraint, name
//                                         , def_or_empty_in_paren
//                                         )
//
//   member_typename                       ( this_type_in_paren, name
//                                         , def_or_empty_in_paren
//                                         )
//
//   constrainted_member_typename          ( constraint
//                                         , this_type_in_paren, name
//                                         , def_or_empty_in_paren
//                                         )
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
//
// error_msg_seq is either empty or a sequence of c-strings representing errors
#define BOOST_GENERIC_DETAIL_REQ_DETS( ... )                                   \
BOOST_PP_IIF( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_NUM_ARGS( __VA_ARGS__ ), 0 )\
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_VALID_EMPTY                   \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL                               \
            )( BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_VALID_EMPTY( ... )                  \
(1)(())


#define BOOST_GENERIC_DETAIL_REQ_DETS_VISIT(dets, macro_base, index_base, data)\
BOOST_PP_SEQ_FOR_EACH_I                                                        \
( BOOST_GENERIC_DETAIL_REQ_DETS_VISIT_IMPL                                     \
, (macro_base)(index_base)(data)                                               \
, BOOST_GENERIC_DETAIL_REQ_DETS_REQUIREMENTS( dets )                           \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_FOLD( dets, macro_base, concept_         \
                                          , param_dets, index_base, state      \
                                          )                                    \
BOOST_PP_SEQ_ELEM                                                              \
( 1, BOOST_PP_SEQ_FOLD_LEFT                                                    \
     ( BOOST_GENERIC_DETAIL_REQ_DETS_FOLD_IMPL                                 \
     , (macro_base)(state)(concept_)(param_dets)(index_base)                   \
     , BOOST_GENERIC_DETAIL_REQ_DETS_REQUIREMENTS( dets )                      \
     )                                                                         \
)

// ToDo: Get rid of the add! Rewrite to use inc instead
#define BOOST_GENERIC_DETAIL_REQ_DETS_VISIT_IMPL( r, data, i, elem )           \
BOOST_GENERIC_DETAIL_SELF                                                      \
( BOOST_PP_CAT( BOOST_PP_SEQ_ELEM( 0, data ), BOOST_PP_SEQ_ELEM( 0, elem ) )   \
  BOOST_GENERIC_DETAIL_SELF                                                    \
  ( ( BOOST_PP_ADD( BOOST_PP_SEQ_ELEM( 1, data ), i )                          \
    , BOOST_PP_SEQ_ELEM( 2, data )                                             \
    , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, elem ) )        \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_FOLD_IMPL( s, state, elem )              \
(BOOST_PP_SEQ_ELEM( 0, state ))                                                \
(BOOST_GENERIC_DETAIL_SELF                                                     \
 ( BOOST_GENERIC_DETAIL_REQ_DETS_FOLD_IMPL_                                    \
   ( BOOST_PP_CAT( BOOST_PP_SEQ_ELEM( 0, state )                               \
                 , BOOST_PP_SEQ_ELEM( 0, elem )                                \
                 )                                                             \
   , BOOST_PP_SEQ_ELEM( 1, state )                                             \
   , BOOST_PP_SEQ_ELEM( 2, state )                                             \
   , BOOST_PP_SEQ_ELEM( 3, state )                                             \
   , BOOST_PP_SEQ_ELEM( 4, state )                                             \
   , BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, elem ) )         \
   )                                                                           \
 )                                                                             \
)                                                                              \
(BOOST_PP_SEQ_ELEM( 2, state ))(BOOST_PP_SEQ_ELEM( 3, state ))                 \
(BOOST_PP_INC(BOOST_PP_SEQ_ELEM( 4, state )))

#define BOOST_GENERIC_DETAIL_REQ_DETS_FOLD_IMPL_( macro, ... )                 \
macro BOOST_GENERIC_DETAIL_WRAP( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_VALID_EMPTY( ... )                  \
(1)(())

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL( args )                             \
BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_WHILE_STATE_TO_DETS                         \
( BOOST_PP_WHILE                                                               \
  ( BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_PRED                              \
  , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_OP                                \
  , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAMS_INITIAL_STATE                    \
    ( BOOST_GENERIC_DETAIL_SEQ_TO_SEQ( args ) )                                \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IS_VALID( dets )                         \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_REQUIREMENTS( dets )                     \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 1, dets ) )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_WHILE_STATE_TO_DETS( state )        \
(BOOST_PP_COMPL(BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_HAS_ERRORS(state)))         \
((BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_DETS(state)))

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_CURR_INDEX( state )                 \
BOOST_PP_SEQ_ELEM( 0, state )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_SEQ( state )                        \
BOOST_PP_SEQ_ELEM( 1, state )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_DETS( state )                       \
BOOST_PP_SEQ_ELEM( 2, state )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_HAS_ERRORS( state )                 \
BOOST_PP_SEQ_ELEM( 3, state )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_PRED( d, state )              \
BOOST_PP_COMPL                                                                 \
( BOOST_PP_BITOR                                                               \
  ( BOOST_PP_EQUAL                                                             \
    ( BOOST_PP_INC( BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_CURR_INDEX( state ) )   \
    , BOOST_GENERIC_DETAIL_SEQ_SIZE                                            \
      ( BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_SEQ( state ) )                      \
    )                                                                          \
  , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_HAS_ERRORS( state )                     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_OP( d, state )                \
BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_OP_IMPL                               \
( state                                                                        \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_DETS_IMPL                           \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN                                          \
    ( BOOST_PP_SEQ_ELEM                                                        \
      ( BOOST_PP_INC( BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_CURR_INDEX( state ) ) \
      , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_SEQ( state )                        \
      )                                                                        \
    )                                                                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_OP_IMPL( state, dets )        \
( BOOST_PP_INC( BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_CURR_INDEX( state ) ) )     \
( BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_SEQ( state ) )                            \
( BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_DETS(state)(dets) )                       \
( BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAGGED_DETS_IS_ERROR( dets ) )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAMS_INITIAL_STATE( seq )         \
BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAMS_INITIAL_STATE_IMPL                   \
( seq                                                                          \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_DETS_IMPL                           \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, seq ) ) )         \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAMS_INITIAL_STATE_IMPL(seq, dets)\
(0)                                                                            \
(seq)                                                                          \
((dets))                                                                       \
( BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAGGED_DETS_IS_ERROR( dets ) )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAGGED_DETS_TAG( dets )             \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAGGED_DETS_DETS( dets )            \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAGGED_DETS_IS_ERROR( dets )      \
BOOST_GENERIC_DETAIL_STARTS_WITH_ERROR( BOOST_PP_SEQ_ELEM( 0, dets ) )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_AXIOM( dets )                   \
(axiom)                                                                        \
( ( (BOOST_GENERIC_DETAIL_AXIOM_DETS_ARG(dets)) ) )

#define BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_AXIOM_PARTIAL( dets )            \
(error)(BOOST_GENERIC_DETAIL_AXIOM_DETS_ERROR(dets))

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_REQUIRES( dets )                \
(requires)                                                                     \
( ( (BOOST_GENERIC_DETAIL_REQUIRES_DETS_CONCEPT_REQ(dets)) ) )

#define BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_REQUIRES_PARTIAL( dets )         \
(error)(BOOST_GENERIC_DETAIL_REQUIRES_DETS_ERROR(dets))

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_TYPENAME( dets )                \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_NESTED( dets )             \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_MEMBER_TYPENAME           \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONMEMBER_TYPENAME        \
            )( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_MEMBER_TYPENAME( dets )         \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_CONSTRAINED( dets )        \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_CONSTRAINED_MEM_TYPENAME  \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_UNCONSTRAINED_MEM_TYPENAME\
            )( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONMEMBER_TYPENAME( dets )      \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_CONSTRAINED( dets )        \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_CONSTRAINED_TYPENAME      \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_UNCONSTRAINED_TYPENAME    \
            )( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_UNCONSTRAINED_TYPENAME( dets )  \
(typename)                                                                     \
( ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( dets )                            \
  , ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( dets ) )                     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_CONSTRAINED_TYPENAME( dets )    \
(constrained_typename)                                                         \
( ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_CONSTRAINT( dets )                      \
  , BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( dets )                            \
  , ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( dets ) )                     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_UNCONSTRAINED_MEM_TYPENAME(dets)\
(member_typename)                                                              \
( ( ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_TYPE( dets ) )                        \
  , BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( dets )                            \
  , ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( dets ) )                     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_CONSTRAINED_MEM_TYPENAME( dets )\
(constrained_member_typename)                                                  \
( ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_CONSTRAINT( dets )                      \
  , ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_TYPE( dets ) )                        \
  , BOOST_GENERIC_DETAIL_TYPENAME_DETS_NAME( dets )                            \
  , ( BOOST_GENERIC_DETAIL_TYPENAME_DETS_DEFAULT( dets ) )                     \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_TYPENAME_PARTIAL( dets )         \
(error)(BOOST_GENERIC_DETAIL_TYPENAME_DETS_ERROR(dets))

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_FUNCTION( dets )                \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_OPERATOR( dets )      \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_OPERATOR                  \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONOPERATOR               \
            )( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONOPERATOR( dets )             \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION( dets )           \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_MEMBER_FUNCTION                       \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONMEMBER_FUNCTION                    \
)( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_MEMBER_FUNCTION( dets )         \
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

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONMEMBER_FUNCTION( dets )      \
(function)                                                                     \
( ( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )            \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NAME( dets )                       \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets ) )             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_OPERATOR( dets )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_MEMBER_FUNCTION( dets )           \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_MEMBER_OPERATOR                       \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONMEMBER_OPERATOR                    \
)( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_MEMBER_OPERATOR( dets )         \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_ASSIGN                                               \
  ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR_NAME( dets ) )     \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_ASSIGN_OPERATOR                       \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONASSIGN_MEMBER_OPERATOR             \
)( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONASSIGN_MEMBER_OPERATOR(dets )\
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

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_ASSIGN_OPERATOR( dets )         \
(BOOST_GENERIC_DETAIL_OPERATOR_KIND                                            \
 (BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_MEMBER_OPERATOR_NAME( dets ))        \
)                                                                              \
( ( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_THIS_TYPE( dets ) )              \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets ) )             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONMEMBER_OPERATOR( dets )      \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_NONBASIC_OP                                          \
  ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR_NAME( dets ) )  \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONBASIC_OPERATOR                     \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONMEMBER_OPERATOR_                   \
)( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONBASIC_OPERATOR( dets )       \
(BOOST_GENERIC_DETAIL_OPERATOR_KIND                                            \
 (BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR_NAME( dets ))     \
)                                                                              \
( ( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )            \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets ) )             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONMEMBER_OPERATOR_( dets )     \
(BOOST_GENERIC_DETAIL_OPERATOR_KIND                                            \
 (BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR_NAME( dets ))     \
)                                                                              \
( ( ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_RETURN_TYPE( dets ) )            \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_NONMEMBER_OPERATOR( dets )         \
  , BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_PARAM_LIST_DETS( dets )            \
  , ( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_DEFINITION( dets ) )             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_FUNCTION_PARTIAL( dets )         \
(error)(BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_ERROR(dets))

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NO_RETURN( dets )               \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_CONSTRUCTOR( dets )       \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_CONSTRUCTOR               \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONCONSTRUCTOR            \
            )( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NONCONSTRUCTOR( dets )          \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_DESTRUCTOR( dets )        \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_DESTRUCTOR                \
            , BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_CONVERSION                \
            )( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_CONSTRUCTOR( dets )             \
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

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_DESTRUCTOR( dets )              \
(destructor)                                                                   \
( ( ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_THIS_TYPE( dets ) )                  \
  , ( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_DEFINITION( dets ) )                 \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_CONVERSION( dets )              \
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

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_DETS_IMPL( elem )             \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_PARENTHESIZED( elem )                                \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_DETS_IMPL_PAREN                     \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_DETS_IMPL_NOT_PAREN                 \
)( elem )

#define BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_PARAM_DETS_IMPL_PAREN(elem)         \
BOOST_GENERIC_DETAIL_ORDERED_IIF_1                                             \
( elem                                                                         \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_UNRECOGNIZED_PARAM                        \
, (BOOST_GENERIC_DETAIL_WRAPPED_REQUIRES_DETS)                                 \
  (BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_PARTIAL)                              \
  (BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_REQUIRES)                             \
, (BOOST_GENERIC_DETAIL_WRAPPED_TYPENAME_DETS)                                 \
  (BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_PARTIAL)                              \
  (BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_TYPENAME)                             \
, (BOOST_GENERIC_DETAIL_WRAPPED_AXIOM_DETS)                                    \
  (BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_PARTIAL)                                 \
  (BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_AXIOM)                                \
, (BOOST_GENERIC_DETAIL_WRAPPED_NO_RETURN_DETS)                                \
  (BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_PARTIAL)                             \
  (BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_NO_RETURN)                            \
, (BOOST_GENERIC_DETAIL_WRAPPED_FUNCTION_DECL_DETS)                            \
  (BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_PARTIAL)                         \
  (BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_FUNCTION)                             \
)

#define BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_AXIOM( dets )                    \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_VALID( dets )                             \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_AXIOM                                 \
, BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_AXIOM_PARTIAL                          \
)( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_REQUIRES( dets )                 \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_VALID( dets )                          \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_REQUIRES                              \
, BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_REQUIRES_PARTIAL                       \
)( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_TYPENAME( dets )                 \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_TYPENAME_DETS_IS_VALID( dets )                          \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_TYPENAME                              \
, BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_TYPENAME_PARTIAL                       \
)( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_FUNCTION( dets )                 \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_FUNCTION_DECL_DETS_IS_VALID( dets )                     \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_FUNCTION                              \
, BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_FUNCTION_PARTIAL                       \
)( dets )

#define BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_NO_RETURN( dets )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NO_RETURN_DETS_IS_VALID( dets )                         \
, BOOST_GENERIC_DETAIL_REQ_DETS_IMPL_TAG_NO_RETURN                             \
, BOOST_GENERIC_DETAIL_REQ_DETS_ANALYZE_NO_RETURN_PARTIAL                      \
)( dets )

#endif // BOOST_GENERIC_DETAIL_CONCEPT_REQ_DETS_HPP
