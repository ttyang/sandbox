/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_logical_not.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::HasLogicalNot;

BOOST_GENERIC_ASSERT( HasLogicalNot< int > );
BOOST_GENERIC_ASSERT( HasLogicalNot< long > );
BOOST_GENERIC_ASSERT( HasLogicalNot< short > );
BOOST_GENERIC_ASSERT( HasLogicalNot< unsigned > );
BOOST_GENERIC_ASSERT( HasLogicalNot< float > );
BOOST_GENERIC_ASSERT( HasLogicalNot< void* > );

struct non_logical_not_object {};

BOOST_GENERIC_ASSERT( HasLogicalNot< void (non_logical_not_object::*)() > );
BOOST_GENERIC_ASSERT( HasLogicalNot< int (non_logical_not_object::*) > );
BOOST_GENERIC_ASSERT_NOT( HasLogicalNot< non_logical_not_object > );

struct logical_not_result {};

struct logical_not_object
{
  bool operator !() const;
};

BOOST_GENERIC_ASSERT( HasLogicalNot< logical_not_object > );

struct logical_not_void_object
{
  void operator !() const;
};

BOOST_GENERIC_ASSERT_NOT( HasLogicalNot< logical_not_void_object > );
BOOST_GENERIC_ASSERT_NOT( HasLogicalNot< void > );
