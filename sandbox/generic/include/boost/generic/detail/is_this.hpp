#ifndef BOOST_GENERIC_DETAIL_IS_THIS_HPP
#define BOOST_GENERIC_DETAIL_IS_THIS_HPP

#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/starts_empty_or_parenthesized.hpp>
#include <boost/generic/detail/num_args_is_2.hpp>
#include <boost/generic/detail/variadic_cat.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/control/iif.hpp>

// Begin "starts with this" macros
#define BOOST_GENERIC_DETAIL_STARTS_WITH_THIS( ... )                           \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_STARTS_EMPTY_OR_PARENTHESIZED( __VA_ARGS__ )            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( 0 )                                  \
, BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPL                                   \
)( __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_STARTS_WITH_THIS_IMPL( ... )                      \
BOOST_GENERIC_DETAIL_NUM_ARGS_AFTER_RESCAN_IS_2                                \
( BOOST_GENERIC_DETAIL_VARIADIC_CAT                                            \
  ( BOOST_GENERIC_DETAIL_STARTS_WITH_THIS                                      \
  , BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ )                          \
  )                                                                            \
)

#define BOOST_GENERIC_DETAIL_STARTS_WITH_THISthis ,

// Begin "eat this" macros
#define BOOST_GENERIC_DETAIL_EAT_THIS( ... )                                   \
BOOST_GENERIC_DETAIL_VARIADIC_CAT                                              \
( BOOST_GENERIC_DETAIL_EAT_THIS, __VA_ARGS__ )

#define BOOST_GENERIC_DETAIL_EAT_THISthis

#endif // BOOST_GENERIC_DETAIL_IS_THIS_HPP
