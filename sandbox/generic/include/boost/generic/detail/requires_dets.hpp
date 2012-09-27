/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_REQUIRES_DETS_HPP
#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_details.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/generic/detail/variadic_stringize.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitor.hpp>

// a requires requirement is specified as:
//   requires concept_requirement

// Result is of the form:
// (validity_bit)(is_partial_bit)((concept_req))
#define BOOST_GENERIC_DETAIL_REQUIRES_DETS( ... )                              \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_WITH_REQUIRES( __VA_ARGS__ )                     \
, BOOST_GENERIC_DETAIL_REQUIRES_DETS_IMPL_IS_REQUIRES                          \
, BOOST_GENERIC_DETAIL_REQUIRES_DETS_IMPL_INVALID                              \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_WRAPPED_REQUIRES_DETS( wrapped_arg )              \
BOOST_GENERIC_DETAIL_REQUIRES_DETS wrapped_arg

// expands to macro( validity_bit, name, empty_or_default_in_paren )
// ToDo: pass error data as well for visitation
#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_VISIT(dets, valid_macro, inv_macro) \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_VALID( dets )              \
            , BOOST_GENERIC_DETAIL_REQUIRES_DETS_VISIT_IMPL_VALID              \
            , BOOST_GENERIC_DETAIL_REQUIRES_DETS_VISIT_IMPL_INVALID            \
            )( dets, valid_macro, invalid_macro )

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_VISIT_IMPL_VALID( dets, valid_macro \
                                                         , inv_macro           \
                                                         )                     \
valid_macro( BOOST_GENERIC_DETAIL_REQUIRES_DETS_PARENT_CONCEPT_SEQ( dets ) )

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_VISIT_IMPL_INVALID( dets            \
                                                           , valid_macro       \
                                                           , inv_macro         \
                                                           )                   \
inv_macro( BOOST_GENERIC_DETAIL_REQUIRES_DETS_ERRORS( dets ) )

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_IMPL_IS_REQUIRES( ... )             \
BOOST_PP_IIF                                                                   \
( BOOST_PP_BITOR                                                               \
  ( BOOST_GENERIC_DETAIL_IS_EMPTY                                              \
    ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT                                       \
      ( BOOST_GENERIC_DETAIL_EAT_REQUIRES( __VA_ARGS__ ) )                     \
    )                                                                          \
  , BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                  \
    ( BOOST_GENERIC_DETAIL_EAT_REQUIRES( __VA_ARGS__ ) )                       \
  )                                                                            \
, BOOST_GENERIC_DETAIL_REQUIRES_DETS_IMPL_PARTIAL                              \
, BOOST_GENERIC_DETAIL_REQUIRES_DETS_IMPL_VALID                                \
)( BOOST_GENERIC_DETAIL_EAT_REQUIRES( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_VALID( dets )                    \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_PARTIAL( dets )                  \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_CONCEPT_REQ( dets )                 \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( BOOST_PP_SEQ_ELEM( 2, dets ) )

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_IMPL_VALID( ... )                   \
(1)                                                                            \
(1)                                                                            \
((__VA_ARGS__))

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_IMPL_PARTIAL( ... )                 \
(0)                                                                            \
(1)                                                                            \
((invalid_concept_requirement))

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_IMPL_INVALID( ... )                 \
(0)                                                                            \
(0)                                                                            \
((invalid_concept_requirement))

#define BOOST_GENERIC_DETAIL_STARTS_WITH_REQUIRES( ... )                       \
BOOST_PP_IIF                                                                   \
( BOOST_PP_BITOR( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )     \
                , BOOST_GENERIC_DETAIL_IS_EMPTY                                \
                  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )        \
                )                                                              \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_REQUIRES_IMPL                               \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_REQUIRES_IMPL( ... )                  \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN                                   \
  ( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                          \
    ( BOOST_GENERIC_DETAIL_STARTS_WITH_REQUIRES                                \
    , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                        \
    )                                                                          \
  )                                                                            \
, 2                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_REQUIRESrequires ,

#define BOOST_GENERIC_DETAIL_EAT_REQUIRES( ... )                               \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_REQUIRES, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_REQUIRESrequires

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_NATIVE_DECL( dets )                 \
requires BOOST_GENERIC_DETAIL_REQUIRES_DETS_CONCEPT_REQ( dets );

#define BOOST_GENERIC_DETAIL_REQUIRES_DETS_NATIVE_DECL_STR( dets )             \
BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                        \
( BOOST_GENERIC_DETAIL_REQUIRES_DETS_NATIVE_DECL( dets ) )

#endif // BOOST_GENERIC_DETAIL_REQUIRES_DETS_HPP
