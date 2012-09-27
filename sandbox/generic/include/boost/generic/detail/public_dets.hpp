/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_PUBLIC_DETS_HPP
#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_details.hpp>
#include <boost/generic/detail/seq_enum.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/generic/detail/variadic_stringize.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitor.hpp>

// a public requirement is specified as:
//   public list, of, parents

// Result is of the form:
// (validity_bit)(is_partial_bit)((variadic)(seq)(of)(parents))
#define BOOST_GENERIC_DETAIL_PUBLIC_DETS( ... )                                \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_WITH_PUBLIC( __VA_ARGS__ )                       \
, BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_IS_PUBLIC                              \
, BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_INVALID                                \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_WRAPPED_PUBLIC_DETS( wrapped_arg )                \
BOOST_GENERIC_DETAIL_PUBLIC_DETS wrapped_arg

// expands to macro( validity_bit, name, empty_or_default_in_paren )
// ToDo: pass error data as well for visitation
#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_VISIT(dets, valid_macro, inv_macro)   \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_VALID( dets )                \
            , BOOST_GENERIC_DETAIL_PUBLIC_DETS_VISIT_IMPL_VALID                \
            , BOOST_GENERIC_DETAIL_PUBLIC_DETS_VISIT_IMPL_INVALID              \
            )( dets, valid_macro, invalid_macro )

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_VISIT_IMPL_VALID( dets, valid_macro   \
                                                         , inv_macro           \
                                                         )                     \
valid_macro( BOOST_GENERIC_DETAIL_PUBLIC_DETS_PARENT_CONCEPT_SEQ( dets ) )

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_VISIT_IMPL_INVALID( dets              \
                                                           , valid_macro       \
                                                           , inv_macro         \
                                                           )                   \
inv_macro( BOOST_GENERIC_DETAIL_PUBLIC_DETS_ERRORS( dets ) )

// TODO allow a single less-refined concept specifier to not be parenthesized
// TODO error if there are parts after the sequence

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_IS_PUBLIC( ... )                 \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT                                         \
    ( BOOST_GENERIC_DETAIL_EAT_PUBLIC( __VA_ARGS__ ) )                         \
  )                                                                            \
, BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_PARTIAL                                \
, BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_VALID                                  \
)( BOOST_GENERIC_DETAIL_EAT_PUBLIC( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_VALID( dets )                      \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_PARTIAL( dets )                    \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_PARENTS_SEQ( dets )                   \
BOOST_PP_SEQ_ELEM( 2, dets )

// Yields a comma-separated list of less-refined concept specifiers
#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_PARENTS( dets )                       \
BOOST_GENERIC_DETAIL_SEQ_ENUM                                                  \
( BOOST_GENERIC_DETAIL_PUBLIC_DETS_PARENTS_SEQ( dets ) )

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_VALID( ... )                     \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )                     \
, BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_VALID_SEQ                              \
, BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_VALID_NO_SEQ                           \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_VALID_SEQ( ... )                 \
(1)                                                                            \
(1)                                                                            \
(__VA_ARGS__)

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_VALID_NO_SEQ( ... )              \
(1)                                                                            \
(1)                                                                            \
((__VA_ARGS__))

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_PARTIAL( ... )                   \
(0)                                                                            \
(1)                                                                            \
((invalid_parent_concepts))

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_IMPL_INVALID( ... )                   \
(0)                                                                            \
(0)                                                                            \
((invalid_parent_concepts))

#define BOOST_GENERIC_DETAIL_STARTS_WITH_PUBLIC( ... )                         \
BOOST_PP_IIF                                                                   \
( BOOST_PP_BITOR( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( __VA_ARGS__ )     \
                , BOOST_GENERIC_DETAIL_IS_EMPTY                                \
                  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )        \
                )                                                              \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_PUBLIC_IMPL                                 \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_PUBLIC_IMPL( ... )                    \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN                                   \
  ( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                          \
    ( BOOST_GENERIC_DETAIL_STARTS_WITH_PUBLIC                                  \
    , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                        \
    )                                                                          \
  )                                                                            \
, 2                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_PUBLICpublic ,

#define BOOST_GENERIC_DETAIL_EAT_PUBLIC( ... )                                 \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_PUBLIC, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_PUBLICpublic

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_NATIVE_DECL( dets )                   \
: BOOST_GENERIC_DETAIL_PUBLIC_DETS_PARENTS( dets )

#define BOOST_GENERIC_DETAIL_PUBLIC_DETS_NATIVE_DECL_STR( dets )               \
BOOST_GENERIC_DETAIL_VARIADIC_STRINGIZE                                        \
( BOOST_GENERIC_DETAIL_PUBLIC_DETS_NATIVE_DECL( dets ) )

#endif // BOOST_GENERIC_DETAIL_PUBLIC_DETS_HPP
