/*==============================================================================
    Copyright (c) 2011 Matt Calabrese

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/generic/std_concept/concepts/has_swap.hpp>

#include <boost/generic/assert.hpp>

struct left_type_with_swap {};

struct right_type_with_swap {};

char swap( left_type_with_swap, right_type_with_swap );

using boost::generic::std_concept::HasSwap;

BOOST_GENERIC_ASSERT( HasSwap< left_type_with_swap, right_type_with_swap > );

BOOST_GENERIC_ASSERT_NOT( HasSwap< right_type_with_swap, left_type_with_swap > );

// TODO figure out a nice way to test these
//BOOST_GENERIC_ASSERT( HasSwap< int, int > );
