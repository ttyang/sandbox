/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/assert.hpp>
#include <boost/generic/std_concept/concepts/has_destructor.hpp>

struct no_destructor_type
{
  ~no_destructor_type() = delete;
};

using boost::generic::std_concept::HasDestructor;

BOOST_GENERIC_ASSERT( HasDestructor< int > );

BOOST_GENERIC_ASSERT( HasDestructor< int& > );

BOOST_GENERIC_ASSERT_NOT( HasDestructor< no_destructor_type > );
