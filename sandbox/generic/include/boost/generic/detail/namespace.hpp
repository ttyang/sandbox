/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_NAMESPACE_HPP
#define BOOST_GENERIC_DETAIL_NAMESPACE_HPP

// This file supplies macros for getting information about a macro namespace
// declaration of the form:
//   ( namespace nested, namespaces, as, list )

#include <boost/generic/detail/args_to_sequence.hpp>
#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/is_empty.hpp>
#include <boost/generic/detail/is_parenthesized.hpp>
#include <boost/generic/detail/num_args.hpp>
#include <boost/generic/detail/remove_paren.hpp>
#include <boost/generic/detail/seq_to_seq.hpp>
#include <boost/generic/detail/seq_size.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_empty.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS( arg )                             \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED( arg )                 \
            , BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_PARENTHESIZED           \
            , BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NOT_PARENTHESIZED       \
            )( BOOST_GENERIC_DETAIL_REMOVE_PAREN( arg ) )

// Note: These macros result in text of the form:
//   (valid_bit)(parenthesized_bit)(namespace_bit)(namespace_sequence)
// where "valid_bit" is 1 if it is a fully valid namespace decl, otherwise 0
// where "parenthesized_bit" is 1 if it starts parenthesized, otherwise 0
// where "namespace_bit" is 1 if it is a namespace param, otherwise 0
// where "namespace_sequence" is a variadic preprocessor sequence of namespaces
// The following are accessors for that information

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID( dets )                   \
BOOST_PP_SEQ_ELEM( 0, dets )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_PARENTHESIZED( dets )           \
BOOST_PP_SEQ_ELEM( 1, dets )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_NAMESPACE( dets )               \
BOOST_PP_SEQ_ELEM( 2, dets )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_NAMESPACE_SEQ( dets )              \
BOOST_PP_SEQ_ELEM( 3, dets )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE( dets )             \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID( dets )             \
            , BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE_              \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( dets )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_CLOSE_NAMESPACE( dets )            \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID( dets )             \
            , BOOST_GENERIC_DETAIL_NAMESPACE_DETS_CLOSE_NAMESPACE_             \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( dets )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE( dets )           \
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID( dets )             \
            , BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE_            \
            , BOOST_GENERIC_DETAIL_VARIADIC_EMPTY                              \
            )( dets )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE_( dets )            \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE_MAC, ~                    \
, BOOST_GENERIC_DETAIL_SEQ_TO_SEQ                                              \
  ( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_NAMESPACE_SEQ( dets ) )                \
)

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE_MAC( r, data, elem )\
namespace                                                                      \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_PARENTHESIZED                                    \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( elem ) )                                \
, BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_ANON_NAMESPACE_IMPL                 \
, BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE_IMPL                      \
)( elem )                                                                      \
{

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_ANON_NAMESPACE_IMPL( elem )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE_IMPL( elem )        \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( elem )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_CLOSE_NAMESPACE_( dets )           \
BOOST_PP_REPEAT                                                                \
( BOOST_GENERIC_DETAIL_SEQ_SIZE                                                \
  ( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_NAMESPACE_SEQ( dets ) )                \
, BOOST_GENERIC_DETAIL_NAMESPACE_DETS_CLOSE_NAMESPACE_MAC, ~                   \
)

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_CLOSE_NAMESPACE_MAC( z, n, text ) }

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE_( dets )          \
BOOST_PP_SEQ_FOR_EACH                                                          \
( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE_MAC, ~                  \
, BOOST_GENERIC_DETAIL_SEQ_TO_SEQ                                              \
  ( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_NAMESPACE_SEQ( dets ) )                \
)

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE_MAC(r,data, elem )\
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_EMPTY                                                \
  ( BOOST_GENERIC_DETAIL_REMOVE_PAREN( elem ) )                                \
, BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_ANON_NAMESPACE_IMPL               \
, BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE_IMPL                    \
)( elem )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_ANON_NAMESPACE_IMPL( elem )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE_IMPL( elem )      \
BOOST_GENERIC_DETAIL_REMOVE_PAREN( elem )::

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NOT_PARENTHESIZED( arg )      \
( 0 )( 0 )( 0 )( (boost_generic_invalid_namespace_declaration) )

// At this point we know that we have something of the form
//   ( something_here )
// ToDo: Possible add check to make sure the next part is not parenthesized
// before checking if it's "namespace"
#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_PARENTHESIZED( ... )          \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_NAMESPACE                                            \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NAMESPACE                           \
, BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NOT_NAMESPACE                       \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NOT_NAMESPACE( ... )          \
( 0 )( 1 )( 0 )( (boost_generic_invalid_namespace_declaration) )

// At this point we know that the argument is of the form
// ( namespace something_here )
// A namespace declaration should not have commas so here we check that
#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NAMESPACE( ... )              \
BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_EATEN                                 \
( BOOST_GENERIC_DETAIL_EAT_NAMESPACE( __VA_ARGS__ ) )

#define BOOST_GENERIC_DETAIL_IS_NAMESPACE( arg )                               \
BOOST_PP_EQUAL                                                                 \
( BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN                                   \
  ( BOOST_PP_CAT( BOOST_GENERIC_DETAIL_IS_NAMESPACE_, arg ) )                  \
, 2                                                                            \
)

#define BOOST_GENERIC_DETAIL_IS_NAMESPACE_namespace _1, _2

#define BOOST_GENERIC_DETAIL_EAT_NAMESPACE( ... )                              \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_NAMESPACE_IMPL_, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_NAMESPACE_IMPL_namespace

// At this point we have something of the form
//   ( namespace something_here )
// We've "eaten" everything up to "something_here"
// Here we check if "something_here" starts parenthesized
#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_EATEN( ... )                  \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_IS_EMPTY( __VA_ARGS__ )                                 \
, BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NAMESPACE_EMPTY                     \
, BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NAMESPACE_NOT_EMPTY                 \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NAMESPACE_EMPTY( ... )        \
( 1 )( 1 )( 1 )( () )

#define BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IMPL_NAMESPACE_NOT_EMPTY( ... )    \
( 1 )( 1 )( 1 )( BOOST_GENERIC_DETAIL_ARGS_TO_SEQUENCE( __VA_ARGS__ ) )

#endif // BOOST_GENERIC_DETAIL_NAMESPACE_HPP
