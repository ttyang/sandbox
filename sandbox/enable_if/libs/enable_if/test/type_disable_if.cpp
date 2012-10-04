/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#include <boost/utility/enable_if_macros.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <utility>

template< class T, class = void >
struct is_arithmetic : boost::mpl::false_ {};

template< class T >
struct is_arithmetic
       < T, BOOST_TYPE_DISABLE_IF
            ( boost::mpl::not_< boost::is_arithmetic< T > > )
       >
  : boost::mpl::true_ {};

struct not_arithmetic_t {};

static_assert( is_arithmetic< int >::value
             , "int incorrectly detected as not being arithmetic."
             );

static_assert( is_arithmetic< double >::value
             , "double incorrectly detected as not being arithmetic."
             );

static_assert( !is_arithmetic< not_arithmetic_t >::value
             , "not_arithmetic_t incorrectly detected as begin arithmetic."
             );
