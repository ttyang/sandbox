/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/regular.hpp>

#include <boost/generic/assert.hpp>

struct regular_type
{
  friend bool operator ==( regular_type, regular_type );
  friend bool operator !=( regular_type, regular_type );
};

using boost::generic::std_concept::Regular;

BOOST_GENERIC_ASSERT( Regular< int > );
BOOST_GENERIC_ASSERT( Regular< char* > );
BOOST_GENERIC_ASSERT( Regular< void* > );

BOOST_GENERIC_ASSERT( Regular< regular_type > );

BOOST_GENERIC_ASSERT_NOT( Regular< int& > );
BOOST_GENERIC_ASSERT_NOT( Regular< void > );
BOOST_GENERIC_ASSERT_NOT( Regular< int[4] > );
BOOST_GENERIC_ASSERT_NOT( Regular< int() > );
