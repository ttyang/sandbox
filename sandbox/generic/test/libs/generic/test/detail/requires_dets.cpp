/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/requires_dets.hpp>

// ToDo: Add tests for incorrect input

/////////////////////////
// Prepare Test Inputs //
/////////////////////////
#define INVALID_NOT_REQUIRES                                                   \
BOOST_GENERIC_DETAIL_REQUIRES_DETS( foo )

#define PARTIAL_EMPTY_REQS                                                     \
BOOST_GENERIC_DETAIL_REQUIRES_DETS( requires )

#define VALID_REQUIRES                                                         \
BOOST_GENERIC_DETAIL_REQUIRES_DETS( requires CopyConstructible< T > )

#if BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_VALID( INVALID_NOT_REQUIRES )
#error Invalid requires argument considered valid.
#endif

#if BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_PARTIAL( INVALID_NOT_REQUIRES )
#error Invalid requires argument considered partial.
#endif

#if BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_VALID( PARTIAL_EMPTY_REQS )
#error Partial requires argument considered valid.
#endif

#if !BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_PARTIAL( PARTIAL_EMPTY_REQS )
#error Partial requires argument considered not partial.
#endif

#if !BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_VALID( VALID_REQUIRES )
#error Valid requires argument considered invalid.
#endif

#if !BOOST_GENERIC_DETAIL_REQUIRES_DETS_IS_PARTIAL( VALID_REQUIRES )
#error Valid requires argument considered not partial.
#endif
