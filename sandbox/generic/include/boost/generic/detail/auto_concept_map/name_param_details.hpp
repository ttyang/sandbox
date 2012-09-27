/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_HPP

#include <boost/generic/detail/args_to_sequence.hpp>
#include <boost/generic/detail/error.hpp>
#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/param_list.hpp>
#include <boost/generic/detail/tail_arguments.hpp>
#include <boost/preprocessor/array/push_back.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/seq.hpp>

// This macro takes the arguments to a BOOST_GENERIC_AUTO_CONCEPT_MAP invocation
// and yields information about the concept name and its parameters, and also
// yields the remaining macro arguments as a sequence.
// This data is in a sequence of the form:
// (error_array)(name)(param_details)
// (remaining_args_seq)(curr_arg_num)
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS( ... )        \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_IMPL                  \
( BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( __VA_ARGS__ ) )

// Accessor for yielded param details - errors
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_ERRORS( dets )         \
BOOST_PP_SEQ_ELEM( 0, dets )

// Accessor for yielded param details - concept name
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_NAME( dets )           \
BOOST_PP_SEQ_ELEM( 1, dets )

// Accessor for yielded param details - param list dets
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_PARAM_LIST_DETS( dets )\
BOOST_PP_SEQ_ELEM( 2, dets )

// Accessor for yielded param details - remaining args
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_REMAINING_ARGS( dets ) \
BOOST_PP_SEQ_ELEM( 3, dets )

// Accessor for yielded param details - curr arg num
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_CURR_ARG_NUM( dets )   \
BOOST_PP_SEQ_ELEM( 4, dets )

// Takes the args as a sequence
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_IMPL(         \
                                                                  args_as_seq )\
BOOST_PP_IIF                                                                   \
( BOOST_PP_GREATER                                                             \
  ( BOOST_GENERIC_DETAIL_NUM_WRAPPED_ARGS( BOOST_PP_SEQ_HEAD( args_as_seq ) )  \
  , 1                                                                          \
  )                                                                            \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_IMPL_VALID_SIZE              \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_IMPL_INVALID_SIZE            \
)( BOOST_PP_SEQ_HEAD( args_as_seq ) )                                          \
( BOOST_PP_SEQ_TAIL( args_as_seq ) )( 2 )                                      \

//
#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_IMPL_INVALID_SIZE(head)\
((1,(BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ERROR_INVALID_NAME_PARAM_FORMAT( head ))))   \
(invalid_name)(invalid_params)

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_IMPL_VALID_SIZE( head )\
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS                                      \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_NAME                                      \
  ( BOOST_GENERIC_DETAIL_HEAD_WRAPPED_ARGUMENT( head ) )                       \
, BOOST_GENERIC_DETAIL_TAIL_WRAPPED_ARGUMENTS( head )                          \
)

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_NAME( head_arg )                    \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( head_arg )                        \
, ((1,(BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ERROR_PARENTHESIZED_NAME( head_arg ))))    \
  (head_arg)                                                                   \
, ((0,()))(head_arg)                                                           \
)

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS( state, ... )                \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL                                 \
( state, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL( state, param_dets )    \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID( param_dets )               \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_VALID                         \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_INVALID                       \
)( state, param_dets )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_INVALID( state          \
                                                              , param_dets     \
                                                              )                \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_ERRORS( state )            \
  , BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ERROR_PARAMS_INVALID                          \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( param_dets ) )  \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_NAME( state ) )              \
( param_dets )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_NOT_PAREN( state        \
                                                                , param_dets   \
                                                                )              \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_ERRORS( state )            \
  , BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ERROR_PARAMS_NOT_PAREN                        \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( param_dets ) )  \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_NAME( state ) )              \
( param_dets )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_INVALID_FORMAT( state   \
                                                                   , param_dets\
                                                                   )           \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_ERRORS( state )            \
  , BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ERROR_INVALID_PARAM_FORMAT                    \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( param_dets ) )  \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_NAME( state ) )              \
( param_dets )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_VALID(state,param_dets) \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( param_dets )                \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_VOID                          \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_NONVOID                       \
)( state, param_dets )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_NONVOID( state          \
                                                              , param_dets     \
                                                              )                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_ARE_ALL_CLASS_OR_TYPENAME            \
  ( param_dets )                                                               \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_FULLY_VALID                   \
, BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_NOT_ALL_TYPE_PARAMS           \
)( state, param_dets )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_NOT_ALL_TYPE_PARAMS(    \
                                                                    state      \
                                                                  , param_dets \
                                                                  )            \
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_ERRORS( state )            \
  , BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ERROR_NONTYPE_PARAMS                          \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_PARAM_LIST_PART( param_dets ) )  \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_NAME( state ) )              \
( param_dets )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_FULLY_VALID( state      \
                                                                  , param_dets \
                                                                  )            \
state                                                                          \
( param_dets )

#define BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_CHECK_PARAMS_IMPL_VOID( state,param_dets )\
( BOOST_PP_ARRAY_PUSH_BACK                                                     \
  ( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_ERRORS( state )            \
  , BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ERROR_VOID_PARAMS()                           \
  )                                                                            \
)                                                                              \
( BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_NAME( state ) )              \
( param_dets )

#endif // BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_NAME_PARAM_DETAILS_HPP
