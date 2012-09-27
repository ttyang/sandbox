/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/copy_constructible.hpp>

#include <boost/generic/assert.hpp>

struct noncopy_constructible_type
{
  noncopy_constructible_type( noncopy_constructible_type const& )
    = delete;
};

using boost::generic::std_concept::CopyConstructible;

BOOST_GENERIC_ASSERT( CopyConstructible< int > );
BOOST_GENERIC_ASSERT( CopyConstructible< int& > );

BOOST_GENERIC_ASSERT_NOT( CopyConstructible< noncopy_constructible_type > );
BOOST_GENERIC_ASSERT_NOT( CopyConstructible< int[] > );
BOOST_GENERIC_ASSERT_NOT( CopyConstructible< int() > );
BOOST_GENERIC_ASSERT_NOT( CopyConstructible< void > );
