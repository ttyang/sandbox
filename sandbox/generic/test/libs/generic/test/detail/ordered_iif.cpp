/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/ordered_iif.hpp>
#include <boost/generic/detail/variadic_identity.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/type_traits/is_same.hpp>

#define TRANSFORM_10( state ) BOOST_PP_ADD( state, 10 )
#define TRANSFORM_50( state ) BOOST_PP_ADD( state, 50 )
#define TRANSFORM_100( state ) BOOST_PP_ADD( state, 100 )

#define IS_10( state ) BOOST_PP_EQUAL( state, 10 )
#define IS_50( state ) BOOST_PP_EQUAL( state, 50 )
#define IS_100( state ) BOOST_PP_EQUAL( state, 100 )

#define TEN_MAC( state ) BOOST_PP_CAT( ten, state )
#define FIFTY_MAC( state ) BOOST_PP_CAT( fifty, state )
#define HUNDRED_MAC( state ) BOOST_PP_CAT( hundred, state )

#define EXPECT_TEN                                                             \
BOOST_GENERIC_DETAIL_ORDERED_IIF                                               \
( 0                                                                            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( unknown )                            \
, (TRANSFORM_10)(IS_10)(TEN_MAC)                                               \
, (TRANSFORM_50)(IS_50)(FIFTY_MAC)                                             \
, (TRANSFORM_100)(IS_100)(HUNDRED_MAC)                                         \
)

#define EXPECT_FIFTY                                                           \
BOOST_GENERIC_DETAIL_ORDERED_IIF                                               \
( 40                                                                           \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( unknown )                            \
, (TRANSFORM_50)(IS_10)(TEN_MAC)                                               \
, (TRANSFORM_10)(IS_50)(FIFTY_MAC)                                             \
, (TRANSFORM_100)(IS_100)(HUNDRED_MAC)                                         \
)

#define EXPECT_HUNDRED                                                         \
BOOST_GENERIC_DETAIL_ORDERED_IIF                                               \
( 50                                                                           \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( unknown )                            \
, (TRANSFORM_100)(IS_10)(TEN_MAC)                                              \
, (TRANSFORM_10)(IS_50)(FIFTY_MAC)                                             \
, (TRANSFORM_50)(IS_100)(HUNDRED_MAC)                                          \
)

#define EXPECT_UNKNOWN                                                         \
BOOST_GENERIC_DETAIL_ORDERED_IIF                                               \
( 0                                                                            \
, BOOST_GENERIC_DETAIL_VARIADIC_IDENTITY( unknown )                            \
, (TRANSFORM_100)(IS_10)(TEN_MAC)                                              \
, (TRANSFORM_10)(IS_50)(FIFTY_MAC)                                             \
, (TRANSFORM_50)(IS_100)(HUNDRED_MAC)                                          \
)

struct ten10;
struct fifty50;
struct hundred100;
struct unknown;

static_assert
( boost::is_same< ten10, EXPECT_TEN >::value
, "BOOST_GENERIC_DETAIL_ORDERED_IIF expected ten10, got "
  BOOST_PP_STRINGIZE( EXPECT_TEN )
);

static_assert
( boost::is_same< fifty50, EXPECT_FIFTY >::value
, "BOOST_GENERIC_DETAIL_ORDERED_IIF expected fifty50, got "
  BOOST_PP_STRINGIZE( EXPECT_FIFTY )
);

static_assert
( boost::is_same< hundred100, EXPECT_HUNDRED >::value
, "BOOST_GENERIC_DETAIL_ORDERED_IIF expected hundred100, got "
  BOOST_PP_STRINGIZE( EXPECT_HUNDRED )
);

static_assert
( boost::is_same< unknown, EXPECT_UNKNOWN >::value
, "BOOST_GENERIC_DETAIL_ORDERED_IIF expected unknown, got "
  BOOST_PP_STRINGIZE( EXPECT_UNKNOWN )
);
