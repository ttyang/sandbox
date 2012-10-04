/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#include <boost/utility/enable_if_macros.hpp>

#include <boost/mpl/bool.hpp>
#include <utility>

boost::mpl::false_ has_plus( ... );

template< class T
        , BOOST_ENABLE_IF_EXPR
          ( std::declval< T >() + std::declval< T >() )
        >
boost::mpl::true_ has_plus( T );

struct has_plus_t {};

void operator +( has_plus_t const&, has_plus_t const& );

struct no_plus_t {};

static_assert( decltype( has_plus( 1 ) )::value
             , "int incorrectly detected as not having plus."
             );

static_assert( decltype( has_plus( has_plus_t() ) )::value
             , "has_plus_t incorrectly detected as not having plus."
             );

static_assert( !decltype( has_plus( no_plus_t() ) )::value
             , "no_plus_t incorrectly detected as having plus."
             );
