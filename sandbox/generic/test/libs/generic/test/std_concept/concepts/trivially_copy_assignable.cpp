/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/trivially_copy_assignable.hpp>

#include <boost/generic/assert.hpp>

struct copy_assignable_type {};

struct default_copy_assignable_type
{
  default_copy_assignable_type& operator=( default_copy_assignable_type const& )
    = default;
};

struct nontrivial_copy_assignable_type
{
  nontrivial_copy_assignable_type&
  operator=( nontrivial_copy_assignable_type const& );
};

struct noncopy_assignable_type
{
  noncopy_assignable_type& operator=( noncopy_assignable_type const& ) = delete;
};

using boost::generic::std_concept::TriviallyCopyAssignable;

BOOST_GENERIC_ASSERT( TriviallyCopyAssignable< int > );
BOOST_GENERIC_ASSERT( TriviallyCopyAssignable< copy_assignable_type > );
BOOST_GENERIC_ASSERT( TriviallyCopyAssignable< default_copy_assignable_type > );

BOOST_GENERIC_ASSERT_NOT( TriviallyCopyAssignable< nontrivial_copy_assignable_type > );
BOOST_GENERIC_ASSERT_NOT( TriviallyCopyAssignable< int& > );
BOOST_GENERIC_ASSERT_NOT( TriviallyCopyAssignable< noncopy_assignable_type > );
BOOST_GENERIC_ASSERT_NOT( TriviallyCopyAssignable< int() > );
BOOST_GENERIC_ASSERT_NOT( TriviallyCopyAssignable< int[] > );

BOOST_GENERIC_ASSERT_NOT( TriviallyCopyAssignable< void > );
