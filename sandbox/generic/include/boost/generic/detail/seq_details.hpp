/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_SEQ_DETAILS_HPP
#define BOOST_GENERIC_DETAIL_SEQ_DETAILS_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/tail_arguments.hpp>
#include <boost/generic/detail/intercept.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_size.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/seq/elem.hpp>

// Result format:
// (is_valid)(starts_as_seq)((data_after_seq))(seq_size)(nonvar_seq)
// Note: seq_size is the size of the sequence even if there is data after it
#define BOOST_GENERIC_DETAIL_SEQ_DETS( ... )                                   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )         \
            , BOOST_GENERIC_DETAIL_SEQ_DETS_IMPL_PAREN                         \
            , BOOST_GENERIC_DETAIL_SEQ_DETS_IMPL_NOT_PAREN                     \
            )( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_SEQ_DETS_IS_VALID( dets )                         \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_SEQ_DETS_SEQ( dets )                              \
BOOST_PP_SEQ_ELEM( 4, dets )

#define BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITHOUT_EXTRA_DATA                \
BOOST_GENERIC_DETAIL_SEQ_DETS_IS_VALID

#define BOOST_GENERIC_DETAIL_SEQ_DETS_STARTS_AS_SEQ( dets )                    \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_SEQ_DETS_IS_SEQ_WITH_EXTRA_DATA( dets )           \
BOOST_PP_BITAND( BOOST_GENERIC_DETAIL_SEQ_DETS_STARTS_AS_SEQ( dets )           \
               , BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( dets )          \
               )

#define BOOST_GENERIC_DETAIL_SEQ_DETS_EXTRA_DATA( dets )                       \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( dets )                   \
BOOST_PP_COMPL                                                                 \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_SEQ_DETS_EXTRA_DATA( dets ) )                         \
)

#define BOOST_GENERIC_DETAIL_SEQ_DETS_SIZE( dets )                             \
BOOST_PP_SEQ_ELEM( 3, dets )

#define BOOST_GENERIC_DETAIL_SEQ_DETS_IS_EMPTY( dets )                         \
BOOST_PP_COMPL                                                                 \
( BOOST_PP_BITOR                                                               \
  ( BOOST_GENERIC_DETAIL_SEQ_DETS_STARTS_AS_SEQ( dets )                        \
  , BOOST_GENERIC_DETAIL_SEQ_DETS_HAS_EXTRA_DATA( dets )                       \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_SEQ_DETS_IMPL_NOT_PAREN( ... )                    \
(0)(0)((__VA_ARGS__))(0)(BOOST_PP_NIL)

#define BOOST_GENERIC_DETAIL_SEQ_DETS_IMPL_PAREN_NO_EXTRA_DATA( ... )          \
(1)(1)(())                                                                     \
(BOOST_GENERIC_DETAIL_SEQ_SIZE(__VA_ARGS__))                                   \
(BOOST_GENERIC_DETAIL_SEQ_TO_SEQ(__VA_ARGS__))

#define BOOST_GENERIC_DETAIL_SEQ_DETS_IMPL_PAREN_EXTRA_DATA( ... )             \
(0)(1)                                                                         \
((BOOST_GENERIC_DETAIL_SPLIT_DATA_FROM_NUM( __VA_ARGS__ )))                    \
(BOOST_GENERIC_DETAIL_SEQ_SIZE( __VA_ARGS__ ))                                 \
(BOOST_GENERIC_DETAIL_SEQ_TO_SEQ(__VA_ARGS__))

#define BOOST_GENERIC_DETAIL_SEQ_DETS_IMPL_PAREN( ... )                        \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_AFTER_RESCAN                           \
    ( BOOST_GENERIC_DETAIL_INTERCEPT                                           \
      ( BOOST_GENERIC_DETAIL_SEQ_SIZE_IMPL( __VA_ARGS__ ) )                    \
    )                                                                          \
  )                                                                            \
, BOOST_GENERIC_DETAIL_SEQ_DETS_IMPL_PAREN_NO_EXTRA_DATA                       \
, BOOST_GENERIC_DETAIL_SEQ_DETS_IMPL_PAREN_EXTRA_DATA                          \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_SPLIT_DATA_FROM_NUM( ... )                        \
BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS_AFTER_RESCAN                               \
( BOOST_GENERIC_DETAIL_SEQ_SIZE_IMPL( __VA_ARGS__ ) )

#endif // BOOST_GENERIC_DETAIL_SEQ_DETAILS_HPP
