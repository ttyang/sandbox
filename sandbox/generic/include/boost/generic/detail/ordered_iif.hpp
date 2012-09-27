/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_ORDERED_IIF_HPP
#define BOOST_GENERIC_DETAIL_ORDERED_IIF_HPP

#include <boost/generic/detail/args_to_sequence.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// Takes macro arguments of the form:
//   data
// , default_macro
// , ( transform0 )( condition0 )( macro0 )
// , ( transform1 )( condition1 )( macro1 )
// , // etc.
//
// And does the equivalent of:
// if( condition0( transform0( data ) ) )
//   macro0( transform0( data ) )
// else
//   if( condition1( transform1( data ) ) )
//     macro1( transform1( data ) )
//   else
//     // etc.
//     else
//       default_macro( data )
#define BOOST_GENERIC_DETAIL_ORDERED_IIF( data, default_macro, ... )           \
BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL                                          \
( data                                                                         \
, BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( __VA_ARGS__ )                         \
  ((BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL_DEFAULT_OP)                          \
   (BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL_DEFAULT_PRED)                        \
   (default_macro)                                                             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL_DEFAULT_PRED( data ) 1

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL_DEFAULT_OP( data ) data

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_INDEX( state )                   \
BOOST_PP_SEQ_ELEM( 0, state )

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_ELEM( state )                    \
BOOST_PP_SEQ_ELEM( BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_INDEX( state )        \
                 , BOOST_GENERIC_DETAIL_ORDERED_IIF_SEQ( state )               \
                 )

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_TRANSFORM( state )               \
BOOST_PP_SEQ_ELEM( 0, BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_ELEM( state ) )

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_PRED( state )                    \
BOOST_PP_SEQ_ELEM( 1, BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_ELEM( state ) )

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_MACRO( state )                   \
BOOST_PP_SEQ_ELEM( 2, BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_ELEM( state ) )

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_DATA( state )                         \
BOOST_PP_SEQ_ELEM( 1, state )

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_SEQ( state )                          \
BOOST_PP_SEQ_ELEM( 2, state )

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_TRANSFORMED_DATA( state )             \
BOOST_PP_SEQ_ELEM( 3, state )

// ToDo: Deduce the reentrancy value
// State is of the form:
//   (curr_elem_index)(data)(seq)(transformed_data)
#define BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL( data, seq )                     \
BOOST_GENERIC_DETAIL_ORDERED_IIF_MACRO                                         \
( BOOST_PP_WHILE                                                               \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_PRED                                      \
  , BOOST_GENERIC_DETAIL_ORDERED_IIF_OP                                        \
  , BOOST_GENERIC_DETAIL_ORDERED_IIF_OP_IMPL                                   \
    ( d, (0)(data)(seq)(~) )                                                   \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_OP( d, state )                        \
BOOST_GENERIC_DETAIL_ORDERED_IIF_OP_IMPL                                       \
( d                                                                            \
, ( BOOST_PP_INC( BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_INDEX( state ) ) )     \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_DATA( state ) )                           \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_SEQ( state ) )                            \
  ( ~ )                                                                        \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_OP_IMPL( d, state )                   \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_INDEX( state ) )                       \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_DATA( state ) )                             \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_SEQ( state ) )                              \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_TRANSFORM( state )                     \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_DATA( state ) )                           \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_PRED( d, state )                      \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_PRED( state )                          \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_TRANSFORMED_DATA( state ) )               \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_MACRO( state )                        \
BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_MACRO( state )                           \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_TRANSFORMED_DATA( state ) )

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_1( data, default_macro, ... )         \
BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL_1                                        \
( data                                                                         \
, BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( __VA_ARGS__ )                         \
  ((BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL_DEFAULT_OP)                          \
   (BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL_DEFAULT_PRED)                        \
   (default_macro)                                                             \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_IMPL_1( data, seq )                   \
BOOST_GENERIC_DETAIL_ORDERED_IIF_MACRO_1                                       \
( BOOST_PP_WHILE                                                               \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_PRED_1                                    \
  , BOOST_GENERIC_DETAIL_ORDERED_IIF_OP_1                                      \
  , BOOST_GENERIC_DETAIL_ORDERED_IIF_OP_IMPL_1                                 \
    ( d, (0)(data)(seq)(~) )                                                   \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_OP_1( d, state )                      \
BOOST_GENERIC_DETAIL_ORDERED_IIF_OP_IMPL_1                                     \
( d                                                                            \
, ( BOOST_PP_INC( BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_INDEX( state ) ) )     \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_DATA( state ) )                           \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_SEQ( state ) )                            \
  ( ~ )                                                                        \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_OP_IMPL_1( d, state )                 \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_INDEX( state ) )                       \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_DATA( state ) )                             \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_SEQ( state ) )                              \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_TRANSFORM( state )                     \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_DATA( state ) )                           \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_PRED_1( d, state )                    \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_PRED( state )                          \
  ( BOOST_GENERIC_DETAIL_ORDERED_IIF_TRANSFORMED_DATA( state ) )               \
)

#define BOOST_GENERIC_DETAIL_ORDERED_IIF_MACRO_1( state )                      \
BOOST_GENERIC_DETAIL_ORDERED_IIF_CURR_MACRO( state )                           \
( BOOST_GENERIC_DETAIL_ORDERED_IIF_TRANSFORMED_DATA( state ) )

#endif // BOOST_GENERIC_DETAIL_ORDERED_IIF_HPP
