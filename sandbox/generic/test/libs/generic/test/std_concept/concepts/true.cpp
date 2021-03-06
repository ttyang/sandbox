/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/true.hpp>

#include <boost/generic/assert.hpp>

using boost::generic::std_concept::True;

BOOST_GENERIC_ASSERT( True< true > );
BOOST_GENERIC_ASSERT_NOT( True< false > );
