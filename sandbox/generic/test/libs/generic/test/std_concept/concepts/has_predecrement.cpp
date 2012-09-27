/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_predecrement.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasPredecrement;
using boost::generic::std_concept::SameType;

struct a {};

struct predecrement_type
{
  friend predecrement_type& operator--( predecrement_type );
};

BOOST_GENERIC_ASSERT( HasPredecrement< int > );
BOOST_GENERIC_ASSERT( HasPredecrement< predecrement_type > );
BOOST_GENERIC_ASSERT( SameType< HasPredecrement< int >::result_type, int& > );
BOOST_GENERIC_ASSERT( SameType< HasPredecrement< predecrement_type >::result_type, predecrement_type& > );

struct no_predecrement_type {};

struct postdecrement_type
{
  friend a operator--( predecrement_type, int );
};

BOOST_GENERIC_ASSERT_NOT( HasPredecrement< no_predecrement_type > );
BOOST_GENERIC_ASSERT_NOT( HasPredecrement< postdecrement_type > );
BOOST_GENERIC_ASSERT_NOT( HasPredecrement< void > );
