/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_virtual_destructor.hpp>

#include <boost/generic/assert.hpp>

struct nonvirtual_destructor_type {};

struct virtual_destructor_type
{
  virtual ~virtual_destructor_type();
};

using boost::generic::std_concept::HasVirtualDestructor;

BOOST_GENERIC_ASSERT( HasVirtualDestructor< virtual_destructor_type > );

BOOST_GENERIC_ASSERT_NOT( HasVirtualDestructor< int > );
BOOST_GENERIC_ASSERT_NOT( HasVirtualDestructor< void > );
BOOST_GENERIC_ASSERT_NOT( HasVirtualDestructor< int() > );
