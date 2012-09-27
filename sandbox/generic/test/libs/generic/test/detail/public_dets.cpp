/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/public_dets.hpp>

// ToDo: Add tests for incorrect input

/////////////////////////
// Prepare Test Inputs //
/////////////////////////
#define INVALID_NOT_PUBLIC                                                     \
BOOST_GENERIC_DETAIL_PUBLIC_DETS( foo )

#define PARTIAL_NOT_SEQ                                                        \
BOOST_GENERIC_DETAIL_PUBLIC_DETS( public )

#define VALID_PUBLIC                                                           \
BOOST_GENERIC_DETAIL_PUBLIC_DETS( public foo< T, U > )

#define VALID_PUBLIC_SEQ                                                       \
BOOST_GENERIC_DETAIL_PUBLIC_DETS( public (foo< T, U >) (bar< T, U >) )

#if BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_VALID( INVALID_NOT_PUBLIC )
#error Invalid public argument considered valid.
#endif

#if BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_PARTIAL( INVALID_NOT_PUBLIC )
#error Invalid public argument considered partial.
#endif

#if BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_VALID( PARTIAL_NOT_SEQ )
#error Partial public argument considered valid.
#endif

#if !BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_PARTIAL( PARTIAL_NOT_SEQ )
#error Partial public argument considered not partial.
#endif

#if !BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_VALID( VALID_PUBLIC )
#error Valid public argument considered invalid.
#endif

#if !BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_PARTIAL( VALID_PUBLIC )
#error Valid public argument considered not partial.
#endif

#if !BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_VALID( VALID_PUBLIC_SEQ )
#error Valid public sequence argument considered invalid.
#endif

#if !BOOST_GENERIC_DETAIL_PUBLIC_DETS_IS_PARTIAL( VALID_PUBLIC_SEQ )
#error Valid public sequence argument considered not partial.
#endif
