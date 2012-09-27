/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_AUTO_CONCEPT_HPP
#define BOOST_GENERIC_AUTO_CONCEPT_HPP

#include <boost/generic/concept.hpp>
//#include <boost/generic/concept_map.hpp>
#include <boost/generic/detail/assert_at_global_scope.hpp>
#include <boost/generic/detail/head_argument.hpp>
#include <boost/generic/detail/namespace.hpp>
#include <boost/generic/detail/tail_arguments.hpp>
#include <boost/preprocessor/control/iif.hpp>

#define BOOST_GENERIC_AUTO_CONCEPT( ... )                                      \
BOOST_GENERIC_DETAIL_ASSERT_AT_GLOBAL_SCOPE                                    \
( "The BOOST_GENERIC_AUTO_CONCEPT macro must be invoked at global scope. "     \
  "To make an auto concept inside a namespace, use a namespace parameter."     \
)                                                                              \
BOOST_GENERIC_AUTO_CONCEPT_DETAIL_IMPL_                                        \
( BOOST_GENERIC_DETAIL_NAMESPACE_DETS                                          \
  ( BOOST_GENERIC_DETAIL_HEAD_ARGUMENT( __VA_ARGS__ ) )                        \
, __VA_ARGS__                                                                  \
)

#define BOOST_GENERIC_AUTO_CONCEPT_DETAIL_IMPL_( namespace_dets, ... )         \
BOOST_PP_IIF                                                                   \
( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_NAMESPACE( namespace_dets )           \
, BOOST_GENERIC_AUTO_CONCEPT_DETAIL_IMPL_NAMESPACE                             \
, BOOST_GENERIC_AUTO_CONCEPT_DETAIL_NO_NAMESPACE                               \
)( namespace_dets, __VA_ARGS__ )

#define BOOST_GENERIC_AUTO_CONCEPT_DETAIL_IMPL_NAMESPACE( namespace_dets, ... )\
BOOST_PP_IIF( BOOST_GENERIC_DETAIL_NAMESPACE_DETS_IS_VALID( namespace_dets )   \
            , BOOST_GENERIC_AUTO_CONCEPT_DETAIL_VALID_NAMESPACE                \
            , BOOST_GENERIC_AUTO_CONCEPT_DETAIL_INVALID_NAMESPACE              \
            )( namespace_dets, __VA_ARGS__ )

#define BOOST_GENERIC_AUTO_CONCEPT_DETAIL_VALID_NAMESPACE(namespace_dets,...)  \
BOOST_GENERIC_CONCEPT_IMPL                                                     \
( 1, namespace_dets                                                            \
, BOOST_GENERIC_DETAIL_CONCEPT_DETS                                            \
  ( BOOST_GENERIC_DETAIL_TAIL_ARGUMENTS( __VA_ARGS__ ) )                       \
)

#define BOOST_GENERIC_AUTO_CONCEPT_DETAIL_INVALID_NAMESPACE(namespace_dets,...)\
static_assert                                                                  \
( false, "Invalid namespace parameter of BOOST_GENERIC_AUTO_CONCEPT." );

#define BOOST_GENERIC_AUTO_CONCEPT_DETAIL_NO_NAMESPACE( namespace_dets, ... )  \
BOOST_GENERIC_CONCEPT_IMPL                                                     \
( 1, namespace_dets, BOOST_GENERIC_DETAIL_CONCEPT_DETS( __VA_ARGS__ ) )                                                                              \

#endif // BOOST_GENERIC_AUTO_CONCEPT_HPP
