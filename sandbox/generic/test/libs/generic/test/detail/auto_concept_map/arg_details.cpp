/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/test/minimal.hpp>

#include <boost/generic/detail/auto_concept_map/arg_details.hpp>

#define VALID_TPL   ( (class) X )
#define INVALID_TPL class X
#define VOID_TPL    ( void )

#define INVALID_NAME_PARAM class X
#define VALID_NAME_PARAM   ( some_concept_name )( some, params )

#define VALID_DETS                                                             \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS                              \
( VALID_TPL, VALID_NAME_PARAM )

#define INVALID_TPL_DETS                                                       \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS                              \
( INVALID_TPL, VALID_NAME_PARAM )

#define VOID_TPL_DETS                                                          \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS                              \
( VOID_TPL, VALID_NAME_PARAM )

#define INVALID_NAME_PARAM_DETS                                                \
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETAILS                              \
( VALID_TPL, INVALID_NAME_PARAM )

#if BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_HAS_ERRORS( VALID_DETS )
BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_EMIT_ERRORS( VALID_DETS )
#endif

#if !BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_HAS_ERRORS( \
    INVALID_TPL_DETS )
#error Auto concept map details considered valid with invalid template params.
#endif

// ToDo: Fix this test
#if !BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_HAS_ERRORS( \
    VOID_TPL_DETS )
#error Auto concept map details considered valid with void template params.
#endif

#if !BOOST_GENERIC_DETAIL_AUTO_CONCEPT_MAP_ARG_DETS_HAS_ERRORS( \
    INVALID_NAME_PARAM_DETS )
#error Auto concept map details considered valid with invalid concept/params.
#endif

int test_main( int argc, char* argv[] )
{
  return 0;
}
