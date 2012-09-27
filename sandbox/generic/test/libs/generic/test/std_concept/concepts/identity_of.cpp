/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/identity_of.hpp>

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/support_concepts/same_type.hpp>

using boost::generic::std_concept::IdentityOf;
using boost::generic::std_concept::SameType;

BOOST_GENERIC_ASSERT( SameType< IdentityOf< int >::type, int > );
BOOST_GENERIC_ASSERT( SameType< IdentityOf< void >::type, void > );
BOOST_GENERIC_ASSERT( SameType< IdentityOf< int& >::type, int& > );
BOOST_GENERIC_ASSERT( SameType< IdentityOf< char() >::type, char() > );
BOOST_GENERIC_ASSERT( SameType< IdentityOf< int[] >::type, int[] > );

struct foo;
BOOST_GENERIC_ASSERT( SameType< IdentityOf< foo >::type, foo > );
