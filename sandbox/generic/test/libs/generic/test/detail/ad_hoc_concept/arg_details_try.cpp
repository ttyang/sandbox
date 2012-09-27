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

#define TRY_ARG_DETAILS \
BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETAILS \
( ( foo, ( (class) X, (class) Y ) ) \
, ( try ( x() + T() ) ) \
)

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_FATAL_ERROR( TRY_ARG_DETAILS )
#error Fatal error with try arg concept
#endif

#if !BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_CONDITIONAL_ARGS(                \
      TRY_ARG_DETAILS )
#error No conditional args detected with try arg concept
#endif

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_PUBLIC_CATEGORY(                 \
      TRY_ARG_DETAILS )
#error Public args detected with try arg concept
#endif

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_FOR_CATEGORY( TRY_ARG_DETAILS )
#error For args detected with try arg concept
#endif

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_FOR_TYPEDEF_CATEGORY(            \
      TRY_ARG_DETAILS )
#error For typedef args detected with try arg concept
#endif

#if BOOST_GENERIC_DETAIL_AD_HOC_CONCEPT_ARG_DETS_HAS_ERRORS( TRY_ARG_DETAILS )
#error Errors detected with try arg concept
#endif
