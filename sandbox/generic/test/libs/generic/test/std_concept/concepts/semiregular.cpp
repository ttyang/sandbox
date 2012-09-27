/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/semiregular.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::Semiregular;

BOOST_GENERIC_ASSERT( Semiregular< int > );
BOOST_GENERIC_ASSERT( Semiregular< char* > );
BOOST_GENERIC_ASSERT( Semiregular< void* > );

struct semiregular_type {};

BOOST_GENERIC_ASSERT( Semiregular< semiregular_type > );

struct not_semiregular_type
{
  int operator =( not_semiregular_type& );
};

BOOST_GENERIC_ASSERT_NOT( Semiregular< not_semiregular_type > );

BOOST_GENERIC_ASSERT_NOT( Semiregular< int& > );
BOOST_GENERIC_ASSERT_NOT( Semiregular< void > );
BOOST_GENERIC_ASSERT_NOT( Semiregular< int[4] > );
BOOST_GENERIC_ASSERT_NOT( Semiregular< int() > );
