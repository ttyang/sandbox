/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/predicate.hpp>

#include <boost/generic/assert.hpp>
#include <functional>

using boost::generic::std_concept::Predicate;

BOOST_GENERIC_ASSERT( Predicate< bool(int,float,char*), int, float, char* > );
BOOST_GENERIC_ASSERT_NOT( Predicate< bool(int,float,char*), int, float, void > );
BOOST_GENERIC_ASSERT_NOT( Predicate< void(int,float,char*), int, float, char > );

struct not_convertible_to_bool {};

struct predicate_type
{
  bool operator ()() const;
  bool operator ()( int, int, int, int ) const;
  not_convertible_to_bool operator ()( float, float, float, float ) const;
};

BOOST_GENERIC_ASSERT( Predicate< std::less< int >, int, int > );
BOOST_GENERIC_ASSERT( Predicate< predicate_type > );
BOOST_GENERIC_ASSERT( Predicate< predicate_type, int, int, int, int > );


BOOST_GENERIC_ASSERT_NOT( Predicate< predicate_type, float, float, float, float > );

BOOST_GENERIC_ASSERT_NOT( Predicate< void > );
BOOST_GENERIC_ASSERT_NOT( Predicate< void, void > );
BOOST_GENERIC_ASSERT_NOT( Predicate< void, int > );
BOOST_GENERIC_ASSERT_NOT( Predicate< int, void > );
BOOST_GENERIC_ASSERT_NOT( Predicate< predicate_type, void > );
