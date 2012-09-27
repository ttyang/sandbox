/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/trivially_copy_constructible.hpp>

#include <boost/generic/assert.hpp>

struct trivially_copy_constructible_type {};

struct trivially_copy_constructible_reference_member_type
{
  int& foo;
};

struct default_trivially_copy_constructible_type
{
  default_trivially_copy_constructible_type
  ( default_trivially_copy_constructible_type const& ) = default;
};

struct noncopy_constructible_type
{
  noncopy_constructible_type( noncopy_constructible_type const& )
    = delete;
};

struct nontrivially_copy_constructible_type
{
  nontrivially_copy_constructible_type( nontrivially_copy_constructible_type const& );
};

using boost::generic::std_concept::TriviallyCopyConstructible;

BOOST_GENERIC_ASSERT( TriviallyCopyConstructible< int > );
BOOST_GENERIC_ASSERT( TriviallyCopyConstructible< int[4] > );
BOOST_GENERIC_ASSERT( TriviallyCopyConstructible< int& > ); // TODO figure out if this should fail
BOOST_GENERIC_ASSERT( TriviallyCopyConstructible< trivially_copy_constructible_reference_member_type > ); // TODO figure out if this should fail
BOOST_GENERIC_ASSERT( TriviallyCopyConstructible< trivially_copy_constructible_type > );
BOOST_GENERIC_ASSERT( TriviallyCopyConstructible< default_trivially_copy_constructible_type > );

BOOST_GENERIC_ASSERT_NOT( TriviallyCopyConstructible< noncopy_constructible_type > );
BOOST_GENERIC_ASSERT_NOT( TriviallyCopyConstructible< nontrivially_copy_constructible_type > );
BOOST_GENERIC_ASSERT_NOT( TriviallyCopyConstructible< int[] > );
BOOST_GENERIC_ASSERT_NOT( TriviallyCopyConstructible< int() > );
BOOST_GENERIC_ASSERT_NOT( TriviallyCopyConstructible< void > );
