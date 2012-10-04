/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#include <boost/utility/enable_if_macros.hpp>

#include <boost/mpl/bool.hpp>
#include <utility>

template< class T, class = void >
struct has_plus_and_minus : boost::mpl::false_ {};

template< class T >
struct has_plus_and_minus
       < T
       , BOOST_TYPE_ENABLE_IF_EXPR
         ( ( std::declval< T >() + std::declval< T >() )
           ( std::declval< T >() - std::declval< T >() )
         )
       > : boost::mpl::true_ {};

struct has_plus_t {};

void operator +( has_plus_t const&, has_plus_t const& );

struct has_minus_t {};

void operator -( has_minus_t const&, has_minus_t const& );

struct has_plus_and_minus_t {};

void operator +( has_plus_and_minus_t const&, has_plus_and_minus_t const& );
void operator -( has_plus_and_minus_t const&, has_plus_and_minus_t const& );

static_assert( !has_plus_and_minus< void >::value
             , "void incorrectly detected as having plus and minus"
             );

static_assert( has_plus_and_minus< int >::value
             , "int incorrectly detected as not having plus and minus"
             );

static_assert( !has_plus_and_minus< has_plus_t >::value
             , "has_plus_t incorrectly detected as having plus and minus"
             );

static_assert( !has_plus_and_minus< has_minus_t >::value
             , "has_minus_t incorrectly detected as having plus and minus"
             );

static_assert
( has_plus_and_minus< has_plus_and_minus_t >::value
, "has_plus_and_minus_t incorrectly detected as not having plus and minus"
);
