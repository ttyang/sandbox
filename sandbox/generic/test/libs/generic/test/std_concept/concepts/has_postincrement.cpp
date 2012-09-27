/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_postincrement.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasPostincrement;
using boost::generic::std_concept::SameType;

struct a {};

struct postincrement_type
{
  friend a operator++( postincrement_type, int );
};

BOOST_GENERIC_ASSERT( HasPostincrement< int > );
BOOST_GENERIC_ASSERT( HasPostincrement< postincrement_type > );
BOOST_GENERIC_ASSERT( SameType< HasPostincrement< int >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< HasPostincrement< postincrement_type >::result_type, a > );

struct no_postincrement_type {};

struct preincrement_type
{
  friend preincrement_type& operator++( preincrement_type );
};

BOOST_GENERIC_ASSERT_NOT( HasPostincrement< no_postincrement_type > );
BOOST_GENERIC_ASSERT_NOT( HasPostincrement< preincrement_type > );
BOOST_GENERIC_ASSERT_NOT( HasPostincrement< void > );
