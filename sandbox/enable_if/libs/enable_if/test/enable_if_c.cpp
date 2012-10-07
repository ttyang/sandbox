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

boost::mpl::false_ is_arithmetic( ... );

template< class T
        , BOOST_ENABLE_IF_C
          ( boost::is_arithmetic< T >::value )
        >
boost::mpl::true_ is_arithmetic( T );

struct not_arithmetic_t {};

static_assert( decltype( is_arithmetic( 1 ) )::value
             , "int incorrectly detected as not being arithmetic."
             );

static_assert( decltype( is_arithmetic( 1. ) )::value
             , "double incorrectly detected as not being arithmetic."
             );

static_assert( !decltype( is_arithmetic( not_arithmetic_t() ) )::value
             , "not_arithmetic_t incorrectly detected as beingarithmetic."
             );
