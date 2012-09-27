/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/detail/this_mem_dets.hpp>

#define NOT_THIS_MEM_DETS                                                      \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS( not this )

#define NO_PAREN_THIS_MEM_DETS                                                 \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS( this no paren )

#define EMPTY_PAREN_THIS_MEM_DETS                                              \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS( this() )

#define VALID_THIS_MEM_DETS_NO_NAME                                            \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS( this(foo) )

#define VALID_THIS_MEM_DETS_WITH_NAME                                          \
BOOST_GENERIC_DETAIL_THIS_MEM_DETS( this(foo) bar )

///// NOT_THIS_MEM_DETS
#if BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( NOT_THIS_MEM_DETS )
#error Not this arg recognized as valid this member argument.
#endif

#if BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( NOT_THIS_MEM_DETS )
#error Not this arg recognized as partial this member argument.
#endif

///// NO_PAREN_THIS_MEM_DETS
#if BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( NO_PAREN_THIS_MEM_DETS )
#error This arg without type recognized as valid this member argument.
#endif

#if !BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_PARTIAL( NO_PAREN_THIS_MEM_DETS )
#error This arg without type not recognized as partial this member argument.
#endif

///// EMPTY_PAREN_THIS_MEM_DETS
#if BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( EMPTY_PAREN_THIS_MEM_DETS )
#error This arg with empty type recognized as valid this member argument.
#endif

#if !BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_PARTIAL( EMPTY_PAREN_THIS_MEM_DETS )
#error This arg with empty type not recognized as partial this member argument.
#endif

///// VALID_THIS_MEM_DETS_NO_NAME
#if !BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( VALID_THIS_MEM_DETS_NO_NAME )
#error This arg without name not recognized as valid this member argument.
#endif

#if !BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_PARTIAL( VALID_THIS_MEM_DETS_NO_NAME )
#error This arg without name not recognized as partial this member argument.
#endif

///// VALID_THIS_MEM_DETS_WITH_NAME
#if !BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_VALID( VALID_THIS_MEM_DETS_WITH_NAME )
#error This arg with name not recognized as valid this member argument.
#endif

#if !BOOST_GENERIC_DETAIL_THIS_MEM_DETS_IS_PARTIAL( VALID_THIS_MEM_DETS_WITH_NAME )
#error This arg with name not recognized as partial this member argument.
#endif
