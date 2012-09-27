/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/test/minimal.hpp>

#include <boost/generic/detail/ad_hoc_concept/arg_details.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

#define NULL_ARG_DETAILS \
BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS \
( ( foo, ( (class) X, (class) Y ) ) )

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FATAL_ERROR( NULL_ARG_DETAILS )
#error Fatal error with null arg concept
#endif

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_CONDITIONAL_ARGS(                \
      NULL_ARG_DETAILS )
#error Conditional args detected with null arg concept
#endif

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_PUBLIC_CATEGORY(                 \
      NULL_ARG_DETAILS )
#error Public args detected with null arg concept
#endif

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_FOR_CATEGORY( NULL_ARG_DETAILS )
#error For args detected with null arg concept
#endif

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_FOR_TYPEDEF_CATEGORY(            \
      NULL_ARG_DETAILS )
#error For typedef args detected with null arg concept
#endif

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_ERRORS( NULL_ARG_DETAILS )
#error Errors detected with null arg concept
#endif

int test_main( int argc, char* argv[] )
{
  return 0;
}
