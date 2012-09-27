/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_HPP
#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_HPP

#include <boost/generic/detail/param_list.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_details.hpp>
#include <boost/generic/detail/seq_size.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// Checks if the argument matches the form (text)(param list) nothing here
// Gracefully handles if the argument is not a sequence or if there is more data
// after the last parameter
// Yields details in the form:
//   (is_valid_bit)(concept_name_in_parentheses)(param_dets)
#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS( ... )                           \
BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL                                     \
( BOOST_GENERIC_DETAIL_SEQ_DETS( __VA_ARGS__ ), __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IS_VALID( dets )                 \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_CONCEPT( dets )                  \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_PARAM_DETS( dets )               \
BOOST_PP_SEQ_ELEM( 2, dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL( seq_dets, ... )            \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_SEQ_DETS_IS_VALID( seq_dets )               \
            , BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_IS_SEQ                \
            , BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_INVALID               \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_INVALID( ... )              \
(0)                                                                            \
((invalid_concept_sig))                                                        \
((invalid_concept_sig))

#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_IS_SEQ( seq )               \
BOOST_PP_IIF( BOOST_PP_EQUAL( BOOST_GENERIC_DETAIL_SEQ_SIZE( seq ), 2 )        \
            , BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_SEQ_2                 \
            , BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_INVALID               \
            )( BOOST_GENERIC_DETAIL_SEQ_TO_SEQ( seq ) )

#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_SEQ_2( nonvarseq )          \
BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_SEQ_2_IMPL                          \
( BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 0, nonvarseq ) )       \
, BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS( BOOST_PP_SEQ_ELEM( 1, nonvarseq ) ) \
)

// ToDo: Require typename/class parameters when in emulated mode
#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_SEQ_2_IMPL(name,param_dets) \
BOOST_PP_IIF                                                                   \
( BOOST_PP_BITAND                                                              \
  ( BOOST_PP_BITAND                                                            \
    ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VALID( param_dets )           \
    , BOOST_PP_COMPL                                                           \
      ( BOOST_GENERIC_DETAIL_PARAM_LIST_DETAILS_IS_VOID( param_dets ) )        \
    )                                                                          \
  , BOOST_PP_COMPL                                                             \
    ( BOOST_PP_BITOR                                                           \
      ( BOOST_GENERIC_DETAIL_IS_EMPTY( name )                                  \
      , BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( name )                      \
      )                                                                        \
    )                                                                          \
  )                                                                            \
, BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_VALID_PARAMS                      \
, BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_INVALID                           \
)( name, param_dets )

#define BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_IMPL_VALID_PARAMS( name          \
                                                               , param_dets    \
                                                               )               \
( 1 )                                                                          \
( name )                                                                       \
( param_dets )

#endif // BOOST_GENERIC_DETAIL_CONCEPT_SIG_DETS_HPP
