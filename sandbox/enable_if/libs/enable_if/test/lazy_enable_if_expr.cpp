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
struct error_if_not_has_plus
  : boost::mpl::true_
{
  typedef decltype( std::declval< T >() + std::declval< T >() ) error;
};


boost::mpl::false_ has_plus( ... );

template< class T
        , BOOST_LAZY_ENABLE_IF_EXPR
          ( std::declval< T >() + std::declval< T >()
          , ( ResultType, typename error_if_not_has_plus< T >::type )
          , ( DefaultParamType, typename error_if_not_has_plus< T >::type )
          )
        >
ResultType has_plus( T, DefaultParamType = DefaultParamType() );

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
