/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/assert.hpp>

#include <boost/generic/std_concept/concepts/copy_assignable.hpp>

struct noncopy_assignable_type
{
  noncopy_assignable_type& operator=( noncopy_assignable_type const& ) = delete;
};

using boost::generic::std_concept::CopyAssignable;

BOOST_GENERIC_ASSERT( CopyAssignable< int > );
BOOST_GENERIC_ASSERT( CopyAssignable< int& > );

BOOST_GENERIC_ASSERT_NOT( CopyAssignable< noncopy_assignable_type > );
BOOST_GENERIC_ASSERT_NOT( CopyAssignable< int() > );
BOOST_GENERIC_ASSERT_NOT( CopyAssignable< int[] > );

BOOST_GENERIC_ASSERT_NOT( CopyAssignable< void > );
