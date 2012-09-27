/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_preincrement.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::HasPreincrement;
using boost::generic::std_concept::SameType;

struct a {};

struct preincrement_type
{
  friend preincrement_type& operator++( preincrement_type );
};

BOOST_GENERIC_ASSERT( HasPreincrement< int > );
BOOST_GENERIC_ASSERT( HasPreincrement< preincrement_type > );
BOOST_GENERIC_ASSERT( SameType< HasPreincrement< int >::result_type, int& > );
BOOST_GENERIC_ASSERT( SameType< HasPreincrement< preincrement_type >::result_type, preincrement_type& > );

struct no_preincrement_type {};

struct postincrement_type
{
  friend a operator++( preincrement_type, int );
};

BOOST_GENERIC_ASSERT_NOT( HasPreincrement< no_preincrement_type > );
BOOST_GENERIC_ASSERT_NOT( HasPreincrement< postincrement_type > );
BOOST_GENERIC_ASSERT_NOT( HasPreincrement< void > );
