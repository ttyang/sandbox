/*==============================================================================
    Copyright (c) 2012 Matt Calabrese

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

//[enable_if_constructor_example
#include <boost/utility/enable_if_macros.hpp>

struct constructable_with_3_arguments
{
  template< class... T, BOOST_ENABLE_IF_C( sizeof...( T ) == 3 ) >
  constructable_with_3_arguments( T&&... );
};

constructable_with_3_arguments this_will_compile( 1, 2.0, '3' );
//constructable_with_3_arguments this_would_not_compile( 1, 2.0, '3', 4.f );
//]
