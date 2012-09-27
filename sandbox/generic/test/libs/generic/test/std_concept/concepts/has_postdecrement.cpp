/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_postdecrement.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasPostdecrement;
using boost::generic::std_concept::SameType;

struct a {};

struct postdecrement_type
{
  friend a operator--( postdecrement_type, int );
};

BOOST_GENERIC_ASSERT( HasPostdecrement< int > );
BOOST_GENERIC_ASSERT( HasPostdecrement< postdecrement_type > );
BOOST_GENERIC_ASSERT( SameType< HasPostdecrement< int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasPostdecrement< postdecrement_type >::result_type, a > );

struct no_postdecrement_type {};

struct predecrement_type
{
  friend predecrement_type& operator--( predecrement_type );
};

BOOST_GENERIC_ASSERT_NOT( HasPostdecrement< no_postdecrement_type > );
BOOST_GENERIC_ASSERT_NOT( HasPostdecrement< predecrement_type > );
BOOST_GENERIC_ASSERT_NOT( HasPostdecrement< void > );
