/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/concept_map/typedef_dets.hpp>

#define INVALID_DETS \
BOOST_GENERIC_DETAIL_TYPEDEF_DETS( int result_type )

#define PARTIAL_DETS \
BOOST_GENERIC_DETAIL_TYPEDEF_DETS( typedef )

#define VALID_DETS \
BOOST_GENERIC_DETAIL_TYPEDEF_DETS( typedef int result_type )

#if BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_VALID( INVALID_DETS )
#error "Invalid typedef considered valid."
#endif

#if BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_PARTIAL( INVALID_DETS )
#error "Invalid typedef considered partial."
#endif

#if BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_VALID( PARTIAL_DETS )
#error "Partial typedef considered valid."
#endif

#if !BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_PARTIAL( PARTIAL_DETS )
#error "Partial typedef not considered partial."
#endif

#if !BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_VALID( VALID_DETS )
#error "Valid typedef not considered valid."
#endif

#if !BOOST_GENERIC_DETAIL_TYPEDEF_DETS_IS_PARTIAL( VALID_DETS )
#error "Valid typedef not considered partial."
#endif

struct a
{
  BOOST_GENERIC_DETAIL_TYPEDEF_DETS_STATEMENT( VALID_DETS )
};

a::result_type foo;
