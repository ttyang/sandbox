/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/callable.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

struct a {}; struct b {}; struct c {};

struct callable_object
{
  void operator ()() const;
  int operator ()( a const& ) const;
  float operator ()( a const&, b const& ) const;
  double operator ()( a const&, b const&, c const& ) const;
};

using boost::generic::std_concept::Callable;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( Callable< callable_object > );
BOOST_GENERIC_ASSERT( Callable< callable_object, a > );
BOOST_GENERIC_ASSERT( Callable< callable_object, a, b > );
BOOST_GENERIC_ASSERT( Callable< callable_object, a, b, c > );

BOOST_GENERIC_ASSERT( SameType< Callable< callable_object >::result_type, void > );
BOOST_GENERIC_ASSERT( SameType< Callable< callable_object, a >::result_type, int > );
BOOST_GENERIC_ASSERT( SameType< Callable< callable_object, a, b >::result_type, float > );
BOOST_GENERIC_ASSERT( SameType< Callable< callable_object, a, b, c >::result_type, double > );

BOOST_GENERIC_ASSERT_NOT( Callable< callable_object, b > );
BOOST_GENERIC_ASSERT_NOT( Callable< callable_object, c > );
BOOST_GENERIC_ASSERT_NOT( Callable< callable_object, b, a > );
BOOST_GENERIC_ASSERT_NOT( Callable< callable_object, b, c, a > );
BOOST_GENERIC_ASSERT_NOT( Callable< callable_object, void > );

BOOST_GENERIC_ASSERT( Callable< int( a ), a > );
BOOST_GENERIC_ASSERT( SameType< Callable< int( a ), a >::result_type, int > );

BOOST_GENERIC_ASSERT( Callable< int(&)( a ), a > );
BOOST_GENERIC_ASSERT( SameType< Callable< int(&)( a ), a >::result_type, int > );

BOOST_GENERIC_ASSERT( Callable< int(*)( a ), a > );
BOOST_GENERIC_ASSERT( SameType< Callable< int(*)( a ), a >::result_type, int > );

BOOST_GENERIC_ASSERT_NOT( Callable< void > );
BOOST_GENERIC_ASSERT_NOT( Callable< void, a > );
BOOST_GENERIC_ASSERT_NOT( Callable< void, void > );
BOOST_GENERIC_ASSERT_NOT( Callable< void, void, void > );
