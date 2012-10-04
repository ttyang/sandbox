/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#include <boost/utility/enable_if_macros.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <utility>

template< class T >
struct static_assert_if_not_arithmetic
  : boost::mpl::true_
{
  static_assert( boost::is_arithmetic< T >::value
               , "Lazy type is incorrectly instantiated."
               );
};

boost::mpl::false_ is_arithmetic( ... );

template< class T
        , BOOST_LAZY_DISABLE_IF_C
          ( !boost::is_arithmetic< T >::value
          , ( ResultType, typename static_assert_if_not_arithmetic< T >::type )
          , ( DefaultParamType
            , typename static_assert_if_not_arithmetic< T >::type
            )
          )
        >
ResultType is_arithmetic( T, DefaultParamType = DefaultParamType() );

struct not_arithmetic_t {};

static_assert( decltype( is_arithmetic( 1 ) )::value
             , "int incorrectly detected as not being arithmetic."
             );

static_assert( decltype( is_arithmetic( 1. ) )::value
             , "double incorrectly detected as not being arithmetic."
             );

static_assert( !decltype( is_arithmetic( not_arithmetic_t() ) )::value
             , "not_arithmetic_t incorrectly detected as begin arithmetic."
             );
