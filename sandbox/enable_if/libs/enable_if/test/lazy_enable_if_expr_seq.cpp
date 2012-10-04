/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#include <boost/utility/enable_if_macros.hpp>

#include <boost/mpl/bool.hpp>
#include <utility>


template< class T >
struct error_if_not_has_plus_and_minus
  : boost::mpl::true_
{
  typedef decltype( std::declval< T >() + std::declval< T >() ) error_plus;
  typedef decltype( std::declval< T >() - std::declval< T >() ) error_minus;
};


boost::mpl::false_ has_plus_and_minus( ... );

template< class T
        , BOOST_LAZY_ENABLE_IF_EXPR
          ( ( std::declval< T >() + std::declval< T >() )
            ( std::declval< T >() - std::declval< T >() )
          , ( ResultType, typename error_if_not_has_plus_and_minus< T >::type )
          , ( DefaultParamType
            , typename error_if_not_has_plus_and_minus< T >::type
            )
          )
        >
ResultType has_plus_and_minus( T, DefaultParamType = DefaultParamType() );

struct has_plus_t {};

void operator +( has_plus_t const&, has_plus_t const& );

struct has_minus_t {};

void operator -( has_minus_t const&, has_minus_t const& );

struct has_plus_and_minus_t {};

void operator +( has_plus_and_minus_t const&, has_plus_and_minus_t const& );
void operator -( has_plus_and_minus_t const&, has_plus_and_minus_t const& );

static_assert( decltype( has_plus_and_minus( 1 ) )::value
             , "int incorrectly detected as not having plus and minus"
             );

static_assert( !decltype( has_plus_and_minus( has_plus_t() ) )::value
             , "has_plus_t incorrectly detected as having plus and minus"
             );

static_assert( !decltype( has_plus_and_minus( has_minus_t() ) )::value
             , "has_minus_t incorrectly detected as having plus and minus"
             );

static_assert
( decltype( has_plus_and_minus( has_plus_and_minus_t() ) )::value
, "has_plus_and_minus_t incorrectly detected as not having plus and minus"
);
