/*==============================================================================
    Copyright (c) 2010 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_GENERIC_DETAIL_STD_FORWARD_DECL_HPP
#define BOOST_GENERIC_DETAIL_STD_FORWARD_DECL_HPP

#include <boost/generic/config/std_lib.hpp>

#if BOOST_GENERIC_STD_LIB_IS_SUPPORTED()

#include <boost/generic/detail/nary_cat.hpp>

// Yields a header file to include to ge a forward declaration of name
#define BOOST_GENERIC_DETAIL_FORWARD_DECL_HEADER( name )                       \
BOOST_GENERIC_DETAIL_NARY_CAT                                                  \
(<boost/generic/detail/std_forward_decl/_,BOOST_GENERIC_STD_LIB,_/_,name,_.hpp>)

// Yields the Boost.Generic style template parameter list for name
// Requires that the corresponding forward declaration header is included first
#define BOOST_GENERIC_DETAIL_FORWARD_DECL_PARAMS( name )                       \
BOOST_GENERIC_DETAIL_NARY_CAT                                                  \
( BOOST_GENERIC_DETAIL_STD_FWD_DECL_PARAMS_, BOOST_GENERIC_STD_LIB, _, name  )()

// Yields the type name for name given the above parameter list
// Requires that the corresponding forward declaration header is included first
#define BOOST_GENERIC_DETAIL_FORWARD_DECL_NAME( name )                         \
BOOST_GENERIC_DETAIL_NARY_CAT                                                  \
( BOOST_GENERIC_DETAIL_STD_FWD_DECL_NAME_, BOOST_GENERIC_STD_LIB, _, name )()

#else

// ToDo: Come up with better definitions for these

// Yields a header file to include to ge a forward declaration of name
#define BOOST_GENERIC_DETAIL_FORWARD_DECL_HEADER( name )                       \
<boost/generic/detail/empty_file.hpp>

// Yields the Boost.Generic style template parameter list for name
// Requires that the corresponding forward declaration header is included first
#define BOOST_GENERIC_DETAIL_FORWARD_DECL_PARAMS( name )

// Yields the type name for name given the above parameter list
// Requires that the corresponding forward declaration header is included first
#define BOOST_GENERIC_DETAIL_FORWARD_DECL_NAME( name )

#endif

#endif // BOOST_GENERIC_DETAIL_STD_FORWARD_DECL_HPP
