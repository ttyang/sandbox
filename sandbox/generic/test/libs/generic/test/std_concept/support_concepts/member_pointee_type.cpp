/*==============================================================================
    Copyright (c) 2011, 2012 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/support_concepts/member_pointee_type.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::MemberPointeeType;

BOOST_GENERIC_ASSERT( MemberPointeeType< int > );
BOOST_GENERIC_ASSERT( MemberPointeeType< int* > );
BOOST_GENERIC_ASSERT( MemberPointeeType< int const volatile > );
BOOST_GENERIC_ASSERT( MemberPointeeType< int() > );
BOOST_GENERIC_ASSERT( MemberPointeeType< int() const > );
BOOST_GENERIC_ASSERT( MemberPointeeType< int[4] > );
BOOST_GENERIC_ASSERT( MemberPointeeType< int[] > );

BOOST_GENERIC_ASSERT_NOT( MemberPointeeType< void > );
BOOST_GENERIC_ASSERT_NOT( MemberPointeeType< int& > );
