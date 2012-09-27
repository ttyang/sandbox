/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/axiom_dets.hpp>

#define NOT_AXIOM_DETS                                                         \
BOOST_GENERIC_DETAIL_AXIOM_DETS( not axiom )

#define PAREN_AXIOM_DETS                                                       \
BOOST_GENERIC_DETAIL_AXIOM_DETS( axiom () )

#define EMPTY_AXIOM_DETS                                                       \
BOOST_GENERIC_DETAIL_AXIOM_DETS( axiom )

#define VALID_AXIOM_DETS                                                       \
BOOST_GENERIC_DETAIL_AXIOM_DETS( axiom Stateless( a _1, a _2 ) { _1 == _2; } )

///// NOT_AXIOM_DETS
#if BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_VALID( NOT_AXIOM_DETS )
#error Nonaxiom detected as a valid axiom.
#endif

#if BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_PARTIAL( NOT_AXIOM_DETS )
#error Nonaxiom detected as a partial axiom.
#endif

///// PAREN_AXIOM_DETS
#if BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_VALID( PAREN_AXIOM_DETS )
#error Nonaxiom detected as a valid axiom.
#endif

#if !BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_PARTIAL( PAREN_AXIOM_DETS )
#error Nonaxiom not detected as a partial axiom.
#endif

///// EMPTY_AXIOM_DETS
#if BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_VALID( EMPTY_AXIOM_DETS )
#error Empty axiom detected as a valid axiom.
#endif

#if !BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_PARTIAL( EMPTY_AXIOM_DETS )
#error Empty axiom not detected as a partial axiom.
#endif

///// VALID_AXIOM_DETS
#if !BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_VALID( VALID_AXIOM_DETS )
#error Valid axiom not detected as an axiom.
#endif

#if !BOOST_GENERIC_DETAIL_AXIOM_DETS_IS_PARTIAL( VALID_AXIOM_DETS )
#error Valid axiom not detected as a partial axiom.
#endif
