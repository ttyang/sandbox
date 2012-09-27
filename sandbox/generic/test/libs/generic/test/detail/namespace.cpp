/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/namespace.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#define NOT_PAREN_DETS                                                         \
BOOST_GENERIC_DETAIL_NAMESPACE_DETS( not_parenthesized )

#define NOT_NAMESPACE_DETS                                                     \
BOOST_GENERIC_DETAIL_NAMESPACE_DETS( ( not_namespace ) )

#define VALID_NAMESPACE_UNNAMED                                                \
BOOST_GENERIC_DETAIL_NAMESPACE_DETS( ( namespace ) )

#define VALID_NAMESPACE_DETS                                                   \
BOOST_GENERIC_DETAIL_NAMESPACE_DETS( ( namespace my, namespace_ ) )

#define VALID_ANON_NAMESPACE_DETS                                              \
BOOST_GENERIC_DETAIL_NAMESPACE_DETS( ( namespace my, other, namespace_, ) )

// NOT_PAREN_DETS tests begin
#if BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID( NOT_PAREN_DETS )
#error Unparenthesized text recognized as namespace declaration.
#endif

#if BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_PARENTHESIZED( NOT_PAREN_DETS )
#error Unparenthesized text recognized as parenthesized.
#endif

#if BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_NAMESPACE( NOT_PAREN_DETS )
#error Unparenthesized text recognized as namespace declaration.
#endif

// NOT_NAMESPACE_DETS tests begin
#if BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID( NOT_NAMESPACE_DETS )
#error Nonnamespace recognized as namespace declaration.
#endif

#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_PARENTHESIZED( NOT_NAMESPACE_DETS )
#error Nonnamespace recognized as unparenthesized.
#endif

#if BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_NAMESPACE( NOT_NAMESPACE_DETS )
#error Nonnamespace recognized as namespace declaration.
#endif

// VALID_NAMESPACE_UNNAMED tests begin
#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID(                              \
      VALID_NAMESPACE_UNNAMED )
#error Unnamed namespace without sequence recognized as namespace declaration.
#endif

#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_PARENTHESIZED(                     \
      VALID_NAMESPACE_UNNAMED )
#error Namespace without sequence recognized as unparenthesized.
#endif

#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_NAMESPACE(                         \
      VALID_NAMESPACE_UNNAMED )
#error Namespace without sequence recognized as nonnamespace declaration.
#endif

// VALID_NAMESPACE_DETS tests begin
#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID(                             \
      VALID_NAMESPACE_DETS )
#error Valid namespace recognized as not a namespace declaration.
#endif

#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_PARENTHESIZED(                     \
      VALID_NAMESPACE_DETS )
#error Valid namespace recognized as unparenthesized.
#endif

#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_NAMESPACE(                         \
      VALID_NAMESPACE_DETS )
#error Valid namespace recognized as nonnamespace declaration.
#endif

struct namespace_checker;
struct anon_namespace_checker;

BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE( VALID_NAMESPACE_DETS )

struct namespace_checker {};

BOOST_GENERIC_DETAIL_NAMESPACE_DETS_CLOSE_NAMESPACE( VALID_NAMESPACE_DETS )

namespace my { namespace namespace_ {

// ToDo: Use BOOST_STATIC_ASSERT_MSG
BOOST_STATIC_ASSERT
( (!boost::is_same< ::namespace_checker, namespace_checker >::value) );

} }

BOOST_STATIC_ASSERT
( (!boost::is_same
  < ::namespace_checker
  , decltype
    ( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE
      ( VALID_NAMESPACE_DETS )
      namespace_checker()
    )
  >::value
  )
);


// VALID_ANON_NAMESPACE_DETS tests begin
#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID(                             \
      VALID_ANON_NAMESPACE_DETS )
#error Valid anonymous namespace recognized as not a namespace declaration.
#endif

#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_PARENTHESIZED(                     \
      VALID_ANON_NAMESPACE_DETS )
#error Valid anonymous namespace recognized as unparenthesized.
#endif

#if !BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_NAMESPACE(                         \
      VALID_ANON_NAMESPACE_DETS )
#error Valid anonymous namespace recognized as nonnamespace declaration.
#endif

BOOST_GENERIC_DETAIL_NAMESPACE_DETS_OPEN_NAMESPACE( VALID_ANON_NAMESPACE_DETS )

struct anon_namespace_checker {};

BOOST_GENERIC_DETAIL_NAMESPACE_DETS_CLOSE_NAMESPACE( VALID_ANON_NAMESPACE_DETS )

namespace my { namespace other { namespace namespace_ { namespace {

// ToDo: Use BOOST_STATIC_ASSERT_MSG
BOOST_STATIC_ASSERT
( (!boost::is_same< ::anon_namespace_checker,anon_namespace_checker >::value) );

} } } }

BOOST_STATIC_ASSERT
( (!boost::is_same
  < ::anon_namespace_checker
  , decltype
    ( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_ACCESS_NAMESPACE
      ( VALID_ANON_NAMESPACE_DETS )
      anon_namespace_checker()
    )
  >::value
  )
);
